#pragma once

#include <mpi.h>
#include "Message.h"
#include "StateMachine.h"

class ReceiverThread {
  public:
    ReceiverThread();
    void start();

    void setStateMachine(StateMachine s) { stateMachine = s; };
  private:
    StateMachine* stateMachine;
};
