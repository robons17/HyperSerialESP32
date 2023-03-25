/* main.cpp
*
*  MIT License
*
*  Copyright (c) 2023 awawa-dev
*
*  https://github.com/awawa-dev/HyperSerialESP32
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in all
*  copies or substantial portions of the Software.

*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*  SOFTWARE.
 */

#include <Arduino.h>
#include <NeoPixelBus.h>

#if !defined(ARDUINO_LOLIN_S2_MINI) && ESP_ARDUINO_VERSION_MAJOR == 2 && ESP_ARDUINO_VERSION_MINOR ==0 && ESP_ARDUINO_VERSION_PATCH <= 5
    #error "Arduino ESP32 versions 2.0.0-2.0.5 are unsupported."
#endif

///////////////////////////////////////////////////////////////////////////
// DO NOT EDIT THIS FILE. ADJUST THE CONFIGURATION IN THE platformio.ini //
///////////////////////////////////////////////////////////////////////////

#define _STR(x) #x
#define _XSTR(x) _STR(x)
#define VAR_NAME_VALUE(var) #var " = " _XSTR(var)
#define _XSTR2(x,y) _STR(x) _STR(y)
#define VAR_NAME_VALUE2(var) #var " = " _XSTR2(var)

#ifdef NEOPIXEL_RGBW
	#pragma message(VAR_NAME_VALUE(NEOPIXEL_RGBW))
#endif
#ifdef NEOPIXEL_RGB
	#pragma message(VAR_NAME_VALUE(NEOPIXEL_RGB))
#endif
#ifdef COLD_WHITE
	#pragma message(VAR_NAME_VALUE(COLD_WHITE))
#endif
#ifdef SPILED_APA102
	#pragma message(VAR_NAME_VALUE(SPILED_APA102))
#endif
#ifdef SPILED_WS2801
	#pragma message(VAR_NAME_VALUE(SPILED_WS2801))
#endif
#pragma message(VAR_NAME_VALUE(SERIALCOM_SPEED))

#if defined(ARDUINO_LOLIN_S2_MINI)
	#ifdef NEOPIXEL_RGBW
		#define LED_DRIVER NeoPixelBus<NeoGrbwFeature, NeoEsp32I2s0Sk6812Method>
	#elif NEOPIXEL_RGB
		#define LED_DRIVER NeoPixelBus<NeoGrbFeature, NeoEsp32I2s0Ws2812xMethod>
	#endif
#else
	#ifdef NEOPIXEL_RGBW
		#define LED_DRIVER NeoPixelBus<NeoGrbwFeature, NeoEsp32I2s1Sk6812Method>
	#elif NEOPIXEL_RGB
		#define LED_DRIVER NeoPixelBus<NeoGrbFeature, NeoEsp32I2s1Ws2812xMethod>
	#endif
#endif

#ifdef SPILED_APA102
	#define LED_DRIVER NeoPixelBus<DotStarBgrFeature, DotStarEsp32DmaHspiMethod>
#elif SPILED_WS2801
	#define LED_DRIVER NeoPixelBus<NeoRbgFeature, NeoWs2801Spi2MhzMethod>
#endif

#pragma message(VAR_NAME_VALUE(DATA_PIN))
#ifdef CLOCK_PIN
	#pragma message(VAR_NAME_VALUE(CLOCK_PIN))
#endif

#if defined(SECOND_SEGMENT_START_INDEX)
	#if defined(NEOPIXEL_RGBW) || defined(NEOPIXEL_RGB)
		#define PARALLEL_MODE
	#endif

	#if defined(PARALLEL_MODE)
		#pragma message("Using parallel mode for segments")
	#endif

	#if defined(ARDUINO_LOLIN_S2_MINI)
		#ifdef NEOPIXEL_RGBW
			#ifdef PARALLEL_MODE
				#undef LED_DRIVER
				#define LED_DRIVER NeoPixelBus<NeoGrbwFeature, NeoEsp32I2s0X8Sk6812Method>
				#define LED_DRIVER2 NeoPixelBus<NeoGrbwFeature, NeoEsp32I2s0X8Sk6812Method>
			#else
				#define LED_DRIVER2 NeoPixelBus<NeoGrbwFeature, NeoEsp32I2s0Sk6812Method>
			#endif
		#elif NEOPIXEL_RGB
			#ifdef PARALLEL_MODE
				#undef LED_DRIVER
				#define LED_DRIVER NeoPixelBus<NeoGrbFeature, NeoEsp32I2s0X8Ws2812Method>
				#define LED_DRIVER2 NeoPixelBus<NeoGrbFeature, NeoEsp32I2s0X8Ws2812Method>
			#else
				#define LED_DRIVER2 NeoPixelBus<NeoGrbFeature, NeoEsp32I2s0Ws2812xMethod>
			#endif
		#elif SPILED_APA102
			#define LED_DRIVER2 NeoPixelBus<DotStarBgrFeature, DotStarEsp32DmaHspiMethod>
		#elif SPILED_WS2801
			#define LED_DRIVER2 NeoPixelBus<NeoRbgFeature, NeoWs2801Spi2MhzMethod>
		#endif
	#else
		#ifdef NEOPIXEL_RGBW
			#ifdef PARALLEL_MODE
				#undef LED_DRIVER
				#define LED_DRIVER NeoPixelBus<NeoGrbwFeature, NeoEsp32I2s1X8Sk6812Method>
				#define LED_DRIVER2 NeoPixelBus<NeoGrbwFeature, NeoEsp32I2s1X8Sk6812Method>
			#else
				#define LED_DRIVER2 NeoPixelBus<NeoGrbwFeature, NeoEsp32I2s0Sk6812Method>
			#endif
		#elif NEOPIXEL_RGB
			#ifdef PARALLEL_MODE
				#undef LED_DRIVER
				#define LED_DRIVER NeoPixelBus<NeoGrbFeature, NeoEsp32I2s1X8Ws2812Method>
				#define LED_DRIVER2 NeoPixelBus<NeoGrbwFeature, NeoEsp32I2s1X8Ws2812Method>
			#else
				#define LED_DRIVER2 NeoPixelBus<NeoGrbFeature, NeoEsp32I2s0Ws2812xMethod>
			#endif
		#elif SPILED_APA102
			#define LED_DRIVER2 NeoPixelBus<DotStarBgrFeature, DotStarEsp32DmaVspiMethod>
		#elif SPILED_WS2801
			#define LED_DRIVER2 NeoPixelBus<NeoRbgFeature, NeoWs2801Spi2MhzMethod>
		#endif
	#endif
	#pragma message(VAR_NAME_VALUE2(LED_DRIVER))
	#pragma message(VAR_NAME_VALUE(SECOND_SEGMENT_START_INDEX))
	#pragma message(VAR_NAME_VALUE(SECOND_SEGMENT_DATA_PIN))
	#ifdef SECOND_SEGMENT_CLOCK_PIN
		#pragma message(VAR_NAME_VALUE(SECOND_SEGMENT_CLOCK_PIN))
	#endif
	#pragma message(VAR_NAME_VALUE2(LED_DRIVER2))
#else
	#pragma message(VAR_NAME_VALUE2(LED_DRIVER))

	class LED_DRIVER2 {
		public:
		bool CanShow() {return true;}
		void Show(bool safe) {}
	};
#endif

#define SerialPort Serial
#include "main.h"

/**
 * @brief separete thread for handling incoming data using cyclic buffer
 *
 * @param parameters
 */
void processDataTask(void * parameters)
{
	for(;;)
	{
		xSemaphoreTake(base.i2sXSemaphore, portMAX_DELAY);
		processData();
	}
}

void processSerialTask(void * parameters)
{
	for(;;)
	{
		if (serialTaskHandler() || base.queueCurrent != base.queueEnd)
			xSemaphoreGive(base.i2sXSemaphore);
		yield();
	}
}

void setup()
{
	bool multicore = true;

	// Init serial port
	Serial.setRxBufferSize(MAX_BUFFER - 1);
	Serial.setTimeout(50);
	Serial.begin(SERIALCOM_SPEED);
	while (!Serial) continue;

	#if defined(NEOPIXEL_RGBW) || defined(NEOPIXEL_RGB)
		#ifdef NEOPIXEL_RGBW
			#ifdef COLD_WHITE
				calibrationConfig.setParamsAndPrepareCalibration(0xFF, 0xA0, 0xA0, 0xA0);
			#else
				calibrationConfig.setParamsAndPrepareCalibration(0xFF, 0xB0, 0xB0, 0x70);
			#endif
		#endif
	#endif

	#if !defined(CONFIG_IDF_TARGET_ESP32S2)
		// Display config
		Serial.println(HELLO_MESSAGE);
		#if defined(SECOND_SEGMENT_START_INDEX)
			SerialPort.write("SECOND_SEGMENT_START_INDEX = ");
			SerialPort.println(SECOND_SEGMENT_START_INDEX);
		#endif

		// Colorspace/Led type info
		#if defined(NEOPIXEL_RGBW) || defined(NEOPIXEL_RGB)
			#ifdef NEOPIXEL_RGBW
				#ifdef COLD_WHITE
					Serial.println("NeoPixelBus SK6812 cold GRBW. ");
				#else
					Serial.println("NeoPixelBus SK6812 neutral GRBW. ");
				#endif
				calibrationConfig.printCalibration();
			#else
				Serial.println("NeoPixelBus ws281x type (GRB).");
			#endif
		#elif defined(SPILED_APA102)
			Serial.println("SPI APA102 compatible type (BGR).");
		#elif defined(SPILED_WS2801)
			Serial.println("SPI WS2801 (RBG).");
		#endif

		//Serial.flush();
		delay(50);
	#endif

	if (multicore)
	{
		// create a semaphore to synchronize threads
		base.i2sXSemaphore = xSemaphoreCreateBinary();


		// create new task for handling received serial data on core 0
		xTaskCreatePinnedToCore(
			processDataTask,
			"processDataTask",
			5096,
			NULL,
			5,
			&base.processDataHandle,
			0);
		// serial handler on core 1
		xTaskCreatePinnedToCore(
			processSerialTask,
			"processSerialTask",
			4096,
			NULL,
			2,
			&base.processSerialHandle,
			1);
	}
}

void loop()
{
	if (base.processDataHandle == nullptr && base.processSerialHandle == nullptr)
	{
		serialTaskHandler();
		processData();
	}
}

