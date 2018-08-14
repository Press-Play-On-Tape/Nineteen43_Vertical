#include "src/Utils/Arduboy2Ext.h"


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Introduction loop initialisation ..
 * -----------------------------------------------------------------------------------------------------------------------------
 */
void introInit() {

  mission = 0;                            
  missionIdx = 0;
  intro = -32;
  gameState = GameState::Intro_Loop;
  sound.tones(score);
  player.initGame();

  obstacleLaunchDelayMin = OBSTACLE_LAUNCH_DELAY_MIN;
  obstacleLaunchDelayMax = OBSTACLE_LAUNCH_DELAY_MAX;
  obstacleBulletsValue = BULLETS_MAX;
  obstacleHealthValue = HEALTH_MAX;
  obstacleFuelValue = FUEL_MAX;
  
  frameRate = INIT_FRAME_RATE;
  arduboy.setFrameRate(frameRate);

}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Credits loop ..
 * -----------------------------------------------------------------------------------------------------------------------------
 */
#ifdef SHOW_CREDITS
void credits_loop() {

  for (int16_t i = -20; i < 100; i++) {

    while (!(arduboy.nextFrame())) {}

    SpritesB::drawOverwrite(116, 12, credits_img, 0);
    arduboy.drawVerticalDottedLine(0, HEIGHT, 110, 2);
    arduboy.drawVerticalDottedLine(0, HEIGHT, 127, 2);

    arduboy.fillRect(110, i - 18, 127, 200, BLACK);
    SpritesB::drawOverwrite(104, i - 18, zero_S, 0);
    SpritesB::drawOverwrite(113, i, zero_S, 0);
  
    arduboy.display();
    gameState = GameState::Game_Init;

  }  

  SpritesB::drawOverwrite(75, 2, filmote, 0);
  SpritesB::drawOverwrite(57, 2, pharap, 0);
  SpritesB::drawOverwrite(41, 0, vampirics, 0);
  SpritesB::drawOverwrite(0, 3, aButton, 0);
  SpritesB::drawOverwrite(3, 12, aButton_continue, 0);
  
  arduboy.display(true);

  while (!arduboy.pressed(A_BUTTON)) {
    delay(100);
  }
 
  #ifdef SAVE_MEMORY
  gameState = GameState::Intro_Init;
  #else
  arduboy.pollButtons();
  gameState = GameState::Save_Score;
  #endif
  
}
#endif


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Introduction loop ..
 * -----------------------------------------------------------------------------------------------------------------------------
 */
void introLoop() {


  // horizontal

  SpritesB::drawOverwrite(86, intro, title, 0);
  SpritesB::drawOverwrite(14, 3, aButton, 0);
  SpritesB::drawOverwrite(14, 12, aButton_startgame, 0);
  
  SpritesB::drawOverwrite(55, 70 - intro, zero_S, 0);
  SpritesB::drawOverwrite(41, 52 - intro, zero_S, 0);
  SpritesB::drawOverwrite(50, 30 - intro, zero_S, 0);

  SpritesB::drawOverwrite(0, 3, level_select, 0);
  SpritesB::drawOverwrite(2, 37, numbers_vert, (level + 1));

  intro--;
  if (intro < - 130) {
    intro = 80;
  }

  arduboy.display(true);

  if (arduboy.justPressed(RIGHT_BUTTON)) {

    if (level < 2) level++;
    eeprom_update_byte((uint8_t *)EEPROM_LEVEL, level);
    #ifdef SHOW_SOUND
      showLevel = true;
    #endif

  }

  if (arduboy.justPressed(LEFT_BUTTON)) {

    if (level > 0) level--;
    eeprom_update_byte((uint8_t *)EEPROM_LEVEL, level);

  }

  #ifdef SHOW_CREDITS
  if (arduboy.justPressed(B_BUTTON)) {

    gameState = GameState::Credits_Loop;   

  }
  #endif

  if (arduboy.justPressed(A_BUTTON)) { 
    
    gameState = GameState::Game_Init;
    mission = 0; 
    
  }  
    
}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Initialize a new game ready for play.
 * -----------------------------------------------------------------------------------------------------------------------------
 */
void gameInit() {

  for (uint8_t i = 0; i < NUMBER_OF_ENEMIES; ++i) {
    enemies[i].setEnabled(false);
  }  
  for (uint8_t i = 0; i < PLAYER_BULLETS_MAX; ++i) {
    playerBullets[i].setEnabled(false);
  }
  for (uint8_t i = 0; i < ENEMY_BULLETS_MAX; ++i) {
    enemyBullets[i].setEnabled(false);
  }
  
  player.initMission();
  obstacle.setEnabled(false);

  sound.tones(mission_start);
  intro = 80;
  gameState = GameState::Game_Loop;

  obstacleLaunchDelayMin = OBSTACLE_LAUNCH_DELAY_MIN;
  obstacleLaunchDelayMax = OBSTACLE_LAUNCH_DELAY_MAX;
  obstacleBulletsValue = BULLETS_MAX;
  obstacleHealthValue = HEALTH_MAX;
  obstacleFuelValue = FUEL_MAX;
  
  frameRate = INIT_FRAME_RATE;
  arduboy.setFrameRate(frameRate);

}
