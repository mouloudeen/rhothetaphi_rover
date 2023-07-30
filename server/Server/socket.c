/**
 *\file socket.c
 *\brief  Liste des fonctions pour la communication TCP
 *\author Quentin BLECHET, Bixente BURUCOA, Sid Ali ZITOUNI TERKI
 *\version V1
 *\date 5 juin 2023
 *
 * Ensemble de fonctions permettant le bon fonctionnement de la communication TCP entre le serveur et le client.
 */
#include "Header.h"

/**
 *\fn int creation_sock(void)
 *\brief Fonction permettant la création d'un socket dans la partie serveur
 *
 *\return int: la valeur du socket
 */
int creation_sock(void)
{
	int ptr;
	ptr = socket(AF_INET, SOCK_STREAM, 0);
	if (ptr < 0)
	{
		perror("[-]Socket error");
		exit(1);
	}
	printf("[+]TCP server socket created.\n");
	return ptr;
}

/**
 *\fn int bindSock(sockaddr_in server_addr, int port, int server_sock)
 *\brief Fonction qui relie un socket à une atre socket de destination dans la partie serveur
 *
 *\param[in] server_addr: structure de l'adresse de destination
 *\param[in] port: port de destination
 *\param[in] server_sock: socket qui est relié au socket externe
 *\return int: la valeur du bind
 */
int bindSock(sockaddr_in server_addr, int port, int server_sock)
{
	memset(&server_addr, '\0', sizeof(server_addr));

	sockaddr_in *ptrAddr;
	ptrAddr = &server_addr;
	ptrAddr->sin_family = AF_INET;
	ptrAddr->sin_port = ntohs(port);
	ptrAddr->sin_addr.s_addr = INADDR_ANY; // inet_addr(ip);

	int n = bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr));
	if (n < 0)
	{
		perror("[-]Bind error");
		exit(1);
	}
	printf("[+]Bind to the port number: %d\n", port);
	return n;
}

/**
 *\fn init_addr(struct sockaddr_in adresse, int socket, char *pt, int entree)
 *\brief Fonction qui relie un socket à une atre socket de destination dans la partie client
 *
 *\param[in] adresse: structure de l'adresse du serveur
 *\param[in] socket: le socket d'envoie
 *\param[in] *pt: adresse ip
 *\param[in] entree: port d'entrée
 *\return Aucun
 */
void init_addr(struct sockaddr_in adresse, int socket, char *pt, int entree)
{
	memset(&adresse, '\0', sizeof(adresse));
	adresse.sin_family = AF_INET;
	adresse.sin_port = htons(entree);
	adresse.sin_addr.s_addr = inet_addr(pt);

	connect(socket, (struct sockaddr *)&adresse, sizeof(adresse));
	printf("Connected to the server.\n");
}

/**
 *\fn int init_sock(void)
 *\brief Fonction permettant la création d'un socket dans la partie client
 *
 *\return Aucun
 */
int init_sock(void)
{
	int sock;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		perror("[-]Socket error");
		exit(1);
	}
	printf("[+]TCP server socket created.\n");
	return sock;
}
