#ifndef ERRORS_H
#define ERRORS_H

#include <exception>

class UnknownSourceException : public std::exception
{
public:
    inline virtual const char* what() const noexcept override
    {
        return "The entered source account number is not found.";
    }
};

class UnknownDestinationException : public std::exception
{
public:
    inline virtual const char* what() const noexcept override
    {
        return "The entered destination account number is not found.";
    }
};

class ExpiredCardException : public std::exception
{
public:
    inline virtual const char* what() const noexcept override
    {
        return "The entered source account has been expired.";
    }
};

class NotEnoughBalanceException : public std::exception
{
public:
    inline virtual const char* what() const noexcept override
    {
        return "You do not have enough money to transfer this amount of money.";
    }
};

class ExceededCashWithdrawException : public std::exception
{
public:
    inline virtual const char* what() const noexcept override
    {
        return "The requested cash to transfer is beyond the limit of transaction.";
    }
};

class IncorrectPasswordException : public std::exception
{
public:
    inline virtual const char* what() const noexcept override
    {
        return "You have entered an incorrect password.";
    }
};

class ExceededDailyTransactionLimitExcepion : public std::exception
{
public:
    inline virtual const char* what() const noexcept override
    {
        return "You have exceeded the limit of daily transaction. Please try again tommorrow!";
    }
};

class IncorrectCVV2Exception : public std::exception
{
public:
    inline virtual const char* what() const noexcept override
    {
        return "You have entered an incorrect CVV2";
    }
};

#endif // ERRORS_H
