#pragma once

#include <mpi.h>
#include "Message.h"

class LamportAdapter {
  public:
    LamportAdapter();

    void send(int tag, int destination);
    Message* receive();
  private:
    int clock;
};
