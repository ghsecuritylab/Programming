/*
 * 程序清单 17-6 s_pipe 函数的套接字版本
 */

#include "apue.h"
#include <sys/socket.h>

/*
 * Returns a full-duplex "stream" pipe (a UNIX domain socket)
 * with the two file descriptors returned in fd[0] and fd[1].
 */
int
s_pipe(int fd[2])
{
  return socketpair(AF_UNIX, SOCK_STREAM, 0, fd);
}

/* figure17-6.c ends here */
