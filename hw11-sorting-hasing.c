/*
 * hw5-sorting.c
 *
 *  Created on: May 22, 2019
 *
 *  Homework 5: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h> //헤더파일들을 인클루드 해줍니다.
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */ //최대 배열 사이즈
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE // 최대 해쉬 테이블 사이즈를 최대 배열 사이즈와 같게 정의

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a); //배열을 초기화해주는 함수입니다. 원소의 값들은 0~12 랜덤을 이용합니다.
int freeArray(int *a); //동적할당 받은 배열을 동적할당 해제해주는 함수입니다.
void printArray(int *a); //배열의 원소들을 모두 출력해주는 함수입니다.

int selectionSort(int *a); //선택정렬 해주는 함수입니다.
int insertionSort(int *a); //삽입정렬 해주는 함수입니다.
int bubbleSort(int *a); //버블정렬 해주는 함수입니다.
int shellSort(int *a); //셸 정렬 해주는 함수입니다.
/* recursive function으로 구현 */
int quickSort(int *a, int n); //퀵 정렬해주는 함수입니다.


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key); //키값을 hashcode로 바꿔줍니다. %연산자를 활용했습니다.

/* array a에대한 hash table을 만든다. */
int hashing(int *a, int **ht); //배열을 활용해서 hash table을 만들어줍니다.

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key); //hash table에서 사용자가 입력한 키 값을 찾아서 해당하는 인덱스를 리턴해줍니다.


int main()
{
	char command; //사용자로부터 명령어 입력받기
	int *array = NULL; //배열을 가리키는 포인터를 널로 초기화시킨다
	int *hashtable = NULL; //해시테이블의 포인터를 널로 초기화시킨다
	int key = -1; //키 값을 초기값인 -1로 초기화시킨다
	int index = -1; //초기 인덱스 값을 -1로 초기화시킨다

	srand(time(NULL)); //seed의 값을 프로그램 실행중에 항상 변하는 시간으로 변경해준다
	//이로써 진짜 랜덤을 구현하게된다

	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = "); //사용자로부터 커맨드를 입려받는다
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array); //배열을 초기화시켜주는 함수를 호출
			break;
		case 'q': case 'Q':
			freeArray(array); //동적할당받은 배열을 동적할당 해제해주는 함수를 호출
			break;
		case 's': case 'S':
			selectionSort(array); //배열을 선택정렬 해주는 함수를 호출
			break;
		case 'i': case 'I':
			insertionSort(array); //배열을 삽입정렬 해주는 함수를 호출
			break;
		case 'b': case 'B':
			bubbleSort(array); //배열을 버블정렬 해주는 함수를 호출
			break;
		case 'l': case 'L':
			shellSort(array); //배열을 쉘정렬 해주는 함수를 호출
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //정렬하기 전의 배열을 출력합니다.
			quickSort(array, MAX_ARRAY_SIZE); //퀵 정렬해줍니다.
			printf("----------------------------------------------------------------\n");
			printArray(array); //정렬한 뒤의 배열을 출력합니다.

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array); //배열을 출력해줍니다.
			hashing(array, &hashtable); //배열을 활용하여 해싱해줍니다.
			printArray(hashtable); //해싱하여 얻은 hashtable을 출력해줍니다.
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key); //사용자로부터 키값을 입력받습니다.
			printArray(hashtable); //현재 hashtable을 출력합니다.
			index = search(hashtable, key); //hashtable에서 입력받은 키값과 일치하는 키값이 있으면 인덱스를 저장합니다.
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break; //일치하는 키값에 대한 정보들을 출력해줍니다.

		case 'p': case 'P':
			printArray(array); //배열의 관한 정보를 출력해주는 함수를 호출
			break;
		default: //잘못된 입력에 대한 오류메세지 출력
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //q가 입력되면 종료

	return 1;
}

int initialize(int** a) //배열을 초기화해주는 함수
{
	int *temp = NULL; //임시 변수 템프를 널포인터로 초기화

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) { //더블 포인터 a가 가리키는 곳, 배열의 주소를 a로 넘겨받았으므로 배열이 존재하지 않는다면
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); //템프에 배열 사이즈만큼 동적할당
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else //배열이 존재한다면
		temp = *a;  //템프가 그 배열에 접근할 수 있도록 포인팅

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) //모든 배열의 인덱스에 대하여
		temp[i] = rand() % MAX_ARRAY_SIZE; //모든 인덱스의 대한 값들을 0~12의 값들 중 랜덤으로 초기화

	return 0;
}

int freeArray(int *a) //동적할당 받은 배열을 동적할당 해제해주는 함수
{
	if(a != NULL) //배열이 비어있지 않다면 (존재한다면)
		free(a); //동적할당 해제해준다
	return 0;
}

void printArray(int *a) //배열에 관한 정보를 출력하는 함수
{
	if (a == NULL) { //배열이 존재하지 않는다면
		printf("nothing to print.\n"); //오류메세지 출력
		return;
	}//배열이 존재한다면
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) //배열의 모든 인덱스에 대해
		printf("a[%02d] ", i); //여백에는 0을 채워넣는 2자리의 정수로 a[00]~a[12]를 출력
	printf("\n"); //개행문자 출력
	for(int i = 0; i < MAX_ARRAY_SIZE; i++) //배열의 모든 인덱스에 대해
		printf("%6d ", a[i]); //6칸을 설정하여 배열의 원소값들을 출력, 기존에 5칸이었는데 라인이 맞지않아서 6칸으로 수정
	printf("\n"); //개행문자 출력
}


int selectionSort(int *a) //배열을 삽입정렬 해주는 함수
{
	int min; //최소값을 담을 변수
	int minindex; //최소값이 담겨있는 인덱스를 담을 변수
	int i, j; //for문을 돌릴 카운트 변수

	printf("Selection Sort: \n"); //삽입 정렬
	printf("----------------------------------------------------------------\n");

	printArray(a); //현재 배열의 정보들을 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++) //배열의 사이즈만큼 가장 바깥 포문을 돌린다. 즉, 13회 반복된다
	{
		minindex = i; //최소값이 담겨있는 인덱스는 i로 초기화된다, 0부터 12가 들어가게 된다
		min = a[i]; //최소값이 담길 변수에 인덱스 i에 위치한 배열의 원소가 담긴다
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) //j를 이용해서i+1의 인덱스부터 배열의 최종 인덱스까지 탐색한다
		{
			if (min > a[j]) //만약 min에 담겨있는 값이 j번째 인덱스보다 크다면
			{
				min = a[j]; //미니멈의 값을 j번째 인덱스의 값으로 바꿔준다
				minindex = j; //미니멈의 인덱스 또한 j로 바꿔준다
			}
		}//이것을 반복한다. 즉 i보다 큰 인덱스들을 다 탐색하여 미니멈 값과 미니멈 인덱스를 갱신해준다
		a[minindex] = a[i]; //위의 탐색에서 a[i] 보다 작은 값을 가지고 있던 인덱스인 J에 a[i]의 값을 넣어준다
		a[i] = min; //즉 더 작은 min을 발견했을 시의 swap의 과정이다!!! 이렇게 i=0부터 i=12까지 최소 값들을 채워나간다
	}

	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬 이후의 배열 정보들을 출력한다
	return 0;
}

int insertionSort(int *a) //삽입정렬에 관한 함수이다
{
	int i, j, t; //i,j는 for문을 돌리는 인덱스 겸 카운터 변수이고, t는 원소값을 담을 임시 변수이다

	printf("Insertion Sort: \n"); //삽입정렬
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬하기 전 현재 배열에 대한 정보들을 출력한다

	for(i = 1; i < MAX_ARRAY_SIZE; i++) // 인덱스 1부터 최종인덱스까지 접근한다. 즉 1부터 12까지 접근
	{
		t = a[i]; //인덱스 i번째의 원소 값을 t에 저장한다
		j = i; //그리고 j에 i번째 인덱스를 저장한다
		while (a[j-1] > t && j > 0) //i번째 인덱스가 가리키는 원소와 그 직전의 인덱스값의 원소의 크기를 비교해서
		{// 이전 인덱스의 값이 더 크면 swap한다
			a[j] = a[j-1];
			j--;
		}
		a[j] = t;
	}//즉 i번째 인덱스의 직전 모든 인덱스를 비교해서 i번째 인덱스가 가리키는 값의 올바른 위치를 찾아간다!!

	printf("----------------------------------------------------------------\n");
	printArray(a); //배열이 정렬된 이후의 정보들을 출력한다

	return 0;
}

int bubbleSort(int *a) //버블정렬 해주는 함수이다
{
	int i, j, t;  //i,j는 for문을 돌리는 인덱스 겸 카운터 변수이고, t는 원소값을 담을 임시 변수이다

	printf("Bubble Sort: \n"); //버블 정렬
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬되기 이전의 배열의 정보를 출력한다

	for(i = 0; i < MAX_ARRAY_SIZE; i++) //i가 인덱스 0부터 최종인덱스인 12까지 루프를 돈다
	{ //밑에 코드를 보면 알 수 있겠지만, 여기서 i는 단순히 루프 반복 횟수에만 개입한다
		for (j = 1; j < MAX_ARRAY_SIZE; j++) //j가 인덱스 1부터 최종인덱스인 12까지 루프를 돈다
		{//원래 j=0이었는데 j=1로 수정했습니다
			if (a[j-1] > a[j]) //j와 바로 그 직전 인덱스인 j-1이 가리키는 값을  계속 비교하면서 큰 값이 나오면
			{ //뒤쪽 인덱스로 계속 보낸다, 즉 가장 뒤쪽 인덱스에 가장 큰 값들이 차곡차곡 쌓인다
				t = a[j-1]; //a[j-1]과 a[j]를 swap하는 과정이다
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	} //위 코드에는 i와 j의 연관성이 상당히 떨어지는 코드라서, 사실 굳이 반복해야되지 않아도 될 끝 인덱스에 대해
	//계속 반복하여 낭비를 하고 있다! 가장 안쪽 for문에 j < MAX_ARRAY_SIZE -1로 수정해줘도 좋을 것 같다
	printf("----------------------------------------------------------------\n");
	printArray(a); //정렬이후의 배열을 출력한다

	return 0;
}

int shellSort(int *a) //셸 정렬을 해주는 함수이다
{
	int i, j, k, h, v; //i는 간격 h로인해 나뉜 그룹의 첫 인덱스들을 탐색해주기 위한 변수이고, j는 i에서 간격 h만큼 떨어진 인덱스들,
//즉 i가 속한 그 그룹을 탐색하는 변수이다. v,k는 삽입정렬에서 임시 저장할 변수들이고 h는 셀 정렬에서 쓰일 간격을 담는 변수이다.
	printf("Shell Sort: \n"); //셸 정렬
	printf("----------------------------------------------------------------\n");

	printArray(a); //정렬되기 전에 배열의 정보를 출력한다

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) //셸 정렬의 핵심인 h(간격)의 초기값을 일반적으로
	{//지금처럼 배열의 원소 개수의 절반으로 둔다. 여기서 h는 루프를 돌면서 계속 반으로 줄어 h=6,3,1이 되고 0이되면 루프 탈출
		for (i = 0; i < h; i++) //간격 h로 인해 나뉜 그룹의 가장 첫 인덱스들을 탐색해주는 반복문이다.
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h) //간격이 h이므로, 기준값인 i에 h를 더한 인덱스를 j라한다.
			{//j가 최대 인덱스 넘버인 12를 넘기지 않도록 한다. 여기서 j += h는 동일 간격만큼 떨어진 인덱스를 j로 모아 순회하는 것이다.
				v = a[j]; //여기서부터는 삽입정렬 알고리즘이다. 현재 j가 가지고있는 인덱스와, 그 배열 원소 값을 v,k에 임시 저장한다.
				k = j;
				while (k > h-1 && a[k-h] > v) //k가 h간격만큼 동일하게 떨어진 인덱스들을 모아 그 그룹끼리 삽입 정렬을 한다.
				{//즉, a[k]가 기준이 되고 그 이전 인덱스 중에 h만큼 간격이 떨어져있는 원소끼리 삽입 정렬하는 것!
					a[k] = a[k-h]; //이전 인덱스에서 큰 값이 발견되었을 시에, swap해주는 과정의 일부이다.
					k -= h; //k를 간격만큼 줄여서 올바른 위치를 찾아가준다.
				}
				a[k] = v; //삽입정렬에서 swap을 마무리하는 과정이다. 올바른 위치에 임시저장해뒀던 v를 넣어준다.
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a); //셸 정렬 이후의 배열을 출력해준다.

	return 0;
}

int quickSort(int *a, int n) //퀵 정렬을 해주는 함수이다. 여기서 초기 n값은 배열의 크기가 넘어온다!
{
	int v, t; //v,j에 피봇 값과 피봇의 인덱스 값을 임시로 저장한다.
	int i, j; //i,j는 각각 left, right인덱스를 담게된다.

	if (n > 1) //pivot을 배열의 맨 마지막값으로 설정한 것이다.
	{//그래서 v와 j라는 변수에 피봇 값과 right값(초기에는 피봇의 index)을 임시로 저장하고 있다.
		v = a[n-1];
		i = -1; //밑에 와일문에서 i값이 선 증가되기 때문에 -1로 설정되어있다. left 인덱스를 담고 있다.
		j = n - 1; //right 인덱스를 담고 있다.

		while(1)
		{
			while(a[++i] < v); //left를 이동시키는데 pivot값보다 크거나 같은 값에 위치시킨다.
			while(a[--j] > v); //right를 이동시키는데 pivot값보다 작거나 같은 값에 위치시킨다.

			if (i >= j) break; //left가 right를 넘어서 추월하게 되면 반복문을 빠져나간다.
			t = a[i]; //left가 right를 추월하지 않고 그대로 작으면 left가 가리키고있는 값과
			a[i] = a[j]; //right가 가리키고있는 값을 swap해준다.
			a[j] = t;
		}
		t = a[i]; //left가 right를 넘어서 추월하게 된 상황이다. 이 상황에서는
		a[i] = a[n-1]; //left가 가리키고있는 값과 pivot을 바꿔준다
		a[n-1] = t;

		quickSort(a, i); //i를 활용해서 right로 쓸 수 있도록 퀵소트 함수를 재귀 호출한다. 즉 피봇 기준으로 좌측 부분과
		quickSort(a+i+1, n-i-1); //오른쪽 부분의 나뉘게 된다. (n-i-1)을 활용해서 오른쪽 부분의 right를 구하게 된다.

	}


	return 0;
}

int hashCode(int key) { //Hash Function으로 division함수를 사용하였습니다.
   return key % MAX_HASH_TABLE_SIZE; //홈 버킷을 모드 연산자에 의해 결정하고 있습니다.
}
//hashing함수는 배열 a를 hashing하는 함수이다
int hashing(int *a, int **ht) //인자로 array와 &hashtable이 넘어오는데 hashtable이 인트 포인터이다.
{ //즉 저 포인터의 값을 바꿔주려고 더블 포인터로 받고있다.
	int *hashtable = NULL; //해시 테이블을 가리킬 포인터를 널포인터로 초기화

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {//해시 태이블이 널포인터를 가리킬경우 동적으로 메모리를 할당한다.
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE); //크기는 MAX_ARRAY_SIZE개 만큼
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++) //hash table을 재활용하는 과정이다.
		hashtable[i] = -1; //-1로 다 초기화 시켜주고 있다.

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1; //키값을 -1로 초기화한다
	int hashcode = -1; //hashcode를 -1로 초기화한다
	int index = -1; //인덱스를 -1로 초기화한다
	for (int i = 0; i < MAX_ARRAY_SIZE; i++) //배열의 모든 원소에 대한 탐색을 진행한다
	{ //즉 a의 모든 원소에 접근해서 hashing해준다. a의 원소들을 hashing해서 hashtable에 넣는 것이다.
		key = a[i]; //키값에 탐색중인 a[i]의 값을 넣어준다.
		hashcode = hashCode(key); //배열 a[i]의 값을 division 함수를 이용해서 hashcode에 넣어준다
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)  //해시 테이블의 초기값을 우리가 전부 -1로 설정했기 때문에 -1이면, 비어있는
		{//상태이다. 따라서, hashtable에 동일한 hashcode를 가지는 값이 없다는 것이므로, 그대로 값을 넣어준다.
			hashtable[hashcode] = key;
		} else 	{//만약에 hashtable의 값이 -1이 아니라면, 어떤 값이 들어가있다는 말이다

			index = hashcode; //index에 hashcode의 값을 넣어준다

			while(hashtable[index] != -1) //hashtable[index]가 -1이 될 때까지 반복문을 실행하면서
			{//hashtable[index]가 -1이 되는 위치를 찾는다. index는 오버플로 처리법중 선형 조사법을 활용했다.
				index = (++index) % MAX_HASH_TABLE_SIZE;
				//인덱스를 1씩 증가시키며 %연산을 실행한다. 즉 다음 칸으로 이동하는 것
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; //hashtable[index] == -1이 되는 위치를 찾았다면, 그 곳에 가지고 있던 key값을 넣어준다.
		}
	}

	return 0;
}

int search(int *ht, int key) //hashtable과 key값을 넘겨받는다.
{
	int index = hashCode(key); //사용자로부터 입력받은 key값을 hashcode함수를 호출해서 해시 주소를 만들어 index에 저장

	if(ht[index] == key) //hashtable에 방금 계산한 인덱스를 참고하여 그 값이 key값과 같은지 확인한다
		return index; //같으면 사용자가 원하는 key값을 찾은 것이므로, index를 리턴한다.

	while(ht[++index] != key) //키값이 일치하지 않는다면
	{
		index = index % MAX_HASH_TABLE_SIZE; //인덱스를 하나씩 늘려가며 hashcode 함수에서 해줬던 연산을 계속해준다
	}
	return index; //결국 일치하는 키값을 찾으면 그 index를 리턴해준다.
	//**********하지만 여기 while문의 문제점이 있는 것 같습니다. 사용자가 검색한 키값이 array, hashtable에 전혀
	//존재하지 않는다면, 무한 루프가 돌게 됩니다.!!!!!!!!!
	//또한 중복된 키값에 대한 인덱스는 상대적으로 작은 인덱스로 한번만 출력하게 됩니다!!!
}


