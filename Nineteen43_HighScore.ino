#include "src/Utils/Arduboy2Ext.h"
#ifndef SAVE_MEMORY

uint8_t clearScores = 0;


// --------------------------------------------------------------------------------------
//  Render High Score screen ..
//
#define HIGH_SCORE_DIST_BETWEEN_ROWS 12
void renderHighScore(HighScore &highScore) {

  uint8_t xOffset = 75;
  uint8_t yOffset = 3;


  arduboy.drawVerticalDottedLine(0, HEIGHT, 127);
  SpritesB::drawOverwrite(114, 0, flying_aces_01, 0);
  SpritesB::drawOverwrite(101, 0, flying_aces_02, 0);
  arduboy.drawVerticalDottedLine(0, HEIGHT, 97);

  
  for (uint8_t x =0; x < MAX_NUMBER_OF_SCORES; x++) {

    yOffset = 4;
    Slot slot = EEPROM_Utils::getSlot(x);

    SpritesB::drawOverwrite(xOffset, yOffset, font4x6_Full, slot.getChar0());
    SpritesB::drawOverwrite(xOffset, yOffset + 6, font4x6_Full, slot.getChar1());
    SpritesB::drawOverwrite(xOffset, yOffset + 12, font4x6_Full, slot.getChar2());


    // Score ..
    {
      uint8_t digits[6] = {};
      extractDigits(digits, slot.getScore());
    
      for (uint8_t i = 0, y2 = yOffset + 52; i < 6; ++i, y2 -= 5) {
        SpritesB::drawSelfMasked(xOffset, y2, font4x6_Full, (digits[i] + 26));
      }
      
    }

    xOffset = xOffset - HIGH_SCORE_DIST_BETWEEN_ROWS;

  }

  if (highScore.getSlotNumber() != DO_NOT_EDIT_SLOT) {

    xOffset = 75;
    yOffset = 4;
    alternate++;
  
    if (alternate < 15) {

      SpritesB::drawOverwrite(xOffset - (highScore.getSlotNumber() * HIGH_SCORE_DIST_BETWEEN_ROWS) - 1, yOffset - 4, arrow, 0);
      SpritesB::drawOverwrite(xOffset - (highScore.getSlotNumber() * HIGH_SCORE_DIST_BETWEEN_ROWS) - 1, yOffset + 59, arrow, 0);
    
    }
    else if (alternate > 30) {

      alternate = 0;

    }

    if (highScore.getCharIndex() == 0) {
      arduboy.fillRect(xOffset - (highScore.getSlotNumber() * HIGH_SCORE_DIST_BETWEEN_ROWS) - 1, yOffset - 1, 8, 6, WHITE);
      SpritesB::drawErase(xOffset - (highScore.getSlotNumber() * HIGH_SCORE_DIST_BETWEEN_ROWS), yOffset, font4x6_Full, highScore.getChar(0));
    }
    else {
      SpritesB::drawOverwrite(xOffset - (highScore.getSlotNumber() * HIGH_SCORE_DIST_BETWEEN_ROWS), yOffset, font4x6_Full, highScore.getChar(0));
    }

    if (highScore.getCharIndex() == 1) {
      arduboy.fillRect(xOffset - (highScore.getSlotNumber() * HIGH_SCORE_DIST_BETWEEN_ROWS) - 1, yOffset + 5, 8, 6, WHITE);
      SpritesB::drawErase(xOffset - (highScore.getSlotNumber() * HIGH_SCORE_DIST_BETWEEN_ROWS), yOffset + 6, font4x6_Full, highScore.getChar(1));
    }
    else {
      SpritesB::drawOverwrite(xOffset - (highScore.getSlotNumber() * HIGH_SCORE_DIST_BETWEEN_ROWS), yOffset + 6, font4x6_Full, highScore.getChar(1));
    }

    if (highScore.getCharIndex() == 2) {
      arduboy.fillRect(xOffset - (highScore.getSlotNumber() * HIGH_SCORE_DIST_BETWEEN_ROWS) - 1, yOffset + 11, 8, 6, WHITE);
      SpritesB::drawErase(xOffset - (highScore.getSlotNumber() * HIGH_SCORE_DIST_BETWEEN_ROWS), yOffset + 12, font4x6_Full, highScore.getChar(2));
    }
    else {
      SpritesB::drawOverwrite(xOffset - (highScore.getSlotNumber() * HIGH_SCORE_DIST_BETWEEN_ROWS), yOffset + 12, font4x6_Full, highScore.getChar(2));
    }


    // Handle buttons ..

    {
      uint8_t justPressed = arduboy.justPressedButtons();
      uint8_t charIndex = highScore.getCharIndex();

      if (justPressed & LEFT_BUTTON)       { highScore.incChar(charIndex); }
      if (justPressed & RIGHT_BUTTON)      { highScore.decChar(charIndex); }
      if (justPressed & UP_BUTTON)         { highScore.decCharIndex(); } 
      if (justPressed & DOWN_BUTTON)       { highScore.incCharIndex(); } 

      if (justPressed & A_BUTTON) { 
        
        EEPROM_Utils::writeChars(highScore.getSlotNumber(), highScore);
        highScore.disableEditting(); 
        
      }

    }

  }
  else {

    uint8_t pressed = arduboy.pressedButtons();
    SpritesB::drawOverwrite(0, 15, splash_press_a, 0);


    // Clear scores ..

    if ((pressed & UP_BUTTON) && (pressed & DOWN_BUTTON)) {

      clearScores++;

      switch (clearScores) {

        case 21 ... 60:
          #ifdef USE_LEDS             
          arduboy.setRGBled(128 - (clearScores * 2), 0, 0);
          #endif
          break;

        case 61:
          clearScores = 0;
          #ifdef USE_LEDS             
          arduboy.setRGBled(0, 0, 0);
          #endif
          EEPROM_Utils::initEEPROM(true);
          sound.tone(NOTE_C6, 100);
          return;

      }

    }
    else {

      if (clearScores > 0) {
      
        #ifdef USE_LEDS             
        arduboy.setRGBled(0, 0, 0);
        #endif
        clearScores = 0;

      }
      
    }

    {
      uint8_t justPressed = arduboy.justPressedButtons();

      if ((justPressed & A_BUTTON) || (justPressed & B_BUTTON)) { 
        #ifdef USE_LEDS             
        arduboy.setRGBled(0, 0, 0);
        #endif
        gameState = GameState::Intro_Init; 
      }

    }
    
  }

  //arduboy.display(true);

}

#endif