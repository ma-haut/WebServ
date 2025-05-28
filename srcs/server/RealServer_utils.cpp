/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RealServer_utils.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:37:12 by achantra          #+#    #+#             */
/*   Updated: 2025/05/26 17:49:24 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RealServer.hpp"

// Manage new conncetions and new request
void    RealServer::fd_read(fd_set *read_set){
    for (int i = 0; i <= _max_fd; i++){
        if (!FD_ISSET(i, read_set))
            continue;
        
        // If it's the server
        bool is_server = false;
        for (std::vector<ListeningSocket>::iterator it = _sockets.begin(); it != _sockets.end(); it ++){
            if (i == (*it).get_sock()){
                is_server = true;
                if (accepter(*it) < 0)
                    continue ;
                break;
            }
        }
        
        //If it's a client
        if (!is_server) {
            _curr_socket = i;
            if (handler(_client_raw_requests[_curr_socket]) < 0){
                remove_client();
                continue ; 
            }
            if (check_request()){
                FD_CLR(_curr_socket, &_master_read_set);
                FD_SET(_curr_socket, &_master_write_set);
            }
        }
    }
}

// Manage responses to client
void    RealServer::fd_write(fd_set *write_set){
    for (int i = 0; i <= _max_fd; i++){
        if (!FD_ISSET(i, write_set))
            continue;

        _curr_socket = i;
        int res = responder();
        // Sending partially done
        if (res == 0)
            continue;
        remove_client();
        //Debug
        if (res > 0)
            std::cout << "====== DONE ======" << std::endl;     
    }
}

// Accept new connections
int    RealServer::accepter(ListeningSocket socket){
    
    struct sockaddr_in addr = socket.get_address();
    int addrlen = sizeof(addr);
    _curr_socket = accept(socket.get_sock(),
    (struct sockaddr *)&addr, (socklen_t *)&addrlen);

    if (_curr_socket < 0){
        perror("accept");
        return (-1);
    }
    FD_SET(_curr_socket, &_master_read_set);
    if (_curr_socket > _max_fd)
        _max_fd = _curr_socket;
    
    _client_sockets.push_back(_curr_socket);
    _client_config[_curr_socket] = _sockets_config[socket.get_sock()];
    std::cout << "New connection accepted: " << _curr_socket << std::endl;
    return (0);
}

// Process requests
int    RealServer::handler(std::string& request){
    
    // A revoir pour la facon de lire
    char    buffer[40];
    memset(buffer, '\0', sizeof(buffer));

    _client_activities[_curr_socket] = time(NULL);
    
    int bytes = recv(_curr_socket, buffer, sizeof(buffer) - 1, 0);

    if (bytes < 0){
        perror("recv");
        // A revoir pour renvoyer erreur interne
        return (-1);
    }

    else if (bytes == 0){
        std::cout << "Client offline: " << _curr_socket << std::endl;
        return (-1);
    }
    // A revoir pour avoir la bonne limite
    if (request.size() + bytes > _max_size + 8200){
        std::cerr << "Request too large from client: " << _curr_socket << std::endl;
        // A revoir pour renvoyer erreur
        return (-1);
    }
    
    request.append(buffer, bytes);
    
    std::cout << "====== REQUEST ======" << std::endl;
    std::cout << request << std::endl;
    return (0);
}

// A revoir lorsqu on gerera les reponse.
//Probablement avoir statut pour indiquer que la reponse est dispo avant de lancer responder
// Send responses to clients
int    RealServer::responder(){
    if (_client_response.find(_curr_socket) == _client_response.end()){
        // Get response
        const char *hello = "HTTP/1.1 200 OK\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
        _client_response[_curr_socket] = std::string(hello);
        _client_response_pos[_curr_socket] = 0;
        _client_response_start[_curr_socket] = time(NULL);
    }

    std::string& response = _client_response[_curr_socket];
    size_t& pos = _client_response_pos[_curr_socket];

    int bytes = send(_curr_socket, response.c_str() + pos, response.size() - pos, 0);
    
    // Error
    if (bytes < 0){
        perror("send");
        return (-1);
    }
    // Debug
    std::cout <<  response.substr(pos, pos + bytes) << std::endl;
    pos += bytes;
    // Everything has been sent
    if (pos >= response.size())
        return (1);
    // Partially sent
    return (0);
}