#ifndef APP_CALLBACK_H
#define APP_CALLBACK_H

#include <string>

#include "tcp_client.h"

std::string applicationMessageCallback(TCPClient *client, std::string &message);

#endif
