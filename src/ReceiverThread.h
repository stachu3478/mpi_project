#pragma once

#include "./Message.h"
#include "./StateMachine.h"
#include "./Logger.h"

class ReceiverThread
{
public:
  ReceiverThread(){};
  void start(void *p);

  void setStateMachine(StateMachine *s) { stateMachine = s; };
  void setLamportAdapter(LamportAdapter *a) { lamportAdapter = a; };
  void setLogger(Logger *l) { logger = l; };

private:
  StateMachine *stateMachine;
  LamportAdapter *lamportAdapter;
  Logger *logger;
};
