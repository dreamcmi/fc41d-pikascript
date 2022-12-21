/*
 * [Warning!] This file is auto-generated by pika compiler.
 * Do not edit it manually.
 * The source code is *.pyi file.
 * More details: 
 * English Doc:
 * https://pikadoc.readthedocs.io/en/latest/PikaScript%20%E6%A8%A1%E5%9D%97%E6%A6%82%E8%BF%B0.html
 * Chinese Doc:
 * https://pikadoc.readthedocs.io/zh/latest/PikaScript%20%E6%A8%A1%E5%9D%97%E6%A6%82%E8%BF%B0.html
 */

#ifndef ___socket_socket__H
#define ___socket_socket__H
#include <stdio.h>
#include <stdlib.h>
#include "PikaObj.h"

PikaObj *New__socket_socket(Args *args);

void _socket_socket__accept(PikaObj *self);
void _socket_socket__bind(PikaObj *self, char* host, int port);
void _socket_socket__close(PikaObj *self);
void _socket_socket__connect(PikaObj *self, char* host, int port);
void _socket_socket__init(PikaObj *self);
void _socket_socket__listen(PikaObj *self, int num);
Arg* _socket_socket__recv(PikaObj *self, int num);
void _socket_socket__send(PikaObj *self, Arg* data);

#endif