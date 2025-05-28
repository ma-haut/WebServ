/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 14:04:26 by md-harco          #+#    #+#             */
/*   Updated: 2025/05/15 16:43:14 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

#include "ReqLine.hpp"
#include <map>
#include <iostream>

class Request {
	private:
		std::string											_buffer;
		ReqLine												_rl;
		std::map<std::string, std::vector<std::string> >	_headers;
		std::string											_body;
		int													_ret_code;

		int	parse_header_line(std::string header_line);
		int	parse_headers(void);

	public:
		Request(void);
		Request(std::string buffer);
		Request(Request const &src);
		~Request(void);

		Request &operator=(Request const &rhs);

		const ReqLine&		get_reqline(void) const;
		const std::map<std::string, std::vector<std::string> >&	get_headers(void) const;
		const std::string&	get_body(void) const;
		int					get_ret_code(void) const;
};

#endif