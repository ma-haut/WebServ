/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReqValidator.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautdharcourt <mahautdharcourt@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 13:38:52 by md-harco          #+#    #+#             */
/*   Updated: 2025/05/30 12:22:01 by mahautdharc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ReqValidator.hpp"

RequestValidator::RequestValidator(const std::vector<ServerConfig>& servers) : _servers(servers) {}

const ServerConfig*		RequestValidator::find_matching_server(const Request& request) const
{
	const std::map<std::string, std::vector<std::string> >& headers = request.get_headers();

	std::map<std::string, std::vector<std::string> >::const_iterator host_it = headers.find("Host");
	
	if (host_it == headers.end() || host_it->second.empty())
		return (&_servers[0]);

	const std::string& host_header = host_it->second[0];

	std::string request_hostname;
	int	request_port = 80; // Default port

	size_t	colon_pos = host_header.find(':');
	if (colon_pos != std::string::npos)
	{
		request_hostname = host_header.substr(0, colon_pos);
		std::stringstream ss(host_header.substr(colon_pos + 1));
		ss >> request_port;
	}
	else
		request_hostname = host_header;

	// Looking fot a matching server (port + name)
	for (std::vector<ServerConfig>::const_iterator it = _servers.begin(); it != _servers.end(); it++)
	{
		if (it->port != request_port)
			continue;
	
		if (it->host == request_hostname)
			return &(*it);
	
		for (std::vector<std::string>::const_iterator name_it = it->name.begin(); name_it != it->name.end(); ++name_it)
		{
			if (*name_it == request_hostname)
				return &(*it);
			
		}
	}
	// If no server found, looking for a server on the same port
	for (std::vector<ServerConfig>::const_iterator it = _servers.begin(); it != _servers.end(); ++it)
	{
        if (it->port == request_port)
            return &(*it); // First server on this port = default server for this port
    }
	
	return (&_servers[0]);
}

const LocationConfig*	RequestValidator::find_matching_location(const std::string& uri, const ServerConfig& server) const
{
	size_t	longest_match = 0;
	size_t	start;
	size_t	len;
	std::vector<LocationConfig>::const_iterator location_match = server.locations.begin();

	for(std::vector<LocationConfig>::const_iterator it = server.locations.begin(); it != server.locations.end(); it++)
	{
		start = 0;
		len = uri.find_first_of('/');
		std::cout << "len = " << len << "\n";
		while(len != std::string::npos && len + 1 <= uri.length() && uri.compare(start, len + 1, it->path) == 0)
		{
			if (longest_match < len)
			{
				longest_match = len;
				location_match = it;
			}
			start += len + 1;
			len = uri.find_first_of('/', start);
		}
	}
	std::cout << "location_match = " << location_match->path << "\n";
	return &(*location_match);
}

bool	RequestValidator::is_method_allowed(const std::string& method, const LocationConfig& location) const
{
	if (location.methods.empty())
		return true; // If no methods are specified, all methods are allowed
	for (std::vector<std::string>::const_iterator it = location.methods.begin(); it != location.methods.end(); ++it)
	{
		if (*it == method)
			return true; // Method is allowed
	}
	return false; // Method is not allowed
}

// bool	RequestValidator::is_body_size_valid(const Request& request, const LocationConfig& location) const
// {
// 	// Check if the request body size exceeds the limit specified in the location config
// 	size_t body_size = request.get_body().size();
// 	if (body_size > MAX_BODY_SIZE)
// 	{
// 		return false; // Body size exceeds the limit
// 	}
// 	return true; // Body size is valid
	
// }


ValidationResult	RequestValidator::validate(const Request& request) const
{
	ValidationResult res;

	res.server = find_matching_server(request);
	res.location = find_matching_location(request.get_reqline().get_uri(), *res.server);

	if (!is_method_allowed(request.get_reqline().get_method(), *res.location))
	{
		res.error_message = "Method " + request.get_reqline().get_method() + " not allowed for " + res.location->path;
		res.is_valid = false; 
		res.error_code = 405;
		return res;
	}

	// if (!is_body_size_valid(request, *res.location))
	// {
	// 	res.error_message = "Request body size exceeds the limit for " + res.location->path;
	// 	res.is_valid = false; 
	// 	res.error_code = 413; // Payload Too Large
	// 	return res;		
	// }

	res.is_valid = true;
	return res;
}





/*
// 1. Parse syntaxique
struct ParseResult {
    bool success;
    int http_status;  // 400, 413, etc.
    std::string error_detail;
    HttpRequest request;  // seulement si success == true
};
ParseResult parse_result = parse_http_request(raw_data);
if (!parse_result.success) {
    return create_error_response(parse_result.http_status, 
                                parse_result.error_detail);
}

// 2. Validation logique
ValidationResult validation = validate_request(parse_result.request, config);
if (!validation.is_valid) {
    return create_error_response(validation.error_code, 
                                validation.error_message);
}
*/