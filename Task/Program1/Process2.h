#include <string>

class Process2
{

private:
    std::string p_array2;

public:
    
    int returnSum();

    void receiveFromBuffer(char *buffer);

    void clearTheBuffer(char *buffer);
};