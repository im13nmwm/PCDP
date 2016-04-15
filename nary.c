#include<stdio.h>
#include<omp.h>
//#include<timer.h>
int a[65536],s,test;
int global_size,global_x,n=4;

void nary_search(int,int);
void seq_search(int);
main()
{
	int i,size=65536,x=0;

	for(i=0;i<size;i++)
	a[i]=i*2;
	printf("Enter number to be searched\n");
	scanf("%d",&s);
	/*intf("enter the number of threads used\n");
	/*scanf("%d",&n)*/

	nary_search(size,x);
	
}



void nary_search(int size,int x)
{
	printf("size = %d\n",size);
	if(size<=4)
	{

		test=0;	
		#pragma omp parallel
		{
			int tid=omp_get_thread_num();
			if(a[global_x+tid]==s)
			{

				printf("found at %d\n",global_x+tid);
				test=1;
			}
		}
		
		if(test==0)
		{

			printf("not found\n");
		}
	}
	else
	{
		test=0;
		#pragma omp parallel 
		{
			int tid=omp_get_thread_num();
			printf("checking (%d --  %d)with thread %d on cpu %d \n",a[tid*size/n+x],a[tid*size/n+size/n-1+x],tid,sched_getcpu());	
			if(s>=a[tid*size/n+x] && s<=a[tid*size/n+size/n-1+x])
			{
				printf("may be here  %d ---- %d  size=(   %d   )\n",a[tid*size/n+x],a[tid*size/n+size/n-1+x],+size/n);
				global_size=size/n;				
				global_x=tid*global_size+x;
				test=1;
			}
		}
		if(test==1)
			nary_search(global_size,global_x);
		else
			printf("not found in");
	}
}
/* output
yash@yash:~/Desktop$ ./a.out
Enter number to be searched
10
size = 65536
checking (32768 --  65534)with thread 1 on cpu 2 
checking (65536 --  98302)with thread 2 on cpu 3 
checking (98304 --  131070)with thread 3 on cpu 0 
checking (0 --  32766)with thread 0 on cpu 1 
may be here  0 ---- 32766  size=(   16384   )
size = 16384
checking (16384 --  24574)with thread 2 on cpu 3 
checking (24576 --  32766)with thread 3 on cpu 0 
checking (8192 --  16382)with thread 1 on cpu 2 
checking (0 --  8190)with thread 0 on cpu 1 
may be here  0 ---- 8190  size=(   4096   )
size = 4096
checking (4096 --  6142)with thread 2 on cpu 3 
checking (0 --  2046)with thread 0 on cpu 1 
may be here  0 ---- 2046  size=(   1024   )
checking (2048 --  4094)with thread 1 on cpu 2 
checking (6144 --  8190)with thread 3 on cpu 0 
size = 1024
checking (0 --  510)with thread 0 on cpu 0 
may be here  0 ---- 510  size=(   256   )
checking (1536 --  2046)with thread 3 on cpu 2 
checking (512 --  1022)with thread 1 on cpu 2 
checking (1024 --  1534)with thread 2 on cpu 3 
size = 256
checking (384 --  510)with thread 3 on cpu 2 
checking (0 --  126)with thread 0 on cpu 0 
may be here  0 ---- 126  size=(   64   )
checking (256 --  382)with thread 2 on cpu 1 
checking (128 --  254)with thread 1 on cpu 3 
size = 64
checking (96 --  126)with thread 3 on cpu 2 
checking (0 --  30)with thread 0 on cpu 0 
may be here  0 ---- 30  size=(   16   )
checking (32 --  62)with thread 1 on cpu 1 
checking (64 --  94)with thread 2 on cpu 3 
size = 16
checking (0 --  6)with thread 0 on cpu 0 
checking (24 --  30)with thread 3 on cpu 2 
checking (16 --  22)with thread 2 on cpu 3 
checking (8 --  14)with thread 1 on cpu 1 
may be here  8 ---- 14  size=(   4   )
size = 4
found at 5
yash@yash:~/Desktop$ */
