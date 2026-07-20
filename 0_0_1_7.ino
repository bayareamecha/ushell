/*
MIT License

Copyright (c) 2021 Marcin Borowicz <marcinbor85@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "shell.h"
#include <Keyboard.h>
#include <Adafruit_I2CDevice.h>
//#define I2C_ADDRESS 0x5F
//Adafruit_I2CDevice i2c_dev = Adafruit_I2CDevice(I2C_ADDRESS);

void setup()
{
    // initialize needed hardware
    pinMode(LED_BUILTIN, OUTPUT);

    // initialize shell
    shell_init();

}

/*
void kpress(){

 char c = Wire.read();  // Store the received data.
    if (c != 0) {
      printf("%c", c);
   //   Serial.println(c, HEX);
      
 switch (c) {
      // Number row
      // Number row
      case 0x1B:
        Keyboard.write(KEY_ESC);
        break;
      case 0x31:
        Keyboard.write('1');
        break;
      case 0x32:
        Keyboard.write('2');
        break;
      case 0x33:
        Keyboard.write('3');
        break;
      case 0x34:
        Keyboard.write('4');
        break;
      case 0x35:
        Keyboard.write('5');
        break;
      case 0x36:
        Keyboard.write('6');
        break;
      case 0x37:
        Keyboard.write('7');
        break;
      case 0x38:
        Keyboard.write('8');
        break;
      case 0x39:
        Keyboard.write('9');
        break;
      case 0x30:
        Keyboard.write('0');
        break;
      case 0x08:
        Keyboard.write(KEY_BACKSPACE);
        break;

      // Top row
      case 0x09:
        Keyboard.write(KEY_TAB);
        break;
      case 0x71:
        Keyboard.write('q');
        break;
      case 0x77:
        Keyboard.write('w');
        break;
      case 0x65:
        Keyboard.write('e');
        break;
      case 0x72:
        Keyboard.write('r');
        break;
      case 0x74:
        Keyboard.write('t');
        break;
      case 0x79:
        Keyboard.write('y');
        break;
      case 0x75:
        Keyboard.write('u');
        break;
      case 0x69:
        Keyboard.write('i');
        break;
      case 0x6F:
        Keyboard.write('o');
        break;
      case 0x70:
        Keyboard.write('p');
        break;

      // Home row
      case 0x61:
        Keyboard.write('a');
        break;
      case 0x73:
        Keyboard.write('s');
        break;
      case 0x64:
        Keyboard.write('d');
        break;
      case 0x66:
        Keyboard.write('f');
        break;
      case 0x67:
        Keyboard.write('g');
        break;
      case 0x68:
        Keyboard.write('h');
        break;
      case 0x6A:
        Keyboard.write('j');
        break;
      case 0x6B:
        Keyboard.write('k');
        break;
      case 0x6C:
        Keyboard.write('l');
        break;
      case 0x0D:
        Keyboard.write(KEY_RETURN);
        break;

      // Bottom row
      case 0x7A:
        Keyboard.write('z');
        break;
      case 0x78:
        Keyboard.write('x');
        break;
      case 0x63:
        Keyboard.write('c');
        break;
      case 0x76:
        Keyboard.write('v');
        break;
      case 0x62:
        Keyboard.write('b');
        break;
      case 0x6E:
        Keyboard.write('n');
        break;
      case 0x6D:
        Keyboard.write('m');
        break;
      case 0x2C:
        Keyboard.write(',');
        break;
      case 0x2E:
        Keyboard.write('.');
        break;
      case 0x20:
        Keyboard.write(' ');
        break;

      // Arrow keys
      case 0xB4:
        Keyboard.write(KEY_LEFT_ARROW);
        break;
      case 0xB5:
        Keyboard.write(KEY_UP_ARROW);
        break;
      case 0xB6:
        Keyboard.write(KEY_DOWN_ARROW);
        break;
      case 0xB7:
        Keyboard.write(KEY_RIGHT_ARROW);
        break;

      // Number row symbols
      case 0x21:
        Keyboard.write('!');
        break;
      case 0x40:
        Keyboard.write('@');
        break;
      case 0x23:
        Keyboard.write('#');
        break;
      case 0x24:
        Keyboard.write('$');
        break;
      case 0x25:
        Keyboard.write('%');
        break;
      case 0x5E:
        Keyboard.write('^');
        break;
      case 0x26:
        Keyboard.write('&');
        break;
      case 0x2A:
        Keyboard.write('*');
        break;
      case 0x28:
        Keyboard.write('(');
        break;
      case 0x29:
        Keyboard.write(')');
        break;
      case 0x7B:
        Keyboard.write('{');
        break;
      case 0x7D:
        Keyboard.write('}');
        break;

      // Top row symbols
      case 0x5B:
        Keyboard.write('[');
        break;
      case 0x5D:
        Keyboard.write(']');
        break;
      case 0x2F:
        Keyboard.write('/');
        break;
      case 0x5C:
        Keyboard.write('\\');
        break;
      case 0x7C:
        Keyboard.write('|');
        break;
      case 0x7E:
        Keyboard.write('~');
        break;
      case 0x27:
        Keyboard.write('\'');
        break;
      case 0x22:
        Keyboard.write('"');
        break;

      // Add more cases for other rows and symbols here following the pattern

      default:
        break;
                Serial.print(c);
 }
      }   

}
*/

void loop()
{
  
    // non-blocking shell service
    shell_service();

}
