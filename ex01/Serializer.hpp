#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

typedef unsigned long int uintptr_t;
struct Data;

class Serializer{
    public:
        static uintptr_t serialize(Data *ptr);
        static Data *deserialize(uintptr_t raw);
};

#endif
