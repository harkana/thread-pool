#include "./thread_pool.h"

void    init_locker(t_locker *locker)
{
    pthread_mutex_init(&locker->lock, NULL);
    pthread_cond_init(&locker->cond, NULL);
}

void    exit_locker(t_locker *locker)
{
    pthread_cond_destroy(&locker->cond);
    pthread_mutex_destroy(&locker->lock);
}

void    wait_pool(t_locker *locker)
{
    pthread_mutex_lock(&locker->lock);
    pthread_cond_wait(&locker->cond, &locker->lock);
    pthread_mutex_unlock(&locker->lock);
}

void     post_pool(t_locker *locker)
{
    pthread_cond_signal(&locker->cond);
}

void     post_all_pool(t_locker *locker)
{
    pthread_cond_broadcast(&locker->cond);
}