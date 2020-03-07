#include "./thread_pool.h"

void    destroy_worker(t_task *task)
{
    free(task);
}
