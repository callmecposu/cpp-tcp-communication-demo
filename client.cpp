#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>

int main(){
    // Create a client socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    // Define server address
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(3001);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    std::cout << "server address: " << server_addr.sin_addr.s_addr << '\n';
    // Connect client socket to the server socket
    connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    // Send a message to server
    char msg[1024] = "wsuppp";
    send(client_socket, msg, strlen(msg), 0);
    // Read a response from server;
    char buffer[1024];
    recv(client_socket, buffer, sizeof(buffer), 0);
    std::cout << "Response: " << buffer << '\n';
    // Close the client socket
    close(client_socket);
    return 0;


}