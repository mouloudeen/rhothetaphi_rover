/**
 *\file Header.h
 *\brief Liste des prototypes de fonctions et bibliothèques utilisées
 *\author Quentin BLECHET, Bixente BURUCOA, Sid Ali ZITOUNI TERKI
 *\version V1
 *\date 5 juin 2023
 */


#ifndef Header_h
#define Header_h

#include <unistd.h>
#include <arpa/inet.h>
#include <linux/can.h>
#include <linux/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include "lib/cJSON.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>

/**
*\def password
 */
 #define password "ckai8MEoQ3cky6qHBqN7"

// Socket
/**
 *\struct sockaddr_in
 *\brief  Structure décrivant l'adresse du réseau
 */
typedef struct sockaddr_in sockaddr_in;

int creation_sock(void);
int init_sock(void);
void init_addr(struct sockaddr_in, int, char *, int);
int bindSock(struct sockaddr_in, int, int);

// Token
void direction(cJSON *);
void accroche(cJSON *);
void mine(cJSON *);
void askNbMine(cJSON *);
void arm(cJSON *);

// Client
void sendClient(int id);
void sendJson(cJSON *, char *, int);
cJSON *createJsonConfirmAccroche();
cJSON *createJsonConfirmMine();
cJSON *createJsonPosition(double, double);
cJSON *createJsonSpeed(double);
cJSON *createJsonRadar(double, double);
cJSON *createJsonNbMine(int);

#endif /* Header_h */
