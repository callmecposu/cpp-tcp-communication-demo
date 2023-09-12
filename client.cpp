#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <fstream>

int main(int argc, char **argv)
{
    // Break if no filename specified
    if (argc == 1)
    {
        std::cout << "No filename specified, exitting\n";
        exit(EXIT_FAILURE);
    }
    // Read a data to be sent from a file
    std::ifstream fs(argv[1]);
    if (!fs.is_open())
    {
        std::cout << "File \'" << argv[1] << "\' does not exist\n";
        exit(EXIT_FAILURE);
    }
    char *msg = nullptr;
    fs.seekg(0, std::ios::end);
    int msg_len = fs.tellg();
    fs.seekg(0);
    msg = new char[msg_len + 1];
    fs.read(msg, msg_len);
    fs.close();
    // Create a client socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    // Define server address
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(3001);
    server_addr.sin_addr.s_addr = INADDR_ANY;
    std::cout << "server address: " << server_addr.sin_addr.s_addr << '\n';
    // Connect client socket to the server socket
    connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr));
    // Send a message to server
    send(client_socket, msg, strlen(msg), 0);
    // Read a response from server;
    char buffer[1024];
    recv(client_socket, buffer, sizeof(buffer), 0);
    std::cout << "Response: " << buffer << '\n';
    // Close the client socket
    close(client_socket);

    delete[] msg;

    return 0;
}