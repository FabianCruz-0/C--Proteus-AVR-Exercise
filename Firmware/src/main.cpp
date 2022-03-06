/*
Cotroladores y Microcontroladores Programables - Jueves M4-M6.
Autor: Fabián Eduardo Cruz Amador.
N.L:9.
Creado con PlatformIO (Visual Studio Code).
*/

#include <time.h>
#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 1000000UL // Velocidad oscilador interno 1Mhz

int main(void)
{

  // DDRD = 0b00001111; <- Otra manera de definir los 4 leds.
  DDRD |= (1 << DDD0) | (1 << DDD1) | (1 << DDD2) | (1 << DDD3); // Se declaran los 4 leds (PD0-PD4).
  DDRB &= ~((1 << DDB0) | (1 << DDB1));                          // Se declaran los 2 botones PB0 y PB1 como entradas (0).

  int numero = (int)((double)rand() / ((double)RAND_MAX + 1) * 16); // Genera un numero aleatorio hasta el numero 15 (1111)

  int i = 1;
  bool vuelta = false;

  while (1)
  {
    switch (PINB)
    {

    case 0b00000000: // CASO 00
      // Todos los leds apagados
      PORTD = 0b00000000;
      numero = 0;
      break;

    case 0b00000001: // CASO 01
      // Efecto auto fantástico a una velocidad de 0.5s
      i = 1;
      vuelta = false;
      while (1)
      {
        if (PINB != 0b00000001) // Rompe el ciclo si el input cambió.
        {
          break;
        }
        if (i <= 8 && vuelta == false)
        {
          PORTD = i;
          _delay_ms(50);
          i *= 2;
          if (i > 8)
          {
            i = 4;
            vuelta = true;
          }
        }
        else
        {
          PORTD = i;
          _delay_ms(50);
          i /= 2;
          if (i == 1)
          {
            vuelta = false;
          }
        }
      }
      break;

    case 0b00000010: // CASO 10
      // Secuencia de leds libre (Secuencia aleatoria)
      if (numero == 0)
      {
        numero = (int)((double)rand() / ((double)RAND_MAX + 1) * 16); // Genera un numero aleatorio hasta el numero 15 (1111)
      }
      PORTD = numero;
      break;

    case 0b00000011: // CASO 11
      // Todos los leds encendidos
      PORTD = 0b00001111;
      break;
    }
  }
}