#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <getopt.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/un.h> 

using namespace std;

// timeout func
void timeout_handler(int signum) {
    (void)signum; // paraneter not in use
    cout << "Timeout reached, exiting..." << endl;
    exit(0);
}

void start_tcp_server(int port) {
    (void)port; // paraneter not in use
    cout << "TCP server function called" << endl;
}

void start_tcp_client(const char* ip, int port) {
    (void)ip; // paraneter not in use
    (void)port; //paraneter not in use
    cout << "TCP client function called" << endl;
}
