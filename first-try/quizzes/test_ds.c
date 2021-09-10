#include <stdio.h>   /* printf */
#include <stdlib.h>  /* malloc */

typedef struct
{
    int *arr;
    size_t *last_updated;
    size_t size;
    size_t cur_rev;
    int set_to;
}mu_t;

void InitArray(mu_t* array, size_t num_of_elements);
void SetVal(mu_t* array, int index, int val);
int GetVal(mu_t* array, int index);
void SetAll(mu_t* array, int val);

void Shift(char* arr, size_t size, size_t shift);
void Mirror(char *arr, size_t size);
void Swap(char *ch1, char *ch2);

int Action (int num1, int num2, char action);
int RecMult (int num1, int num2);
int recDiv(int num1, int num2);

unsigned int RecAddOne (unsigned int num);

/******************************************************************************/

int main()
{
    mu_t *arr = malloc(sizeof(mu_t));
    size_t i = 0;

    return 0;

}

/******************************************************************************/

void InitArray(mu_t* array, size_t num_of_elements)
{
    array->arr = (int*) calloc (num_of_elements, sizeof(int));
    array->last_updated = (size_t*) calloc (num_of_elements, sizeof(size_t));

    array->size = num_of_elements;
    array->cur_rev = 0;
    array->set_to = 0;
}

void SetVal(mu_t* array, int index, int val) /* index based 0 */
{
    if (array->size < index)
    {
        printf("index exceed size of array \n");
        return;
    }

    array->arr[index] = val;
    array->last_updated[index] = array->cur_rev + 1;
}

int GetVal(mu_t* array, int index)
{
    if (array->size < index)
    {
        printf("index exceed size of array \n");
        return 0;
    }

    return array->last_updated[index] > array->cur_rev ?
        array->arr[index] :
        array->set_to;
}

void SetAll(mu_t* array, int val)
{
    array->set_to = val;
    array->cur_rev++;
}

unsigned int RecAddOne (unsigned int num)
{
    if (num == -1)
    {
        return 0;
    }

    if ((num & 1) == 0)
    {
        return (num | 1);
    }

    return (RecAddOne(num >> 1) << 1);
}

void Shift(char* arr, size_t size, size_t shift)
{
    size_t size1 = shift % size;
    size_t size2 = size - size1;

    Mirror(arr, size);
    Mirror(arr, size1);
    Mirror(arr + size1, size2);
}

void Mirror(char *arr, size_t size)
{
    char *end = arr + size -1;
    while(arr < end)
    {
        Swap(arr, end);
        arr++;
        end--;
    }
}

void Swap(char *ch1, char *ch2)
{
    char tmp = *ch1;
    *ch1 = *ch2;
    *ch2 = tmp;
}

int Action (int num1, int num2, char action)
{
    int result = 0;
    int sign = 1;

    if (num1 < 0)
    {
        sign *= -1;
        num1 *= -1;
    }

    if (num2 < 0)
    {
        sign *= -1;
        num2 *= -1;
    }

    if (action == '*')
    {
        result = RecMult(num1, num2);
    }

    else 
    {
        if (num2 == 0)
        {
            return 0;
        }

        result = recDiv(num1, num2);
    }

    return result * sign;
}

int RecMult (int num1, int num2)
{
    if (num2 == 0)
    {
        return 0;
    }

    return num1 + RecMult(num1, num2 - 1);
}

int recDiv(int num1, int num2)
{
    if (num1 < num2)
    {
        return 0;
    }

    return 1 + recDiv(num1 - num2, num2);
}

