#include "./Logger.h"

void Logger::log(const char *txt, int clock)
{
  printf("%c[%d;%dm [%d] [::%d]: ", 27, (1 + (rank / 7)) % 2, 31 + (6 + rank) % 7, rank, clock);
  printf(txt);
  printf("%c[%d;%dm\n", 27, 0, 37);
}