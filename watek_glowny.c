#include "main.h"
#include "watek_glowny.h"

int i;
void mainLoop()
{
    srandom(rank);
    while (state != InFinish) {
        /* code here */
        if (state == Mission) {
            sleep(rand() % 5);
            changeState(EnteringBar);
            println("Czekam na bar");
        } else if (state == EnteringBar) {
            pthread_mutex_lock(&lamportMut);
            sem_init(&ackSemaphore, FALSE, -1);
            packet_t packet;
            packet.ts = ++lamportClock;
            for (i = 0; i < size; i++) {
                if (i != rank) {
                    sendPacket(&packet, i, REQ);
                }
            }            
            barEntrancePriority = priorityFunc(packet);
	    debug("Czekam na %d x ACK moj priorytet %d", barSize - size + 2, barEntrancePriority);
            pthread_mutex_unlock(&lamportMut);
	    for (i = 0; i < size - barSize; i++)
		sem_wait(&ackSemaphore);
            sem_wait(&ackSemaphore);
            pthread_mutex_lock(&stateMut);
            sem_destroy(&ackSemaphore);
            changeState(InBar);
	    println("Wchodze do baru");
        } else if (state == InBar) {
            sleep(rand() % 5);
            pthread_mutex_lock(&stateMut);
            changeState(Rest);
            println("Wychodze z baru");
        } else if (state == Rest) {
            for (i = 0; i < waitingForAckCount; i++) {
                sendPacket(0, waitingForAck[i], ACK);
            }
            waitingForAckCount = 0;
            sleep(rand() % 5);
            changeState(Mission);
        } else {
            printf("Zły stan: %d", state);
            exit(state);
        }
    }
}
