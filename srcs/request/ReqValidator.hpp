/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReqValidator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:26:53 by md-harco          #+#    #+#             */
/*   Updated: 2025/05/28 12:46:59 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQVALIDATOR_HPP
# define REQVALIDATOR_HPP

#include <sstream>
# include "Request.hpp"
# include "../server/RealServer.hpp"

struct ValidationResult {
    bool		is_valid;
    int			error_code;
    const		ServerConfig* server;
    const		LocationConfig* location;
    std::string	error_message;
};

class RequestValidator {
private:
	const std::vector<ServerConfig>&	_servers;

	const ServerConfig*		find_matching_server(const Request& request) const;
    const LocationConfig*	find_matching_location(const std::string& uri, const ServerConfig& server) const;
	bool	is_method_allowed(const std::string& method, const LocationConfig& location) const;
	// bool	is_body_size_valid(const Request& request, const LocationConfig& location) const;

public:
	RequestValidator(const std::vector<ServerConfig>& servers);

	ValidationResult	validate(const Request& request) const;
};

#endif
