/* +--------------------------------------------+ */
/* |  AVR VFD 16x1 Library (Driver MSC1937-01)  | */
/* |                   vfd.h                    | */
/* | (c)copyright nitram147 [Martin Ersek] 2018 | */
/* +--------------------------------------------+ */
#ifndef VFD_H
#define VFD_H

#define VFD_DISPLAY_CHAR_LENGTH 16
#define VFD_WAIT_BRIGHTNESS_TIME 200
#define VFD_WAIT_SCROLL_TIME 200

#define VFD_POWERONRESET_DDR DDRD
#define VFD_POWERONRESET_PORT PORTD
#define VFD_POWERONRESET_BIT PD0

#define VFD_MAX_BRIGHTNESS 31

#define VFD_CHANGE_BRIGHTNESS 0b11100000
#define VFD_PUTCHAR 0b00111111
#define VFD_GOTO 0b10100000

#define vfd_wait_brightness() _delay_ms(VFD_WAIT_BRIGHTNESS_TIME)
#define vfd_wait_scroll() _delay_ms(VFD_WAIT_SCROLL_TIME)

//init vfd display
void vfd_init();

//change brightness, allowed range 0-31
void vfd_change_brightness(uint8_t tmp_brightness);

//adjust brightness from zero to max smoothly with VFD_WAIT_BRIGHTNESS_TIME ms step delay
void vfd_zero_to_max_brightness();

//adjust brightness from max to zero smoothly with VFD_WAIT_BRIGHTNESS_TIME ms step delay
void vfd_max_to_zero();

//write char to display
void vfd_putc(char tmp_char);

//write string to display
void vfd_puts(const char *tmp_string);

//goto position on display, indexes starting from 1 !!!, valid range 1-16
void vfd_goto(uint8_t tmp_position);

//clear display and set position to start
void vfd_clear();

//move string from left to right with space prefix and suffix
void vfd_move_text_left_to_right(char *tmp_string);

#endif
