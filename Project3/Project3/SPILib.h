#ifndef SPILib_H
#define SPILib_H

#define MASTER 0x00
#define SLAVE 0xff
#define HIGH "HIGH"
#define LOW "LOW"

void slaveSelect(char* state);
int initSPI(char role);
char transmit(char transmitionCode);

#endif // SPILib_H