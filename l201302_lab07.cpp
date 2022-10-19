#include<iostream>
#include<fcntl.h>
#include <sys/wait.h>
#include<unistd.h>
#include<cstring>
#include<string>
using namespace std;

void printArray(int* array, int size){
    for(int i=0; i < size; i++)
        cout<<array[i]<<endl;
}

int* readArray(int fd, int& size){
    char str[100];
    int r =read(fd,&str,sizeof(str));
	
    char str2[100];
    strcpy(str2,str);
    char* num = strtok(str," ");
	
     size = 0;
    for (;num != NULL;){
        num = strtok(NULL," ");
        size++;
    }

    int* num1 = new int [size];
    char* m = strtok(str2," ");
    num1[0] = atoi(m);
    int i =1;
    for (;m != NULL;){
        m = strtok(NULL," ");
        if (m!=NULL) {
            num1[i] = atoi(m);
            i++;
        }else break;
    }
    return num1;
}

int* calculateSum(int* arr1 , int size1, int* arr2, int size2, int& resultSize){
	int largeSize = 0;
	int smallSize = 0;
	bool smallArr = false;
	if (size1 > size2){
		largeSize = size1;
		smallSize = size2;
		smallArr = true;
	}
	else{ 
		largeSize = size2;
		smallSize = size1;
	}
	
	int* result = new int [largeSize];
	
	int index =0;
	for (; index < smallSize; index++)
		result[index] = arr1[index] + arr2[index];
	
	if (smallArr == true){
		for (; index < largeSize; index++)
			result[index] = arr1[index];
	}
	else {
				for (; index < largeSize; index++)
					result[index] = arr2[index];
	}
	resultSize = largeSize;
	return result;
}

int main(int argc, char* argv[]){

    int pfd[2];
    pipe(pfd);

    pid_t id = fork();

    if (id > 1){
	int size1 = strlen(argv[1]) + strlen(".txt");
	int size2 = strlen(argv[2]) + strlen(".txt");
		
	char file1[size1];
        char file2[size2];


        strcpy(file1,argv[1]);
	strcat(file1, ".txt");
		
        strcpy(file2,argv[2]);
        strcat(file2, ".txt");

	write(pfd[1], &file1, strlen(file1));
	write(pfd[1], &file2, strlen(file2));

        close(pfd[1]);
        close(pfd[0]);

    }

    if (id ==0 ){
        close(pfd[1]);
        //cout<<"Child"<<endl;
		
	int s1 = strlen(argv[1]) + strlen(".txt");
	int s2 = strlen(argv[2]) + strlen (".txt");
	char file1 [s1];
	char file2 [s2];

	read(pfd[0], &file1, s1);
	read(pfd[0], &file2, s2);
	
	
	int fd1 = open(file1,O_CREAT | O_RDONLY, 0644);
	
	int fd2 = open(file2,O_CREAT | O_RDONLY, 0644);
	
	
	int size1 = 0; 
	int size2 = 0;
	int* arr1 = readArray(fd1 ,size1);
        int* arr2 = readArray(fd2, size2);
		
		
        printArray(arr1,size1);
        printArray(arr2,size2);
		
	int resSize = 0;
	int* res = calculateSum(arr1,size1,arr2,size2,resSize);
	int resfd = open ("file3.txt" ,  O_WRONLY  | O_CREAT, 0644);
	close(1);
	dup2(resfd,1);	
		
		
	printArray(res,resSize);
	close(resfd);
	close(fd1);
	close(fd2);

        close(pfd[0]);
    }


    if (id < 0){
        cout<<"Pipe error"<<endl;
    }
}
