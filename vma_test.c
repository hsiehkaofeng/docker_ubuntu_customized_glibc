#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <gnu/libc-version.h>


#define B 1024
#define MB 1024 * 1024
#define GB 1024 * 1024 * 1024


void *myThreadtest(void *vargp){
    sleep(1);
    printf("In the Thread\n");
    return NULL;

}


int main()
{
    /*
    //stack overflow
    int stack[1000000][1000000];
    for (int i = 0; i < 1000000; i++)
    {
        //stack[i] = i;
        for (int j = 0; j < 1000000; j++)
        {
            stack[i][j] = j;
        }
    }*/
    int stack[(MB / 4) * 7];
    double a = sizeof(stack);
    printf("GNU libc version: %s\n", gnu_get_libc_version());
    printf("%lf MB\n", a / 1048576);
    printf("parent pid : %ld\n", (long)getppid());
    printf("pid : %ld\n", (long)getpid());
    
    pthread_t thread_id;
    printf("before thread\n");
    pthread_create(&thread_id,NULL,myThreadtest,NULL);
    pthread_join(thread_id,NULL);
    printf("after thread\n");
    //int testInteger;
    //printf("Enter an integer: ");
    //scanf("%d", &testInteger);

    getchar();
    return (0);
}
