/*
 * File:   bme280.c
 * Author: C16783
 *
 * Created on May 13, 2020, 11:56 AM
 */

#include "bme280.h"
#include "oledC/oledC.h"

/**
  Section: Driver APIs
 */

uint8_t i2c_read_buff[24];
uint8_t i2c_write_buff[8];

uint8_t BME280_getID(void) {
    
    i2c_write_buff[0] = BME280_ID_REG;
    I2C1_WriteRead(BME280_ADDR, i2c_write_buff, 1, i2c_read_buff, 1);
    while( I2C1_IsBusy() );
    bme280_id = i2c_read_buff[0];
    return I2C1_ErrorGet();
}

uint8_t BME280_reset(void) {
    i2c_write_buff[0] = BME280_RESET_REG;
    i2c_write_buff[1] = BME280_SOFT_RESET;
    I2C1_Write(BME280_ADDR, i2c_write_buff, 2);
    while( I2C1_IsBusy() );
    return I2C1_ErrorGet();
}

uint8_t BME280_sleep(void) {
    bme280_ctrl_meas.mode = BME280_SLEEP_MODE;
    i2c_write_buff[0] = BME280_CTRL_MEAS_REG;
    i2c_write_buff[1] = bme280_ctrl_meas.ctrlMeasReg;
    I2C1_Write(BME280_ADDR, i2c_write_buff, 2);
}

void BME280_readFactoryCalibrationParams(void) {
    i2c_write_buff[0] = BME280_CALIB_DT1_LSB_REG;
    I2C1_WriteRead(BME280_ADDR, i2c_write_buff, 1, i2c_read_buff, 24);
    while( I2C1_IsBusy() );
    calibParam.dig_T1 = (((uint16_t) i2c_read_buff[1]) << 8) + i2c_read_buff[0];
    calibParam.dig_T2 = (((int) i2c_read_buff[3]) << 8) + i2c_read_buff[2];
    calibParam.dig_T3 = (((int) i2c_read_buff[5]) << 8) + i2c_read_buff[4];
    calibParam.dig_P1 = (((uint16_t) i2c_read_buff[7]) << 8) + i2c_read_buff[6];
    calibParam.dig_P2 = (((int) i2c_read_buff[9]) << 8) + i2c_read_buff[8];
    calibParam.dig_P3 = (((int) i2c_read_buff[11]) << 8) + i2c_read_buff[10];
    calibParam.dig_P4 = (((int) i2c_read_buff[13]) << 8) + i2c_read_buff[12];
    calibParam.dig_P5 = (((int) i2c_read_buff[15]) << 8) + i2c_read_buff[14];
    calibParam.dig_P6 = (((int) i2c_read_buff[17]) << 8) + i2c_read_buff[16];
    calibParam.dig_P7 = (((int) i2c_read_buff[19]) << 8) + i2c_read_buff[18];
    calibParam.dig_P8 = (((int) i2c_read_buff[21]) << 8) + i2c_read_buff[20];
    calibParam.dig_P9 = (((int) i2c_read_buff[23]) << 8) + i2c_read_buff[22];

    i2c_write_buff[0] = BME280_CALIB_DH1_REG;
    calibParam.dig_H1 = (uint8_t) I2C1_WriteRead(BME280_ADDR, i2c_write_buff, 1, i2c_read_buff, 1);
    while( I2C1_IsBusy() );

    i2c_write_buff[0] = BME280_CALIB_DH2_LSB_REG;
    I2C1_WriteRead(BME280_ADDR, i2c_write_buff, 1, i2c_read_buff, 7);
    while( I2C1_IsBusy() );
    
    calibParam.dig_H2 = (((int) i2c_read_buff[1]) << 8) + i2c_read_buff[0];
    calibParam.dig_H3 = (uint8_t) i2c_read_buff[2];
    calibParam.dig_H4 = (((int) i2c_read_buff[3]) << 4) | (i2c_read_buff[4] & 0xF);
    calibParam.dig_H5 = (((int) i2c_read_buff[5]) << 4) | (i2c_read_buff[4] >> 4);
    calibParam.dig_H6 = (short) i2c_read_buff[6];
}

void BME280_config(uint8_t sbtime, uint8_t coeff) {
    bme280_config.t_sb = sbtime; // Set standby time;
    bme280_config.filter = coeff; // Set filter coefficient;
}

void BME280_ctrl_meas(uint8_t osrs_T, uint8_t osrs_P, uint8_t mode) {
    bme280_ctrl_meas.osrs_T = osrs_T; // Set oversampling temperature;
    bme280_ctrl_meas.osrs_P = osrs_P; // Set oversampling pressure;
    bme280_ctrl_meas.mode = mode; // Set sensor mode;
}

void BME280_ctrl_hum(uint8_t osrs_H) {
    bme280_ctrl_hum = osrs_H; // Set oversampling humidity;
}

void BME280_initializeSensor(void) {
    
    i2c_write_buff[0] = BME280_CONFIG_REG;
    i2c_write_buff[1] = bme280_config.configReg;
    I2C1_Write(BME280_ADDR, i2c_write_buff, 2);
    while( I2C1_IsBusy() );
    
    i2c_write_buff[0] = BME280_CTRL_HUM_REG;
    i2c_write_buff[1] = bme280_ctrl_hum;
    I2C1_Write(BME280_ADDR, i2c_write_buff, 2);
    while( I2C1_IsBusy() );
    
    i2c_write_buff[0] = BME280_CTRL_MEAS_REG;
    i2c_write_buff[1] = bme280_ctrl_meas.ctrlMeasReg;
    I2C1_Write(BME280_ADDR, i2c_write_buff, 2);
    while( I2C1_IsBusy() );
}

void BME280_startForcedSensing(void) {
    bme280_ctrl_meas.mode = BME280_FORCED_MODE;
    
    i2c_write_buff[0] = BME280_CTRL_MEAS_REG;
    i2c_write_buff[1] = bme280_ctrl_meas.ctrlMeasReg;
    I2C1_Write(BME280_ADDR, i2c_write_buff, 2);
    while( I2C1_IsBusy() );
}

void BME280_readMeasurements(void) {
    uint8_t sensorData[BME280_DATA_FRAME_SIZE];
    i2c_write_buff[0] = BME280_PRESS_MSB_REG;
    I2C1_WriteRead(BME280_ADDR, i2c_write_buff, 1, sensorData, BME280_DATA_FRAME_SIZE);
    while( I2C1_IsBusy() );

    adc_H = ((uint32_t) sensorData[BME280_HUM_MSB] << 8) |
            sensorData[BME280_HUM_LSB];

    adc_T = ((uint32_t) sensorData[BME280_TEMP_MSB] << 12) |
            (((uint32_t) sensorData[BME280_TEMP_LSB] << 4) |
            ((uint32_t) sensorData[BME280_TEMP_XLSB] >> 4));

    adc_P = ((uint32_t) sensorData[BME280_PRESS_MSB] << 12) |
            (((uint32_t) sensorData[BME280_PRESS_LSB] << 4) |
            ((uint32_t) sensorData[BME280_PRESS_XLSB] >> 4));
}

float BME280_getTemperature(void) {
    float temperature = (float) BME280_compensateTemperature() / 100;
    return temperature;
}

float BME280_getPressure(void) {
    float pressure = (float) BME280_compensatePressure() / 1000;
    pressure = pressure * 0.295301;
    return pressure;
}

float BME280_getHumidity(void) {
    float humidity = (float) BME280_compensateHumidity() / 1024;
    return humidity;
}

/* 
 * Returns temperature in DegC, resolution is 0.01 DegC. 
 * Output value of "5123" equals 51.23 DegC.  
 */
static uint32_t BME280_compensateTemperature(void) {
    long tempV1, tempV2, t;

    tempV1 = ((((adc_T >> 3) - ((long) calibParam.dig_T1 << 1))) * ((long) calibParam.dig_T2)) >> 11;
    tempV2 = (((((adc_T >> 4) - ((long) calibParam.dig_T1)) * ((adc_T >> 4) - ((long) calibParam.dig_T1))) >> 12)*((long) calibParam.dig_T3)) >> 14;
    t_fine = tempV1 + tempV2;
    t = (t_fine * 5 + 128) >> 8;

    return t;
}

/* 
 * Returns pressure in Pa as unsigned 32 bit integer. 
 * Output value of "96386" equals 96386 Pa = 96.386 kPa 
 */
static uint32_t BME280_compensatePressure(void) {
    long pressV1, pressV2;
    uint32_t p;

    pressV1 = (((long) t_fine) >> 1) - (long) 64000;
    pressV2 = (((pressV1 >> 2) * (pressV1 >> 2)) >> 11) * ((long) calibParam.dig_P6);
    pressV2 = pressV2 + ((pressV1 * ((long) calibParam.dig_P5)) << 1);
    pressV2 = (pressV2 >> 2)+(((long) calibParam.dig_P4) << 16);
    pressV1 = (((calibParam.dig_P3 * (((pressV1 >> 2) * (pressV1 >> 2)) >> 13)) >> 3) +
            ((((long) calibParam.dig_P2) * pressV1) >> 1)) >> 18;
    pressV1 = ((((32768 + pressV1))*((long) calibParam.dig_P1)) >> 15);

    if (pressV1 == 0) {
        // avoid exception caused by division by zero
        return 0;
    }

    p = (((uint32_t) (((long) 1048576) - adc_P)-(pressV2 >> 12)))*3125;
    if (p < 0x80000000) {
        p = (p << 1) / ((uint32_t) pressV1);
    } else {
        p = (p / (uint32_t) pressV1) * 2;
    }

    pressV1 = (((long) calibParam.dig_P9) * ((long) (((p >> 3) * (p >> 3)) >> 13))) >> 12;
    pressV2 = (((long) (p >> 2)) * ((long) calibParam.dig_P8)) >> 13;
    p = (uint32_t) ((long) p + ((pressV1 + pressV2 + calibParam.dig_P7) >> 4));

    return p;
}

static uint32_t BME280_compensateHumidity(void) {
    long humV;
    uint32_t h;

    humV = (t_fine - ((long) 76800));
    humV = (((((adc_H << 14) - (((long) calibParam.dig_H4) << 20) - (((long) calibParam.dig_H5) * humV)) +
            ((long) 16384)) >> 15) * (((((((humV * ((long) calibParam.dig_H6)) >> 10) *
            (((humV * ((long) calibParam.dig_H3)) >> 11) + ((long) 32768))) >> 10) +
            ((long) 2097152)) * ((long) calibParam.dig_H2) + 8192) >> 14));
    humV = (humV - (((((humV >> 15) * (humV >> 15)) >> 7) * ((long) calibParam.dig_H1)) >> 4));
    humV = (humV < 0 ? 0 : humV);
    humV = (humV > 419430400 ? 419430400 : humV);

    h = (uint32_t) (humV >> 12);
    return h;
}