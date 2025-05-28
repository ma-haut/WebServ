/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:10:51 by achantra          #+#    #+#             */
/*   Updated: 2025/05/26 14:06:39 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

int main(int ac, char **av) {
    try{
        if (ac > 3){
            std::cerr << "Usage: ./webserv <config_file>" << std::endl;
            return (1);
        }
        std::vector<ServerConfig> s_configs;
        if (ac < 2){
            // Parse the default conf
            s_configs = parse_config((char *)"server.conf");
        }
        
        else if (ac == 2){
            // Parse the given conf
            s_configs = parse_config(av[1]);
        }
        RealServer re = RealServer(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 1, s_configs);
    }
    catch (const std::exception& e){
        std::cerr << "Config error: " << e.what() << std::endl;
    }
}       
