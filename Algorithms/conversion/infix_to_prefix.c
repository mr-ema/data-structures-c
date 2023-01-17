#include <stdio.h>
#include <string.h>

#include "acutest.h"

#define N 100

char stack[N];
int top = -1;

void push(char value)
{
        top++;
        stack[top] = value;
}

void pop()
{
        if (top <= -1) {
                return;
        }

        top--;
}

int is_empty()
{
        return (top == -1);
}

int precedence(char operator)
{
        if (operator == '^')
                return 3;
        if (operator == '*' || operator == '/')
                return 2;
        if (operator == '+' || operator == '-')
                return 1;

        return 0;
}

int is_operator(char ch)
{
        return (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '(' || ch == ')');
}

int compare_presedence(char op_1, char op_2)
{
       return (precedence(op_1) > precedence(op_2));
}

int is_parentesis(char ch)
{
        return (ch == '(' || ch == ')');
}

void watch(int i, int j, char *expression)
{
        printf("\n\e[0;36mSTEP: %22s[%d]\n", "", i);
        printf("\e[0;32mTOP: %23s[%d]\n", "", top);
        printf("STACK[TOP]: %16s\e[1m[%c]\n", "", stack[top]);
        printf("\e[0;33mCURRENT_EXPRESSION_CHAR: %3s\e[1m[%c]\n\e[0m", "", expression[i]);

        printf("\e[0;33mPOSTFIX: %19s", "");
        for (int k = 0; k < j; k++) {
                printf("\e[1m[%c]", expression[k]);
        }
        printf("\n\e[0m\n");
}

void reverse_expression(char *expression)
{
        int len = strlen(expression);

        char temp[len];
        int j = 0;

        for (int i = len - 1; i >= 0; i--) { 
                if (!expression[i]) {
                        continue;
                }
                if (expression[i] == '(') {
                        temp[j++] = ')';
                        continue;
                }
                if (expression[i] == ')') {
                        temp[j++] = '(';
                        continue;
                }
                
                temp[j++] = expression[i];
        }

        temp[j] = '\0';

        strcpy(expression, temp);
}

void infix_to_postfix(char *expression, int len)
{
        int j = 0;

        for (int i = 0; expression[i] != '\0'; i++) {
                // remove comment to watch stack
                // watch(i, j, expression);
                if (stack[top] == ')') {
                        while (stack[top] != '(' && !is_empty()) {
                                pop();
                                if (stack[top] == '(') {
                                        pop(); // get rid off parentesis
                                        break;
                                }
                                expression[j++] = stack[top];
                        }
                }

                if (!is_operator(expression[i])) {
                                expression[j++] = expression[i];
                                continue;
                }

                if (compare_presedence(expression[i], stack[top]) || is_parentesis(expression[i])) {
                        push(expression[i]);
                } else {
                        while (precedence(expression[i]) <= precedence(stack[top]) && !is_empty()) {
                                // Special case when converting to prefix
                                if (expression[i] != '^' && precedence(expression[i]) == precedence(stack[top])) {
                                        break;
                                }
                                expression[j++] = stack[top];
                                pop();
                        }
                        push(expression[i]);
                }
        }
        // clean stack
        while (!is_empty()) {
                expression[j++] = stack[top];
                pop();
        }
        expression[j] = '\0';
}

void infix_to_prefix(char *expression, int len)
{
        reverse_expression(expression);
        // printf("1. reverse %s\n", expression);

        infix_to_postfix(expression, len);
        // printf("2. postfix %s\n", expression);

        reverse_expression(expression);
        // printf("3. reverse %s\n", expression);
}

/****************************************************** 
 *                       TESTS                        *
 ******************************************************/

void test_stack_size()
{
        TEST_CHECK(N >= 20);
        TEST_MSG("EXPECTED N TO BE AT LEAST 20 BUT GOT %d", N);
}

void test_infix_to_postfix()
{
        char t1[] = "x^y/(5*z)+2";
        infix_to_postfix(t1, sizeof(t1) - 1);

        TEST_CHECK(strcmp(t1,"xy^5z*/2+") == 0);
        TEST_MSG("EXPECTED xy^5z*/2+ GOT %s", t1);

        /* --------------- CASE_2 ---------------------- */
        char t2[] = "k+l-m*n+(o^p)*w/u/v*t+q";  
        infix_to_postfix(t2, sizeof(t2) - 1);

        TEST_CHECK(strcmp(t2,"klmn*op^wuvt*//*q++-+") == 0);
        TEST_MSG("EXPECTED klmn*op^wuvt*//*q++-+ GOT %s", t2);
}

void test_infix_to_prefix()
{
        char t1[] = "x^y/(5*z)+2";
        infix_to_prefix(t1, sizeof(t1) - 1);

        TEST_CHECK(strcmp(t1,"+/^xy*5z2") == 0);
        TEST_MSG("EXPECTED +/^xy*5z2 GOT %s", t1);

        /* --------------- CASE_2 ---------------------- */
        char t2[] = "k+l-m*n+(o^p)*w/u/v*t+q";  
        infix_to_prefix(t2, sizeof(t2) - 1);

        TEST_CHECK(strcmp(t2,"++-+kl*mn*//*^opwuvtq") == 0);
        TEST_MSG("EXPECTED ++-+kl*mn*//*^opwuvtq GOT %s", t2);
}

TEST_LIST = {
        { "STACK SIZE", test_stack_size },

        { "INFIX TO POSTFIX", test_infix_to_postfix },
        { "INFIX TO PREFIX", test_infix_to_prefix },

        { NULL, NULL }
};
