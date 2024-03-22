#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_SIZE 100

typedef struct {
    int top;
    char items[MAX_SIZE];
} Stack;

void push(Stack *s, char c);
char pop(Stack *s);
bool is_empty(Stack *s);
bool is_operator(char c);
int precedence(char c);
void infix_to_postfix(char *infix, char *postfix);

int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];

    printf("Enter infix expression: ");
    fgets(infix, MAX_SIZE, stdin);

    infix_to_postfix(infix, postfix);

    printf("Postfix expression: %s\n", postfix);

    return 0;
}

void push(Stack *s, char c) {
    if (s->top == MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        exit(EXIT_FAILURE);
    } else {
        s->items[++(s->top)] = c;
    }
}

char pop(Stack *s) {
    if (is_empty(s)) {
        printf("Stack Underflow\n");
        exit(EXIT_FAILURE);
    } else {
        return s->items[(s->top)--];
    }
}

bool is_empty(Stack *s) {
    return s->top == -1;
}

bool is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

int precedence(char c) {
    if (c == '*' || c == '/' || c == '%') {
        return 2;
    } else if (c == '+' || c == '-') {
        return 1;
    } else {
        return 0;
    }
}

void infix_to_postfix(char *infix, char *postfix) {
    Stack stack;
    stack.top = -1;
    int i = 0, j = 0;

    while (infix[i] != '\0') {
        char current = infix[i];

        if (isalnum(current)) {
            postfix[j++] = current;
        } else if (current == '(') {
            push(&stack, current);
        } else if (current == ')') {
            while (!is_empty(&stack) && stack.items[stack.top] != '(') {
                postfix[j++] = pop(&stack);
            }
            pop(&stack);
        } else if (is_operator(current)) {
            while (!is_empty(&stack) && precedence(stack.items[stack.top]) >= precedence(current)) {
                postfix[j++] = pop(&stack);
            }
            push(&stack, current);
        }

        i++;
    }

    while (!is_empty(&stack)) {
        postfix[j++] = pop(&stack);
    }

    postfix[j] = '\0';
}
