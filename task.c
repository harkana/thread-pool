#include "./thread_pool.h"

void    destroy_worker(t_task *task)
{
    free(task);
}

int    add_worker(t_thread_pool *pool, void (*handle)(void *), void *arg)
{
    t_task  *task;

    if ((task = (t_task *)malloc(sizeof(*task))) == NULL)
    {
        return (0);
    }
    task->pool = pool;
    task->handle = handle;
    task->arg = arg;
    task->next = pool->tasks;
    pool->tasks = task;
    pool->nb_tasks++;
    usleep(1);
    pthread_cond_signal(&pool->locker.cond);
    pthread_mutex_unlock(&pool->locker.lock);
    return (1);
}

t_task  *pull_task(t_thread_pool *pool)
{
    t_task  *tasks;

    tasks = pool->tasks;
    if (pool->tasks)
    {
        pool->tasks = pool->tasks->next;
    }
    if (tasks)
    {
        pool->nb_tasks--;
    }
    return (tasks);
}