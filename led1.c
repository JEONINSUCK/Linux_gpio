#include "mygpio.h"

int main(void)
{
	int data;
	
	pinMode(18, IN);
	pinMode(23, OUT);
	
	while(1)
	{
		data = digitalRead(18);
		if (data == 1)
			digitalWrite(23, HIGH);
		else
			digitalWrite(23, LOW);
	}
	return 0;
}