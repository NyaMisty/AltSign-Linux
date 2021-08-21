#include <sys/socket.h>
#include <arpa/inet.h>

typedef struct timeval TIMEVAL;
#ifndef odslog
#define odslog(msg) { std::cout << msg << std::endl; }
#endif