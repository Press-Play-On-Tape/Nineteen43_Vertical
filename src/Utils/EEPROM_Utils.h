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
 *   Looks for the characters '1' and '9' in the first two bytes of the EEPROM
 *   memory range starting from byte EEPROM_STORAGE_SPACE_START.  If not found,
 *   it resets the settings ..
 */

const uint8_t letter1 = '1'; 
const uint8_t letter2 = '9'; 

void EEPROM_Utils::initEEPROM(bool forceClear) {

  byte c1 = eeprom_read_byte((uint8_t *)EEPROM_START_C1);
  byte c2 = eeprom_read_byte((uint8_t *)EEPROM_START_C2);

  if (forceClear || c1 != letter1 || c2 != letter2) { 

    uint8_t mission = 1;
    uint16_t score = 10;

    eeprom_update_byte((uint8_t *)EEPROM_START_C1, letter1);
    eeprom_update_byte((uint8_t *)EEPROM_START_C2, letter2);
    eeprom_update_byte((uint8_t *)EEPROM_LEVEL, 0);

    for (uint8_t x = 0; x < MAX_NUMBER_OF_SCORES; x++) {

      eeprom_update_byte((uint8_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x)), 0);
      eeprom_update_byte((uint8_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 1), 0);
      eeprom_update_byte((uint8_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 2), 0);
      eeprom_update_word((uint16_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * x) + 3), score);
      score = score - 2;

    }

  }

}


/* -----------------------------------------------------------------------------
 *   Get High Score details. 
 */
uint16_t EEPROM_Utils::getHighScore() {

  uint16_t score = eeprom_read_word((uint16_t *)(EEPROM_TOP_START + 3));

  return score;

}


/* -----------------------------------------------------------------------------
 *   Get slot details. 
 */
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


/* -----------------------------------------------------------------------------
 *   Save score and return index.  255 not good enough! 
 */
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


/* -----------------------------------------------------------------------------
 *   Save characters in the nominated slot index. 
 */
void EEPROM_Utils::writeChars(uint8_t slotIndex, HighScore &highScore) {

    eeprom_update_byte((uint8_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * slotIndex)), highScore.getChar(0));
    eeprom_update_byte((uint8_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * slotIndex) + 1), highScore.getChar(1));
    eeprom_update_byte((uint8_t *)(EEPROM_TOP_START + (EEPROM_ENTRY_SIZE * slotIndex) + 2), highScore.getChar(2));

}
