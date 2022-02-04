#include <iostream>
#include <mutex>
#include <thread>
#include <mutex>
#include <string>
#include <algorithm>
#include <typeinfo>
#include "cstring"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class Process1
{

private:
	std::string p_array;

public:
	//заполняем строку

	void EnterString()
	{
		std::cout<<"WARNING! Don't forget to run program №2 before writing the string!\n";
		std::cout<< "Enter string: " << '\n';
		std::cin >> p_array;
	}

	//функция проверяет соотвествие условиям - строка состоит из цифр и меньше 10
	bool check()
	{
		//проверка на длину.
		if (p_array.length() < 65)
		{
			for (int i = 0; i < p_array.length(); i++)
			{
				//является ли символ цифрой
				if (p_array[i] >= '0' && p_array[i] <= '9')
				{
					continue;
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			return false;
		}
		return true;
	}

	//сортируем и меняем четные символы на KV
	void changeSymb()
	{
		//сортировка по убыванию
		std::sort(p_array.begin(), p_array.end(), std::greater<int>());
		//инициализирую новый массив для замены четных чисел на KV
		std::string NewMyarray;
		for (int i = 0; i < p_array.length(); i++)
		{
			if ((static_cast<int>(p_array[i])) % 2 == 0)
			{
				NewMyarray.push_back('K');
				NewMyarray.push_back('V');
			}
			else
			{
				//std::cout<<p_array[i]<<" ";
				NewMyarray.push_back(p_array[i]);
			}
		}
		//возвращаю массив с изменениями
		p_array = NewMyarray;
	}

	//отправляем в буфер
	void SendToBuffer(char *buffer)
	{
		p_array.copy(buffer, p_array.length());
	}

	std::string RetString()
	{
		return p_array;
	}
};

class Process2
{

private:
	std::string p_array2;

public:
	//возвращает сумму строки
	int ReturnSum()
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

	//получаем из буфера
	void ReceiveFromBuffer(char *buffer)
	{
		p_array2.append(buffer);
	}

	//чистим буфер
	void ClearTheBuffer(char *buffer)
	{
		for (int i = 0; i < 128; i++)
			buffer[i] = 0;
	}

	std::string RetString()
	{
		return p_array2;
	}
};

class Sender
{
private:
	std::string s_msg;

public:
	void send(std::string &message)
	{

		s_msg = message;

		int sock;
		struct sockaddr_in addr;

		sock = socket(AF_INET, SOCK_DGRAM, 0);

		addr.sin_family = AF_INET;
		addr.sin_port = htons(3425);
		addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

		sendto(sock, s_msg.c_str(), sizeof(s_msg), 0, (struct sockaddr *)&addr, sizeof(addr));

		connect(sock, (struct sockaddr *)&addr, sizeof(addr));

		close(sock);
	}
};

int main()
{
	std::mutex m1;
	std::mutex m2;
	//объявляю буфер
	char Buffer[128]{};
	Process1 str;
	Process2 str2;

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

	return 0;
}