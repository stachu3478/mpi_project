#include "./LamportAdapter.h"

void LamportAdapter::send(int tag, int destination)
{
  int messageClock = clock++;
  Message *m = create(tag);
  send(m, destination);
  delete m;
}

void LamportAdapter::send(Message *m, int destination)
{
  MPI_Send(m->getClock(), 1, MPI_INT, destination, m->getTag(), MPI_COMM_WORLD);
}

Message *LamportAdapter::receive()
{
  int messageClock;
  MPI_Status status;
  MPI_Recv(&messageClock, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
  Message *m = new Message(status.MPI_SOURCE, status.MPI_TAG, messageClock);
  clock = (clock > messageClock ? clock : messageClock) + 1;
  return m;
}
