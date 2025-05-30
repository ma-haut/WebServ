/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Resource.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautdharcourt <mahautdharcourt@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:16:52 by mahautdharc       #+#    #+#             */
/*   Updated: 2025/05/30 12:22:04 by mahautdharc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Resource.hpp"

Resource::Resource(void) : _requested_uri(""), _path(""), _exists(false), _is_directory(false), _is_file(false), _is_cgi(false), _cgi_extension("") {}

Resource::Resource(std::string const &uri, std::string const &root) 
	: _requested_uri(uri), _path(root + uri), _exists(false), _is_directory(false), _is_file(false), _is_cgi(false), _cgi_extension("") {
	resolve_path();
}

Resource::Resource(Resource const &src) 
	: _requested_uri(src._requested_uri), _path(src._path), _exists(src._exists), 
	  _is_directory(src._is_directory), _is_file(src._is_file), _is_cgi(src._is_cgi), 
	  _cgi_extension(src._cgi_extension) {}

Resource::~Resource(void) {}

Resource &Resource::operator=(Resource const &rhs) {
	if (this != &rhs) {
		_requested_uri = rhs._requested_uri;
		_path = rhs._path;
		_exists = rhs._exists;
		_is_directory = rhs._is_directory;
		_is_file = rhs._is_file;
		_is_cgi = rhs._is_cgi;
		_cgi_extension = rhs._cgi_extension;
	}
	return *this;
}

std::string const& Resource::get_path(void) const {
	return _path;
}

std::string const& Resource::get_requested_uri(void) const {
	return _requested_uri;
}

bool Resource::exists(void) const {
	return _exists;
}

bool Resource::is_directory(void) const {
	return _is_directory;
}

bool Resource::is_file(void) const {
	return _is_file;
}

bool Resource::is_cgi(void) const {
	return _is_cgi;
}

std::string const& Resource::get_cgi_extension(void) const {
	return _cgi_extension;
}

