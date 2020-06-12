# 16f877a-dijitalsaat
PIC16F877A ile RTC kullanmadan, PIC16F877A timer0 modülü ile 16*2 LCD ekranda sistem enerjilendiğinde butonlar ile saat ve zaman dilimi ayarı yaparak CCS C programı aracılığıyla kodladığım dijital saat uygulaması.

Sistemde 16F877A mikrodenetleyicisi ve 16*2 LCD ekran ve 4Mhz Kristal kullanılmıştır.

Sistem enerjilendiğinde mikrodenetleyicinin A ve C portlarında bulunan saat ve zaman dilimi ayarı butonları ile saatimizi ayarlıyoruz. 
C2 portunda bulunan onay tuşuna bastığımızda ise  sistem çalışmaya başlayarak LCD ekran üzerinde saat bilgisini gösteriyor.

Real Time Clock kullanmadan PIC16F877A mikrodenetleyicisinin Timer0 modülünü  4 milisaniyede bir kesme verecek şekilde ayarladık. Bu sayede  her 250 kesme de 1 saniye geçeceği için kesme fonksiyonu içerisine her 250 kesmede bir saniye değişkeninin 1 artırmasını yazdık. Main fonksiyonu içerisinde yer alan döngüde ise B portu üzerine bağlanmış LCD ekran üzerine saat ve zaman dilimini anlık olarak basmasını yazdık. 

Proteus programı ile yaptığım simulasyon uygulamasını indirerek sistemi deneyebilirsiniz.
