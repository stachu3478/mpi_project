#pragma once

#include "./MessagePriority.h"

class Message
{
public:
  Message(int source, int tag) : priority{source} { this->tag = tag; };
  Message(int source, int tag, int clock) : priority{source, clock} { this->tag = tag; };

  int getTag() { return tag; };
  MessagePriority *getPriority() { return &priority; };
  void setClock(int v) { priority.setClock(v); };
  int getClock() { return priority.getClock(); };

  const static int FINISH = 1;
  const static int REQ = 2;
  const static int ACK = 3;

private:
  MessagePriority priority;
  int tag;
};
