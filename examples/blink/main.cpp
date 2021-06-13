/*
    This example sketch uses the Timer class to blink the built-in LED.
    The duration is chosen so that the LED toggles every 0.5 seconds
    and will therefor blink once per second.
*/

#include <Arduino.h>
#include <Timer.h>

Timer ledTimer;
const Duration ledToggleInterval(Timer::Seconds(0.5));
bool ledState = false;

void setup()
{
    ledTimer.setDuration(ledToggleInterval);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    if (ledTimer.expired())
    {
        ledTimer.setDuration(ledToggleInterval); // timer must be re-loaded after expiring
        ledState = !ledState;
        digitalWrite(LED_BUILTIN, ledState ? HIGH : LOW);
    }
}