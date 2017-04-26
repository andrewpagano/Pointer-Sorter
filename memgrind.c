#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/time.h>
#include "mallocPlus.h"

/**
 *CS 214 Systems Programming
 *Assignment 1: Memory Allocation++
 *due 2/26/2017
 *
 *@author Thurgood Kilper
 *@author Andrew Pagano
 */

/**
 *A: 1000 separate malloc()s of 1 byte, then free() the 1000 1 byte pointers one by one
 */
double testA()
{
    printf("begin WorkLoad A\n");
    struct timeval start, stop;
    double elapsed = 0;

    gettimeofday(&start, NULL);

    char *bytes[1000];
    int alloc = 0;
    int freed = 0;
    int i=0; 
    for(i=0; i<1000; i++){
        bytes[i] = mallocPlus(1);
        alloc++;
        if(bytes[i]==NULL)
            alloc--;
    }
    for(i=0; i<1000; i++){
        freed += freePlus(bytes[i]);
    }
    printf("number of allocated bytes: %d \n", alloc);
    printf("number of freed bytes: %d \n", freed);

    gettimeofday(&stop, NULL);
    elapsed = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);

    printf("WorkLoad A done. Time elapsed: %f\n", elapsed);
    return elapsed;
}

/**
 *B: first malloc() 1 byte and immediately free it - do this 1000 times
 */
double testB()
{
    printf("begin WorkLoad B\n");
    struct timeval start, stop;
    double elapsed = 0;

    gettimeofday(&start, NULL);

    char *bytes[1000];
    int alloc = 0;
    int freed = 0;
    int i=0;
    for(i=0; i<1000; i++){
        bytes[i] = mallocPlus(1);
        alloc++;
        if(bytes[i]==NULL)
            alloc--;
        freed += freePlus(bytes[i]);
    }

    printf("number of allocated bytes: %d \n", alloc);
    printf("number of freed bytes: %d \n", freed);

    gettimeofday(&stop, NULL);
    elapsed = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("WorkLoad B done. Time elapsed: %f\n", elapsed);
    return elapsed;
}

/**
 *C: Randomly choose between a 1 byte malloc() or free()ing a 1 byte pointer - do this 1000 times
 *- Keep track of each operation so that you eventually malloc() 1000 bytes, in total
 *- Keep track of each operation so that you eventually free() all pointers
 */
double testC()
{
    printf("begin WorkLoad C\n");
    struct timeval start, stop;
    double elapsed = 0;

    gettimeofday(&start, NULL);

    char *bytes[1000][2];
    int alloc = 0;
    int freed = 0;
    int coinflip;
    int i=0;
	int freemem = 4988;
	int pointers[1000] = {0};
    while(alloc<1000){
        coinflip=rand()%2;
        if(coinflip==0 && freemem>13){
            *bytes[i] = mallocPlus(1);
            freemem-=13;
            pointers[i]=1;
            alloc++;
            i++;
        }else{
            if(i == 0){
                continue;
            }
            i--;
            pointers[i]=0;
            freemem+=13;
            freed+=freePlus(*bytes[i]);
        }
    }

	for(i=0; i<1000; i++){
        if(pointers[i]!=0)
            freed+=freePlus(*bytes[i]);
	}

    printf("number of allocated blocks: %d \n", alloc);
    printf("number of freed blocks: %d \n", freed);

    gettimeofday(&stop, NULL);
    elapsed = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("WorkLoad C done. Time elapsed: %f\n", elapsed);
    return elapsed;
}

/**
 *D: Randomly choose between a randomly-sized malloc() or free()ing a pointer – do this many
 *times (see below)
 *- Keep track of each malloc so that all mallocs do not exceed your total memory capacity
 *- Keep track of each operation so that you eventually malloc() 1000 times
 *- Keep track of each operation so that you eventually free() all pointers
 *- Choose a random allocation size between 1 and 64 bytes
 */
double testD(){
    printf("begin WorkLoad D\n");
    struct timeval start, stop;
    double elapsed = 0;

    gettimeofday(&start, NULL);

    char *bytes[1000][64];
    int sizes[1000] = {0};
   	int alloc = 0;
    int freed = 0;
    int coinflip;
    int number = 0;
	int i = 0;
	int freemem = 4988;
	while(alloc<1000){
        coinflip=rand()%2;
        number =(rand()%64);
        number+=1;
        if(coinflip==0 && freemem >(number+12)){
            freemem-=number; freemem-=12;
            sizes[i]=number;
            *bytes[i] = mallocPlus(number);
            alloc++;
            i++;
		}else{
			if(i > 0){
				i--;
                freemem+=sizes[i]; freemem+=12;
                sizes[i]=0;
                freed+=freePlus(*bytes[i]);
			}

		}
	}

    for(i=0; i<1000; i++){
        if(sizes[i]!=0)
            freed+=freePlus(*bytes[i]);
    }

    printf("number of allocated blocks: %d \n", alloc);
    printf("number of freed blocks: %d \n", freed);

    gettimeofday(&stop, NULL);
    elapsed = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("WorkLoad D done. Time elapsed: %f\n", elapsed);
    return elapsed;
}

/**
 *E,F: Two more workloads of your choosing
 *- Describe both workloads in your testplan.txt
 */
double testE()
{
    printf("begin WorkLoad E\n");
    struct timeval start, stop;
    double elapsed = 0;

    gettimeofday(&start, NULL);

    char *bytes[5000][50];
    int alloc = 0;
    int freed = 0;
    int i = 0;
    int ad = 1;
    int freemem = 4988;
    int sizes[1000] = {0};
    while(i<50){
        if(freemem>=(ad+12)){
            *bytes[i] = mallocPlus(ad);
            sizes[i] = ad;
            ad++;
            alloc++;
        }
        i++;
    }
    while(i>=0){
        if(sizes[i]!=0)
            freed += freePlus(*bytes[i]);
        i--;
    }

    printf("number of allocated blocks: %d \n", alloc);
    printf("number of freed blocks: %d \n", freed);

    gettimeofday(&stop, NULL);
    elapsed = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("WorkLoad E done. Time elapsed: %f\n", elapsed);
    return elapsed;
}

double testF()
{
    printf("begin WorkLoad F\n");
    struct timeval start, stop;
    double elapsed = 0;

    gettimeofday(&start, NULL);

     char *bytes[200][1000];
    int sizes[200] = {0};
       int alloc = 0;
    int freed = 0;
    int coinflip;
    int number = 0;
    int i = 0;
    int freemem = 4988;
    while(alloc<200){
        coinflip=rand()%2;
        number =(rand()%900) +101;
        if(coinflip==0 && freemem >(number+12)){
            freemem-=number; freemem-=12;
            sizes[i]=number;
            *bytes[i] = mallocPlus(number);
            alloc++;
            i++;
        }else{
            if(i == 0){
                continue;
            }
            i--;
            freemem+=sizes[i]; freemem+=12;
            sizes[i]=0;
            freed+=freePlus(*bytes[i]);
        }
    }
    for(i=0; i<200; i++){
        if(sizes[i]!=0)
            freed+=freePlus(*bytes[i]);
    }

    printf("number of allocated blocks: %d \n", alloc);
    printf("number of freed blocks: %d \n", freed);

    gettimeofday(&stop, NULL);
    elapsed = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("WorkLoad F done. Time elapsed: %f\n", elapsed);
    return elapsed;
}

/**
 *run the memory tests
 */
int main()
{
  /*  int i=0;
    double totaltime, avgtime;
    testF();
    printf("Now starting memgrind tests.\n");
        printf("Press ENTER to start\n");
        getchar();

    totaltime = 0; avgtime = 0;
    for(i=0; i<100; i++)
        totaltime += testA();
    avgtime = totaltime/100;
    printf("test A total time elapsed: %f\n", totaltime);
    printf("test A average time elapsed: %f\n", avgtime);

        printf("Press ENTER to continue...\n");
        getchar();

    totaltime = 0; avgtime = 0;
    for(i=0; i<100; i++)
        totaltime += testB();
    avgtime = totaltime/100;
    printf("test B total time elapsed: %f\n", totaltime);
    printf("test B average time elapsed: %f\n", avgtime);

        printf("Press ENTER to continue...\n");
        getchar();

    totaltime = 0; avgtime = 0;
    for(i=0; i<100; i++)
        totaltime += testC();
    avgtime = totaltime/100;
    printf("test C total time elapsed: %f\n", totaltime);
    printf("test C average time elapsed: %f\n", avgtime);

        printf("Press ENTER to continue...\n");
        getchar();

    totaltime = 0; avgtime = 0;
    for(i=0; i<100; i++)
        totaltime += testD();
    avgtime = totaltime/100;
    printf("test D total time elapsed: %f\n", totaltime);
    printf("test D average time elapsed: %f\n", avgtime);

        printf("Press ENTER to continue...\n");
        getchar();

    totaltime = 0; avgtime = 0;
    for(i=0; i<100; i++)
        totaltime += testE();
    avgtime = totaltime/100;
    printf("test E total time elapsed: %f\n", totaltime);
    printf("test E average time elapsed: %f\n", avgtime);

        printf("Press ENTER to continue...\n");
        getchar();

    totaltime = 0; avgtime = 0;
    for(i=0; i<100; i++)
        totaltime += testF();
    avgtime = totaltime/100;
    printf("test F total time elapsed: %f\n", totaltime);
    printf("test F average time elapsed: %f\n", avgtime);

    printf("total time elapsed: %f\n", totaltime);
*/

//~~~~~
double totaltime = 0, avgA = 0, avgB = 0, avgC = 0, avgD = 0, avgE = 0, avgF=0;
	int i = 0;
	for(i=0;i<100;i++){
    printf("Now starting memgrind tests.\n");
        printf("Press ENTER to start\n");
    //    getchar();
    avgA+= testA(); 
        printf("Press ENTER to continue...\n");
    //    getchar();
    avgB += testB();
        printf("Press ENTER to continue...\n");
    //    getchar();
    avgC += testC();
        printf("Press ENTER to continue...\n");
    //    getchar();
    avgD += testD();
        printf("Press ENTER to continue...\n");
    //    getchar();
    avgE += testE();
        printf("Press ENTER to continue...\n");
    //    getchar();
    avgF += testF();
	
    printf("total time elapsed: %f\n", totaltime);
	totaltime=0;
	}
	printf("average time:\n %f\n%f\n%f\n%f\n%f\n%f\n",
		avgA/100,avgB/100,avgC/100,avgD/100,avgE/100,avgF/100);
    return 0;
}

