/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi_utils.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 10:36:23 by achantra          #+#    #+#             */
/*   Updated: 2025/05/27 11:45:08 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi_handler.hpp"

std::vector<std::string>    setup_env(/*Request& req, ServerConfig& config*/){
    std::vector<std::string> env_strings;

    env_strings.push_back("REQUEST_METHOD=GET");   //HTTP methods
    env_strings.push_back("QUERY_STRING=name=John&age=30");    //After ? in URL
    env_strings.push_back("CONTENT_LENGTH=0"); //Body length
    env_strings.push_back("CONTENT_TYPE=text/html"); //type MIME of HTTP body
    env_strings.push_back("SCRIPT_NAME=/cgi-bin/hello.py"); //CGI script path
    env_strings.push_back("SERVER_PROTOCOL=HTTP/1.1"); //HTTP protocol version
    env_strings.push_back("SERVER_SOFTWARE=MyCppServer/1.0"); //webserveur name
    env_strings.push_back("SERVER_NAME=localhost"); // Host name of server
    env_strings.push_back("SERVER_PORT=8080"); // Port of server
    env_strings.push_back("REMOTE_ADDR=192.168.1.10"); //Client IP
    env_strings.push_back("REMOTE_PORT=51234"); // Client port
    env_strings.push_back("HTTP_USER_AGENT=Mozilla/5.0 (compatible; MyCppClient/1.0)"); // HTTP variable inherited from header
    env_strings.push_back("HTTP_ACCEPT=text/html,application/xhtml+xml"); // HTTP variable inherited from header
    env_strings.push_back("HTTP_COOKIE=sessionid=abc123"); // HTTP variable inherited from header
    
    return env_strings;
}

void    set_argv(char *argv[3], char *script_path, char *cgi_path){
    argv[2] = NULL;
    // If there is a path, the script is an argument
    if (cgi_path != NULL) {
        argv[0] = cgi_path;
        argv[1] = script_path;
    }
    // If no path, the script is the path
    else {
        argv[0] = script_path;
        argv[1] = NULL;
    }
}

bool    is_executable(char *script){
    if (access(script, X_OK) == 0)
        return true;
    perror("CGI executable not found or not executable ");
    return false;
}

int transmit_body(int fd, std::string& request_body){
    size_t total = 0;
    while (total < request_body.size()){
        ssize_t written = write(fd, request_body.c_str()+ total, request_body.size() - total);
        if (written <= 0){
            perror("Cannot write CGI input");
            return (-1);
        }
        total += written;
    }
    return (0);
}

int read_result(int fd, std::string& cgi_response){
    char buffer[4096];
    ssize_t b_read = read(fd, buffer, sizeof(buffer));

    while (b_read > 0){
        cgi_response.append(buffer, b_read);
        b_read = read(fd, buffer, sizeof(buffer));
    }
    if (b_read == -1){
        perror("Cannot read CGI output");
        return (-1);
    }
    return (0);
}