#include <stdio.h>

void print1 (int *ptr, int rows); //print1 함수의 선언

int main()
{
	int one[] = {0,1,2,3,4}; //one이라는 배열을 초기화

	printf("----------------software 2017038063 박성진---------------\n");
	printf("one = %p\n", one); //배열 one의 주소 출력
	printf("&one = %p\n", &one); //one의 주소 출력
	printf("&one[0] = %p\n", &one[0]); //one[0]의 주소값을 출력
	printf("\n");

	print1(&one[0], 5); //print1함수 호출

	return 0;
}

void print1 (int *ptr, int rows)
{
	/* print out a one-dimensional array uing a pointer */

	int i;
	printf("Address \t Contents\n");
	for (i=0; i < rows; i++) //넘겨받은 배열의 모든 원소의 주소값과 들어있는 값을 출력
		printf("%p \t %5d\n", ptr + i, *(ptr + i));
	printf("\n");
}
