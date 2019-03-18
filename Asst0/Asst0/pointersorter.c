#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

typedef struct Node node;

node *insertNode(node *front,char *data);

struct Node{
	char *data;
	struct Node *next;
};

int compare(char a, char b){			//a is new, b is ptr
	int check = 0;
	if(isupper(a) && islower(b)){
		check = 0;			//new should be before ptr
	}else if(islower(a) && isupper(b)){
		check = 1;			//new should be behind ptr
	}else{					//a and b are same case
		if(a > b){
			check = 0;
		}else if(a < b){
			check = 1;
		}else{
			check = -1;		//a and b are same
		}
	}
	return check;
}
node *insertNode(node *front, char *data){
	node *new, *ptr, *prev;
	new = (node *)malloc(sizeof(node));
	ptr = (node *)malloc(sizeof(node));
	prev = (node *)malloc(sizeof(node));

	if(new == NULL || ptr == NULL || prev == NULL){
		printf("ERROR : unable to malloc the memory");
		exit(1);
	}
	
	new->data = data;
	new->next = NULL;

	if(front->data == 0 && front->next == NULL){
		front = new;
	}else{
		int check = -1, i = 0;
		ptr = front;
		prev->next = front;
		while(ptr != NULL){
			i = 0;
			check = -1;
			while(check == -1){
				if(i >= strlen(new->data) && i < strlen(ptr->data)){		//ptr is longer than new
					check = 1;						//so new should be behind ptr
				}else if(i < strlen(new->data) && i >= strlen(ptr->data)){	//new is longer  than ptr
					check = 0;						//so new should be before ptr
				}else if(i == strlen(new->data) && i == strlen(ptr->data)){	//ptr and new are the same
					check = 0;						//doesn't matter 
				}else{
					check = compare(new->data[i],ptr->data[i]);
				}
				i++;
			}
			if(check == 1){
				ptr = ptr->next;
				prev = prev->next;
			}else if(check == 0){
				if(prev->next == front){
					new->next = ptr;
					front = new;
				}
				else{
					prev->next = new;
					new->next = ptr;
				}
				return front;
			}
		}
		prev->next = new;
	}
	new = ptr;
	prev = ptr;
	free(ptr);
	ptr = NULL;
	new = NULL;
	prev = NULL;
	return front;
}



void traverse(node *front){
	node *ptr;
	ptr = (node *)malloc(sizeof(node));

	if(ptr == NULL){
		printf("ERROR : unable to malloc the memory");
		exit(1);
	}

	ptr = front;
	
	while(ptr!= NULL){
		printf("%s\n", ptr->data);
		ptr = ptr->next;
	}
	free(ptr);
	ptr = NULL;
}

int main(int argc, char ** argv){
	if(argc == 1){
		printf("No valid input token\nprogram will output nothing\n");
		return 0;
	}

	node *front;
	front = (node *)malloc(sizeof(node));

	int i = 0, j = 0;
	char *ptr1, *ptr2;
	for(i = 1; i < argc; i++){
		//devide the input into strings by space
		ptr1 = (char*)malloc(strlen(argv[i]) * sizeof(char));

		if(ptr1 == NULL){
			printf("ERROR : unable to malloc the memory");
			exit(1);
		}

		strcpy(ptr1,argv[i]);
			
		int begin = 0, len = 0;
		for(j = 0; j <= strlen(ptr1) ; j++){			
			//check inside of every string
			if(!isalpha(ptr1[j]) || j == strlen(ptr1)){
				len = j-begin;
				if(len != 0){
					ptr2 = (char*)malloc(len * sizeof(char));

					if(ptr2 == NULL){
						printf("ERROR : unable to malloc the memory");
						exit(1);
					}
					
					strncpy(ptr2, ptr1+begin, len);
					front = insertNode(front, ptr2);
				}
				begin = j+1;
			}
		}
	}

	if(front->data == 0 && front->next == NULL){
		printf("No valid input token\nprogram will output nothing\n");
		return 0;
	}	
	traverse(front);	
	free(ptr1);
	ptr1 = NULL;
	free(ptr2);
	ptr2 = NULL;
	free(front);
	front = NULL;
	return 0;
}

