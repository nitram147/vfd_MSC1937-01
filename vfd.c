/* +--------------------------------------------+ */
/* |  AVR VFD 16x1 Library (Driver MSC1937-01)  | */
/* |                   vfd.c                    | */
/* | (c)copyright nitram147 [Martin Ersek] 2018 | */
/* +--------------------------------------------+ */
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "spi.h"
#include "vfd.h"
			
static void power_on_reset(){
	VFD_POWERONRESET_PORT &= ~(1<<VFD_POWERONRESET_BIT);
	_delay_us(200);
	VFD_POWERONRESET_PORT |= (1<<VFD_POWERONRESET_BIT);
	_delay_us(1);
}

void vfd_init(){
	VFD_POWERONRESET_DDR |= (1<<VFD_POWERONRESET_BIT);
	InitSPI();
	_delay_ms(100);
	power_on_reset();
	_delay_ms(1);	
}

void vfd_change_brightness(uint8_t tmp_brightness){
	if(tmp_brightness > VFD_MAX_BRIGHTNESS) return;
	WriteByteSPI(VFD_CHANGE_BRIGHTNESS | tmp_brightness);
	_delay_ms(1);
}

void vfd_zero_to_max_brightness(){
	for(uint8_t i=0; i<VFD_MAX_BRIGHTNESS+1; ++i){
		vfd_change_brightness(i);
		vfd_wait_brightness();
	}
}

void vfd_max_to_zero(){
	for(uint8_t i=VFD_MAX_BRIGHTNESS; i; --i){
		vfd_change_brightness(i);
		vfd_wait_brightness();
	}	
}

void vfd_putc(char tmp_char){
	WriteByteSPI(VFD_PUTCHAR & tmp_char);
	_delay_us(41);	
}

void vfd_puts(const char *tmp_string){
	register char tmp_char;
	while((tmp_char = *tmp_string++)){
		if(tmp_char >= 'a' && tmp_char <= 'z') tmp_char -= ('a' - 'A');
		vfd_putc(tmp_char);
	}
}

void vfd_goto(uint8_t tmp_position){
	if(!tmp_position || tmp_position > VFD_DISPLAY_CHAR_LENGTH) return;

	if(tmp_position == 1) tmp_position = 15;
	else tmp_position -= 2;

	WriteByteSPI(VFD_GOTO | pozicia);
	_delay_us(41);
}

void vfd_clear(){
	for(uint8_t i=VFD_DISPLAY_CHAR_LENGTH; i; --i){
		vfd_putc(' ');
		vfd_goto(1);
	}
}

static size_t strlen(const char *tmp_string){
	size_t tmp_size = 0;
	while(*tmp_string++) ++tmp_size;
	return tmp_size;
}

void vfd_move_text_left_to_right(char *tmp_string){
	if(!(*tmp_string)) return;
	
	const size_t tmp_string_length = strlen(tmp_string);

	vfd_clear();
	vfd_wait_scroll();

	for(uint8_t tmp_prefix_count = VFD_DISPLAY_CHAR_LENGTH - 1; tmp_prefix_count; --tmp_prefix_count){

		vfd_goto(1);

		for(uint8_t i=tmp_prefix_count; i; --i) vfd_putc(' ');

		uint8_t tmp_size = (VFD_DISPLAY_CHAR_LENGTH - tmp_prefix_count);
		if(tmp_string_length < tmp_size) tmp_size = tmp_string_length;

		for(uint8_t i=0; i<tmp_size; ++i) vfd_putc(tmp_string[i]);

		if((tmp_size + tmp_prefix_count) < VFD_DISPLAY_CHAR_LENGTH){
			for(uint8_t i=(VFD_DISPLAY_CHAR_LENGTH - tmp_prefix_count - tmp_size); i; --i) vfd_putc(' ');
		}
		vfd_wait_scroll();
	}

	uint8_t tmp_size = tmp_string_length;
	for(uint8_t i=0; i<tmp_string_length; ++i){
		
		vfd_goto(1);

		char *tmp_string_addr = tmp_string+i;

		for(uint8_t j=0; (j<VFD_DISPLAY_CHAR_LENGTH && (*tmp_string_addr)); (++j && ++tmp_string_addr)){
			vfd_putc(*tmp_string_addr);
		}

		if(VFD_DISPLAY_CHAR_LENGTH > tmp_size){
			for(uint8_t i=(VFD_DISPLAY_CHAR_LENGTH - tmp_size); i; --i) vfd_putc(' ');
		}

		--tmp_size;
		vfd_wait_scroll();
	}

	vfd_clear();
}
