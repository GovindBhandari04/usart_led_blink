#include <avr/io.h>
#include <util/delay.h>

void USART_intialisation()
{
	UCSRB |= (1<<TXEN)|(1<<RXEN)|(1<<RXCIE)|(1<<UCSZ2);
	UCSRC |= (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
	UCSRA |= (1<<U2X);
	UBRRL = 103;
	UBRRH = 0;
}
void USART_Txchar(char data)
{
	while(!(UCSRA & (1<<UDRE)));
	UDR = data;
	while(!(UCSRA & (1<<TXC)));
}

unsigned char USART_Rxchar()
{
	while(!(UCSRA & (1<<RXC)));
	return UDR;
}

void USART_msg(char *str)
{
	while(*str != '\0')
	{
		USART_Txchar(*str);
		str++;
	}
}

unsigned char data;
int main()
{
	USART_intialisation();
	USART_msg("Hello Govind Bhandari");
	DDRB = (1<<DDB0);
	DDRD |= (1<<DDD0)|(1<<DDD1);
	
	while(1)
	{
	data = USART_Rxchar();
	if(data == 'a')
	{
		PORTB |= (1<<PB0);	
	}
	
	if(data == 'b')
	{
		PORTB &= ~(1<<PB0);
	}
}
}