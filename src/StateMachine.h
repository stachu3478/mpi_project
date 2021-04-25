#pragma once

typedef enum
{
  REST,
  MISSION,
  WAIT_FOR_BAR,
  BAR,
  STOP
} State;

class StateMachine
{
public:
  StateMachine();

  void setState(State s) { state = s; };
  State getState() { return state; };

private:
  State state;
};