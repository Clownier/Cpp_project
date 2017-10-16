#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<fstream>
#include <vector>
#include<string>
#include"STACK.h"
using namespace std;
char * getOpenFile(char * filename) {
	char *openfile= strtok(filename, ".");
	char *file = strtok(NULL,".") ;
	while (file&&strcmp(file,"exe")) {
		strcat(openfile, file);
		file = strtok(NULL, ".");
	}
	strcat(openfile, ".txt");
	return openfile;
}
int main(int argc,char *argv[]) {
	char *openfile = getOpenFile(argv[0]);
	printf("file = %s\n", openfile);
	ofstream write;
	write.open(openfile);
	if (!write.is_open()) {
		exit(-1);
	}
	write << "this is version 1.0";
	write.close();
	return 0;
}