#include "bsp_sht30.h"
#include <math.h>

// CRC8校验函数（SHT30专用）[[13][65]]
static uint8_t CRC8_Calculate(const uint8_t *data, uint8_t len) {
    uint8_t crc = 0xFF;
    for (uint8_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (uint8_t bit = 8; bit > 0; bit--) {
            if (crc & 0x80) {
                crc = (crc << 1) ^ 0x31;
            } else {
                crc <<= 1;
            }
        }
    }
    return crc;
}

// 初始化传感器
SHT30_Status SHT30_Init(I2C_HandleTypeDef *hi2c) {
    uint8_t cmd[2] = {0x22, 0x36};  // 高精度周期测量命令
    if (HAL_I2C_Master_Transmit(hi2c, SHT30_ADDR, cmd, 2, 100) != HAL_OK) {
        return SHT30_ERR_I2C;
    }
    HAL_Delay(20);  // 等待传感器初始化完成
    return SHT30_OK;
}

// 读取温湿度数据
SHT30_Status SHT30_ReadData(I2C_HandleTypeDef *hi2c, float *temp, float *humidity) {
    uint8_t rx_buf[6];
    uint8_t cmd[2] = {0xE0, 0x00};  // 周期模式读取命令[[26][65]]

    // 发送读取命令
    if (HAL_I2C_Master_Transmit(hi2c, SHT30_ADDR, cmd, 2, 100) != HAL_OK) {
        return SHT30_ERR_I2C;
    }
    HAL_Delay(15);  // 等待测量完成

    // 接收数据
    if (HAL_I2C_Master_Receive(hi2c, SHT30_ADDR, rx_buf, 6, 100) != HAL_OK) {
        return SHT30_ERR_I2C;
    }

    // CRC校验
    for (int i=0; i<2; i++) {
        if (CRC8_Calculate(&rx_buf[i*3], 2) != rx_buf[i*3+2]) {
            return SHT30_ERR_CRC;
        }
    }

    // 数据转换（高精度公式）
    uint16_t raw_temp = (rx_buf[0] << 8) | rx_buf[1];
    uint16_t raw_hum = (rx_buf[3] << 8) | rx_buf[4];
    
    *temp = -45 + 175 * (float)raw_temp / 65535.0f;  // 温度计算公式
    *humidity = 100 * (float)raw_hum / 65535.0f;     // 湿度计算公式
    
    return SHT30_OK;
}

