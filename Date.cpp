//
// Created by David  on 2019-04-06.
//

#include "Date.h"


Date::Date(int y, int m, int d) : day(d), month(m), year(y) {
    if (day > getMaxDays())
        day = 1;
}

int Date::getDay() const {
    return day;
}

void Date::setDay(int day) {
    int maxDay = getMaxDays();
    if (day <= 0 || day > maxDay) {
        Date::day = 1;
        Date::month = 1;
        Date::year = 2019;
        throw BearException{"Hai inserito un giorno impossibile !!!"};
    }

    Date::day = day;
}

int Date::getYear() const {
    return year;
}

void Date::setYear(int year) {
    Date::year = year;
}

int Date::getMonth() const {
    return month;
}

void Date::setMonth(int month) {
    Date::month = month;
    if (month <= 0 || month > 12) {
        Date::day = 1;
        Date::month = 1;
        Date::year = 2019;
        throw BearException{"Hai inserito un mese impossibile !!!"};
    }

}

int Date::getMaxDays() {
    switch (month) {
        case 9:
        case 4:
        case 6:
        case 11:
            return 30;
        case 2:
            if ((year % 400 == 0 || (year % 4 && !year % 100 == 0))) return 28; //controllo anno bisestile
            else return 29;
        default:
            return 31;
    }
}

string Date::getStringDate() {
    string date, gg;
    try {
        gg = to_string(day);
    }
    catch (bad_alloc &e) {
        wxMessageBox("errore di conversione da int a string !!!");
    }
    if (gg.length() == 1)
        gg = "0" + gg;
    date = gg + "/" + getMonthString() + "/" + to_string(year);
    return date;
}


std::string Date::getMonthString() const {

    ostringstream oss;
    oss << setw(2) << setfill('0') << month;
    return oss.str();

    /* switch (month) {
         case 1:
             return "01";
         case 2:
             return "02";
         case 3:
             return "03";
         case 4:
             return "04";
         case 5:
             return "05";
         case 6:
             return "06";
         case 7:
             return "07";
         case 8:
             return "08";
         case 9:
             return "09";
         case 10:
             return "10";
         case 11:
             return "11";
         case 12:
             return "12";
     }*/
}

void Date::check_format_date(wxString str) { //controllo formale della data

    if (str.length() != 10)
        throw BearException{"Non hai inserito una data valida: ci vogliono 10 caratteri gg/mm/aaaa !!!"};

    if (!(str[2] == '/') || !(str[5] == '/'))
        throw BearException{"Non hai inserito una data valida: manca la / di separazione tra giorno, mese e anno !!!"};

    string s = string(str);                                 //converte wxString in string per la successiva gestione
    string date;
    date = {s[0], s[1], s[3], s[4], s[6], s[7], s[8], s[9]};       //forma una stringa dalla data senza le '/'

    for (int i = 0; i != date.length(); i++) {              //verifica che siano tutti numeri
        int x = date[i];
        if (!(x > 47 && x < 58))
            throw BearException{
                    "Non hai inserito una data valida: servono solo numeri per indicare giorno, mese ed anno !!!"};

    }
    // separa gg mm e aaaa dalla stringa di soli numeri
    string day_s, month_s, year_s;
    day_s = {date[0], date[1]};
    month_s = {date[2], date[3]};
    year_s = {date[4], date[5], date[6], date[7]};

    // controllo sostanziale della data
    try {
        //conversione di string in int
        setYear(stoi(year_s));
        setMonth(stoi(month_s));
        setDay(stoi(day_s));
    }
    catch (invalid_argument &e) {
        wxMessageBox("Errore dati in input: La conversione da string a int non è andata a buon fine");
    }

}

