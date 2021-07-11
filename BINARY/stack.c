#include "stack.h"

/************stack************/

void init(stack *s) {
	s -> i = 0;
}
void push(stack *s, int no) {
	s -> a[s -> i] = no;
	s -> i++;
}
int pop(stack *s) {
	int t;
	t = s -> a[s -> i -1];
	s -> i--;
	return t;
}
int isempty(stack *s) {
	return s -> i == 0;
}
int isfull(stack *s) {
	return s -> i == MAX;
}

/************cstack************/

void cinit(cstack *s) {
	s -> i = 0;
}
void cpush(cstack *s, char ch) {
	s -> a[s -> i] = ch;
	s -> i++;
}
char cpop(cstack *s) {
	char t;
	t = s -> a[s -> i -1];
	s -> i--;
	return t;
}
int cisempty(cstack *s) {
	return s -> i == 0;
}
int cisfull(cstack *s) {
	return s -> i == MAX;
}

/************fstack************/

void finit(fstack *s) {
	s -> i = 0;
}
void fpush(fstack *s, float n) {
	s -> a[s -> i] = n;
	s -> i++;
}
float fpop(fstack *s) {
	float t;
	t = s -> a[s -> i -1];
	s -> i--;
	return t;
}
int fisempty(fstack *s) {
	return s -> i == 0;
}
int fisfull(fstack *s) {
	return s -> i == MAX;
}
