#include <iostream>
int main()
{
    std::string s1 = "abc";
    std::string s2 = "def";

    std::cout << s1 + s2 << std::endl;

    std::cout << s1.compare(s2) << std::endl;

    
    std::cout << s1.empty() <<" "<< std::endl;

    s1 = "abc";

    s1.erase(0, 2);
    std::cout << s1 << std::endl;

    s1 = "abc";
    std::cout << s1.find("b") << std::endl;

    s1.insert(2, "lol");
    std::cout << s1 << std::endl;
}