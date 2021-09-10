#include <stdlib.h> /* strtod, malloc, free */
#include <string.h> /* strlen */
#include <math.h> /* pow */

#include "calculate.h"
#include "stack.h"

#define ACTIVE 1

enum states {GET_NUM, GET_OP};

typedef struct calculator calculator_t;
typedef void (*func_t)(calculator_t* calc);
status_t Calculate(const char *expression, double *result);
static calculator_t* CalcCreate(const char *expression);
static void InitLUTS();
static void SyntaxError(calculator_t* calc);
static void ValidNum(calculator_t* calc);
static void OpenBracket(calculator_t* calc);
static void CloseBracket(calculator_t* calc);
static void Operation(calculator_t* calc);
static void Finish(calculator_t* calc);
static int IsHigherPriority(calculator_t* calc);
static int Priority(char ch);
static void SingleCalc(calculator_t* calc);
static void CalcDestroy(calculator_t* calc);

static func_t LUTS[2][256];

struct calculator
{
    const char* expression;
    unsigned char cur_char;
    int state;
    status_t status;
    stack_t* numbers;
    stack_t* operations;
};

status_t Calculate(const char *expression, double *result)
{
    calculator_t* calc = CalcCreate(expression);
    status_t return_status = SUCCESS;
    *result = 0;

    if (!calc)
    {
        return ALLOC_ERR;
    }

    InitLUTS();

    while (calc->status == ACTIVE)
    {
        calc->cur_char = *(calc->expression);
        LUTS[calc->state][calc->cur_char](calc);
    }

    if (calc->status == SUCCESS)
    {
        *result = *((double*)(StackPeek(calc->numbers)));
    }

    return_status = calc->status;

    CalcDestroy(calc); 

    return return_status;
}

static calculator_t* CalcCreate(const char *expression)
{
    calculator_t* new_calc = (calculator_t*)malloc(sizeof(calculator_t));

    if (!new_calc)
    {
        return NULL;
    }

    if (!(new_calc->numbers = StackCreate(strlen(expression), sizeof(double))))
    {
        free(new_calc);
        return NULL;
    }

    if (!(new_calc->operations = StackCreate(strlen(expression), sizeof(char))))
    {
        free(new_calc->numbers);
        free(new_calc);
        return NULL;
    }

    new_calc->expression = expression;
    new_calc->cur_char = 0;
    new_calc->state = GET_NUM;
    new_calc->status = ACTIVE;

    return new_calc;
}

static void InitLUTS()
{
    int i = 0;

    for (i = 0; i < 256; ++i)
    {
        LUTS[0][i] = SyntaxError;
        LUTS[1][i] = SyntaxError;
    }

    for (i = 0; i < 10 ; ++i)
    {
        LUTS[0][i + '0'] = ValidNum; 
    }

    LUTS[0]['.'] = ValidNum;
    LUTS[0]['+'] = ValidNum;
    LUTS[0]['-'] = ValidNum;
    LUTS[0]['('] = OpenBracket;
    LUTS[1][')'] = CloseBracket;
    LUTS[1]['+'] = Operation;
    LUTS[1]['-'] = Operation;
    LUTS[1]['*'] = Operation;
    LUTS[1]['/'] = Operation;
    LUTS[1]['^'] = Operation;
    LUTS[1]['\0'] = Finish;
}

static void SyntaxError(calculator_t* calc)
{
    calc->status = INVAL_INPUT;
}

static void ValidNum(calculator_t* calc)
{
    double cur_num = 0;
    char* end = NULL;

    cur_num = strtod(calc->expression, &end);

    if (calc->expression == end)
    {
        SyntaxError(calc);
        return;
    }

    calc->expression = end;
    calc->state = GET_OP;
    StackPush(calc->numbers, &cur_num);
}

static void OpenBracket(calculator_t* calc)
{
    StackPush(calc->operations, &(calc->cur_char));
    ++(calc->expression);
}

static void CloseBracket(calculator_t* calc)
{
    while (!StackIsEmpty(calc->operations) &&
            *(unsigned char*)StackPeek(calc->operations) != '(' &&
            calc->status == ACTIVE)
    {
        Operation(calc);
    }

    if (calc->status == MATH_ERR)
    {
        return;
    }
    
    if (StackIsEmpty(calc->operations))
    {
        calc->status = INVAL_INPUT;
        return;
    }

    StackPop(calc->operations);
    ++(calc->expression);
}

static void Operation(calculator_t* calc)
{
    while (!IsHigherPriority(calc))
    {
        SingleCalc(calc);   
    }

    if (calc->cur_char == ')' || calc->cur_char == '\0')
    {
        return;
    }

    StackPush(calc->operations, &(calc->cur_char));
    calc->state = GET_NUM;
    ++(calc->expression);
}

static void Finish(calculator_t* calc)
{
    while (!StackIsEmpty(calc->operations) &&
            *(unsigned char*)StackPeek(calc->operations) != '(' &&
            calc->status == ACTIVE)
    {
        Operation(calc);        
    }

    if (calc->status == MATH_ERR)
    {
        return;
    }

    if (StackIsEmpty(calc->operations))
    {
        calc->status = SUCCESS;
        return;
    }

    calc->status = INVAL_INPUT;
}

/* returns 1 if cur operator has higher priority than last one and 0 if not */
static int IsHigherPriority(calculator_t* calc)
{
    char* last_op = (char*)StackPeek(calc->operations);

    if (!last_op)
    {
        return 1;
    }

    return Priority(calc->cur_char) > Priority(*last_op);
}

static int Priority(char ch)
{
    int priority = 0;

    switch (ch)
    {
        case '(':
            priority = 0;
            break;

        case ')':
            priority = 1;
            break;
        
        case '\0':
            priority = 1;
            break;

        case '+':
            priority = 2;
            break;

        case '-':
            priority = 2;
            break;

        case '/':
            priority = 3;
            break;

        case '*':
            priority = 3;
            break;

        case '^':
            priority = 4;
            break;
    }

    return priority;
}

static void SingleCalc(calculator_t* calc)
{
    double result = 0;
    double num1 = 0;
    double num2 = 0;
    char op = *(char*)StackPeek(calc->operations);
    StackPop(calc->operations);
    num2 = *(double*)StackPeek(calc->numbers);
    StackPop(calc->numbers);
    num1 = *(double*)StackPeek(calc->numbers);
    StackPop(calc->numbers);

    switch (op)
    {
        case '+':
            result = num1 + num2;
            break;

        case '-':
            result = num1 - num2;
            break;

        case '*':
            result = num1 * num2;
            break;

        case '/':
        {
            if (num2 == 0)
            {
                calc->status = MATH_ERR;
                break;
            }

            result = num1 / num2;
            break;
        }

        case '^':
            result = pow(num1, num2);
            break;
    }
    
    StackPush(calc->numbers, &result);
}

static void CalcDestroy(calculator_t* calc)
{
    StackDestroy(calc->numbers);
    StackDestroy(calc->operations);
    free(calc);
}