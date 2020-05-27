/*
 * Binary Search Tree #2
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>



typedef struct node { //노드에 관한 구조체이다
	int key;
	struct node *left; //왼쪽 자식 노드를 가리킬 포인터
	struct node *right; //오른쪽 자식 노드를 가리킬 포인터
} Node;

/* for stack */
#define MAX_STACK_SIZE		20 //최대 스택 사이즈는 20이다
Node* stack[MAX_STACK_SIZE]; //스택을 생성
int top = -1; //탑은 -1

Node* pop(); //스택 팝을 구현
void push(Node* aNode); //스택 푸쉬를 구현

/* for queue */
#define MAX_QUEUE_SIZE		20 //최대 큐 사이즈는 20이다
Node* queue[MAX_QUEUE_SIZE]; //큐를 생성
int front = -1; //프론트와 리어는 -1이다
int rear = -1;

Node* deQueue(); //디큐를 구현
void enQueue(Node* aNode); //인큐를 구현


int initializeBST(Node** h); //동적할당 해제 및 초기화

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */

int isEmpty(); //큐가 비었는지 확인하는 함수이다
int isFull(); //큐가 가득 찼는지 확인하는 함수이다



int main()
{
	char command; //사용자로부터 명령 입력받기
	int key;
	Node* head = NULL; //노드를 가리키는 헤드 포인터를 널로 초기화

	printf("--------------software 2017038063 박성진----------------\n");

	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z': //동적할당 해제 및 초기화
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head); //동적할당 해제
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key); //노드를 추가한다
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key); //노드를 삭제한다 3가지 케이스에 맞게
			break;

		case 'r': case 'R':
			recursiveInorder(head->left); //재귀호출 방식으로 인오더 트래버설 구현
			break;
		case 't': case 'T':
			iterativeInorder(head->left); //비 재귀호출 방식으로 인오더 트래버설 구현
			break;

		case 'l': case 'L':
			levelOrder(head->left); //레벨 오더 구현
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q가 입력되면 종료

	return 1;
}

int initializeBST(Node** h) { //동적할당 해제 및 초기화

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) //트리가 비어있지 않으면 동적할당해제 먼저해준다
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //트리가 비어있게되면 헤드포인터를 생성해준다
	(*h)->left = NULL;	/* root */ //올바르게 초기화해준다
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1; //탑은 -1로 초기화

	front = rear = -1; //프론트와 리어는 -1로 초기화

	return 1;
}



void recursiveInorder(Node* ptr) //재귀 호출로 인오더 트래버설 구현
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node) //비 재귀호출로 인오더 트래버설 구현
{
	top = -1; //스택 초기화
	for(int i=0;i<MAX_STACK_SIZE-1;i++)
	{
		stack[i] = NULL;
	}

	for (;;) //무한루프
	{
		for(;node;node = node->left) //제일 왼쪽 노드까지 접근
			push(node); //하나씩 스택에 삽입하면서
		node = pop(); //스택에서 하나 팝

		if(!node) //공백 스택일경우에 반복 멈추기
			break;

		printf(" [%d] ", node->key); //팝한 노드 하나씩 출력하기
		node = node->right; //노드의 오른쪽으로 접근
	}
}

/**
 * textbook: p 225
 */
void levelOrder(Node* ptr) //레벨순서 순회
{
	front = -1;//큐를 초기값으로 설정해준다.
	rear = -1;
	for(int i=0;i < MAX_QUEUE_SIZE-1;i++)
	{
		queue[i] = NULL;
	}
	if(!ptr) //공백 트리일경우
		return; //함수 종료
	enQueue(ptr); //큐에 노드를 하나 삽입해준다
	for(;;) //무한루프
	{
		ptr = deQueue(); //디큐 한번
		if(ptr) //디큐한 노드가 존재하면
		{
			printf(" [%d] ", ptr->key); //디큐한 노드를 출력해준다
			if(ptr->left) //왼쪽 자식 노드가 존재하면
				enQueue(ptr->left); //왼쪽 자식 노드를 큐에 넣어준다
			if(ptr->right) //오른쪽 자식 노드가 존재하면
				enQueue(ptr->right); //오른쪽 자식 노드를 큐에 넣어준다
		}
		else break; //큐가 공백이면 반복 종료
	}
}


int insert(Node* head, int key) //올바른 위치에 노드를 삽입한다
{
	Node* newNode = (Node*)malloc(sizeof(Node)); //새로운 노드를 동적할당 받는다
	newNode->key = key; //사용자로부터 입력받은 키값을 넣어준다
	newNode->left = NULL; //왼쪽 오른쪽 자식노드는 널로 초기화한다
	newNode->right = NULL;

	if (head->left == NULL) { //만약 공백 트리라면 새로만든 노드를 이어준다
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left; //루트 노드를 ptr이 가리키도록 설정해준다

	Node* parentNode = NULL; //부모노드를 가리킬 노드포인터를 널로 생성한다
	while(ptr != NULL) { //널이 아닐때까지 반복한다

		/* if there is a node for the key, then just return */
		if(ptr->key == key) return 1; //키값이 같으면 함수를 종료한다 (삽입하지 않고 무시하는 것임)

		/* we have to move onto children nodes,
		 * keep tracking the parent using parentNode */
		parentNode = ptr; //부모노드의 위치를 설정해준다

		/* key comparison, if current node's key is greater than input key
		 * then the new node has to be inserted into the right subtree;
		 * otherwise the left subtree.
		 */
		if(ptr->key < key) //사용자로부터 입력받은 키값이 더 크면 오른쪽으로 탐색을 진행한다
			ptr = ptr->right;
		else //사용자로부터 입력받은 키값이 더 작으면 왼쪽으로 탐색을 진행한다
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if(parentNode->key > key) //부모노드의 키값이 더 크면 새로만든 노드는 왼쪽에 놓는다
		parentNode->left = newNode;
	else //부모노드의 키값이 더 작으면 새로만든 노드는 오른쪽에 놓는다
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key) //입력받은 노드를 삭제하는 함수
{
	Node* lead = head->left;
	Node* previous = NULL;
	Node* temp = NULL; //case3에서 임시로 저장할 포인터
	if(lead == NULL)
	{
		printf("the node [%d] is not in tree\n", key);
		return 0;
	}

	while(lead) //리드가 유효할 때
	{
		if(key == lead->key) //키값을 발견하면 와일문을 빠져나온다
		{
			break;
		}
		else if(key < (lead->key)) //노드의 키값보다 작으면
		{
			if(lead->left != NULL) //리드의 다음 위치가 널인지 확인하고 널이 아니면
			{
				previous = lead; //리드의 이전 위치를 기억
				lead = lead->left; //리드를 옮겨준다
			}
			else //리드의 다음 위치가 널이면
			{
				printf("the node [%d] is not in tree\n", key);
				return 0;
			}
		}
		else if(key > (lead->key)) //리드가 가리키는 노드의 키값보다 크면
		{
			if(lead->right != NULL) //리드의 다음 위치가 널인지 확인하고 널이 아니면
			{
				previous = lead; //리드의 이전 위치를 기억
				lead = lead->right; //리드를 옮겨준다
			}
			else //리드의 다음 위치가 널이면
			{
				printf("the node [%d] is not in tree\n", key);
				return 0;
			}
		}
	}
	if((lead->left == NULL) && (lead->right == NULL)) //단말노드인지 판별
	{
		if(previous == NULL) //노드가 하나만 있을 때 예외처리
		{
			free(lead);
			head->left = NULL;
			return 0;
		}

		if(lead->key > previous->key) //단말노드중에서 부모노드의 오른쪽에 위치하던 노드
		{
			free(lead);
			previous->right = NULL;
		}
		else //단말노드중에서 부모노드의 왼쪽에 위치하던 노드
		{
			free(lead);
			previous->left = NULL;
		}
	}
	else //단말노드가 아닐 때
	{
		if(((lead->left != NULL) && (lead->right == NULL)) || ((lead->left == NULL) && (lead->right != NULL)))
		{	//자식노드로 한개의 노드만 가지는 경우 (case 2)
			if(head->left == lead) //루트노드일 경우
			{
				if(lead->left != NULL) //왼쪽 자식 노드를 한개 가지는 경우
				{
					head->left = lead->left;
					free(lead);
				}
				else //오른쪽 자식 노드를 한개 가지는 경우
				{
					head->left = lead->right;
					free(lead);
				}
			}
			else
			{
				if(lead->key > previous->key) //리드의 키값이 이전 키값보다 클경우
				{
					if(lead->left != NULL) //왼쪽 자식 노드를 한개 가지는 경우
					{
						previous->right = lead->left;
						free(lead);
					}
					else //오른쪽 자식 노드를 한개 가지는 경우
					{
						previous->right = lead->right;
						free(lead);
					}
				}
				else // 리드의 키값이 이전 키값보다 작을경우
				{
					if(lead->left != NULL) //왼쪽 자식 노드를 한개 가지는 경우
					{
						previous->left = lead->left;
						free(lead);
					}
					else //오른쪽 자식 노드를 한개 가지는 경우
					{
						previous->left = lead->right;
						free(lead);
					}
				}
			}
		}
		else //자식노드로 두개의 노드를 가지는 경우 (case 3)
		{
			temp = lead;
			previous = lead;
			lead = lead->left; //왼쪽 노드중에서 가장 큰 노드를 올리는 방식으로 구현
			if(!(lead->right)) //왼쪽 노드가 가장 큰 노드일 때
			{
				if(lead->left == NULL) //왼쪽에 자식노드가 있지 않는 경우
				{
					previous->key = lead->key;
					previous->left = NULL;
					free(lead);
				}
				else //왼쪽에 자식노드가 있는 경우
				{
					previous->key = lead->key;
					previous->left = lead->left;
					free(lead);
				}
				return 0;
			}
			while(lead->right) //오른쪽 노드가 더 있을 경우, 오른쪽노드가 널이될 때까지 탐색
			{
				previous = lead; //이전 노드를 기록
				lead = lead->right; //계속 오른쪽 노드로 이동
			}
			temp->key = lead->key;

			if(lead->left != NULL) //오른쪽 끝 노드가 왼쪽 자식 노드를 가지는 경우
			{
				previous->right = lead->left;
				free(lead);
			}
			else //왼쪽 자식 노드를 가지지 않는 경우
			{
				previous->right = NULL;
				free(lead);
			}
		}
	}
	return 0;
}


void freeNode(Node* ptr) //헤드 포인터를 넘겨받는다
{
	if(ptr) {
		freeNode(ptr->left); //포인터의 왼쪽 자식노드를 재귀호출한다
		freeNode(ptr->right); //포인터의 오른쪽 자식노드를 재귀호출한다
		free(ptr); //동적할당 해제한다
	}
}

int freeBST(Node* head)
{
	if(head->left == head) //트리가 비어있을 때
	{
		free(head); //헤드포인터를 해제한다
		return 1; //그리고 함수 종료
	}

	Node* p = head->left; //헤드 포인터가 가리키는 노드를 가리키게 만든다

	freeNode(p); //재귀호출을 이용해서 순차적으로 다 동적할당 해제한다

	free(head); //최종적으로 헤드 포인터까지 해제한다
	return 1;
}



Node* pop() //stack pop구현
{
	if(top == -1) //빈 스택일 경우 함수 종료
		return NULL;
	else //스택이 차있을 경우
		return stack[top--];
}

void push(Node* aNode) //stack push구현
{
	if(top == MAX_STACK_SIZE-1) //스택이 가득차있을 경우 함수 종료
		return;
	else //스택에 공간이 남아있을 경우
		stack[++top] = aNode;
}



Node* deQueue() //큐에서 원소 하나를 제거한다
{
	if(isEmpty()==1) //큐가 비어있을 때
		return NULL; //널 포인터를 리턴

	front = (front + 1) % MAX_QUEUE_SIZE; //서큘러 큐로 인덱스 하나 증가
	return queue[front]; //제거할 노드를 리턴
}

void enQueue(Node* aNode) //큐에 원소 하나를 넣는다
{
	rear = (rear + 1) % MAX_QUEUE_SIZE; //서큘러 큐로 리어의 인덱스 하나 증가
	if(isFull() == 1) //가득 차있으면 함수 종료
		return;
	queue[rear] = aNode; //가득 차있지 않으면 리어에 노드 넣어주기
}

int isEmpty() //큐가 비었는지 확인하는 함수이다
{
	if(front == rear) //front와 rear가 같으면 원소가 비어있는 것이다
	{
		return 1; //원소가 비어있을 때는 1을 리턴한다
	}
	return 0;
}

int isFull() //큐가 가득 찼는지 확인하는 함수이다
{
	if(front == rear) //isFull함수를 호출하기 전에 rear+1이 되었고 그 후 front와 rear가 같으므로 full상태이다
	{
		if(rear == 0) //서큘러 큐이므로 케이스를 나눠준다
		{
			rear = MAX_QUEUE_SIZE-1;
		}
		else
		{
			rear = rear-1;
		}
		return 1; //큐가 가득찼을 때 1을 리턴해준다
	}
	return 0;
}



