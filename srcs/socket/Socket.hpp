/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Socket.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 13:50:36 by achantra          #+#    #+#             */
/*   Updated: 2025/05/16 11:56:02 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOCKET_HPP
# define SOCKET_HPP

# include <sys/socket.h>
# include <netinet/in.h>
# include <iostream>
# include "../utils/utils.hpp"
# include <string.h>

class Socket{
    protected:
        struct sockaddr_in _address;
        int _sock;

        // Constructor
        Socket(void);
        Socket(int domain, int service, int protocol,
            int port, u_long interface);
        Socket(const Socket& s);
        Socket& operator=(const Socket& s);
    
     public :
        //Destructor
        virtual ~Socket();
        
        //Getter
        struct sockaddr_in get_address() const;
        int get_sock() const;
    };      

#endif