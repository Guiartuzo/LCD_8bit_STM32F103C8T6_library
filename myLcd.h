#ifndef MYLCD_H
#define MYLCD_H

void LcdInitGpio8Bits(void);							//inicializa as GPIO's utilizadas para controle do display LCD
void LcdInitGpio4Bits(void);							//Inicializa as GPIO's para uso 4 bits
void LcdBegin8bit2lines(void);						//Inicializa o LCD em modo 8 bits com 2 linhas, caract 5x7
void LcdBegin4bits1lines(void);						//Inicializa o LCD em modo de 4 bits com 1 linhas, caract 5x7
void LcdWriteString(char string[]);				//Escreve uma string no LCD
void LcdSendCommand(unsigned char com);		//Envia comandos ao LCD
void LcdSendData(unsigned char data);			//Envia dados ao LCD
void LcdClearHome(void);									//Limpa o LCD, e cursor home
void LcdEntryModeIncrement(void);					//LCD entry mode, incrementando caracteres
void SystickDelayMs(int n);								//Delay systick

void LcdWriteString4Bits(char data);
void LcdWriteNibble(char data);

#endif