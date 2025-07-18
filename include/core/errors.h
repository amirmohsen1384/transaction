#ifndef ERRORS_H
#define ERRORS_H

#include <exception>

class UnknownSourceException : std::exception
{
public:
    inline virtual const char* what() const noexcept override
    {
        return "The entered source account number is not found.";
    }
};

class UnknownDestinationException : std::exception
{
public:
    inline virtual const char* what() const noexcept override
    {
        return "The entered destination account number is not found.";
    }
};

class ExpiredCardException : std::exception
{
public:
    inline virtual const char* what() const noexcept override
    {
        return "The entered source account has been expired.";
    }
};

class NotEnoughBalanceException : std::exception
{
public:
    inline virtual const char* what() const noexcept override
    {
        return "The entered source account has been expired.";
    }
};

class ExceededCashWithdraw : std::exception
{
public:
    inline virtual const char* what() const noexcept override
    {
        return "The requested cash to transfer is beyond the limit of transaction.";
    }
};

class IncorrectPasswordException : std::exception
{
public:
    inline virtual const char* what() const noexcept override
    {
        return "The requested cash to transfer is beyond the limit of transaction.";
    }
};

class ExceededDailyTransactionLimit : std::exception
{
public:
    inline virtual const char* what() const noexcept override
    {
        return "You have exceeded the limit of daily transaction. Please try again tommorrow!";
    }
};

#endif // ERRORS_H
