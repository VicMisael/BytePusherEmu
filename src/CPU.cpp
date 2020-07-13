#include "CPU.h"
#include <cstring>
#include <iostream>
#include <algorithm>

#define mem_size 0x1000008
#define cycles 65536
uint8_t memory[mem_size];

CPU::CPU() {
	std::fill(memory, memory + mem_size, 0);

}
CPU::~CPU() {}
uint8_t* CPU::getMemory() {
	return memory;
}
void  CPU::loadROM(uint8_t rom[], int romSize) {
	for (int i = 0; i < romSize; i++) {
		memory[i] = rom[i];
	}
}
void CPU::setControllers(uint8_t MSB, uint8_t LSB) {
	memory[0] = MSB;
	memory[1] = LSB;
	
}


void CPU::run() {
	uint32_t PC = getBytes(2, 3);
	for (int i = 0; i < cycles; i++) {
		memory[getBytes(PC + 3, 3)] = memory[getBytes(PC, 3)];
		PC = getBytes(PC + 6, 3);
	}

}
uint8_t* CPU::getAudioMemSection()
{
	return &memory[getBytes(6, 2) << 8];
}
uint8_t* CPU::getVideoMemSection() {
	return &memory[getBytes(5, 1) << 16];
}
uint64_t  CPU::getBytes(int position, int size) {
	uint64_t PC = 0;
	while (size--) {
		PC <<= 8;
		PC |= memory[position++];
	}
	return PC;
}