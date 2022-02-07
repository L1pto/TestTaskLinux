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
		//1 thread
		std::thread first([&m1, &m2, &str, &buffer, &cv, &i]()
						  {
							  //lock resources
							  std::unique_lock<std::mutex> lk(m2);
							  std::cout << "thread 1 " << std::this_thread::get_id() << '\n';
							  
							  cv.notify_all();
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
							  i = 1;
							  lk.unlock();
							  cv.notify_all();
							  //m2.unlock();
						  });
		//b
		Sender message;
		std::thread second([&m1, &m2, &str2, &buffer, &message, &sum, &cv, &i]()
						   {
							   //std::lock_guard<std::mutex> lg1(m1);
							   std::cout << "thread 2 " << std::this_thread::get_id() << '\n';
							   //lock resources
							   std::unique_lock<std::mutex> lk(m2);
							   //m2.lock();
							   cv.wait(lk, [&i]{ return i == 1; });
							   cv.notify_all();
							   //receive data from the buf
							   str2.receiveFromBuffer(buffer, m1);

							   std::cout << "Thread got data: " << str2.retString() << '\n';

							   //return sum of string
							   //str2.;
							   //clear buf

							   //std::cout <<sum <<" Sum"<< '\n';
							   sum = str2.returnSum();

							   str2.clearTheBuffer(buffer);

							   std::string msg1 = std::to_string(sum);
							   std::cout << sum << " Sum" << '\n';
							   sum = 0;
							   message.send(msg1);
							   //std::cout << "Message sent\n";
							   //unlock resources
							   //m1.unlock();
							   m2.unlock();
						   });
		second.join();
		first.join();
	} while (1);

	return 0;
}