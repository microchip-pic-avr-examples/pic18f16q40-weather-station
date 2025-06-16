 /*
     (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
 */

#include <stdint.h>
#include <stdbool.h>
#include "oledC.h"
#include "../mcc_generated_files/system/system.h"

enum STREAMING_MODES 
{
    NOSTREAM, WRITESTREAM, READSTREAM
};
static uint8_t streamingMode = NOSTREAM;

static void startStreamingIfNeeded(OLEDC_COMMAND cmd);
static void stopStreaming(void);
static uint16_t exchangeTwoBytes(uint8_t byte1, uint8_t byte2);

oledc_color_t oledC_parseIntToRGB(uint16_t raw)
{
    oledc_color_t parsedColor;
    uint8_t byte1 = raw >> 8;
    uint8_t byte2 = raw & 0xFF;
    parsedColor.red = (byte1 >> 3);
    parsedColor.green = ((byte1 & 0x7) << 3) | (byte2 >> 5);
    parsedColor.blue = byte2 & 0x1F;
    return parsedColor;
}

uint16_t oledC_parseRGBToInt(uint8_t red, uint8_t green, uint8_t blue)
{
    red &= 0x1F;
    green &= 0x3F;
    blue &= 0x1F;
    uint8_t byte1;
    uint8_t byte2;
    byte1 = (red << 3) | (green >> 3);
    byte2 = (green << 5) | blue;
    return (((uint16_t)byte1) << 8) | byte2;
}

static void startStreamingIfNeeded(OLEDC_COMMAND cmd)
{
    if(cmd == OLEDC_CMD_WRITE_RAM || cmd == OLEDC_CMD_READ_RAM)
    {
        streamingMode = cmd == OLEDC_CMD_WRITE_RAM ? WRITESTREAM : READSTREAM;
    } 
    else 
    {
        streamingMode = NOSTREAM;
    }
}

static void stopStreaming(void)
{
    streamingMode = NOSTREAM;
}

void oledC_sendCommand(OLEDC_COMMAND cmd, uint8_t *payload, uint8_t payload_size)
{
    
    oledC_nCS_SetLow(); 
    oledC_DC_SetLow(); 
    SPI1_ByteWrite(cmd);
    if(payload_size > 0)
    {
        oledC_DC_SetHigh(); 
        SPI1_BufferExchange(payload, payload_size);
        oledC_DC_SetLow(); 
    }
    oledC_nCS_SetHigh(); 
    startStreamingIfNeeded(cmd);
}

void oledC_setRowAddressBounds(uint8_t min, uint8_t max)
{
    uint8_t payload[2];
    payload[0] = min > 95 ? 95 : min;
    payload[1] = max > 95 ? 95 : max;
    oledC_sendCommand(OLEDC_CMD_SET_ROW_ADDRESS, payload, 2);
    
}

void oledC_setColumnAddressBounds(uint8_t min, uint8_t max)
{
    min = min > 95 ? 95 : min;
    max = max > 95 ? 95 : max;
    uint8_t payload[2];
    payload[0] = 16+min;
    payload[1] = max + 16;
    oledC_sendCommand(OLEDC_CMD_SET_COLUMN_ADDRESS, payload, 2);
}

void oledC_setSleepMode(bool on)
{
    oledC_sendCommand(on ? OLEDC_CMD_SET_SLEEP_MODE_ON : OLEDC_CMD_SET_SLEEP_MODE_OFF, NULL, 0);
}

void oledC_setDisplayOrientation(void) 
{
    uint8_t payload[1];
    payload[0] = 0x32;
    oledC_sendCommand(OLEDC_CMD_SET_REMAP_DUAL_COM_LINE_MODE, payload, 1);
    payload[0] = 0x20;
    oledC_sendCommand(OLEDC_CMD_SET_DISPLAY_START_LINE, payload, 1);
}

void oledC_startReadingDisplay(void)
{
    oledC_sendCommand(OLEDC_CMD_READ_RAM, NULL, 0);    
    oledC_nCS_SetLow(); /* set oledC_nCS output low */
    oledC_DC_SetHigh(); /* set oledC_DC output high */
}

void oledC_stopReadingDisplay(void)
{
    oledC_stopWritingDisplay();
}

uint16_t oledC_readColor(void)
{
    if(streamingMode != READSTREAM)
    {
        oledC_startReadingDisplay();
    }
    if(streamingMode != READSTREAM)
    {
        return 0xFFFF;
    }
    uint8_t readBuffer[2];
    SPI1_BufferRead(readBuffer, 2);
    return (readBuffer[0] << 8 | readBuffer[1]);
}

void oledC_startWritingDisplay(void)
{
    oledC_sendCommand(OLEDC_CMD_WRITE_RAM, NULL, 0);    
    oledC_nCS_SetLow(); /* set oledC_nCS output low */
    oledC_DC_SetHigh(); /* set oledC_DC output high */
}

void oledC_stopWritingDisplay(void)
{
    oledC_nCS_SetHigh(); /* set oledC_nCS output high */
    oledC_DC_SetLow(); /* set oledC_DC output low */
    stopStreaming();
}

void oledC_sendColor(uint8_t r, uint8_t g, uint8_t b)
{
    oledC_sendColorInt(oledC_parseRGBToInt(r,g,b));
}

void oledC_sendColorInt(uint16_t raw)
{
    if(streamingMode != WRITESTREAM)
    {
        oledC_startWritingDisplay();
    }
    if(streamingMode != WRITESTREAM)
    {
        return;
    }
    uint8_t writeBuffer[2];
    writeBuffer[0] = ((raw >> 8)&0xff);
    writeBuffer[1] = (raw & 0xff);
    SPI1_BufferWrite(writeBuffer, 2);
}

void oledC_setup(void)
{
    oledC_EN_SetLow(); /* set oledC_EN output low */
    oledC_RST_SetHigh(); /* set oledC_RST output high */
    oledC_RW_SetLow(); /* set oledC_RW output low */
    __delay_ms(1);
    oledC_RST_SetLow(); /* set oledC_RST output low */
    __delay_us(2);
    oledC_RST_SetHigh(); /* set oledC_RST output high */
    oledC_EN_SetHigh(); /* set oledC_EN output high */
    __delay_ms(1);
    oledC_setSleepMode(false);
    __delay_ms(200);
    oledC_setColumnAddressBounds(0, 95);
    oledC_setRowAddressBounds(0, 95);
    oledC_setDisplayOrientation();
}
