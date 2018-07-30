

/* -----------------------------------------------------------------------------------------------------------------------------
 *  End of mission / game loop ..
 * -----------------------------------------------------------------------------------------------------------------------------
 */
void endOfSequence(uint8_t level) {

  uint16_t high = EEPROMReadInt(EEPROM_SCORE + (level * 2));
  
  if (player.getGrandScore() > high) EEPROMWriteInt(EEPROM_SCORE + (level * 2), player.getGrandScore());
  
  for (int8_t i = -20; i < 100; i++) {

    while (!(arduboy.nextFrame())) {}

    if (gameState == STATE_GAME_END_OF_MISSION) {
      Sprites::drawOverwrite(106, 2, mission_successful, 0);
    }
    else {
      Sprites::drawOverwrite(104, 8, game_over, 0);
    }

    arduboy.drawVerticalDottedLine(0, HEIGHT, 102, WHITE);
    arduboy.drawVerticalDottedLine(0, HEIGHT, 127, WHITE);

    arduboy.fillRect(102, i - 18, 127, 200, BLACK);
    Sprites::drawOverwrite(102, i - 18, zero_S, 0);
    Sprites::drawOverwrite(111, i, zero_S, 0);
  
    arduboy.display();

  }

  while (true) {
    
    while (!(arduboy.nextFrame())) {}
    arduboy.pollButtons();

    if (gameState == STATE_GAME_END_OF_MISSION) {
      Sprites::drawOverwrite(106, 2, mission_successful, 0);
    }
    else {
      Sprites::drawOverwrite(104, 8, game_over, 0);
    }

    arduboy.drawVerticalDottedLine(0, HEIGHT, 102, WHITE);
    arduboy.drawVerticalDottedLine(0, HEIGHT, 127, WHITE);


    // Score ..
    {
      Sprites::drawOverwrite(61, 4, score_img, 0);
      uint8_t digits[4] = {};
      extractDigits(digits, player.getScore());
      
      for (uint8_t i = 0, y = 56; i < 4; ++i, y -= 6) {
        Sprites::drawSelfMasked(61, y, numbers_vert, digits[i]);
      }
      
    }

    // Total ..
    {
      Sprites::drawOverwrite(48, 4, total_img, 0);
      uint8_t digits[4] = {};
      extractDigits(digits, player.getGrandScore());
      
      for (uint8_t i = 0, y = 56; i < 4; ++i, y -= 6) {
        Sprites::drawSelfMasked(48, y, numbers_vert, digits[i]);
      }
      
    }

    Sprites::drawOverwrite(2, 3, aButton_continue, 0);

    arduboy.display(true);


    if (gameState == STATE_GAME_END_OF_MISSION) {
      if (arduboy.justPressed(A_BUTTON)) { gameState = STATE_GAME_INIT; break; }
    }
    else {
      if (arduboy.justPressed(UP_BUTTON) && arduboy.justPressed(DOWN_BUTTON)) { initEEPROM(true); player.setGrandScore(0); }
      if (arduboy.justPressed(A_BUTTON)) { gameState = STATE_INTRO_INIT; break; }

    }

  }

  if (level == 0 && mission == 30) { gameState = STATE_GAME_END_OF_GAME; }
  if (level == 1 && mission == 60) { gameState = STATE_GAME_END_OF_GAME; }

}
