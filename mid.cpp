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



std:: string recvStr(int clientSoket) {

    uint32_t len ;
    recvData(clientSoket, &len, sizeof(len));
    len = ntohl(len);
    char buffer[BUFFER_SIZE] = {0};
    recvData(clientSoket, buffer, len);

    return std::string(buffer);


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







    uint32_t messeg_name_lendth;
    recvData(clientSocket, &messeg_name_lendth, sizeof(messeg_name_lendth));
    messeg_name_lendth = ntohl(messeg_name_lendth);

    char buffer[messeg_name_lendth + 1];
    recvData(clientSocket, buffer, messeg_name_lendth);
    buffer[messeg_name_lendth] = '\0';

    std::cout << buffer << std::endl;


    std::string my_name;
    std::cout << "Enter your name: ";

    std::cin >> my_name;


    uint32_t name_length = htonl(my_name.size());
    sendCommand(clientSocket, &name_length, sizeof(name_length));

    sendCommand(clientSocket, my_name.c_str(), my_name.size());






    uint32_t messeg_lastname_lendth;
    recvData(clientSocket, &messeg_lastname_lendth, sizeof(messeg_lastname_lendth));
    messeg_lastname_lendth = ntohl(messeg_lastname_lendth);

    char buffer_lastname[messeg_lastname_lendth + 1];
    recvData(clientSocket, buffer_lastname, messeg_lastname_lendth);
    buffer_lastname[messeg_lastname_lendth] = '\0';

    std::cout << buffer_lastname << std::endl;


    std::string my_lastname;
    std::cout << "Enter your lastname: ";

    std::cin >> my_lastname;


    uint32_t lastname_length = htonl(my_lastname.size());
    sendCommand(clientSocket, &lastname_length, sizeof(lastname_length));

    sendCommand(clientSocket, my_lastname.c_str(), my_lastname.size());


    uint8_t variant = 0x12;
    sendCommand(clientSocket, &variant, sizeof(variant));
    std::cout << "send--" << std::hex << (int)variant << std::endl;


    std::string response = recvStr(clientSocket);
    std::cout << response << std::endl;














    uint16_t question_num1 = htons(1);
    sendCommand(clientSocket, &question_num1, sizeof(question_num1));
    std::string question1 = recvStr(clientSocket);
    std::cout  << question1 << std::endl;
    std::string answer1;
    std::cout << "Enter your answer: ";
    std::cin.ignore();
    std::getline(std::cin, answer1);
    uint32_t answerLength1 = htonl(answer1.size());
    sendCommand(clientSocket, &answerLength1, sizeof(answerLength1));
    sendCommand(clientSocket, answer1.c_str(), answer1.size());
    std::cout << recvStr(clientSocket) << std::endl;

    uint16_t question_num2 = htons(2);
    sendCommand(clientSocket, &question_num2, sizeof(question_num2));
    std::string question2 = recvStr(clientSocket);
    std::cout <<  question2 << std::endl;
    std::string answer2;
    std::cout << "Enter your answer:";
    std::getline(std::cin, answer2);
    uint32_t answerLength2 = htonl(answer2.size());
    sendCommand(clientSocket, &answerLength2, sizeof(answerLength2));
    sendCommand(clientSocket, answer2.c_str(), answer2.size());
    std::cout <<  recvStr(clientSocket) << std::endl;

    uint16_t question_num3 = htons(3);
    sendCommand(clientSocket, &question_num3, sizeof(question_num3));
    std::string question3 = recvStr(clientSocket);
    std::cout  << question3 << std::endl;
    std::string answer3;
    std::cout << "Enter your answer:";
    std::getline(std::cin, answer3);
    uint32_t answerLength3 = htonl(answer3.size());
    sendCommand(clientSocket, &answerLength3, sizeof(answerLength3));
    sendCommand(clientSocket, answer3.c_str(), answer3.size());
    std::cout <<  recvStr(clientSocket) << std::endl;


    uint16_t question_num4 = htons(4);
    sendCommand(clientSocket, &question_num4, sizeof(question_num4));
    std::string question4 = recvStr(clientSocket);
    std::cout << question4 << std::endl;
    std::string answer4;
    std::cout << "Enter your answer: ";
    std::getline(std::cin, answer4);
    uint32_t answerLength4 = htonl(answer4.size());
    sendCommand(clientSocket, &answerLength4, sizeof(answerLength4));
    sendCommand(clientSocket, answer4.c_str(), answer4.size());
    std::cout  << recvStr(clientSocket) << std::endl;


    uint16_t questionID5 = htons(5);
    sendCommand(clientSocket, &questionID5, sizeof(questionID5));
    std::string question5 = recvStr(clientSocket);
    std::cout  << question5 << std::endl;
    std::string answer5;
    std::cout << "Enter your answer:";
    std::getline(std::cin, answer5);
    uint32_t answerLength5 = htonl(answer5.size());
    sendCommand(clientSocket, &answerLength5, sizeof(answerLength5));
    sendCommand(clientSocket, answer5.c_str(), answer5.size());
    std::cout   << recvStr(clientSocket) << std::endl;




    std::cout << "server" << recvStr(clientSocket) << std::endl;


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











