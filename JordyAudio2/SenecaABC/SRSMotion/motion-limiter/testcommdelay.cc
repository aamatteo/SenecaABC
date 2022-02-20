/* ------------------------------------------------------------------   */
/*      item            : testcommdelay.cc
        made by         : Rene' van Paassen
        date            : 030306
	category        : body file 
        description     : Test of Blueheat opto serial IO latency
	changes         : 030306 first version
        language        : C++
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <sys/time.h>
#include <sched.h>
#include <iomanip>

inline int64_t getclock()
{
  timeval tv;
  gettimeofday(&tv, NULL);
  return int64_t(tv.tv_sec)*1000000 + tv.tv_usec;
}

const int BUFFLEN=88;

int main() 
{
  // open serial ports
  int fdout = open("/dev/ttyS04", O_WRONLY | O_NOCTTY /* | O_NDELAY*/);

  if (fdout == -1) {
    perror("opening ttyS04");
    exit(1);
  }

  // baudrate
  struct termios options;
  
  tcgetattr(fdout, &options);
  
  cfsetispeed(&options, B460800);
  cfsetospeed(&options, B460800);
  
  cfmakeraw(&options);
  options.c_cflag |= (CLOCAL | CREAD);
  
  // no parity
  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~CSTOPB;
  options.c_cflag &= ~CSIZE;
  options.c_cflag |= CS8;
  
  // disable hardware flow control
  options.c_cflag &= ~CRTSCTS;
  
  // set it
  tcsetattr(fdout, TCSANOW, &options);
  
  // output buffer
  int obuffer[22]; 
  for (int ii = 22; ii--; ) obuffer[ii] = ii;
  obuffer[4] = 0;
  obuffer[7] = 0x0d;
  
  // input port, inbuffer
  int fdin = open("/dev/ttyS05", O_RDONLY | O_NOCTTY);
  if (fdin == -1) {
    perror("opening ttyS05");
    exit(1);
  }

  //struct termios options;
  
  tcgetattr(fdin, &options);
  cfmakeraw(&options);
  
  cfsetispeed(&options, B460800);
  cfsetospeed(&options, B460800);
  
  options.c_cflag |= (CLOCAL | CREAD);
  
  // no parity
  options.c_cflag &= ~PARENB;
  options.c_cflag &= ~CSTOPB;
  options.c_cflag &= ~CSIZE;
  options.c_cflag |= CS8;
  
  // disable hardware flow control
  options.c_cflag &= ~CRTSCTS;
  
  // no software flow control
  options.c_iflag &= ~(IXON | IXOFF | IXANY);
  
  // set it
  tcsetattr(fdin, TCSANOW, &options);
  
  // buffer
  int ibuffer[22]; ibuffer[0] = 0;

  // test program
  const int NLOOPS = 100;
  int delay[NLOOPS];

  // flushing
  tcflush(fdin, TCIOFLUSH); 
  tcflush(fdout, TCIOFLUSH); 

  // over to real-time/FIFO
  sched_param rtpar; rtpar.sched_priority = 50;
  int err = sched_setscheduler(0, SCHED_FIFO, &rtpar);
  if (err) {
    perror("setting prio");
  }

  for (int ii = 0; ii < NLOOPS; ii++) {
    obuffer[0] = ii;
    int64_t start = getclock();
    int s = write(fdout, obuffer, BUFFLEN);
    if (s != BUFFLEN) {
      cerr << "incomplete write packet " << ii << endl;
      exit(1);
    }
    
    int r = read(fdin, ibuffer, BUFFLEN);
    delay[ii] = getclock() - start;
    if (r != BUFFLEN) {
      cerr << "incomplete read packet " << ii << endl;
      exit(1);
    }
    
    if (ibuffer[0] != ii) {
      cerr << "packet disparity, sent " << ii << " got " << ibuffer[0] << endl;
    }
    else {
      bool same = true;
      for (int jj = BUFFLEN/4; jj--; ) {
	same = same && (obuffer[jj] == ibuffer[jj]);
	if (obuffer[jj] != ibuffer[jj]) 
	  cerr << jj << ' ' << obuffer[jj] << "!=" << ibuffer[jj] << endl;
      }
      if (!same) {
	cerr << "packet error " << ii << endl;
      }
    }

    usleep(5000);
  }

  // loop and print
  for (int ii = 0; ii < NLOOPS; ii++) {
    cout << delay[ii] << endl;
  }
  
  return 0;
}

    
    
