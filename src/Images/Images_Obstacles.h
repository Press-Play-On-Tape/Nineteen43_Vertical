#pragma once

const uint8_t PROGMEM fuel[] = {
  12, 9,
  0x00,	0x7C,	0x82,	0x82,	0xAA,	0x92,	0xAA,	0x82,	0x84,	0x8E,	0x74,	0x00,
  0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,
};

const uint8_t PROGMEM fuel_mask[] = {
  0x7C,	0xFE,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xFE,	0xFF,	0xFE,	0x7C,
  0x00,	0x00,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x00,	0x00,
};

const uint8_t PROGMEM bullets[] = {
  10, 9,
  0x00,	0x0E,	0xEE,	0xEE,	0xEE,	0xEA,	0xAA,	0xA4,	0x40,	0x00,
  0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,
};

const uint8_t PROGMEM bullets_mask[] = {
  0x1F,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xFF,	0xFE,	0xE4,	0x40,
  0x00,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x01,	0x00,	0x00,
};

const uint8_t PROGMEM health[] = {
  9, 9,
  0x00,	0x10,	0x38,	0x7C,	0xFE,	0xFE,	0xFE,	0x6C,	0x00,
  0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,	0x00,
};

const uint8_t PROGMEM health_mask[] = {
  0x10,	0x38,	0x7C,	0xFE,	0xFF,	0xFF,	0xFF,	0xFE,	0x6C,
  0x00,	0x00,	0x00,	0x00,	0x01,	0x01,	0x01,	0x00,	0x00,
};

const uint8_t PROGMEM power_up[] = {
  9,9,
  0x00, 0x38, 0x44, 0x44, 0x44, 0x28, 0x54, 0x92, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

const uint8_t PROGMEM power_up_mask[] = {
  0x38, 0x7C, 0xFE, 0xFE, 0xFE, 0x7C, 0xFE, 0xFF, 0xBA,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
};