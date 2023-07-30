/**
 *\file server.c
 *\brief Programme principale qui initialise la communication TCP et qui gère la communication reçu par le serveur
 *\author Quentin BLECHET, Bixente BURUCOA, Sid Ali ZITOUNI TERKI
 *\version V1
 *\date 5 juin 2023
 *
 *\ Programme *
 */
#include "Header.h"
#include <stdio.h>

/**
* \fn int main (void)
* \brief Entrée du programme.
*
* \return EXIT_SUCCESS - Arrêt normal du programme.
* \return EXIT_FAILURE - Arrêt anormal du programme.
*/
int main()
{
    // structure of cJSON
    cJSON *parsed_json;
    cJSON *pass;

    int port = 8082;

    int server_sock, client_sock;
    sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    char buffer[1024];
    int n;

    
    // création du sock
    server_sock = creation_sock();

    // liaison connexion
    n = bindSock(server_addr, port, server_sock);

    // en attente d'instruction
    listen(server_sock, 1);
    printf("Listening...\n");

    // boucle infinie /en écoute
    while (1)
    {
        addr_size = sizeof(client_addr);
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &addr_size);
        printf("[+]Client connected.\n");

        // récupération du json
        bzero(buffer, 1024);
        recv(client_sock, buffer, sizeof(buffer), 0);
        

        parsed_json = cJSON_Parse(buffer);
        // retrieve the paswword of the json_parsed
        pass = cJSON_GetObjectItem(parsed_json, "password");

        // password n'existe pas
        if (pass == NULL)
        {
            printf("\nPassword does not exist\n");
            printf("[-]Client disconnected.\n\n");
            continue;
        }

        // si mot de passe invalide -> déconnexion du client
        else if (strcmp(pass->valuestring, password) != 0)
        {
            bzero(buffer, 1024);
            strcpy(buffer, "INVALID Password.\n");
            send(client_sock, buffer, sizeof(buffer), 0);
            printf("\nInvalid Password.\n");
            printf("[-]Client disconnected.\n\n");
        }

        // si mot de passe valide -> affiche les données.
        else
        {
            cJSON *token;
            cJSON *value;
            token = cJSON_GetObjectItem(parsed_json, "token");
            value = cJSON_GetObjectItem(parsed_json, "value");

            // token n'existe pas
            if (token == NULL)
            {
                printf("\nToken does not exist\n");
                printf("[-]Client disconnected.\n\n");
            }

            else
            {

                // differents tokens possibles
                switch (token->child->valueint)
                {
                case 1:
                    direction(value);
                    printf("[+]Client disconnected.\n\n");
                    break;
                case 2:
                    accroche(value);
                    printf("[+]Client disconnected.\n\n");
                    break;
                case 3:
                    mine(value);
                    printf("[+]Client disconnected.\n\n");
                    break;
                case 4:
                    askNbMine(value);
                    printf("[+]Client disconnected.\n\n");
                    break;
                case 11:
                    arm(value);
                    printf("Invalid Token\n[-]Client disconnected.\n\n");
                    break;
                default:
                    break;
                }
            }
        }
    }
    // déconnexion du client
    close(client_sock);

    return 0;
}
