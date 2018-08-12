

/* -----------------------------------------------------------------------------------------------------------------------------
 *  End of mission / game loop ..
 * -----------------------------------------------------------------------------------------------------------------------------
 */
void endOfSequence_Render() {

  while (!(arduboy.nextFrame())) {}

  if (gameState == STATE_GAME_END_OF_MISSION) {
    Sprites::drawOverwrite(106, 2, mission_successful, 0);
  }
  else {
    Sprites::drawOverwrite(112, 8, game_over, 0);
  }

  arduboy.drawVerticalDottedLine(0, HEIGHT, 102, WHITE);
  arduboy.drawVerticalDottedLine(0, HEIGHT, 127, WHITE);

}

void endOfSequence(const uint8_t level) {

  #ifdef SAVE_MEMORY
    uint16_t high = EEPROMReadInt(EEPROM_SCORE + (level * 2));
    if (player.getGrandScore() > high) EEPROMWriteInt(EEPROM_SCORE + (level * 2), player.getGrandScore());
  #endif
  
  for (int8_t i = -20; i < 100; i++) {

    endOfSequence_Render(); 

    arduboy.fillRect(102, i - 18, 127, 200, BLACK);
    Sprites::drawOverwrite(102, i - 18, zero_S, 0);
    Sprites::drawOverwrite(111, i, zero_S, 0);
  
    arduboy.display();

  }

  while (true) {

    endOfSequence_Render();
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
      Sprites::drawOverwrite(34, 4, total_img, 0);
      uint8_t digits[4] = {};
      extractDigits(digits, player.getGrandScore());
      
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

  if (level == 0 && mission == 30) { gameState = STATE_GAME_END_OF_GAME; }
  if (level == 1 && mission == 60) { gameState = STATE_GAME_END_OF_GAME; }

}
