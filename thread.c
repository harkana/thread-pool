#include "./thread_pool.h"

void    destroy_thread(t_thread *thread)
{
    free(thread);
}

void    running_thread(t_thread *thread)
{
    pthread_mutex_init(&thread->locker, NULL);
    while (thread->pool->initialized)
    {
        printf("%p\n", thread);
    }
    pthread_mutex_destroy(&thread->locker);
}

int     init_thread(t_thread_pool *pool, int i)
{
    t_thread    *thread;

    if (!pool || !pool->initialized)
    {
        return (0);
    }
    if (((thread) = (t_thread *)malloc(sizeof(*thread))) == NULL)
    {
        return (0);
    }
    thread->pool = pool;
    pthread_create(&thread->tid, NULL, (action)&running_thread, thread);
    pthread_detach(thread->tid);
    pool->threads[i] = thread;
    return (1);
}