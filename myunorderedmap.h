#ifndef MYUNORDEREDMAP_H
#define MYUNORDEREDMAP_H

#include <unordered_map>

struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

template <typename Key>
using HashType = typename std::conditional<std::is_enum<Key>::value, EnumClassHash, std::hash<Key>>::type;

template <typename Key, typename T>
using MyUnorderedMap = std::unordered_map<Key, T, HashType<Key>>;


#endif // MYUNORDEREDMAP_H
