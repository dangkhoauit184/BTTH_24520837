#include <iostream>
using namespace std;

struct Date {
    int day;
    int month;
    int year;
};

// Hàm kiểm tra năm nhuận
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Hàm tính số ngày trong tháng
int daysInMonth(int month, int year) {
    if (month == 2) {
        return isLeapYear(year) ? 29 : 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    return 31;
}

// Hàm tìm ngày kế tiếp
Date getNextDay(Date currentDate) {
    Date nextDay = currentDate;
    nextDay.day++;
    if (nextDay.day > daysInMonth(nextDay.month, nextDay.year)) {
        nextDay.day = 1;
        nextDay.month++;
        if (nextDay.month > 12) {
            nextDay.month = 1;
            nextDay.year++;
        }
    }
    return nextDay;
}

// Hàm tìm ngày trước đó
Date getPreviousDay(Date currentDate) {
    Date previousDay = currentDate;
    previousDay.day--;
    if (previousDay.day < 1) {
        previousDay.month--;
        if (previousDay.month < 1) {
            previousDay.month = 12;
            previousDay.year--;
        }
        previousDay.day = daysInMonth(previousDay.month, previousDay.year);
    }
    return previousDay;
}

// Hàm tính ngày thứ bao nhiêu trong năm
int dayOfYear(Date currentDate) {
    int dayCount = currentDate.day;
    for (int month = 1; month < currentDate.month; month++) {
        dayCount += daysInMonth(month, currentDate.year);
    }
    return dayCount;
}

int main() {
    Date currentDate;
    cout << "Nhập ngày (dd mm yyyy): ";
    cin >> currentDate.day >> currentDate.month >> currentDate.year;

    Date nextDay = getNextDay(currentDate);
    cout << "Ngày kế tiếp là: " << nextDay.day << "/" << nextDay.month << "/" << nextDay.year << endl;

    Date previousDay = getPreviousDay(currentDate);
    cout << "Ngày trước đó là: " << previousDay.day << "/" << previousDay.month << "/" << previousDay.year << endl;

    int dayOfYearCount = dayOfYear(currentDate);
    cout << "Ngày " << currentDate.day << "/" << currentDate.month << "/" << currentDate.year << " là ngày thứ " << dayOfYearCount << " trong năm." << endl;

    return 0;
}
