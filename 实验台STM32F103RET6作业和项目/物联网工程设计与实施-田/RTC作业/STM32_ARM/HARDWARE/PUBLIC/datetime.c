#include "datetime.h"

// 判断是否为闰年
bool is_leap_year(uint16_t year) {
    if ((year % 400) == 0) {
        return true;
    } else if ((year % 100) == 0) {
        return false;
    } else if ((year % 4) == 0) {
        return true;
    }
    return false;
}

// 获取某个月的天数
uint8_t get_month_days(uint8_t month, uint16_t year) {
    static const uint8_t days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (month == 2 && is_leap_year(year)) {
        return 29;
    }
    
    if (month >= 1 && month <= 12) {
        return days_in_month[month - 1];
    }
    
    return 0;
}

// 基姆拉尔森公式计算星期几
uint8_t calculate_weekday(uint16_t year, uint8_t month, uint8_t day) {
    uint8_t m = month;
    uint16_t y = year;
    
    // 1月和2月被视为上一年的13月和14月
    if (m < 3) {
        m += 12;
        y--;
    }
    
    uint8_t K = y % 100; // 年份后两位
    uint8_t J = y / 100; // 年份前两位
    
    // 基姆拉尔森公式
    uint8_t h = (day + (13 * (m + 1)) / 5 + K + (K / 4) + (J / 4) + 5 * J) % 7;
    
    // 转换为0=周日,1=周一,...,6=周六
    return (h + 6) % 7;
}

// 增加一秒，自动处理进位
void datetime_increment(DateTime *dt) {
    dt->second++;
    
    if (dt->second >= 60) {
        dt->second = 0;
        dt->minute++;
        
        if (dt->minute >= 60) {
            dt->minute = 0;
            dt->hour++;
            
            if (dt->hour >= 24) {
                dt->hour = 0;
                dt->day++;
                dt->weekday = (dt->weekday + 1) % 7; // 星期递增
                
                if (dt->day > get_month_days(dt->month, dt->year)) {
                    dt->day = 1;
                    dt->month++;
                    
                    if (dt->month > 12) {
                        dt->month = 1;
                        dt->year++;
                        // 年份变化需要重新计算闰年
                    }
                }
            }
        }
    }
}

// 检查日期时间是否有效
bool datetime_is_valid(const DateTime *dt) {
    if (dt->year < 2000 || dt->year > 2099) return false;
    if (dt->month < 1 || dt->month > 12) return false;
    if (dt->day < 1 || dt->day > get_month_days(dt->month, dt->year)) return false;
    if (dt->weekday > 6) return false;
    if (dt->hour > 23) return false;
    if (dt->minute > 59) return false;
    if (dt->second > 59) return false;
    
    return true;
}