#pragma once

#include <mpi.h>
#include "./Message.h"
#include "./StateMachine.h"

class ReceiverThread
{
public:
  ReceiverThread();
  void start();

  void setStateMachine(StateMachine s) { stateMachine = s; };
  void setLamportAdapter(LamportAdapter a) { lamportAdapter = a; };

private:
  StateMachine *stateMachine;
  LamportAdapter *lamportAdapter;
};
