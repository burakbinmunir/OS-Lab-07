#include<iostream>
#include<cstring>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>
using namespace std;
/*

void printArray(int* array, int size){
    for(int i=0; i < size; i++)
        cout<<array[i]<<endl;
}

int* readArray(int fd, int& size){
    char str[100];
    int r = read(fd,&str,sizeof(str));
	
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
        }
        else break;
    }
    return num1;
}*/
/*
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

*/
int main (int argc,char* argv[]){

    int fd[2];

    pipe(fd);

    int retVal = fork();

    if (retVal > 0) { // parent

        int s1  = strlen(argv[1]) + strlen(".txt");
        int s2  = strlen(argv[2]) + strlen(".txt");

        char file1[s1];
        char file2[s2];


        strcpy(file1,argv[1]);
        strcat(file1,".txt");
                string str = file1;
                cout<<str;
                string str2 = file2;
        strcpy(file2, argv[2]);
        strcat(file2, ".txt");

        //file1[s1-1] = '\0';
        //file2[s2-1] = '\0';
        
	write(fd[1], &str, strlen(file1));
        write(fd[1], &str2, strlen(file2));

       // int file1_fd = open(file1, O_RDONLY, 0644);
       // int file2_fd = open(file2, O_RDONLY , 0644);

        write(fd[1], &file1_fd, sizeof(int));
        write(fd[1], &file2_fd, sizeof(int));
        //cout<<file1<<file2<<endl;
//        cout<<file1_fd<<file2_fd<<endl;

        close(fd[1]);
        close(fd[0]);
    }

    if (retVal == 0) {
        int f1;
        cout<<"Child";
        int f2;
        read(fd[0], &f1, sizeof(int));
        read(fd[0], &f2, sizeof(int));
        cout<<f1<<f2;
        /*int size1 =0, size2 =0 , resSize =0 ;
        int * arr = readArray(f1,size1);
        int * arr2 = readArray(f2, size2);
        cout<<size1;
        printArray(arr,size1);
        printArray(arr,size2);*/

       /* int s1  = strlen(argv[1]) + strlen(".txt");
        int s2  = strlen(argv[2]) + strlen(".txt");

        char file1[s1];
        char file2[s2];
       

        read(fd[0], &file1, s1);
        read(fd[0], &file2, s2);

      //  cout<<s1<<" "<<strlen(file1)<<" " <<s2<<" "<<strlen(file2)<<endl;
        file2[s1] = '\0';
        file2[s2] = '\0';
        //cout<<file1<<"\n"<<file2<<endl;

        char tr[s1];
        int i=0;
        for (; i < s1; i++){
            tr[i] = file1[i];
        }
        ///tr[i] = '\0';
        cout<<"Trimmed" <<tr;
*/

    }

    if (retVal < 0 ){
        cout<<"Error while forking";
        perror("fork");
    }
    
 
    
    
}
