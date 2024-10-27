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

// פונקציות TCP
void start_tcp_server(int port);
void start_tcp_client(const char* ip, int port);

// פונקציות UDP
void start_udp_server(int port);
void start_udp_client(const char* ip, int port);

// פונקציית הרצת תוכנה
void execute_program(const char* program);

// פונקציית הטיימאוט
void timeout_handler(int signum) {
    cout << "Timeout reached, exiting..." << endl;
    exit(0);
}

void start_unix_datagram_server(const char *path) {
    int sockfd;
    struct sockaddr_un server_addr;

    if ((sockfd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, path, sizeof(server_addr.sun_path) - 1);

    unlink(path); // להסרת הקובץ הקודם במידה והוא קיים
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Unix Datagram Server listening on %s\n", path);
    char buffer[1024];
    recvfrom(sockfd, buffer, sizeof(buffer), 0, NULL, NULL);
    printf("Received from client: %s\n", buffer);
    close(sockfd);
}

void start_unix_datagram_client(const char *path) {
    int sockfd;
    struct sockaddr_un server_addr;

    if ((sockfd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, path, sizeof(server_addr.sun_path) - 1);

    const char *message = "Hello from Unix Datagram Client!";
    sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
    printf("Message sent to server\n");
    close(sockfd);
}

void start_unix_stream_server(const char *path) {
    int server_fd, client_fd;
    struct sockaddr_un server_addr;

    if ((server_fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, path, sizeof(server_addr.sun_path) - 1);

    unlink(path); 
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 1) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Unix Stream Server listening on %s\n", path);
    if ((client_fd = accept(server_fd, NULL, NULL)) < 0) {
        perror("accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    read(client_fd, buffer, sizeof(buffer));
    printf("Received from client: %s\n", buffer);

    close(client_fd);
    close(server_fd);
}

void start_unix_stream_client(const char *path) {
    int sockfd;
    struct sockaddr_un server_addr;

    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, path, sizeof(server_addr.sun_path) - 1);

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    const char *message = "Hello from Unix Stream Client!";
    send(sockfd, message, strlen(message), 0);
    printf("Message sent to server\n");
    close(sockfd);
}


int main(int argc, char *argv[]) {
    char *exec_program = nullptr;
    char *input_source = nullptr;
    char *output_dest = nullptr;
    int opt;

    while ((opt = getopt(argc, argv, "e:i:o:")) != -1) {
        switch (opt) {
            case 'e':
                exec_program = optarg;
                break;
            case 'i':
                input_source = optarg;
                break;
            case 'o':
                output_dest = optarg;
                break;
            default:
                cerr << "Usage: " << argv[0] << " -e <program> [-i input] [-o output]" << endl;
                exit(EXIT_FAILURE);
        }
    }

    if (exec_program) {
        if (input_source) {
            if (strncmp(input_source, "UDSSD", 5) == 0) {
                start_unix_datagram_server(input_source + 5);
            } else if (strncmp(input_source, "UDSSS", 5) == 0) {
                start_unix_stream_server(input_source + 5);
            }
        }
        if (output_dest) {
            if (strncmp(output_dest, "UDSCD", 5) == 0) {
                start_unix_datagram_client(output_dest + 5);
            } else if (strncmp(output_dest, "UDSCS", 5) == 0) {
                start_unix_stream_client(output_dest + 5);
            }
        }

        execute_program(exec_program);
    } else {
        cerr << "Error: No program specified with -e" << endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}

// פונקציה להרצת תוכנה
void execute_program(const char* program) {
    pid_t pid = fork();
    if (pid == 0) {
        execl("/bin/sh", "sh", "-c", program, nullptr);
        perror("execl failed");
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        wait(nullptr);
    } else {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }
}

// פונקציית שרת TCP (קלט בלבד)
void start_tcp_server(int port) {
    // ... מימוש כפי שהצגת קודם
}

// פונקציית לקוח TCP (פלט בלבד)
void start_tcp_client(const char* ip, int port) {
    // ... מימוש כפי שהצגת קודם
}

// פונקציית שרת UDP (קלט בלבד)
void start_udp_server(int port) {
    int sock;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t cli_len = sizeof(cli_addr);
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if (bind(sock, (const struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        perror("bind failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    cout << "UDP Server listening on port " << port << endl;

    // קריאת הודעות מהלקוח
    int n = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &cli_addr, &cli_len);
    buffer[n] = '\0';
    cout << "Received from client: " << buffer << endl;
    close(sock);
}

// פונקציית לקוח UDP (פלט בלבד)
void start_udp_client(const char* ip, int port) {
    int sock;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &serv_addr.sin_addr);

    const char* message = "Hello from UDP client!";
    sendto(sock, message, strlen(message), 0, (const struct sockaddr *) &serv_addr, sizeof(serv_addr));
    cout << "Message sent to UDP server" << endl;
    close(sock);
}
