#include <cstdio>
#include <cstring>
#include <iostream>

#include <ctime>
#include <cstdlib>

class Base{
    public:
        virtual ~Base(void);
};

class A: public Base{

};


class B: public Base{

};


class C: public Base{

};

Base::~Base(void){}

Base *generate(void){
    int random = std::rand();
    std::cout << RAND_MAX << ": " << random << std::endl;
    if (0<=random && random<RAND_MAX/3)
        return (new (A));
    else if (RAND_MAX/3<=random && random<2*(RAND_MAX/3))
        return (new (B));
    else
        return (new (C));
    return (NULL);
}

int main(void)
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    Base *base = generate();
    A *a = dynamic_cast<A *>(base);
    B *b = dynamic_cast<B *>(base);
    C *c = dynamic_cast<C*>(base);
    if (a!=NULL)
        std::cout << "Type: A" << std::endl;
    if (b!=NULL)
        std::cout << "Type: B" << std::endl;
    if (c!=NULL)
        std::cout << "Type: C" << std::endl;

    return (0);
}

// https://cpprefjp.github.io/reference/typeinfo/bad_cast.html