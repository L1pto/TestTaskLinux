#include <string>

class Process2
{

private:
    std::string p_array2;

public:
    //ret sum
    int ReturnSum();

    void ReceiveFromBuffer(char *buffer);

    void ClearTheBuffer(char *buffer);
};