/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RealServer.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:26:10 by achantra          #+#    #+#             */
/*   Updated: 2025/05/26 17:47:18 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REALSERVER_HPP
# define REALSERVER_HPP

# include "Server.hpp"
# include "../request/Request.hpp"

class Server;

class RealServer : public Server{
    private:
        // Track the socket currently used
        int     _curr_socket;
        // Track all the sockets the server could read from
        fd_set  _master_read_set;
        // Track all the sockets the server could send response to
        fd_set  _master_write_set;
        // Keep the fd_max
        int     _max_fd;
        // Keep client_body_max_size
        size_t     _max_size;
        
        // Store client socket
        std::vector<int>_client_sockets;
        // Map client socket and config
        std::map<int, ServerConfig> _client_config;
        
        // Keep client request until they are complete
        std::map<int, std::string> _client_raw_requests;
        // Keep client clomplete request until they are processed
        std::map<int, Request> _client_requests;
        // Track the time since the request began
        std::map<int, time_t> _client_activities;
        
        // Keep client response until they are sent
        std::map<int, std::string> _client_response;
        // Track the sending of responses
        std::map<int, size_t> _client_response_pos;
        // Track the time since the last part of response was sent
        std::map<int, time_t> _client_response_start;
        

        RealServer(void);
        
        int accepter(ListeningSocket socket);
        int handler(std::string& request);
        int responder();
    
    public:
        RealServer(int domain, int service, int protocol,
            u_long interface, int backlog, std::vector<ServerConfig> configs);
        ~RealServer();
        RealServer& operator=(const RealServer& s);
        RealServer(const RealServer& s);
        
        void    launch();
        void    remove_client();
        bool    check_request(void);
        void    check_read_timeout();
        void    check_write_timeout();
        void    fd_read(fd_set *read_set);
        void    fd_write(fd_set *read_set);
        void    stop_server();
        
};

#endif