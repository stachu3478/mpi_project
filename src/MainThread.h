#pragma once

#include "./Message.h"
#include "./StateMachine.h"
#include "./Logger.h"

class MainThread
{
public:
  MainThread(){};
  void start();

  void setStateMachine(StateMachine *s) { stateMachine = s; };
  void setLamportAdapter(LamportAdapter *a) { lamportAdapter = a; };
  void setLogger(Logger *l) { logger = l; };

private:
  StateMachine *stateMachine;
  LamportAdapter *lamportAdapter;
  Logger *logger;
};