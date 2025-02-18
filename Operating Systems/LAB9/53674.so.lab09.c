//SO IS1 224A LAB09
//Łukasz Watral
//lukasz_watral@zut.edu.pl


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <windows.h>
#include <process.h>

int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr, "Argument needed!\n");
		return 1;
	}
	size_t length = strlen(argv[1]);
	char str[26] = {0};
	strcpy_s(str, argv[1]);
	for (int i = 0; i < length; i++) {
		if (str[i] < 48 || str[i]>57 || length > 25) {
			fprintf(stderr, "Wrong argument!\n");
			return 1;
		}
	}
	if (strlen(str) == 1) {
		int r = atoi(str);
		return r;
	}
	char str1[26] = {0};
	char str2[26] = {0};
	for (int i = 0; i < length/2; i++) {
		str1[i] = str[i];
		str2[i] = str[i + length / 2];
	}
	if (length % 2 == 1) {
		str2[strlen(str) / 2] = str[length - 1];
	}
	STARTUPINFOA si;
	PROCESS_INFORMATION pi1;
	PROCESS_INFORMATION pi2;
	memset(&si, 0, sizeof(si));
	memset(&pi1, 0, sizeof(pi1));
	memset(&pi2, 0, sizeof(pi2));
	char argline1[50];
	char argline2[50];
	sprintf_s(argline1, "%s %s", argv[0], str1);
	sprintf_s(argline2, "%s %s", argv[0], str2);
	si.cb = sizeof(si);
	if ((CreateProcessA(NULL, argline1, NULL, NULL, 0, 0, NULL, NULL, &si, &pi1)) == 0) {
		printf("Cant create process 1");
		return 1;
	}
	int id1 = GetProcessId(pi1.hProcess);
	if((CreateProcessA(NULL, argline2, NULL, NULL, 0, 0, NULL, NULL, &si, &pi2)) == 0) {
		printf("Cant create proces 2");
		return 1;
	}
	int id2 = GetProcessId(pi2.hProcess);
	DWORD r1;
	DWORD r2;
	WaitForSingleObject(pi1.hProcess, INFINITE);
	WaitForSingleObject(pi2.hProcess, INFINITE);
	GetExitCodeProcess(pi1.hProcess, &r1);
	GetExitCodeProcess(pi2.hProcess, &r2);
	fprintf(stdout, "\n%d %d\t%s %d", GetCurrentProcessId(), id1, str1, r1);
	fprintf(stdout, "\n%d %d\t%s %d", GetCurrentProcessId(), id2, str2, r2);
	return(r1 + r2);
}
