#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef char element;
typedef struct {
    int top;
    element *data;
    int capacity;
} Stack;

void initStack(Stack *s, int capacity) {
    s->top = -1;
    s->capacity = capacity;
    s->data = (element *)malloc(capacity * sizeof(element));
}

bool isEmpty(Stack *s) {
    return (s->top == -1);
}


void push(Stack *s, element item){
    if(s -> top == s -> capacity -1){
        s->capacity *= 2;
        s->data = (element *)realloc(s->data, s->capacity *sizeof(element));
    }
    s -> data[++(s->top)] = item ;
}

element pop(Stack *s){
    if(!isEmpty(s)){
    return s -> data[s->top--];
    }
}
bool check_matching(char *input) {
    Stack *s = (Stack *)malloc(sizeof(Stack));
    initStack(s, 10);

    for (int i = 0; i < strlen(input); i++) {
        char current = input[i];

        if (current == '[' || current == '{' || current == '(') {
            push(s, current);
        } 
        else if (current == ']' || current == '}' || current == ')') {
            if (isEmpty(s)) {
                free(s->data);
                free(s);
                return false; 
            }
            char pop_char = pop(s);
            if ((current == ']' && pop_char != '[') ||
                (current == '}' && pop_char != '{') ||
                (current == ')' && pop_char != '(')) {
                free(s->data);
                free(s);
                return false; 
            }
        }
    }

    bool result = isEmpty(s);
    free(s->data);
    free(s);
    return result; 
}

int main(void){
    char *input = "{[(12)]321}";

     if (check_matching(input)) {
        printf("괄호가 매칭됩니다.\n");
    } else {
        printf("괄호가 매칭되지 않습니다.\n");
    }

    return 0;
}


