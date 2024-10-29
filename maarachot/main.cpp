#include <iostream>


void start_tcp_server(int port);
void start_tcp_client(const char* ip, int port);

int main(int argc, char *argv[]) {
    
    start_tcp_server(4050);
    start_tcp_client("127.0.0.1", 4050);

    std::cout << "Program completed successfully" << std::endl;
    return 0;
}
