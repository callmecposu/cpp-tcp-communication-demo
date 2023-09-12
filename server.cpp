#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

int main()
{
    // Create a server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    // Define server address
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(3001);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    // Bind the server socket to its address
    bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    // Listen for connections
    listen(server_socket, 5);
    std::cout << "Server now listening on port 3001..." << '\n';
    std::cout << "address: " << server_addr.sin_addr.s_addr << '\n';

    // Declare client socket addr & len
    sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    // Create client socket on connection
    int client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len);
    // Read from client socket
    char buffer[1024] = {0};
    recv(client_socket, buffer, sizeof(buffer), 0);
    std::cout << "Data received: " << buffer << '\n';
    // "Generate" a response
    strcat(buffer, " - this was your request");
    // Send a response to client socket
    send(client_socket, buffer, strlen(buffer), 0);
    // Close the sockets
    close(server_socket);
    close(client_socket);
    return 0;
}