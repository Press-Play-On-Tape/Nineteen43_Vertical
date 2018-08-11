#pragma once
 
#include "../Utils/Arduboy2Ext.h"
#include "Sprites.h"
#include "Arduino.h"
#include "../Utils/Enums.h"
#include "Plane.h"

class Player : public Plane {
  
  public:
   
    Player(const uint8_t * const * images);

    #ifdef SAVE_MEMORY
    void Player::renderImage();
    #else
    void Player::renderImage(uint8_t frame);
    #endif
    void initGame();
    void initMission();

    SQ7x8 getFuel();
    uint8_t getBullets();
    uint16_t getScore();
    uint16_t getGrandScore();
    bool inRoll();
    bool getPowerUp();

    void setFuel(const SQ7x8 value);
    void decFuel(const SQ7x8 value);
    void setBullets(const uint8_t value);
    void addBullets(const uint8_t value);
    void decBullets();
    void setScore(const uint16_t value);
    void setGrandScore(const uint16_t value);
    void setPowerUp(boolean value);
    void decPowerUp();
    void startRoll();
  
  private:
    uint16_t _score;
    uint16_t _grandScore;
    uint8_t _bullets;
    SQ7x8 _fuel;
    uint8_t _rollState;
    uint8_t _powerUp;
    
};

