/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReqLine.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 12:21:31 by md-harco          #+#    #+#             */
/*   Updated: 2025/05/16 12:26:11 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQLINE_HPP
# define REQLINE_HPP

#include <cctype>
#include <string>
#include <vector>
#include <iostream>

class ReqLine {
	private:
		std::string	_reqline;
		std::string _temp_rl;
		std::string	_method;
		std::string	_uri;
		std::string _version;
		int			_ret_code;

		int			parse_method(void);
		int			parse_uri(void);
		int			parse_version(void);
	
		
		
    public:
		ReqLine(void);
		ReqLine(const std::string& buffer);
		ReqLine(ReqLine const &src);
		~ReqLine(void);

		ReqLine &operator=(ReqLine const &rhs);

		std::string const&	get_reqline(void) const;
		std::string const&	get_method(void) const;
		std::string const&	get_uri(void) const;
		std::string const&	get_version(void) const;
		int					get_ret_code(void) const;
};

#endif
