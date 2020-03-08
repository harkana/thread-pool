#include "./thread_pool.h"

void    destroy_worker(t_task *task)
{
    free(task);
}

void    destroy_tasks(t_tasks *tasks)
{
    t_task  *tmp;

    if (!tasks)
    {
        return;
    }
    tmp = NULL;
    while (tasks->node)
    {   
        tmp = tasks->node;
        tasks->node = tasks->node->next;   
        free(tmp);
    }
    free(tasks);
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
    task->next = pool->tasks->node;
    pool->tasks->node = task;
    pool->tasks->len++;
    post_pool(&pool->tasks->locker);
    return (1);
}

t_task  *pull_task(t_thread_pool *pool)
{
    t_task  *tasks;

    tasks = NULL;
    pthread_mutex_lock(&pool->tasks->locker.lock);
    tasks = pool->tasks->node;
    pool->tasks->len--;
    if (pool->tasks->node)
    {
        pool->tasks->node = pool->tasks->node->next;
    }
    if (tasks)
    {
        post_pool(&pool->tasks->locker);
    }
    pthread_mutex_unlock(&pool->tasks->locker.lock);
    return (tasks);
}