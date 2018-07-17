#include <PT6523.h>

PT6523 lcd;

char full[9] = "########";
char alphabet[27] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char number[11] = "0123456789";

void setup() { 
  lcd.begin(10, 130); 
}

void loop() {
  lcd.reset();
  lcd.speed(50);
  lcd.text("SYMBOLS");
  boolean sts = true;
  lcd.symbol(CD_ICON, sts);
  lcd.symbol(MUTE, sts);
  lcd.symbol(MUSIC, sts);
  lcd.symbol(FOLDER_ICON, sts);
  lcd.symbol(AUDIO_FILE_ICON, sts);
  lcd.symbol(PERSON_ICON, sts);
  lcd.symbol(BOOK_ICON, sts);
  lcd.symbol(EQ_BORDER, sts);
  lcd.symbol(EQ, sts);
  lcd.symbol(CLAS, sts);
  lcd.symbol(FLAT, sts);
  lcd.symbol(POP, sts);
  lcd.symbol(ROCK, sts);
  lcd.symbol(BLUETOOTH, sts);
  lcd.symbol(TP, sts);
  lcd.symbol(TA, sts);
  lcd.symbol(AF, sts);
  lcd.symbol(PTY, sts);
  lcd.symbol(EON, sts);
  lcd.symbol(RDM, sts);
  lcd.symbol(INT, sts);
  lcd.symbol(RPT, sts);
  lcd.symbol(LOUD, sts);
  lcd.symbol(MP3, sts);
  lcd.symbol(DISC, sts);
  lcd.symbol(TRACK, sts);

  lcd.volumeChart(8, 1);
  lcd.volumeChart(9, 1);
  lcd.volumeChart(10, 1);
  lcd.volumeChart(11, 1);
  lcd.volumeLevel(7);
  delay(2500);

  lcd.clear();
  lcd.speed(100);
  for (int i = 0; lcd.textLoopCount() < 1; i++) {
    lcd.sChart(1);
    lcd.sText(alphabet);
  }

  lcd.clear();
  lcd.speed(150);
  for (int i = 0; lcd.textLoopCount() < 1; i++) {
    lcd.sChart(1);
    lcd.sText(number);
  }

  lcd.reset();
  lcd.clear();
  lcd.speed(100);
  lcd.levelDirection(OUT);
  int r = 0;
  for (int i = 0; lcd.textLoopCount() < 2; i++) {
    r = random(0, 7);
    lcd.volumeLevel(r);
    lcd.sText("VOLUME LEVEL OUT RIGHT");
  }

  lcd.reset();
  lcd.clear();
  lcd.speed(100);
  lcd.levelDirection(IN);
  for (int i = 0; lcd.textLoopCount() < 2; i++) {
    r = random(0, 7);
    lcd.volumeLevel(r);
    lcd.sText("VOLUME LEVEL IN RIGHT");
  }
}
