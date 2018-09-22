#include "src/Utils/Arduboy2Ext.h"


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Introduction loop initialisation ..
 * -----------------------------------------------------------------------------------------------------------------------------
 */
void introInit() {

  mission = 0;                            
  missionIdx = 0;
  introState = 0;
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
void credits_loop() {

  #ifdef SAVE_MEMORY
  SpritesB::drawOverwrite(113, 6, credits_01, 0);
  SpritesB::drawOverwrite(104, 4, credits_02, 0);
  #else
  Sprites::drawOverwrite(113, 6, credits_01, 0);
  Sprites::drawOverwrite(104, 4, credits_02, 0);
  #endif

  arduboy.drawVerticalDottedLine(0, HEIGHT, 97);
  arduboy.drawVerticalDottedLine(0, HEIGHT, 127);

  if (intro < 120) {

    drawFlyingPair();
  
  }
  else {  

    #ifdef SAVE_MEMORY
    SpritesB::drawOverwrite(70, 9, filmote_01, 0);
    SpritesB::drawOverwrite(70, 26, filmote_02, 0);
    SpritesB::drawOverwrite(52, 9, pharap_01, 0);
    SpritesB::drawOverwrite(53, 26, pharap_02, 0);
    SpritesB::drawOverwrite(36, 8, vampirics_01, 0);
    SpritesB::drawOverwrite(37, 26, vampirics_02, 0);
    SpritesB::drawOverwrite(0, 15, splash_press_a, 0);
    #else
    Sprites::drawOverwrite(70, 9, filmote_01, 0);
    Sprites::drawOverwrite(70, 26, filmote_02, 0);
    Sprites::drawOverwrite(52, 9, pharap_01, 0);
    Sprites::drawOverwrite(53, 26, pharap_02, 0);
    Sprites::drawOverwrite(36, 8, vampirics_01, 0);
    Sprites::drawOverwrite(37, 26, vampirics_02, 0);
    Sprites::drawOverwrite(0, 15, splash_press_a, 0);
    #endif

  }

  if (arduboy.justPressed(A_BUTTON)) {
    #ifdef SAVE_MEMORY
    gameState = GameState::Intro_Init;
    #else
    arduboy.pollButtons();
    gameState = GameState::Save_Score;
    #endif
  }

}


/* -----------------------------------------------------------------------------------------------------------------------------
 *  Introduction loop ..
 * -----------------------------------------------------------------------------------------------------------------------------
 */
enum class IntroState : uint8_t {
  PressA,
  Level1,
  Level2,
  Level3
};

enum class ArrowState : uint8_t {
  None,
  Lower,
  Upper
};

#define SPLASH_ARROW_MAX 7
#define SPLASH_PRESS_A_X 23
#define SPLASH_PRESS_A_Y 15
#define SPLASH_LEVEL_CAPTION_X SPLASH_PRESS_A_X + 2
#define SPLASH_LEVEL_CAPTION_Y SPLASH_PRESS_A_Y + 5
#define SPLASH_LEVEL_NUMBER_X SPLASH_LEVEL_CAPTION_X + 1
#define SPLASH_LEVEL_NUMBER_Y SPLASH_LEVEL_CAPTION_Y + 21
#define SPLASH_LEVEL_ARROW_UP_X SPLASH_LEVEL_CAPTION_X + 10
#define SPLASH_LEVEL_ARROW_UP_Y 28
#define SPLASH_LEVEL_ARROW_DOWN_X SPLASH_LEVEL_CAPTION_X - 6
#define SPLASH_LEVEL_ARROW_DOWN_Y 28

void introLoop() {

  #ifdef SAVE_MEMORY
  SpritesB::drawOverwrite(73, 1, title, 0);
  SpritesB::drawOverwrite(59, 4, battle_of_midway_1, 0);
  SpritesB::drawOverwrite(49, 4, battle_of_midway_2, 0);
  SpritesB::drawOverwrite(112, 0, splash_upper, 0);
  SpritesB::drawOverwrite(0, 0, splash_lower, 0);
  #else
  Sprites::drawOverwrite(73, 1, title, 0);
  Sprites::drawOverwrite(59, 4, battle_of_midway_1, 0);
  Sprites::drawOverwrite(49, 4, battle_of_midway_2, 0);
  Sprites::drawOverwrite(112, 0, splash_upper, 0);
  Sprites::drawOverwrite(0, 0, splash_lower, 0);
  #endif

  {
    IntroState state = static_cast<IntroState>((introState & 0b11100000) >> 5);
    ArrowState arrowState = static_cast<ArrowState>((introState & 0b00011000) >> 3);
    uint8_t arrowDelay = introState & 0b00000111;

    switch (state) {

      case IntroState::PressA:
        #ifdef SAVE_MEMORY
        SpritesB::drawOverwrite(SPLASH_PRESS_A_X, SPLASH_PRESS_A_Y, splash_press_a, 0);
        #else
        Sprites::drawOverwrite(SPLASH_PRESS_A_X, SPLASH_PRESS_A_Y, splash_press_a, 0);
        #endif
        break;

      case IntroState::Level1 ... IntroState::Level3:
        {
          uint8_t upX = SPLASH_LEVEL_ARROW_UP_X;
          uint8_t downX = SPLASH_LEVEL_ARROW_DOWN_X;
        
          #ifdef SAVE_MEMORY
          SpritesB::drawOverwrite(SPLASH_LEVEL_CAPTION_X, SPLASH_LEVEL_CAPTION_Y, level_select, 0);
          SpritesB::drawOverwrite(SPLASH_LEVEL_NUMBER_X, SPLASH_LEVEL_NUMBER_Y, level_numbers, level);
          #else
          Sprites::drawOverwrite(SPLASH_LEVEL_CAPTION_X, SPLASH_LEVEL_CAPTION_Y, level_select, 0);
          Sprites::drawOverwrite(SPLASH_LEVEL_NUMBER_X, SPLASH_LEVEL_NUMBER_Y, level_numbers, level);
          #endif

          switch (arrowState) {

            case ArrowState::None:  
              break;

            case ArrowState::Lower:
              downX = SPLASH_LEVEL_ARROW_DOWN_X - 2;
              break;

            case ArrowState::Upper:
              upX = SPLASH_LEVEL_ARROW_UP_X + 2;
              break;

          }

          #ifdef SAVE_MEMORY
          SpritesB::drawOverwrite(downX, SPLASH_LEVEL_ARROW_DOWN_Y, arrow_down, 0);
          SpritesB::drawOverwrite(upX, SPLASH_LEVEL_ARROW_UP_Y, arrow_up, 0);
          #else
          Sprites::drawOverwrite(downX, SPLASH_LEVEL_ARROW_DOWN_Y, arrow_down, 0);
          Sprites::drawOverwrite(upX, SPLASH_LEVEL_ARROW_UP_Y, arrow_up, 0);
          #endif

        }

        if (arrowDelay > 0) {
          arrowDelay--;
          introState = (introState & 0b11111000) | arrowDelay;
          if (arrowDelay == 0) {
            introState = introState & 0b11100000;
          }
        }

        break;

    }

  }

  //arduboy.display(true);

  {
   
    uint8_t justPressed = arduboy.justPressedButtons();
    IntroState state = static_cast<IntroState>((introState & 0b11100000) >> 5);
 
    if (justPressed & RIGHT_BUTTON) {
      
      switch (state) {

        case IntroState::PressA:
          introState = ((static_cast<uint8_t>(IntroState::Level1) + level) << 5) | (static_cast<uint8_t>(ArrowState::None) << 3) | SPLASH_ARROW_MAX;
          break;

        case IntroState::Level1:
          introState = (static_cast<uint8_t>(IntroState::Level2) << 5) | (static_cast<uint8_t>(ArrowState::Upper) << 3) | SPLASH_ARROW_MAX;
          level++;
          eeprom_update_byte(EEPROM_LEVEL, level);
          break;

        case IntroState::Level2:
          introState = (static_cast<uint8_t>(IntroState::Level3) << 5) | (static_cast<uint8_t>(ArrowState::Upper) << 3) | SPLASH_ARROW_MAX;
          level++;
          eeprom_update_byte(EEPROM_LEVEL, level);
          break;

        default: break;

      }

    }

    if (justPressed & LEFT_BUTTON) {

      switch (state) {

        case IntroState::PressA:
          introState = ((static_cast<uint8_t>(IntroState::Level1) + level) << 5) | (static_cast<uint8_t>(ArrowState::None) << 3) | SPLASH_ARROW_MAX;
          break;

        case IntroState::Level2:
          introState = (static_cast<uint8_t>(IntroState::Level1) << 5) | (static_cast<uint8_t>(ArrowState::Lower) << 3) | SPLASH_ARROW_MAX;
          level--;
          eeprom_update_byte(EEPROM_LEVEL, level);
          break;

        case IntroState::Level3:
          introState = (static_cast<uint8_t>(IntroState::Level2) << 5) | (static_cast<uint8_t>(ArrowState::Lower) << 3) | SPLASH_ARROW_MAX;
          level--;
          eeprom_update_byte(EEPROM_LEVEL, level);
          break;

        default: break;

      }

    }

    if (justPressed & B_BUTTON) {
      if (state != IntroState::PressA) {
        introState = 0;
      }
      else {
        gameState = GameState::Credits_Init;   
      }
    }

    if (justPressed & A_BUTTON) { 
      
      gameState = GameState::Game_Init;
      mission = 0; 
      
    }  

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
  
  initSceneryItems();
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
