#include <string>
#include <mutex>

class Process2
{

private:
    std::string p_array2;

public:
    int returnSum();

    void receiveFromBuffer(char *buffer, std::mutex &m);

    void clearTheBuffer(char *buffer);

    std::string retString();
};