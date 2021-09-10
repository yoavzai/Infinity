#ifndef _ILRD_OL734_SERIALIZER_HPP_
#define _ILRD_OL734_SERIALIZER_HPP_

#include <memory>
#include <iostream>
#include <vector>
#include <map>
#include <boost/core/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <algorithm>
#include <typeinfo>

#include "factory.hpp"

// user must have a function that take an instance of a class and make
// map<string, string> of it.
// map<std::string, std::string>& ToMap(T&);

namespace ilrd
{

typedef std::map<std::string, std::string> data_map;

template <typename T>
class Serializer : private boost::noncopyable
{
    typedef boost::shared_ptr<T> (*Creator)(data_map);

public:
    Serializer(std::iostream& ios_);
    ~Serializer();

    template <typename D>
    void AddType(Creator creator_);  

    void Serialize(std::vector<T*>& instances_);

    //throws: type_not_found, bad_alloc
    std::vector<boost::shared_ptr<T> > Deserialize(); 

private:

    Factory< boost::shared_ptr<T>, std::string, data_map > m_types;
    //std::map<std::string, Creator> m_types;
    std::iostream m_ios;
};

template <typename T>
Serializer<T>::Serializer(std::iostream& ios_)
    : m_ios(ios_)
{}

template <typename T>
Serializer<T>::~Serializer()
{}

template <typename T>
template <typename D>
void Serializer<T>::AddType(Creator creator_)
{
    m_types.Add(typeid(D).name(), creator_);
}  

template <typename T>
void Serializer<T>::Serialize(std::vector<T*>& instances_)
{

    for(std::vector<T*>::iterator vec_iter = instances_.begin(),
                                vec_iter != instances_.end(), ++vec_iter)
    {
        data_map cur_map = (*iter)->ToMap();

        for(data_map::iterator map_iter = cur_map.begin(), map_iter != cur_map.end(), ++map_iter)
        {
            m_ios << map_iter->first << std::endl << map_iter->second << std::endl;
        }
    }
}

}
#endif // _ILRD_OL734_SERIALIZER_HPP_
