/**
 *\file client.c
 *\brief Programme qui regroupe tous les fonctions du client (version Future)
 *\author Quentin BLECHET, Bixente BURUCOA, Sid Ali ZITOUNI TERKI
 *\version Future
 *\date 5 juin 2023
 *
 *\ Programme qui permet d'envoyer des informations à un autre serveur (IHM )
 */

#include "Header.h"

/**
* \fn void sendClient(int id)
* \brief Fonction permettant d'envoyer un json selon son type
*
 * Fonction en cours de développement
* \param[in] id : Type d'information envoyé
* \return Aucun
*/
void sendClient(int id)
{
    char *ip = "51.91.150.164"; // ip ubuntu
    int port = 2202;
    cJSON *json;

    switch (id)
    {
    case 5:
        json = createJsonConfirmAccroche();
        break;

    case 6:
        json = createJsonConfirmMine();
        break;

    case 7:
        json = createJsonPosition(15.5, 12.3);
        break;

    case 8:
        json = createJsonSpeed(25.5);
        break;

    case 9:
        json = createJsonRadar(49.3, 64.0);
        break;

    case 10:
        json = createJsonNbMine(5);
        break;

    default:
        printf("Erreur ID Json Creation");
    }

    sendJson(json, ip, port);
}


/**
* \fn void sendJson(cJSON *json, char *ip, int port)
* \brief Fonction permettant d'envoyer un json par rapport à l' ip et au port définie
*
* Fonction en cours de développement
 
* \param[in] *json : Pointeur de cJson
* \param[in] *ip: Pointeur int qui pointe vers l'adresse ip
* \param[in] port : port de destination
* \return Aucun
*/
void sendJson(cJSON *json, char *ip, int port)
{
    char buffer_json[1024];
    int sock;
    struct sockaddr_in addr;

    // JSON String
    strcpy(buffer_json, cJSON_Print(json));
    

    // Socket creation
    sock = init_sock();

    // Connection to ubuntu
    init_addr(addr, sock, ip, port);

    // Send Json
    send(sock, buffer_json, sizeof(buffer_json), 0);
}


/**
* \fn cJSON *createJsonConfirmAccroche()
* \brief Fonction qui crée le cJson confirmAccroche
*
* Fonction en cours de développement
 *
* \return Aucun
*/
cJSON *createJsonConfirmAccroche()
{
    // JSON
    cJSON *confirmAccroche = cJSON_CreateObject();

    // Password
    cJSON_AddStringToObject(confirmAccroche, "password", password);

    // Token
    cJSON *token = cJSON_CreateObject();
    cJSON_AddNumberToObject(token, "confirmAccroche", 5);
    cJSON_AddItemToObject(confirmAccroche, "token", token);

    // Value
    cJSON_AddNumberToObject(confirmAccroche, "value", 1);

    return confirmAccroche;
}

/**
* \fn cJSON *createJsonConfirmMine()
* \brief Fonction qui crée le cJson confirmMine
*
* Fonction en cours de développement
 *
* \return Aucun
*/
cJSON *createJsonConfirmMine()
{
    // JSON
    cJSON *confirmMine = cJSON_CreateObject();

    // Password
    cJSON_AddStringToObject(confirmMine, "password", password);

    // Token
    cJSON *token = cJSON_CreateObject();
    cJSON_AddNumberToObject(token, "confirmMine", 6);
    cJSON_AddItemToObject(confirmMine, "token", token);

    // Value
    cJSON_AddNumberToObject(confirmMine, "value", 1);

    return confirmMine;
}

/**
* \fn cJSON *createJsonPosition(double x, double y)
* \brief Fonction qui crée le cJson position
*
* Fonction en cours de développement
*
*\param[in] x: coordonnée d'une position
*\param[in] y: coordonnée d'une position
* \return cJson
*/
cJSON *createJsonPosition(double x, double y)
{
    // JSON
    cJSON *position = cJSON_CreateObject();

    // Password
    cJSON_AddStringToObject(position, "password", password);

    // Token
    cJSON *token = cJSON_CreateObject();
    cJSON_AddNumberToObject(token, "position", 7);
    cJSON_AddItemToObject(position, "token", token);

    // Value
    cJSON *value = cJSON_CreateObject();
    cJSON_AddNumberToObject(value, "x", x);
    cJSON_AddNumberToObject(value, "y", y);
    cJSON_AddItemToObject(position, "value", value);

    return position;
}

/**
* \fn cJSON *createJsonSpeed(double speedValue)
* \brief Fonction qui crée le cJson speed
*
* Fonction en cours de développement
*
*\param[in] speedValue: vitesse
* \return cJson
*/
cJSON *createJsonSpeed(double speedValue)
{
    // JSON
    cJSON *speed = cJSON_CreateObject();

    // Password
    cJSON_AddStringToObject(speed, "password", password);

    // Token
    cJSON *token = cJSON_CreateObject();
    cJSON_AddNumberToObject(token, "speed", 8);
    cJSON_AddItemToObject(speed, "token", token);

    // Value
    cJSON_AddNumberToObject(speed, "value", speedValue);

    return speed;
}

/**
* \fn cJSON *createJsonRadar(double x, double y)
* \brief Fonction qui crée le cJson radar
*
* Fonction en cours de développement
*
*\param[in] x: coordonnée d'une position
*\param[in] y: coordonnée d'une position
* \return cJson
*/
cJSON *createJsonRadar(double x, double y)
{
    // JSON
    cJSON *radar = cJSON_CreateObject();

    // Password
    cJSON_AddStringToObject(radar, "password", password);

    // Token
    cJSON *token = cJSON_CreateObject();
    cJSON_AddNumberToObject(token, "radar", 9);
    cJSON_AddItemToObject(radar, "token", token);

    // Value
    cJSON *value = cJSON_CreateObject();
    cJSON_AddNumberToObject(value, "x", x);
    cJSON_AddNumberToObject(value, "y", y);
    cJSON_AddItemToObject(radar, "value", value);

    return radar;
}

/**
* \fn cJSON *createJsonNbMine(int nbMineValue)
* \brief Fonction qui crée le cJson nbMine
*
* Fonction en cours de développement
*\param[in] nbMineValue: nombre de mines
* \return cJSON
*/
cJSON *createJsonNbMine(int nbMineValue)
{
    // JSON
    cJSON *nbMine = cJSON_CreateObject();

    // Password
    cJSON_AddStringToObject(nbMine, "password", password);

    // Token
    cJSON *token = cJSON_CreateObject();
    cJSON_AddNumberToObject(token, "nbMine", 10);
    cJSON_AddItemToObject(nbMine, "token", token);

    // Value
    cJSON_AddNumberToObject(nbMine, "value", nbMineValue);

    return nbMine;
}
