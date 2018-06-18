#pragma once

#if !(defined(__FreeBSD__) || defined(__APPLE__) || defined(_MSC_VER))

/// https://stackoverflow.com/questions/20759750/resolving-redefinition-of-timespec-in-time-h
#define timespec linux_timespec
#define timeval linux_timeval
#include <linux/aio_abi.h>
#undef timespec
#undef timeval


/** Small wrappers for asynchronous I/O.
  */

int io_setup(unsigned nr, aio_context_t * ctxp);

int io_destroy(aio_context_t ctx);

/// last argument is an array of pointers technically speaking
int io_submit(aio_context_t ctx, long nr, struct iocb * iocbpp[]);

int io_getevents(aio_context_t ctx, long min_nr, long max_nr, io_event * events, struct timespec * timeout);


struct AIOContext : private boost::noncopyable
{
    aio_context_t ctx;

    AIOContext(unsigned int nr_events = 128);
    ~AIOContext();
};

#endif