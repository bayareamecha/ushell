#include "pico/assert.h"
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
#include <Keyboard.h>
#include <Wire.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_BusIO_Register.h>
#include <Arduino.h>

#include <Adafruit_GFX.h>  // Core graphics library
#include "Adafruit_ThinkInk.h"
#include <Adafruit_ImageReader_EPD.h>  // Image-reading functions
#include <microshell.h>

#define EPD_DC        10
#define EPD_CS        9
#define EPD_BUSY     -1  // Not used
#define SRAM_CS       6
#define EPD_RESET    -1  // controlled programatically
#define EPD_SPI &SPI

#define I2C_ADDRESS 0x5F
Adafruit_I2CDevice i2c_dev = Adafruit_I2CDevice(I2C_ADDRESS);
ThinkInk_290_Grayscale4_T5 display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

// non-blocking read interface
static int ush_read(struct ush_object *self, char *ch)

{
    if (Wire.requestFrom(I2C_ADDRESS, 1)) {
    if (Wire.available()) {
        *ch = Wire.read();
                    // Debug print to ensure the correct character is being read

   //     inputBuffer += *ch; // Update the input buffer for display
        return 1;
    }
  }
  
    // should be implemented as a FIFO
    if (Serial.available() > 0) {
        *ch = Serial.read();
        return 1;
    }
    
    /*
    if (Wire.available() > 0) {
        while (Wire.requestFrom(I2C_ADDRESS, 1)){
        *ch = Wire.read();

        return 1;
        }
}
    /*
    if (Wire.available() > 0) {
          Wire.requestFrom(I2C_ADDRESS, 1);  // Request 1 byte from the slave device.
        *ch = Wire.read();
        return 1;
        }
*/
            // Read from I2C if data is available



    return 0;

}




// non-blocking write interface
static int ush_write(struct ush_object *self, char ch)
{
    display.setTextColor(EPD_BLACK);
    display.setCursor(display.getCursorX(), display.getCursorY());
    display.print(ch);
    Serial.print(ch);

  //  return (Wire.write(ch) == 1);
    // should be implemented as a FIFO

        if (ch == '\n') {
        display.display(); // Update the display on newline
    }
    return 1; // Return success
   return (Serial.write(ch) == 1);
  //  return (Serial.print(ch) == 1); // Print to Serial for debugging/output
        // should be implemented as a FIFO
   // return (Keyboard.write(ch) == 1);
}

// I/O interface descriptor
static const struct ush_io_interface ush_iface = {
    .read = ush_read,
    .write = ush_write,
};

// working buffers allocations (size could be customized)
#if defined(ARDUINO_ARCH_ESP32) || defined(ARDUINO_AVR_MEGA2560) || defined(ARDUINO_ARCH_STM32)
    #define BUF_IN_SIZE    128
    #define BUF_OUT_SIZE   128
    #define PATH_MAX_SIZE  128
#else
    #define BUF_IN_SIZE    32
    #define BUF_OUT_SIZE   32
    #define PATH_MAX_SIZE  32
#endif

static char ush_in_buf[BUF_IN_SIZE];
static char ush_out_buf[BUF_OUT_SIZE];

// microshell instance handler
struct ush_object ush;

// microshell descriptor
static const struct ush_descriptor ush_desc = {
    .io = &ush_iface,                           // I/O interface pointer
    .input_buffer = ush_in_buf,                 // working input buffer
    .input_buffer_size = sizeof(ush_in_buf),    // working input buffer size
    .output_buffer = ush_out_buf,               // working output buffer
    .output_buffer_size = sizeof(ush_out_buf),  // working output buffer size
    .path_max_length = PATH_MAX_SIZE,           // path maximum length (stack)
    .hostname = "Midnight-Labs",                      // hostname (in prompt)
};

extern void shell_commands_add(void);
extern void shell_root_mount(void);
extern void shell_dev_mount(void);
extern void shell_bin_mount(void);

void shell_init(void)
{
    // initialize I/O interface
    Serial.begin(115200UL);
    Wire.begin();

    display.begin(THINKINK_GRAYSCALE4);
    display.clearBuffer();
    display.display();

//    Keyboard.begin();

    // Initialize the EPD display
    display.begin(THINKINK_GRAYSCALE4);
    display.clearBuffer();
    display.display(); // Show a blank screen initially

    // initialize microshell instance
    ush_init(&ush, &ush_desc);

    // add commands
    shell_commands_add();

    // mount nodes (root must be first)
    shell_root_mount();
    shell_dev_mount();
    shell_bin_mount();
}

void displayCommandLine(char ch) {
    display.clearBuffer();
    display.setTextSize(1.5);
    display.setTextColor(EPD_BLACK);
    display.print(ch);
    display.display();
}


void shell_service(void)
{/*
    if (updateDisplay) {
        displayCommandLine(); // Display the updated command line
        updateDisplay = false; // Reset the flag
    }
    */
    ush_service(&ush);
}