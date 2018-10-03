/* +--------------------------------------------+ */
/* |  AVR VFD 16x1 Library (Driver MSC1937-01)  | */
/* |              test_scrolling.c              | */
/* | (c)copyright nitram147 [Martin Ersek] 2018 | */
/* +--------------------------------------------+ */

/* Test for vfd scrolling function */
#include <stdio.h>
#include <stdint.h>

#define VFD_DISPLAY_CHAR_LENGTH 16

void vfd_putc(char tmp_char){
	printf("%c", tmp_char);
}

void vfd_clear(){
	printf("\n");
}

void vfd_wait_scroll(){
	return;
}

void vfd_goto(uint8_t tmp_position){
	vfd_clear();
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

int main(){

	vfd_move_text_left_to_right("Scrolltest");
	printf("--------------------------------------\n");
	vfd_move_text_left_to_right("");
	printf("--------------------------------------\n");
	vfd_move_text_left_to_right("ab!");
	printf("--------------------------------------\n");
	vfd_move_text_left_to_right("0123456789ABCDEF");
	printf("--------------------------------------\n");
	vfd_move_text_left_to_right("aaaaawwwdsadadsadasdsanfdsfdsf");
	printf("--------------------------------------\n");
	vfd_move_text_left_to_right("Some very long sentence, really long, foo bar bar foo !!!");
	printf("--------------------------------------\n");

	return 0;
}