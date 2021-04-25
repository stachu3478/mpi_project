#pragma once

#include "./Message.h"

class MessageMaker
{
public:
  MessageMaker(int processId) { this->processId = processId; };

  Message *create(int tag, int clock) { return create(processId, tag, clock); };
  Message *create(int processId, int tag, int clock) { return new Message(processId, tag, clock); };

private:
  int processId;
};