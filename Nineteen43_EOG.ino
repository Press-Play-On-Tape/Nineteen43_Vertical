

/* -----------------------------------------------------------------------------------------------------------------------------
 *  End of mission / game loop ..
 * -----------------------------------------------------------------------------------------------------------------------------
 */
void endOfSequence_Render(bool endOfLevel) {

  while (!(arduboy.nextFrame())) {}

  if (gameState == STATE_GAME_END_OF_MISSION) {
    Sprites::drawOverwrite(117, 14, mission_successful_1, 0);
    Sprites::drawOverwrite(106, 0, mission_successful_2, 0);
  }
  else {
    if (endOfLevel) {
      Sprites::drawOverwrite(117, 17, level_complete_1, 0);
      Sprites::drawOverwrite(106, 10, level_complete_2, 0);
    }
    else {
      Sprites::drawOverwrite(112, 7, game_over, 0);
    }
  }

  arduboy.drawVerticalDottedLine(0, HEIGHT, 102, 2);
  arduboy.drawVerticalDottedLine(0, HEIGHT, 127, 2);

}

void endOfSequence(const uint8_t level) {

  bool endOfLevel = false;

  if (level == 0 && mission == 30) { gameState = STATE_GAME_END_OF_GAME; endOfLevel = true; } 
  if (level == 1 && mission == 60) { gameState = STATE_GAME_END_OF_GAME; endOfLevel = true; }

  #ifdef SAVE_MEMORY
    uint16_t high = eeprom_read_byte((uint8_t *)(EEPROM_SCORE + (level * 2)));
    if (player.getGrandScore() > high) eeprom_update_byte((uint8_t *)(EEPROM_SCORE + (level * 2)), player.getGrandScore());
  #else
    uint16_t high = EEPROM_Utils::getHighScore();
  #endif
  
  for (int8_t i = -20; i < 100; i++) {

    arduboy.pollButtons();
    endOfSequence_Render(endOfLevel); 

    arduboy.fillRect(102, i - 18, 127, 200, BLACK);
    Sprites::drawOverwrite(102, i - 18, zero_S, 0);
    Sprites::drawOverwrite(111, i, zero_S, 0);
  
    arduboy.display();
    if (arduboy.justPressed(A_BUTTON)) { break; }

  }

  while (true) {

    endOfSequence_Render(endOfLevel);
    arduboy.pollButtons();
    Sprites::drawOverwrite(68, 15, usaf, 0);


    // Score ..
    {
      Sprites::drawOverwrite(47, 4, score_img, 0);
      uint8_t digits[4] = {};
      extractDigits(digits, player.getScore());
      
      for (uint8_t i = 0, y = 56; i < 4; ++i, y -= 6) {
        Sprites::drawSelfMasked(47, y, numbers_vert, digits[i]);
      }
      
    }

    // Total ..
    {
      uint8_t digits[4] = {};
      if (gameState == STATE_GAME_END_OF_MISSION) {
        Sprites::drawOverwrite(34, 4, total_img, 0);
        extractDigits(digits, player.getGrandScore());
      }
      else {
        Sprites::drawOverwrite(32, 4, highScore_img, 0);
        extractDigits(digits, high);
      }
      
      for (uint8_t i = 0, y = 56; i < 4; ++i, y -= 6) {
        Sprites::drawSelfMasked(34, y, numbers_vert, digits[i]);
      }
      
    }

    Sprites::drawOverwrite(2, 3, aButton_continue, 0);

    arduboy.display(true);


    if (gameState == STATE_GAME_END_OF_MISSION) {
      if (arduboy.justPressed(A_BUTTON)) { gameState = STATE_GAME_INIT; break; }
    }
    else {
      #ifdef SAVE_MEMORY
      if (arduboy.justPressed(UP_BUTTON) && arduboy.justPressed(DOWN_BUTTON)) { initEEPROM(true); player.setGrandScore(0); }
      if (arduboy.justPressed(A_BUTTON)) { gameState = STATE_INTRO_INIT; break; }
      #else
      if (arduboy.justPressed(A_BUTTON)) { gameState = STATE_GAME_SAVE_SCORE; break; }
      #endif

    }

  }

}
