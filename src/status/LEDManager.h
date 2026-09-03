/*
	SlimeVR Code is placed under the MIT license
	Copyright (c) 2022 TheDevMinerTV

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.
*/
#ifndef SLIMEVR_LEDMANAGER_H
#define SLIMEVR_LEDMANAGER_H

#include <Arduino.h>

#include "../globals.h"
#include "../logging/Logger.h"

#define DEFAULT_LENGTH 300
#define DEFAULT_GAP 500
#define DEFAULT_INTERVAL 3000

#define STANDBUY_LENGTH DEFAULT_LENGTH
#define IMU_ERROR_LENGTH DEFAULT_LENGTH
#define IMU_ERROR_INTERVAL 1000
#define IMU_ERROR_COUNT 5
#define LOW_BATTERY_LENGTH DEFAULT_LENGTH
#define LOW_BATTERY_INTERVAL 300
#define LOW_BATTERY_COUNT 1
#define WIFI_CONNECTING_LENGTH DEFAULT_LENGTH
#define WIFI_CONNECTING_INTERVAL 3000
#define WIFI_CONNECTING_COUNT 3
#define SERVER_CONNECTING_LENGTH DEFAULT_LENGTH
#define SERVER_CONNECTING_INTERVAL 3000
#define SERVER_CONNECTING_COUNT 2

// Only used on boards with an addressable RGB status LED (LED_BUILTIN aliased
// to RGB_BUILTIN by the board variant, e.g. ESP32-S3 Supermini). Colors are
// plain 0-255 RGB; brightness is a global 0-255 scaler applied on top so you
// don't have to dim every color macro individually.
#ifndef RGB_LED_BRIGHTNESS
#define RGB_LED_BRIGHTNESS 32
#endif

#define COLOR_DEFAULT 255, 255, 255  // used by generic on()/blink()/pattern() calls
#define COLOR_STANDBY 0, 255, 0  // idle heartbeat pulse
#define COLOR_LOW_BATTERY 255, 60, 0
#define COLOR_IMU_ERROR 255, 0, 0
#define COLOR_WIFI_CONNECTING 0, 60, 255
#define COLOR_SERVER_CONNECTING 200, 0, 255

namespace SlimeVR {
enum LEDStage { OFF, ON, GAP, INTERVAL };

class LEDManager {
public:
	void setup();
    void SleepySlime();
	/*!
	 *  @brief Turns the LED on
	 */
	void on();

	/*!
	 *  @brief Turns the LED off
	 */
	void off();

	/*!
	 *  @brief Blink the LED for [time]ms. *Can* cause lag
	 *  @param time Amount of ms to turn the LED on
	 */
	void blink(unsigned long time);

	/*!
	 *  @brief Show a pattern on the LED. *Can* cause lag
	 *  @param timeon Amount of ms to turn the LED on
	 *  @param timeoff Amount of ms to turn the LED off
	 *  @param times Amount of times to display the pattern
	 */
	void pattern(unsigned long timeon, unsigned long timeoff, int times);

	void update();

	/*!
	 *  @brief Set the color used by the next on()/blink()/pattern() call.
	 *  Harmless no-op effect on boards without an RGB status LED.
	 *  @param r,g,b 0-255 color components (pre-brightness-scaling)
	 */
	void setColor(uint8_t r, uint8_t g, uint8_t b);

private:
	uint8_t m_CurrentCount = 0;
	unsigned long m_Timer = 0;
	LEDStage m_CurrentStage = OFF;
	unsigned long m_LastUpdate = millis();

	uint8_t m_Pin = LED_PIN;
	bool m_Enabled = m_Pin >= 0 && m_Pin < LED_OFF;
	bool m_On = LED_INVERTED ? LOW : HIGH;
	bool m_Off = !m_On;

	uint8_t m_ColorR = 255;
	uint8_t m_ColorG = 255;
	uint8_t m_ColorB = 255;

	Logging::Logger m_Logger = Logging::Logger("LEDManager");
};
}  // namespace SlimeVR

#endif
