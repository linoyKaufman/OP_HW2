#ifndef MYNC_HPP
#define MYNC_HPP

#include <string>

void start_tcp_server(int port);
void start_tcp_client(const char* ip, int port);
void execute_program(const char* program);
void start_unix_datagram_server(const char *path);
void start_unix_datagram_client(const char *path);
void start_unix_stream_server(const char *path);
void start_unix_stream_client(const char *path);

#endif // MYNC_HPP
