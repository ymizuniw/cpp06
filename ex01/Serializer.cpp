#include "Serializer.hpp"

#include <cstddef>

uintptr_t Serializer::serialize(Data *ptr){
    if (ptr==NULL)
        return (0);
    uintptr_t ret = reinterpret_cast<uintptr_t>(ptr);
    return (ret);
}

Data *Serializer::deserialize(uintptr_t raw){
    Data *ret = reinterpret_cast<Data *>(raw);
    return (ret);
}
