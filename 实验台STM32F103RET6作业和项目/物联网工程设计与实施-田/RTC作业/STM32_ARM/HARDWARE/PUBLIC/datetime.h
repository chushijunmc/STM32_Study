#ifndef __DATETIME_H
#define __DATETIME_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint16_t year;   // 2000-2099
    uint8_t month;   // 1-12
    uint8_t day;     // 1-31
    uint8_t weekday; // 0-6 (0=Sunday, 1=Monday, ..., 6=Saturday)
    uint8_t hour;    // 0-23
    uint8_t minute; // 0-59
    uint8_t second; // 0-59
} DateTime;

bool is_leap_year(uint16_t year);
uint8_t get_month_days(uint8_t month, uint16_t year);
uint8_t calculate_weekday(uint16_t year, uint8_t month, uint8_t day);
void datetime_increment(DateTime *dt);
bool datetime_is_valid(const DateTime *dt);

#endif /* __DATETIME_H */