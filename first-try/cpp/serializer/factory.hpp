#ifndef _ILRD_OL734_FACTORY_HPP_
#define _ILRD_OL734_FACTORY_HPP_

#include <map>

namespace ilrd
{

template <typename Obj_Handle, typename Key, typename Data, typename Create_Func = Obj_Handle(*)(Data)>
class Factory
{

public:
    void Add(Key key_, Create_Func creator_);  
    Obj_Handle Create(Key key_, Data data_) const;

private:
    std::map<Key, Create_Func> m_map;
};

} // namespace ilrd

#endif // _ILRD_OL734_FACTORY_HPP_