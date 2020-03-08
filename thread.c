#include "./thread_pool.h"

void    destroy_thread(t_thread *thread)
{
    free(thread);
}

void    running_thread(t_thread *thread)
{
    pthread_mutex_lock(&thread->pool->locker.lock);
    thread->pool->thread_alive++;
    pthread_mutex_unlock(&thread->pool->locker.lock);
    while (thread->pool->initialized || thread->pool->tasks->len > 0)
    {
        wait_pool(&thread->pool->tasks->locker);
        if (thread->pool->initialized || thread->pool->tasks->len > 0)
        {
            pthread_mutex_lock(&thread->pool->locker.lock);
            thread->pool->thread_working++;
            pthread_mutex_unlock(&thread->pool->locker.lock);
            t_task  *tasks = pull_task(thread->pool);
            if (tasks)
            {
                pthread_mutex_lock(&thread->pool->locker.lock);
                tasks->handle(tasks->arg);
                free(tasks);
                thread->pool->thread_working--;
                if (thread->pool->thread_working == 0)
                {
                    pthread_cond_signal(&thread->pool->locker.cond);
                }
                pthread_mutex_unlock(&thread->pool->locker.lock);
            }
        }
    }
    pthread_mutex_lock(&thread->pool->locker.lock);
    thread->pool->thread_alive--;
    pthread_mutex_unlock(&thread->pool->locker.lock);
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