//
// Created by David  on 2019-04-06.
//

#ifndef BEARLIST_DATE_H
#define BEARLIST_DATE_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "Exception.h"

class Date {
public:
    explicit Date(int y=2019, int m=1, int d=1);

    int getMonth() const;
    void setMonth(int month);
    int getDay() const;
    void setDay(int day);
    int getYear() const;
    void setYear(int year);
    void check_format_date(wxString str);
    string getStringDate();

private:
    int day, year, month;

    int getMaxDays();
    string getMonthString() const;
};


#endif //BEARLIST_DATE_H
