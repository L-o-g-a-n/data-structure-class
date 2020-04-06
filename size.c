#include <stdio.h>
#include <stdlib.h>

void main()
{
	int **x; //이중포인터 선언, 쓰레기 값이 들어가있을 것이다.
	printf("-----------------software 2017038063 박성진---------------\n");
	printf("sizeof(x) = %lu\n", sizeof(x)); //포인터 변수라서 64비트에선 8바이트가 출력
	printf("sizeof(*x) = %lu\n", sizeof(*x)); //마찬가지로 8바이트 출력
	printf("sizeof(**x) = %lu\n", sizeof(**x)); //인트형이기 때문에 4바이트 출력
}
