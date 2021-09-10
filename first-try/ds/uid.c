#include <stddef.h> /*size_t*/
#include <time.h> /*time()*/
#include <sys/types.h> /*pid_t, getpid()*/
#include <unistd.h> /*getpid()*/

#include "uid.h"

const ilrd_uid_t bad_uid = {0};

ilrd_uid_t UIDCreate(void)
{
    static size_t counter = 0;
    ilrd_uid_t new_uid = {0};
    time_t cur_time = time(NULL);
    pid_t cur_pid = getpid();
    
    if (cur_time == -1)
    {
        return bad_uid;
    }

    new_uid.counter = counter;
    new_uid.time = cur_time;
    new_uid.pid = cur_pid;
    
    counter ++;

    return new_uid;
}

int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
    return (uid1.counter == uid2.counter &&
            uid1.time == uid2.time &&
            uid1.pid == uid2.pid);
}

int UIDIsBad(ilrd_uid_t uid)
{
    return UIDIsSame(uid, bad_uid);
}