#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10
//define semaphore
sem_t s;

typedef struct {
	char type; // 0=fried chicken, 1=French fries
	int amount; // pieces or weight
	char unit; // 0=piece, 1=gram
} item;

//item pointer array
item* Items[3];

item buffer[BUFFER_SIZE];
int first = 0;
int last = 0;

void produce(item *i) {
	while ((first + 1) % BUFFER_SIZE == last) {
		// do nothing -- no free buffer item
	}
	sem_wait(&s);
	memcpy(&buffer[first], i, sizeof(item));
	first = (first + 1) % BUFFER_SIZE;
	sem_post(&s);
}

item *consume() {
	item *i = malloc(sizeof(item));
	while (first == last) {
		// do nothing -- no free buffer item
	}
	sem_wait(&s);
	memcpy(i, &buffer[last], sizeof(item));
	last = (last + 1) % BUFFER_SIZE;
	sem_post(&s);
	return i;
}
//make item
item* make(char type, int amount, char unit){
	item *i = malloc(sizeof(item));
	i->type = type;
	i->amount = amount;
	i->unit = unit;
	return i;
}
//print first last value
void printFirstLast(){
	printf("\nCurrent values:	First: %d	Last: %d\n",first,last);
}
//print item's value
void printItem(item i){
	printf("\nType: %c	Amount: %d	Unit: %c\n", i.type, i.amount, i.unit);
}
//produce items
void *produceItems(void* v_number){

	for(int i = 0; i<3; i++){
		produce(Items[i]);
		printf("\nProduce item %d\n",i);
		printFirstLast();
	}
}
//consume items
void *consumeItems(void* v_number){
	
	for(int i = 0; i<2; i++){
		consume();
		printf("\nConsume item the %d time\n",i+1);
		printFirstLast();
	}	
}
int main(){

	printf("Initial values:	First: %d	Last: %d\n",first,last);
	//make 3 items
	Items[0] = make('0',5,'0');
	Items[1] = make('1', 10, '1');
	Items[2] = make('1', 20, '0');

	printf("Begin producing thread\n");
	sem_init(&s,0,1);
	
	//produce 3 items in different thread
	pthread_t tid_producer;
	pthread_create (
		&tid_producer,
		NULL,
		produceItems,
		NULL
	);
	printf("Begin consuming thread\n");
	//consume 2 items in different thread
	pthread_t tid_consumer;
	pthread_create (
		&tid_consumer,
		NULL,
		consumeItems,
		NULL
	);

	printf("Return to main thread\n");

	pthread_join(tid_producer, NULL);
	pthread_join(tid_consumer, NULL);

	printf("Destroys semaphore!\n");
	sem_destroy(&s);


	return 0;

}
