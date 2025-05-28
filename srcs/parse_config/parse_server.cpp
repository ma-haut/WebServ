/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_server.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:29:35 by achantra          #+#    #+#             */
/*   Updated: 2025/05/26 17:38:05 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_config.hpp"

// Create a new ServerConfig for the new server bloc
void new_server_conf(std::istringstream& iss, int& brace_count, bool& in_server, ServerConfig& cur_conf){
    std::string brace;
    iss >> brace;
    
    if (brace != "{")
        throw std::runtime_error("Missing '{' after 'server'");
    brace_count ++;
    in_server = true;
    cur_conf = ServerConfig();
}

// Set the configuration of the server
void    set_server_conf(std::istringstream& iss, std::string& token,
    ServerConfig& cur_conf, int& brace_count, bool& in_location,
    LocationConfig& cur_loc, std::vector<ServerConfig>& configs, bool& in_server){
    if (token == "listen")
        set_port(iss, cur_conf);
    else if (token == "server_name"){
        std::string sname;
        while (iss >> sname)
            cur_conf.name.push_back(sname);
    }
    else if (token == "root")
        iss >> cur_conf.root;
    else if (token == "error_page")
        set_error_page(iss, cur_conf);
    else if (token == "client_max_body_size")
        set_max_body_size(iss, cur_conf);
    else if (token == "host")
        iss >> cur_conf.host;
    else if (token == "location")
        new_location(iss, cur_loc, brace_count, in_location);
    else if (token == "}")
        close_server_section(brace_count, cur_conf, configs, in_server);
    else
        std::cerr << "Warning: Unknown directive '" << token << "'" << std::endl;
}

void    set_max_body_size(std::istringstream& iss, ServerConfig& cur_conf){
    std::string value;
    iss >> value;
    size_t i = 0;
    while (i < value.size() && std::isdigit(value[i]))
        i ++;
    std::stringstream ss(value);
    size_t size;
    ss >> size;
    value = value.substr(i);
    if (value.empty())
        cur_conf.client_max_body_size = size;
    else if (value == "K" || value =="k")
        cur_conf.client_max_body_size = size * 1024;
    else if (value == "M" || value =="M")
        cur_conf.client_max_body_size = size * 1024 * 1024;
    else if (value == "G" || value =="g")
        cur_conf.client_max_body_size = size * 1024 * 1024 * 1024;
    else
        throw std::invalid_argument("Unknown size unit: " + value);     
}

// Set the port of the server
void    set_port(std::istringstream& iss, ServerConfig& cur_conf){
    std::ostringstream oss;
    if (!(iss >> cur_conf.port) ||
            cur_conf.port <= 0 ||
            cur_conf.port > 65535){
        oss << "Invalid port value: " << cur_conf.port;
        throw std::runtime_error(oss.str());
    }
}

// Set the error pages of the server
void    set_error_page(std::istringstream& iss, ServerConfig& cur_conf){
    std::ostringstream oss;
    int code;
    std::string path;
    iss >> code >> path;
    if (code < 100 || code > 599){
        oss << "Invalid HTTP code value: " << code << std::endl;
        throw std::runtime_error(oss.str());
    }
    cur_conf.error_pages[code] = path;
}

//Create a new LocationConfig for the new location bloc
void new_location(std::istringstream& iss, LocationConfig& cur_loc, int& brace_count, bool& in_location){
    if (in_location)
        throw std::runtime_error("Nested 'location' blocks not allowed");
    std::string path;
    std::string brace;
    iss >> path >> brace;
    
    if (brace != "{")
        throw std::runtime_error("Missing '{' after 'server'");
    brace_count ++;
    in_location = true;
    cur_loc = LocationConfig();
    cur_loc.path = path;
}

// End the server section
void    close_server_section(int& brace_count,ServerConfig& cur_conf, std::vector<ServerConfig>& configs, bool& in_server){
    std::ostringstream oss;
    brace_count--;
    if (brace_count < 0){
        throw std::runtime_error("Unexpected closing '}' in config file");
    }
    else if (!cur_conf.port) {
        throw std::runtime_error("Server block missing 'listen' directive");
    }
    for (size_t i = 0; i < configs.size(); i++){
        if (cur_conf.port == configs[i].port){
            for (size_t j = 0; j < cur_conf.name.size(); j++){
                if (find(configs[i].name.begin(), configs[i].name.end(), cur_conf.name[i]) != configs[i].name.end()){
                oss << "Duplicate server '" << cur_conf.name[i] << "'on port: " << cur_conf.port << std::endl;
                throw std::runtime_error(oss.str());
                }
            }
        }
    }             
    configs.push_back(cur_conf);
    in_server = false;
}
