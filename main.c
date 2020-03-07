#include "./thread_pool.h"

typedef void    (*defaultCallback)(void *);

void    func1()
{
    printf("Hello world ! %d\n", (int)pthread_self());
   // printf("thread id: %d\n", (int)pthread_self());
}

void    func2()
{
    printf("Salut les gens ! %d\n", (int)pthread_self());
    //printf("thread id: %d\n", (int)pthread_self());
}

int main(void)
{
    t_thread_pool   *pool;

    pool = init_pool(4);
    for (int i = 0; i < 25; i++)
    {
        add_worker(pool, (defaultCallback)&func1, NULL);
        add_worker(pool, (defaultCallback)&func2, NULL);
    }
    printf("destroy pool\n");
    destroy_pool(pool);
    return (EXIT_SUCCESS);
}