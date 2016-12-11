/* +------------------------------------------------+ */
/* |             Atmel Vfd 16x1 kniznica            | */
/* |             Atmel Vfd 16x1 library             | */
/* | (c)copyright 2015 nitram147 (www.nitram147.eu) | */
/* +------------------------------------------------+ */

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#include "spi.h"
#include "vfd.h"
			
void power_on_reset(){poweronresetport &= ~(1<<poweronresetpin);_delay_us(200);poweronresetport |= (1<<poweronresetpin);_delay_us(1);}
void writewwwnitram147eu(){
			WriteByteSPI(0x17);_delay_ms(100);
			WriteByteSPI(0x17);_delay_ms(100);
			WriteByteSPI(0x17);_delay_ms(100);
			WriteByteSPI(0x20);_delay_ms(100);
			WriteByteSPI(0x2e);_delay_ms(100);
			WriteByteSPI(0x0e);_delay_ms(100);
			WriteByteSPI(0x09);_delay_ms(100);
			WriteByteSPI(0x14);_delay_ms(100);
			WriteByteSPI(0x12);_delay_ms(100);
			WriteByteSPI(0x01);_delay_ms(100);
			WriteByteSPI(0x0d);_delay_ms(100);
			WriteByteSPI(0x31);_delay_ms(100);
			WriteByteSPI(0x34);_delay_ms(100);
			WriteByteSPI(0x37);_delay_ms(100);
			WriteByteSPI(0x20);_delay_ms(100);
			WriteByteSPI(0x2e);_delay_ms(100);
			WriteByteSPI(0x05);_delay_ms(100);
			WriteByteSPI(0x15);_delay_ms(100);
}

void menjas(int jas){WriteByteSPI(0b11100000 | jas);_delay_ms(1);}

void pridavajjas(){for(int i=0;i<31;i++){menjas(i);cakajpostupne();}}

void uberajjas(){for(int i=31;i>=0;i--){menjas(i);cakajpostupne();}}

void pisc(char piscc){WriteByteSPI(0b00111111 & piscc);_delay_us(41);}

void pis(const char *s){register char cecko;while ( (cecko = *s++) ) {if(cecko>96&&cecko<123){cecko -= 32;}pisc(cecko);}}

void chodna(int pozicia){if(pozicia==1){pozicia = 15;}else{pozicia-= 2;}WriteByteSPI(0b10100000 | pozicia);_delay_us(41);}

void zmazdisplej(){for(int zmaz=0;zmaz<16;zmaz++){pisc(0x20);}chodna(1);}

void posuvajtext(const char *s){register char cecko;char lol[16];int pocet;while ( (cecko = *s++) ) {if(cecko>96&&cecko<123){cecko -= 32;}pocet++;lol[pocet-1] = cecko;}cakajposun();for(int i=0;i<pocet;i++){zmazdisplej();int pocet2=pocet-i;for(int q=0;q<pocet2;q++){pisc(lol[i+q]);}cakajposun();}}

void posuvajtext2(const char *s){register char cecko;char lol[48];for(int iu=0;iu<16;iu++){lol[iu]=0x20;}int pocet;while ( (cecko = *s++) ) {if(cecko>96&&cecko<123){cecko -= 32;}pocet++;lol[pocet+15] = cecko;}cakajposun();int pocet3=16-pocet+16;for(int i=0;i<pocet3;i++){lol[16+pocet+i]=0x20;}for(int i=0;i<pocet+17;i++){zmazdisplej();int pocet2=pocet+16;for(int q=0;q<16;q++){pisc(lol[i+q]);}cakajposun();}}

void initvfd(){poweronresetddr |= (1<<poweronresetpin);InitSPI();_delay_ms(100);power_on_reset();_delay_ms(1);}

