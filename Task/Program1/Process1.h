#include <string>

class Process1
{

private:
    std::string p_array;

public:
    void EnterString();

    //The function checks if the string consists of digits and is less than 65
    bool check();

    //change the characters depending on the conditions
    void changeSymb();

    //send to buf
    void SendToBuffer(char *buffer);

};