/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RealServer_utils2.cpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:39:17 by achantra          #+#    #+#             */
/*   Updated: 2025/05/26 14:36:31 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RealServer.hpp"

void    RealServer::check_read_timeout(){
    time_t curr_time = time(NULL);
    std::map<int, time_t>::iterator it = _client_activities.begin();
    while (it != _client_activities.end()){
        if (curr_time - it->second > 30){
            // A revoir pour remplir la reponse client avec une erreur avant de passer en lecture
            _curr_socket = it->first;
            it++;
            std::cout << "Request timeout for client: " << _curr_socket << std::endl;
            _client_activities.erase(_curr_socket);
            FD_CLR(_curr_socket, &_master_read_set);
            FD_SET(_curr_socket, &_master_write_set);
        }
        else
            it ++;
    }
}
void    RealServer::check_write_timeout(){
    time_t curr_time = time(NULL);
    std::map<int, time_t>::iterator it = _client_response_start.begin();
    while (it != _client_response_start.end()){
        if (curr_time - it->second > 30){
            // A revoir pour renvoyer l erreur au client avant la supression
            _curr_socket = it->first;
            it++;
            std::cout << "Response timeout for client: " << _curr_socket << std::endl;
            remove_client();
        }
        else
            it ++;
    }
}

void    RealServer::stop_server(){
    for (std::vector<int>::iterator it = _client_sockets.begin();  it != _client_sockets.end(); it++)
        close(*it);

    for (std::vector<ListeningSocket>::iterator it = _sockets.begin(); it != _sockets.end(); it ++)
        close((*it).get_sock());
}

void    RealServer::remove_client(){
    close(_curr_socket);
    FD_CLR(_curr_socket, &_master_read_set);
    FD_CLR(_curr_socket, &_master_write_set);
    //Find new max_fd
    if (_curr_socket == _max_fd){
        while (_max_fd > 0 && !FD_ISSET(_max_fd, &_master_read_set))
            _max_fd--;
    }
    // Remove from list
    std::vector<int>::iterator it = std::find(_client_sockets.begin(), _client_sockets.end(), _curr_socket);
    if (it != _client_sockets.end()){
        std::cout << "Client disconnected: " << *it << std::endl;
        _client_sockets.erase(it);
    }
    _client_raw_requests.erase(_curr_socket);
    _client_activities.erase(_curr_socket);
    _client_response.erase(_curr_socket);
    _client_response_pos.erase(_curr_socket);
    _client_response_start.erase(_curr_socket);
    _client_config.erase(_curr_socket);
}

bool    RealServer::check_request(void) {
    std::string raw_request = _client_raw_requests[_curr_socket];
    if (raw_request.find("\r\n\r\n") != std::string::npos){
        
        Request request(raw_request);
        _client_requests[_curr_socket] = request;
        return (1);
    }
    return (0);
}
