#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <time.h>

void show_num(int n)
{
  //PD1 = DP = 2
  //PD2 = B == 4(0100)
  //PD3 = C == 8(1000)
  //PD4 = D == 16()
  //PD5 = E  == 32
  //PD6 = A == 64
  //PD7 = F == 128
  //PB0 = G == 1
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
  case 10:
    //G
    PORTB |= 1;
    break;
  default:
    break;
  }
}

void clear()
{
  PORTD = 0;
  PORTB &= (~1); //3? // 254? 0B11111110
}

void print_digits(int num1, int num2, int num3, int num4)
{
  int dig_delay = 1;
  int loop_delay = 6;
  //DIG1
  PORTB = 0B00111000;
  show_num(num1);
  _delay_ms(dig_delay);
  clear();

  //DIG2
  PORTB = 0B00110100;
  PORTD |= 2;
  show_num(num2);
  _delay_ms(dig_delay);
  clear();

  //DIG3
  PORTB = 0B00101100;
  show_num(num3);
  _delay_ms(dig_delay);
  clear();

  //DIG4
  PORTB = 0B00011100;
  show_num(num4);
  _delay_ms(dig_delay);
  clear();

  _delay_ms(loop_delay);
}

void intro_loop()
{
  int r = 3 + (rand() % 7);
  int counter = 0;
  while (1)
  {
    // '-'
    print_digits(10, 10, 10, 10);
    counter++;
    if (counter > 100 * r)
      break;
  }
}

void counter_loop(int *digits)
{
  int button = 0;
  int buttonWasReleased = 0;

  while (1)
  {

    button = PINB;

    if (button & 1 << PB1)
    {
      if (buttonWasReleased == 1)
      {
        buttonWasReleased = 0;
        break;
      }
    }
    else
    {
      buttonWasReleased = 1;
      digits[3]++;
      if (digits[3] > 9)
      {
        digits[3] = 0;
        digits[2]++;
        if (digits[2] > 9)
        {
          digits[2] = 0;
          digits[1]++;
          if (digits[1] > 9)
          {
            digits[1] = 0;
            digits[0]++;
            if (digits[0] > 5)
            {
              digits[0] = 0;
            }
          }
        }
      }
    }

    print_digits(digits[0], digits[1], digits[2], digits[3]);
  }
}

void show_result_loop(int *digits)
{
  int counter = 0;
  while (1)
  {
    print_digits(digits[0], digits[1], digits[2], digits[3]);
    counter++;
    if (counter > 300)
      break;
  }
}

int main()
{
  //init
  DDRB = 0B00111101; //13.12.11.10 = out, 9 in 8 G out
  DDRD = 0B11111111; //outputs
  int digits[4] = {0, 0, 0, 0};

  srand(time(NULL));

  while (1)
  {
    intro_loop();

    counter_loop(digits);

    show_result_loop(digits);

    digits[0] = 0;
    digits[1] = 0;
    digits[2] = 0;
    digits[3] = 0;
  }

  return 0;
}