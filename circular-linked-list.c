/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node { //노드 타입의 구조체 선언
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h); //초기화 함수
int freeList(listNode* h); //동적할당 해제 함수
int insertLast(listNode* h, int key); //입력받은 키 값을 가장 마지막 노드로 삽입하는 함수
int deleteLast(listNode* h); //가장 마지막 노드를 지우는 함수
int insertFirst(listNode* h, int key); //가장 첫 번째 노드로 삽입하는 함수
int deleteFirst(listNode* h); //가장 첫 번째 노드를 지우는 함수
int invertList(listNode* h); //노드의 순서를 역순으로 만드는 함수

int insertNode(listNode* h, int key); //노드를 오름차순에 맞게 삽입하는 함수
int deleteNode(listNode* h, int key); //입력받은 키값을 가진 노드를 지우는 함수

void printList(listNode* h); //노드의 정보를 출력하는 함수



int main()
{
	char command;
	int key;
	listNode* headnode=NULL; //초기 헤드노드를 널로 설정한다
	printf("---------------software 2017038063 박성진----------------\n");

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //사용자로부터 명령을 입력받기

		switch(command) { //입력받은 명령어에 맞게 함수 실행
		case 'z': case 'Z':
			initialize(&headnode); //이중포인터라서 주소값을 넘김
			break;
		case 'p': case 'P':
			printList(headnode); //노드의 정보를 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key); //노드를 오름차순으로 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key); //키값이 일치하는 노드를 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key); //마지막에 노드 삽입
			break;
		case 'e': case 'E':
			deleteLast(headnode); //마지막 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key); //가장 첫 번째에 노드 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode); //가장 첫 번째 노드를 삭제
			break;
		case 'r': case 'R':
			invertList(headnode); //노드를 역순으로
			break;
		case 'q': case 'Q':
			freeList(headnode); //모든 동적할당 해제
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) { //초기화 시키는 함수

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){

	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->rlink; //헤드노드가 가리키는 곳을 p가 가리키도록 해준다.

	if(h->rlink == h) //리스트에 노드가 한개도 없을 때
	{
		free(h); //헤드 노드만 동적할당받은 메모리를 반납
		return 0;
	}
	while(p != h) {
		p = p->rlink; //P가 다음노드를 가리킬 수 있도록 한다.
		free(p->llink); //이전 노드들은 해제한다.
	}
	free(h); //최종적으로 headnode도 해제한다.
	h = NULL; //headnode를 NULL로 초기화한다.

	return 0;
}



void printList(listNode* h) { //노드에 대한 자세한 정보를 출력
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) { //노드가 초기화되지 않았을 때
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink; //p가 첫 번째 노드를 가리키게 한다

	while(p != NULL && p != h) { //p가 h가 될 때까지 , 즉 노드 마지막까지 돈다.
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink; //다음 노드로 이동
		i++; //카운팅
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);
	//주소값에 대한 정보들을 출력
	i = 0;
	p = h->rlink; //가장 첫 번째 노드를 가리키게 함
	while(p != NULL && p != h) { //노드 마지막까지 반복
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink; //계속해서 다음노드로 이동
		i++; //카운팅
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로 삽입할 노드를 동적할당한다
	node->llink = h; //새로 생성한 노드에 헤드노드 포인터로 초기화하고 키 값을 넣는다.
	node->rlink = h;
	node->key = key;
	listNode* p = h->llink; //움직일 포인터를 가장 마지막 노드로 초기화
	if(p == h) // 해드 포인터가 가리키는 리스트가 없다면 , 즉 노드가 없다면
	{
		h->llink = node; //새로 삽입할 노드를 가장 첫 노드로 셋팅
		h->rlink = node;
	}
	else //노드가 하나이상 있을 경우
	{
		p->rlink = node; //마지막 노드에 도달 시, 새로 삽입할 노드와 연결해준다.
		node->llink = p;
		h->llink = node; //헤드 노드의 llink를 바꿔준다
	}

	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {

	listNode* p = h->llink; //헤드 포인터가 마지막 노드를 가리키도록 한다.

	if(p == h) //노드가 아무것도 없을 때
	{
		printf("삭제할 노드가 없습니다.\n"); //오류 메시지 출력
		return 0;
	}
	else //노드가 하나이상 있을 때
	{
		if((p->llink == h) && (p->rlink == h)) //노드가 한개만 있을 때
		{
			h->llink = h;
			h->rlink = h;
		}
		else //노드가 두개 이상 있을 때
		{
			(p->llink)->rlink = h;
			h->llink = p->llink;
		}
	}
	free(p); //동적할당 해제


	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로 삽입할 노드를 동적할당
	listNode* p = h->rlink; //움직일 포인터를 첫 번째 노드로 초기화

	node->key = key; //새로 만든 노드에 키값을 넣고 링크를 초기화한다.
	node->llink = h;
	node->rlink = h;

	if(p == h) //리스트가 비어있을 때
	{
		h->llink = node; //노드의 시작을 새로삽입한 노드로 변경
		h->rlink = node;
	}
	else //노드가 하나이상 있을 때
	{
		h->rlink = node;
		node->rlink = p;
		p->llink = node;
	}


	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {

	listNode* p = h->rlink; //움직이는 포인터를 첫 번째 노드로 초기화

	if(p == h) //리스트에 노드가 하나도 없을 때
	{
		printf("삭제할 노드가 없습니다.\n"); //오류 메세지 출력
		return 0;
	}
	else //리스트에 노드가 하나이상 있을 때
	{
		if((p->rlink == h) && (p->llink == h)) //노드가 한개만 있을 때
		{
			h->rlink = h; //헤드 포인터가 자기 자신을 가리키도록
			h->llink = h;
		}
		else //노드가 2개이상 있을 때
		{
			h->rlink = p->rlink;
			(p->rlink)->llink = h;
		}
		free(p); //동적할당된 메모리를 반납해준다
	}



	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {

	listNode* lead = h->rlink;
	listNode* tail = h;
	listNode* temp; //swap을 위한 변수

	if((h->rlink == h) && (h->llink == h)) //리스트에 노드가 하나도 없을 때
	{
		printf("리스트에 노드가 없습니다.\n");
		return 0;
	}

	while (lead != h) //리드가 마지막 노드가 될 때까지 반복
	{
		temp = lead->rlink; //rlink의 값과 llink의 값을 바꿔준다
		lead->rlink = lead->llink;
		lead->llink = temp;
		tail = lead; //tail을 다음 노드 포인팅
		lead = lead->llink; //lead를 다음 노드 포인팅
	}
	h->rlink = tail; //헤드 포인터가 invert된 리스트를 가리키도록 수정.
	while (tail != h) //리드가 Invert된 리스트의 마지막 노드가 될 때까지 반복
	{
		lead = tail;
		tail = tail->rlink;
	}
	h->llink = lead;
	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {

	listNode* lead = h->rlink; //가장 첫번째 노드를 가리키는 리드 노드를 생성
	listNode* previous = h; //이전 노드의 위치를 기억할 포인터 변수
	listNode* node = (listNode*)malloc(sizeof(listNode)); //새로 삽입할 노드를 동적할당
	node->rlink = h; //새로 삽입할 노드를 헤드 노드로 초기화
	node->llink = h;
	int count = 0; //아래 반복문에서 반복되는 횟수를 세기 위한 카운트 변수
	node -> key = key; //넘겨받은 키값을 새로 생성한 노드에 삽입

	if ((h->rlink == h) && (h->llink == h))
	{//리스트에 아무 노드도 없을 때
		h->rlink = node; //새로 생성한 노드를 가장 첫 노드로 삽입
		h->llink = node;
	}
	else //리스트에 적어도 1개의 노드가 있을 때
	{
		if ((lead->rlink == h) && (lead->llink == h)) //노드가 딱 1개있을 때
		{
			if (lead->key >= key) //새로 만든 노드의 키값이 더 작을 경우
			{
				node->rlink = lead; //이미 있는 노드 앞에 새로 만든 노드를 삽입
				lead->llink = node;
				h->rlink = node;
			}
			else //새로 만든 노드의 키값이 더 큰 경우
			{
				lead->rlink = node; //이미 있는 노드 뒤에 새로 만든 노드를 삽입
				node->llink = lead;
				h->llink = node;
			}
			return 0; //끝나면 함수 탈출
		}
		while(lead != h) //노드가 2개이상 있을 때
		{
			count ++; //와일 반복문에 들어온 횟수를 1개씩 카운트
			if(lead->key >= key) //리드가 가리키는 키값이 새로 만든 노드의 키값보다 클경우
			{
				node->rlink = lead; //새로만든 노드를 리드 앞에 삽입
				lead->llink = node;
				if (count == 1) //새로만든 노드가 맨 앞에 있을 때
				{
					h->rlink = node; //맨 앞을 가리키는 헤드포인터를 새로만든 노드로 초기화
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

		if(lead == h) //새로 만든 노드가 가장 뒤쪽에 삽입되어야할 때
		{
			previous->rlink = node; //이전의 노드 뒤로 삽입한다.
			node->llink = previous;
			h->llink = node;
		}
	}


	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {

	listNode* lead = h->rlink; //첫 번째 노드를 lead가 가리키게 한다
	listNode* previous = h; //이전 노드를 가리킬 previous 변수를 h로 생성



	if((h->rlink == h) && (h->llink == h)) //아무 노드도 없을 때
	{
		printf("삭제할 노드가 없습니다.\n");
		return 0; //함수 탈출
	}
	else //노드가 적어도 한개 이상 있을 때
	{
		while(lead->rlink != h) //리스트의 모든 노드를 검사
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

		if(previous == h) //키 값을 찾은 경우 총 세가지 케이스로 분류
		{//가장 앞에 노드가 키 값과 일치하는 경우
			h->rlink = lead->rlink;
			(lead->rlink)->llink = h;
			free(lead);
		}
		else if(lead->rlink == h) //가장 끝에 노드가 키 값과 일치하는 경우
		{
			previous->rlink = lead->rlink;
			h->llink = previous;
			free(lead);
		}
		else //노드가 양 끝에 있지 않고 가운데 있는 경우
		{
			previous->rlink = lead->rlink;
			(lead->rlink)->llink = previous;
			free(lead);
		}

	}


	return 0;
}

