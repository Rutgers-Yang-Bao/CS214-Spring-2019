#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include"mymalloc.c"


void test_A(){
	int i = 0;
	for(i = 0; i < 150; i++){
		char * ptr = (char *)malloc(1);
		free(ptr);
	}
}	

void test_B(){
	int i = 0, j = 0,count = 0;
	char * array[150];
	for(i = 0; i < 150; i++){
		char * ptr = (char *)malloc(1);
		array[i] = ptr;
		if(count == 49 || count == 99 || count == 149){
			for(j = count; j > count - 50; j--){
				free(array[j]);
			}
		}
		count++;
	}
}


void test_C(){
	int bool = 0, j = 0, i = 0, count = 0;
	char * array[50];

	while(count < 50){
		bool = rand() % 2;
		if(bool == 1){
			array[i] = (char *)malloc(1);
			i++;
			count++;
		}
		else{	
			if(i > j){
				free(array[j]);
				j++;
			}
		}
	}
	while (j < 50){
		free(array[j]);
		j++;
	}
}
	

void test_D(){
	int bool = 0, j = 0, i = 0, count = 0, value = 0;
	char * array[50];

	while(count < 50){
		bool = rand() % 2;
		if(bool == 1){
			value = rand() % 64 + 1;
			array[i] = (char *)malloc(value);
			i++;
			count++;
		}
		else{	
			if(i > j){
				free(array[j]);
				j++;
			}
		}

	}
	while (j < 50){
		free(array[j]);
		j++;
	}

}

void test_E(){
	int bool = 0, j = 0, i = 0, count = 0, value = 0;
	char * array[100];
	int index[100] = {0};

	while(count < 100){
		bool = rand() % 2;
		if(bool == 1){
			value = rand() % 64 + 1;
			i = rand() % 100;
			while(index[i] == 1){
				i++;
				if(i > 99){
					i = i - 100;
				}
			}
			array[i] = (char *)malloc(value);
			index[i] = 1;
			count++;
		}
		else{	
			j = rand() % 100;
			if(index[j] == 1){
				free(array[j]);
				index[j] = 0;
			}
		}

	}
	for(i = 0; i < 100; i++){
		if(index[i] == 1){
			free(array[i]);
		}
	}
 
}

void test_F(){
	int i = 0, j = 0;
	char * array[150];
	for(i = 0; i < 150; i++){
		for(j = 0; j <= i; j++){
			char * ptr = (char *)malloc(1);
			array[j] = ptr;
		}
		for(j = 0; j <= i; j++){
			free(array[j]);
		}
	}
}

int cal_time(struct timeval start, struct timeval end){
	return 1000000*(end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
}

int main(){
	int i = 0;
	int ta[101] = {0},tb[101] = {0},tc[101] = {0},td[101] = {0},te[101] = {0},tf[101] = {0};
	struct timeval start, end;
	

	for(i = 0; i < 100; i++){
		gettimeofday(&start,NULL);
		test_A();
		gettimeofday(&end,NULL);
		ta[i] = cal_time(start, end);
		ta[101]+=ta[i];
	}

	for(i = 0; i < 100; i++){
		gettimeofday(&start,NULL);
		test_B();
		gettimeofday(&end,NULL);
		tb[i] = cal_time(start, end);	
		tb[101]+=tb[i];		
	}

	for(i = 0; i < 100; i++){
		gettimeofday(&start,NULL);
		test_C();
		gettimeofday(&end,NULL);
		tc[i] = cal_time(start, end);	
		tc[101]+=tc[i];
	}

	for(i = 0; i < 100; i++){
		gettimeofday(&start,NULL);
		test_D();
		gettimeofday(&end,NULL);
		td[i] = cal_time(start, end);
		td[101]+=td[i];	
	}

	for(i = 0; i < 100; i++){
		gettimeofday(&start,NULL);
		test_E();
		gettimeofday(&end,NULL);
		te[i] = cal_time(start, end);
		te[101]+=te[i];	
	}

	for(i = 0; i < 100; i++){
		gettimeofday(&start,NULL);
		test_F();
		gettimeofday(&end,NULL);
		tf[i] = cal_time(start, end);
		tf[101]+=tf[i];	
	}


	printf("The average time of workload A is : %d\n", ta[101]/100);
	printf("The average time of workload B is : %d\n", tb[101]/100);
	printf("The average time of workload C is : %d\n", tc[101]/100);
	printf("The average time of workload D is : %d\n", td[101]/100);
	printf("The average time of workload E is : %d\n", te[101]/100);
	printf("The average time of workload F is : %d\n", tf[101]/100);
}
