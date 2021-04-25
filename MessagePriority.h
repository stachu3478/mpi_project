#pragma once

class MessagePriority
{
public:
  MessagePriority(int source) { this->source = source; };
  MessagePriority(int source, int clock);
  bool operator>(MessagePriority *val);
  bool operator<(MessagePriority *val) { return val > this; };

  void setClock(int v) { clock = v; };
  int getClock() { return clock; };

private:
  int source;
  int clock;
};