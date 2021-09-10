#ifndef _ILRD_OL734_FACTORY_HPP_
#define _ILRD_OL734_FACTORY_HPP_

#include <map>
#include <cstdio>

namespace ilrd
{

template <typename Obj_Handle, typename Key, typename Data, typename Create_Func = Obj_Handle(*)(Data)>
class Factory
{

public:
    void Add(Key key_, Create_Func creator_);  
    Obj_Handle Create(Key key_, Data data_);

private:
    std::map<Key, Create_Func> m_map;
};

template <typename Obj_Handle, typename Key, typename Data, typename Create_Func>
void Factory<Obj_Handle, Key, Data, Create_Func>::Add(Key key_, Create_Func creator_)
{
    m_map[key_] = creator_;
}

template <typename Obj_Handle, typename Key, typename Data, typename Create_Func>
Obj_Handle Factory<Obj_Handle, Key, Data, Create_Func>::Create(Key key_, Data data_)
{
    Obj_Handle a =  m_map[key_](data_);

    return a;
}

} // namespace ilrd

#endif // _ILRD_OL734_FACTORY_HPP_