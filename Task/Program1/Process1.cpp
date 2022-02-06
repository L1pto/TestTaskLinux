#include "Process1.h"
#include <iostream>
#include <algorithm>

void Process1::enterString()
{
    std::cout << "WARNING! Don't forget to run program №2 before writing the string!\n";
    std::cout << "Enter string: " << '\n';
    std::cin >> p_array;
}

//The function checks if the string consists of digits and is less than 65
bool Process1::check()
{
    //length check
    if (p_array.length() < 65)
    {
        for (int i = 0; i < p_array.length(); i++)
        {
            //character test
            if (p_array[i] >= '0' && p_array[i] <= '9')
            {
                continue;
            }
            else
            {
                return false;
            }
        }
    }
    else
    {
        return false;
    }
    return true;
}

//sort and change the even characters to KV
void Process1::changeSymb()
{
    //descend sort
    std::sort(p_array.begin(), p_array.end(), std::greater<int>());
    //initialize a new array for the numbers after replacement
    std::string NewMyarray;
    for (int i = 0; i < p_array.length(); i++)
    {
        if ((static_cast<int>(p_array[i])) % 2 == 0)
        {
            NewMyarray.push_back('K');
            NewMyarray.push_back('V');
        }
        else
        {
            NewMyarray.push_back(p_array[i]);
        }
    }
    //return the array with the changes
    p_array = NewMyarray;
}

void Process1::sendToBuffer(char *buffer)
{
    p_array.copy(buffer, p_array.length());
}
