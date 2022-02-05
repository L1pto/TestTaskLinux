#include <mutex>
#include <thread>
#include <iostream>
#include "Process3.h"
#include "Process2.h"
#include "Process1.h"

int main()
{
	std::mutex m1;
	std::mutex m2;
	//объявляю буфер
	char Buffer[128]{};
	Process1 str;
	Process2 str2;
	do{
	//1 поток
	std::thread First([&str, &Buffer, &m1, &m2]()
					  {
						  //блокирование ресурсов
						  m1.lock();
						  m2.lock();

						  while (true)
						  {
							  //ввод строки
							  str.EnterString();

							  if (str.check())
							  {
								  //сортировка по убыванию и замена символов на KV
								  str.changeSymb();

								  //отправка данных в буфер
								  str.SendToBuffer(Buffer);
								  break;
							  }
							  else
							  {
								  std::cout << "The check is not passed. Try again" << std::endl;
							  }
						  }

						  //разблокировка ресурсов
						  m1.unlock();
						  m2.unlock();
					  });

	//std::cout << str.RetString() << "  1 str" << '\n';
	//2 поток

	int sum = 0;
	std::thread Second([&str2, &Buffer, &m1, &m2, &sum]()
					   {
						   //блокирование ресурсов
						   m1.lock();
						   m2.lock();

						   //получение данных из буферов
						   str2.ReceiveFromBuffer(Buffer);

						   //std::cout << "Second thred got string: " << str2.RetString() << '\n';

						   //очищение буфера
						   str2.ClearTheBuffer(Buffer);

						   //возвращает сумму
						   sum = str2.ReturnSum();

						   //разблокировка ресурсов
						   m1.unlock();
						   m2.unlock();
					   });
	First.join();
	Second.join();

	Sender message;

	std::cout<<"Message sent\n";
	//отправка сообщения через сокет
	std::string msg1 = std::to_string(sum);
	message.send(msg1);
	}while(1);
	return 0;
}