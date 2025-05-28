/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:10:35 by md-harco          #+#    #+#             */
/*   Updated: 2025/05/28 12:26:15 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

Request::Request(void){
	
}

Request::Request(std::string buffer) : 
	_buffer(buffer),
	_rl(_buffer),
	_ret_code(_rl.get_ret_code())
{
	if (_ret_code == 200)
	{
		_buffer = _buffer.substr(_rl.get_reqline().size());
		_ret_code = parse_headers();
		if (_ret_code == 200 && !_buffer.empty())
			_body = _buffer;
	}
}

Request::Request(Request const &src) :
	_buffer(src._buffer),
    _rl(src._rl),
    _headers(src._headers),
    _body(src._body),
    _ret_code(src._ret_code)
{
}

Request::~Request(void) {}

Request &Request::operator=(Request const &rhs)
{
    if (this != &rhs)
    {
		_buffer = rhs._buffer;
		_rl = rhs._rl;
		_headers = rhs._headers;
		_body = rhs._body;
		_ret_code = rhs._ret_code;
    }
	return *this;
}

int	Request::parse_header_line(std::string header_line)
{
	size_t		pos;
	std::string	key;
	std::string	value;

	// Parse key
	pos = header_line.find(':');
	if (pos == std::string::npos)
		return (400);
	key = header_line.substr(0, pos);

	// Remove whitespaces from key
	while (!key.empty() && isspace(key[key.length() - 1]))
		key.erase(key.length() - 1);

	header_line = header_line.substr(pos + 1);
	pos = header_line.find_first_not_of(" \t");
	if (pos == std::string::npos || isspace(header_line[pos]))
		return (400);
	header_line = header_line.substr(pos);
	pos = header_line.find_first_of("\n,;");
	if (pos == std::string::npos)
		return (400);
	value = header_line.substr(0, pos);
	
	// Remove whitespaces from value
	while (!value.empty() && isspace(value[value.length() - 1]))
		value.erase(value.length() - 1);

	_headers[key].push_back(value);

	while (header_line[pos] == ',' || header_line[pos] == ';')
	{
		header_line = header_line.substr(pos + 1);
		pos = header_line.find_first_not_of(" \t\n");
		if (pos == std::string::npos || isspace(header_line[pos]))
			return (400);
		header_line = header_line.substr(pos);
		pos = header_line.find_first_of("\n,;");
		if (pos == std::string::npos)
			return (400);
		value = header_line.substr(0, pos);

		while (!value.empty() && isspace(value[value.length() - 1]))
			value.erase(value.length() - 1);
	
		_headers[key].push_back(value);
	}
	return (200);
}

int	Request::parse_headers(void)
{
	size_t		pos;
	int			ret_code;
	std::string	header_line;

	ret_code = 200;
	pos = _buffer.find_first_of('\n');
	if (pos == std::string::npos)
			return (400);
	while (ret_code && !_buffer.empty())
	{
		if (_buffer[0] == '\n' || (_buffer[0] == '\r' && _buffer[1] == '\n'))
			break;
		if (isspace(_buffer[0]))
			return (400);
		pos = _buffer.find_first_of('\n');
		if (pos == std::string::npos)
			return (400);
		header_line = _buffer.substr(0, pos + 1);
		_buffer = _buffer.substr(pos + 1);
		while (_buffer[0] == ' ' || _buffer[0] == '\t')
		{
			pos = _buffer.find_first_of('\n');
			if (pos == std::string::npos)
				return (400);
			header_line += _buffer.substr(0, pos + 1);
			_buffer = _buffer.substr(pos + 1);
		}
		ret_code = parse_header_line(header_line);
	}
	//Verify that Host is part of the headers
	if (ret_code && _headers.find("Host") != _headers.end())
		return (200);
	return (400);
}

const ReqLine&		Request::get_reqline(void) const
{
	return (_rl);
}

const std::map<std::string, std::vector<std::string> >&	Request::get_headers(void) const
{
	return (_headers);
}

const std::string&	Request::get_body(void) const
{
	return (_body);
}

int	Request::get_ret_code(void) const
{
	return (_ret_code);
}