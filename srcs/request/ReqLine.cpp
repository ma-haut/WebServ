/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReqLine.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:34:49 by md-harco          #+#    #+#             */
/*   Updated: 2025/05/26 15:00:55 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReqLine.hpp"

ReqLine::ReqLine(void) {}

ReqLine::ReqLine(const std::string& buffer)
{
	size_t	pos;

	pos = buffer.find_first_of('\n');
	if (pos == std::string::npos)
		_ret_code = 400;
	else
	{
		_reqline = buffer.substr(0, pos + 1);
		_temp_rl = _reqline;
		_ret_code = parse_method();
		if (_ret_code == 200)
			_ret_code = parse_uri();
		if (_ret_code == 200)
			_ret_code = parse_version();
	}
}

ReqLine::ReqLine(ReqLine const &src)
{
	*this = src;
}

ReqLine::~ReqLine(void) {}

ReqLine &ReqLine::operator=(ReqLine const &rhs)
{
	if (this != &rhs)
	{
		_reqline = rhs.get_reqline();
		_method = rhs.get_method();
		_uri = rhs.get_uri();
		_version = rhs.get_version();
		_ret_code = rhs.get_ret_code();
	}
	return (*this);
}

int	ReqLine::parse_method(void)
{
	std::string method;
	size_t		pos;

	pos = _reqline.find_first_of(" \t");
	if (pos == std::string::npos)
		return (400);
	method = _reqline.substr(0, pos);

	//Only accepting methods defined in VALID_METHODS
	if (method == "GET" || method == "POST" || method == "DELETE")
	{
		this->_method = method;
		return (200);
	}
	return (400);
}


int	ReqLine::parse_uri(void)
{
	std::string uri;
	size_t		pos;

	_temp_rl = _temp_rl.substr(_method.length());
	pos = _temp_rl.find_first_not_of(" \t");
	if (pos == std::string::npos)
		return (400);
	_temp_rl = _temp_rl.substr(pos);

	pos = _temp_rl.find_first_of(" \t");
	if (pos == std::string::npos)
		return (400);
	uri = _temp_rl.substr(0, pos);

	//Only accepting URI that starts with / (absolute form)
	if (uri.empty())
		return (400);
	if (uri[0] != '/')
		return (400);
	this->_uri = uri;
	return (200);
}

int	ReqLine::parse_version(void)
{
	std::string	version;
	size_t		pos;

	_temp_rl = _temp_rl.substr(_uri.length());
	pos = _temp_rl.find_first_not_of(" \t");
	if (pos == std::string::npos)
		return (400);
	_temp_rl = _temp_rl.substr(pos);

	pos = _temp_rl.find_first_of(" \t\r\n");
	if (pos == std::string::npos)
		return (400);
	version = _temp_rl.substr(0, pos);

	//Version must respect format HTTP/x.x with x digits
	if (version.size() != 8)
		return (400);
	if (version.substr(0, 5) != "HTTP/")
		return (400);
	if (!isdigit(version[5]) || version[6] != '.' || !isdigit(version[7]))
		return (400);
	this->_version = version;

	//Verifying the rest of temp rl is only white spaces 
	_temp_rl = _temp_rl.substr(_version.length());
	pos = _temp_rl.find_first_not_of(" \t\r\n");
	if (pos != std::string::npos)
		return (400);
	return (200);
}

//GETTERS 

std::string	const&	ReqLine::get_reqline(void) const
{
	return _reqline;
}

std::string	const&	ReqLine::get_method(void) const
{
	return _method;
}

std::string	const&	ReqLine::get_uri(void) const
{
	return _uri;
}

std::string	const&	ReqLine::get_version(void) const
{
	return _version;
}

int	ReqLine::get_ret_code(void) const
{
	return _ret_code;
}