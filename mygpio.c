#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 50
#define HIGH 1
#define LOW 0
#define OUT 1
#define IN 0
#define	GPIO_DIR "/sys/class/gpio"

int pinMode(int pinNum, int mode);
int error_handle(char *msg);
int set_dir(int pinNum, int mode);
int digitalWrite(int pinNum, int value);

int main(void)
{
	pinMode(23, OUT);
	while(1)
	{
		digitalWrite(23, HIGH);
		sleep(1);
		digitalWrite(23, LOW);
		sleep(1);
	}
	
	return 0;
}

int pinMode(int pinNum, int mode)
{
	FILE *fd;
	char buf[BUFSIZE] = {0,};
	int len;
	
	if(fd = fopen(GPIO_DIR"/export", "w"))
	{	
		len = sprintf(buf, "%d", pinNum);
		fwrite(buf,1, len, fd);
	}
	else
		error_handle("fopen() error in pinMode() method");
	fclose(fd);
	usleep(100000);
	set_dir(pinNum, mode);
	
	return 0;
}
	
int set_dir(int pinNum, int mode)
{
	FILE *fd;
	char buf[BUFSIZE] = {0,};
	
	sprintf(buf, GPIO_DIR"/gpio%d/direction", pinNum);
	//printf("%s\n", buf);
	if(fd = fopen(buf, "w"))
	{	
		if(mode == OUT)
			fwrite("out", 4, 1, fd);
		else
			fwrite("in", 3, 1, fd);
	}
	else
		error_handle("fopen() error in set_dir() method");
	fclose(fd);
	return 0;
}

int error_handle(char *msg)
{
	printf("%s\n",msg);
	exit(1);
}
	
int digitalWrite(int pinNum, int value)
{
	FILE *fd;
	char buf[BUFSIZE] = {0,};
	
	sprintf(buf, GPIO_DIR"/gpio%d/value", pinNum);
	//printf("%s\n",buf);
	if(fd = fopen(buf, "w"))
	{
		if(value == HIGH)
			fwrite("1", 1, 2, fd);
		else
			fwrite("0", 1, 2, fd);
	}
	else
		error_handle("fopen() error in digitalWrite() method");
	fclose(fd);
	return 0;
}
	
	
	
	