#include <string>

class Process2
{

private:
    std::string p_array2;

public:
    //возвращает сумму строки
    int ReturnSum();

    //получаем из буфера
    void ReceiveFromBuffer(char *buffer);

    //чистим буфер
    void ClearTheBuffer(char *buffer);

    std::string RetString();
};