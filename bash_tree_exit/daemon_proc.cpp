#include <chrono>
#include <iostream>
#include <thread>

#include <unistd.h>
#include <signal.h>

static void catchExit(int signal)
{
  std::cout << "EXITING (caught by signal catcher)" << std::endl;
}

static void catchHup(int signal)
{
  std::cout << "Caught SIGHUP" << std::endl;
  
  std::exit(128 + signal);
}

int main()
{
  std::cout << "Daemon PID: " << getpid() << std::endl;
  
  signal(SIGHUP, catchHup);
  // signal(SIGEXIT, catchExit);
  
  unsigned long iterations{0};
  
  using namespace std::chrono;
  while (true)
  {
    std::this_thread::sleep_for(1s);
    std::cout << "Still running; iterations = " << ++iterations << std::endl;
  }
  std::cout << "exiting" << std::endl;
}
