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

PIPE
Важное отличие pip’а от файла заключается в том, что прочитанная информация немедленно удаляется из него и не может быть прочитана повторно.
Pipe можно представить себе в виде трубы ограниченной емкости, расположенной внутри адресного пространства операционной системы, доступ к входному и выходному отверстию которой осуществляется с помощью системных вызовов. В действительности pipe представляет собой область памяти, недоступную пользовательским процессам напрямую, зачастую организованную в виде кольцевого буфера (хотя существуют и другие виды организации). По буферу при операциях чтения и записи перемещаются два указателя, соответствующие входному и выходному потокам. При этом выходной указатель никогда не может перегнать входной и наоборот. Для создания нового экземпляра такого кольцевого буфера внутри операционной системы используется системный вызов pipe ().

***
◦ **access** - проверка существования файла / доступность для записи или чтения 
0	Существование файла
1	Исполняемость файла
2	Доступность для записи
3	Доступность для чтения
4	Доступность для чтения/записи
Функция access() возвращает 0, если проверяемый вид доступа разрешен; в противном случае она возвращает —1.

	**int access(const char *filename, int mode);**

◦ **open** - открывает файл с именем filename и устанавливает режим доступа к нему в соответствии со значением аргумента access.
O_RDONLY	Открыть только для чтения
O_WRONLY	Открыть только для записи
O_RDWR	Открыть для чтения/записи

	**int open(const char *filename, int access);**

◦ **unlink** -  удаляет файл с именем filename.

	**int unlink(const char *filename);**

◦ **close** - закрывает файл. В случае успеха close() возвращает 0, в противном случае —1. 

	**int close(int fd);**

◦ **read** - считывает count байт из файла, описываемого аргументом fd, в буфер buf. Функция возвращает количество действительно считанных байт. В случае ошибки возвращается —1, а 0 возвращается при попытке чтения в конце файла. 

	**int read(int fd, void *buf, unsigned count);**

◦ **write** - переписывает count байт из буфера buf в файл с fd.

	**int write(int fd, void *buf, int count);**

◦ **malloc** - возвращает адрес на первый байт области памяти размером size байт, кото­рая была выделена из кучи. Если памяти недостаточно, чтобы удовлетворить запрос, функция malloc() возвращает нулевой указатель. 

	**void *malloc(size_t size);**
	
◦ **wait** - системный вызов, который блокирует родительский процесс пока не завершится один из его потомков.

	**pid_t wait (int * EXIT_STATUS);**
	
◦ **waitpid** -  системный вызов, который задерживает родительский процесс пока не завершится один из его потомков.

	**pid_t waitpid(pid_t pid, int *status, int options);**
	
◦ **free** - возвращает память, на которую указывает параметр ptr, назад в кучу. 

	**void free(void *ptr);**
	
◦ **pipe** - системный вызов, который предназначен для создания pip'а внутри операционной системы. Заносит в массив int fd[2] два дескриптора открытых файлов. fd[0] – открыт на чтение, fd[1] – открыт на запись. Канал уничтожается, когда будут закрыты все файловые дескрипторы ссылающиеся на него.
Системный вызов возвращает значение 0 при нормальном завершении и значение -1 при возникновении ошибок.

	**int pipe(int *fd);**
	

◦ **dup** - возвращает новый дескриптор файла, который полностью описывает (т.е. дублирует) состояние файла fd. В случае успеха возвращается неотрицательная величина, а в противном случае —1.

	**int dup(int fd);**

◦ **dup2** - дублирует old_fd как new_fd. Если имеется файл, который был связан с new_fd до вызова dup2(), то он будет закрыт. В случае успеха возвращается 0, а в случае ошибки —1.

	**int dup2(int old_fd, int new_fd);**
	
◦ **execve** - системный вызов, который выполняет программу, заданную исполняемым файлом (передаем путь исполняемого файла, аргументы команды и envp). В случае ошибки возвращает -1, если все хорошо - завершается ВСЯ программа.

	**int execve (const char * PATH, const char ** ARGV, const char ** ENVP);**
	
◦ **fork** - системный вызов, который порождает (клонирует) новый процесс. Возвращает -1 в случае ошибки, 0 - если процесс дочерний и другое если родительский.

	**pid_t fork (void);**
	
◦ **perror** - помещает значение глобальной переменной errno в строку и записывает эту строку в файл stderr. Если str имеет ненулевое значение, то сначала выводится строка, а за ней следует двоеточие и сообщение об ошибке, соответствующее значению errno.

	**void perror(const char *str);**
	
◦ **strerror** - возвращает указатель на сообщение об ошибке, связанное с номером ошибки.

	**char *strerror(int num);**
	
◦ **exit** - вызывает немедленное окончание работы программы. status = 0

	**void exit (int status);**

***
