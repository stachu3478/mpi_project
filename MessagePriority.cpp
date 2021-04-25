#include "MessagePriority.h"

MessagePriority::MessagePriority(int source, int clock)
{
  this->source = source;
  this->clock = clock;
};

bool MessagePriority::operator>(MessagePriority *v)
{
  if (clock > v->clock)
    return true;
  else if (clock == v->clock)
    return source > v->source;
}