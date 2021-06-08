#include "main.h"
#include "watek_komunikacyjny.h"

void addAck(int id) {
    if (!ackVector[id]) {
        ackVector[id] = TRUE;
        sem_post(&ackSemaphore);
    }
}

/* wątek komunikacyjny; zajmuje się odbiorem i reakcją na komunikaty */
void *startKomWatek(void *ptr)
{
    MPI_Status status;
    packet_t packet;
    /* Obrazuje pętlę odbierającą pakiety o różnych typach */
    while ( state!=InFinish ) {
	    debug("czekam na recv");
        MPI_Recv( &packet, 1, MPI_PAKIET_T, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
        pthread_mutex_lock(&lamportMut);
        lamportClock = MAX(packet.ts, lamportClock) + 1;
        pthread_mutex_unlock(&lamportMut);

        int priority = priorityFunc(packet);

        pthread_mutex_lock(&stateMut);
        switch ( status.MPI_TAG ) {
	    case FINISH:
            changeState(InFinish);
	    break;
	    case REQ:
            if (state == EnteringBar) {
                if (priority < barEntrancePriority) {
                    addAck(packet.src)
                    waitingForAck[waitingForAckCount++] = packet.src;
                    debug("Dostalem implicit ACK, odesle jak wyjde");
                } else if (priority > barEntrancePriority) {
                    debug("Za maly priorytet");
                } else {
                    println("Nie ma 2 wiadomosci z takim samym priorytetem! Wychodze");
                    exit(priority);
                }
            } else if (state == InBar) {
                waitingForAck[waitingForAckCount++] = packet.src;
                debug("Wysle ACK jak wyjde");
            } else {
                sendPacket(0, packet.src, ACK);
                debug("Wysylam ACK");
            }
	    break;
	    case ACK:
            if (state == EnteringBar) {
                if (priority < barEntrancePriority) {
                    addAck(packet.src)
                }
            }
	    break;
        }
        pthread_mutex_unlock(&stateMut);
    }
}
