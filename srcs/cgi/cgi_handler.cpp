/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cgi_handler.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achantra <achantra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 14:57:27 by achantra          #+#    #+#             */
/*   Updated: 2025/05/27 11:45:18 by achantra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cgi_handler.hpp"

int   cgi_process(char *script_path, char *cgi_path, std::string& request_body, std::string& cgi_response){
    int fd_in[2];
    int fd_out[2];
    std::vector<std::string> envp = setup_env();
    
    if (pipe(fd_in) == -1 || pipe(fd_out) == -1) {
        perror("pipe");
        return (-1);
    }
    
    pid_t pid = fork();
    if (pid < 0){
        perror("fork");
        return (-1);
    }
    
    // Child process
    if (pid == 0)
        child_process(envp, script_path, cgi_path, fd_in, fd_out);
    
    // Parent process
    else
        return (parent_process(fd_in, fd_out, pid, request_body, cgi_response));
}

void    child_process(std::vector<std::string>& env_strings, char *script_path, char *cgi_path, int *fd_in, int *fd_out){
    // Set argv
    char *argv[3];
    set_argv(argv, script_path, cgi_path);
    if (!is_executable(argv[0])){
        close(fd_in[1]);
        close(fd_in[0]);
        close(fd_out[0]);
        close(fd_out[1]);
        exit(1);
    }
    // Convert env to char *
    std::vector<char*> envp;
    for (size_t i = 0; i < env_strings.size(); ++i)
        envp.push_back(const_cast<char*>(env_strings[i].c_str()));
    envp.push_back(NULL);
    
    close(fd_in[1]);
    if (dup2(fd_in[0], STDIN_FILENO) == -1) {
        perror("dup2 stdin");
        exit(1);
    }
    close(fd_in[0]);

    close(fd_out[0]);
    if (dup2(fd_out[1], STDOUT_FILENO) == -1) {
        perror("dup2 stdout");
        exit(1);
    }
    close(fd_out[1]);
    
    //Execute
    execve(argv[0], argv, envp.data());
    
    // If execve fails
    perror("execve");
    exit(1);
}

int    parent_process(int *fd_in, int *fd_out, pid_t pid, std::string& request_body, std::string& cgi_response){
        close(fd_in[0]);
        close(fd_out[1]);
        int status;
        
        // Transmission of the body
        if (!request_body.empty()) {
            if (transmit_body(fd_in[1], request_body) == -1){
                close(fd_in[1]);
                close(fd_out[0]);
                waitpid(pid, &status, 0);
                return (-1);
            }
        }
        close(fd_in[1]);
        
        //Reading the result of execve in the child
        if (read_result(fd_out[0], cgi_response) == -1){
            close(fd_out[0]);
            waitpid(pid, &status, 0);
            return (-1);
        }
        close(fd_out[0]);
        
        // Wait for the child
        waitpid(pid, &status, 0);
        //Check the exit status of the child
        if (WIFEXITED(status)) {
            int exit_status = WEXITSTATUS(status);
            if (exit_status != 0) {
                std::cerr << "CGI script exited with status " << exit_status << std::endl;
                return (-1);
            }
        }
        else {
            std::cerr << "CGI script terminated abnormally" << std::endl;
            return (-1);
        }
        return (0);
}