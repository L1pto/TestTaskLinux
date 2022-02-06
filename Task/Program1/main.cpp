#include <mutex>
#include <thread>
#include <iostream>
#include "Sender.h"
#include "Process2.h"
#include "Process1.h"

int main()
{
	std::mutex m1;
	std::mutex m2;
	// declare a buf
	char buffer[128]{};
	Process1 str;
	Process2 str2;
	do{
	//1 thread
	std::thread first([&str, &buffer, &m1, &m2]()
					  {
						  //lock resources
						  m1.lock();
						  m2.lock();

						  while (true)
						  {
							  //enter the string
							  str.enterString();

							  if (str.check())
							  {
								  //sorting in descending order and replacing characters by KV
								  str.changeSymb();

								  //send the data to the buffer
								  str.sendToBuffer(buffer);
								  break;
							  }
							  else
							  {
								  std::cout << "The check is not passed. Try again" << std::endl;
							  }
						  }

						  //unlock resources
						  m1.unlock();
						  m2.unlock();
					  });

	int sum = 0;
	std::thread second([&str2, &buffer, &m1, &m2, &sum]()
					   {
						   //lock resources
						   m1.lock();
						   m2.lock();

						   //receive data from the buf
						   str2.receiveFromBuffer(buffer);

						   //clear buf
						   str2.clearTheBuffer(buffer);

						   //return sum of string
						   sum = str2.returnSum();

						   //unlock resources
						   m1.unlock();
						   m2.unlock();
					   });
	first.join();
	second.join();

	Sender message;

	std::cout<<"Message sent\n";
	//send a message using a socket
	std::string msg1 = std::to_string(sum);
	message.send(msg1);
	}while(1);
	return 0;
}