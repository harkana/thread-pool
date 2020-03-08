#include "./thread_pool.h"

t_thread_pool     *init_pool(int size) 
{
    t_thread_pool *pool;
    int           i;

    if ((pool = (t_thread_pool *)malloc(sizeof(*pool))) == NULL)
    {
        return (NULL);
    }
    if (size < 1){
        return (NULL);
    }
    pool->id = counter;
    pool->initialized = 1;
    if ((pool->tasks = (t_tasks *)malloc(sizeof(*(pool->tasks)))) == NULL)
    {
        return (NULL);
    }
    pool->tasks->node = NULL;
    pool->tasks->len = 0;
    pool->len = size;
    pool->thread_alive = 0;
    pool->thread_working = 0;
    init_locker(&pool->locker);
    init_locker(&pool->tasks->locker);
    if ((pool->threads = (t_thread **)malloc(sizeof(*(pool->threads)) * (size + 1))) == NULL)
    {
        return (NULL);
    }
    for (i = 0; i < size; i++)
    {
        init_thread(pool, i);
    }
    pool->threads[i] = 0;
    counter++;
    return (pool);
}

void    destroy_pool(t_thread_pool *pool)
{
    int i;

    pool->initialized = 0;
    while (pool->thread_alive > 0)
    {
        post_pool(&pool->tasks->locker);
    }
    exit_locker(&pool->tasks->locker);
    exit_locker(&pool->locker);
    destroy_tasks(pool->tasks);
    for (i = 0; i < pool->len; i++)
    {
        destroy_thread(pool->threads[i]);
    }
    free(pool->threads);
    free(pool);
}
