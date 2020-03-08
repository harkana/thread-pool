#ifndef _THREAD_POOL_H_
# define _THREAD_POOL_H_

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <errno.h>
#include <time.h>

typedef struct s_task           t_task;
typedef struct s_thread         t_thread;
typedef struct s_thread_pool    t_thread_pool;
typedef struct s_locker         t_locker;
typedef struct s_tasks          t_tasks;

typedef void   *(*action)(void *);

struct s_locker {
    pthread_mutex_t lock;
    pthread_cond_t  cond;
};

struct s_thread_pool {
    int             id;
    int             initialized;
    t_tasks         *tasks;
    t_thread        **threads;
    int             len;
    t_locker        locker;
    int             thread_alive;
    int             thread_working;
 };

struct s_thread {
    pthread_t       tid;
    t_thread_pool   *pool;
};

struct s_task {
    t_task          *next;
    void            (*handle)(void *);
    void            *arg;
    t_thread_pool   *pool;
};

struct s_tasks {
    int         len;
    t_task      *node;
    t_locker    locker;
};

/*
    Init thread pool
*/
t_thread_pool   *init_pool(int);
void            destroy_pool(t_thread_pool *);

/*
    Init thread
*/
int     init_thread(t_thread_pool *, int);
void    destroy_thread(t_thread *);
void    running_thread(t_thread *);

/*
    Add task in thread pool
*/
int     add_worker(t_thread_pool *, void (*handle)(void *), void *);
void    destroy_tasks(t_tasks *);
void    destroy_worker(t_task *);

/*
    Pull task in task list
*/
t_task  *pull_task(t_thread_pool *);

void    init_locker(t_locker  *);
void    exit_locker(t_locker *);
void    wait_pool(t_locker *);
void    post_pool(t_locker *);
void    post_all_pool(t_locker *);

int        counter;
extern int counter;

#endif
