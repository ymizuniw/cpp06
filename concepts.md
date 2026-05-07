
1.static_cast<>()
    upcast/downcast between related types.
    make implicit cast to explicit for readability.
    done in compile time. 
2.dynamic_cast<>()
     upcast/downcast between related types.
     done in runtime.
     it will be NULL if the cast fails, and always needs null check.
3.reinterpret_cast<>()
    convert any types to aother type.
    it is used in limited situations like to get general pointer expr <unsinged int *>.
4.const_cast<>()
    used to drop const qualifier from const object.
    usually, using this is not recommended, but in limited cases, it helps you.
