//SO IS1 224A LAB08
//Łukasz Watral
//lukasz_watral@zut.edu.pl


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char **argv){
	if(argc != 2){
	fprintf(stderr, "Argument needed!\n");
	return 1;
	}
	char str[strlen(argv[1])];
	strcpy(str, argv[1]);
	for(int i=0; i<strlen(str); i++){
		if(str[i]<48 || str[i]>57 || strlen(str)>25){
	fprintf(stderr, "Wrong argument!\n");
	return 1;
	}
	}
	if(strlen(str)==1){
	int r = atoi(str);
	return r;
	}
	char str1[strlen(str)/2];
	char str2[(strlen(str)/2)-strlen(str1)];
	for(int i=0; i<(strlen(str)/2); i++){
	str1[i] = str[i];
	str2[i] = str[i+strlen(str)/2];
	}
	if(strlen(str)%2==1){
	str2[strlen(str)/2] = str[strlen(str)-1];
	}
	pid_t fork1, fork2;
	if((fork1 = fork()) == 0){
		execl(argv[0], argv[0], str1, NULL);
	}
	else if((fork2 = fork()) == 0){
		execl(argv[0], argv[0], str2, NULL);
	}
	else{
		int r1, r2;
		waitpid(fork1,&r1,0);
		waitpid(fork2,&r2,0);
		printf("%d ", getpid());
		printf("%d \t%s %d\n",fork1, str1, WEXITSTATUS(r1));
		printf("%d ", getpid());
		printf("%d \t%s %d\n",fork2, str2, WEXITSTATUS(r2));
		return WEXITSTATUS(r1) + WEXITSTATUS(r2);
	}
}
