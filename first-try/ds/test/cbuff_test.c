#include <stdio.h> /* printf */
#include <sys/types.h> /* ssize_t */

#include "cbuff.h"
#include "test_functions.h"



int main()
{
    char arr[20];    
    
    char ch = 'a';
    char ch_read[1];

    short sh = 22;
    short sh_read[1];

    int num = -345;
    int num_read[1];

    size_t big = 123456789;
    size_t big_read[1];

    cbuff_t* my_cbuff = CBuffCreate(16);

    VerifySizeT(CBuffCapacity(my_cbuff), 16, "Create");
    VerifySizeT(CBuffFreeSpace(my_cbuff), 16, "Create");
    VerifyInt(CBuffIsEmpty(my_cbuff), 1, "Create");
    VerifyPointerNot(my_cbuff, NULL, "Create");

    VerifySizeT(CBuffWrite(my_cbuff, &ch, 1), 1, "Write");
    VerifySizeT(CBuffCapacity(my_cbuff), 16, "Capacity");
    VerifySizeT(CBuffFreeSpace(my_cbuff), 15, "FreeSpace");
    VerifyInt(CBuffIsEmpty(my_cbuff), 0, "IsEmpty");

    VerifySizeT(CBuffRead(my_cbuff, &ch_read, 1), 1, "Read");
    VerifySizeT(CBuffFreeSpace(my_cbuff), 16, "Read");
    VerifyInt(CBuffIsEmpty(my_cbuff), 1, "Read");
    VerifyInt(ch, ch_read[0], "Read");

    VerifySizeT(CBuffWrite(my_cbuff, &sh, 2), 2, "Write");
    VerifySizeT(CBuffWrite(my_cbuff, &num, 4), 4, "Write");
    VerifySizeT(CBuffWrite(my_cbuff, &sh, 2), 2, "Write");
    VerifySizeT(CBuffWrite(my_cbuff, &big, 8), 8, "Write");
    VerifySizeT(CBuffWrite(my_cbuff, &big, 8), 0, "Write");

    VerifySizeT(CBuffFreeSpace(my_cbuff), 0, "FreeSpace");
    VerifySizeT(CBuffRead(my_cbuff, &sh_read, 2), 2, "Read");
    VerifyInt(sh, sh_read[0], "Read");
    VerifySizeT(CBuffRead(my_cbuff, &num_read, 4), 4, "Read");
    VerifyInt(num, num_read[0], "Read");
    VerifySizeT(CBuffRead(my_cbuff, &sh_read, 2), 2, "Read");
    VerifyInt(sh, sh_read[0], "Read");
    VerifySizeT(CBuffFreeSpace(my_cbuff), 8, "FreeSpace");

    VerifySizeT(CBuffRead(my_cbuff, &big_read, 8), 8, "Read");
    VerifySizeT(big, big_read[0], "Read");

    VerifySizeT(CBuffWrite(my_cbuff, &sh, 2), 2, "Write");
    VerifySizeT(CBuffWrite(my_cbuff, &arr, 20), 14, "Write");
    VerifySizeT(CBuffRead(my_cbuff, &arr, 20), 16, "Read");
    VerifySizeT(CBuffFreeSpace(my_cbuff), 16, "FreeSpace");

    CBuffDestroy(my_cbuff);
    

    return 0;
}











