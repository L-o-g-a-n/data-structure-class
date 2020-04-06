#include <stdio.h>

struct student1 {
	char lastName;
	int studentId;
	char grade;
}; //student1 이라는 구조체를 정의, typedef를 안써줬기 때문에 항상 struct를 붙여써야한다.

typedef struct {
	char lastName;
	int studentId;
	char grade;
}student2; //student2라는 구조체를 정의

int main() {

	struct student1 st1 = {'A', 100, 'A'}; //student1이라는 구조체 데이터 타입의 변수 st1을 초기화
	printf("----------------software 2017038063 박성진-------------\n");
	printf("st1.lastName = %c\n", st1.lastName); //st1의 lastname 출력
	printf("st1.studentId = %d\n", st1.studentId); //st1의 studentId 출력
	printf("st1.grade = %c\n", st1.grade); //st1의 grade 출력

	student2 st2 = {'B', 200, 'B'}; //student2라는 구조체 데이터 타입의 변수 st2를 초기화.

	printf("\nst2.lastName = %c\n", st2.lastName); //st2의 lastName 출력
	printf("st2.studentId = %d\n", st2.studentId); //st2의 studentId 출력
	printf("st2.grade = %c\n", st2.grade); //st2의 grade 출력

	student2 st3; //student2 타입의 변수 st3을 선언

	st3 = st2; //st2를 st3에 덮어씌우기

	printf("\nst3.lastName = %c\n", st3.lastName); //st3의 lastName 출력
	printf("st3.studentId = %d\n", st3.studentId); //st3의 studentId 출력
	printf("st3.grade = %c\n", st3.grade); //st3의 grade 출력

	/* equality test */
	/*
	 * if(st3 == st2)
	 * 		printf("equal\n");
	 * 	else
	 * 		printf("not equal\n");
	 */      //이 동등성 테스트는 지원하지 않는다. 오류 발생.
	return 0;
}
