
#include "threadpool.h"

struct threadpool* threadpool_init(int thread_num, int queue_max_num)
{
  struct threadpool *pool = NULL;
  do
  {
    pool = (struct threadpool *) malloc(sizeof (struct threadpool));
    if (NULL == pool)
    {
		cout << ("failed to malloc threadpool!\n");
		break;
    }
    pool->thread_num = thread_num;
    pool->queue_max_num = queue_max_num;
    pool->queue_cur_num = 0;
    pool->head = NULL;
    pool->tail = NULL;
	pool->pthreads = new std::thread[thread_num];
    if (NULL == pool->pthreads)
    {
		cout << ("failed to malloc pthreads!\n");
		break;
    }
    pool->queue_close = 0;
    pool->pool_close = 0;
    int i;

    return pool;
  } while (0);

  return NULL;
}

int my_threadpool_add_job(struct threadpool* pool, threadjob callback_function, void *arg)
{
	assert(pool != NULL);
	assert(callback_function != NULL);
	assert(arg != NULL);


	if (pool->queue_cur_num >= pool->queue_max_num) //不能超过最带队列
	{
		return -1;
	}

	if (pool->queue_close || pool->pool_close) //队列关闭或者线程池关闭就退出
	{
		return -1;
	}
	struct job *pjob = (struct job*) malloc(sizeof (struct job));
	if (NULL == pjob)
	{
		return -1;
	}
	pjob->callback_function = callback_function;
	pjob->arg = arg;
	pjob->next = NULL;
	if (pool->head == NULL)
	{
		pool->head = pool->tail = pjob;
	} else
	{
		pool->tail->next = pjob;
		pool->tail = pjob;
	}
	pool->queue_cur_num++;
	return 0;
}

int threadpool_add_job(struct threadpool* pool, threadjob callback_function, void *arg)
{
	if (0 != my_threadpool_add_job(pool, callback_function, arg))
	{
		//cout << "quene full !!!!!!!!!add failed!" << endl;
		return -1;
	}

	//cout << "insert ok!!" << (char*) arg << endl;
	return 0;
}

void* threadpool_function(void* arg)
{

  
 
	return nullptr;
}

int threadpool_destroy(struct threadpool *pool)
{
	return 0;
}
