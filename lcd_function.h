/*
  ******************************************************************************
  * @file    lcd_function.h
  * @author  sh_seok
  * @version V1.0
  * @date    2017.07.26
  ******************************************************************************
*/

#define LCD_RS_SET	GPIOA->BSRR = GPIO_PIN_8
#define LCD_RS_RESET	GPIOA->BRR = GPIO_PIN_8

#define LCD_E_SET       GPIOB->BSRR = GPIO_PIN_1;
#define LCD_E_RESET     GPIOB->BRR = GPIO_PIN_1;

#define LCD_RS      	GPIO_PIN_8
#define LCD_E       	GPIO_PIN_1
#define LCD_DB4     	GPIO_PIN_0
#define LCD_DB5     	GPIO_PIN_1
#define LCD_DB6     	GPIO_PIN_3
#define LCD_DB7     	GPIO_PIN_4

#define LCD_CMD         0	//RS = 0(Instruction code)
#define LCD_DAT         1	//RS = 1(Data code)

#define LCD_INIT8B	0x03
#define LCD_INIT4B	0x02

#define LCD_CLEAR       0x01
#define LCD_HOME        0x02
#define LCD_ENTSET      0x06
#define LCD_DISP_OFF    0x08

#define LCD_DISP_NCUR   0x0c
#define LCD_DISP_CUR    0x0f
#define LCD_DISP_BNK    0x0d
#define LCD_DISP_ALL    0x0f
#define LCD_FCSET4B	0x28

void LCD_init(void);
void LCD_DB_SetBits(uint8_t data_4bits);
void lcd_putc(uint8_t data, uint8_t rs);
void lcd_xy(uint8_t x, uint8_t y);
void lcd_clear();
void lcd_puts(uint8_t *str);
void lcd_dataout(uint32_t data);
void lcd_write_cgram(uint8_t addr, uint8_t *data);

