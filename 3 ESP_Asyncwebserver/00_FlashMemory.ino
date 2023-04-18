// #include <EEPROM.h>


// void initEEPROM(){
//   EEPROM.begin(64);
// }
// // Store a float value in flash memory
// void storeFloatInFlash(uint32_t address, float value) {
//   byte* p = (byte*)&value;
//   for (int i = 0; i < sizeof(value); i++) {
//     EEPROM.write(address + i, *(p + i));
//   }
// }

// // Read a float value from flash memory
// float readFloatFromFlash(uint32_t address) {
//   float value;
//   byte* p = (byte*)&value;
//   for (int i = 0; i < sizeof(value); i++) {
//     *(p + i) = EEPROM.read(address + i);
//   }
//   return value;
// }

// void storeXYZToFlash(float x, float y, float z){
//   storeFloatInFlash(0, x);
//   storeFloatInFlash(10, y);
//   storeFloatInFlash(20, z);
// }

// void readXYZFromFlash(float *x, float *y, float *z){
//   *x = readFloatFromFlash(0);
//   *y = readFloatFromFlash(10);
//   *z = readFloatFromFlash(20);
// }



