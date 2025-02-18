// SO IS1 224A LAB11
// Łukasz Watral
// lukasz_watral@zut.edu.pl

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>


float sum = 0.0;

typedef struct {
	int size;
	int first_index;
	HANDLE mutex;
	float part_sum;
	float* tab;
	DWORD name;
}ThreadData;


DWORD WINAPI thread(LPVOID data) {
	ThreadData* msg = (ThreadData*)data;
	float tmp_sum = 0.0;
	for (int i = msg->first_index; i < (msg->first_index + msg->size); i++) {
		tmp_sum += msg->tab[i];
	}
	DWORD self = GetCurrentThreadId();
	srand(self);
	fprintf(stdout, "Thread #%xd size=%d\n", self, msg->size);
	WaitForSingleObject(msg->mutex, INFINITE);
	sum += tmp_sum;
	ReleaseMutex(msg->mutex);
	msg->name = self;
	msg->part_sum = tmp_sum;
	return 0;
}

int main(int argc, char** argv) {
	if (argc != 3) {
		fprintf(stderr, "Argument needed!\n");
		return 1;
	}
	int n = atoi(argv[1]);
	int w = atoi(argv[2]);
	if (n <= 0 || n >= 1000000 || w <= 0 || w >= n) {
		fprintf(stderr, "Wrong argument!\n");
		return 1;	
	}
	float* t = (float*)malloc(n * sizeof(float));
	srand(0);
	for (int i = 0; i < n;i++) {
		t[i] = 1000. * rand() / RAND_MAX;
	}
	HANDLE* threads = (HANDLE*)malloc(w * sizeof(HANDLE));
	DWORD* tid = (DWORD*)malloc(w * sizeof(DWORD));
	ThreadData* data = (ThreadData*)malloc(w * sizeof(ThreadData));
	int first = 0;
	HANDLE mymutex = CreateMutex(NULL, FALSE, NULL);
	double time = 0.0;
	clock_t t1, t2;
	t1 = clock();
	for (int i = 0; i < w - 1; i++) {
		data[i].size = n / w;
		data[i].first_index = first;
		data[i].mutex = &mymutex;
		data[i].part_sum = 0.0;
		data[i].tab = t;
		threads[i] = CreateThread(NULL, 0, thread, data + i, 0, tid + i);
		first += n / w;
	}
	data[w - 1].size = (n / w) + (n % w);
	data[w - 1].first_index = first;
	data[w - 1].mutex = &mymutex;
	data[w - 1].part_sum = 0.0;
	data[w - 1].tab = t;
	threads[w-1] = CreateThread(NULL, 0, thread, data + (w-1), 0, tid + (w-1));
	for (int i = 0; i < w; i++) {

		WaitForSingleObject(threads[i], INFINITE);
		CloseHandle(threads[i]);
	}
	t2 = clock();
	for (int i = 0; i < w; i++) {
		fprintf(stdout, "Thread #%lxd sum=%f\n", data[i].name, data[i].part_sum);
	}
	time = (double)((t2 - t1 - 0.) / CLOCKS_PER_SEC);
	fprintf(stdout, "w/Threads sum=%f, %fsec\n", sum, time);
	double sum_tmp = 0.0;
	t1 = clock();
	for (int i = 0; i < n; i++) {
		sum_tmp += t[i];
	}
	t2 = clock();
	time = (double)((t2 - t1 - 0.) / CLOCKS_PER_SEC);
	fprintf(stdout, "wo/Threads sum=%f, %fsec\n", sum_tmp, time);
	free(t);
	free(threads);
	free(tid);
	free(data);
	return 0;
}
