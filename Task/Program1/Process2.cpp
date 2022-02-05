#include "Process2.h"

int Process2::ReturnSum()
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
void Process2::ReceiveFromBuffer(char *buffer)
{
    p_array2.append(buffer);
}

//clear buf
void Process2::ClearTheBuffer(char *buffer)
{
    for (int i = 0; i < 128; i++)
        buffer[i] = 0;
}