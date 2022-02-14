#ifndef ERROR_H
#define ERROR_H

#include <QString>


class Error {
public:
    QString what() const { return str; }
protected:
    Error(const QString& str) { this->str = str;}
private:
    QString str;
};

class ErrorFile : public Error {
public:
    static ErrorFile open() { return ErrorFile("Файл не возможно открыть!"); };

private:
    ErrorFile(const QString& str): Error(str) {};
};

class ErrorPeriod : public Error {
public:
    static ErrorPeriod longInterval() { return ErrorPeriod("Period слишком длиный. Уменьшите его!"); };

private:
    ErrorPeriod(const QString& str): Error(str) {};
};

#endif // ERROR_H
