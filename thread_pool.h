#ifndef _THREAD_POOL_H_
# define _THREAD_POOL_H_

#include <pthread.h>

typedef struct s_task t_task;
typedef struct s_thread t_thread;
typedef struct s_thread_pool t_thread_pool;

struct s_thread_pool {
    int             id;
    int             initialized;
    t_task          *tasks;
    t_thread        *threads;
    int             len;
    int             nb_tasks;
};

struct s_thread {
    pthread_t       tid;
    void            (*handle)(struct s_thread *);
    t_thread_pool   *pool;
    pthread_mutex_t *locker;
};

struct s_task {
    struct s_job    *next;
    void            (*handle)(void *);
    void            *arg;
};

/*
    Init thread pool
*/
int     init_pool(t_thread_pool *, int);

/*
    Init thread
*/
int     init_thread(t_thread *);

/*
    Add task in thread pool
*/
int     add_worker(t_thread_pool *, void (*handle)(void *), void *);

/*
    Pull task in task list
*/
t_task  *pull_task(t_thread_pool *);

#endif