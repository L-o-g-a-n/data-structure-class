/*
 * Binary Search Tree #1
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node { //struct node를 Node로 정의
	int key; //키 값
	struct node *left; //왼쪽 자식 가리키는 포인터
	struct node *right; //오른쪽 자식 가리키는 포인터
} Node;

int initializeBST(Node** h); //이진 탐색 트리를 초기화하는 함수
void freef(Node* ptr); //free를 위한 재귀호출 함수
/* functions that you have to implement */
void inorderTraversal(Node* ptr);	  /* recursive inorder traversal */
void preorderTraversal(Node* ptr);    /* recursive preorder traversal */
void postorderTraversal(Node* ptr);	  /* recursive postorder traversal */
int insert(Node* head, int key);  /* insert a node to the tree */
int deleteLeafNode(Node* head, int key);  /* delete the leaf node for the key */
Node* searchRecursive(Node* ptr, int key);  /* search the node for the key */
Node* searchIterative(Node* head, int key);  /* search the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */


int main()
{
	char command; //사용자로부터 입력받는 명렁키
	int key; //키값
	Node* head = NULL; //헤드노드의 선언
	Node* ptr = NULL;	/* temp */
	printf("------------------software 2017038063 박성진------------------\n");
	do{
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #1                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = n      Delete Node                  = d \n");
		printf(" Inorder Traversal    = i      Search Node Recursively      = s \n");
		printf(" Preorder Traversal   = p      Search Node Iteratively      = f\n");
		printf(" Postorder Traversal  = t      Quit                         = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //사용자로부터 명령키 입력받기

		switch(command) { //사용자 명령에 따라 함수 호출
		case 'z': case 'Z':
			initializeBST(&head); //이중포인터라서 헤드노드의 주소값을 넘겨 받는다.
			break;
		case 'q': case 'Q':
			freeBST(head); //동적할당을 해제하는 함수
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key); //입력받은 키값의 노드를 삽입하는 함수
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteLeafNode(head, key); //단말노드를 삭제하는 함수
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchIterative(head, key); //입력 받은 키를 가진 노드를 재귀호출을 사용하지 않고 탐색하는 함수
			if(ptr != NULL) //탐색 결과가 있을 때
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else //탐색 결과가 없을 때
				printf("\n Cannot find the node [%d]\n", key);
			break;
		case 's': case 'S':
			printf("Your Key = ");
			scanf("%d", &key);
			ptr = searchRecursive(head->left, key); //입력 받은 키를 가진 노드를 재귀호출을 통해 탐색하는 함수
			if(ptr != NULL) //탐색 결과가 있을 때
				printf("\n node [%d] found at %p\n", ptr->key, ptr);
			else //탐색 결과가 없을 때
				printf("\n Cannot find the node [%d]\n", key);
			break;

		case 'i': case 'I':
			inorderTraversal(head->left); //중위순회를 하는 함수
			break;
		case 'p': case 'P':
			preorderTraversal(head->left); //전위순회를 하는 함수
			break;
		case 't': case 'T':
			postorderTraversal(head->left); //후위순회를 하는 함수
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q가 입력될 때 종료

	return 1;
}

int initializeBST(Node** h) { //동적할당을 모두 해제하고 헤드 노드를 세팅해주는 함수

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if(*h != NULL) //트리가 비어있지 않을 때 모든 동적할당을 해제한다.
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node)); //헤드노드에 동적할당해주기
	(*h)->left = NULL;	/* root */
	(*h)->right = *h; //헤드노드 초기값을 올바르게 세팅
	(*h)->key = -9999;
	return 1;
}



void inorderTraversal(Node* ptr) //중위순회하는 함수
{
	if(ptr)
	{//재귀호출을 활용한 중위순회 함수
		inorderTraversal(ptr->left);
		printf(" [%d] ", ptr->key);
		inorderTraversal(ptr->right);
	}
}

void preorderTraversal(Node* ptr) //전위순회하는 함수
{
	if(ptr)
	{//재귀호출을 활용한 전위순회 함수
		printf(" [%d] ", ptr->key);
		preorderTraversal(ptr->left);
		preorderTraversal(ptr->right);
	}
}

void postorderTraversal(Node* ptr) //후위순회하는 함수
{
	if(ptr)
	{//재귀호출을 활용한 후위순회 함수
		postorderTraversal(ptr->left);
		postorderTraversal(ptr->right);
		printf(" [%d] ", ptr->key);
	}
}


int insert(Node* head, int key)
{
	Node* node = (Node*)malloc(sizeof(Node));
	Node* lead = head->left; //트리에서 움직일 포인터 lead를 root노드로 설정해준다.
	node->key = key; //새로만들 노드에 키 값을 넣어준다
	node->left = NULL; //초기 세팅
	node->right = NULL;

	if(head->left == NULL) //트리가 비어있을 때
	{
		head->left = node; //새로만든 노드를 이어준다
		return 0;
	}

	while(lead) //리드가 유효할 때
	{
		if(key == lead->key) //리드가 가리키는 노드의 키값과 같으면
			return 0; //무시한다
		else if(key < (lead->key)) //노드의 키값보다 작으면
		{
			if(lead->left != NULL) //리드의 다음 위치가 널인지 확인하고 널이 아니면
			{
				lead = lead->left; //리드를 옮겨준다
			}
			else //리드의 다음 위치가 널이면
			{
				lead->left = node; //그 곳에 새로만든 노드를 삽입한다
				return 0; //그리고 함수 종료
			}
		}
		else if(key > (lead->key)) //리드가 가리키는 노드의 키값보다 크면
		{
			if(lead->right != NULL) //리드의 다음 위치가 널인지 확인하고 널이 아니면
			{
				lead = lead->right; //리드를 옮겨준다
			}
			else //리드의 다음 위치가 널이면
			{
				lead->right = node; //그 곳에 새로만든 노드를 삽입한다
				return 0; //그리고 함수 종료
			}
		}
	}
	return 0;
}

int deleteLeafNode(Node* head, int key)
{
	Node* lead = head->left; //트리에서 움직일 포인터 lead를 root노드로 설정해준다.
	Node* previous = NULL; //lead의 전 움직임을 기억하는 포인터
	if(head->left == NULL) //트리가 비어있을 때
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
		printf("the node [%d] is not a leaf\n", key);
	}
	return 0;
}

Node* searchRecursive(Node* ptr, int key)
{
	if(!ptr) //트리가 비어있을 때
		return NULL;
	if(key == ptr->key) //키값이 일치할 때
		return ptr; //주소 리턴
	if(key < ptr->key) //노드의 키값이 더 클 때
		return searchRecursive(ptr->left, key); //왼쪽으로 가야하므로
	return searchRecursive(ptr->right, key); //노드의 키값이 더 작을 때 오른쪽으로 가야하므로
}

Node* searchIterative(Node* head, int key)
{
	Node* ptr = head->left; //head 그 자체가 넘어오기 때문에 head의 left값으로 초기화
	while(ptr) //널이 아닐때까지
	{
		if(key == ptr->key) //키 값이 같을 때
			return ptr;
		if(key < ptr->key) //키 값이 작을때
			ptr = ptr->left; //왼쪽으로 가야하므로
		else //키 값이 더 클 때
			ptr = ptr->right; //오른쪽으로 가야하므로
	}
	return NULL; //탐색하지 못했을 때 널 리턴
}


int freeBST(Node* head)
{
	Node* lead = head->left; //트리에서 움직일 포인터 lead를 root노드로 설정해준다.
	freef(lead); //재귀호출을 활용하여 모든 노드에 접근하여 동적할당을 해제해준다.
	free(head); //최종적으로 헤드노드도 동적할당을 해제해준다.
	return 0;
}

void freef(Node* ptr) //freeBST의 free를 도와주는 함수
{
	if(ptr) //ptr이 널이 아닐 때
	{
		freef(ptr->left); //왼쪽 관련 동적할당 해제
		freef(ptr->right); //오른쪽 관련 동적할당 해제
		free(ptr); //포인터 본인 동적할당 해제
	}


}



