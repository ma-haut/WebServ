/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BindingSocket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:45:20 by achantra          #+#    #+#             */
/*   Updated: 2025/05/16 15:05:40 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "BindingSocket.hpp"

BindingSocket::BindingSocket(void){
}

BindingSocket::BindingSocket(int domain, int service, int protocol,
    int port, u_long interface): Socket(domain, service, protocol, port, interface){
    
    int opt = 1;
    if (setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        perror("setsockopt(SO_REUSEADDR)");
        exit(EXIT_FAILURE);
    }
        
    //Binding
    _binding = bind(_sock, (struct sockaddr *)&_address, sizeof(_address));
    test_error(_binding, (char *) "bind");
}

BindingSocket::~BindingSocket(){
}

BindingSocket::BindingSocket(const BindingSocket& s){
    *this = s;
}

BindingSocket& BindingSocket::operator=(const BindingSocket& s){
    // Adress structure
    _address.sin_family = s._address.sin_family;
    _address.sin_port = s._address.sin_port;
    _address.sin_addr.s_addr = s._address.sin_addr.s_addr;
    
    _sock = s._sock;
    _binding = s._binding;
    
    return *this;
}