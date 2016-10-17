#include "MS5611.h"

int MS5611_Cmd(uint8_t *Data, _MS5611 *Device){
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

int MS5611_PROM(_MS5611 *Device){

  uint8_t pTxData;
  uint8_t pRxData[2];

  pTxData = MFG;
  pRxData[0] = 0;
  pRxData[1] = 0;

  //MFG Config
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Reset;
  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Set);

  HAL_SPI_TransmitReceive(Device->spi, &pTxData, pRxData, 3, 0xFFFF);

  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Reset);
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Set;

  //Is there a more efficient way to do this? Are the casts necessary?
  Device->CFC[0]=((uint16_t)pRxData[0] << 8) | ((uint16_t)pRxData[1] & 0xFF);


  //C1
  pTxData = CFC1;
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Reset;
  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Set);

  HAL_SPI_TransmitReceive(Device->spi, &pTxData, pRxData, 3, 0xFFFF);

  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Reset);
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Set;

  //Is there a more efficient way to do this? Are the casts necessary?
  Device->CFC[1]=((uint16_t)pRxData[0] << 8) | ((uint16_t)pRxData[1] & 0xFF);

  //C2
  pTxData = CFC2;
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Reset;
  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Set);

  HAL_SPI_TransmitReceive(Device->spi, &pTxData, pRxData, 3, 0xFFFF);

  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Reset);
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Set;

  //Is there a more efficient way to do this? Are the casts necessary?
  Device->CFC[2]=((uint16_t)pRxData[0] << 8) | ((uint16_t)pRxData[1] & 0xFF);

  //C3
  pTxData = CFC3;
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Reset;
  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Set);

  HAL_SPI_TransmitReceive(Device->spi, &pTxData, pRxData, 3, 0xFFFF);

  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Reset);
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Set;

  //Is there a more efficient way to do this? Are the casts necessary?
  Device->CFC[3]=((uint16_t)pRxData[0] << 8) | ((uint16_t)pRxData[1] & 0xFF);

  //C4
  pTxData = CFC4;
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Reset;
  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Set);

  HAL_SPI_TransmitReceive(Device->spi, &pTxData, pRxData, 3, 0xFFFF);

  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Reset);
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Set;

  //Is there a more efficient way to do this? Are the casts necessary?
  Device->CFC[4]=((uint16_t)pRxData[0] << 8) | ((uint16_t)pRxData[1] & 0xFF);

  //C5
  pTxData = CFC5;
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Reset;
  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Set);

  HAL_SPI_TransmitReceive(Device->spi, &pTxData, pRxData, 3, 0xFFFF);

  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Reset);
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Set;

  //Is there a more efficient way to do this? Are the casts necessary?
  Device->CFC[5]=((uint16_t)pRxData[0] << 8) | ((uint16_t)pRxData[1] & 0xFF);

  //C6
  pTxData = CFC6;
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Reset;
  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Set);

  HAL_SPI_TransmitReceive(Device->spi, &pTxData, pRxData, 3, 0xFFFF);

  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Reset);
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Set;

  //Is there a more efficient way to do this? Are the casts necessary?
  Device->CFC[6]=((uint16_t)pRxData[0] << 8) | ((uint16_t)pRxData[1] & 0xFF);

  //CRC
  pTxData = MS5611_CRC;
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Reset;
  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Set);

  HAL_SPI_TransmitReceive(Device->spi, &pTxData, pRxData, 3, 0xFFFF);

  Device->CS_Port->BSRR &= ~(Device->GPIO_Mask_Reset);
  Device->CS_Port->BSRR |= Device->GPIO_Mask_Set;

  //Is there a more efficient way to do this? Are the casts necessary?
  Device->CFC[7]=((uint16_t)pRxData[0] << 8) | ((uint16_t)pRxData[1] & 0xFF);

  return 1;
}
