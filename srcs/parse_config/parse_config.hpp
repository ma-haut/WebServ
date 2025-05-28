/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:37:32 by achantra          #+#    #+#             */
/*   Updated: 2025/05/26 16:54:53 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONF_PARSING
# define CONF_PARSING

# include <vector>
# include <fstream>
# include <iostream>
# include <sstream>
# include <string>
# include "../server/Server.hpp"

std::vector<ServerConfig>    parse_config(char *conf);

void    clean_line(std::string& line);
void    new_server_conf(std::istringstream& iss, int& brace_count,
            bool& in_server, ServerConfig& cur_conf);
void    set_max_body_size(std::istringstream& iss, ServerConfig& cur_conf);
void    set_port(std::istringstream& iss, ServerConfig& cur_conf);
void    set_error_page(std::istringstream& iss, ServerConfig& cur_conf);
void    new_location(std::istringstream& iss, LocationConfig& cur_loc,
            int& brace_count, bool& in_location);
void    close_server_section(int& brace_count,ServerConfig& cur_conf,
            std::vector<ServerConfig>& configs, bool& in_server);
void    set_server_conf(std::istringstream& iss, std::string& token,
            ServerConfig& cur_conf, int& brace_count, bool& in_location,
            LocationConfig& cur_loc, std::vector<ServerConfig>& configs, bool& in_server);

void    set_return(std::istringstream& iss, LocationConfig& cur_loc);
void    set_cgi(std::istringstream& iss, LocationConfig& cur_loc);
void    set_index(std::istringstream& iss, LocationConfig& cur_loc);
void    set_methods(std::istringstream& iss, LocationConfig& cur_loc);
void    set_autoindex(std::istringstream& iss, LocationConfig& cur_loc);
void    close_location_section(int& brace_count, ServerConfig& cur_conf,
            LocationConfig& cur_loc, bool& in_location);
void    set_location_config(std::istringstream& iss, std::string& token, LocationConfig& cur_loc,
            int& brace_count, ServerConfig& cur_conf, bool& in_location);

void    print_config(std::vector<ServerConfig> configs);

#endif