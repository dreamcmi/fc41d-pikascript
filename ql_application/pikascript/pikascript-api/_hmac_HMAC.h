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

#ifndef ___hmac_HMAC__H
#define ___hmac_HMAC__H
#include <stdio.h>
#include <stdlib.h>
#include "PikaObj.h"

PikaObj *New__hmac_HMAC(Args *args);

void _hmac_HMAC_copy(PikaObj *self);
Arg* _hmac_HMAC_digest(PikaObj *self);
char* _hmac_HMAC_hexdigest(PikaObj *self);
void _hmac_HMAC_new(PikaObj *self, Arg* key, Arg* msg, char* digestmod);
void _hmac_HMAC_update(PikaObj *self, Arg* msg);

#endif