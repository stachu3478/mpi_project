#include "./ReceiverThread.h"

void ReceiverThread::start(void *p)
{
  while (1)
  {
    logger->log("Czekam na recv", lamportAdapter->getClock());
    Message *message = lamportAdapter->receive();

    if (message->getTag() == Message.FINISH)
    {
      stateMachine->setState(STOP);
      break;
    }

    /* code here */

    delete message;
  }
}
