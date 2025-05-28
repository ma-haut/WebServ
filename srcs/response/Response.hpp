/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:04:15 by md-harco          #+#    #+#             */
/*   Updated: 2025/05/27 13:37:49 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP

# include "RealServer.hpp"

class Response {
	private:
		std::string	_http_version;
		int			_status_code;
		std::string	_status_message;
		std::map<std::string, std::string> _headers;
		std::string	_body;

		size_t      _content_length;
		std::string _content_type;

		void		build_status_line(void);
		void		build_headers(void);
		void		set_default_headers(void);
		void		handle_resource(void);
		void		serve_file(void);
		void		serve_directory(void);
		void		execute_cgi(void);

	public:
		Response(void);
		Response(int error_code);
		Response(Request request, LocationConfig);
		Response(Response const &src);
		~Response(void);

		Response &operator=(Response const &rhs);

		int 		get_status_code(void) const;
		std::string get_formatted_response(void) const;

		static const std::map<int, std::string> STATUS_CODES;
};

#endif