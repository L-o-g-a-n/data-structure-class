#include <stdio.h>

struct student {
	char lastName[13];	/* 13 바이트 */
	int studentId;		/* 4 바이트 */
	short grade;			/* 2 바이트 */
};

int main()
{

	struct student pst; //student 타입의 변수 pst 선언

	printf("--------------software 2017038063 박성진---------------\n");
	printf("size of student = %ld\n", sizeof(struct student)); //구조체 student의 사이즈 출력
	printf("size of int = %ld\n", sizeof(int)); //int형의 사이즈 출력
	printf("size of short = %ld\n", sizeof(short)); //short형의 사이즈 출력
//원래 겉보기에는 13+4+2바이트로 19바이트가 나와야할 것 같지만 24바이트가 출력 되었다. 이것은 패딩 때문이다.
	return 0;
}
