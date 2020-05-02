/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         singly-linked-list의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	char command; //사용자로부터 명령을 입력 받음
	int key; //사용자로부터 키 값을 입력 받음
	headNode* headnode=NULL; //초기 헤드노드가 없음

	do{
		printf("-------------software 2017038063 박성진--------------\n");
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //사용자로부터 명령을 입력 받음.

		switch(command) { //명령어에 걸맞는 동작을 수행
		case 'z': case 'Z':
			initialize(&headnode); //이중포인터라서 주소값을 넘김
			break;
		case 'p': case 'P': //리스트의 정보를 출력
			printList(headnode);
			break;
		case 'i': case 'I': //오름차순순으로 입력받은 노드를 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D': //입력받은 키 값을 검색하여 노드를 삭제
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N': //가장 마지막 노드 뒤에 노드를 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E': //가장 마지막 노드를 삭제
			deleteLast(headnode);
			break;
		case 'f': case 'F': //가장 첫번째 노드 앞에 노드를 삽입
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T': //가장 첫번째 노드를 삭제
			deleteFirst(headnode);
			break;
		case 'r': case 'R': //리스트를 뒤집는다
			invertList(headnode);
			break;
		case 'q': case 'Q': //실행종료
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q가 입력되면 종료

	return 1;
}


int initialize(headNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);
	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (headNode*)malloc(sizeof(headNode)); //동적할당
	(**h).first = NULL; //headnode를 초기화하기 위해서 널 포인터를 담아준다.
	return 1;
}

int freeList(headNode* h){

	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first; //헤드노드가 가리키는 곳을 p가 가리키도록 해준다.

	if(!p) //리스트에 노드가 한개도 없을 때
	{
		free(h); //헤드 노드만 동적할당받은 메모리를 반납
		return 0;
	}
	while(p->rlink != NULL) {
		p = p->rlink; //P가 다음노드를 가리킬 수 있도록 한다.
		free(p->llink); //이전 노드들은 해제한다.
	}
	free(p);
	free(h); //최종적으로 headnode도 해제한다.

	return 0;
}


void printList(headNode* h) { //링크드 리스트에 관련된 정보를 출력한다.
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { //가리킬 링크드 리스트가 없을 때
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로 삽입할 노드를 동적할당한다
	node->llink = NULL; //새로 생성한 노드에 널 포인터로 초기화하고 키 값을 넣는다.
	node->rlink = NULL;
	node->key = key;
	listNode* p = h->first; //움직일 포인터를 초기화
	if(p == NULL) // 해드 포인터가 가리키는 리스트가 없다면 , 즉 노드가 없다면
	{
		h->first = node; //새로 삽입할 노드를 가장 첫 노드로 셋팅
	}
	else //노드가 하나이상 있을 경우
	{
		while(p->rlink != NULL) //마지막 노드에 도달할 때까지
		{
			p = p->rlink; //포인터를 이동시켜준다
		}
		p->rlink = node; //마지막 노드에 도달 시, 새로 삽입할 노드와 연결해준다.
		node->llink = p;
	}

	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) { //가장 마지막 노드를 삭제

	listNode* p = h->first; //헤드 포인터가 가리키는 노드를 p가 가리키게 한다
	int count = 0; //와일문 반복 횟수를 계산하기 위한 카운터 변수.

	if(h->first == NULL) //노드가 아무것도 없을 때
	{
		printf("삭제할 노드가 없습니다.\n"); //오류 메시지 출력
		return 0;
	}
	else //노드가 하나이상 있을 때
	{
		while(p->rlink != NULL) //가장 마지막 노드에 도달할때까지
		{
			count++;
			p = p->rlink;
		}

		if(count != 0) //노드가 2개이상 있을 때
		{
			(p->llink)->rlink=NULL;
		}
		else //노드가 1개일 때
		{
			h->first = NULL;
		}
	}
	free(p); //동적할당 해제

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로 삽입할 노드를 동적할당
	listNode* p = h->first; //움직일 포인터를 헤드 포인터와 동일하게 초기화

	node->key = key; //새로 만든 노드에 키값을 넣고 링크를 초기화한다.
	node->llink = NULL;
	node->rlink = NULL;

	if(p == NULL) //리스트가 비어있을 때
	{
		h->first = node; //노드의 시작을 새로삽입한 노드로 변경
	}
	else //노드가 하나이상 있을 때
	{
		h->first = node; //양방향으로 노드를 링크해준다.
		node->rlink = p;
		p->llink = node;
	}

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {

	listNode* p = h->first; //움직이는 포인터를 헤드 포인터로 초기화

	if(h->first == NULL) //리스트에 노드가 하나도 없을 때
	{
		printf("삭제할 노드가 없습니다.\n"); //오류 메세지 출력
		return 0;
	}
	else //리스트에 노드가 하나이상 있을 때
	{
		if(p->rlink == NULL) //노드가 한개만 있을 때
		{
			h->first = NULL; //헤드 포인터가 널을 가리키도록
		}
		else //노드가 2개이상 있을 때
		{
			h->first = p->rlink;
			(p->rlink)->llink = NULL;
		}
		free(p); //동적할당된 메모리를 반납해준다
	}

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	listNode* lead = h->first;
	listNode* tail = NULL;
	listNode* temp; //swap을 위한 변수

	if(h->first == NULL) //리스트에 노드가 하나도 없을 때
	{
		printf("리스트에 노드가 없습니다.\n");
		return 0;
	}

	while (lead) //리드가 NULL이 될 때까지 반복
	{
		temp = lead->rlink; //rlink의 값과 llink의 값을 바꿔준다
		lead->rlink = lead->llink;
		lead->llink = temp;
		tail = lead; //tail을 다음 노드 포인팅
		lead = lead->llink; //lead를 다음 노드 포인팅
	}
	h->first = tail; //헤드 포인터가 invert된 리스트의 가장 첫번째 노드를 가리키도록 바꿔준다

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* lead = h->first; //가장 첫번째 노드를 가리키는 리드 노드를 생성
	listNode* previous = NULL; //이전 노드의 위치를 기억할 포인터 변수
	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로 삽입할 노드를 동적할당
	node->rlink = NULL; //새로 삽입할 노드를 널로 초기화
	node->llink = NULL;
	int count = 0; //아래 반복문에서 반복되는 횟수를 세기 위한 카운트 변수
	node -> key = key; //넘겨받은 키값을 새로 생성한 노드에 삽입

	if (h->first == NULL) //리스트에 아무 노드도 없을 때
		h->first = node; //새로 생성한 노드를 가장 첫 노드로 삽입

	else //리스트에 적어도 1개의 노드가 있을 때
	{
		if (lead->rlink == NULL) //노드가 딱 1개있을 때
		{
			if (lead->key >= key) //새로 만든 노드의 키값이 더 작을 경우
			{
				node->rlink = lead; //이미 있는 노드 앞에 새로 만든 노드를 삽입
				lead->llink = node;
				h->first = node;
			}
			else //새로 만든 노드의 키값이 더 큰 경우
			{
				lead->rlink = node; //이미 있는 노드 뒤에 새로 만든 노드를 삽입
				node->llink = lead;
			}
			return 0; //끝나면 함수 탈출
		}
		while(lead != NULL) //노드가 2개이상 있을 때
		{
			count ++; //와일 반복문에 들어온 횟수를 1개씩 카운트
			if(lead->key >= key) //리드가 가리키는 키값이 새로 만든 노드의 키값보다 클경우
			{
				node->rlink = lead; //새로만든 노드를 리드 앞에 삽입
				lead->llink = node;
				if (count == 1) //새로만든 노드가 맨 앞에 있을 때
				{
					h->first = node; //맨 앞을 가리키는 헤드포인터를 새로만든 노드로 초기화
					return 0; //함수 탈출
				}
				else //새로만든 노드가 맨 앞에 있지 않을 때 (노드와 노드 사이에 있을 때)
				{
					previous->rlink = node; //이전 노드의 다음노드로 새로만든 노드를 삽입
					node->llink = previous;
					return 0; //함수 탈출
				}
			}

			previous = lead; //이전을 가리키는 노드를 현재 리드가 가리키는 곳으로 지정
			lead = lead->rlink; //리드가 다음 노드를 가리키도록 지정

		}

		if(lead == NULL) //새로 만든 노드가 가장 뒤쪽에 삽입되어야할 때
		{
			previous->rlink = node; //이전의 노드 뒤로 삽입한다.
			node->llink = previous;
		}
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
		while(lead->rlink != NULL) //리스트의 모든 노드를 검사
		{
			if (lead->key == key) //리드가 가리키는 키값과 입력받은 키값이 같으면
			{
				break; //반복문 탈출
			}
			previous = lead; //키값이 같지 않으면 프리비어스를 현 위치로 설정
			lead = lead->rlink; //현 리드를 다음 위치로 변경
		}

		if(lead->key != key) //반복문에서 결국 키 값을 찾지 못하고 빠져나오는 케이스를 분류
		{
			printf("일치하는 키 값이 없습니다.\n");
			return 0; //함수 탈출
		}

		if(previous == NULL) //키 값을 찾은 경우 총 세가지 케이스로 분류
		{//가장 앞에 노드가 키 값과 일치하는 경우
			h->first = lead->rlink;
			free(lead);
		}
		else if(lead->rlink == NULL) //가장 끝에 노드가 키 값과 일치하는 경우
		{
			previous->rlink = lead->rlink;
			free(lead);
		}
		else //노드가 양 끝에 있지 않고 가운데 있는 경우
		{
			previous->rlink = lead->rlink;
			(lead->rlink)->llink = previous;
			free(lead);
		}

	}

	return 1;
}

