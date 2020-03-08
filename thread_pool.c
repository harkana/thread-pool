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
    pool->tasks = NULL;
    pool->nb_tasks = 0;
    pool->len = size;
    pool->thread_alive = 0;
    pool->thread_working = 0;
    pthread_mutex_init(&pool->locker.lock, NULL);
    pthread_cond_init(&pool->locker.cond, NULL);
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
        usleep(1);
        pthread_cond_signal(&pool->locker.cond);
        pthread_mutex_unlock(&pool->locker.lock);
    }
    usleep(1);
    pthread_cond_destroy(&pool->locker.cond);
    pthread_mutex_destroy(&pool->locker.lock);
    for (i = 0; i < pool->len; i++)
    {
        destroy_thread(pool->threads[i]);
    }
    free(pool->threads);
    free(pool);
}
