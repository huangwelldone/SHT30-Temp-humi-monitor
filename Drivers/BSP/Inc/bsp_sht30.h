#ifndef BSP_SHT30_H
#define BSP_SHT30_H
#include "main.h"
#include "i2c.h"

#define SHT30_ADDR        0x44 << 1  // ADDR引脚接低电平时地址为0x44
#define SHT30_HIGH_REPEAT_CMD  0x2236  // 高精度模式，2次/秒[[26][65]]

typedef enum {
    SHT30_OK,
    SHT30_ERR_I2C,
    SHT30_ERR_CRC
} SHT30_Status;

// 初始化与数据读取函数
SHT30_Status SHT30_Init(I2C_HandleTypeDef *hi2c);
SHT30_Status SHT30_StartPeriodicMeasurement(I2C_HandleTypeDef *hi2c);
SHT30_Status SHT30_ReadData(I2C_HandleTypeDef *hi2c, float *temp, float *humidity);

#endif

