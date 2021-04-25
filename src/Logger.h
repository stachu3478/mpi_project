#pragma once

class Logger
{
public:
  Logger(int rank) { this->rank = rank; };

  void log(const char *txt, int clock);

private:
  int rank;
};