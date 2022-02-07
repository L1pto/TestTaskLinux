#include <mutex>
#include <thread>
#include <iostream>
#include "Sender.h"
#include "Process2.h"
#include "Process1.h"
#include <chrono>
#include <condition_variable>

int i = 0;

int main()
{
	std::condition_variable cv;
	std::mutex m1;
	std::mutex m2;
	// declare a buf
	char buffer[128]{};
	Process1 str;
	Process2 str2;
	int sum = 0;
	int i = 0;
	do
	{
		i = 0;

		std::thread first([&m1, &m2, &str, &buffer, &cv, &i]()
						  {
							  //lock resources
							  std::unique_lock<std::mutex> lk(m2);

							  while (true)
							  {

								  //enter the string
								  str.enterString();

								  if (str.check())
								  {
									  //sorting in descending order and replacing characters by KV
									  str.changeSymb();

									  //send the data to the buffer
									  str.sendToBuffer(buffer, m1);
									  break;
								  }
								  else
								  {
									  std::cout << "The check is not passed. Try again" << std::endl;
								  }
							  }
							  //send message to conditional varible
							  i = 1;
							  lk.unlock();

							  //Unblocks all threads currently waiting for
							  cv.notify_all();
						  });
		Sender message;
		std::thread second([&m1, &m2, &str2, &buffer, &message, &sum, &cv, &i]()
						   {
							   //lock resources
							   std::unique_lock<std::mutex> lk(m2);

							   //Waiting for a message to continue the thread
							   cv.wait(lk, [&i]
									   { return i == 1; });

							   //receive data from the buf
							   str2.receiveFromBuffer(buffer, m1);

							   std::cout << "Thread got data: " << str2.retString() << '\n';

							   sum = str2.returnSum();

							   str2.clearTheBuffer(buffer);

							   std::string msg1 = std::to_string(sum);
							   sum = 0;

							   //send message to Program2
							   message.send(msg1);
							   std::cout << "Message sent\n\n"
										 << std::endl;
							   //unlock resources
							   lk.unlock();
						   });
		second.join();
		first.join();
	} while (1);

	return 0;
}