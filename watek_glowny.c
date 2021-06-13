#include "main.h"
#include "watek_glowny.h"

int i;


void getEntryPermission()
{
	sem_init(&ackSemaphore, FALSE, 0);
            packet_t packet;
            packet.ts = ++lamportClock;
            for (i = 0; i < size; i++) {
                if (i != rank) {
                    sendPacket(&packet, i, REQ);
                }
                ackVector[i] = FALSE;
            }
            barEntrancePriority = priorityFunc(packet);
                debug("Czekam na %d x ACK moj priorytet %d", barSize - size + 2, barEntrancePriority);
            pthread_mutex_unlock(&lamportMut);
            for (i = 0; i < size - barSize; i++)
                    sem_wait(&ackSemaphore);
            pthread_mutex_lock(&stateMut);
            sem_destroy(&ackSemaphore);
}

void waitAndChangeState( state_t state, int t)
{
	sleep(rand() % t);
	changeState(state);
}

void mainLoop()
{
    srandom(rank);
    while (state != InFinish) {
        if (state == Mission) {
            waitAndChangeState(EnteringBar, 5);
            println("Czekam na bar");
        } else if (state == EnteringBar) {
            pthread_mutex_lock(&lamportMut);
	    getEntryPermission();
            changeState(InBar);
	        println("Wchodze do baru");
        } else if (state == InBar) {
            waitAndChangeState(Rest, 5);
            println("Wychodze z baru");
        } else if (state == Rest) {
            for (i = 0; i < waitingForAckCount; i++) {
                sendPacket(0, waitingForAck[i], ACK);
            }
            waitingForAckCount = 0;
            waitAndChangeState(Mission, 5);
        } else {
            printf("Zły stan: %d", state);
            exit(state);
        }
    }
}
