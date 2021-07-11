#define MAX 128

typedef struct node{
	char data;
	struct node* next;
	struct node* prev;
}node;

typedef struct Integer{
	node* front;
	node* rear;
	int sign;
	int dot;
}Integer;

typedef struct bstack{
	Integer a[MAX];
	int i;
}bstack;

void binit(bstack *s);
void bpush(bstack *s, Integer);
Integer bpop(bstack *s);
int bisempty(bstack *s);
int bisfull(bstack *s);
void initInteger(Integer* a, int n);
Integer createIntegerFromString(char* str);
void printInteger(Integer a);
int size(Integer a);
void appendleft(Integer *c, int no);

Integer addIntegers(Integer a, Integer b);
Integer subtractInt(Integer a, Integer b);
Integer multiply(Integer a, Integer b);
Integer divide(Integer a, Integer b);
Integer Power(Integer a, Integer b);
Integer modulus(Integer m, Integer n);
int iszero(Integer* a);
char* makestring(Integer a);
Integer bigpostfix(char* str);
Integer rmzero(Integer* a);




