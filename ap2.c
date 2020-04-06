#include <stdio.h>
#include <stdlib.h>

void main()
{
	int list[5]; //list 배열 선언
	int *plist[5]; //plist 포인터들이 모인 배열 선언

	list[0] = 10; //list[0]를 10으로 초기화
	list[1] = 11; //list[1]를 11로 초기화

	plist[0] = (int*)malloc(sizeof(int)); //plist[0]에 인트형 메모리를 동적할당

	printf("------------------software 2017038063 박성진------------------\n");
	printf("list[0] \t= %d\n", list[0]); //list[0]의 값을 출력
	printf("address of list \t= %p\n", list); //list의 주소를 출력
	printf("address of list[0] \t= %p\n", &list[0]); //list[0]의 주소를 출력
	printf("address of list + 0 \t= %p\n", list+0); //list+0의 주소를 출력
	printf("address of list + 1 \t= %p\n", list+1); //list+1의 주소를 출력
	printf("address of list + 2 \t= %p\n", list+2); //list+2의 주소를 출력
	printf("address of list + 3 \t= %p\n", list+3); //list+3의 주소를 출력
	printf("address of list + 4 \t= %p\n", list+4); //list+4의 주소를 출력
	printf("address of list[4] \t= %p\n", &list[4]); //list[4]의 주소를 출력

	free(plist[0]); //동적할당 해준 메모리를 반납
}
