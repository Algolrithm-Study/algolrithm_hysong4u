#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 101
typedef int element; 


/*
1. 입력된 전위 표현식을 오른쪽에서 왼쪽으로 읽는다.
2. 피연산자를 만나면 push
3. 연산자를 만나면 스택에서 두 개의 피연산자를 pop, 해당 연산을 수행한 후, 그 결과를 다시 push
*/


typedef struct {
    element data[MAX_SIZE];
    int top;
} Stack;

int is_empty(Stack *s) {
    return (s->top == -1);   
}

int is_full(Stack *s) {
    return (s->top == MAX_SIZE - 1); 
}

void init_stack(Stack *s) {
    s->top = -1;
}

int push(Stack *s, element item) {
    if (!is_full(s)) {
        s->data[++(s->top)] = item; 
        return 1;
    } else {
        printf("stack is full\n"); 
        return 0;
    }
}

element pop(Stack *s) {
    if (!is_empty(s)) {
        return s->data[(s->top)--];
    } else {
        printf("stack is empty\n"); 
        return 0;
    }
}


void print_stacks(Stack *operand_stack, Stack *operator_stack) {
    printf("Operand Stack  : ");
    int length = operand_stack->top + 1;
    for (int i = 0; i < length; i++) {
        printf(" %d", operand_stack->data[i]);
    }
    printf(" \n");

    printf("Operator Stack : ");
    length = operator_stack->top + 1;
    for (int i = 0; i < length; i++) {
        printf(" %c", operator_stack->data[i]);
    }
    printf(" \n\n");
}



void prefix2StackEval(char *input) {
    Stack operator_stack;
    Stack operand_stack;

    init_stack(&operator_stack);
    init_stack(&operand_stack);

    int length = 0;
    while (input[length] != '\0') {
        length++;
    }

    int i = length - 1; //역순으로 해야함
    while (i >= 0) {
        if (input[i] >= '0' && input[i] <= '9') {
            int number = 0;
            int factor = 1;
            while (i >= 0 && input[i] >= '0' && input[i] <= '9') { //2자리수 이상인 수일 때
                number = number + (input[i] - '0') * factor;
                factor *= 10;
                i--;
            }
            push(&operand_stack, number);
            print_stacks(&operand_stack, &operator_stack);
        }

        else if (input[i] == '+' || input[i] == '-' || input[i] == '/' || input[i] == '*') {
            push(&operator_stack, input[i]);

            print_stacks(&operand_stack, &operator_stack);

            int A = pop(&operand_stack);
            int B = pop(&operand_stack);
            int result = 0;

            switch (input[i]) {
                case '+': result = A + B; break;
                case '-': result = A - B; break;
                case '*': result = A * B; break;
                case '/': result = A / B; break;
            }
            push(&operand_stack, result);
            pop(&operator_stack);

            print_stacks(&operand_stack, &operator_stack);
        }
        i--;
    }

    printf("Final result : %d\n", pop(&operand_stack));
}

int main(void) {

    printf("\n\n=============== 2021111945 송하연 ================\n\n");

    printf("\n\n===================== 실습 1  =====================\n\n");
    char *input1 = "* + 2 5 + 6 7";
    printf("INPUT : %s\n\n", input1);
    prefix2StackEval(input1);


    printf("\n\n===================== 실습 2  =====================\n\n");
    char *input2 = "+ - 7 2 * 8 / 12 4";
    printf("INPUT : %s\n\n", input2);
    prefix2StackEval(input2);


    printf("\n\n===================== 실습 3  =====================\n\n");
    char *input3 = "+ - 20 * 3 4 1";
    printf("INPUT : %s\n\n", input3);
    prefix2StackEval(input3);

    return 0;
}
