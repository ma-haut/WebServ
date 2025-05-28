/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_location.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 11:30:43 by achantra          #+#    #+#             */
/*   Updated: 2025/05/26 16:58:12 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "parse_config.hpp"

// Set the configuration of the location
void    set_location_config(std::istringstream& iss, std::string& token, LocationConfig& cur_loc,
            int& brace_count, ServerConfig& cur_conf, bool& in_location){
    if (token == "root")
        iss >> cur_loc.root;
    else if (token == "autoindex")
        set_autoindex(iss, cur_loc);
    else if (token == "cgi")
        set_cgi(iss, cur_loc);
    else if (token == "index")
        set_index(iss, cur_loc);
    else if (token == "methods")
        set_methods(iss, cur_loc);
    else if (token == "return")
        set_return(iss, cur_loc);
    else if (token == "}")
        close_location_section(brace_count, cur_conf, cur_loc, in_location);
    else
        std::cerr << "Warning: Unknown directive '" << token << "'" << std::endl;
}

void    set_cgi(std::istringstream& iss, LocationConfig& cur_loc){
    std::string ext;
    iss >> ext;
    if (ext.size() < 2 || ext[0] != '.'){
        std::ostringstream oss;
        oss << "Invalid cgi extension: " << ext;
        throw std::runtime_error(oss.str());
    }
    std::string path;
    iss >> path;
    if (path.empty())
        throw std::runtime_error("Missing cgi path");
    cur_loc.cgi_map[ext] = path;
}

void    set_return(std::istringstream& iss, LocationConfig& cur_loc){
        std::string code_value;
        iss >> code_value;
        
        for (size_t i = 0; i < code_value.size(); i++){
            if (!std::isdigit(code_value[i])){
                std::ostringstream oss;
                oss << "Invalid return code value: " << code_value;
                throw std::runtime_error(oss.str());
            }
        }
        std::stringstream ss(code_value);
        int code;
        ss >> code;
        cur_loc.return_code = code;
        std::string url;
        iss >> url;
        if (url.empty())
            throw std::runtime_error("Missing return url");
        cur_loc.return_url = url;
}

void    set_index(std::istringstream& iss, LocationConfig& cur_loc){
        std::string sindex;
        while (iss >> sindex)
            cur_loc.index.push_back(sindex);
}

void    set_methods(std::istringstream& iss, LocationConfig& cur_loc){
        std::string smethods;
        while (iss >> smethods)
            cur_loc.methods.push_back(smethods);
}

// Set autoindex value
void    set_autoindex(std::istringstream& iss, LocationConfig& cur_loc){
    std::ostringstream oss;
    std::string value;
    iss >> value;
    if (value != "on" && value != "off"){
        oss << "Invalid autoindex value: " << value;
        throw std::runtime_error(oss.str());
    }
    cur_loc.autoindex = (value == "on");
}

// End the location section
void    close_location_section(int& brace_count, ServerConfig& cur_conf, LocationConfig& cur_loc, bool& in_location){
    std::ostringstream oss;
    brace_count--;
    if (brace_count < 0)
        throw std::runtime_error("Unexpected closing '}' in config file");
    for (size_t i = 0; i < cur_conf.locations.size(); i++){
        if (cur_conf.locations[i].path == cur_loc.path){
            oss << "Duplicate location path: " << cur_loc.path;
            throw std::runtime_error(oss.str());
        }
    }
    cur_conf.locations.push_back(cur_loc);
    in_location = false;
}


