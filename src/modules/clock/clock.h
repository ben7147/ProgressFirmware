#ifndef CLOCK_H
#define CLOCK_H

#include <ESP32Time.h>

extern ESP32Time rtc;
extern String timeStr;

void storeCurrentTime();

#endif // CLOCK_H
