# Arduino Library `TA.Arduino.Timer`

## Description

This library is a simple, easy-to-use timer utility with emphasis on ease of use.
The utility is perfect for timing "human scale time intervals" of up to 49.7 days.
The maximum duration is governed by the size of the Arduino `millis()` counter, which "rolls over" (resets to zero) about every 49.7 days.
The utility correctly implements the circular arithmetic required so that timers work correctly even if the `millis()` count rolls over, so your code will not mysteriously fail when this happens.

The timer resolution is 1 millisecond, but timing accuracy depends on how often the timer is checked within user code.
Typically, a timer will be checked once each time around the main loop, therefore the accuracy typically depends on the execution time of the main loop.
If the main loop takes 10 milliseconds to execute, then the timer accuracy will be no better than 10 milliseconds, on average.

This makes `TA.Arduino.Timer` great for implementing timouts and controlling user interface elements, where accuracy to within a few milliseconds or tens of milliseconds is sufficient.

This type of timer is not great for producing very accurately timed events or signals or for maintaining accurate timing over a long period of time. High accuracy timing is probably best done using a hardware counter-timer and possibly an interrupt service routine.

## Theory of Operation

The `Timer` class works by taking and storing a "snapshot" of the `millis()` counter at the moment it is started. This happens when the _duration_ is set to a nonzero value.

Subsequently, each time the timer is queried, is computes _elapsed time_ by fetching the current value of `millis()` and subtracting the start value using unsigned aritmetic, which works correctly even if the counter has "rolled over".

Once the elapsed time is found, it can be determined whether the timer has _expired_ by simply comparing to the configured duration.

A timer is _started_ by calling `setDuration()` with a nonzero duration.

A timer is _stopped_ by setting the duration to zero, or calling the `stop()` method.

A timer is said to be _enabled_ whenever it has a nonzero duration.

A timer is said to be _expired_ whenever it is _enabled_ AND the elapsed time is equal or greater than the configured duration.

## Interfact contract

The `Timer` class has the following methods (please refer to source code for further information):

| Method | Description |
|---|---|
| void setDuration(Duration) | Sets the timer duration and starts the timer |
| bool expired() | Returns `true` if the timer interval has expired, `false` otherwise |
| Duration elapsed() | Returns the time duration elapsed since the timer was started |
| Duration remaining() | Returns the time remaining until the timer expires |
| bool enabled() | returns `true` if the timer is running (has a nonzero duration), `false` otherwise |
| void stop() | Stops the timer by clearing its duration to zero.|

# Using a Timer

Timers are simple to use.

1. Declare a timer object, usually as a global item at the top of your Arduino sketch. You can also declare duration constants if you wish.
```lang=cpp
Timer myTimer;
const Duration repeatInterval = Timer::Seconds(5);
```

2. Set the duration to be timed. This can be done in the `setup()` method or anywhere in code as needed.
```lang-cpp
void setup()
    {
    myTimer.setDuration(Timer::Seconds(10));
    }
```

Note that the `Timer::` namespace declares a few useful _constant expressions_ for specifying the timer duration:
- `Timer::Days(n)`
- `Timer::Hours(n)`
- `Timer::Minutes(n)`
- `Timer::Seconds(n)`
- `Timer::Milliseconds(n)`

3. Periodically check whether the timer has expired, usually in your main loop.
```lang=cpp
void loop()
    {
    if (myTimer.expired())
        {
        // Whatever code is necessary.
        // Finally, restart the timer if needed (or alternatively stop it).
        myTimer.setDuration(repeatInterval)    
        }
    }
```

For more advanced uses, please see the source code.
