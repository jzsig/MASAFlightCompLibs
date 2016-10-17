#ifndef MS5611_H_
#define MS5611_H_

#include <stdlib.h>
#include <stdio.h>

//First 3 includes must be in this order
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal_conf.h"
#include "stm32f4xx_hal_spi.h"

//PROM Offsets
#define MFG 0xA0
#define CFC1 0xA2
#define CFC2 0xA4
#define CFC3 0xA6
#define CFC4 0xA8
#define CFC5 0xAA
#define CFC6 0xAC
#define MS5611_CRC 0xAE

//Commands
#define CVT_D1_256 0x40
#define CVT_D1_512 0x42
#define CVT_D1_1024 0x44
#define CVT_D1_2048 0x46
#define CVT_D1_4096 0x48
#define CVT_D2_256 0x50
#define CVT_D2_512 0x52
#define CVT_D2_1024 0x54
#define CVT_D2_2048 0x56
#define CVT_D2_4096 0x58
#define ADC_READ 0x00
#define MS_RESET 0x1E

typedef struct
{
  SPI_HandleTypeDef *spi;

  uint32_t GPIO_Mask_Set;

  uint32_t GPIO_Mask_Reset;

  GPIO_TypeDef *CS_Port;

  uint16_t CFC[8];

}_MS5611;

int MS5611_Cmd(uint8_t *Data, _MS5611 *Device);
int MS5611_PROM(_MS5611 *Device);
//void MS5611_Cfg(_MS5611 *Device);

#endif /* MS5611_H_ */
