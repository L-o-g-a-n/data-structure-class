#include <stdio.h>

#define MAX_SIZE 100 //맥스 사이즈를 100으로 정의

float sum(float [], int); //넘겨 받은 배열의 원소의 합을 구하는 함수를 선언
float input[MAX_SIZE], answer; //input이라는 배열과 answer 변수 선언
int i;
void main(void)
{
	printf("-----------------software 2017038063 박성진------------------\n");
	for(i=0; i < MAX_SIZE; i++) //input이라는 배열에 0부터 99까지 매핑
		input[i] = i;

	/* for checking call by reference */
	printf("address of input = %p\n", input); //Input의 주소를 출력


	answer = sum(input, MAX_SIZE); //answer에 sum함수의 리턴값을 담는다
	printf("The sum is: %f\n", answer); //answer를 출력
}

float sum(float list[], int n)
{

	printf("value of list = %p\n", list); //list의 값을 출력 여기선 input의 주소이다
	printf("address of list = %p\n\n", &list); //list의 주소값을 출력


	float tempsum = 0;
	for(i=0; i < n; i++) //0부터 n까지의 누적합을 계산한다.
		tempsum += list[i];
	return tempsum;
}
