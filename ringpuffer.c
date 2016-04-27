#include <stdlib.h>
#include <stdio.h>



typedef struct ringbuffer
{
	int * buffer;
	int write;
	int read;
	int length;

}ringbuffer;

#define LENGTH 5

static void initialize(ringbuffer* puffer, int size);
static int destroy(ringbuffer* puffer);
static int write(ringbuffer* puffer, int value);
static int read(ringbuffer* puffer);

int main(void)
{
	ringbuffer* puffer2 = malloc(sizeof(ringbuffer)); //errorhandle
	
	initialize(puffer2,sizeof(int));

	write(puffer2, 10);

	write(puffer2, 20);
	write(puffer2, 30);
	write(puffer2, 40);
	printf("\n%d\n", read(puffer2));
	printf("\n%d\n", read(puffer2));
	write(puffer2, 50);
	printf("read: %d -- write:%d\n", puffer2->read, puffer2->write);
	write(puffer2, 60);
	write(puffer2, 70);


	/*
	printf("%d", read(puffer2));
	printf("%d", read(puffer2));
	printf("%d", read(puffer2));
	printf("%d", read(puffer2));
	printf("%d", read(puffer2));
	*/
	int i = 0;

	for(i =0;i<LENGTH;i++)
		printf("\n%d\n", puffer2->buffer[i]);


	destroy(puffer2);
}

void initialize(ringbuffer* puffer,int size)
{
	puffer->length = LENGTH;
	puffer->read = 0;
	puffer->write = 0;
	puffer->buffer = malloc(LENGTH * size);

}

static int write(ringbuffer* puffer, int value)
{
	if ((puffer->write+1)%LENGTH == puffer->read)
		return -1;

	
	puffer->buffer[puffer->write] = value;
	
	puffer->write = (puffer->write + 1) % LENGTH;

	return 0;
}



static int read(ringbuffer* puffer)
{	
	int temp;

	if (puffer->read == puffer->write)
	{
		return -1;
	}

	temp = puffer->buffer[puffer->read];

	puffer->read = (puffer->read + 1) % LENGTH;

	return temp;


}

static int destroy(ringbuffer* puffer)
{
	free(puffer);
	// errorhandle und semaphor
	return 0;
}