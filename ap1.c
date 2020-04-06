#include <stdio.h>
#include <stdlib.h>

void main()
{
	int list[5]; //list라는 배열을 생성
	int *plist[5] = {NULL,}; //자료형이 인트 포인터인 변수 5개로 이루어진 배열

	plist[0] = (int *)malloc(sizeof(int)); //plist배열 첫 원소에 인트 사이즈 만큼 즉 4바이트 만큼 동적할당.

	list[0] = 1; // 1로 초기화
	list[1] = 100; //100으로 초기화

	*plist[0] = 200; // 동적할당한 plist[0]이 가리키는 곳에 200으로 초기화

	printf("----------------software 2017038063 박성진------------------\n");
	printf("value of list[0] = %d\n", list[0]); // list[0]의 값 출력
	printf("address of list[0] = %p\n", &list[0]); //list[0]의 주소 출력
	printf("value of list = %p\n", list); //list의 값 출력
	printf("address of list (&list) = %p\n", &list); //list의 주소값 출력

	printf("-------------------------------------------\n\n");
	printf("value of list[1] = %d\n", list[1]); //list[1]의 값인 100출력
	printf("address of list[1] = %p\n", &list[1]); //list[1]의 주소 출력
	printf("value of *(list+1) = %d\n", *(list + 1)); //마찬가지로 list[1]의 값이 출력
	printf("address of list+1 = %p\n", list+1); //list[1]의 주소 값을 출력

	printf("-------------------------------------------\n\n");

	printf("value of *plist[0] = %d\n", *plist[0]); //plist[0]이 가리키는 값을 출력
	printf("&plist[0] = %p\n", &plist[0]); // plist[0]의 주소값을 출력
	printf("&plist = %p\n", &plist); //plist의 주소값을 출력
	printf("plist = %p\n", plist); //plist를 출력
	printf("plist[0] = %p\n", plist[0]); //plist[0]의 값을 출력
	printf("plist[1] = %p\n", plist[1]); //plist[1]부터 plist[4]의 주소값을 출력
	printf("plist[2] = %p\n", plist[2]); //초기에  null 포인터로 초기화 했기 때문에
	printf("plist[3] = %p\n", plist[3]); //모두 null 이다.
	printf("plist[4] = %p\n", plist[4]);

	free(plist[0]); //동적할당 해준 메모리를 반납한다.

}
