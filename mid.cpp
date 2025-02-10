#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <fstream>

#define PORT 18756
#define BUFFER_SIZE 1024


/*     uint8_t variant = 0x12; // - 18*/



void sendCommand(int clientSocket, const void*data, size_t size )
{
    ssize_t bytesSent = send(clientSocket, data, size, 0) ;
    if ( bytesSent <=0 ) {

        perror("send error");
        exit(1);
    }

}


void recvData(int clientSoket, void*buffer, size_t size) {
    ssize_t bytesRead = recv(clientSoket, buffer, size, 0);
if (bytesRead <= 0) {
    perror("recv error");
    exit(1);
}

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


    uint32_t connectionID;
    recvData(clientSocket, &connectionID, sizeof(connectionID));
    std::cout << "Connection ID: " << ntohl(connectionID) << std::endl;


    sendCommand(clientSocket, &connectionID, sizeof( connectionID));

    close(clientSocket);
    return 0;





}


 /*
 std::string command;
std::cout << " command > ";
std::getline(std::cin, command);
    /*command = trim(command);#1#
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
*/











