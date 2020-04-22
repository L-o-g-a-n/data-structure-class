/*
 * postfix.c
 *
 *  2020 Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STACK_SIZE 10
#define MAX_EXPRESSION_SIZE 20

/* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum{ //배열의 Index로 쉽게 쓰기위해 enum을 따로 초기화하지 않았습니다.
	lparen,  /* ( 왼쪽 괄호 */
	rparen,  /* ) 오른쪽 괄호*/
	times,   /* * 곱셈 */
	divide,  /* / 나눗셈 */
	plus,    /* + 덧셈 */
	minus,   /* - 뺄셈 */
	operand /* 피연산자 */
} precedence;


char infixExp[MAX_EXPRESSION_SIZE];   	/* infix expression을 저장하는 배열 */
char postfixExp[MAX_EXPRESSION_SIZE];	/* postfix로 변경된 문자열을 저장하는 배열 */
char postfixStack[MAX_STACK_SIZE];	/* postfix로 변환을 위해 필요한 스택 */
int evalStack[MAX_STACK_SIZE];		/* 계산을 위해 필요한 스택 */

static int isp[] = {0,19,13,13,12,12,0}; //스택 안에 있을때 연산 우선 순위 (숫자가 클수록 우선순위가 높다)
static int icp[] = {20,19,13,13,12,12,0}; //스택 밖에 있을때 연산 우선 순위 (숫자가 클수록 우선순위가 높다)

int postfixStackTop = -1;  /* postfixStack용 top */
int evalStackTop = -1;	   /* evalStack용 top */

int evalResult = 0;	   /* 계산 결과를 저장 */

void postfixPush(char x) //postfixstack에 push하는 함수
{
    postfixStack[++postfixStackTop] = x;
}

char postfixPop() //postfixstack에 pop하는 함수
{
    char x;
    if(postfixStackTop == -1) //postfixstack이 비어있으면 널을 리턴
        return '\0';
    else {
    	x = postfixStack[postfixStackTop--];
    }
    return x;
}


void evalPush(int x) //evalstack에 push하는 함수
{
    evalStack[++evalStackTop] = x;
}

int evalPop() //evalstack에 pop하는 함수
{
    if(evalStackTop == -1) //evalstack이 비어있으면 -1을 리턴.
        return -1;
    else
        return evalStack[evalStackTop--];
}


/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix() //infix형태로 입력받는 함수.
{
    printf("Type the expression >>> ");
    scanf("%s",infixExp);
}

precedence getToken(char symbol) //입력받은 문자를 precedence enum으로 리턴하는 함수.
{
	switch(symbol) {
	case '(' : return lparen;
	case ')' : return rparen;
	case '+' : return plus;
	case '-' : return minus;
	case '/' : return divide;
	case '*' : return times;
	default : return operand;
	}

}

precedence getPriority(char x) //getToken을 실행해주는 함수.
{ //하지만 여기서는 getToken 함수를 직접 쓰는 것과 별반 차이가 없다.
	return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)
{
	if (postfixExp == '\0') //postfixExp가 비어있을 경우에는 덮어씌어도 되므로 strncpy를 사용.
		strncpy(postfixExp, c, 1);
	else //postfixExp가 비어있지 않을 경우에는 이어 붙여야하므로 strncat을 사용.
		strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp; //infixExp를 가리키는 포인터
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */
	char a; //postfixPop()의 리턴값을 담기위한 변수.

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0') //exp를 하나씩 탐색하는데 널이 나올때까지 루프를 돈다.
	{
		/* 필요한 로직 완성 */
		x = *exp; //exp에서 따온 한글자를 x에 담는다.
		if (getToken(x) == operand) //x를 enum으로 봤을때 피연산자이면,
		{
			charCat(&x); //바로 출력할 수 있게 postfixExp에 넣어준다.
		}
		else //피연산자가 아니면,
		{
			if (getToken(x) == rparen) //그중에서도 우측 괄호일경우에, 왼쪽 괄호가 나올때까지 pop해준다.
			{
				do
				{
					a = postfixPop(); //팝을 해주고 임시변수 a에 담아준다.
					if (getToken(a) == lparen) //왼쪽 괄호가 나오면 멈춘다.
						break;
					charCat(&a); //pop해서 나온 원소를 postfixExp에 담아준다.
				}while(getToken(a) != lparen);
			}
			else if (icp[getToken(x)] > isp[getToken(postfixStack[postfixStackTop])])
			{//스택에 들어가기 전의 우선순위와 스택의 탑에 있는 원소의 연산자 우선순위를 비교해준다.
				postfixPush(x); //들어가기 전이 더 크면 푸쉬해준다.
			}
			else //들어가기 전이 더 작으면 팝해준 뒤 푸시해준다.
			{
				a = postfixPop(); //팝을 해주고 임시변수 a에 담아준다.
				charCat(&a); //팝한 원소는 postfixExp에 담아준다.
				postfixPush(x); //푸시를 해준다.
			}
		}
		exp++; //다음 원소를 탐색하기 위해 포인터를 증가시켜준다.
	}

	while(postfixStackTop != -1) //postfixstack에 남아있는 원소들을 모두 pop해준다.
	{
		a = postfixPop(); //하나씩 팝을 해주면서
		charCat(&a); //출력할 수 있도록 postfixExp에 하나씩 담아준다.
	}
	/* 필요한 로직 완성 */

}
void debug() //각종 정보를 상세하게 출력해주는 함수이다.
{
	printf("\n---DEBUG\n");
	printf("infixExp =  %s\n", infixExp);
	printf("postExp =  %s\n", postfixExp);
	printf("eval result = %d\n", evalResult);

	printf("postfixStack : ");
	for(int i = 0; i < MAX_STACK_SIZE; i++)
		printf("%c  ", postfixStack[i]);

	printf("\n");

}

void reset() //디버그 값들을 모두 0과같은 초기값으로 리셋해주는 함수이다.
{
	infixExp[0] = '\0';
	postfixExp[0] = '\0';

	for(int i = 0; i < MAX_STACK_SIZE; i++)
		postfixStack[i] = '\0';

	postfixStackTop = -1; //초기값으로 재설정.
	evalStackTop = -1;
	evalResult = 0;
}

void evaluation() //postfix를 연산해주는 함수이다.
{
	/* postfixExp, evalStack을 이용한 계산 */
	precedence token; //토큰을 담기위한 변수
	int a,b; //피연산자 2개를 담을 변수

	char *ptr = postfixExp; //postfixExp를 가리키기위한 포인터이다.

	while(*ptr != '\0')
	{
		token = getToken(*ptr); //ptr에서 1개의 원소를 뽑아 enum으로 바꾼다.

		if (token == operand) //피연산자일 경우,
		{
			evalPush(*ptr-48); //아스키코드값에 48을 빼서 우리가 원하는 int값을 푸쉬한다.
		}
		else //연산자일 경우,
		{
			a = evalPop(); //총 두개를 팝해서 a,b에 넣는다.
			b = evalPop();

			if (token == times) //stack의 구조 특성상 LIFO 구조이기때문에 b,a순으로 연산해준다.
				evalPush(b*a); //연산자의 기능에 맞게 연산해준다.
			else if (token == divide)
				evalPush(b/a);
			else if (token == plus)
				evalPush(b+a);
			else if (token == minus)
				evalPush(b-a);

		}
		ptr++; //다음 원소를 가리킨다.
	}
	evalResult = evalStack[evalStackTop]; //evalStackTop에 최종적인 연산 결과가 들어있다.
}


int main()
{
	char command;
	printf("----------------software 2017038063 박성진-----------------\n");
	do{
		printf("----------------------------------------------------------------\n");
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = "); //사용자로부터 명령을 입력받는다.
		scanf(" %c", &command);

		switch(command) { //입력받은 명령에 따른 함수를 실행한다.
		case 'i': case 'I':
			getInfix();
			break;
		case 'p': case 'P':
			toPostfix();
			break;
		case 'e': case 'E':
			evaluation();
			break;
		case 'd': case 'D':
			debug();
			break;
		case 'r': case 'R':
			reset();
			break;
		case 'q': case 'Q':
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 0;


}
