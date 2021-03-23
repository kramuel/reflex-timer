#include <avr/io.h>
#include <util/delay.h>

void num(int n)
{
  //PD2 = B == 4(0100)
  //PD3 = C == 8(1000)
  //PD4 = D == 16()
  //PD5 = E  == 32
  //PD6 = A == 64
  //PD7 = F == 128
  //PB0 = G == 1
  //PB1 = DP = 2
  switch (n)
  {
  case 0:
    PORTD |= 252;
    break;
  case 1:
    // B & C
    PORTD |= 4 + 8;
    break;
  case 2:
    //A, B, G, E, D
    PORTD |= 64 + 4 + 32 + 16;
    PORTB |= 1;
    break;
  case 3:
    //A, B, G, C, D
    PORTD |= 64 + 4 + 8 + 16;
    PORTB |= 1;
    break;
  case 4:
    //F, B, G, C
    PORTD |= 128 + 4 + 8;
    PORTB |= 1;
    break;
  case 5:
    //A, F, G, C, D
    PORTD |= 64 + 128 + 8 + 16;
    PORTB |= 1;
    break;
  case 6:
    //F, G, E, C, D, A
    PORTD |= 128 + 32 + 8 + 16 + 64;
    PORTB |= 1;
    break;
  case 7:
    //A, B, C
    PORTD |= 64 + 4 + 8;
    break;
  case 8:
    //ABCDEFG
    PORTD |= 252;
    PORTB |= 1;
    break;
  case 9:
    //A, F, G, B, C, D
    PORTD |= 64 + 128 + 4 + 8 + 16;
    PORTB |= 1;
    break;
  default:
    break;
  }
}

void clear()
{
  PORTD = 0;
  PORTB &= (~1); //3?
}

int main()
{
  DDRB = 0B00000011; //13.12.11.10 = input, 9.8 outputs
  DDRD = 0B11111100; //7-3 outputs

  while (1)
  {
  }
  return 0;
}