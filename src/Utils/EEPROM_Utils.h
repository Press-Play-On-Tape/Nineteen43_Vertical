#pragma once

#include "Arduboy2Ext.h"
#include "../Entities/Slot.h"
#include "HighScoreEditor.h"

class EEPROM_Utils {

  public: 

    EEPROM_Utils(){};
        
    static void initEEPROM(bool forceClear);
    static Slot getSlot(uint8_t x);
    static uint8_t saveScore(uint16_t score);
    static void writeChars(uint8_t slotIndex, HighScore &highScore);
    static uint16_t getHighScore();

};


/* ----------------------------------------------------------------------------
 *   Is the EEPROM initialised?
 *
 *   Looks for the characters '4' and '3' in the first two bytes of the EEPROM
 *   memory range starting from byte EEPROM_STORAGE_SPACE_START.  If not found,
 *   it resets the settings ..
 */
void EEPROM_Utils::initEEPROM(bool forceClear) {

  uint8_t c1 = eeprom_read_byte((uint8_t *)EEPROM_START_C1);
  uint8_t c2 = eeprom_read_byte((uint8_t *)EEPROM_START_C2);

  if (forceClear || c1 != '4' || c2 != '3') { 

    eeprom_update_byte((uint8_t *)EEPROM_START_C1, '4');
    eeprom_update_byte((uint8_t *)EEPROM_START_C2, '3');
    eeprom_update_byte((uint8_t *)EEPROM_LEVEL, 0);

    #ifdef SAVE_MEMORY

      uint16_t score = 0;
      uint8_t level = 0;

      eeprom_update_byte((uint8_t *)EEPROM_SCORE, level);
      // eeprom_update_byte((uint8_t *)(EEPROM_SCORE + 1), level);
      // eeprom_update_byte((uint8_t *)(EEPROM_SCORE + 2), level);
      // eeprom_update_byte((uint8_t *)(EEPROM_SCORE + 3), level);
      // eeprom_update_byte((uint8_t *)(EEPROM_SCORE + 4), level);
      // eeprom_update_byte((uint8_t *)(EEPROM_SCORE + 5), level);
      eeprom_update_word((uint16_t *)EEPROM_SCORE, score);
      eeprom_update_word((uint16_t *)(EEPROM_SCORE + 2), score);
      eeprom_update_word((uint16_t *)(EEPROM_SCORE + 4), score);

    #else

      uint16_t score = 10;

      for (uint8_t x = 0; x < MAX_NUMBER_OF_SCORES; x++) {

        eeprom_update_byte((uint8_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x)), 0);
        eeprom_update_byte((uint8_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 1), 0);
        eeprom_update_byte((uint8_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 2), 0);
        eeprom_update_word((uint16_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 3), score);
        score = score - 2;

      }

    #endif

  }

}


/* -----------------------------------------------------------------------------
 *   Get High Score details. 
 */
#ifndef SAVE_MEMORY
uint16_t EEPROM_Utils::getHighScore() {

  uint16_t score = eeprom_read_word((uint16_t *)(EEPROM_TOP_START + 3));

  return score;

}
#endif


/* -----------------------------------------------------------------------------
 *   Get slot details. 
 */
#ifndef SAVE_MEMORY
Slot EEPROM_Utils::getSlot(uint8_t x) {

  Slot slot;

  slot.setChar0(eeprom_read_byte((uint8_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x))));
  slot.setChar1(eeprom_read_byte((uint8_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 1)));
  slot.setChar2(eeprom_read_byte((uint8_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 2)));

  uint16_t score = 0;
  score = eeprom_read_word((uint16_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 3));
  slot.setScore(score);


  return slot;

}
#endif


/* -----------------------------------------------------------------------------
 *   Save score and return index.  255 not good enough! 
 */
#ifndef SAVE_MEMORY
uint8_t EEPROM_Utils::saveScore(uint16_t score) {

  uint8_t idx = DO_NOT_EDIT_SLOT;

  for (uint8_t x = 0; x < MAX_NUMBER_OF_SCORES; x++) {

    Slot slot = getSlot(x);

    if (slot.getScore() < score) {

      idx = x;
      break;

    }

  }

  if (idx < DO_NOT_EDIT_SLOT) {

    for (uint8_t x = MAX_NUMBER_OF_SCORES - 1; x > idx; x--) {

      Slot slot = getSlot(x - 1);

      eeprom_update_byte((uint8_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x)), slot.getChar0());
      eeprom_update_byte((uint8_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 1), slot.getChar1());
      eeprom_update_byte((uint8_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 2), slot.getChar2());
      eeprom_update_word((uint16_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 3), slot.getScore());

    }

    eeprom_update_byte((uint8_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * idx)), 0);
    eeprom_update_byte((uint8_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * idx) + 1), 0);
    eeprom_update_byte((uint8_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * idx) + 2), 0);
    eeprom_update_word((uint16_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * idx) + 3), score);

  }

  return idx;

}
#endif


/* -----------------------------------------------------------------------------
 *   Save characters in the nominated slot index. 
 */
#ifndef SAVE_MEMORY
void EEPROM_Utils::writeChars(uint8_t slotIndex, HighScore &highScore) {

    eeprom_update_byte((uint8_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * slotIndex)), highScore.getChar(0));
    eeprom_update_byte((uint8_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * slotIndex) + 1), highScore.getChar(1));
    eeprom_update_byte((uint8_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * slotIndex) + 2), highScore.getChar(2));

}
#endif