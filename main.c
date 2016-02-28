#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <usb_keyboard.h>

// ====== GPIO =================================================================
// Teensy 2.0: LED is active high
#define LED_ON		(PORTD |= (1<<6))
#define LED_OFF		(PORTD &= ~(1<<6))

#define LED_CONFIG	(DDRD |= (1<<6))
#define CPU_PRESCALE(n)	(CLKPR = 0x80, CLKPR = (n))

// SETUP JOYSTICK
#define JOYSTICK_CONFIG (DDRF = 0x00); (PORTF = 0xFF)
// SETUP MAIN BUTTONS
#define BUTTON0_CONFIG (DDRB = 0x00); (PORTB = 0xFF)
// SETUP SYSTEM BUTTONS
#define BUTTON1_CONFIG (DDRD &= ~0x09); (PORTD |= 0x09)

#define UP (PINF & (1<<0))
#define DOWN (PINF & (1<<1))
#define LEFT (PINF & (1<<4))
#define RIGHT (PINF & (1<<5))
#define BTN1 (PINB & (1<<0))
#define BTN2 (PINB & (1<<1))
#define BTN3 (PINB & (1<<3))
#define BTN4 (PINB & (1<<4))
#define BTN5 (PINB & (1<<5))
#define BTN6 (PINB & (1<<6))
#define PONE (PIND & (1<<0))
#define COIN (PIND & (1<<3))

// ====== KEYBOARD =============================================================
void resetKeyboard(void) {
    keyboard_modifier_keys = 0;
    keyboard_keys[0] = 0;
    keyboard_keys[1] = 0;
    keyboard_keys[2] = 0;
    keyboard_keys[3] = 0;
    keyboard_keys[4] = 0;
    keyboard_keys[5] = 0;
}

// ====== MAIN LOOP ============================================================
void run(void) {
    // signal the prgm is running
    LED_ON;

    while(1) {
        resetKeyboard();
        // update keys
        if(!UP)
            usb_keyboard_press(KEY_UP, 0);
        if(!DOWN)
            usb_keyboard_press(KEY_DOWN, 0);
        if(!LEFT)
            usb_keyboard_press(KEY_LEFT, 0);
        if(!RIGHT)
            usb_keyboard_press(KEY_RIGHT, 0);
        if(!BTN1)
            usb_keyboard_press(KEY_LEFT_CTRL, 0);
        if(!BTN2)
            usb_keyboard_press(KEY_ALT, 0);
        if(!BTN3)
            usb_keyboard_press(KEY_SPACE, 0);
        if(!BTN4)
            usb_keyboard_press(KEY_LEFT_SHIFT, 0);
        if(!BTN5)
            usb_keyboard_press(KEY_Z, 0);
        if(!BTN6)
            usb_keyboard_press(KEY_X, 0);
        if(!PONE)
            usb_keyboard_press(KEY_1, 0);
        if(!COIN)
            usb_keyboard_press(KEY_5, 0);
    }
}

// ====== SETUP ================================================================
void setup(void) {
    // set for 16 MHz clock, and make sure the LED is off
	CPU_PRESCALE(0);

    LED_CONFIG;
	LED_OFF;

    JOYSTICK_CONFIG;
    BUTTON0_CONFIG;
    BUTTON1_CONFIG;

    // init usb controller
    usb_init();
    while (!usb_configured());
    // let the driver load
    _delay_ms(1000);
}

// ====== MAIN =================================================================
int main(void) {
    setup();

    run();
}
