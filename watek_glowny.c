#include "main.h"
#include "watek_glowny.h"

void mainLoop()
{
    srandom(rank);
    while (state != InFinish) {
        /* code here */
        if (state === Mission) {
            sleep(rand() % 5);
            changeState(EnteringBar);
        } else if (state === EnteringBar) {
            pthread_mutex_lock(&lamportMut);
            sem_init(ackSemaphore, FALSE, barSize - size + 1);
            pkt->ts = ++lamportClock;
            packet_t packet;
            for (int i = 0; i < size; i++) {
                if (i != rank) {
                    sendPacket(packet, i, REQ);
                }
            }
            barEntrancePriority = priorityFunc(packet);
            pthread_mutex_unlock(&lamportMut);
            sem_wait(ackSemaphore);
            pthread_mutex_lock(&stateMut);
            sem_destroy(ackSemaphore);
            changeState(InBar);
        } else if (state === InBar) {
            sleep(rand() % 5);
            pthread_mutex_lock(&stateMut);
            changeState(Rest);
        } else if (state === Rest) {
            for (int i = 0; i < waitingForAckCount; i++) {
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
