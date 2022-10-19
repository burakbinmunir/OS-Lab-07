#include<iostream>
#include<cstring>
#include<unistd.h>
#include<sys/wait.h>

using namespace std;


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
        
        strcpy(file2, argv[2]);
        strcat(file2, ".txt");

        //file1[s1-1] = '\0';
        //file2[s2-1] = '\0';
        
        write(fd[1], &file1, strlen(file1));
        write(fd[1], &file2, strlen(file2));

        //cout<<file1<<file2<<endl;

        close(fd[1]);
        close(fd[0]);
    }

    if (retVal == 0) {
        
        int s1  = strlen(argv[1]) + strlen(".txt");
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

        close(fd[1]);
        close(fd[0]);

    }

    if (retVal < 0 ){
        cout<<"Error while forking";
        perror("fork");
    }
    
 
    
    
}