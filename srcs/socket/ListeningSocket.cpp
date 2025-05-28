/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListeningSocket.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:55:51 by achantra          #+#    #+#             */
/*   Updated: 2025/05/16 11:43:37 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ListeningSocket.hpp"

ListeningSocket::ListeningSocket(void){
}

ListeningSocket::ListeningSocket(int domain, int service,
    int protocol, int port, u_long interface,
    int backlog): BindingSocket(domain, service, protocol, port, interface){
    _backlog = backlog;
    
    // Start listening
    _listening = listen(_sock, _backlog);
    test_error(_listening, (char *) "listen");
}

ListeningSocket::~ListeningSocket(){
}

ListeningSocket::ListeningSocket(const ListeningSocket& s){
    *this = s;
}

ListeningSocket& ListeningSocket::operator=(const ListeningSocket& s){
    // Adress structure
    _address.sin_family = s._address.sin_family;
    _address.sin_port = s._address.sin_port;
    _address.sin_addr.s_addr = s._address.sin_addr.s_addr;
    
    _sock = s._sock;

    _backlog = s._backlog;
    _binding = s._binding;
    _listening = s._listening;
    
    return *this;
}

int ListeningSocket::get_backlog() const{
    return this->_backlog;
}
int ListeningSocket::get_listening() const{
    return  this->_listening;
}
