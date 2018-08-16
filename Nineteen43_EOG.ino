#include "src/Utils/Arduboy2Ext.h"


/* -----------------------------------------------------------------------------------------------------------------------------
 *  End of mission / game loop ..
 * -----------------------------------------------------------------------------------------------------------------------------
 */
void endOfSequence_Render(bool endOfLevel) {

  if (gameState == GameState::End_Of_Mission) {

    SpritesB::drawOverwrite(117, 14, mission_successful_1, 0);
    SpritesB::drawOverwrite(106, 0, mission_successful_2, 0);

  }
  else {
    if (endOfLevel) {
      SpritesB::drawOverwrite(117, 17, level_complete_1, 0);
      SpritesB::drawOverwrite(106, 10, level_complete_2, 0);
    }
    else {
      SpritesB::drawOverwrite(101, 0, game_over, 0);
    }
  }

  arduboy.drawVerticalDottedLine(0, HEIGHT, (gameState == GameState::End_Of_Mission || endOfLevel ? 102 : 97), 2);
  arduboy.drawVerticalDottedLine(0, HEIGHT, 127, 2);

}

void endOfSequence(const uint8_t level) {

  bool endOfLevel = false;

  if (level == 0 && mission == 30) { gameState = GameState::End_Of_Game; endOfLevel = true; } 
  if (level == 1 && mission == 60) { gameState = GameState::End_Of_Game; endOfLevel = true; }

  #ifdef SAVE_MEMORY
    uint16_t high = eeprom_read_word((uint16_t *)(EEPROM_SCORE + (level * 2)));
    if (player.getScore() > high) { 
      eeprom_update_word((uint16_t *)(EEPROM_SCORE + (level * 2)), player.getScore());
      high = player.getScore();
    }
  #else
    uint16_t high = EEPROM_Utils::getHighScore();
  #endif
  
  int8_t i = -20;

  while (true) {

    while (!(arduboy.nextFrame())) {}
    arduboy.pollButtons();
    endOfSequence_Render(endOfLevel); 

    if (i< 100) {

      arduboy.fillRect(97, i - 18, 127, 200, BLACK);

      SpritesB::drawOverwrite((gameState == GameState::End_Of_Mission || endOfLevel ? 102 : 97), i - 18, zero_S, 0);
      SpritesB::drawOverwrite(111, i, zero_S, 0);
      i++;
    }
    else {

      SpritesB::drawOverwrite(66, 15, usaf, 0);


      // Score ..
      {
        SpritesB::drawOverwrite(45, 4, score_img, 0);
        uint8_t digits[4] = {};
        extractDigits(digits, player.getScore());

        for (uint8_t i = 0, y = 56; i < 4; ++i, y -= 6) {
          SpritesB::drawSelfMasked(45, y, numbers_vert, digits[i]);
        }
        
      }

      // Total ..
      {
        uint8_t digits[4] = {};
        // if (gameState == GameState::End_Of_Mission) {
        //   SpritesB::drawOverwrite(32, 4, total_img, 0);
        //   extractDigits(digits, player.getGrandScore());
        // }
        // else {
          SpritesB::drawOverwrite(30, 4, highScore_img, 0);
          extractDigits(digits, high);
        // }
        
        for (uint8_t i = 0, y = 56; i < 4; ++i, y -= 6) {
          SpritesB::drawSelfMasked(32, y, numbers_vert, digits[i]);
        }
        
      }

      SpritesB::drawOverwrite(2, 3, aButton, 0);
      SpritesB::drawOverwrite(5, 12, aButton_continue, 0);

    }

    arduboy.display(true);

    if (gameState == GameState::End_Of_Mission) {
      if (arduboy.justPressed(A_BUTTON)) { gameState = GameState::Game_Init; break; }
    }
    else {
      #ifdef SAVE_MEMORY
      if (arduboy.justPressed(UP_BUTTON) && arduboy.justPressed(DOWN_BUTTON)) { initEEPROM(true); player.setScore(0); }
      if (arduboy.justPressed(A_BUTTON)) { gameState = GameState::Intro_Init; break; }
      #else
      if (arduboy.justPressed(A_BUTTON)) { gameState = GameState::Save_Score; break; }
      #endif

    }

  }

}
