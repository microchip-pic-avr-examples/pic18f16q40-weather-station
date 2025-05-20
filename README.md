<a href="https://www.microchip.com" rel="nofollow"><img src="images/microchip.png" alt="MCHP" width="300"/></a>

# Creating a Weather Station Using the PIC18F16Q40 Microcontroller

## Introduction 

The pic18f16q40-weather-station project highlights the advanced communications peripherals found on the PIC18-Q40 family of devices to create a PIC18 powered weather station. The I2C module was used to interface a Bosch BME280 Weather Sensor to provide real-time measurements for temperature, relative humidity, and atmospheric pressure. This project also implements the 12-bit Analog-to-Digital (ADC) Converter with Computation to interface an analog ambient light sensor which was used to measure light intensity. The Serial Peripheral Interface (SPI) module was used to drive an OLED display that shows the weather station output values in real time, and the UART module was used to also display the weather station output values over a serial port in real time.

## Software Used
  - [MPLAB® X IDE 6.25 or newer](http://www.microchip.com/mplab/mplab-x-ide)
  - [MPLAB® XC8 3.0 or a newer compiler](http://www.microchip.com/mplab/compilers)
  - [MPLAB® Code Configurator (MCC) 5.7.1 or newer](https://www.microchip.com/mplab/mplab-code-configurator)
  - [Microchip PIC18F-Q Series Device Support 1.28.451 or newer](https://packs.download.microchip.com/)

## Hardware Used
  - [PIC18F16Q40 Microcontroller](https://www.microchip.com/wwwproducts/en/PIC18F16Q40)
  - [Curiosity Low Pin Count (LPC) Development Board](https://www.microchip.com/DevelopmentTools/ProductDetails/DM164137)     
  - [MikroElektronika Weather Click Board](https://www.mikroe.com/weather-click)
  - [MikroElektronika Ambient Click Board](https://www.mikroe.com/ambient-click)      
  - [MikroElektronika OLED C Click Board](https://www.mikroe.com/oled-c-click)         

## Demo Configuration
The Curiosity Low Pin Count (LPC) Development Board was selected as the development platform for this code example. The weather station display was implemented using the MikroElektronika OLEDC Click board, the Bosch BME280 weather sensor was provided using the MikroElektronika Weather Click Board, and the ambient light sensor was provided using the MikroElektronika Ambient Click Board. The Curiosity LPC Development Board only has one MikroBUS&#x2122; socket which was used for the OLED display, so the other two sensor boards (Ambient Click and Weather Click) were connected using a breadboard and jumper wires. The jumper wire connections needed to connect the sensors on the breadboard to the PIC18F16Q40 on the Curiosity LPC Development Board are the following:

- Yellow wires: Connections between SDA/SCL on the Weather Click for I2C communication, to the corresponding SDA and SCL pins on the Curiosity LPC development board
  
    **Note**: Resistors R55 and R53 must be removed from   the back of the Curiosity LPC development board to disconnect the SPI SCK and MISO signals from the existing pins and re-route them to the pins described below


- Green wire: Connection between the analog output of the Ambient Click Board to the corresponding positive ADC channel on the PIC microcontroller

- Orange wire: Connection from UART Tx pin (RB7) of the PIC18F16Q40 to the Tx connection of the Curiosity LPC Virtual COM port for serial communication.

- Red wire: Connection from 3.3V of the Curiosity LPC Development Board to the power supply rail of the breadboard where the sensors are placed

- Black wire: Connection from ground of the Curiosity board to the ground rail of the breadboard

The following table summarizes the signal connections used in this code example:

|Signal                    | Microcontroller Pin     |
|------------------------- | :--------------------: |
|UART TX	                 | RB7                    |
|Weather Click – SDA (I2C) | RB4                    |
|Weather Click – SCL (I2C) | RB6                    |
|OLEDC Click – SDO (SPI)	 | RC7                    |
|OLEDC Click – SDI (SPI)	 | RC0                    |
|OLEDC Click – SCK (SPI)	 | RC1                    |
|OLEDC Click – CS (SPI)	   | RC6                    |
|OLEDC Click – DC	         | RC5                    |
|OLEDC Click – EN	         | RA2                    |
|OLEDC Click – RST	       | RA4                    |
|OLEDC Click – RW	         | RC2                    |
|Ambient Click Output      | RB5                    |

### Curiosity LPC Project Setup
<img src="images/weather-station.jpg" alt="MCHP" width="750"/></a>

## I2C Module Configuration
The I2C module was used in this code example to communicate with the Bosch BME280 weather sensor to measure temperature, pressure, and relative humidity. For this example, the I2C module was initialized using the MPLAB Code Configurator (MCC). The I2C was configured to operate with a standard clock speed of 100 kHz, and external pull-up resistors were used on both the SDA and SCL pins. The slave address of the BME280 weather sensor was 0x76. The temperature, pressure, and humidity measurements were acquired from the Bosch BME280 weather sensor as raw uncompensated outputs.

### BME280 Weather Sensor Compensation Routines
The I2C module was used in this example to read the temperature, pressure, and humidity from the BME280 sensor. The temperature and pressure are read as 20-bit unsigned values, and the relative humidity is read as a 16-bit signed value. These sensor measurements obtained using the I2C module are raw data measurements from the weather sensor, and compensation routines must be used to convert the raw sensor outputs to values that can be used for display. The BME280 weather sensor has a set of compensation parameters stored in the device memory that must be read and stored by the PIC microcontroller. These compensation parameters are all used in the conversion routines to properly convert the raw sensor output to the final output results. The compensation routines used to convert the BME280 raw outputs to temperature in degrees Celsius, atmospheric pressure in inches of mercury, and relative humidity as a percentage are shown below.

### Temperature Compensation Routines (°C)
```c
static uint32_t BME280_compensateTemperature(void) {
    long tempV1, tempV2, t;

    tempV1 = ((((adc_T >> 3) - ((long) calibParam.dig_T1 << 1))) * ((long) calibParam.dig_T2)) >> 11;
    tempV2 = (((((adc_T >> 4) - ((long) calibParam.dig_T1)) * ((adc_T >> 4) - ((long) calibParam.dig_T1))) >> 12)*((long) calibParam.dig_T3)) >> 14;
    t_fine = tempV1 + tempV2;
    t = (t_fine * 5 + 128) >> 8;
    t = t / 100;
    return t;
}
```

### Atmospheric Pressure Compensation Routine (inHg)
```c
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

```

### Relative Humidity Compensation Routine (%)
```c
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
```


## ADC With Computation Module Configuration
The ADC with Computation was used in this code example to measure the output of the ambient light sensor. This peripheral was configured in Burst-Average mode for this sensor interface, which allows the ADC to perform a pre-determined burst of conversions while accumulating the conversion results while being core independent. In Burst-Average mode, once the specified number of conversions have been completed, the accumulated sum of the conversion results is then right shifted (or divided) by the specified number of bits by the ADC hardware. The purpose of this hardware feature is to allow the ADC to perform averaging without any software intervention. The right shifted result can be read from the ADFLTR register.

The ADC conversion result was then used to calculate the ambient light intensity in µW/cm2 using the characteristic curve provided in the sensor data sheet. The following code snippet shows the firmware used to perform the burst-average conversion on the ambient light sensor output, and the compensation routine used to convert the raw analog value to light intensity. The MPLAB Code Configurator was used to quickly and easily setup of the ADC with Computation module for this sensor interface. The setup and configuration of the ADC with Computation using MCC is shown in the figure below. The ADC with Computation was configured to perform 32 burst average conversions and then right shift them by 5 (divide by 32).

### ADC Settings
#### Hardware Settings
| Setting                      | Value     |
|------------------------------|-----------|
| Enable ADC                   |  Enabled  |
| Result Alignment             | Right     | 
| Positive Input Channel       | ANB5      | 
| Positive Voltage Reference   |   FVR     | 
| Negative Voltage Reference   |   VSS     | 
| Auto-Conversion Trigger      |  Disabled | 

#### Computation Settings 
| Setting                  | Value             |
|--------------------------|-------------------|
| Computation Mode         | Burst_average_mode|
| Sample Repeat Count      | 32                |
| Threshold Interrupt Mode | Enabled           |
| Accumulator Right Shift  | 5                 |

#### Clock Settings
| Setting             |   Value           |
|---------------------|-------------------|
| Clock Source        |  FOSC             |
| Clock Divider       |  FOSC/8           |

### Ambient Light Sensor Acquisition & Compensation
```c
float Ambient_ReadSensor(void) {
    ADC_ConversionStart();
    while( 0 == ADC_IsConversionDone() );
    while( 0 == ADC_IsThresholdInterruptFlagSet() );
    return ADC_FilterValueGet();
}

float AmbientCompensation(void) {

  #define ADCC_RESOLUTION         4096
  #define ADCC_POS_REFERENCE      4.096
  #define POLY1_TERM1             147.2
  #define POLY1_TERM0             -9.5  

  float Ambient_Raw, Ambient_Volt, Light_Intensity;
  Ambient_Raw = Ambient_ReadSensor();
  // Calculate ADC voltage using conversion result;
  Ambient_Volt = (Ambient_Raw / ADCC_RESOLUTION) * ADCC_POS_REFERENCE;
  Light_Intensity = (POLY1_TERM1 * Ambient_Volt) + POLY1_TERM0; // Calculate ambient light intensity;
  return (Light_Intensity); // Return light intensity (uW/cm^2);
}
```
## SPI Module Configuration
The SPI module was used in this code example to communicate with the OLED display to show the real-time weather station output results.

### SPI Settings
|   Setting             |  Value       |
|-----------------------|--------------|
| Requested Speed (kHz) | 2000         |
| Mode                  | Mode 0       |
| Data Input Sampled At | Middle       |


## UART Module Configuration
The UART module was used in this code example as an alternative way of displaying the weather station output results by printing the temperature, pressure, humidity, and ambient light intensity periodically using a serial port. The UART module was configured using MCC in Asynchronous 8-bit mode with a baud rate of 9600 baud. Transmission and reception were both enabled, and the “Redirect STDIO to UART” checkbox was selected under the **software settings** tab to include the library needed for “printf” functions. The UART TX pin was selected as pin RB7 and connected to the TX pin of the Virtual COM port on the Curiosity LPC Development Board (orange wire).

## Weather Station Serial Port Output Results
<img src="images/uart-output.PNG" alt="MCHP" width="750"/></a>

## Weather Station OLED Display Output Results
<img src="images/weather-station.gif" alt="MCHP" width="750"/></a>

## Summary
This code example shows how various features of the PIC18F16Q40 microcontroller can be used to make a weather station. The ADC with Computation was used to sample an ambient light sensor while peforming averaging of the signal in hardware. The I2C peripheral was used to communicate with a temperture/humidity sensor, and the SPI peripheral was used to communicate with an OLED display to show all of the results. 