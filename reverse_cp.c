//Joseph Pallansch
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

int main(int argc, char **argv){
	//wrong number of arguments
	if(argc != 3){
		printf("This program takes two arguments\n");
		printf("The first one is the file to be copied and reversed\n");
		printf("The second is the name of the new file destination\n");
		exit(0);
	}

	int fd1;
	int fd2;
	int fd3;
	
	fd1 = open(argv[1], O_RDONLY);
	fd3 = open(argv[2], O_RDONLY);
	//destination file already exists
	if(fd3>0){
		printf("Destination file exists already\n");
		printf("Please restart with a name for a new file to create\n");
		exit(0);
	}
	fd2 = open(argv[2], O_CREAT | O_RDWR, 0666);
	//error opening first file
	if(fd1<0){
		printf("Please input a valid file to be reversed as your first argument\n");
		exit(0);
	}
	//error opening destination file
	if(fd2<0){
		printf("Error creating destination file\n");
		exit(0);
	}
	int size = lseek(fd1, 0, SEEK_END);
	//occurs if file is empty
	if(size <= 0){
		printf("Can not find anything to be copied in this file\n");
		exit(0);
	}
	int bound = size*(-1);
	int n = -1;
	char buffer[1] = {0};
	int a = 0;
	int b = 0;
	
	//when n < bound then the whole file has been copied
	while(n >= bound){
		//n moves cursor back away from the end of file
		lseek(fd1, n, SEEK_END);
		a = read(fd1, buffer, 1);
		//occurs if problem reading the file
		if(a<=0){
			printf("Error reading file\n");
			exit(0);
		}
		b = write(fd2, buffer, 1);
		//occurs if problem writing to the file
		if(b<=0){
			printf("Error writing to file\n");
			exit(0);
		}
		n--;
	}
	
	close(fd1);
	close(fd2);

	printf("The program has finished copying!\n");
	
	return 0;
}
