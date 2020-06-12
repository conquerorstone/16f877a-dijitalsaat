#include <16F877A.h>
#device ADC=16

#FUSES XT,NOWDT, NOPROTECT, NOBROWNOUT, NOLVP, NOPUT, NOWRT, NODEBUG, NOCPD

#use delay(crystal=4MHz)
#define saatart   PIN_A0
#define saatazal   PIN_A1
#define dkart   PIN_A2
#define dkazal   PIN_A3
#define snart   PIN_A4
#define snazal   PIN_A5
#define oniki   PIN_C0
#define yirmidort   PIN_C1
#define onay   PIN_C2


unsigned int16 kesme;
int saat,dk,sn,dilim;

#INT_TIMER0
void  TIMER0_isr(void) // timer0 kesme fonksiyonu
{
kesme=kesme+1;
if(kesme%250==0)// her 4msn de bir kesme oluþacaðý için kesme sayýsý 250 olduðunda 1 saniye geçmiþ olacak
sn=sn+1;
if(sn>59){
dk=dk+1;
sn=0;}
if(dk>59){
saat=saat+1;
dk=0;
}
if(dilim==1 && saat>24){
saat=1;}
if(dilim==0 && saat>12){
saat=1;}
}
#define LCD_ENABLE_PIN PIN_B0
#define LCD_RS_PIN PIN_B1
#define LCD_RW_PIN PIN_B2
#define LCD_DATA4 PIN_B3
#define LCD_DATA5 PIN_B4
#define LCD_DATA6 PIN_B5
#define LCD_DATA7 PIN_B6

#include <lcd.c>
void main()
{
   setup_psp(PSP_DISABLED);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_CCP1(CCP_OFF);
   setup_CCP2(CCP_OFF);
   
   lcd_init();
   set_tris_a(0b00111111);//giriþler belirlendi
   set_tris_c(0b00000111);//giriþler belirlendi
   while(!input(onay))// onay butonuna basýlana kadar
   {
   lcd_gotoxy(1,1); 
   printf(lcd_putc,"%2i:%2i:%2i  ",saat,dk,sn); //SS:DD:SnSn ve saat dilimini yazdýr
   if(dilim==1){
   lcd_gotoxy(1,2); 
   printf(lcd_putc,"24 saat",); }
   if(dilim==0){
   lcd_gotoxy(1,2); 
   printf(lcd_putc,"12 saat",); }
   if(input(yirmidort)) //24 butonuna basýldýðýnda
   {
   dilim=1;
   }
   else if(input(oniki))//24 basýlmadýysa 12 butonuna basýldýðýnda
   {
   dilim=0;
   }
   if(input(saatart)) //saatartýrma butonu
   {
   saat=saat+1; // saati artýr
   if(dilim==0&& saat>12) // dilim 0 ise 0-12  dilim 1 ise 0-24
   saat=0;
   if(dilim==1&& saat>24)
   saat=0;
   while(input(saatart))// buton býrakýlana kadar bekle
   {}
   }
   else if(input(saatazal))// saat azaltma
   {
   saat=saat-1;
   if(dilim==0&& (saat+1)==0)
   saat=12;
   if(dilim==1&& (saat+1)==0)
   saat=24;
   
   while(input(saatazal))
   {}
   }
   if(input(dkart))
   {
   dk=dk+1;
   if(dk>=60)
   dk=0;
   while(input(dkart))
   {}
   }
   else if(input(dkazal))
   {
   dk=dk-1;
   if((dk+1)==0)
   dk=59;
   while(input(dkazal))
   {}
   }
   if(input(snart))
   {
   sn=sn+1;
   if(sn>=60)
   sn=0;
   while(input(snart))
   {}
   }
   else if(input(snazal))
   {
   sn=sn-1;
   if((sn+1)==0)
   sn=59;
   while(input(snazal))
   {}
   }
   }
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_16|RTCC_8_bit);      // timer0 ayarý 4Mhz kristal kullanýldýðýnda 4 msn de taþma yapýyor
   enable_interrupts(INT_TIMER0); // timer0 kesmesi etkin
   enable_interrupts(GLOBAL); // global kesmeler etkin
   while(TRUE)
   {
       if(input(yirmidort)) // sistem çalýþýrken saat dilimi deðiþtirme
         {
         dilim=1;
         }
       else if(input(oniki))
         {
         if(saat>12) // 24 lük dilimden 12 lik dilime geçerken saat 12 den büyükse
         saat=saat-12;
         dilim=0;
         }
      lcd_gotoxy(1,1); 
      printf(lcd_putc,"%2i:%2i:%2i",saat,dk,sn); // ekrana sürekli saati ve tercih edilen saat dilimini bastýrma 
         if(dilim==1){
         lcd_gotoxy(1,2); 
         printf(lcd_putc,"24 saat",); }
         if(dilim==0){
         lcd_gotoxy(1,2); 
         printf(lcd_putc,"12 saat",); }
   }

}
