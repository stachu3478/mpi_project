#include "./ReceiverThread.h"

void ReceiverThread::start()
{
  while (1)
  {
    logger->debug("Czekam na recv");
    Message *message = lamportAdapter->receive();

    if (message->getTag() == Message.FINISH)
      break;

    /* code here */

    delete message;
  }
}
