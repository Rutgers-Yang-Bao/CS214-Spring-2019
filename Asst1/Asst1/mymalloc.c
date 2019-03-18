#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include "mymalloc.h"



void myfree(void *pointer, char* file, int line){
	/* initialize previous, next, and current address in order to sort through 
	array and find the address mathches the the pointer we want to free*/
	char *previous_address = NULL, *next_address = NULL;
	char  *current_address = myblock; // current address as the address of the first element in the array

	char * ptr;
 	ptr = pointer-5;	

	int c_address_int =*(int*)(1+current_address);


	
	if(*ptr=='a'){
		fprintf(stderr, "Redundant free()ing of the same pointer in FILE:'%s', LINE:'%d'\n",file,line);
		return;
	}


	
	if((*(ptr)!='a')&&(*(ptr)!='o')){
		fprintf(stderr, "Free()ing pointers that were not allocated by malloc() OR not a pointer in FILE:'%s', LINE:'%d'\n",file,line);
		return;
	}
	
	

	if(ptr <current_address || ptr > current_address + 4095 ){
		fprintf(stderr, "Free()ing pointers that were not allocated by malloc() OR not a pointer in FILE:'%s', LINE:'%d'\n",file,line);
		return;
	}

	while(1){
		c_address_int= *(int*)(1+current_address);

		if(!*current_address){
			//printf("3\n");
			break;
		}
		if(current_address == ptr){
			next_address =current_address + *(int*)(1+current_address);
			//printf("1\n");
			break;
		}
		else{
			previous_address = current_address;
			current_address = current_address+c_address_int;
			next_address =current_address + *(int*)(1+current_address);
		}
	}
//	printf("---------------------------------------\n");
/*	printf("the previous flag is %c, space is %d\n", *previous_address, *(int*)(1+previous_address));
	printf("the current flag is %c, space is %d\n", *current_address, *(int*)(1+current_address));
	printf("the next flag is %c, space is %d\n", *next_address, *(int*)(1+next_address));
*/
	// combine the space together if the next address is also available
	if(next_address != NULL){
		if(*next_address == 'a' ){
			//printf("1begin\n");
			*current_address = 'a';
			*(int*)(current_address +1) = *(int*)(current_address +1)+ *(int*)(next_address +1);
			*next_address = '\0';
			//printf("1nice\n");
		}
	}
	if(previous_address != NULL){
		if(*previous_address == 'a'){
			//printf("2begin\n");
			*(int*)(previous_address +1) = *(int*)(current_address +1)+ *(int*)(previous_address +1);
			*current_address='\0';
			//printf("2nice\n");
		}
		else{
			//printf("3begin\n");
			*ptr = 'a';
			//printf("3nice\n");
		}
	}
		//printf("Check\n");
		*(ptr) = 'a';

//	printf("After free the current flag is %c, space is %d\n", *current_address, *(int*)(1+current_address));

		return;


}


char * traverse(size_t size){
	char * ptr;
	ptr = myblock;
	int space = 0;
	while(1){
		space = *(int*)(ptr + 1);
//		printf("the distance from end to ptr is %d\n",myblock+4095-ptr);
//		printf("in this ptr, flag is %c, space is %d\n", *ptr, *(int *)(ptr+1));

		if(ptr == NULL){
			return NULL;
		}
		else if(*ptr == 'a' && space >= size + 5){
			return ptr;
		}
		else{
			if(ptr + size + space >= myblock + 4095 || space == 0){
				return "overload";
			}
		ptr+=space;
		}
	}
	return NULL;
}
		
void split(char * target, size_t size){
	char * temp;
	int space = *(int *)(target + 1);
	temp = target + size + 5;

	if(space > size + 10){
		*temp = 'a';
		*(int *)(temp + 1) = space - size - 5;
		*target = 'o';
		*(int *)(target + 1) = size + 5;
	}
	else{
		*target = 'o';
	}
	
/*
	rest = rest - 5 - size;
	temp = target + size + 5;
	if(*temp != 'o'){
		*temp = 'a';
		*(int *)(temp + 1) = rest;
	}
	*target = 'o';
	*(int *)(target + 1) = size + 5;
*/
}


char* mymalloc(size_t size, char* file, int line){
	if(size <= 0){
		fprintf(stderr, "ERROR : input size is negative or 0 in FILE:'%s', LINE:'%d'\n",file,line);
		return NULL;
	}
	char * start = myblock;
	if (*start == '\0'){
		*start = 'a';
		*(int *)(start + 1) = 4096 - 5;
	}
	
	char * target = traverse(size);
//	printf("target found, flag is %c, space is %d\n", *target, *(int *)(target+1));
	if(target == "overload"){
		fprintf(stderr,"ERROR : not enough memory in FILE:'%s', LINE:'%d'\n",file,line);
		return NULL;
	}
	if(target != NULL){
		if(*(int *)(target + 1) >= size){
			split(target,size);
//			printf("After split, flag is %c, space is %d\n", *target, *(int *)(target+1));
		}
	}else{
		return NULL;
	}
	return (target+5);
}

/*
int main()
{
	int *c, *a,*b, *d;

	a = (int*)malloc(sizeof(int)*10);
	b = (int*)malloc(sizeof(int)*20);
	c = (int*)malloc(sizeof(int)*30);
	d = (int*)malloc(sizeof(int)*40);
	
	free(d);
	free(c);
	free(b);
	free(a);


	return 0;
}
*/
