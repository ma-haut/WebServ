/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 15:22:17 by achantra          #+#    #+#             */
/*   Updated: 2025/05/26 17:40:48 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parse_config.hpp"

//Parse the .conf file
std::vector<ServerConfig>    parse_config(char *conf){
    //Open
    std::ifstream file(conf);
    if (!file)
        throw std::runtime_error("Cannot open config file" + std::string(conf));
    
    std::vector<ServerConfig> configs;
    std::string line, full_line, token;
    ServerConfig cur_conf;
    bool in_server, in_location = false;
    LocationConfig cur_loc;
    std::ostringstream oss;
    int brace_count = 0;
    // Read
    while (std::getline(file, line)){
        clean_line(line);
        if (line.empty())
            continue;
        full_line += line;
        // Read until reaching ;, { or }
        if (line.find(';') != std::string::npos ||
                line.find('{') != std::string::npos ||
                line.find('}') != std::string::npos){
            // Supress ';'
            full_line.erase(std::remove(full_line.begin(), full_line.end(), ';'), full_line.end());
                    
            std::istringstream iss(full_line);
            full_line.clear();
            // Read word by word
            iss >> token;
            if (token.empty())
                continue;
            // Server bloc
            if (token == "server")
                new_server_conf(iss, brace_count, in_server, cur_conf);
            // New bloc in a server bloc
            else if (in_server && !in_location)
                set_server_conf(iss, token, cur_conf,brace_count,
                    in_location, cur_loc, configs, in_server);
            // New bloc in a location bloc
            else if (in_server && in_location)
                set_location_config(iss, token, cur_loc, brace_count, cur_conf, in_location);
            // Unknown bloc
            else
                std::cerr << "Warning: Unknown directive '" << token << "'" << std::endl;
        }
        // Separate last word of first line and first word of second line
        else
            full_line += " ";
    }
    // Check the bracket consistancy
    if (brace_count != 0)
        throw std::runtime_error("Unmatched braces in config file");
    //Debug
    print_config(configs);
    return configs;
}

// Get rid of extra spaces
void    clean_line(std::string& line){
    // Supress comments
    size_t comment_pos = line.find('#');
    if (comment_pos != std::string::npos)
        line = line.substr(0, comment_pos);
    
    // Trim spaces
    line.erase(0, line.find_first_not_of(" \t"));
    line.erase(line.find_last_not_of(" \t") + 1);
}

// Debug parsing
void    print_config(std::vector<ServerConfig> configs){
    for (size_t i = 0; i < configs.size(); i ++){
        std::cout << "port = " << configs[i].port << std::endl;
        std::cout << "host = " << configs[i].host << std::endl;
        std::cout << "max_size = " << configs[i].client_max_body_size << std::endl;
        for (std::vector<std::string>::iterator it = configs[i].name.begin(); it != configs[i].name.end(); ++it)
            std::cout << "name = " << *it << std::endl;
        std::cout << "root = " << configs[i].root << std::endl;
        std::cout << "Error pages:" << std::endl;
        for (std::map<int, std::string>::iterator it = configs[i].error_pages.begin(); it != configs[i].error_pages.end(); ++it)
            std::cout <<"   " << it->first << " : " << it->second << std::endl;
        
        std::cout << "Locations: " << std::endl;
        for (size_t j = 0; j < configs[i].locations.size(); j++) {
            const LocationConfig& loc = configs[i].locations[j];
            std::cout << " Location = " << loc.path << std::endl;
            std::cout << "  root = " << loc.root << std::endl;
            std::cout << "  autoindex = " << (loc.autoindex ? "on" : "off") << std::endl;
            for (std::map<std::string, std::string>::iterator it = configs[i].locations[j].cgi_map.begin(); it != configs[i].locations[j].cgi_map.end(); ++it)
                std::cout << "  cgi: " << it->first <<" => " << it->second  << std::endl;
            for (std::vector<std::string>::iterator it = configs[i].locations[j].index.begin(); it != configs[i].locations[j].index.end(); ++it)
                std::cout << "  index = " << *it << std::endl;
            for (std::vector<std::string>::iterator it = configs[i].locations[j].methods.begin(); it != configs[i].locations[j].methods.end(); ++it)
                std::cout << "  methods = " << *it << std::endl;
            std::cout << "  return code = " << loc.return_code << std::endl;
            std::cout << "  return url = " << loc.return_url << std::endl;
        }
        std::cout << std::endl;
    }
}