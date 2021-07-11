#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "big.h"
#include "stack.h"

void binit(bstack *s) {
	s -> i = 0;
}

void bpush(bstack *s, Integer n) {
	s -> a[s -> i] = n;
	s -> i++;
}

Integer bpop(bstack *s) {
	Integer t;
	initInteger(&t, 1);
	t = s -> a[s -> i -1];
	s -> i--;
	return t;
}

int bisempty(bstack *s) {
	return s -> i == 0;
}

int bisfull(bstack *s) {
	return s -> i == MAX;
}

int Isoperator(char ch){
	if(ch == '^' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%')
		return 1;
	else
		return 0;
}

void initInteger(Integer* a, int n){
	a -> front = NULL;
	a -> rear = NULL;
	a -> sign = n;
	a -> dot = 0;
}

void addDigit(Integer *a, char c){
	if(c > '9'){
		return;
	}
	node* newnode = (node*) malloc(sizeof(node));
	if(!newnode){
		printf("Can't allocate memory.\n");
		return;
	}
	newnode -> data = c;
	newnode -> next = NULL;
	newnode -> prev = NULL;
	if(a -> front == NULL){
		a -> front = newnode;
		a -> rear = newnode;
		return;
	}
	newnode -> prev = a -> rear;
	a -> rear -> next =  newnode;
	a -> rear = newnode;
}

int size(Integer a){
	node* ptr = a.front;
	if(!ptr){
		return 0;
	}
	int count = 0;
	while(ptr){
		ptr = ptr -> next;
		count++;
	}
	return count;
}

Integer createIntegerFromString(char* str){
	int i = 0, n = strlen(str), count = 0;
	char ch;
	Integer G;
	initInteger(&G, 1);
	if(str[i] == '-'){
		G.sign = -1;
		i++;
	}
	while(i < n){
		ch = str[i];
		if(count != 0){
			count++;
		}
		if(ch == '.'){
			count++;
			i++;
			ch = str[i];
		}
		addDigit(&G, ch);
		i++;
	}
	G.dot = count;
	return G;
}

void printInteger(Integer a){
	node* temp = a.front;
	char ch;
	int count = 0, n = size(a), k = n, loop = 1;
	if(!temp){
		printf("Empty Integer.\n");
	}
	if(a.sign < 0){
		printf("-");
	}
	if(a.dot >= n){
		printf("0");
		printf(".");
		while(k != a.dot){
			printf("0");
			k++;
		}
		loop = 0;
	}
	while(temp){
		if(count == n - a.dot && loop){
			printf(".");
		}
		ch = temp -> data;
		printf("%c", ch);
		temp = temp -> next;
		count++;
	}
	printf("\n");
}

void destroyInteger(Integer* a){
	node* ptr = a -> front;
	while(ptr){
		node* temp = ptr;
		ptr = ptr -> next;
		temp -> next = NULL;
		temp -> prev = NULL;
		free(temp);
	}
	initInteger(a, 1);
}

char* makestring(Integer a){
	int i = 0, n1 = size(a);
	char* result = (char*) malloc(10000);
	node* ptr = a.front;
	while(ptr){
		result[i] = ptr -> data;
		ptr = ptr -> next;
		i++;
	}
	result[i] = '\0';
	return result;
}

int iszero(Integer* a){
	if(a -> front == NULL){
		return 1;
	}
	node* ptr = a -> front;
	int sum = 0;
	while(ptr){
		sum = sum + (ptr -> data - '0');
		ptr = ptr -> next;
	}
	if(sum == 0){
		return 0;
	}
	else
		return 1;
}

Integer rmzero(Integer* a){
	if(!iszero(a)){
		Integer z = createIntegerFromString("0");
		return z;
	}
	node *ptr = a -> front, *temp = NULL;
	if(ptr -> data != '0'){
		return *a;
	}
	char ch = ptr -> data;
	while(ptr){
		ch = ptr -> data;
		if(ch == '0')
			ptr = ptr -> next;
		else
			break;
	}
	if(ch != '0'){
		temp = a -> front;
		a -> front = ptr;
		ptr -> prev = NULL;
		free(temp);
	}
	return *a;
}

void appendleft(Integer *c, int no){
	if(no < 0 || no > 9)
		return;
	node *tmp = (node *)malloc(sizeof(node));
	if(!tmp)
		return;
	tmp -> data = no + '0';
	tmp -> prev = NULL;
	if((c -> front == NULL) && (c -> rear == NULL)){
		tmp -> next = NULL;
		c -> front = c -> rear = tmp;
		return;
	}
	tmp -> next = c -> front;
	c -> front -> prev = tmp;
	c -> front = tmp;
	return;
}


// ADDITION

Integer addIntegers(Integer a, Integer b){

	int n1 = size(a), n2 = size(b), x = 0, y = 0, i = 0, sum = 0, carry = 0, SIZE = 0;
	char s, c;
	char* result = malloc(10000);
	Integer z;
	initInteger(&z, 1);

	if(a.dot > b.dot){
		while(a.dot != b.dot){
			addDigit(&b, '0');
			b.dot++;
		}
	}
	if(a.dot < b.dot){
		while(a.dot != b.dot){
			addDigit(&a, '0');
			a.dot++;
		}
	}

	node *ptr1 = a.rear, *ptr2 = b.rear;

	while(ptr1 != NULL || ptr2 != NULL){
		if(ptr1 == NULL && ptr2 != NULL){
			x = 0;
			y = ptr2 -> data - '0';
		}
		else if(ptr2 == NULL && ptr1 != NULL){
			y = 0;
			x = ptr1 -> data - '0';
		}
		else{
			x = ptr1 -> data - '0';
			y = ptr2 -> data - '0';
		}
		sum = (x + y + carry) % 10;
		carry = (x + y + carry) / 10;

		s = sum + '0';
		c = carry + '0';

		result[i] = s;

		if(ptr1){
			ptr1 = ptr1 -> prev;
		}
		if(ptr2){
			ptr2 = ptr2 -> prev;
		}
		i++;
	}
	if(carry != 0){
		result[i] = c;
		result[i + 1] = '\0';
	}
	else{
		result[i] = '\0';
	}
	char *final = (char*)malloc(10000);
	SIZE = strlen(result);

	for(i = 0; i < SIZE; i++){
		final[i] = result[SIZE - i - 1];
	}
	final[i] = '\0';

	z = createIntegerFromString(final);
	if(a.dot > b.dot){
		z.dot = a.dot;
	}
	else{
		z.dot = b.dot;
	}
	return z;
}


// SUBSTRACTION

Integer subtractInt(Integer a, Integer b){

	a = rmzero(&a);
	b = rmzero(&b);
	int n1, n2, x = 0, y = 0, i = 0, diff = 0, borrow = 0, SIZE = 0, sign = 0, loop = 1;
	char d, bo, result[10000];
	node *ptr1, *ptr2;

	if(a.dot > b.dot){
		while(a.dot != b.dot){
			addDigit(&b, '0');
			b.dot++;
		}
	}
	if(a.dot < b.dot){
		while(a.dot != b.dot){
			addDigit(&a, '0');
			a.dot++;
		}
	}
	printf("\n");
	n1 = size(a);
	n2 = size(b);
	if(n1 > n2){
		ptr1 = a.rear, ptr2 = b.rear;
		sign = 1;
	}
	if(n2 > n1) {
		ptr1 = b.rear, ptr2 = a.rear;
		sign = -1;
	}
	if(n1 == n2){
		ptr1 = a.front, ptr2 = b.front;

		while(ptr1 && ptr2 && loop){
			if(((ptr1 -> data - '0') - (ptr2 -> data - '0')) < 0){
				ptr1 = b.rear;
				ptr2 = a.rear;
				sign = -1;
				loop = 0;
				ptr1 = b.rear;
				ptr2 = a.rear;
				sign = -1;
			}
			else if(((ptr1 -> data - '0') - (ptr2 -> data - '0')) > 0){
				loop = 0;
				ptr1 = a.rear;
				ptr2 = b.rear;
				sign = 1;
			}
			else{
				ptr1 = ptr1 -> next;
				ptr2 = ptr2 -> next;
			}
		}
		if(!ptr1 && !ptr2){
			ptr1 = a.rear;
			ptr2 = b.rear;
			sign = 1;
		}
	}
	while(ptr1 != NULL || ptr2 != NULL){
		if(ptr1 == NULL && ptr2 != NULL){
			x = 0;
			y = ptr2 -> data - '0';
		}
		else if(ptr2 == NULL && ptr1 != NULL){
			x = ptr1 -> data - '0';
			y = 0;
		}
		else{
			x = ptr1 -> data - '0';
			y = ptr2 -> data - '0';
		}
		diff = (x - y - borrow);
		if(diff < 0){
			borrow = 1;
			diff = diff + 10;
		}
		else{
			borrow = 0;
		}

		d = diff + '0';
		bo = borrow + '0';

		result[i] = d;

		if(ptr1){
			ptr1 = ptr1 -> prev;
		}
		if(ptr2){
			ptr2 = ptr2 -> prev;
		}
		i++;
	}

	if(borrow != 0){
		result[i] = bo;
		result[i + 1] = '\0';
	}
	else{
		result[i] = '\0';
	}

	char *final = (char*)malloc(10000);
	SIZE = strlen(result);

	for(i = 0; i < SIZE; i++){
		final[i] = result[SIZE - i - 1];
	}
	final[i] = '\0';

	Integer z;
	initInteger(&z, sign);
	z = createIntegerFromString(final);
	z.sign = sign;
	if(a.dot >= b.dot){
		z.dot = a.dot;
	}
	else{
		z.dot = b.dot;
	}
	return z;

}

// PRODUCT

Integer multiply(Integer a, Integer b){

	char *s1, *s2;
	s1 = makestring(a);
	s2 = makestring(b);
	int n1 = strlen(s1), n2 = strlen(s2), i = 0, j = 0, temp = 0, size = 0;
	char* num1 = (char*) malloc(10000);
	char* num2 = (char*) malloc(10000);
	char* result = (char*) malloc(10000);

	for(i = 0; i < n1; i++){
		num1[i] = s1[n1 - i - 1];
	}
	num1[i] = '\0';
	for(i = 0; i < n2; i++){
		num2[i] = s2[n2 - i - 1];
	}
	num2[i] = '\0';

	int* prod = (int*) calloc(n1 + n2, (n1 + n2)*(sizeof(int)));

	for(j = 0; j < n2; j++){
		for(i = 0; i < n1; i++){
			prod[i + j] = prod[i + j] + (num1[i] - '0') * (num2[j] - '0');
		}
	}
	for(i = 0; i < n1 + n2; i++){
		temp = prod[i] / 10;
		prod[i] = prod[i] % 10;
		prod[i + 1] = prod[i + 1] + temp;
	}

	for(i = n1 + n2; i >= 0; i--){
		if(prod[i] > 0)
			break;
	}
	size = i + 1;
	result = (char*) malloc(10000);
	for(i = 0; i < size; i++){
		result[i] = prod[size - i - 1] + '0';
	}
	result[i] = '\0';
	if(strlen(result) == 0){
		Integer m = createIntegerFromString("0");
		return m;
	}
	Integer m = createIntegerFromString(result);
	m.dot = a.dot + b.dot;
	return m;
}

// DIVISION

Integer divide(Integer m, Integer n){

	char *str1, *str2, ch;
	str1 = makestring(m);
	str2 = makestring(n);
	int i = 0, sum = 0, p = m.dot, q = n.dot, n1 = strlen(str1), n2 = strlen(str2), g = 0;
	Integer c, a, b, y, z;
	initInteger(&a, 1);
	initInteger(&b, 1);
	initInteger(&c, 1);
	initInteger(&y, 1);
	initInteger(&z, 1);
	if(str1[n1 - p] > '4'){
		g = str1[n1 - p - 1] - '0';
		g++;
		str1[n1 - p - 1] = g + '0';
	}
	str1[n1 - p] = '\0';

	if(str2[n2 - q] > '4'){
		g = str1[n2 - q - 1] - '0';
		g++;
		str2[n2 - q - 1] = g + '0';
	}
	str2[n2 - q] = '\0';

	if(atoi(str2) == 1){
		return m;
	}

	if(strlen(str1) < strlen(str2)){
		z = createIntegerFromString("0");
		return z;
	}
	for(i = 0; i < strlen(str2); i++){
		sum = sum + (str2[i] - '0');
	}
	if(sum == 0){
		printf("*ERROR*\n**N/0 form encountered.**\n");
		exit(1);
	}
	a = createIntegerFromString(str1);
	b = createIntegerFromString(str2);
	y = createIntegerFromString("0");
	z = createIntegerFromString("1");
	c = subtractInt(a, b);
	if(iszero(&c) == 0){
		return z;
	}
	if(c.sign < 0){
		return y;
	}
	i = 0, g = 0;
	n1 = strlen(str1), n2 = strlen(str2);
	char* result = (char*) malloc(strlen(str1) + 1);

	strcpy(result, str1);
	g = n2 + 1;
	str1[n2 + 1] = '\0';
	a = createIntegerFromString(str1);
	for(i = 0; i <= strlen(result) - strlen(str1); i++){
		if(iszero(&y)){
			addDigit(&y, '0');
		}
		while(subtractInt(a, b).sign > 0){
			initInteger(&c, 1);
			c = subtractInt(a,b);
			c = rmzero(&c);
			y = addIntegers(y, z);
			a = c;
			c = subtractInt(a, b);
		}
		if(c.sign < 0){
			c = subtractInt(b, c); // 
			ch = result[g++];
			if(ch != '\0')
				addDigit(&c, ch);
			c = rmzero(&c);
			a = c;
		}
	}
	return y;
}



// Modulo

Integer modulus(Integer m, Integer n){
	Integer a, b, z;
	initInteger(&a, 1);
	initInteger(&b, 1);
	initInteger(&z, 1);
	z.sign = m.sign * n.sign;
	a = divide(m, n);
	b = multiply(a, n);
	z = subtractInt(m, b);
	return z;
}

// Power

Integer Power(Integer a, Integer b){
	Integer x;
	initInteger(&x, 1);
	x = createIntegerFromString("1");
	int n1 = size(a), n2 = size(b), n = 0, i = 0;
	if(b.dot >= n1 || !iszero(&b)){
		return x;
	}

	char* str2 = makestring(b);
	str2[n2 - b.dot] = '\0';
	n = atoi(str2);
	if(n < 0){
		return x;
	}
	for(i = 0; i < n; i++){
		x = multiply(x, a);
	}
	return x;
}


Integer bigpostfix(char* str){
	bstack s;
	binit(&s);
	int i = 0, j = 0, n = strlen(str);
	char* num = (char*) malloc(2048);
	char curr = str[i];
	Integer x, a, b, c;
	initInteger(&x, 1);
	initInteger(&a, 1);
	initInteger(&b, 1);
	initInteger(&c, 1);
	for(i = 0; i < n; i++){
		curr = str[i];
		if(isdigit(curr) || curr == '.'){
			num[j++] = curr;
		}
		if(curr == ' '){
			num[j] = '\0';
			if(strlen(num) != 0){
				initInteger(&x, 1);
				x = createIntegerFromString(num);
				bpush(&s, x);
			}
			j = 0;
		}
		if(curr == '-' && isdigit(str[i + 1])){
			num[j] = curr;
			curr = str[i + 1];
			j++;
		}
		if(Isoperator(curr)){

			if(!bisempty(&s)){
				b = bpop(&s);
			}

			if(!bisempty(&s)){
				a = bpop(&s);
			}

			else {
				printf("*ERROR*\n**Too many operators**\n");
				exit(1);
			}

			switch(curr){

				case '+':{

					if(a.sign > 0 && b.sign > 0){
						c = addIntegers(a,b);
						break;
					}

					if(a.sign > 0 && b.sign < 0){
						c = subtractInt(a, b);
						break;
					}
					if(a.sign < 0 && b.sign > 0){
						c = subtractInt(b, a);
						break;
					}
					if(a.sign < 0 && b.sign < 0){
						c = addIntegers(a, b);
						c.sign = -1;
						break;
					}
				}
				case '-':{

					if(a.sign > 0 && b.sign > 0){
						c = subtractInt(a, b);
						break;
					}
					if(a.sign > 0 && b.sign < 0){
						c = addIntegers(a, b);
						break;
					}
					if(a.sign < 0 && b.sign > 0){
						c = addIntegers(a, b);
						c.sign = -1;
						break;
					}
					if(a.sign < 0 && b.sign < 0){
						c = subtractInt(a, b);
						break;
					}
				}
				case '*':{

					if(a.sign * b.sign > 0){
						c = multiply(a, b);
						break;
					}
					if(a.sign * b.sign < 0){
						c = multiply(a, b);
						c.sign = -1;
						break;
					}
				}
				case '/':{

					if(a.sign * b.sign > 0){
						c = divide(a, b);
						break;
					}
					if(a.sign * b.sign < 0){
						c = divide(a, b);
						c.sign = -1;
						break;
					}
				}
				case '%':{
					c = modulus(a, b);
					break;
				}
				case '^':{
					c = Power(a, b);
					break;
				}
			}
			if(!bisfull(&s)){
				bpush(&s, c);
			}
			else
				printf("*ERROR\n*");
		}
	}
	x = bpop(&s);
	return x;
}





