#include <iostream>

// הכרזת פונקציות מmync.cpp כדי שהן יהיו נגישות ל-main
void start_tcp_server(int port);
void start_tcp_client(const char* ip, int port);

int main(int argc, char *argv[]) {
    // דוגמה לשימוש בפונקציות שהוגדרו בmync.cpp
    start_tcp_server(4050);
    start_tcp_client("127.0.0.1", 4050);

    std::cout << "Program completed successfully" << std::endl;
    return 0;
}
