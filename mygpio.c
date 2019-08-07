#include "mygpio.h"

int pinMode(int pinNum, int mode);
int error_handle(char *msg);
int set_dir(int pinNum, int mode);
int digitalWrite(int pinNum, int value);
int digitalRead(int pinNum);

/*int main(void)
{
	int input;

	pinMode(18, IN);
	pinMode(23, OUT);
	
	while(1)
	{
		input = digitalRead(18);
		if(input == 1)
			digitalWrite(23, HIGH);
		else
			digitalWrite(23, LOW);
	}
}
*/
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

int digitalRead(int pinNum)
{
	FILE *fd;
	char buf[BUFSIZE];
	char inputData[2];
	int result = 0;
	int check = 0;
	
	sprintf(buf, GPIO_DIR"/gpio%d/value", pinNum);
	//printf("%s\n",buf);
	
	if(fd = fopen(buf, "r"))
	{
		check = fread(inputData, 1, 2, fd);
		if (check)
			result = atoi(inputData);
			//printf("Read data len: %i\n", check);
		else
		{
			if(ferror(fd))
				error_handle("reading file error in digitalRead() method");
			else if(feof(fd))
				error_handle("EOF error in digitalRead() method");
		}
	}
	else
		error_handle("fopen() error in digitalRead() mehtod");
	fclose(fd);
	
	return result;
}
	
	