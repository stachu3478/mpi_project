#include "main.h"
#include "watek_glowny.h"

void mainLoop()
{
    srandom(rank);
    while (stan != InFinish) {
        /* code here */
        sleep(rand() % 5);
    }
}
