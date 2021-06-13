#ifndef WATEK_GLOWNY_H
#define WATEK_GLOWNY_H

/* po losowym czasie (1..t) zmienia stan */
void waitAndChangeState();
/* wysyła wiadmomości REQ i oczekuje na ACK  */
void getEntryPermission();
/* pętla główna aplikacji: zmiany stanów itd */
void mainLoop();

#endif
