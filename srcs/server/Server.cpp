/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:12:16 by achantra          #+#    #+#             */
/*   Updated: 2025/05/26 14:03:13 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server(void){
}

Server::Server(int domain, int service, int protocol,
    u_long interface, int backlog, std::vector<ServerConfig> configs){
        
    for (size_t i = 0; i < configs.size(); i++){
        _sockets.push_back(ListeningSocket(domain, service, protocol, configs[i].port, interface, backlog));
        _sockets_config[_sockets.back().get_sock()] = configs[i];
    }
}
    

Server::Server(const Server& s){
    *this = s;
}

Server& Server::operator=(const Server& s){
    
    _sockets = s._sockets;
    //_sockets_config = s._sockets_config;
    
    return *this;  
}

Server::~Server(){
}
