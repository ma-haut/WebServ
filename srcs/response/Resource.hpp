/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Resource.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 17:47:32 by md-harco          #+#    #+#             */
/*   Updated: 2025/05/26 18:34:51 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESOURCE_HPP
# define RESOURCE_HPP

#include <string>

class Resource {
	private:
		std::string	_requested_uri;	// Original URI from request
		std::string	_path;			// Full path to the resource
		bool		_exists;		// Does the resource exist?
		bool		_is_directory;	// Is it a directory?
		bool		_is_file;		// Is it a regular file?
		bool		_is_cgi;		// Is it a CGI script?
		std::string	_cgi_extension;	// If CGI, what extension (.php, .py, etc)
    
	public:
		Resource(void);
		Resource(std::string const &uri, std::string const &root);
		Resource(Resource const &src);
		~Resource(void);

		Resource &operator=(Resource const &rhs);

		std::string const& get_path(void) const;
		std::string const& get_requested_uri(void) const;
		bool        exists(void) const;
		bool        is_directory(void) const;
		bool        is_file(void) const;
		bool        is_cgi(void) const;
		std::string const& get_cgi_extension(void) const;

		// Methods
		bool        check_access(void) const;  // Check read permissions
		void        resolve_path(void);        // Handle directory listings/index files
		bool        is_valid_cgi(void) const;  // Check if CGI is properly configured
};

#endif