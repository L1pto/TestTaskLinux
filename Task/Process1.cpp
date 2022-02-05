#include "Process1.h"
#include <iostream>
#include <algorithm>

void Process1::EnterString()
{
    std::cout << "WARNING! Don't forget to run program №2 before writing the string!\n";
    std::cout << "Enter string: " << '\n';
    std::cin >> p_array;
}

//функция проверяет соотвествие условиям - строка состоит из цифр и меньше 10
bool Process1::check()
{
    //проверка на длину.
    if (p_array.length() < 65)
    {
        for (int i = 0; i < p_array.length(); i++)
        {
            //является ли символ цифрой
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

//сортируем и меняем четные символы на KV
void Process1::changeSymb()
{
    //сортировка по убыванию
    std::sort(p_array.begin(), p_array.end(), std::greater<int>());
    //инициализирую новый массив для замены четных чисел на KV
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
            //std::cout<<p_array[i]<<" ";
            NewMyarray.push_back(p_array[i]);
        }
    }
    //возвращаю массив с изменениями
    p_array = NewMyarray;
}

//отправляем в буфер
void Process1::SendToBuffer(char *buffer)
{
    p_array.copy(buffer, p_array.length());
}

std::string Process1::RetString()
{
    return p_array;
}