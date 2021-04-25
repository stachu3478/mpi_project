#pragma once

#include "./MessagePriority.h"

class Message
{
public:
  Message(int source, int tag);
  Message(int source, int tag, int clock);

  int getTag() { return tag; };
  MessagePriority *getPriority() { return &priority; };
  void setClock(int v) { priority.setClock(v); };
  int getClock() { return priority.getClock(); };

private:
  MessagePriority priority;
  int tag;
}
