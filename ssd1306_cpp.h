#ifndef _SSD1306_CPP_H_
#define _SSD1306_CPP_H_

// SSD1306 Driver by AZO

#include "ssd1306.h"

typedef void (*SSD1306_I2C_BeginTransmission_t)(const uint8_t u8I2CAddress);
typedef void (*SSD1306_I2C_Write_t)(const uint8_t u8Value);
typedef void (*SSD1306_I2C_EndTransmission_t)(void);

// SPI Wire mode 4 or 3
#define SSD1306_SPI_WIRE 4

typedef void (*SSD1306_SPI_SetPinIO_t)(const uint8_t u8Pin, const uint8_t u8IOMode);
typedef void (*SSD1306_SPI_PinOutput_t)(const uint8_t u8Pin, const bool bHigh);
typedef void (*SSD1306_SPI_Transfer_t)(const uint8_t u8Data);
typedef void (*SSD1306_DelayMS_t)(const uint16_t u16MS);

class SSD1306 {
public:
  SSD1306(void);
#ifndef SSD1306_FRAMEBUFFER_STATIC
  ~SSD1306_(void);
#endif  // SSD1306_FRAMEBUFFER_STATIC

  // subclass must implement initialise()

  bool initDevice(void);

  bool clear(void);
  bool getPixel(uint8_t* pu8Pixel, const uint8_t u8X, const uint8_t u8Y);
  bool getSeg(uint8_t* pu8Pattern, const uint8_t u8X, const uint8_t u8Seg);
  bool setSeg(const uint8_t u8X, const uint8_t u8Seg, const uint8_t u8Pattern);

  bool drawPixel(const uint8_t u8X, const uint8_t u8Y, const uint8_t u8Color);
  bool drawLine(
    const int16_t i16X1,
    const int16_t i16Y1,
    const int16_t i16X2,
    const int16_t i16Y2,
    const uint8_t u8Color
  );
  bool drawRectangle(
    const int16_t i16X1,
    const int16_t i16Y1,
    const int16_t i16X2,
    const int16_t i16Y2,
    const uint8_t u8Color,
    const bool bFill,
    const uint8_t u8FillColor
  );
  bool drawCircle(
    const int16_t i16X,
    const int16_t i16Y,
    const int16_t i16R,
    const uint8_t u8Color,
    const bool bFill,
    const uint8_t u8FillColor
  );
  bool isInvert(void);
  void setInvert(const bool bInvert);

  bool refresh(void);

  bool isScroll(void);
  bool HScroll(const bool bLeft, const uint8_t u8StartPage, const uint8_t u8Intreval, const uint8_t u8EndPage);
  bool VHScroll(const bool bLeft, const uint8_t u8StartPage, const uint8_t u8Intreval, const uint8_t u8EndPage, const uint8_t u8Offset);
  bool disableScroll(void);

  bool isSleep(void);
  bool sleep(void);
  bool wakeup(void);

  /* Access (Don't use) */
  static void gen_write(void* pSSD1306, const SSD1306_Write_Data_t* ptWriteData);

protected:
  SSD1306_t tSSD1306;
};

class SSD1306_I2C : public SSD1306 {
public:
  SSD1306_I2C(void);

  // MaxX and MaxY must be multiples of 8
  bool initialize(
    const SSD1306_I2C_BeginTransmission_t tBeginTransmission,
    const SSD1306_I2C_Write_t             tWrite,
    const SSD1306_I2C_EndTransmission_t   tEndTransmission,
    const SSD1306_MemoryBarrier_t         tMemoryBarrier,
    void** ppLock,
    const uint8_t u8I2CAddress,
    const uint8_t u8MaxX,
    const uint8_t u8MaxY,
    const uint8_t u8Contrast
  );

  uint8_t setI2CAddress(const uint8_t u8I2CAddress);
  uint8_t getI2CAddress(void);

  static void gen_write(void* pSSD1306_I2C, const SSD1306_Write_Data_t* ptWriteData);

private:
  SSD1306_I2C_BeginTransmission_t tBeginTransmission;
  SSD1306_I2C_Write_t             tWrite;
  SSD1306_I2C_EndTransmission_t   tEndTransmission;

  uint8_t u8I2CAddress;
};

class SSD1306_SPI : public SSD1306 {
public:
  SSD1306_SPI(void);

  // MaxX and MaxY must be multiples of 8
  bool initialize(
    const SSD1306_SPI_SetPinIO_t  tSetPinIO,
    const SSD1306_SPI_PinOutput_t tPinOutput,
    const SSD1306_SPI_Transfer_t  tTransfer,
    const SSD1306_DelayMS_t       tDelayMS,
    const SSD1306_MemoryBarrier_t tMemoryBarrier,
    void** ppLock,
    const uint8_t u8CS,
    const uint8_t u8RST,
#if SSD1306_SPI_WIRE == 4
    const uint8_t u8DC,
#endif
    const uint8_t u8MaxX,
    const uint8_t u8MaxY,
    const uint8_t u8Contrast
  );

  void setCS(const uint8_t u8CS);
  uint8_t getCS(void);
  void setRST(const uint8_t u8RST);
  uint8_t getRST(void);
#if SSD1306_SPI_WIRE == 4
  void setDC(const uint8_t u8DC);
  uint8_t getDC(void);
#endif

  static void gen_write(void* pSSD1306_SPI, const SSD1306_Write_Data_t* ptWriteData);

private:
  SSD1306_t tSSD1306;

  uint8_t u8CS;
  uint8_t u8RST;
#if SSD1306_SPI_WIRE == 4
  uint8_t u8DC;
#endif

  SSD1306_SPI_SetPinIO_t  tSetPinIO;
  SSD1306_SPI_PinOutput_t tPinOutput;
  SSD1306_SPI_Transfer_t  tTransfer;
  SSD1306_DelayMS_t       tDelayMS;
};

#endif  /* _SSD1306_CPP_H_ */

