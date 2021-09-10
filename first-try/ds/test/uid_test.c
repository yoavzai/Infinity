#include <stddef.h> /*size_t*/
#include <time.h> /*time()*/
#include <sys/types.h> /*pid_t, getpid()*/
#include <unistd.h> /*getpid()*/
#include <stdio.h>
#include <stdlib.h>

#include "uid.h"
#include "test_functions.h"


void smoke_test()
{
    ilrd_uid_t uid1 = UIDCreate();
    ilrd_uid_t uid2 = UIDCreate();

    VerifyInt(uid1.pid, uid2.pid, "Create");
    VerifySizeTNot(uid1.counter, uid2.counter, "Create");
    VerifyInt(UIDIsSame(uid2, uid1), 0, "IsSame");
    VerifyInt(UIDIsBad(bad_uid), 1, "IsBad");
    VerifyInt(UIDIsBad(uid1), 0, "IsBad");
    VerifyInt(UIDIsBad(uid2), 0, "IsBad");
}

void stress_test()
{
    size_t i = 0;
    size_t j = 0;
    size_t same = 0;
    size_t bad = 0;
    ilrd_uid_t* uid_list = malloc(sizeof(ilrd_uid_t) * 100000);

    for (i = 0; i < 100000; ++i)
    {
        uid_list[i] = UIDCreate();
    }

    for (i = 0; i < 99999; i++)
    {
        bad += UIDIsBad(uid_list[i]);
        for (j = i + 1; j < 100000; j++)
        {
            same += UIDIsSame(uid_list[i], uid_list[j]);
        }
    }

    VerifySizeT(same, 0, "All Unique");
    VerifySizeT(bad, 0, "All Good");
}




int main()
{
    smoke_test();
    stress_test();

    return 0;
}