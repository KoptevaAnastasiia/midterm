#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <fstream>

#define PORT 18756
#define BUFFER_SIZE 1024


/*     uint8_t variant = 0x12; // - 18*/



void sendCommand(int clientSocket, const std::string& command);
//void sendFile(int clientSocket, const std::string& filename);

/*
std::string trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");
    return (first == std::string::npos) ? "" : str.substr(first, last - first + 1);
}
*/


void sendCommand(int clientSocket, const std::string& command){
    send(clientSocket, command.c_str(), command.size(), 0);

    char buffer[BUFFER_SIZE];
    ssize_t bytesReceived = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::cout << "Response:\n" << buffer << std::endl;}
}
int main() {


 int port = 18756;
 const char* serverIp = "3.78.28.71";



 // Create a TCP socket
 int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
 if (clientSocket == -1) {
 perror("Error creating socket");
 return 1;
 }

/*sockaddr_in – структура, яка містить інформацію про сервер.*/

 // Connect the socket to the server's address and port
 sockaddr_in serverAddr{};
 serverAddr.sin_family = AF_INET;  /*використовується IPv4*/
 serverAddr.sin_port = htons(port);  /*переводить число у "мережевий порядок байтів"  (Протокол TCP/IP завжди використовує Big-Endian.)*/
 inet_pton(AF_INET, serverIp, &(serverAddr.sin_addr));  /*перетворює текстову IP-адресу у бінарну форму, щоб її можна було використовувати у sockaddr_in*/

 /*af = AF_INET – означає, що працюємо з IPv4.
 src = serverIp – IP-адреса у форматі 127.0.0.1.
 dst = &(serverAddr.sin_addr) – вказівник, куди записати бінарну IP-адресу.*/




 if (connect(clientSocket, reinterpret_cast<struct sockaddr*>(&serverAddr), sizeof(serverAddr)) == -1) {
 perror("Connect failed");
 close(clientSocket);
 return 1;}



 std::string command;
std::cout << " command > ";
std::getline(std::cin, command);
    /*command = trim(command);*/
    sendCommand(clientSocket, command);


    uint32_t response_length;

    if (recv(clientSocket, &response_length, sizeof(response_length), 0) <= 0) {
        std::cerr << "Помилка отримання довжини відповіді\n";
        close(clientSocket);
        return 1;
    }

    response_length = ntohl(response_length);


    char* buffer = new char[response_length + 1];
    if (recv(clientSocket, buffer, response_length, 0) <= 0) {
        std::cerr << "Помилка отримання повідомлення\n";
        delete[] buffer;
        close(clientSocket);
        return 1;
    }
    buffer[response_length] = '\0';


    std::cout << "Отримане повідомлення від сервера: " << buffer << std::endl;


};











