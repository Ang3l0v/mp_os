#include <not_implemented.h>

#include "../include/client_logger.h"

#include <map>
#include <pair>

client_logger::client_logger(
    client_logger const &other)
    :_streams(other._streams),
    _message_format(other._message_format),
    _formated_message(other._formated_message)
{
    throw not_implemented("client_logger::client_logger(client_logger const &other)", "your code should be here...");
}





client_logger &client_logger::operator=(
    client_logger const &other)
{
    if (this == &other)
    {
        return *this;
    }


    _streams = other._streams;
    _message_format = other._message_format;
    _formated_message = other._formated_message;

    return *this;
    throw not_implemented("client_logger &client_logger::operator=(client_logger const &other)", "your code should be here...");
}





client_logger::client_logger(
    client_logger &&other) noexcept
    :_streams(std::move(other._streams)),
     _message_format(std::move(other._message_format)),
     _formated_message(std::move(other._formated_message))
{
    throw not_implemented("client_logger::client_logger(client_logger &&other) noexcept", "your code should be here...");
}




client_logger &client_logger::operator=(
    client_logger &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    _streams = std::move(other._streams);
    _message_format = std::move(other._message_format);
    _formated_message = std::move(other._formated_message);

    return *this;
    throw not_implemented("client_logger &client_logger::operator=(client_logger &&other) noexcept", "your code should be here...");
}

client_logger::~client_logger() noexcept
{
    _streams.clear();
    _message_format.clear();
    _formated_message.clear();

    //throw not_implemented("client_logger::~client_logger() noexcept", "your code should be here...");
}




logger const *client_logger::log(
    const std::string &text,
    logger::severity severity) const noexcept
{
    _formated_message = '[' + current_datetime_to_string() + severity_to_string(severity) + text + ']';

    throw not_implemented("logger const *client_logger::log(const std::string &text, logger::severity severity) const noexcept", "your code should be here...");
}