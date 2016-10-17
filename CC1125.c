#include "CC1125.h"

int CC1125_Cmd(uint8_t *Data, _CC1125 *Device){

  //Pull CS pin low
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Reset;
  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Set);

  //Transmit cmd to CC1125 over SPI
  //If need to optimize, HAL can be replaced with low level spi implementation.
  HAL_SPI_Transmit(Device->spi, Data, 1, 0xFFFF);

  //Push CS pin high
  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Reset);
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Set;


  return 1;
}

int CC1125_Reg(uint8_t Addr, uint8_t Data, _CC1125 *Device){

  //Set up packet for HAL transmit function. (Something that can be optmized if
  //we switch to custom spi driver).
  uint8_t Packet[2];
  Packet[0] = Addr;
  Packet[1] = Data;

  //Pull CS pin low
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Reset;
  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Set);

  //Transmit cmd to CC1125 over SPI
  //If need to optimize, HAL can be replaced with low level spi implementation.
  HAL_SPI_Transmit(Device->spi, Packet, 2, 0xFFFF);

  //Push CS pin high
  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Reset);
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Set;


  return 1;
}

int CC1125_EReg(uint8_t Addr, uint8_t Data, _CC1125 *Device){
  //Set up packet for HAL transmit function. (Something that can be optmized if
  //we switch to custom spi driver).
  uint8_t Packet[3];
  Packet[0] = EXTEND_ADDR;
  Packet[1] = Addr;
  Packet[2] = Data;

  //Pull CS pin low
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Reset;
  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Set);

  //Transmit cmd to CC1125 over SPI
  //If need to optimize, HAL can be replaced with low level spi implementation.
  HAL_SPI_Transmit(Device->spi, Packet, 3, 0xFFFF);

  //Push CS pin high
  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Reset);
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Set;


  return 1;
}

int CC1125_TxFIFO(uint8_t Data, _CC1125 *Device){
  //Set up packet for HAL transmit function. (Something that can be optmized if
  //we switch to custom spi driver).
  uint8_t Packet[2];
  Packet[0] = 0x3F;
  Packet[1] = Data;

  //Pull CS pin low
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Reset;
  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Set);

  //Transmit cmd to CC1125 over SPI
  //If need to optimize, HAL can be replaced with low level spi implementation.
  HAL_SPI_Transmit(Device->spi, Packet, 2, 0xFFFF);

  //Push CS pin high
  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Reset);
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Set;


  return 1;
}

int CC1125_RxFIFO(uint8_t *RxPacket, _CC1125 *Device){
  //May want to change so packet is returned by value not reference

  //Set up packet for HAL transmit function. (Something that can be optmized if
  //we switch to custom spi driver).
  uint8_t TxPacket = 0x3F+0x80;

  //Pull CS pin low
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Reset;
  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Set);

  //Transmit NOP to CC1125 over SPI and record CC1125 response
  //If need to optimize, HAL can be replaced with low level spi implementation.
  HAL_SPI_TransmitReceive(Device->spi, &TxPacket, RxPacket, 1, 0xFFFF);

  //Push CS pin high
  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Reset);
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Set;

  return 1;
}

int CC1125_GetState(_CC1125 *Device){

  //Set up packet for HAL transmit function. (Something that can be optmized if
  //we switch to custom spi driver).
  uint8_t TxPacket = SNOP;
  uint8_t RxPacket = 0;

  //Pull CS pin low
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Reset;
  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Set);

  //Transmit NOP to CC1125 over SPI and record CC1125 response
  //If need to optimize, HAL can be replaced with low level spi implementation.
  HAL_SPI_TransmitReceive(Device->spi, &TxPacket, &RxPacket, 1, 0xFFFF);

  //Push CS pin high
  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Reset);
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Set;

  Device->State = (RxPacket >> 4);

  return 1;
}

void CC1125_Cfg(_CC1125 *Device){

  //Working Configureation for 869MHz
  CC1125_Reg(0x00, 0xB0, Device);
  CC1125_Reg(0x01, 0x06, Device);
  CC1125_Reg(0x02, 0xB0, Device);
  CC1125_Reg(0x03, 0x40, Device);
  CC1125_Reg(0x08, 0x0B, Device);
  CC1125_Reg(0x0C, 0x1C, Device);
  CC1125_Reg(0x10, 0xC6, Device);
  CC1125_Reg(0x11, 0x19, Device);
  CC1125_Reg(0x13, 0x05, Device);
  CC1125_Reg(0x17, 0x20, Device);
  CC1125_Reg(0x18, 0x19, Device);
  CC1125_Reg(0x1C, 0xA9, Device);
  CC1125_Reg(0x1D, 0xCF, Device);
  CC1125_Reg(0x1E, 0x00, Device);
  CC1125_Reg(0x21, 0x12, Device);
  CC1125_Reg(0x28, 0x00, Device);
  CC1125_Reg(0x2B, 0x74, Device);
  CC1125_Reg(0x2D, 0x7E, Device);
  CC1125_Reg(0x2E, 0xFF, Device);

  CC1125_EReg(0x00, 0x00, Device);
  CC1125_EReg(0x01, 0x22, Device);
  CC1125_EReg(0x0C, 0x6C, Device);
  CC1125_EReg(0x0D, 0xA7, Device);
  CC1125_EReg(0x0E, 0x33, Device);
  CC1125_EReg(0x12, 0x00, Device);
  CC1125_EReg(0x13, 0x5F, Device);
  CC1125_EReg(0x17, 0x0E, Device);
  CC1125_EReg(0x19, 0x03, Device);
  CC1125_EReg(0x1B, 0x33, Device);
  CC1125_EReg(0x1D, 0x17, Device);
  CC1125_EReg(0x1F, 0x50, Device);
  CC1125_EReg(0x20, 0x6E, Device);
  CC1125_EReg(0x21, 0x14, Device);
  CC1125_EReg(0x22, 0xAC, Device);
  CC1125_EReg(0x32, 0x0E, Device);
  CC1125_EReg(0x34, 0xC7, Device);
  CC1125_EReg(0x36, 0x07, Device);
}

