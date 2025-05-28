/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi_handler.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:17:49 by achantra          #+#    #+#             */
/*   Updated: 2025/05/27 11:44:43 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_HANDLER
# define CGI_HANDLER

# include <iostream>
# include <unistd.h>
# include <sys/wait.h>
# include <cstring>
# include <vector>
# include "../request/Request.hpp"
# include "../server/Server.hpp"

int     cgi_process(char *script_path, char *cgi_path, std::string& request_body, std::string& cgi_response);
std::vector<std::string>    setup_env(/*Request& req, ServerConfig& config*/);

void    child_process(std::vector<std::string>& envp, char *script_path, char *cgi_path, int *fd_in, int *fd_out);
void    set_argv(char *argv[3], char *script_path, char *cgi_path);
bool    is_executable(char *script);


int     parent_process(int *fd_in, int *fd_out, pid_t pid, std::string& request_body, std::string& cgi_response);
int     transmit_body(int fd, std::string& request_body);
int     read_result(int fd, std::string& cgi_response);


#endif