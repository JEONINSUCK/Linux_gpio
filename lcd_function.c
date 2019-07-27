#include "stm32l4xx_hal.h"
#include "lcd_function.h"

void LCD_init(void)
{
	LCD_RS_RESET;
	LCD_E_RESET;

	HAL_Delay(15);

	LCD_E_SET;
	LCD_DB_SetBits(LCD_INIT8B);
	LCD_E_RESET;

	HAL_Delay(5);

	LCD_E_SET;
	LCD_DB_SetBits(LCD_INIT8B);
	LCD_E_RESET;

	HAL_Delay(1);

	LCD_E_SET;
	LCD_DB_SetBits(LCD_INIT8B);
	LCD_E_RESET;
        HAL_Delay(1);

        LCD_E_SET;
	LCD_DB_SetBits(LCD_INIT4B);
	LCD_E_RESET;
        
	lcd_putc(LCD_FCSET4B, LCD_CMD);
	HAL_Delay(1);
        lcd_putc(LCD_DISP_OFF, LCD_CMD);
	HAL_Delay(1);
        lcd_putc(LCD_CLEAR, LCD_CMD);
	HAL_Delay(1);
        lcd_putc(LCD_ENTSET, LCD_CMD);
	HAL_Delay(1);
        lcd_putc(LCD_DISP_CUR, LCD_CMD);
        HAL_Delay(1);
}


void LCD_DB_SetBits(uint8_t data_4bits)
{
    HAL_GPIO_WritePin(GPIOA, LCD_DB4, (data_4bits >> 0) & 0x01);
    HAL_GPIO_WritePin(GPIOA, LCD_DB5, (data_4bits >> 1) & 0x01);
    HAL_GPIO_WritePin(GPIOA, LCD_DB6, (data_4bits >> 2) & 0x01);
    HAL_GPIO_WritePin(GPIOA, LCD_DB7, (data_4bits >> 3) & 0x01);
}

void lcd_putc(uint8_t data, uint8_t rs)
{
	uint8_t  upper_data;
	uint8_t  lower_data;

	upper_data = data >> 4;
	lower_data = data & 0x0f;

	HAL_Delay(1);

	if (rs==1) {
		LCD_RS_SET;	//Data Register
	} else {
		LCD_RS_RESET;	//Instruction Register
	}

	LCD_E_SET;
	LCD_DB_SetBits(upper_data);
	LCD_E_RESET;

	HAL_Delay(1);

	LCD_E_SET;
	LCD_DB_SetBits(lower_data);
	LCD_E_RESET;
}

void lcd_xy(uint8_t x, uint8_t y)
{
    uint8_t  adr;
    adr=(y*0x40+x) | 0x80;
    lcd_putc(adr, LCD_CMD);
}

void lcd_clear(void)
{
	lcd_putc(LCD_CLEAR, 0);
        HAL_Delay(2);
}

void lcd_puts(uint8_t *str)
{
while(*str) {
    lcd_putc(*str, LCD_DAT);
    str++;
    }
}

void lcd_dataout(uint32_t data)
{
	uint8_t temp;
	int8_t strtemp[16];
	int16_t i, k;
	i=0;
	do {
		temp = data % 10;
		strtemp[i++] = temp + '0';
	} while (( data /= 10 ) != 0);
	i--;
	for( k=i; k>=0; k-- ) {
		lcd_putc( strtemp[k], LCD_DAT);
	}
}

void lcd_write_cgram(uint8_t addr, uint8_t *data)
{
    int i;

    lcd_putc(0x40 | ((addr&7) << 3), LCD_CMD);
    for (i=0; i<8; i++)
    {
        lcd_putc(*data++, LCD_DAT);
    }
    lcd_putc(LCD_HOME, LCD_CMD);
}