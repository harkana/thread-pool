#include "./thread_pool.h"

typedef void    (*defaultCallback)(void *);

int     count = 0;

void    func1()
{
    printf("Hello world ! %d\n", count);
    count++;
   // printf("thread id: %d\n", (int)pthread_self());
}

void    func2()
{
    printf("Salut les gens ! %d\n", count);
    count++;
    //printf("thread id: %d\n", (int)pthread_self());
}

int main(void)
{
    t_thread_pool   *pool;

    pool = init_pool(4);
    for (int i = 0; i < 25; i++)
    {
        add_worker(pool, (defaultCallback)&func2, NULL);
        add_worker(pool, (defaultCallback)&func1, NULL);
     }
    destroy_pool(pool);
    printf("count: %d\n", count);
    return (EXIT_SUCCESS);
}