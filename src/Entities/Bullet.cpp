#include "Bullet.h"
#include "../Utils/Arduboy2Ext.h"
#include "../Utils/Enums.h"

Bullet::Bullet() { }

uint8_t Bullet::getX() {

  return _x;

}

void Bullet::setX(const uint8_t value) {

  _x = value;

}

uint8_t Bullet::getY() {

  return _y;

}

void Bullet::setY(const uint8_t value) {

  _y = value;

}

Direction Bullet::getDirection() {

  return static_cast<Direction>(_details & 0x0F);

}

void Bullet::setDirection(const Direction value) {

  _details = (_details & 0xF0) | static_cast<uint8_t>(value);
  
}

bool Bullet::getEnabled() {

  return (_details & 0xF0) > 0;

}

void Bullet::setEnabled(const bool value) {

  _details = (_details & 0x0F) | (value ? 0xF0 : 0x00);
  
}

void Bullet::move() {
  
  const int8_t xOffset[] = { 0, 1, 1, 1, 0, -1, -1, -1 };
  const int8_t yOffset[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
  // switch (getDirection()) {
  
  //   case Direction::North:
  //     --_y;  
  //     break;
  
  //   case Direction::NorthEast:
  //     ++_x;
  //     --_y;
  //     break;
  
  //   case Direction::East:
  //     ++_x;
  //     break;
  
  //   case Direction::SouthEast:
  //     ++_x;
  //     ++_y;
  //     break;
  
  //   case Direction::South:
  //     ++_y;
  //     break;
  
  //   case Direction::SouthWest:
  //     --_x;
  //     ++_y;
  //     break;
  
  //   case Direction::West:
  //     --_x;
  //     break;
  
  //   case Direction::NorthWest:
  //     --_x;
  //     --_y;
  //     break;

  //   default: break;
      
  // }
  _x = _x + xOffset[(uint8_t)getDirection()];
  _y = _y + yOffset[(uint8_t)getDirection()];

  if (_x > WIDTH - SCOREBOARD_OUTER_RECT_WIDTH) setEnabled(false);    
  if (_y > HEIGHT) setEnabled(false);
  
}

