/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RealServer_routine.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:33:46 by achantra          #+#    #+#             */
/*   Updated: 2025/05/26 12:03:39 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RealServer.hpp"


bool running = true;

// Handle signal for a clean shutdown
void signal_handler(int signal){
    if (signal == SIGINT){
        running = false;
        std::cout << "\nShutting down server" << std::endl;
    }
}

void RealServer::launch(){
    //Signal handler
    signal(SIGINT, signal_handler);
    // FD for select
    fd_set read_set, write_set;

    // Timeout for select
    struct timeval timeout;
    
    while (running){
        std::cout << "====== WAITING ======" << std::endl;
        
        // Detect reading timeout
        check_read_timeout();
        // Detect writing timeout
        check_write_timeout();

        // Copy master sets
        read_set = _master_read_set;
        write_set = _master_write_set;
        
        // Init timeout at 1sec
        init_timer(1, 0, &timeout);
        
        // Wait for an event
        int ret = select(_max_fd + 1, &read_set, &write_set, NULL, &timeout);
        if (ret < 0){
            perror("select");
            break;
        }
        
        // Timeout reached without any event
        if (!ret)
            continue;
        
        // Search for ready fd to read
        fd_read(&read_set);
        // Search for ready fd to write
        fd_write(&write_set);
    }
    stop_server();
}