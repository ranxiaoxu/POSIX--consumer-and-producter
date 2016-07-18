#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

#define _SIZE_ 64

int buf[_SIZE_];

sem_t space_nums;
sem_t data_nums;

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;

void *product(void *arg)
{
	int index = 0;
	while(1){
		sem_wait(&space_nums);
		
		pthread_mutex_lock(&lock1);
		
		buf[index] = rand() %1234;
		printf("producter done,data is %d\n",buf[index]);
		index++;
		index %= _SIZE_;

		sem_post(&data_nums);

		pthread_mutex_unlock(&lock1);
	}
}

void *consume(void *arg)
{

	int index = 0;
	while(1){
		sem_wait(&data_nums);
		
		pthread_mutex_lock(&lock2);

		int data = buf[index];
		printf("consumer done,data is %d\n",data);
		index++;
		index %= _SIZE_;

		sem_post(&space_nums);
		
		sleep(1);

		pthread_mutex_unlock(&lock2);
	}
}

int main()
{
	sem_init(&space_nums,0,_SIZE_);
	sem_init(&data_nums,0,0);

	pthread_t producter1,producter2,producter3,producter4;
	pthread_t consumer1,consumer2,consumer3;

	pthread_create(&producter1,NULL,product,NULL);
	pthread_create(&producter2,NULL,product,NULL);
	pthread_create(&producter3,NULL,product,NULL);
	pthread_create(&producter4,NULL,product,NULL);
	
	pthread_create(&consumer1,NULL,consume,NULL);
	pthread_create(&consumer2,NULL,consume,NULL);
	pthread_create(&consumer3,NULL,consume,NULL);
	
	pthread_join(producter1,NULL);
	pthread_join(producter2,NULL);
	pthread_join(producter3,NULL);
	pthread_join(producter4,NULL);
	
	pthread_join(consumer1,NULL);
	pthread_join(consumer2,NULL);
	pthread_join(consumer3,NULL);
	
	sem_destroy(&space_nums);
	sem_destroy(&data_nums);

	pthread_mutex_destroy(&lock1);
	pthread_mutex_destroy(&lock2);

	return 0;
}
