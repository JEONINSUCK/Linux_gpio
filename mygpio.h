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
int digitalRead(int pinNum);
