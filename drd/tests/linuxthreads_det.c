/** Test whether DRD recognizes LinuxThreads as LinuxThreads and NPTL as
 *  NPTL.
 */


#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


static pthread_mutex_t s_mutex;
static pid_t s_main_thread_pid;


void* thread_func(void* arg)
{
  pid_t main_thread_pid;

  pthread_mutex_lock(&s_mutex);
  main_thread_pid = s_main_thread_pid;
  pthread_mutex_unlock(&s_mutex);

  if (s_main_thread_pid == getpid())
  {
    write(STDOUT_FILENO, "NPTL or non-Linux POSIX threads implementation detected.\n", 57);
  }
  else
  {
    write(STDOUT_FILENO, "Detected LinuxThreads as POSIX threads implementation.\n", 55);
  }
  return 0;
}

int main(int argc, char** argv)
{
  pthread_t threadid;

  pthread_mutex_init(&s_mutex, 0);

  pthread_mutex_lock(&s_mutex);
  s_main_thread_pid = getpid();
  pthread_mutex_unlock(&s_mutex);
  pthread_create(&threadid, 0, thread_func, 0);
  pthread_join(threadid, 0);

  pthread_mutex_destroy(&s_mutex);

  return 0;
}
