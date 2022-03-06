# TestTaskLinux

**Program №1**
Must consist of two threads and one shared buffer. 
> Stream 1. Gets the string to be entered by the user.   There should be a check that the string consists only of digits and does not exceed 64 characters. After the check, the    > string must be sorted in descending order and all elements whose value is even must be replaced by the Latin letters "KV". After that the given string is placed into the common > buffer and the thread should wait for further data entry by the user.
> Stream 2 should process the data placed in the shared buffer. After receiving the data the shared buffer is cleared. The thread should display the data and calculate the total  > sum of all items that are numeric values.  The resulting sum is sent to program 2. After that the thread waits for the next data.


**Program №2**
> Waits for data from program #1. When it receives the data, it analyzes how many characters the transferred value is. If it is greater than 2 characters and if it is a multiple of > 32, it outputs a data message, otherwise it outputs an error message. The program then continues to wait for the data.
