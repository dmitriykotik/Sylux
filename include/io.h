#pragma once

#include <stdint.h>

uint8_t InByte(uint16_t port);
void OutByte(uint16_t port, uint8_t value);
void SleepIO(uint32_t ticks);