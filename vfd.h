/* +------------------------------------------------+ */
/* |             Atmel Vfd 16x1 kniznica            | */
/* |             Atmel Vfd 16x1 library             | */
/* | (c)copyright 2015 nitram147 (www.nitram147.eu) | */
/* +------------------------------------------------+ */

void power_on_reset(void);//potrebny pri starte / needed during start
void writewwwnitram147eu(void);//vypis wwwnitram147eu / write wwwnitram147eu
void menjas(int jas);//meni jas - rozsah hodnot 0-31 / change brightness - from 0 to 31
void pridavajjas(void);//postupne plynule pridava jas / smoothly adjusting (incrementing) brightness
void uberajjas(void);//postupne plynule ubera jas / smoothly adjusting (deincrementing) brightness
void pisc(char piscc);//vypise znak / write one char
void pis(const char *s);//vypise znaky / write multiple chars
void chodna(int pozicia);//chod na poziciu na displeji - 1 az 16 / go to position on display - range 1 - 16
void zmazdisplej(void);//zmaze displej / clear displej
void posuvajtext(const char *s);//posuva text po displeji / moving text on display
void posuvajtext2(const char *s);//posuva text po displeji / moving text on display
void initvfd(void);//inicializacia vfd / initialization of vfd

#define cakajpostupne() _delay_ms(200);//cas medzi postupnym pridavanim jasu / time between smoothly adjusting brightness
#define cakajposun() _delay_ms(200);//cas (rychlost) posuvania textu po displayi / time (speed) of moving text on display
#define poweronresetddr DDRD	//ddr portu na poweronreset pin / ddr of port on poweronreset pin
#define poweronresetport PORTD	//ddr portu na poweronreset pin / ddr of port on poweronreset pin
#define poweronresetpin PD0	//nazov pinu na poweronreset / name of pin for powerofreset

