/*
 Name:		Timer.cpp
 Created:	2/5/2019 1:56:49 PM
 Author:	Tim Long, Tigra Astronomy
 Editor:	http://www.visualmicro.com
*/

#include "Timer.h"

Timer::Timer()
	{
	startedAt = 0;
	interval = 0;
	}

/*
 * Sets the timer interval and establishes the reference datum as the instant when this method was called.
 */
void Timer::setDuration(unsigned long duration)
	{
	startedAt = millis();
	interval = duration;
	}

Duration Timer::elapsed() const
	{
	if (!enabled())
		return 0UL;
	return millis() - startedAt;
	}

Duration Timer::remaining() const
	{
	return interval - elapsed();
}

bool Timer::expired() const
	{
	return enabled() ? elapsed() >= interval : false;
	}


bool Timer::enabled() const
	{
	return interval > 0;
}

void Timer::stop()
{
	interval = 0;
}



