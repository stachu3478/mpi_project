#include "MainThread.h"

void MainThread::start()
{
  stateMachine->setState(MISSION);
  while (stateMachine->getState() != STOP)
  {
    /* code here */
    sleep(2);
    stateMachine->setState(REST);
    sleep(2);
    stateMachine->setState(MISSION);
  }
};