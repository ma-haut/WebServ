/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautdharcourt <mahautdharcourt@studen    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 18:20:19 by md-harco          #+#    #+#             */
/*   Updated: 2025/05/30 12:22:05 by mahautdharc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Response.hpp"

Response::Response(void)
{
}

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
