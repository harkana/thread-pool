#include "./thread_pool.h"

void    destroy_thread(t_thread *thread)
{
    free(thread);
}

void    running_thread(t_thread *thread)
{
    thread->pool->thread_alive++;
    while (thread->pool->initialized)
    {
        thread->pool->thread_working++;
        pthread_mutex_lock(&thread->pool->locker.lock);
        pthread_cond_wait(&thread->pool->locker.cond, &thread->pool->locker.lock);
        if (thread->pool->initialized)
        {
            t_task  *tasks = pull_task(thread->pool);

            if (tasks)
            {
                tasks->handle(tasks->arg);
                pthread_cond_signal(&thread->pool->locker.cond);
                pthread_mutex_unlock(&thread->pool->locker.lock);
            }
        }
        thread->pool->thread_working--;
    }
    thread->pool->thread_alive--;
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