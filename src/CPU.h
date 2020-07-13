#include <cstdint>
class CPU{
    public:
    CPU();
    ~CPU();
    uint8_t* getMemory();
    void  run();
    void setControllers(uint8_t MSB,uint8_t LSB);
    void loadROM(uint8_t rom[],int romSize);
    uint8_t* getAudioMemSection();
    uint8_t* getVideoMemSection();
    uint64_t getBytes(int position, int size);
   

};