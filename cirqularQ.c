/*
 * circularQ.c
 *
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 //배열의 구성원소를 4로 정했다. 하지만 원형 큐를 만들기 위해 실제 넣을 수 있는 원소는 3개로 생각한다.

typedef char element; //캐릭터형을 element로 정의한다.
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType; //구조체를 통해 큐를 구현할 배열과 front,rear를 묶었다.


QueueType *createQueue(); //동적할당을 통해 큐를 생성한다.
int isEmpty(QueueType *cQ); //큐가 비었는지 확인해준다.
int isFull(QueueType *cQ); //큐가 가득 차있는지 확인해준다.
void enQueue(QueueType *cQ, element item); //큐에 원소를 하나 넣는다. 물론 rear에 넣는다.
void deQueue(QueueType *cQ, element* item); //큐에서 원소 하나를 제거한다. front에서부터 제거한다.
void printQ(QueueType *cQ); //현재 큐에 들어있는 원소를 출력한다.
void debugQ(QueueType *cQ); //큐가 어떻게 구성되어있는지 자세히 출력한다.

element getElement(); //원소를 입력받는다.


int main(void)
{
	QueueType *cQ = createQueue(); //큐를 동적할당으로 생성하여 cQ에 연결시켜준다.
	element data; //추후에 입력받는 원소를 넣을 변수이다.

	char command; //명령을 받을 변수이다.
	printf("---------------software 2017038063 박성진----------------\n");
	do{
		printf("\n-----------------------------------------------------\n");
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Dubug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'i': case 'I': //원소를 넣을 때
			data = getElement();
			enQueue(cQ, data);
			break;
		case 'd': case 'D': //원소를 제거할 때
			deQueue(cQ,&data);
			break;
		case 'p': case 'P': //들어있는 원소를 출력할 때
			printQ(cQ);
			break;
		case 'b': case 'B': //큐가 어떻게 이루어져있는지 상세히 출력할 때
			debugQ(cQ);
			break;
		case 'q': case 'Q': //프로그램을 중단할 때
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q를 입력했을 때 중단.


	return 1;
}


QueueType *createQueue() //큐를 동적할당을 이용해서 만드는 함수이다.
{
	QueueType *cQ;
	cQ = (QueueType *)malloc(sizeof(QueueType));
	cQ->front = 0; //초기 front = 0
	cQ->rear = 0; //초기 rear = 0
	return cQ;
}

element getElement() //원소를 입력받는 함수이다.
{
	element item;
	printf("Input element = ");
	scanf(" %c", &item);
	return item;
}


/* complete the function */
int isEmpty(QueueType *cQ) //큐가 비었는지 확인하는 함수이다.
{
	if (cQ->front == cQ->rear) //front와 rear가 같으면 원소가 비어있는 것이다.
	{
		printf("Circular Queue is empty!\n");
		return 1; //원소가 비어있을 때는 1을 리턴한다.
	}
    return 0;
}

/* complete the function */
int isFull(QueueType *cQ) //큐가 가득 찼는지 확인하는 함수이다.
{
	if(cQ->front == cQ-> rear) //isfull함수를 호출하기전에 rear가 +1이 되었고 그 후 front와 rear가 같으므로 full상태이다.
	{
		if(cQ->rear == 0) //isfull함수를 호출하기전에 rear에 +1이 되었으므로 원상태로 돌려준다.
		{//rear가 1이 증가되서 0이 되었다는 경우는 rear의 값이 이전에 MAX_QUEUE_SIZE-1이었다는 말이다.
			cQ->rear = MAX_QUEUE_SIZE -1;
		}
		else //rear가 0이 아닌 경우에는 -1만 도로 다시해주면 된다.
		{
			cQ->rear = cQ->rear -1;
		}
		printf("Circular Queue is full!\n"); //오류 메세지 출력
		return 1; //queue가 가득 찼을 때는 리턴 1을 한다.
	}
	return 0; //queue가 가득차지 않았다는 뜻이다.
}


/* complete the function */
void enQueue(QueueType *cQ, element item) //큐에 원소를 넣는 함수이다.
{
	cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; //rear값을 하나 증가시킨다. 원형 큐 방식을 따른다.
	if (isFull(cQ)==1)
		return; //queue가 가득찼을 때 이 함수를 빠져나간다.

	cQ->queue[cQ->rear] = item; //queue에 빈 공간이 있으므로 원소를 집어넣는다.

}

/* complete the function */
void deQueue(QueueType *cQ, element *item) //큐에서 원소를 하나 제거하는 함수이다.
{
    if (isEmpty(cQ) == 1) //queue가 비어있을 때 이 함수를 빠져나간다.
    	return;

    cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; //front 값을 하나 증가시킨다. 원형 큐 방식을 따른다.
    cQ->queue[cQ->front] = '\0'; //queue에 원소가 적어도 1개 이상 있으므로 front에 가장 가까이 있는 원소를 없앤다.

}


void printQ(QueueType *cQ) //큐에 들어있는 원소를 출력하는 함수이다.
{
	int i, first, last;

	first = (cQ->front + 1)%MAX_QUEUE_SIZE; //First의 값을 하나 증가시킨다.
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE; //Last의 값을 하나 증가시킨다.

	printf("Circular Queue : [");

	i = first;
	while(i != last){ //first와 last가 같아질때까지 돌면서 원소를 출력한다.
		printf("%3c", cQ->queue[i]);
		i = (i+1)%MAX_QUEUE_SIZE; //i를 원형큐 방식으로 하나씩 증가시킨다.

	}
	printf(" ]\n");
}


void debugQ(QueueType *cQ) //큐의 구성 상태를 상세히 출력하는 함수이다.
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)
	{
		if(i == cQ->front) { //front일 때는 front라고 명시해준다.
			printf("  [%d] = front\n", i);
			continue; //다시 반복문의 조건으로 돌아간다.
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]); //순서대로 출력해준다.

	}
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //front와 rear의 값을 출력한다.
}

