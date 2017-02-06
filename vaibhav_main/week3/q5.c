
/* first, lock the mutex */
int rc = pthread_mutex_lock(&a_mutex);
if (rc) { /* an error has occurred */
    perror("pthread_mutex_lock");
    pthread_exit(NULL);
}
/* mutex is now locked - wait on the condition variable.             */
/* During the execution of pthread_cond_wait, the mutex is unlocked. */
rc = pthread_cond_wait(&got_request, &a_mutex);
if (rc == 0) { /* we were awakened due to the cond. variable being signaled */
               /* The mutex is now locked again by pthread_cond_wait()      */
    /* do your stuff... */
    .
}
/* finally, unlock the mutex */ 
pthread_mutex_unlock(&a_mutex);


Now an example using the pthread_cond_timedwait() function: 


#include <sys/time.h>     /* struct timeval definition           */
#include <unistd.h>       /* declaration of gettimeofday()       */

struct timeval  now;            /* time when we started waiting        */
struct timespec timeout;        /* timeout value for the wait function */
int             done;           /* are we done waiting?                */

/* first, lock the mutex */
int rc = pthread_mutex_lock(&a_mutex);
if (rc) { /* an error has occurred */
    perror("pthread_mutex_lock");
    pthread_exit(NULL);
}
/* mutex is now locked */

/* get current time */ 
gettimeofday(&now);
/* prepare timeout value */
timeout.tv_sec = now.tv_sec + 5
timeout.tv_nsec = now.tv_usec * 1000; /* timeval uses microseconds.         */
                                      /* timespec uses nanoseconds.         */
                                      /* 1 nanosecond = 1000 micro seconds. */

/* wait on the condition variable. */
/* we use a loop, since a Unix signal might stop the wait before the timeout */
done = 0;
while (!done) {
    /* remember that pthread_cond_timedwait() unlocks the mutex on entrance */
    rc = pthread_cond_timedwait(&got_request, &a_mutex, &timeout);
    switch(rc) {
        case 0:  /* we were awakened due to the cond. variable being signaled */
                 /* the mutex was now locked again by pthread_cond_timedwait. */
            /* do your stuff here... */
            .
            .
            done = 0;
            break;
        case ETIMEDOUT: /* our time is up */
            done = 0;
            break;
        default:        /* some error occurred (e.g. we got a Unix signal) */
            break;      /* break this switch, but re-do the while loop.   */
    }
}
/* finally, unlock the mutex */
pthread_mutex_unlock(&a_mutex);
