#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_VERTEX 20 //최대 Vertex의 개수를 20개로 정의합니다.

typedef struct Vertex //Vertex를 담을 구조체입니다.
{
	int num; //Vertex number
	struct Vertex* link; //인접리스트로 graph를 표현하기 때문에 다음 Vertex를 가리켜줄 포인터입니다.
}Vertex;

typedef struct VertexHead //Vertex를 가리키는 Vertex*가 담겨있는 구조체입니다.
{
	Vertex* head;
}VertexHead;

typedef struct Graph //VertexHead들이 배열로 모여있는 곳을 가리키기 위한 vlist가 들어있는 graph 구조체입니다.
{
	VertexHead* vlist;
}Graph;

int Vertex_status[MAX_VERTEX] = { 0, }; //Vertex가 생성이 되었는지 표시하는 배열입니다.
//0으로 초기화가 되어, 1이면 해당 인덱스의 Vertex가 존재하는 것입니다. Vertex의 존재 유무를 판단하기 위해 정의하였습니다.

int DFS_flag[MAX_VERTEX] = { 0, }; //DFS에서 사용할 Visit flag입니다. 1이 들어있는 Index는 방문한 Vertex입니다.
int Stack[MAX_VERTEX]; //DFS에서 iterative 방식으로 구현하기 위해 사용하는 Stack입니다.
int StackTop = -1; //초기 StackTop을 -1로 설정해줍니다.

int BFS_flag[MAX_VERTEX] = { 0, }; //BFS에서 사용할 Visit flag입니다. 1이 들어있는 Index는 방문한 Vertex입니다.
int Queue[MAX_VERTEX]; //큐를 구현할 배열입니다.
int Front = 0; //큐의 front입니다.
int Rear = 0; //큐의 Rear입니다.


// <<<<<<<<<<<< 함수들의 목록 >>>>>>>>>>>>
void createGraph(Graph* graph); //기본적으로 그래프를 동적할당 해주는 함수입니다. 만약 그래프가 이미 존재한다면, 동적할당 해제 해준 뒤 동적할당 다시 받습니다.
void destroyGraph(Graph* graph); //그래프를 초기화하는 함수이다.
void freeVertexHead(VertexHead* VertexHead); //destroyGraph에서 사용하는 함수이며, vlist[i]와 같이 한 리스트에 대해 구석구석 동적할당 해제해줍니다.
void insertVertex(void); //Vertex를 삽입하는 함수입니다.
void HugeInsertion(void); //직접 정의한 함수로, 연속적인 숫자에 대해 Vertex insert를 쉽게하게 해주는 함수입니다.
int searchVertex(int vertex1, int vertex2); //HugeInsertion함수에서 범위 내에 Vertex가 이미 존재하는지 확인하기 위해 정의한 함수.
void swap(int* vertex1, int* vertex2); //두 수를 교환해주는 함수입니다.
void deleteVertex(Graph* graph); //Vertex를 제거해주는 함수입니다. 인접한 edge까지 모두 제거합니다.
void insertEdge(VertexHead* vlist); //Edge를 두 Vertex를 입력받고, 삽입해줍니다.
int searchNum(VertexHead* vlist, int vertex1, int vertex2);//insertEdge에서 이미 Edge가 존재하는데, 동일한 Edge를 추가하려는 경우를 걸러주기 위한 함수입니다.
//이 함수는 delteEdge에서도 같은 역할로 쓰입니다. 삭제하기 전에, 해당 Edge가 존재하는지 검사해주는 함수입니다.
void insertNode(VertexHead* h, int key); //인접리스트 1개에서, 오름차순에 맞게 key값을 삽입해주는 함수입니다.
void deleteNode(VertexHead* h, int key, int vertex, int option); //인접리스트 1개에서, key값을 삭제해주는 함수입니다.
void deleteEdge(Graph* graph); //사용자로부터 2개의 Vertex를 입력받아, 그 사이의 Edge를 삭제해주는 함수입니다.
void Push(int x); //Stack의 Push입니다.
int Pop(void); //Stack의 Pop입니다.
int adjacent(Graph* graph, int vertex, int* array); //depthFS와 breadthFS에서 사용합니다. 넘겨받는 Vertex와 인접하며 방문하지 않았던 vertex를 리턴합니다.
//depthFS에서 사용할때는 array에 DFS_flag를 넘겨주고, breadthFS에서 사용할때는 array에 BFS_flag를 넘겨주었습니다.
void flagClear(int* array); //DFS_flag, BFS_flag를 모두 0으로 초기화시켜주는 함수입니다.
void depthFS(Graph* graph); //DFS를 하는 함수입니다.
int isEmpty(void); //Queue의 공백 조건을 검사하는 함수입니다.
int isFull(void); //Queue의 풀 조건을 검사하는 함수입니다.
void enQueue(int item); //enQueue하는 함수입니다.
int deQueue(void); //deQueue하는 함수입니다.
void breadthFS(Graph* graph); //BFS를 하는 함수입니다.
void printGraph(Graph* graph); //그래프의 존재하는 Vertex, 존재하는 Edge, 인접리스트를 출력하는 함수입니다.

int main() //메인함수입니다.
{
	Graph graph; //그래프 하나를 만들어준다.
	graph.vlist = NULL; //그래프의 vlist 초기값은 NULL로 세팅해준다.
	int z_count = 0; //프로그램이 시작되고, 가장 먼저 Create Graph가 (Command z)가 실행되어야 하기 때문에 예외처리 해주기위한 변수.

	char command; //사용자로부터 명령 입력받기

	printf(">>>>>>>   Software, SUNGJIN PARK,  2017038063   <<<<<<<\n"); //소프트웨어학과 2017038063 박성진
	printf(">>>>>>>> 첫 Command는 반드시 z 혹은 Z를 입력해주세요 !!! <<<<<<<<\n"); //그래프의 생성을 위해 Z를 먼저 눌러야합니다.
	do{//Z를 먼저 누르지 않을 시, 오류 메세지가 출력되도록 구현하였습니다.
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                 TermProject : Graph                            \n");
		printf("----------------------------------------------------------------\n");
		printf(" Create Graph         = z      Huge Insertion               = h \n");
		printf(" Insert Vertex        = i      Delete Vertex                = d \n");
		printf(" Insert Edge          = r      Delete Edge                  = t \n");
		printf(" DFS                  = f      BFS                          = g \n");
		printf(" Print Graph          = p      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");
		printf("Command = ");
		scanf(" %c", &command);

		if((command != 'z' && command != 'Z') && z_count == 0) //첫 Command는 반드시 z를 입력받아야 하므로, z_count를 활용해서 예외처리
		{
			if(command != 'q' && command != 'Q') //q를 입력받으면 즉시 종료해줘야하기 때문에 예외처리.
			{
				printf("첫 Command는 반드시 z 혹은 Z를 입력해주세요 !!!\n"); //오류 메세지 출력
				printf("그래도 안된다면, 입력 값을 다시 한번 확인해주세요!!!\n"); //오류 메세지 출력
				continue; //새로 입력받기 위해 반복문의 조건으로 이동
			}
		}

		switch(command) {
		case 'z': case 'Z':
			createGraph(&graph); //z를 입력받으면 그래프를 생성합니다.
			z_count++; //z를 입력받을 때마다 z_count +1씩 증가
			break;
		case 'h': case 'H':
			HugeInsertion(); //Vertex로 연속된 정수를 입력할 때 유용하게 사용할 수 있다.
			break;
		case 'q': case 'Q':
			destroyGraph(&graph); //프로그램을 종료하기 전에 생성된 Graph의 모든 동적할당 해제
			break;
		case 'i': case 'I':
			insertVertex(); //Vertex를 한개씩 입력하는 함수입니다.
			break;
		case 'd': case 'D':
			deleteVertex(&graph); //Vertex 1개를 지우는 함수입니다.
			break;
		case 'r': case 'R':
			insertEdge(graph.vlist); //Edge 1개를 삽입하는 함수입니다.
			break;
		case 't': case 'T':
			deleteEdge(&graph); //Edge를 1개 삭제하는 함수입니다.
			break;
		case 'f': case 'F':
			depthFS(&graph); //DFS를 시행하는 함수입니다.
			break;
		case 'g': case 'G':
			breadthFS(&graph); //BFS를 시행하는 함수입니다.
			break;
		case 'p': case 'P':
			printGraph(&graph); //그래프의 현존하는 Edge,Vertex를 출력하고 인접리스트또한 출력합니다.
			break;

		default:
			break;
		}

	}while(command != 'q' && command != 'Q'); //q가 입력되면 종료

}


void createGraph(Graph* graph) //기본적으로 그래프를 동적할당 해주는 함수입니다. 만약 그래프가 이미 존재한다면, 동적할당 해제 해준 뒤 동적할당 다시 받습니다.
{
	if(graph->vlist == NULL) //그래프가 비어있다면
	{
		graph->vlist = (VertexHead*)malloc(sizeof(VertexHead) * MAX_VERTEX); //MAX_VERTEX사이즈 만큼 VertexHead를 동적할당 해준다.
		for(int i=0; i<MAX_VERTEX; i++) //vlist안에 모든 포인터 원소들을 널값으로 초기화해준다.
		{
			graph->vlist[i].head = NULL;
			Vertex_status[i] = 0; //Vertex의 생성을 나타내주는 배열도 초기값인 0으로 초기화해준다.
		}
		return;
	}
	else //그래프가 비어있지 않다면
	{
		destroyGraph(graph); //그래프를 먼저 동적할당 해제해주고
		createGraph(graph); //새로 동적할당 해제해줌과 동시에 초기화해준다
	}
}

void destroyGraph(Graph* graph) //그래프를 초기화하는 함수이다.
{
	if(graph->vlist == NULL) //그래프가 비어있다면 그대로 함수종료
		return;
	else //그래프가 차있다면, 초기화시켜줘야한다.
	{
		for(int i=0; i < MAX_VERTEX ; i++) //vlist의 각 인덱스에 접근해야한다.
		{
			freeVertexHead((graph->vlist)+i); //각 인덱스에 접근하면 VertexHead들이 있는데, 한개의 VertexHead를 구석구석 free해주는 함수를 반복호출한다.
		}
		free(graph->vlist); //최종적으로는 vlist를 free해준다.
		graph->vlist = NULL; //vlist는 NULL로 초기화해준다.
	}
}

void freeVertexHead(VertexHead* VertexHead) //destroyGraph에서 사용하는 함수이며, vlist[i]와 같이 한 리스트에 대해 구석구석 동적할당 해제해줍니다.
{
	Vertex* lead = VertexHead->head; //VertexHead의 head가 가리키는 곳을 lead가 가리키게 한다. Vertex들 사이를 움직일 포인터이다.
	Vertex* previous = NULL; //lead보다 한칸 이전의 위치를 기억해줄 포인터이다.
	while(lead != NULL) //lead가 가리키는 값이 널이 아닐때까지 반복한다, 즉 널이되면 빠져나온다.
	{
		previous = lead; //이전의 위치를 담기위해 현재 lead의 위치름 담고
		lead = lead->link; //리드를 다음 vertex로 이동시켜준다.
		free(previous); //이전의 vertex를 동적할당 해제해준다.
	}//이렇게되면, 한개의 VertexHead에 대해 모든 동적할당 해제가 가능하다.
	VertexHead->head = NULL; //VertexHead는 초기값인 NULL로 세팅해준다.
}

void insertVertex(void) //Vertex를 삽입하는 함수입니다.
{
	int num; //사용자로부터 삽입할 Vertex Number를 입력받습니다.
	while(1) //무한루프
	{
		printf("(Vertex Number는 0부터 19까지. -1을 입력하면 입력을 종료합니다.)\n삽입하실 Vertex Number를 입력해주세요. : ");
		if(scanf("%d", &num) != 1) //사용자로부터 Vertex Number를 입력받습니다.
		{//###완전히 사용자로부터 잘못된 입력을 받을시에도 이상없이 작동하도록 구현했습니다.
			while(getchar()!='\n');
			continue;
		}
		if(num == -1) //-1이 입력되는 경우 함수를 종료합니다.
		return;
		if(num < 0 || num > 19) //입력범위에 해당되지 않는 경우
		{
			printf("Vertex Number는 0부터 19까지만 가능합니다.\n"); //전처리해줍니다.
			continue; //반복문 조건문으로 돌아가, 입력을 다시 받도록 구현했습니다.
		}
		if(Vertex_status[num] == 1) //Vertex_status[num] == 1이라는 것은 이미 존재하는 Vertex라는 의미이므로, 오류 메세지 출력해줍니다.
		{
			printf("이미 입력된 Vertex입니다. 다른 Vertex Number를 입력해주세요.\n");
			continue; //반복문 조건문으로 돌아가, 입력을 다시 받도록 구현합니다.
		}
		else //정상적인 입력이 되었을 때
		{
			printf("Vertex[%02d] 정상 입력되었습니다.\n", num); //정상 메세지 출력
			Vertex_status[num] = 1; //Vertex_status array에서도 1로 값을 수정해줍니다.
			return;
		}
	}
}
//직접 정의한 함수로, 연속적인 숫자에 대해 Vertex insert를 쉽게하게 해주는 함수입니다.
void HugeInsertion(void) //입력의 편의성을 위해, 직접 제작한 함수입니다. 함수 내에서 사용자로부터 정수 2개를 입력받습니다.
{ //Vertex1과 Vertex2를 입력받고, 그 두 Vertex를 포함하여 사이에 있는 Vertex를 모두 InsertVertex합니다.
	int vertex1, vertex2; //Vertex 1, 2를 입력받습니다.
	while(1) //무한루프
	{
		printf("(Vertex Number는 0부터 19까지. -1과 -1을 입력하면 입력을 종료합니다.)\n");
		printf("HugeInsertion은 입력받은 두 정수 사이의 모든 정수를 Vertex로 Insert합니다.\n연속적으로 입력하고자하는 Vertex Number의 범위를 입력해주세요. : ");
		if(scanf("%d %d", &vertex1, &vertex2) != 2) //사용자로부터 Vertex 1, 2를 입력받습니다.
		{//###완전히 사용자로부터 잘못된 입력을 받을시에도 이상없이 작동하도록 구현했습니다.
			while(getchar()!='\n');
			continue;
		}
		if(vertex1 == -1 && vertex2 == -1) //-1과 -1을 입력받는 경우 함수를 종료합니다.
		return;
		if(vertex1 < 0 || vertex1 > 19) //입력범위를 벗어났을 시, 오류 메세지를 출력합니다.
		{
			printf("Vertex Number는 0부터 19까지만 가능합니다.\n");
			continue; //재입력받기위해, 반복문으로 돌아갑니다.
		}
		if(vertex2 < 0 || vertex2 > 19) //입력범위를 벗어났을 시, 오류 메세지를 출력합니다.
		{
			printf("Vertex Number는 0부터 19까지만 가능합니다.\n");
			continue; //재입력받기위해, 반복문으로 돌아갑니다.
		}
		if(vertex1 == vertex2) //동일한 Vertex를 입력할 시, 그 Vertex 한개를 삽입합니다.
		{
			if(Vertex_status[vertex1] == 1) //이미 존재하는 Vertex라면 오류 메세지를 출력합니다.
			{
				printf("이미 입력된 Vertex입니다. 다른 Vertex Number를 입력해주세요.\n"); //오류 메세지 출력
				continue; //입력을 다시 받기 위해 반복문으로 돌아갑니다.
			}
			else
			{
				printf("Vertex[%02d] 정상 입력되었습니다.\n", vertex1); //정상 메세지 출력
				Vertex_status[vertex1] = 1; //Vertex_status array에서도 1로 값을 수정해줍니다.
				return;
			}
		}
		if(vertex1 > vertex2) //사용자가 vertex1을 vertex2보다 큰 수로 입력했을 경우, 원활한 범위 설정을 위해 스왑해줍니다.
			swap(&vertex1, &vertex2); //직접 정의한 swap함수 호출
		if(searchVertex(vertex1, vertex2) == 1) //입력 범위 안에는 들어왔으나 범위 안에 이미 존재하는 Vertex가 포함 되어 있을 때
		{//searchVertex함수도 직접 정의한 함수입니다. 두 정수를 입력받아서, 범위 안에 이미 Vertex가 존재하면 1을 리턴합니다. 존재하지 않으면 0을 리턴합니다.
			printf("입력하신 범위 안에 이미 존재하는 Vertex가 포함되어 있습니다.\n");
			continue; //사용자로부터 입력을 다시 받습니다.
		}
		else //사용자가 입력한 정수 범위 안에 속하는 Vertex가 없을 시에, 그 범위 내의 모든 Vertex를 삽입합니다.
		{
			for(int i=vertex1; i<=vertex2; i++) //vertex1부터 vertex2까지
			{
				Vertex_status[i] = 1; //vertex를 삽입합니다.
			}
			printf("Vertex[%02d]부터 Vertex[%02d]까지 정상 입력되었습니다.\n", vertex1, vertex2); //정상 메세지 출력
			return; //함수 종료
		}
	}

}

int searchVertex(int vertex1, int vertex2) //HugeInsertion함수에서 범위 내에 Vertex가 이미 존재하는지 확인하기 위해 정의한 함수.
{
	for (int i=vertex1; i<=vertex2; i++) //범위 내를 탐색하며, 이미 존재하는 Vertex를 발견 시에 1을 리턴합니다.
	{
		if(Vertex_status[i] == 1)
			return 1;
	}
	return 0; //범위 내에 속하는 Vertex가 없을 시 0을 리턴합니다.
}

void swap(int* vertex1, int* vertex2) //단순히 두 정수를 서로 교환해주는 함수입니다. HugeInsertion함수에서 사용합니다.
{
	int temp;
	temp = *vertex1;
	*vertex1 = *vertex2;
	*vertex2 = temp;
}

void deleteVertex(Graph* graph) //사용자로부터 입력받은 숫자의 Vertex를 지워주는 함수입니다.
{
	int num; //사용자로부터 숫자를 입력받습니다.
	int adjacent[MAX_VERTEX] = { 0, }; //deleteVertex 과정에서, 삭제될 Vertex와 인접한 Vertex의 인접리스트에서도 효율적으로 지우기 위해 생성한 배열
	Vertex* lead; //삭제될 노드와 인접한 Vertex들을 탐색하기 위해, 이동할 Vertex 포인터
	while(1) //무한루프
	{
		printf("(Vertex Number는 0부터 19까지. -1을 입력하면 입력을 종료합니다.)\n삭제하실 Vertex Number를 입력해주세요. : ");
		if(scanf("%d", &num) != 1) //사용자로부터 숫자를 입력받습니다.
		{//###완전히 사용자로부터 잘못된 입력을 받을시에도 이상없이 작동하도록 구현했습니다.
			while(getchar()!='\n');
			continue;
		}
		if(num == -1) //-1이 입력되는 경우 함수를 종료합니다.
		return;
		if(num < 0 || num > 19) //입력 범위를 벗어났을 시, 오류 메세지를 출력합니다.
		{
			printf("Vertex Number는 0부터 19까지만 가능합니다.\n");
			continue; //다시 재입력 받기 위해서, 반복문의 조건으로 다시 돌아갑니다.
		}
		if(Vertex_status[num] == 1) //사용자로부터 입력받은 Vertex가 존재하는지 검사해서, 존재했을 경우에
		{
			lead = ((graph->vlist) + num)->head; //vlist[num]의 head의 위치를 lead에게 넘겨준다.
			while(lead != NULL) //lead가 해당 인접리스트를 순차 이동한다.
			{//탐색되는 모든 Vertex들의 num값을 가지고 adjacent[num]에 1로 저장한다.
				adjacent[lead->num] = 1; //adjacent배열에서 1을 가지는 인덱스들은 삭제될 Vertex의 인접 Vertex인 것이다.
				lead = lead->link; //리드의 위치를 다음 Vertex로 이동시켜준다.
			}
			for(int i=0; i<MAX_VERTEX; i++) //adjacent array를 탐색해서, 원소의 값이 1인 인덱스를 찾는다.
			{
				if(adjacent[i] == 1)
					deleteNode(graph->vlist+i, num, i, 1); //자체 정의함수인, deleteNode를 이용해서 Vertex[i]의 인접리스트에 접근하여, 사용자가 지우고자하는 Vertex를 지운다.
			}
			freeVertexHead((graph->vlist) + num); //자체 정의함수인, freeVertexHead를 호출하여 그 Vertex의 모든 동적할당을 해제하며, 널로 초기화시킵니다.
			Vertex_status[num] = 0; //또한, 이제 Vertex가 사라졌기 때문에, Vertex_status array에서 값을 0으로 수정해줍니다.
			printf("Vertex[%02d]를 삭제했습니다.\n", num); //정상 종료를 나타내는 메세지 출력.
			return; //함수 종료
		}
		else //Vertex가 존재하지 않을때, 오류 메세지를 출력하며, 사용자로부터 재입력 받습니다.
		{
			printf("Vertex Number[%02d]가 존재하지 않습니다.\n", num);
			continue; //반복문의 조건문으로 이동해 재입력받기.
		}
	}
}

void insertEdge(VertexHead* vlist) //사용자로부터 Vertex Number 2개를 받아, 그 사이의 엣지를 삽입해주는 함수입니다.
{
	int vertex1, vertex2; //Vertex 1, 2를 입력받습니다.
	while(1) //무한루프
	{
		printf("(Vertex Number는 0부터 19까지. -1과 -1을 입력하면 입력을 종료합니다.)\n연결시키고자하는 Vertex Number를 두 개 입력해주세요. : ");
		if(scanf("%d %d", &vertex1, &vertex2) != 2) //사용자로부터 Vertex 1, 2를 입력받습니다.
		{//###완전히 사용자로부터 잘못된 입력을 받을시에도 이상없이 작동하도록 구현했습니다.
			while(getchar()!='\n');
			continue;
		}
		if(vertex1 == -1 && vertex2 == -1) //-1과 -1을 입력받는 경우 함수를 종료합니다.
		return;
		if(vertex1 == vertex2) //동일한 Vertex를 입력할 시, 오류 메세지를 출력합니다.
		{
			printf("Graph는 Self-loop를 허용하지 않습니다.\n");
			continue;
		}
		if(vertex1 < 0 || vertex1 > 19) //입력범위를 벗어났을 시, 오류 메세지를 출력합니다.
		{
			printf("Vertex Number는 0부터 19까지만 가능합니다.\n");
			continue; //재입력받기위해, 반복문으로 돌아갑니다.
		}
		if(vertex2 < 0 || vertex2 > 19) //입력범위를 벗어났을 시, 오류 메세지를 출력합니다.
		{
			printf("Vertex Number는 0부터 19까지만 가능합니다.\n");
			continue; //재입력받기위해, 반복문으로 돌아갑니다.
		}
		if(Vertex_status[vertex1] != 1 || Vertex_status[vertex2] != 1) //입력 범위 안에는 들어왔으나, 존재하지않는 Vertex를 입력했을 시,
		{
			if(Vertex_status[vertex1] != 1 && Vertex_status[vertex2] == 1) //둘중에 하나만 잘못 입력했을 때, 아래처럼 오류 메세지 출력해줍니다.
			{
				printf("Vertex Number[%02d]가 존재하지 않습니다.\n", vertex1);
				continue;
			}
			else if(Vertex_status[vertex1] == 1 && Vertex_status[vertex2] != 1) //둘중에 하나만 잘못 입력했을 때, 아래처럼 오류 메세지 출력해줍니다.
			{
				printf("Vertex Number[%02d]가 존재하지 않습니다.\n", vertex2);
				continue;
			}
			else //둘 다 잘못입력했을 때 아래와 같이 오류메세지 출력해줍니다.
			{
				printf("Vertex Number[%02d]와 Vertex Number[%02d] 모두 존재하지 않습니다.\n", vertex1, vertex2);
				continue;
			}
		}
		if (searchNum(vlist, vertex1, vertex2) == 1) //이미 존재하는 Edge인지 확인하기 위해, 직접 만든 searchNum함수를 호출합니다.
		{ //위 함수의 리턴값이 1일경우 동일한 Edge가 있는 것입니다.
			printf("이미 동일한 Edge를 가지고 있습니다.\n"); //오류 메세지 출력
			continue;
		}
		else //동일한 Edge가 없는 경우
		{//Edge를 추가해줍니다.
			printf("Edge가 정상적으로 생성되었습니다.\n");
			insertNode((vlist + vertex1), vertex2); //vertex1을 인덱스로 가지는 vlist[vertex1]의 위치에 있는 인접리스트에 오름차순으로 vertex2를 삽입합니다.
			insertNode((vlist + vertex2), vertex1); //vertex2을 인덱스로 가지는 vlist[vertex2]의 위치에 있는 인접리스트에 오름차순으로 vertex1를 삽입합니다.
			return;
		}
	}
}

int searchNum(VertexHead* vlist, int vertex1, int vertex2) //insertEdge에서 이미 Edge가 존재하는데, 동일한 Edge를 추가하려는 경우를 걸러주기 위한 함수입니다.
{//이 함수는 delteEdge에서도 같은 역할로 쓰입니다. 삭제하기 전에, 해당 Edge가 존재하는지 검사해주는 함수입니다.
	Vertex* lead = vlist[vertex1].head; //vertex1의 인접리스트를 탐색하기 위한 lead를 설정해줍니다.
	while(lead != NULL) //lead가 인접리스트의 끝에 도달할때까지 반복문을 돌립니다.
	{
		if(lead->num == vertex2) //lead가 반복문을 돌면서 num값을 vertex2와 비교합니다.
		{
			return 1; //vertex2의 값과 같은 값이 있다면 1을 리턴해줍니다. (탐색 성공을 의미합니다.)
 		}
		lead = lead->link; //lead가 다음 Vertex로 이동할 수 있도록 움직여줍니다.
	}
	lead = vlist[vertex2].head; //vertex2의 인접리스트를 탐색하기 위해 lead를 재설정해줍니다.
	while(lead != NULL) //lead가 인접리스트 끝에 도달할때까지 반복문을 돌립니다.
	{
		if(lead->num == vertex1) //lead가 반복문을 돌면서 num값을 vertex1와 비교합니다.
		{
			return 1; //vertex1의 값과 같은 값이 있다면 1을 리턴해줍니다. (탐색 성공을 의미합니다.)
		}
		lead = lead->link; //lead가 다음 Vertex로 이동할 수 있도록 움직여줍니다.
	}
	return -1; //탐색 실패시 -1을 리턴합니다.
}

void insertNode(VertexHead* h, int key) //인접리스트 1개에서, 오름차순에 맞게 key값을 삽입해주는 함수입니다.
{
	Vertex* lead = h->head; //가장 첫번째 Vertex를 가리키는 리드 노드를 생성
	Vertex* previous = NULL; //이전 Vertex의 위치를 기억할 포인터 변수
	Vertex* vertex = (Vertex*)malloc(sizeof(Vertex)); //새로 삽입할 Vertex를 동적할당
	vertex->link = NULL; //새로 삽입할 Vertex의 꼬리를 널로 초기화
	int count = 0; //아래 반복문에서 반복되는 횟수를 세기 위한 카운트 변수
	vertex -> num = key; //넘겨받은 키 값을 새로 생성한 Vertex에 삽입

	if(h->head == NULL) //리스트에 아무 Vertex도 없는 경우
	{
		h->head = vertex; //새로 생성한 Vertex를 가장 첫 Vertex로 삽입
		vertex->link = NULL; //새로 생성한 Vertex의 꼬리를 널로 초기화
	}
	else //리스트에 적어도 1개의 Vertex가 있을 때
	{
		if(lead->link == NULL) //Vertex가 딱 1개만 있을 때
		{
			if(lead->num >= key) //새로 만든 Vertex의 키 값이 더 작은 경우
			{
				vertex->link = lead; //이미 있는 Vertex 앞에 새로만든 Vertex를 삽입
				h->head = vertex;
			}
			else //새로만든 Vertex의 키 값이 더 큰 경우
			{
				lead->link = vertex; //이미 있는 Vertex뒤에 새로만든 Vertex를 삽입
			}
			return; //끝나면 함수 종료.
		}
		while(lead != NULL) //Vertex가 2개이상 있을 때
		{
			count++; //반복문에 들어온 횟수를 한번씩 증가시켜가며 카운트
			if(lead->num >= key) //리드가 가리키는 키 값이 새로 만든 Vertex의 키 값보다 큰 경우
			{
				vertex->link = lead; //새로만든 Vertex를 리드 앞에 삽입
				if(count == 1) //새로만든 Vertex가 맨 앞에 있을 때
				{
					h->head = vertex; //맨 앞을 가리키는 헤드 포인터를 새로만든 Vertex로 초기화
					return; //함수 종료
				}
				else //새로만든 Vertex가 맨 앞에 있지 않을 때 (즉 Vertex와 Vertex사이에 있을 때)
				{
					previous->link = vertex; //이전 Vertex의 다음 Vertex로 새로만든 Vertex를 삽입.
					return; //함수 종료
				}
			}
			previous = lead; //이전을 가리키는 Vertex를 현재 리드가 가리키는 곳으로 지정
			lead = lead->link; //리드가 다음 Vertex를 가리키도록 지정
		}
		if(lead == NULL) //새로만든 Vertex가 가장 뒤쪽에 삽입되어야할 때
		{
			previous->link = vertex; //이전의 Vertex 뒤로 삽입한다.
			vertex->link = NULL;
		}
	}
}

void deleteNode(VertexHead* h, int key, int vertex, int option) //deleteVertex함수에서 삭제되는 vertex를 인접리스트에서 찾아서 삭제해줍니다.
{//여기서 인자로 넘겨받은 vertex는 탐색중인 Vertex를 나타내고, key값은 지워야하는 Vertex를 의미합니다!!!
	//option 매개변수는 deleteNode을 deleteVertex에서도 사용하고, deleteEdge에서도 사용하는데, 출력 문구의 변화를 주기 위해
	//option이 1로 넘어올때는, deleteVertex 함수에 관한 출력 메세지를, option이 2로 넘어올때는, deleteEdge 함수에 관한 출력 메세지만을 출력합니다.
	Vertex* lead = h->head; //head가 가리키는 곳을 lead가 가리키게 한다.
	Vertex* previous = NULL; //이전 Vertex를 가리킬 previous 변수를 초기값 널로 생성
	if(h->head == NULL) //아무 Vertex도 없을 때
	{
		if(option == 1) //deleteVertex 함수에서 이 함수를 사용할 경우에만 출력!
			printf("Vertex[%02d]에 아무 Vertex도 존재하지 않습니다.\n", vertex); //오류 메세지 출력
		return;
	}
	else //Vertex가 적어도 한개 이상 있을 때
	{
		while(lead->link != NULL) //인접리스트의 모든 Vertex를 검사
		{
			if(lead->num == key) //리드가 가리키는 키 값과 넘겨받은 키 값이 같으면
			{
				break; //반복문 탈출
			}
			previous = lead; //키값이 같지 않으면 previous를 현재 위치로 설정
			lead = lead->link; //현 리드를 다음 위치로 변경
		}

		if(lead->num != key) //반복문에서 결국 키 값을 찾지 못하고 빠져나오는 케이스를 처리
		{
			if(option == 1) //deleteVertex 함수에서 이 함수를 사용할 경우에만 출력!
				printf("Vertex[%02d]에 일치하는 Vertex가 없습니다.\n", vertex); //오류 메세지 출력
			return;
		}

		if(previous == NULL) //키 값을 찾은 경우 아래와 같이 총 세가지 케이스로 분류
		{//가장 앞에 있는 Vertex가 키 값과 일치하는 경우
			if(option == 1) //deleteVertex 함수에서 이 함수를 사용할 경우에만 출력!
				printf("Vertex[%02d]에서 일치하는 Vertex를 삭제했습니다.\n", vertex);
			h->head = lead->link;
			free(lead);
		}
		else if(lead->link == NULL) //가장 끝에 있는 Vertex가 키 값과 일치하는 경우
		{
			if(option == 1) //deleteVertex 함수에서 이 함수를 사용할 경우에만 출력!
				printf("Vertex[%02d]에서 일치하는 Vertex를 삭제했습니다.\n", vertex);
			previous->link = lead->link;
			free(lead);
		}
		else //Vertex가 인접리스트의 양 끝에 있지 않고 Vertex들 사이에 있는 경우
		{
			if(option == 1) //deleteVertex 함수에서 이 함수를 사용할 경우에만 출력!
				printf("Vertex[%02d]에서 일치하는 Vertex를 삭제했습니다.\n", vertex);
			previous->link = lead->link;
			free(lead);
		}
	}
}

void deleteEdge(Graph* graph)
{
	int vertex1, vertex2; //Vertex 1, 2를 입력받습니다.
	while(1) //무한루프
	{
		printf("(Vertex Number는 0부터 19까지. -1과 -1을 입력하면 입력을 종료합니다.)\n해제시키고자하는 Vertex Number를 두 개 입력해주세요. : ");
		if(scanf("%d %d", &vertex1, &vertex2) != 2) //사용자로부터 Vertex 1, 2를 입력받습니다.
		{//###완전히 사용자로부터 잘못된 입력을 받을시에도 이상없이 작동하도록 구현했습니다.
			while(getchar()!='\n');
			continue;
		}
		if(vertex1 == -1 && vertex2 == -1) //사용자로부터 -1 -1을 입력받으면 함수를 종료합니다.
		return;
		if(vertex1 == vertex2) //동일한 Vertex를 입력할 시, 오류 메세지를 출력합니다.
		{
			printf("Graph는 Self-loop를 허용하지 않습니다.\n");
			continue;
		}
		if(vertex1 < 0 || vertex1 > 19) //입력범위를 벗어났을 시, 오류 메세지를 출력합니다.
		{
			printf("Vertex Number는 0부터 19까지만 가능합니다.\n");
			continue; //재입력받기위해, 반복문으로 돌아갑니다.
		}
		if(vertex2 < 0 || vertex2 > 19) //입력범위를 벗어났을 시, 오류 메세지를 출력합니다.
		{
			printf("Vertex Number는 0부터 19까지만 가능합니다.\n");
			continue; //재입력받기위해, 반복문으로 돌아갑니다.
		}
		if(Vertex_status[vertex1] != 1 || Vertex_status[vertex2] != 1) //입력 범위 안에는 들어왔으나, 존재하지않는 Vertex를 입력했을 시,
		{
			if(Vertex_status[vertex1] != 1 && Vertex_status[vertex2] == 1) //둘중에 하나만 잘못 입력했을 때, 아래처럼 오류 메세지 출력해줍니다.
			{
				printf("Vertex Number[%02d]가 존재하지 않습니다.\n", vertex1);
				continue;
			}
			else if(Vertex_status[vertex1] == 1 && Vertex_status[vertex2] != 1) //둘중에 하나만 잘못 입력했을 때, 아래처럼 오류 메세지 출력해줍니다.
			{
				printf("Vertex Number[%02d]가 존재하지 않습니다.\n", vertex2);
				continue;
			}
			else //둘 다 잘못입력했을 때 아래와 같이 오류메세지 출력해줍니다.
			{
				printf("Vertex Number[%02d]와 Vertex Number[%02d] 모두 존재하지 않습니다.\n", vertex1, vertex2);
				continue;
			}
		}
		if (searchNum(graph->vlist, vertex1, vertex2) == 1) //이미 존재하는 Edge인지 확인하기 위해, 직접 만든 searchNum함수를 호출합니다.
		{ //위 함수의 리턴값이 1일경우 Edge가 있는 것입니다.
			deleteNode(graph->vlist+vertex2, vertex1, vertex2, 2); //vlist[vertex2]에 가서 vertex1 값을 가지면 해당 Vertex를 지웁니다.
			deleteNode(graph->vlist+vertex1, vertex2, vertex1, 2); //vlist[vertex1]에 가서 vertex2 값을 가지면 해당 Vertex를 지웁니다.
			printf("Edge가 정상적으로 삭제되었습니다.\n"); //정상 메세지 출력
			return;
		}
		else //해당하는 Edge가 없는 경우
		{
			printf("삭제할 Edge가 없습니다.\n"); //에러 메세지 출력
			continue; //반복문으로 돌아갑니다.
		}
	}
}

void Push(int x) //DFS에서 사용하는 Stack의 Push를 구현한 함수입니다.
{
	if(StackTop == MAX_VERTEX-1) //풀스택의 조건입니다.
	{
		printf("Stack이 가득 차있습니다.\n"); //오류 메세지 출력
		return; //함수 종료
	}
	Stack[++StackTop] = x; //스택에 자리가 남아있다면, Push진행.
	printf(" %02d ", x); //DFS 방문 순서에 맞게 출력해줍니다.
}

int Pop(void) //DFS에서 사용하는 Stack의 Pop을 구현한 함수입니다.
{
	if(StackTop == -1) //스택의 공백 조건입니다.
	{
		printf("Stack이 비어있습니다.\n"); //오류 메세지 출력
		return -1; //-1을 리턴
	}
	else //스택이 비어있지 않다면
		return Stack[StackTop--]; //Pop을 수행
}

int adjacent(Graph* graph, int vertex, int* array) //depthFS와 breadthFS에서 사용합니다. 넘겨받는 Vertex와 인접하며 방문하지 않았던 vertex를 리턴합니다.
{//depthFS에서 사용할때는 array에 DFS_flag를 넘겨주고, breadthFS에서 사용할때는 array에 BFS_flag를 넘겨주었습니다.
	Vertex* lead = NULL; //탐색을 위해 설정한 lead 포인터입니다.
	lead = graph->vlist[vertex].head; //lead가 넘겨받은 Vertex의 리스트를 가리킬 수 있도록 해줍니다.
	while(lead != NULL) //넘겨받은 Vertex의 인접 Vertex들을 순차 탐색합니다.
	{
		if(array[lead->num] == 0) //탐색하다가 방문하지 않은 Vertex를 발견하면 해당 Vertex Number를 리턴합니다.
		{
			array[lead->num] = 1; //lead->num을 방문했다고 flag array에 표시해줍니다.
			return lead->num;
		}
		lead = lead->link; //다음 Vertex로 이동.
	}
	return -1; //인접하는 Vertex가 없거나 방문하지 않았던 Vertex가 없다면 -1을 리턴합니다.
}

void flagClear(int* array) //DFS_flag와 BFS_flag를 0으로 초기화시켜주는 함수입니다.
{
	for(int i=0; i<MAX_VERTEX; i++)
	{
		array[i] = 0;
	}
}

void depthFS(Graph* graph)
{
	int num; //사용자로부터 입력받는 변수입니다.
	int startVertex; //사용자로부터 입력받은 num과 같은 값입니다. 의미를 상기시키기 위해 따로 만들어줬습니다.
	int w; //인접한 Vertex를 담기위한 변수입니다.
	flagClear(DFS_flag); //DFS_flag를 사용 전에 0으로 초기화해줍니다.
	while(1) //무한루프
	{
		printf("(Vertex Number는 0부터 19까지. -1을 입력하면 입력을 종료합니다.)\nDepth First Search를 시작할 Vertex Number를 입력해주세요. : ");
		if(scanf("%d", &num) != 1) //사용자로부터 Vertex Number를 입력받습니다.
		{//###완전히 사용자로부터 잘못된 입력을 받을시에도 이상없이 작동하도록 구현했습니다.
			while(getchar()!='\n');
			continue;
		}
		if(num == -1) //-1이 입력될 경우 함수를 종료합니다.
		return;
		if(num < 0 || num > 19) //입력범위에 해당되지 않는 경우
		{
			printf("Vertex Number는 0부터 19까지만 가능합니다.\n"); //전처리해줍니다.
			continue; //반복문 조건문으로 돌아가, 입력을 다시 받도록 구현했습니다.
		}
		if(Vertex_status[num] != 1) //사용자로부터 입력받은 Vertex가 존재하지 않을 때
		{
			printf("Vertex Number[%02d]가 존재하지 않습니다.\n", num); //오류 메세지 출력
			continue; //사용자로부터 다시 입력받을 수 있도록, 반복문의 조건문으로 복귀
		}
		else //사용자로부터 입력받은 Vertex가 존재하므로, DFS 시작!
		{
			printf("<Depth First Search>\n");
			startVertex = num; //사용자로부터 입력받은 Vertex Number를 시작점으로 설정합니다.
			DFS_flag[startVertex] = 1; //시작점을 방문했다고 표시해줍니다.
			Push(startVertex); //시작점을 스택에 푸쉬합니다.
			while(StackTop != -1) //스택이 공백 스택일때까지 반복합니다.
			{
				w = adjacent(graph, Stack[StackTop], DFS_flag); //직접 정의한 인접 함수를 활용해 인접 Vertex를 w에 저장합니다.
				if(w == -1) //adjacent의 비정상 리턴입니다. 즉, 인접 Vertex가 없거나 방문하지 않았던 Vertex가 없을 경우입니다.
					Pop(); //팝 해줍니다.
				else //adjacent가 정상적인 리턴일 때
					Push(w); //w를 푸시해줍니다.
			}
			printf("\n"); //개행문자 출력
			return; //함수 종료
		}
	}
}

int isEmpty(void) //Queue의 공백조건을 검사해주는 함수입니다.
{
	if(Front == Rear) //공백조건
	{
		printf("Circular Queue가 비어있습니다.\n"); //오류 메세지 출력
		return 1; //공백이면 1을 리턴하고
	}
	return 0; //공백이 아니면 0을 리턴합니다.
}

int isFull(void) //Stack의 풀 조건을 검사하는 함수입니다.
{
	if(Front == Rear) //풀 조건
	{
		if(Rear == 0) //isFull을 호출하기전에 Circular Queue에 따라 rear의 인덱스 1이 증가되었으므로 원상태로 돌려줍니다.
			Rear = MAX_VERTEX -1; //Circular Queue이기 때문에 Rear = 0일때는 가장 끝 인덱스로 돌려 보냅니다.
		else
			Rear = Rear -1;
		printf("Circular Queue가 가득 차있습니다.\n"); // 오류 메세지 출력
		return 1; //풀 조건이면 1을 리턴합니다.
	}
	return 0; //풀이 아니면 0을 리턴합니다.
}

void enQueue(int item) //enQueue해주는 함수입니다.
{
	Rear = (Rear+1) % MAX_VERTEX; //Circular Queue에 맞춰 증가시켜줍니다.
	if(isFull() == 1)
		return;
	Queue[Rear] = item;
}

int deQueue(void) //deQueue해주는 함수입니다.
{
	if(isEmpty() == 1)
		return -1;
	Front = (Front+1) % MAX_VERTEX; //Circular Queue에 맞춰 증가시켜줍니다.
	printf(" %02d ", Queue[Front]); //BFS 방문 순서에 맞게 출력해줍니다.
	return Queue[Front];
}

void breadthFS(Graph* graph)
{
	int num; //사용자로부터 입력받는 변수입니다.
	int startVertex; //사용자로부터 입력받은 num과 같은 값입니다. 의미를 상기시키기 위해 따로 만들어줬습니다.
	int w; //인접한 Vertex를 담기위한 변수입니다.
	int temp; //adjacent의 리턴값을 담을 임시용 변수입니다.
	flagClear(BFS_flag); //BFS_flag를 사용 전에 0으로 초기화해줍니다.
	while(1) //무한루프
	{
		printf("(Vertex Number는 0부터 19까지. -1을 입력하면 입력을 종료합니다.)\nBreath First Search를 시작할 Vertex Number를 입력해주세요. : ");
		if(scanf("%d", &num) != 1) //사용자로부터 Vertex Number를 입력받습니다.
		{//###완전히 사용자로부터 잘못된 입력을 받을시에도 이상없이 작동하도록 구현했습니다.
			while(getchar()!='\n');
			continue;
		}
		if(num == -1) //-1이 입력될 경우 함수를 종료합니다.
		return;
		if(num < 0 || num > 19) //입력범위에 해당되지 않는 경우
		{
			printf("Vertex Number는 0부터 19까지만 가능합니다.\n"); //전처리해줍니다.
			continue; //반복문 조건문으로 돌아가, 입력을 다시 받도록 구현했습니다.
		}
		if(Vertex_status[num] != 1) //사용자로부터 입력받은 Vertex가 존재하지 않을 때
		{
			printf("Vertex Number[%02d]가 존재하지 않습니다.\n", num); //오류 메세지 출력
			continue; //사용자로부터 다시 입력받을 수 있도록, 반복문의 조건문으로 복귀
		}
		else //사용자로부터 입력받은 Vertex가 존재하므로, DFS 시작!
		{
			printf("<Breadth First Search>\n");
			startVertex = num; //사용자로부터 입력받은 Vertex Number를 시작점으로 설정합니다.
			BFS_flag[startVertex] = 1; //시작점을 방문했다고 표시해줍니다.
			enQueue(startVertex); //시작점을 원형 큐에 푸쉬합니다.
			while(Front != Rear) //원형 큐가 공백 원형 큐일때까지 반복합니다.
			{
				w = deQueue(); //w에 deQueue한 값을 넣어줍니다.
				BFS_flag[w] = 1; //방문했다고 표시해줍니다.
				do
				{
					temp = adjacent(graph, w, BFS_flag); //인접한 인자를 리턴받아 temp에 임시 저장합니다.
					if(temp != -1) //인접한 인자가 있다면 인접한 인자를 인큐합니다.
						enQueue(temp);
				}while(temp != -1); //인접한 인자가 없을 때까지 반복해줍니다.
			}
			printf("\n"); //개행문자 출력
			return; //함수 종료
		}
	}
}

void printGraph(Graph* graph) //그래프에 관한 정보들을 출력합니다. Vertex의 생성 유무와 Edge의 정보를 보기 위해 인접 리스트를 출력합니다.
{
	Vertex* lead = NULL; //리드 포인터를 널로 초기화해줍니다.
	int count = 0; //가독성을 높이기 위해, 줄 맞춤을 위한 카운트 변수입니다.
	printf("#현재 존재하는 Vertex를 출력합니다.#\n\n");
	for (int i=0; i < MAX_VERTEX; i++) //Vertex의 생성 유무를 출력해줍니다.
	{ //Vertex_status[i]의 값이 1이면 Vertex가 생성되어 있는 것입니다.
		if(Vertex_status[i] == 1)
		{
			printf("Vertex[%02d]\t", i);
			count++;
			if(count % 4 == 0) //가독성을 높이기 위해, 한 줄에 4개씩 출력합니다.
				printf("\n");
		}
	}
	printf("\n\n#Edge가 존재하는 Vertex의 인접 Vertex를 출력합니다.#\n\n");
	for(int i=0; i < MAX_VERTEX; i++) //Vertex의 Edge를 보기 위해 인접 리스트를 출력합니다.
	{
		if(graph->vlist[i].head != NULL) //모든 Verex의 인접 Vertex를 출력하면 가독성이 떨어져서, Edge를 가지는 Vertex만 출력합니다.
		{
			lead = graph->vlist[i].head; //lead를 통해 한 Vertex의 리스트에 접근합니다.
			printf("Vertex[%02d] =", i); //출력 문구
			while(lead != NULL) //해당 리스트의 마지막까지 도달할 수 있도록 반복합니다.
			{
				printf(" %02d ", lead->num); //순차 탐색하면서 Vertex들의 num을 출력합니다.
				lead = lead->link; //리드 포인터를 다음 Vertex자리로 계속 옮겨줍니다.
			}
			printf("\n"); //한 Vertex의 인접 Vertex출력이 끝나면 개행문자를 하나 삽입해줍니다.
		}
	}
	count = 0; //아래에서 카운터 변수를 사용해야하므로 초기화해준다.
	printf("\n\n#모든 Edge를 출력합니다.\n\n"); //Edge에 관한 정보를 출력한다.
	for(int i=0; i<MAX_VERTEX; i++) //vlist를 탐색하기위해 반복해줍니다.
	{
		lead = graph->vlist[i].head; //lead가 vlist[i]의 헤드를 가리키도록 해줍니다.
		while(lead != NULL) //vlist[i]의 끝을 만날때까지 탐색합니다.
		{
			if(i < lead->num) //Edge를 출력하는 알고리즘입니다. vlist[i]에서 자기 자신인 i보다 큰 값을 만나면 출력해주면 됩니다.
			{
				printf("< %02d %02d >\t", i, lead->num); //Edge 출력
				count++; //카운트 1 증가
				if(count % 4 == 0) //가독성을 높이기 위해, 한 줄에 4개씩 출력합니다.
					printf("\n");
			}
			lead = lead->link; //리드 포인터를 다음 Vertex로 이동시켜줍니다.
		}
	}

}
