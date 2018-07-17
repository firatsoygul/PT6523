#include <PT6523.h>

PT6523 lcd;

void setup() { lcd.begin(10, 130); }

void loop()
{
    lcd.reset();
    lcd.speed(100);
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

    lcd.symbol(VOLUME_1, sts);
    lcd.symbol(VOLUME_2, sts);
    lcd.symbol(VOLUME_3, sts);
    lcd.symbol(VOLUME_4, sts);
    lcd.symbol(VOLUME_5, sts);
    lcd.symbol(VOLUME_6, sts);
    lcd.symbol(VOLUME_7, sts);

    delay(2500);
}
