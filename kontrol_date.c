#include "kontrol_date.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int days_in_month(int month, int year) {
    switch (month) {
        case 1: return 31;
        case 2: return is_leap_year(year) ? 29 : 28;
        case 3: return 31;
        case 4: return 30;
        case 5: return 31;
        case 6: return 30;
        case 7: return 31;
        case 8: return 31;
        case 9: return 30;
        case 10: return 31;
        case 11: return 30;
        case 12: return 31;
        default: return 0;
    }
}

void add_days(char* input_date, char* result_date) {
    int day, month, year;
    sscanf(input_date, "%d-%d-%d", &day, &month, &year);
    
    day += 3;
    
    while (day > days_in_month(month, year)) {
        day -= days_in_month(month, year);
        month++;
        if (month > 12) {
            month = 1;
            year++;
        }
    }

    const char* months[] = {
        "Januari", "Februari", "Maret", "April", "Mei", "Juni",
        "Juli", "Agustus", "September", "Oktober", "November", "Desember"
    };
    
    sprintf(result_date, "%d %s %d", day, months[month - 1], year);
}
