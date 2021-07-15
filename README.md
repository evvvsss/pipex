🥰🥰🥰
Что такое char **envp в int main:

 envp == environment pointer
 Содержит переменные среды/информацию об ОС
 env — нуль-терминальный массив указателей на строки переменных окружения. Каждая строка в формате ИМЯ=ЗНАЧЕНИЕ
 
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv, char **envp)
{
	int i = 0;
 	 char * home, * host;

	while (envp[i] != NULL)
		printf("%s\n", envp[i++]);
 	home = getenv("HOME");
 	host = getenv("LOGNAME");
	printf("\nВаш домашний каталог %s на %s. \n", home, host);
}
вот и из этой программы мы получим все, что хранится в envp
![image](https://user-images.githubusercontent.com/83909594/125801209-c3c677c8-ddd6-483c-aa4a-95b8ccbcafa7.png)

