/*
  PT6523 Library for Arduino.
  Created by Fırat SOYGÜL, 20 Aralık 2017
  GNU General Public License v3.0
  (https://github.com/firatsoygul/PT6523/blob/master/LICENSE)
*/

#ifndef PT6523_h
#define PT6523_h
#include "Arduino.h"

enum symbolName {
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
};

enum direction {
  IN,
  OUT
};

class PT6523 {
public:
  PT6523();
  void begin(int chipEnabledPin, int address);
  void text(char text[]);
  void sChart(boolean chartValue);
  void sText(char text[]);
  int textLoopCount();
  void symbol(enum symbolName name, boolean status);
  void volumeChart(int volumeChartNo, boolean status);
  void volumeStartValue(int startValue);
  void volumeEndValue(int endValue);
  void volumeLevel(int levelValue);
  void levelDirection(direction d);
  void speed(int textSpeed);
  void display();
  void noDisplay();
  void clear();
  void reset();

private:
  int _volumeLevel = 0;
  direction _levelDirection = OUT;
  int _loopNumber = 0;
  int _tScroll = 0;
  byte _sScroll = 0;
  int _chartScroll = 1;
  byte _container[16];
  int _containerSize = 16;
  int _n = 0;
  int _textLenght = 0;
  int _chipEnabledPin = 10;
  int _address = 130;
  int _textSpeed = 300; // Default speed
  void _textLoop();
  void _textSize(char text[]);
  void _letters(char gk[]);
  void _letters_ORJ(uint8_t gk[]);
  void _setLetters();
  void _setSymbols();
  void _print(int pAddress, byte pScreen[], byte pSymbols[]);
  int _volumeStartValue = 0;
  int _volumeEndValue = 7;
  // boolean _symbolChartDot = false;
  // boolean _symbolChart_1 = false;
  // boolean _symbolChart_2 = false;
  // boolean _symbolChart_3 = false;
  boolean _symbolChart[5];
  boolean _symbolInt = false;
  boolean _symbolMute = false;
  boolean _symbolBluetooth = false;
  boolean _symbolTrack = false;
  boolean _symbolDisc = false;
  boolean _symbolRdm = false;
  boolean _symbolRpt = false;
  boolean _symbolMp3 = false;
  boolean _symbolFolderIcon = false;
  boolean _symbolMusic = false;
  boolean _symbolAudioFileIcon = false;
  boolean _symbolBookIcon = false;
  // boolean _symbolLoud = false;
  // boolean _symbolPersonIcon = false;
  // boolean _symbolCdIcon = false;
  // boolean _symbolPty = false;
  // boolean _symbolAf = false;
  // boolean _symbolDot = false;
  // boolean _symbolEon = false;
  // boolean _symbolTa = false;
  // boolean _symbolTp = false;
  // boolean _symbolEq = false;
  // boolean _symbolPop = false;
  // boolean _symbolFlat = false;
  // boolean _symbolEqBorder = false;
  // boolean _symbolRock = false;
  // boolean _symbolClas = false;
  // boolean _symbolVolume_1 = false;
  // boolean _symbolVolume_2 = false;
  // boolean _symbolVolume_3 = false;
  // boolean _symbolVolume_4 = false;
  // boolean _symbolVolume_5 = false;
  // boolean _symbolVolume_6 = false;
  // boolean _symbolVolume_7 = false;
  byte _symbols[6];         // 5 SPI byte package for symbol data
  byte _bellekTasmasi1[10]; // Bellek taşmasına geçici çözüm.
  byte _screen[16];         // 15 SPI byte package for character data
  byte _bellekTasmasi2[10]; // Bellek taşmasına geçici çözüm. leftBased()
                            // metodundaki for dönüsünün ikinci if sorgusunda
                            // bulunan -1 lik sağa öteleme düzeltildikten sonra
                            // kaldırılabilir.
};

#endif
