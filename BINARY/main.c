#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "math.h"

#include "stack.h"
#include "big.h"

#define OPERAND	100
#define OPERATOR       200
#define END            300
#define ERR            400

typedef struct info{
	int max;
	int neg;
}info;

int isoperator(char ch){
	if(ch == '^' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%')
		return 1;
	else
		return 0;
}

int precedence(char ch){
	if(ch == '+' || ch == '-')
		return 1;
	else if(ch == '*' || ch == '/')
		return 2;
	else if(ch == '%')
		return 3;
	else if(ch == '^')
		return 4;
	else
		return 0;
}

int nextop(char* str, int i){
//	str[i] = '('
	int j = i + 1;
	char ch = str[j];
	while(ch == ' '){
		j++;
		ch = str[j];
	}
	if(ch == '-'){
		return 1;
	}
	else
		return 0;
}

char* infixtopostfix(char* str, char* result){

	if(!str){
		return NULL;
	}
	int size = strlen(str), i = 0, j = 0, k = 0;
	char ch, x, prev = '\0';
	result = (char*)malloc(1024);
	cstack s;
	cinit(&s);
	cpush(&s, '(');
	ch = str[0];
	if(isoperator(ch) || ch == ' '){
		if(ch == '-'){
			result[k] = '0';
			result[k + 1] = ' ';
			k++;
			j = k;
		}
		if(ch == ' '){
			while(ch == ' '){
				ch = str[k++];
			}
			if(ch == '-'){
				result[j] = '0';
				result[j + 1] = ' ';
				j = 2;
			}
		}
		i = k - 1;
	}
	strcat(str, ")");
	ch = str[i];
	while(ch != '\0'){
		if(str[i] == '.' && str[i + 1] == '.'){
			printf("**Incorrect Expression.**\n");
			exit(1);
		}
		if(ch == '('){
			cpush(&s, ch);
			if(nextop(str, i)){
				ch = str[i + 1];
				i++;
				while(ch != '-'){
					result[j++] = ch;
					ch = str[i + 1];
					i++;
				}
				if(ch == '-'){
					result[j++] = ch;
				}
				if(isdigit(str[i + 1]) == 0){
					while(!isdigit(str[i + 1])){
						i++;
					}
					ch = str[i];
					prev = str[i - 1];
				}
				if(isdigit(str[i + 1])){
					i++;
					ch = str[i];
					result[j++] = ch;
					prev = ch;
				}
			}
		}

		else if(isdigit(ch)){
			if(isoperator(prev)){
				result[j++] = ' ';
			}
			result[j++] = ch;
		}

		else if(ch == ' ' || ch == '.'){
			result[j++] = ch;
		}

		else if(isoperator(ch)){

			if(isdigit(prev)){
				result[j++] = ' ';
			}
			if(!cisempty(&s)){
				x = cpop(&s);
			}
			while(isoperator(x) && precedence(x) >= precedence(ch)){
				result[j++] = x;
				result[j++] = ' ';
				x = cpop(&s);
			}
			cpush(&s, x);
			cpush(&s, ch);
		}
		else if(ch == ')'){
			if(!cisempty(&s)){
				x = cpop(&s);
			}
			while(x != '('){
				result[j++] = ' ';
				result[j++] = x;
				result[j++] = ' ';
				x = cpop(&s);
			}
		}
		else{
			printf("Invalid Infix Expression");
			exit(1);
		}
		i++;
		prev = ch;
		ch = str[i];
	}
	result[j] = '\0';

	return result;

}

typedef struct token{
	int type; // OPERAND, OPERATOR or END
	union data{
           int num; //  if type==OPERAND
	   char op; //  if type == OPERATOR
       }data;
}token;

enum state { NUMBER, OP, FINISH, ERROR, SPC };

//char *states[5] = { "NUMBER", "OP", "FINISH", "ERROR", "SPC" };

int power(int x, int y){
	int z = 1, i = 1;
	if(y == 0)
		return 1;
	for(i = 1; i <= y; i++){
		z = x * z;
	}
	return z;
}

token gettoken(char *expr) {
	static int i = 0;
	int no;
	char currchar;
	static enum state currstate = SPC;
	enum state nextstate;
	token t;

	while(1) {
		currchar = expr[i];
		switch(currstate) {
			case NUMBER:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						nextstate = NUMBER;
						no = no * 10 + (currchar - '0');
						i++;
						break;
					case '+': case '-': case '*': case '/': case '%': case '^':
						nextstate = OP;
						t.type = OPERAND;
						t.data.num = no;
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERAND;
						t.data.num = no;
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERAND;
						t.data.num = no;
						currstate = nextstate;
						i++;
						return t;
						break;
					default: 
						nextstate = ERROR;
						t.type = OPERAND;
						t.data.num = no;
						currstate = nextstate;
						return t;
						break;
				}
				break;
			case OP:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						no = currchar - '0';
						t.type = OPERATOR;
						t.data.op = expr[i - 1];
						nextstate = NUMBER;
						currstate = nextstate;
						i++;
						return t;
						break;
					case '+': case '-': case '*': case '/': case '%': case '^':
						nextstate = OP;
						t.type = OPERATOR;
						t.data.op = expr[i - 1];
						currstate = nextstate;
						i++;
						return t;
						break;
					case '\0':
						nextstate = FINISH;
						t.type = OPERATOR;
						t.data.op = expr[i - 1];
						currstate = nextstate;
						return t;
						break;
					case ' ':
						nextstate = SPC;
						t.type = OPERATOR;
						t.data.op = expr[i - 1];
						currstate = nextstate;
						i++;
						return t;
						break;
					default: // anything else
						nextstate = ERROR;
						t.type = OPERATOR;
						t.data.op = expr[i - 1];
						currstate = nextstate;
						return t;
					 	break;
				}
				break;
			case FINISH:
				t.type = END;
				return t;
				break;
			case ERROR:
				t.type = ERR;
				return t;
				break;
			case SPC:
				switch(currchar) {
					case '0':case '1':case '2': case '3':
					case '4':case '5':case '6': case '7':
					case '8':case '9':
						no = currchar - '0';
						nextstate = NUMBER;
						i++;
						break;
					case '+': case '-': case '*': case '/': case '%': case '^':
						nextstate = OP;
						i++;
						break;
					case '\0':
						nextstate = FINISH;
						break;
					case ' ':
						nextstate = SPC;
						i++;
						break;
					default: // anything else
						nextstate = ERROR;
						break;
				}
				currstate = nextstate;
				break;
		}
	}
}

int intpostfix(char *expr) {
	token t;
	int x, y, z;
	stack s;
	init(&s);
	while(1) {
		t = gettoken(expr);
		if(t.type == OPERAND){
                        if(!isfull(&s))
			     push(&s, t.data.num);
                        else
                             return INT_MIN;
		}else if(t.type == OPERATOR)  {
			if(!isempty(&s))
                              x = pop(&s);
			else
                              return INT_MIN;
                        if(!isempty(&s))
                              y = pop(&s);
			else
                              return INT_MIN;
			switch(t.data.op) {
				case '+':
					z = y + x;
					break;
				case '*':
					z = y * x;
					//printf("\n***\n");
					break;
				case '-':
					z = y - x;
					break;
				case '/':
					z = y / x;
					break;
				case '%':
					z = y % x;
					break;
				case '^':
					z = power(y, x);
					break;
				default:
					return INT_MIN;
			}
			if(!isfull(&s))
                           push(&s, z);
                        else
                             return INT_MIN;
		} else if(t.type == END)
			if(!isempty(&s))
                              return pop(&s);
			else
                              return INT_MIN;
	}
}

int fisoperator(char ch){
	if(ch == '^' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%')
		return 1;
	else
		return 0;
}

float fpower(float x, int y){
	float z = 1.0000;
	int i = 1, j = y;
	if(y == 0)
		return 1;
	if(y < 0)
		y = (-1)*y;
	for(i = 1; i <= y; i++){
		z = x * z;
	}
	if(j < 0){
		return 1/z;
	}
	return z;
}


float evalfloat(char* str){

	fstack s;
	finit(&s);
	int i = 0, j = 0, a, b, p, num_count = 0, op_count = 0;
	float x = 0, y = 0, z = 0, n = 0;
	char ch = str[i], num[100];
	for(j = 0; j < strlen(str); j++){

		ch = str[j];
		if(isdigit(ch) || ch == '.'){
			if(i < 100){
				num[i++] = ch;
			}
		}
		if(ch == ' ' || fisoperator(ch)){
			if(str[j - 1] != ' ' && !fisoperator(str[j - 1])){
				num[i] = '\0';
				n = atof(num);
				fpush(&s, n);
				i = 0;
				//num_count++;
			}
		}
		if(ch == '-' && isdigit(str[j + 1])){
				num[i] = ch;
				i++;
				ch = str[j + 1];
				//j++;
		}
		if(fisoperator(ch)){
			//op_count++;
			if(!fisempty(&s)){
				y = fpop(&s);
				if(!fisempty(&s))
					x = fpop(&s);
				else{
					printf("*ERROR*\n**Too many operators**\n");
					return INT_MIN;
				}
			}
			else
				continue;

			switch(ch) {
				case '+':
					z = x + y;
					break;
				case '-':
					z = x - y;
					break;
				case '*':
					z = x * y;
					break;
				case '/':
					z = x / y;
					break;
				case '%':
					a = (int)x;
					b = (int)y;
					z = (float)(a % b);
					break;

				case '^':
					p = (int)y;
					z = fpower(x, p);
					break;
			}
			if(!fisfull(&s)){
				fpush(&s, z);
			}
			else{
				printf("**ERROR**\n");
				return INT_MIN;
			}
		}
	}
	if(isdigit(str[j - 1])){
		printf("*ERROR*\n**Too many operands**\n");
		return INT_MIN;
	}
	return fpop(&s);
}

info strinfo(char* str){
	info t;
	int i = 0, n = strlen(str), count = 0, max = 0, size = 0;
	for(i = 0; i < n; i++){
		if(str[i] == '-' && isdigit(str[i + 1]))
			count++;
		if(isdigit(str[i]))
			size++;
		if(str[i] == ' '){
			if(size > max){
				max = size;
			}
			size = 0;
		}
	}
	t.neg = count;
	t.max = max;
	return t;
}


int readline(char *line, int len) {
	int i;
	char ch;
	i = 0;
	while(i < len - 1) {
		ch = getchar();
		if(ch == '\n') {
			line[i++] = '\0';
			return i - 1;
		}
		else
			line[i++] = ch;
	}
	line[len - 1] = '\0';
	return len - 1;
}

int space (char* str){
	int count = 0, i = 0, n = strlen(str);
	for( i = 0; i < n; i++){
		if(str[i] == ' ' )
			count++;
	}
	return count;
}

int main(int argc, char* argv[]){
	char str[2048], *result, *final, postfix[2048], *dot, SIZE, trigo[50], *tok;
	info t;
	int n = 0;
	float z = 0;
	char ch;
	Integer R;
	initInteger(&R, 1);

	printf("\n************************************************ ARBITARY-PRECISION-CALCULATOR ************************************************\n");
	printf("\t\t\t------------> Mihir Malani ------------> 111903046\n");
	printf("\t\t\tThis is free software with ABSOLUTELY NO WARRANTY.\n\n");
	printf("\tFor Trigonometric Functions\ttrigo\n");
	printf("\tFor normal expressions     \tEnter directly.\n\n");

	while(scanf("%[^\n]%*c", str) != EOF) {
		if(strcmp(str, "trigo") == 0){
			printf("\nS - Sine\tC - Cosine\tT - Tangent\nCalculates the value of only one function at a time.(0 in radians.)\n");
			while(scanf("%c", &ch) != EOF){
				scanf("\n");
				switch(ch){
					case 'S': case's':
						scanf("%[^\n]s", trigo);
						if(space(trigo)){
							result = infixtopostfix(trigo, final);
							z = evalfloat(result);
						}
						else
							z = atof(trigo);
						printf("0 = %f rad.\n", z);
						printf("Sine = %f\n", sin(z));
						break;

					case 'C': case 'c':
						scanf("%[^\n]s", trigo);
						if(space(trigo)){
							result = infixtopostfix(trigo, final);
							z = evalfloat(result);
						}
						else
							z = atof(trigo);
						printf("0 = %f rad.\n", z);
						printf("Cosine = %f\n", cos(z));
						break;
					case 'T': case 't':
						scanf("%[^\n]s", trigo);
						if(space(trigo)){
							result = infixtopostfix(trigo, final);
							z = evalfloat(result);
						}
						else
							z = atof(trigo);
						printf("0 = %f rad.\n", z);
						printf("Tangent = %f\n", tan(z));
						break;
					default:
						break;
				}
			}
		}
		else{
			SIZE = strlen(str);
			final = infixtopostfix(str, result);
			strcpy(postfix, final);
			t = strinfo(postfix);
			dot = strstr(postfix, ".");
			if(dot == NULL && t.neg == 0 && t.max < 5 && SIZE < 20){
				n = intpostfix(postfix);
  				printf("\n%d\n\n", n);
			}

			else if(dot != NULL && t.max < 5 && SIZE < 30){
				z = evalfloat(postfix);
				printf("\n%f\n\n", z);
			}

			else{
				R = bigpostfix(postfix);
				rmzero(&R);
				printf("\n");
				printInteger(R);
				printf("\n\n");
			}
		}
	}

	return 0;
}

