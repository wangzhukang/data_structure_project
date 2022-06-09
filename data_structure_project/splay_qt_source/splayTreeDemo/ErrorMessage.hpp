#ifndef ErrorMessage_H
#define ErrorMessage_H

#include <iostream>
#include <string>

//----------------------- exception class ErrorMessage -----------------------//
class ErrorMessage
{
private:
    std::string message;
public:
    ErrorMessage()
    {
        this->message = "throw an exception ErrorMessage";
    }
    ErrorMessage(std::string message)
    {
        this->message = message;
    }
    std::string what() const
    {
        return this->message;
    }
};

//----------------------- exception class ErrorMessage -----------------------//

#endif