//SO IS1 224A LAB10
//Łukasz Watral
//lukasz_watral@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

double sum = 0.0;

typedef struct{
	int size;
	int first_index;
	pthread_mutex_t *mutex;
	double part_sum;
	pthread_t name;
}ThreadData;

double pi_part(int n){
	if(n==0) return 3.0;
	if (n % 2 == 1) {
            return (4.0 / ((2 * n) * (2 * n + 1) * (2 * n + 2 )));
            }
       	if (n % 2 == 0){
            return (-(4.0 / ((2 * n) * (2 * n + 1) * (2 * n + 2))));
        }
}

void *thread(void *data) {
ThreadData *msg = (ThreadData *) data;
double tmp_sum = 0.0;
for(int i = msg->first_index; i<(msg->first_index+msg->size); i++){
	tmp_sum += pi_part(i);
}
pthread_t self = pthread_self();
srand(self);
pthread_mutex_lock(msg->mutex);
sum += tmp_sum;
pthread_mutex_unlock(msg->mutex);
printf("Thread %lxd size=%d first==%d\n", self, msg->size, msg->first_index);
msg->part_sum = tmp_sum;
msg->name = self;
}

int main(int argc, char **argv){
	if(argc != 3){
	fprintf(stderr, "Argument needed!\n");
	return 1;
	}
	int n = atoi(argv[1]);
	int w = atoi(argv[2]);
	if(n<=1 || n>=1000000 || w<=1 || w>=n || w>=100){
		fprintf(stderr, "Wrong argument!\n");
	return 1;
	}
	struct timespec begin;
	struct timespec end;
	pthread_mutex_t mymutex = PTHREAD_MUTEX_INITIALIZER;
	pthread_t threads[w];
	ThreadData data[w];
	int first = 0;
		clock_gettime(CLOCK_MONOTONIC, &begin);
		for(int i = 0; i<w-1; i++){
			data[i].size = n/w;
			data[i].first_index = first;
			data[i].mutex = &mymutex;
			data[i].part_sum = 0.0;
			pthread_create(&threads[i], NULL, thread, (void *) &data[i]);
			first += n/w;
		}
			data[w-1].size = (n/w)+(n%w);
			data[w-1].first_index = first;
			data[w-1].mutex = &mymutex;
			data[w-1].part_sum = 0.0;
			pthread_create(&threads[w-1], NULL, thread, (void *) &data[w-1]);
	for(int i = 0; i < w; i++){
		pthread_join(threads[i], NULL);
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	for(int i =0; i < w; i++){
		printf("Thread %lxd sum=%.20f\n", data[i].name,data[i].part_sum);
	}
	double time = (end.tv_sec-begin.tv_sec)+(end.tv_nsec-begin.tv_nsec)/1000000000.0;
	printf("w/Threads PI=%.20f time=%f\n", sum, time);
	double sum_tmp = 0.0;
	clock_gettime(CLOCK_MONOTONIC, &begin);
	for(int i=0; i<n; i++){
		sum_tmp += pi_part(i);
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	time = (end.tv_sec-begin.tv_sec)+(end.tv_nsec-begin.tv_nsec)/1000000000.0;
	printf("wo/Threads PI=%.20f time=%f\n ", sum_tmp, time);
	
return 0;
}
