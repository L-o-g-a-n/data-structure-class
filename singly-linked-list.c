/*
 * single linked list
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>

/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key; //key 값
	struct Node* link; //노드를 가리키는 노드 포인터
} listNode;

typedef struct Head {
	struct Node* first; //가장 첫번 째 노드를 가리킬 포인터
}headNode;




/* 함수 리스트 */
headNode* initialize(headNode* h); //linked list를 초기화하는 함수
int freeList(headNode* h); //h와 연결된 node를 해제하고 head도 해제하는 함수

int insertFirst(headNode* h, int key); //list 처음에 key를 가지는 노드 하나를 추가
int insertNode(headNode* h, int key); //입력받은 key보다 큰 값을 가지는 노드 바로 앞에 노드 하나 추가
int insertLast(headNode* h, int key); //list 가장 마지막에 노드를 하나 추가

int deleteFirst(headNode* h); //첫번 째 노드를 제거
int deleteNode(headNode* h, int key); //list에서 key값을 가지는 노드를 하나 제거
int deleteLast(headNode* h); //가장 마지막 노드를 제거
int invertList(headNode* h); //노드의 순서를 역순으로 전환

void printList(headNode* h); //list관련 정보들을 출력

int main()
{
	char command; //명령어를 담을 변수
	int key; //키 값을 입력받을 변수
	headNode* headnode=NULL; //가장 첫번 째 노드를 가리킬 포인터를 선언

	printf("----------------software 2017038063 박성진---------------\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //명령어를 사용자로부터 입력받는다

		switch(command) {
		case 'z': case 'Z':
			headnode = initialize(headnode); //리스트를 초기화
			break;
		case 'p': case 'P': //리스트의 정보를 출력
			printList(headnode);
			break;
		case 'i': case 'I': //노드를 삽입하는데 오름차순에 맞게 삽입
			printf("Your Key = ");
			scanf("%d", &key); //키를 입력받는다
			insertNode(headnode, key);
			break;
		case 'd': case 'D': //입력받은 키값을 가지는 노드를 삭제한다
			printf("Your Key = ");
			scanf("%d", &key); //키값을 입력받는다
			deleteNode(headnode, key);
			break;
		case 'n': case 'N': //마지막 노드에 키값을 입력받아 삽입한다
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E': //마지막 노드를 지운다
			deleteLast(headnode);
			break;
		case 'f': case 'F': //가장 첫 노드에 노드를 삽입한다
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T': //가장 첫 노드를 삭제한다
			deleteFirst(headnode);
			break;
		case 'r': case 'R': //리스트를 역순으로 뒤집는다
			invertList(headnode);
			break;
		case 'q': case 'Q': //지금까지 동적할당된 메모리를 반납하고 프로그램을 종료한다
			freeList(headnode);
			break;
		default: //잘못 입력됐을 때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(h != NULL)
		freeList(h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	headNode* temp = (headNode*)malloc(sizeof(headNode));
	temp->first = NULL; //headnode를 초기화하기 위해서 널 포인터를 담아준다.
	return temp;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; //헤드노드가 가리키는 곳을 p가 가리키도록 해준다.

	listNode* prev = NULL; //이전 노드를 기억하기 위한 포인터를 선언한다.
	while(p != NULL) {
		prev = p; //이전 노드를  저장한다
		p = p->link; //P가 다음노드를 가리킬 수 있도록 한다.
		free(prev); //이전 노드들은 해제한다.
	}
	free(h); //최종적으로 headnode도 해제한다.
	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로운 노드를 동적할당한다.
	node->key = key; //새로만든 노드의 키값을 입력해준다

	node->link = h->first; //새로만든 노드의 포인터를 가장 첫번째 노드 앞에 붙여준다.
	h->first = node; //헤드 노드가 새로 만든 노드를 가리키도록 한다.

	return 0;
}


/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* lead = h->first; //가장 첫번째 노드를 가리키는 리드 노드를 생성
	listNode* previous = NULL; //이전 노드의 위치를 기억할 포인터 변수
	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로 삽입할 노드를 동적할당
	node->link = NULL; //새로 삽입할 노드의 꼬리를 널로 초기화
	int count = 0; //아래 반복문에서 반복되는 횟수를 세기 위한 카운트 변수
	node -> key = key; //넘겨받은 키값을 새로 생성한 노드에 삽입

	if (h->first == NULL) //리스트에 아무 노드도 없을 때
	{
		h->first = node; //새로 생성한 노드를 가장 첫 노드로 삽입
		node->link = NULL; //새로 생성한 노드의 꼬리를 널로 초기화
	}
	else //리스트에 적어도 1개의 노드가 있을 때
	{
		if (lead->link == NULL) //노드가 딱 1개있을 때
		{
			if (lead->key >= key) //새로 만든 노드의 키값이 더 작을 경우
			{
				node->link = lead; //이미 있는 노드 앞에 새로 만든 노드를 삽입
				h->first = node;
			}
			else //새로 만든 노드의 키값이 더 큰 경우
			{
				lead->link=node; //이미 있는 노드 뒤에 새로 만든 노드를 삽입
			}
			return 0; //끝나면 함수 탈출
		}
		while(lead != NULL) //노드가 2개이상 있을 때
		{
			count ++; //와일 반복문에 들어온 횟수를 1개씩 카운트
			if(lead->key >= key) //리드가 가리키는 키값이 새로 만든 노드의 키값보다 클경우
			{
				node->link = lead; //새로만든 노드를 리드 앞에 삽입
				if (count == 1) //새로만든 노드가 맨 앞에 있을 때
				{
					h->first = node; //맨 앞을 가리키는 헤드포인터를 새로만든 노드로 초기화
					return 0; //함수 탈출
				}
				else //새로만든 노드가 맨 앞에 있지 않을 때 (노드와 노드 사이에 있을 때)
				{
					previous->link = node; //이전 노드의 다음노드로 새로만든 노드를 삽입
					return 0; //함수 탈출
				}
			}

			previous = lead; //이전을 가리키는 노드를 현재 리드가 가리키는 곳으로 지정
			lead = lead->link; //리드가 다음 노드를 가리키도록 지정

		}

		if(lead == NULL) //새로 만든 노드가 가장 뒤쪽에 삽입되어야할 때
		{
			previous->link = node; //이전의 노드 뒤로 삽입한다.
			node->link = NULL;
		}
	}

	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
//가장 뒤쪽에 노드를 삽입한다
	listNode* lead = h->first;
	listNode* node = (listNode*)malloc(sizeof(listNode)); //삽입할 노드를 동적할당한다
	node->link = NULL;
	node->key = key; //입력받은 키값을 넣어준다

	if(h->first == NULL) //노드가 아무 것도 없을 때
	{
		h->first = node;
	}
	else //노드가 적어도 한개 이상 있을 때
	{
		while(lead->link != NULL) //리드가 끝 노드에 도달할 때까지
		{
			lead = lead->link; //리드를 움직여준다
		}
		lead->link = node; //가장 끝 노드에 새로 삽입할 노드를 이어준다
	}

	return 0;
}


/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	if(h->first == NULL) //리스트에 노드가 하나도 없을 때
	{
		printf("삭제할 노드가 없습니다.\n");
		return 0;
	}
	else //리스트에 노드가 적어도 하나 이상 있을 때
	{
	listNode* lead = h->first;
	h->first = lead->link; //헤드를 가리키는 노드 포인터를 다음 노드로 이동시켜준다
	free(lead); //가장 첫 노드 였던 노드를 반납해준다
	}
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	listNode* lead = h->first; //first가 가리키는 곳을 lead가 가리키게 한다
	listNode* previous = NULL; //이전 노드를 가리킬 previous 변수를 널포인터로 생성



	if(h->first == NULL) //아무 노드도 없을 때
	{
		printf("삭제할 노드가 없습니다.\n");
		return 0; //함수 탈출
	}
	else //노드가 적어도 한개 이상 있을 때
	{
		while(lead->link != NULL) //리스트의 모든 노드를 검사
		{
			if (lead->key == key) //리드가 가리키는 키값과 입력받은 키값이 같으면
			{
				break; //반복문 탈출
			}
			previous = lead; //키값이 같지 않으면 프리비어스를 현 위치로 설정
			lead = lead->link; //현 리드를 다음 위치로 변경
		}

		if(lead->key != key) //반복문에서 결국 키 값을 찾지 못하고 빠져나오는 케이스를 분류
		{
			printf("일치하는 키 값이 없습니다.\n");
			return 0; //함수 탈출
		}

		if(previous == NULL) //키 값을 찾은 경우 총 세가지 케이스로 분류
		{//가장 앞에 노드가 키 값과 일치하는 경우
			h->first = lead->link;
			free(lead);
		}
		else if(lead->link == NULL) //가장 끝에 노드가 키 값과 일치하는 경우
		{
			previous->link = lead->link;
			free(lead);
		}
		else //노드가 양 끝에 있지 않고 가운데 있는 경우
		{
			previous->link = lead->link;
			free(lead);
		}

	}

	return 0; //정상 수행시 함수 탈출

}

/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {

	listNode* lead = h->first; //리스트에서 이동하며 쓸 포인터
	listNode* previous = NULL; //이전 노드를 가리키는 포인터

	if (h->first == NULL) //리스트에 노드가 하나도 없을 때
	{
		printf("삭제할 노드가 없습니다.\n");
		return 0;
	}
	else //리스트에 노드가 적어도 한 개 이상 있을 때
	{
		if ((lead->link == NULL) && (previous == NULL)) //노드가 단 1개밖에 없을 때
		{
			h->first = NULL; //헤드 포인터를 널로 초기화
			free(lead); //기존에 있던 노드는 반납
			return 0;
		}

		while(lead->link != NULL) //노드가 2개이상일 때
		{
		previous = lead; //이전 노드를 lead 위치로
		lead = lead->link; //lead를 다음 노드의 위치로
		}
		previous->link = NULL; //이전노드가 가장 꼬리가 되므로 널을 가리키도록 한다
		free(lead); //원래 맨 마지막에 있던 노드는 반납


	}

	return 0;
}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	listNode* lead = h->first;
	listNode* tail;
	listNode* middle = NULL;

	if(h->first == NULL) //리스트에 노드가 하나도 없을 때
	{
		printf("리스트에 노드가 없습니다.\n");
		return 0;
	}

	while (lead) //리드가 NULL이 될 때까지 반복
	{
		tail = middle; //tail노드를 middle로
		middle = lead; //middle노드를 lead로
		lead = lead->link; //lead를 다음 노드의 위치로
		middle->link = tail; //middle의 포인터를 역방향으로 바꿔준다
	}
	h->first = middle; //역순이 되어 이제는 middle이 헤드 노드가 된다

	return 0;
}


void printList(headNode* h) { //리스트에 대한 정보를 출력
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { //리스트가 비어있을 경우
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) { //리스트를 순차적으로 탐색하면서 정보를 출력
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);
}
