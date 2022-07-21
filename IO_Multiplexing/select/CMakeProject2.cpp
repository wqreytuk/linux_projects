#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>

int select(int maxfdp1, fd_set* readset, fd_set* writeset, fd_set* exceptset,
    const struct timeval* timeout);
// if timeout param is null, wait forever
// if the value of timeout is 0, then select function will return immediately
// descriptor sets param, these three middle param
// they specify the descriptors that we want kernel to test for reading, writing and exception conditions
// exception conditions contains arrival of out-of-band data for socket and balh
// descriptor sets are just an array of integers
// every bit in integer is corresponding to a descriptor
// for example, a 32-bit integer can represent 0-31 descriptor
// then the second integer in the integer array can represent 32-63, et cetera
// we can use these four functions to manipulate fs_set
/******************
void FD_ZERO(fd_set *fdset);          // clear all bits in fdset
void FD_SET(int fd, fd_set *fdset);   // turn on the bit for fd in fdset
void FD_CLR(int fd, fd_set *fdset);   // turn off the bit for fd in fdset
int FD_ISSET(int fd, fd_set *fdset);  // is the bit for fd on in fdset ?
******************/
// and we can assign fd_set with =
// here I demonstrate how to turn on 1,4,5 descriptors
/*
fd_set rset;

FD_ZERO(&rset);          // initialize the set: all bits off
FD_SET(1, &rset);        // turn on bit for fd 1
FD_SET(4, &rset);        // turn on bit for fd 4
FD_SET(5, &rset);        // turn on bit for fd 5
*/
// any of the three middle fd_set param can be null if we're not interested
// if we set all these three middle param to null, then we get a sleep with more precise timer than sleep function, same as pool function
// the first param maxfdp1, this is the number of descriptors to be tested
// its value is the maximum fd to be test plus 1, which means fd 0,1,2,3...till maxfdp-1 are tested
// these three middle param is out param, means they will be modified by select
// they will indicate which fd is ready
/* Returns: positive count of ready descriptors, 0 on timeout, –1 on error */

// maximum number of fd for select, in fact, it is not limited, it is limited at the first time
// but now it is not, it is only limited by memory
// here is the definition of FD_SETSIZE in sys/types.h
/***
#ifndef FD_SETSIZE
#define FD_SETSIZE      256
#endif
***/
// but I did NOT find this definition in my sys/types.h
// we can NOT just define outselves FD_SETSIZE macro to get a larger FD_SETSIZE
// because the real FD_SETSIZE if defined in kernel, we can only change that and the recompile kernel to up the limit



struct timeval {
    long   tv_sec;          /* seconds */
    long   tv_usec;         /* microseconds */
};

