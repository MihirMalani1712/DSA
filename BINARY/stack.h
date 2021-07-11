#define MAX 128
/* User to call init before calling other functions.
 * User to check isempty() before calling pop()
 * User to check isfull() before calling push()
 */
typedef struct stack{
	int a[MAX];
	int i;;
}stack;

void init(stack *s);
void push(stack *s, int no);
int pop(stack *s);
int isempty(stack *s);
int isfull(stack *s);

typedef struct fstack{
	float a[MAX];
	int i;
}fstack;
void finit(fstack *s);
void fpush(fstack *s, float n);
float fpop(fstack *s);
int fisempty(fstack *s);
int fisfull(fstack *s);

typedef struct cstack{
	char a[MAX];
	int i;;
}cstack;
void cinit(cstack *s);
void cpush(cstack *s, char ch);
char cpop(cstack *s);
int cisempty(cstack *s);
int cisfull(cstack *s);




