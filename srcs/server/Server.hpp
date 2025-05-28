/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:12:19 by achantra          #+#    #+#             */
/*   Updated: 2025/05/26 17:43:25 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "../socket/ListeningSocket.hpp"
# include "../utils/utils.hpp"
# include <string.h>
# include <string>
# include <unistd.h>
# include <vector>
# include <sys/select.h>
# include <algorithm>
# include <map>
# include <cerrno>
# include <ctime>
# include <signal.h>


struct LocationConfig{
    std::string path;
    std::string root;
    int return_code;
    std::string return_url;
    std::vector<std::string> index;
    std::vector<std::string> methods;
    bool autoindex;
    std::map<std::string, std::string> cgi_map;
};

struct ServerConfig{
    int port;
    std::string host;
    std::vector<std::string> name;
    std::string root;
    std::map<int, std::string> error_pages;
    std::vector<LocationConfig> locations;
    size_t client_max_body_size;
};

class Server {
    protected:
        //Store the sockets to listen
        std::vector<ListeningSocket> _sockets;
        //Store the configs describe in the conf file
        std::vector<ServerConfig> _configs;
        //Map the sockets and the corresponding config
        std::map<int, ServerConfig> _sockets_config;

        Server(void);
        Server(const Server& s);
        Server& operator=(const Server& s);
        Server(int domain, int service, int protocol,
            u_long interface, int backlog, std::vector<ServerConfig> configs);

    private:
        virtual int    accepter(ListeningSocket socket) = 0;
        virtual int    handler(std::string& request) = 0;
        virtual int    responder() = 0;


    public:
        
        ~Server();

        virtual void    launch() = 0;
};

#endif