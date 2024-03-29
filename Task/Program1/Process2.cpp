#include "Process2.h"

int Process2::returnSum()
{
    int sum = 0;
    for (int i = 0; i < p_array2.length(); i++)
    {
        if ((p_array2[i] <= '9') && (p_array2[i] >= '0'))
        {
            sum = sum + (p_array2[i] - '0');
        }
    }
    return sum;
}

//receive from buf
void Process2::receiveFromBuffer(char *buffer, std::mutex &m)
{
    m.lock();
    p_array2.append(buffer);
    m.unlock();
}

//clear buf
void Process2::clearTheBuffer(char *buffer)
{
    for (int i = 0; i < 128; i++)
    {
        buffer[i] = 0;
    }
    p_array2.clear();
}

std::string Process2::retString()
{
    return p_array2;
}