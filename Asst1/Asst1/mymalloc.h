#ifndef _MYMALLOC_H_
#define _MYMALLOC_H_

#define malloc(size) mymalloc(size, __FILE__, __LINE__);
#define free(a) myfree(a, __FILE__, __LINE__);
#define size_t unsigned int


//memory of size 4096 with all '\0'
static char myblock[4096]={'\0'};

//my malloc functions
static char* mymalloc(size_t size, char* file, int line);
static void myfree(void *pointer, char* file, int line);

//support functions
static char * traverse(size_t size);
static void split(char * target, size_t size);



#endif



