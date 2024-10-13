#include <not_implemented.h>

#include "../include/client_logger_builder.h"
#include "client_logger.h"

#include <map>
#include <string>

#include "C:\json-develop\single_include\nlohmann\json.hpp"




client_logger_builder::client_logger_builder()
{
    throw not_implemented("client_logger_builder::client_logger_builder()", "your code should be here...");
}






client_logger_builder::client_logger_builder(
    client_logger_builder const &other)
    :_streams(other._streams),
    _message_format(other._message_format)
    //_formated_message(other._formated_message)
{
    throw not_implemented("client_logger_builder::client_logger_builder(client_logger_builder const &other)", "your code should be here...");
}







client_logger_builder &client_logger_builder::operator=(
    client_logger_builder const &other)
{
    if (this == &other)
    {
        return *this;
    }

    _streams = other._streams;

    _message_format = other._message_format;

    //_formated_message = other._formated_message;

    return *this;


    throw not_implemented("client_logger_builder &client_logger_builder::operator=(client_logger_builder const &other)", "your code should be here...");
}




client_logger_builder::client_logger_builder(
    client_logger_builder &&other) noexcept
    :_streams(std::move(other._streams)),
    _message_format(std::move(other._message_format))
    //_formated_message(std::move(other._formated_message))
{
    //throw not_implemented("client_logger_builder::client_logger_builder(client_logger_builder &&other) noexcept", "your code should be here...");
}





client_logger_builder &client_logger_builder::operator=(
    client_logger_builder &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    _streams = other._streams;

    _message_format = other._message_format;

    //_formated_message = other._formated_message;

    return *this;
    throw not_implemented("client_logger_builder &client_logger_builder::operator=(client_logger_builder &&other) noexcept", "your code should be here...");
}



client_logger_builder::~client_logger_builder() noexcept
{
    _streams.clear();
    //_formated_message.clear();
    _message_format.clear();
    //throw not_implemented("client_logger_builder::~client_logger_builder() noexcept", "your code should be here...");
}




logger_builder *client_logger_builder::add_file_stream(
    std::string const &stream_file_path,
    logger::severity severity)
{

    _streams[stream_file_path] = logger::severity_to_string(severity);

    return this;
    //throw not_implemented("logger_builder *client_logger_builder::add_file_stream(std::string const &stream_file_path, logger::severity severity)", "your code should be here...");
}



logger_builder *client_logger_builder::add_console_stream(
    logger::severity severity)
{
    _streams["cerr"] = logger::severity_to_string(severity);

    return this;
    //throw not_implemented("logger_builder *client_logger_builder::add_console_stream(logger::severity severity)", "your code should be here...");
}




logger_builder* client_logger_builder::transform_with_configuration(
    std::string const &configuration_file_path,
    std::string const &configuration_path)
{


    //throw not_implemented("logger_builder* client_logger_builder::transform_with_configuration(std::string const &configuration_file_path, std::string const &configuration_path)", "your code should be here...");
}






logger_builder *client_logger_builder::clear()
{
    _streams.clear();
    //_formated_message.clear();
    _message_format.clear();
    return this;
    //throw not_implemented("logger_builder *client_logger_builder::clear()", "your code should be here...");
}






logger *client_logger_builder::build() const
{

    client_logger* logger_object = new client_logger;

    logger_object->_streams = _streams;
    logger_object->_message_format = _message_format;
    //logger_object->_formated_message = _formated_message;

    return logger_object;

    throw not_implemented("logger *client_logger_builder::build() const", "your code should be here...");
}