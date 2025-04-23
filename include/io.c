#include "io.h"

uint8_t InByte(uint16_t port) {
    uint8_t result;
    __asm__ volatile ("inb %1, %0" : "=a"(result) : "Nd"(port));
    return result;
}

void OutByte(uint16_t port, uint8_t value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

void SleepIO(uint32_t ticks) {
    for (volatile uint32_t i = 0; i < ticks * 1000; i++) {
        __asm__ __volatile__("nop");
    }
}