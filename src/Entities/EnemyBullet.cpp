#include "EnemyBullet.h"
#include "../Utils/Enums.h"

EnemyBullet::EnemyBullet() { }

void EnemyBullet::move() {

  // FIX 20180821
  // switch (getDirection()) {
  
  //   case Direction::North:
  //     _y = _y - 2;
  //     break;
  
  //   case Direction::NorthEast:
  //     _x = _x + 2;
  //     _y = _y - 2;
  //     break;
  
  //   case Direction::East:
  //     _x = _x + 2;
  //     break;
  
  //   case Direction::SouthEast:
  //     _x = _x + 2;
  //     _y = _y + 2;
  //     break;
  
  //   case Direction::South:
  //     _y = _y + 2;
  //     break;
  
  //   case Direction::SouthWest:
  //     _x = _x - 2;
  //     _y = _y + 2;
  //     break;
  
  //   case Direction::West:
  //     _x = _x - 2;
  //     break;
  
  //   case Direction::NorthWest:
  //     _x = _x - 2;
  //     _y = _y - 2;
  //     break;

  //   default: break;
      
  // }

  // FIX 20180821
  _x = _x + static_cast<int8_t>(pgm_read_byte(&movement_x_offset[static_cast<uint8_t>(getDirection())]) * 2);
  _y = _y + static_cast<int8_t>(pgm_read_byte(&movement_y_offset[static_cast<uint8_t>(getDirection())]) * 2);

  if (_x > WIDTH - SCOREBOARD_OUTER_RECT_WIDTH) setEnabled(false);  
  if (_y > HEIGHT) setEnabled(false);
  
}

