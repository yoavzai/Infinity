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
#include <string>

#include "factory.hpp"
#include "shape.hpp"

// user must have a function that take an instance of a class and make
// map<string, string> of it.
// map<std::string, std::string>& ToMap(T&);

namespace ilrd
{

typedef std::map<std::string, std::string> data_map;

template <typename T>
class Serializer : private boost::noncopyable
{
    typedef T* (*Creator)(data_map);

public:
    Serializer(std::iostream& ios_);
    ~Serializer();

    template <typename D>
    void AddType(Creator creator_);  

    void Serialize(std::vector<T*>& instances_);

    //throws: type_not_found, bad_alloc
    std::vector<T*> Deserialize(); 

private:

    Factory<T*, std::string, data_map> m_types;
    //std::map<std::string, Creator> m_types;
    std::iostream& m_ios;
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
    m_ios << instances_.size() << std::endl;

    for(typename std::vector<T*>::iterator vec_iter = instances_.begin();
                                vec_iter != instances_.end(); ++vec_iter)
    {
        data_map cur_map = (*vec_iter)->ToMap();

        for(data_map::iterator map_iter = cur_map.begin(); map_iter != cur_map.end(); ++map_iter)
        {
            m_ios << map_iter->first << std::endl << map_iter->second << std::endl;
        }
    }
}

template <typename T>
std::vector<T*> Serializer<T>::Deserialize()
{
    std::vector<T*> vector;
    std::string s_size;
    std::string name;
    std::string attr;
    std::getline(m_ios, s_size);
    int size = std::stoi(s_size);

    for (int i = 0; i < size; ++i)
    {
        data_map map;
        std::getline(m_ios, name);
        std::getline(m_ios, attr);
        map[name] = attr;

        vector.push_back(m_types.Create(name, map));
    }

    return vector;
}

}
#endif // _ILRD_OL734_SERIALIZER_HPP_
