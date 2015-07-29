/*
 * 程序清单 12-5 线程安全的 getenv 的兼容版本
 */

#include <limits.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>

static pthread_key_t key;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;
pthread_mutex_t env_mutex = PTHREAD_MUTEX_INITIALIZER;

extern char **environ;

static void
thread_init(void)
{
  pthread_key_create(&key, free);
}

char *
getenv(const char *name)
{
  int i, len;
  char *envbuf;

  pthread_once(&init_done, thread_init);
  pthread_mutex_lock(&env_mutex);
  envbuf = (char *)pthread_getspecific(key);
  if (envbuf == NULL) {
    envbuf = malloc(ARG_MAX);
    if (envbuf == NULL) {
      pthread_mutex_unlock(&env_mutex);
      return NULL;
    }
    pthread_setspecific(key, envbuf);
  }
  len = strlen(name);
  for (i = 0; environ[i] != NULL; i++) {
    if ((strncmp(name, environ[i], len) == 0) &&
        (environ[i][len] == '=')) {
      strcpy(envbuf, &environ[i][len+1]);
      pthread_mutex_unlock(&env_mutex);
      return envbuf;
    }
  }
  pthread_mutex_unlock(&env_mutex);
  return NULL;
}

/* figure12-5.c ends here */
