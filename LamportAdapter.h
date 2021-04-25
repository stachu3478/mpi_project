#pragma once

#include <mpi.h>
#include "Message.h"

class LamportAdapter : public MessageMaker
{
public:
  LamportAdapter();

  void send(int tag, int destination);
  void send(Message *m, int destination);
  Message *create(int tag) { create(tag, clock); };
  Message *receive();

private:
  int clock;
};
