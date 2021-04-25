#include <pthread.h>
#include "sys/param.h"
#include "main.h"
#include "watek_komunikacyjny.h"

/* wątek komunikacyjny; zajmuje się odbiorem i reakcją na komunikaty */
void * startKomWatek(void *ptr)
{
    MPI_Status status;
    int is_message = FALSE;
    packet_t pakiet;
    /* Obrazuje pętlę odbierającą pakiety o różnych typach */
    while ( stan!=InFinish ) {
	debug("czekam na recv");
	
        MPI_Recv( &pakiet, 1, MPI_PAKIET_T, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
	pthread_mutex_lock( &lamportMut ); 
	lamportClock = MAX(pakiet.ts, lamportClock) + 1;
	pthread_mutex_unlock( &lamportMut );
	
        switch ( status.MPI_TAG ) {
	    case FINISH: 
                changeState(InFinish);
	    break;
	    case TALLOWTRANSPORT: 
                changeTallow( pakiet.data);
                debug("Dostałem wiadomość od %d z danymi %d",pakiet.src, pakiet.data);
	    break;
	    case INRUN: 
                changeState( InRun );
                debug("Od tej chwili decyzję podejmuję autonomicznie i losowo");
	    break;
	    default:
	    break;
        }
    }
};

