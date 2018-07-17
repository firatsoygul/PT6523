# Arduino library for PT6523

Arduino için PT6523 lcd sürücü kütüphanesi.

> Bu kütüphaneyi, KAMOSONIC marka eski bir araba kasetçalarının ön panelinde bulunan ekranı kullanarak oluşturdum. Büyük ihtimalle benim çalıştığım panelin aynısına sahip olmayacaksınız. Sizin sahibi olduğunuz lcd paneli, tamamen kendine özel alanlar içerebilir. Aynı bendeki panelde olduğu gibi. Ancak PT6523 entegresi ile birebir uyumlu olduğundan, segment ve sembol datalarını kendi kartınıza göre düzenleyerek, bu sürücü ile tasarlanmış diğer lcd paneller için de kullanılabilirsiniz.



## KURULUM

- Arduino taslak klasörünüzde bulunan `libraries/` klasörünün altında `PT6523` adında yeni bir klasör oluşturun(libraries klasörü henüz mevcut değilse siz oluşturun).
- Kütüphane dosyaları içinde bulunan `src/` ve `example/` klasörlerini, yeni oluşturduğunuz `PT6523/` klasörüne yerleştirin.

Arduino taslak klasörü, işletim sisteminize bağlı olarak aşağıdaki konumlarda bulunur(eğer değiştirmediyseniz).

- Linux için: `/home/<username>/Arduino/` veya `/home/<username>/sketchbook/`
- Windows için: `C:\Users\<username>\My Documents\arduino\`
- Mac için: `/Users/<username>/Documents/Arduino/`

Ayrıca Arduino IDE menüsünden `Dosya > Tercihler` penceresini açtığınızda, "Taslak Defteri Konumu" alanından da öğrenebilir-değiştirebilirsiniz.

Dosyaları yerleştirdikten sonra, açık olan bütün Arduino IDE'leri kapatın. Tekrar açtığınızda, IDE otomatik olarak kütüphanelerinizi tekrar tarayacak ve yeni eklediğiniz kütüphaneyi de listesine ekleyecektir. Bunu kontrol etmek için, Arduino IDE'nizi açın ve `Dosya > Örnekler` menüsü altında `PT6523` satırını arayın. Bu satır üzerine geldiğinizde, kullanıma hazır bazı örnekler göreceksiniz.

## BAĞLANTI

Bu kütüphane SPI bağlantısı için standart Arduino SPI kütüphanesini kullanır. Bu nedenle;

- Data girişini Arduino 11 nolu pine (veya ICSP soketi üzerindeki 4 nolu MOSI pinine),
- CLK'yı ise Arduino 13 nolu pine (veya ICSP soketi üzerindeki 3 nolu SCK pinine),
- FCE (ChipEnabled, SlaveSelect) girişini Arduino 10 nolu pine bağlamak gerekiyor.
- INH girişini ise +5v. akımla beslemelisiniz.

Bu pinler Arduino Uno modeli için geçerli. Diğer Arduino modelleri için [bu sayfadaki tabloya](https://www.arduino.cc/en/Reference/SPI) bakabilirsiniz. FCE (ChipEnabled, SlaveSelect) girişini ise bütün modellerde Arduino 10 nolu pine bağlıyoruz. Veya `begin(<SlaveSelect pin>, <adres>)` fonksiyonundaki parametreyi başka bir pine ayarlayabilirsiniz. Bağlantı şeması görseldeki gibi olmalıdır.

![Baglanti](https://raw.githubusercontent.com/firatsyg/PT6523/master/img/baglanti.jpg?raw=true)

## KULLANIMI

Kütüphaneyi kendi projenizde kullanabilmek için, Arduino IDE menüsünde `Taslak > library ekle > PT6523` yolunu takip edebilirsiniz. Veya kendiniz `.ino` dosyanızın en üstüne aşağıdaki kodu ekleyin.

```C++
#include <PT6523.h>
```

Kütüphaneyi bu şekilde çalışmaya dahil ettikten sonra, kütüphanedeki `PT6523` sınıfından yeni bir nesne üretmeniz gerekiyor.

```C++
PT6523 lcd;
```

Artık oluşturduğunuz bu yeni `lcd` nesnesi ile, aşağıdaki fonksiyonları kullanabilirsiniz.

### void begin(int chipEnabledPin, int address)

Bu fonksiyon lcd'yi başlatır. Chip enable `(slaveSelect)` pin  numarasının ve sürücünün SPI adresinin parametre olarak girilmesi gerekiyor. Ayrıca `SPISettings()` ve `SPI.begin()` gibi standart Arduino SPI fonksiyonlarını içerir ve chip enable pinini `OUT` durumuna getirir. Bu işlemlerin ekrana yazdırma yapılmadan önce başlatılması gerektiği için, Arduino `setup()` fonksiyonu içinde tanımlanması gerekiyor.

```C++
void setup()
{
  lcd.begin(10, 130);
}
```

### void text(char text[])

Girilen metni sabit biçimde ekrana yazdırır. Yazdırılacak metin `char` türünde bir dizi değişkeni olarak girilebilir  veya doğrudan `""` karakterleri arasında yazılarak parametre olarak girilmelidir. Ekran aynı anda 8 karakteri gösterebildiği için, girilen metnin ilk 8 karakteri ekranda görünür.

> Kütüphane yalnızca [ASCII karakter tablosundaki](https://www.arduino.cc/en/Reference/ASCIIchart) 32 - 127 arası karakterleri destekler. Bunun dışındaki karakterler ekranda iki karakterlik boşluk olarak görünür.

```C++
void loop()
{
  char a[14]="MERHABA DUNYA";
  lcd.text(a);

  //veya

  lcd.text("MERHABA DUNYA");
}
```

### void sText(char text[])

Girilen metni ekran üzerinde sağdan sola doğru kaydırarak yazdırır. Yazdırılacak metin `char` tipinde bir dizi değişkeni olarak girilebilir  veya doğrudan `""` karakterleri arasında yazılarak parametre olarak girilmelidir. Bu yazım şeklinde ekranda gösterilen metnin bir karakter sayı sınırı bulunmaz.

> Kütüphane yalnızca [ASCII karakter tablosundaki](https://www.arduino.cc/en/Reference/ASCIIchart) 32 - 127 arası karakterleri destekler. Bunun dışındaki karakterler ekranda iki karakterlik boşluk olarak görünür.

```C++
void loop()
{
  char a[44]="ARDUINO PT6523 KUTUPHANESI. 01 TEMMUZ 2018";
  lcd.sText(a);

  //veya

  lcd.sText("ARDUINO PT6523 KUTUPHANESI. 01 TEMMUZ 2018");
}
```

> Metni taşıyan `char` dizisi tanımlanırken, dizisinin eleman sayısı metnin karakter sayısından 1 fazla olmalıdır. Eğer 12 harfli bir metin giriyorsanız, diziyi 13 elemanlı oluşturmalısınız. Böylece dizinin son elemanına `/0` karakteri otomatik olarak yerleştirilir. Aksi halde, sonlandırma elemanı olmayan bir dizi ekrana yazdırılırken, kendisinden sonra tanımlanmış ya da bellekte kendisinden sonraki adreslerde bulunan alakasız veriler de ekrana yazdırılır.

Bazı durumlarda, `char`, `int` gibi farklı veri tiplerinden oluşan birden fazla veriyi, aynı anda ekrana yazdırmanız gerekebilir. Böylesi durumlarda, `C++` fonksiyonlarından [sprintf()](http://www.cplusplus.com/reference/cstdio/sprintf/)'i kullanabilirsiniz. Aşağıdaki örnekte, bir `int` değişkenin değeri ile bazı `char` karakterler birleştirilerek, lcd nesnesinin `sText()` fonksiyonuna parametre olarak giriliyor.

```C++
void loop()
{
  int a = 4;
  int b = 8;
  char buffer[14];
  sprintf (buffer, "%d ARTI %d = %d", a, b, a+b);
  lcd.sText(buffer);
}
```

`Sprintf()` fonksiyonu `int` veri tipini desteklerken, `float` tipindeki değişkenleri desteklemiyor. Bu durumu aşmak için `dtostrf()` fonksiyonunu kullanabilirsiniz. Aşağıda, bir `float` değişkenin değeri, `dtostrf()` fonksiyonu ile başka bir `char` dizisine aktarılıyor. Bir sonraki adımda ise `sprintf()` fonksiyonunda başka bir `char` dizisiyle birleştiriliyor. Ve son olarak `sText()` fonksiyonu ile ekrana yazdırılıyor.

```C++
void loop()
{
  char ss[2];
  char scr[2];
  int val = 0;
  float volt;

  val = analogRead(0);
  volt = val * 0.00468;
  dtostrf(volt, 4, 2, ss);
  sprintf(scr, "%s V", ss);
  lcd.text(scr);
}
```

> Yukarıdaki örnek kodu içeren .ino dosyası: [`PT6523/examples/Voltage_Level/Voltage_Level.ino`](examples/Voltage_Level/Voltage_Level.ino)

### int textLoopCount()

`sText()` fonksiyonu ile soldan sağa kaydırılarak ekrana yazdırılan metnin, ekranda kaç defa döndüğü bilgisini `int` tipinde dışa  döndürür. Bir metnin görünürlüğünü, ekranda belirli sayıda tekrarladıktan sonra sonlandırmak istiyorsanız, bu fonksiyondan dönen değere göre işlem yapabilirsiniz. Aşağıdaki örnekte, girilen metin 3 defa ekranda döndükten sonra döngüden çıkılır ve bir sonraki
işleme geçilir.

```C++
void loop()
{
  for (int i = 0; lcd.textLoopCount() < 3; i++)
   {
    lcd.sText("BU METIN EKRANDA 3 DEFA DONECEK.);
   }
}
```

> Yukarıdaki örnek kodu içeren .ino dosyası: [`PT6523/examples/Text/Text.ino`](examples/Text/Text.ino)

### void symbol(enum Symbol symbolName, boolean status)

Bu fonksiyon ile ekran üzerinde bulunan sembolleri gösterebilir ve gizleyebilirsiniz. Lcd panel üzerindeki tüm sembollere karşılık gelen birer `enum` sabiti tanımlanmıştır. `Symbol` isimli bu `enum` sabitlerinden birini ve içereceği durumu (*`true` veya `1` = göster,  `false` veya `0` = gizle*) bu fonksiyona parametre olarak girerek, ilgili sembolün görünürlüğünü değiştirebilirsiniz.

```C++
void loop()
{
  // Sembol durum bilgisi true girilerek semboller gösteriliyor.
  boolean sts = true;
  lcd.symbol(MUSIC, sts);
  lcd.symbol(MUTE, sts);
  lcd.symbol(BLUETOOTH, sts);
  delay(1500);
  
  // Sembol durum bilgisi 0 girilerek semboller gizleniyor.
  byte bsts = 0;
  lcd.symbol(MUSIC, bsts);
  lcd.symbol(MUTE, bsts);
  lcd.symbol(BLUETOOTH, bsts);
}
```

> Yukarıdaki örnek kodu içeren .ino dosyası: [`PT6523/examples/Symbols/Symbols.ino`](examples/Symbols/Symbols.ino)

Tüm sembol sabitleri aşağıda verilmiştir.

```C++
  INT,
  MUTE,
  BLUETOOTH,
  TRACK,
  DISC,
  RDM,
  RPT,
  MP3,
  FOLDER_ICON,
  MUSIC,
  AUDIO_FILE_ICON,
  BOOK_ICON,
  LOUD,
  PERSON_ICON,
  CD_ICON,
  PTY,
  AF,
  DOT,
  EON,
  TA,
  TP,
  EQ,
  POP,
  FLAT,
  EQ_BORDER,
  ROCK,
  CLAS,
  CHART_DOT,
  CHART_1,
  CHART_2,
  CHART_3,
  VOLUME_1,
  VOLUME_2,
  VOLUME_3,
  VOLUME_4,
  VOLUME_5,
  VOLUME_6,
  VOLUME_7
```

### void volumeChart(int volumeChartNo, boolean status)

'Volume seviyesi' ve 'chart' gösterimi gibi, sıralı ve birbiri ile bağlantılı bazı sembollerin kontrolü için kullanılır. `symbol()` fonksiyonuyla da müdahale edilebilen `VOLUME_*` ve `CHART_*` sembollerinin durumu, bu fonksiyon ile sıralı `int` değerler girilerek değiştirilebilir. Böylece bu sembolleri bir döngü içinde sıralı işlemlerde kullanabilirsiniz.

```C++
void loop()
{
  // VOLUME_1 sembolünü göster.
  lcd.volumeChart(1, true);

  // VOLUME_2 sembolünü göster.
  lcd.volumeChart(2, true);

  // CHART_1 sembolünü göster.
  lcd.volumeChart(9, true);

  // VOLUME_2 sembolünü gizle.
  lcd.volumeChart(2, false);
}
```

Volume ve chart sembollerinin fonksiyon içindeki sıralaması aşağıda verilmiştir.

```C++
    1: // VOLUME_1
    2: // VOLUME_2
    3: // VOLUME_3
    4: // VOLUME_4
    5: // VOLUME_5
    6: // VOLUME_6
    7: // VOLUME_7

    8: // CHART_DOT
    9: // CHART_1
   10: // CHART_2
   11: // CHART_3
```

### void volumeLevel(int levelValue)

Volume seviyesini istenen konuma getirir. Toplamda 7 basamaklı volume sembolünü ayarlayabilirsiniz. Bu seviye sembollerini döngüye girmeden bir seferde istenilen seviyeye getirmek için bu fonksiyonu kullanabilirsiniz. Örneğin seviyeyi 5. düzeye getirmek için `volumeLevel(3)` komutunu kullanmak yeterli.

```C++
void loop()
{
  lcd.volumeLevel(3);
  lcd.volumeLevel(7);
}
```

Seviye basamakları toplam 7 farklı segmentten oluşuyor. Varsayılan olarak en düşük seviye `0`, en yüksek seviye ise `7` kabul edilmiştir. Ancak bu değerleri `volumeStartValue()`, ve `volumeEndValue()` fonksiyonları ile düzenleyebilirsiniz.

### void volumeStartValue(int startValue), void volumeEndValue(int endValue)

Seviye aralığı olarak 7 birimin yetmediği durumlarda, bu fonksiyonlar ile başlangıç ve bitiş değerleri ayarlanabilir. Örneğin aşağıdaki örnekte, Arduino `A0` nolu analog pinine uygulanan voltajın (max. 5 v.) yaklaşık değeri, seviye simgeleri üzerinde gösterilmiştir. Arduino analog girişten gelen voltaj değerini 0 - 1023 arası bir değere çevirmektedir. Ancak bu değer standart seviye sınırı olan yediyi aştığı için, yedinin üzerindeki her veri seviyeyi en sona taşır. Bu durumu düzeltmek için, alt ve üst seviye sınırlarını bu iki fonksiyonla bildirebilirsiniz.

Program boyunca bu ayarı değiştirme ihtiyacı duyulmuyorsa, `setup()` fonksiyonu içinde tanımlayınız.

```C++
void setup()
{
  lcd.begin(10, 130);
  lcd.volumeStartValue(0);
  lcd.volumeEndValue(1023);
  int val = 0;
}

void loop()
{
  val = analogRead(0);

  lcd.volumeLevel(val);
}
```

![image_3]()

> Yukarıdaki örnek kodu içeren .ino dosyası: [`PT6523/examples/Voltage_Level/Voltage_Level.ino`](examples/Voltage_Level/Voltage_Level.ino)

### void levelDirection(direction d)

Seviye animasyonunun hareket yönünü ayarlamanızı sağlar. Fonksiyona girelebileceğiniz toplam iki yön bulunuyor.

```C++
IN
OUT
```

Animasyonun, volume arttıkça içe doğru çoğalması için, fonksiyonu aşağıdaki gibi kullanın.

```C++
void loop()
{
  levelDirection(IN);
}
```

`setup()` fonksiyonu içinde, başlangıçta bir defa tanımlamanız yeterli olacaktır. Öntanımlı değer olarak `OUT` ayarlıdır.

### void sChart(boolean chartValue)

Chart sembollerinin, dönme animasyonu için kullanılır. Fonksiyona `true` veya `1` değeri girildiği sürece, chart sembolleri üzerinde dönüş animasyonu oluşturur.

```C++
void loop()
{
  for (int j = 0; j <= 8; j++)
    {
        lcd.sChart(1);
    }
}
```

> Yukarıdaki örnek kodu içeren .ino dosyası: [`PT6523/examples/Symbols/Smbols.ino`](examples/Symbols/Symbols.ino)

### void speed(int textSpeed)

Ekrandaki animasyonların (metin kaydırma, seviye geçişleri, chart animasyonu vb.) hızını belirlemek için kullanılır. Uygulamanın herhangi bir noktasında kullanılabilir. `int` tipindeki parametre milisaniye cinsinden olmalıdır. Belirtilen süre animasyonun geçiş hızını belirler. Dolayısıyla süre ne kadar az ise, animasyonlar o kadar hızlı gösterilir. Hiç bir değer belirtilmemişse, varsayılan değer 300 milisaniye olarak uygulanır.

### void clear()

Ekranda o anda yazılı olan karakterleri siler. Metinler arası geçişlerde kullanıldığında, metinlerin iç içe geçme riskini engeller. Her yeni metni ekrana yazdırmadan önce kullanmanız gerekiyor.

### void reset()

`clear()` fonksiyonuna ek olarak, `textLoopCount()` ile tutulan metin döngü sayısını, ekrandaki tüm sembolleri, sol ve sağ seviye bilgilerini sıfırlar. Animasyon hızını başlangıç değeri olan 300 milisaniyeye ayarlar. Ekran güç tasarrufu (power saving) modunda ise açılacaktır. Ancak `volumeStartValue()` ve `volumeEndValue()` ile belirlenen seviye aralıklarını **değiştirmez**.

### void noDisplay()

Sürücü güç tasarrufu (power saving) moduna geçer. Sürücü içindeki osilatör duracağı ve segment hatlarındaki voltaj Vss değerine çekileceği için, ekran lcd bölümü kapanır. Ekranın batarya ile çalıştırılacağı durumlarda, belirli bir süre sonunda bu moda geçilebilir.

### void display()

Güç tasarrufu (power saving) modunda bulunan sürücüyü normal çalışma moduna geçirir.

![Image_1](https://raw.githubusercontent.com/firatsyg/PT6523/master/img/IMG_0101.JPG?raw=true)

![Sample_2](https://raw.githubusercontent.com/firatsyg/PT6523/master/img/IMG_0103.JPG?raw=true)
