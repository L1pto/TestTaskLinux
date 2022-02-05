#include <string>

class Process1
{

private:
    std::string p_array;

public:
    //заполняем строку

    void EnterString();

    //функция проверяет соотвествие условиям - строка состоит из цифр и меньше 10
    bool check();

    void changeSymb();

    //отправляем в буфер
    void SendToBuffer(char *buffer);

    std::string RetString();
};