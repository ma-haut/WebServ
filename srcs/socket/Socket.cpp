/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:50:34 by achantra          #+#    #+#             */
/*   Updated: 2025/05/16 11:43:40 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Socket.hpp"

// Constructor & Destructor
Socket::Socket(void){
}

Socket::Socket(int domain, int service, int protocol,
    int port, u_long interface){
    
    // Adress structure
    _address.sin_family = domain;
    _address.sin_port = htons(port);
    _address.sin_addr.s_addr = htonl(interface);
    memset(_address.sin_zero, '\0', sizeof _address.sin_zero);
    
    //Socket
    _sock = socket(domain, service, protocol);
    test_error(_sock, (char *) "socket");
}

Socket::Socket(const Socket& s){
    *this = s;
}

Socket& Socket::operator=(const Socket& s){
    // Adress structure
    _address.sin_family = s._address.sin_family;
    _address.sin_port = s._address.sin_port;
    _address.sin_addr.s_addr = s._address.sin_addr.s_addr;
    
    //Socket
    _sock = s._sock;
    return *this;  
}

Socket::~Socket(){
    return ;
}

// Getter
struct sockaddr_in Socket::get_address() const{
    return this->_address;
}

int Socket::get_sock() const{
    return this->_sock;
}