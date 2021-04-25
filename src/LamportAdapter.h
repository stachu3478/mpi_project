#pragma once

#include <mpi.h>
#include "Message.h"

class LamportAdapter : public MessageMaker
{
public:
  LamportAdapter(int processId) : MessageMaker{processId};

  int getClock() { return clock; };

  void send(int tag, int destination);
  void send(Message *m, int destination);
  Message *create(int tag) { create(tag, clock++); };
  Message *receive();

private:
  int clock;
};
