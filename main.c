#include "./thread_pool.h"

int main(void)
{
    t_thread_pool   *pool;

    pool = init_pool(4);
    destroy_pool(pool);
    return (EXIT_SUCCESS);
}