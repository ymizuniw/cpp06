#include <string>
#include <sstream>
#include <iostream>
#include <cctype>

int validate_num(std::string num)
{
    // int part
    size_t i = 0;
    while(i<num.length())
    {
        if (!std::isdigit(num.at(i)))
            break;
        i++;
    }
    if (i==num.length())
        return 1;
    if (num.at(i)=='.')
        i++;
    if (i==num.length())
        return (1);
    // fractional part
    while(i<num.length())
    {
        if (!std::isdigit(num.at(i)))
            break;
        i++;
    }
    if (i==num.length())
        return (1);
    if (num.at(i)=='f')
        i++;
    else
        return (0);
    if (i==num.length())
        return (1);
    return (0);
}

int main(void)
{
    std::string num = "1f";
    int valid_num = validate_num(num);
    std::cout << valid_num << std::endl;
    // std::stringstream ss(num);
    // int inum;
    // ss >> inum;
    // ss.clear();
    // std::cout << inum << std::endl;
    // float f;
    // ss >> f;
    // ss.clear();
    // std::cout << f << std::endl;
    // double d;
    // ss >> d;
    // ss.clear();
    // std::cout << f << std::endl;
    char c = 41;
    std::cout << c << std::endl;
    std::cout << std::isprint(-1) << std::endl;

    std::stringstream ss ("-3000000000000000000");
    int res1 = 0;
    ss>>res1;
    std::cout << res1 << std::endl;
    return (0);
}
