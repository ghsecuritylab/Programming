/*
 * 程序清单 15-7 调用大写/小写过滤程序以读取命令
 */

#include "apue.h"
#include <sys/wait.h>

int
main(void)
{
  char line[MAXLINE];
  FILE *fpin;

  if ((fpin = popen("myuclc", "r")) == NULL)
    err_sys("popen error");
  for ( ; ; ) {
    fputs("prompt> ", stdout);
    fflush(stdout);
    if (fgets(line, MAXLINE, fpin) == NULL) /* read from pipe */
      break;
    if (fputs(line, stdout) == EOF)
      err_sys("fputs error to pipe");
  }
  if (pclose(fpin) == -1)
    err_sys("pclose error");
  putchar('\n');
  exit(0);
}

/* figure15-7.c ends here */
