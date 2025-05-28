/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: md-harco <md-harco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:20:19 by md-harco          #+#    #+#             */
/*   Updated: 2025/05/26 18:21:57 by md-harco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response(void) {}

Response::Response(Response const &src)
{
	*this = src;
}

Response::~Response(void) {}

Response &Response::operator=(Response const &rhs)
{
	if (this != &rhs)
{
		
	}
	return *this;
}
