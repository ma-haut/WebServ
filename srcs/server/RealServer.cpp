/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RealServer.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:26:58 by achantra          #+#    #+#             */
/*   Updated: 2025/05/26 17:46:36 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RealServer.hpp"

RealServer::RealServer():Server(){
}

RealServer::~RealServer(){
}

RealServer::RealServer(int domain, int service, int protocol,
    u_long interface, int backlog, std::vector<ServerConfig> configs):
    Server(domain, service, protocol, interface, backlog, configs){
        
    FD_ZERO(&_master_read_set);
    FD_ZERO(&_master_write_set);
    _max_fd = 0;
    _max_size = 0;

    for (std::vector<ListeningSocket>::iterator it = _sockets.begin(); it != _sockets.end(); ++it){
        FD_SET(it->get_sock(), &_master_read_set);
    
        // Init max_fd
        if (it->get_sock() > _max_fd)
            _max_fd = it->get_sock();
    }
    for (std::vector<ServerConfig>::iterator it = _configs.begin(); it != _configs.end(); ++it){
        if (it->client_max_body_size > _max_size)
            _max_size = it->client_max_body_size;
    }
    
    launch();
}

RealServer::RealServer(const RealServer& s){
    *this = s;
}

RealServer& RealServer::operator=(const RealServer& s){
    
    _sockets = s._sockets;
    _sockets_config = s._sockets_config;
    _curr_socket = s._curr_socket;
    _master_read_set = s._master_read_set;
    _master_write_set = s._master_write_set;
    _max_fd = s._max_fd;
    _client_sockets = s._client_sockets;
    _client_raw_requests = s._client_raw_requests;
    _client_requests = s._client_requests;
    _client_activities = s._client_activities;
    _client_response = s._client_response;
    _client_response_pos = s._client_response_pos;
    _client_response_start = s._client_response_start;
    _client_config = s._client_config;
    
    return *this;  
}
