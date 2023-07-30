/**
 *\file token.cpp
 *\brief  Liste des fonctions token
 *\author Quentin BLECHET, Bixente BURUCOA, Sid Ali ZITOUNI TERKI
 *\version V1
 *\date 5 juin 2023
 *
 * Fonctions exécutés selon les informations transmises au serveur.
 */

#include "Header.h"
/**
 *\fn void direction(cJSON *parsed_json)
 *\brief Fonction qui envoie des informations de directions à l'Arduino
 *
 *\param[in] cJSON *parsed_json Pointeur de type  cJSON
 *\return Aucun
 */
void direction(cJSON *parsed_json)
{
    int s;
    struct sockaddr_can addr;
    struct ifreq ifr;
    struct can_frame frame;

    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
    {
        perror("Socket");
    }

    strcpy(ifr.ifr_name, "can0");
    ioctl(s, SIOCGIFINDEX, &ifr);

    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("Bind");
    }

    frame.can_id = 0x01;
    frame.can_dlc = 2;
    frame.data[0] = 0;
    frame.data[1] = parsed_json->valueint;

    if (write(s, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame))
    {
        perror("Write");
    }

    if (close(s) < 0)
    {
        perror("Close");
    }

    std::cout << parsed_json->valueint << std::endl;
}

// Version ameliorée
/**
 *\fn void accroche(cJSON *parsed_json)
 *\brief Fonction pour passer le rover en mode accroche (Version Future).
 *
 *\param[in] cJSON *parsed_json Pointeur de type  cJSON
 *\return Aucun
 */
void accroche(cJSON *parsed_json)
{
    std::cout << parsed_json->valueint << std::endl;
}

// Version ameliorée
void mine(cJSON *parsed_json)
{
    std::cout << parsed_json->valueint << std::endl;
}

// Version ameliorée
/**
 *\fn void askNbMine(cJSON *parsed_json)
 *\brief Fonction qui envoie une demande d'information sur le nombres de mines restantes
 *
 *\param[in] cJSON *parsed_json Pointeur de type  cJSON
 *\return Aucun
 */
void askNbMine(cJSON *parsed_json)
{
    std::cout << parsed_json->valueint << std::endl;
}

/**
 *\fn void arm(cJSON *parsed_json)
 *\brief Fonction qui envoie des informations de mise en mouvement du bras à l'Arduino
 *
 *\param[in] cJSON *parsed_json Pointeur de type  cJSON
 *\return Aucun
 */
void arm(cJSON *parsed_json)
{
    int s;
    struct sockaddr_can addr;
    struct ifreq ifr;
    struct can_frame frame;

    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0)
    {
        perror("Socket");
    }

    strcpy(ifr.ifr_name, "can0");
    ioctl(s, SIOCGIFINDEX, &ifr);

    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("Bind");
    }

    frame.can_id = 0x01;
    frame.can_dlc = 2;
    frame.data[0] = 1;
    frame.data[1] = parsed_json->valueint;

    if (write(s, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame))
    {
        perror("Write");
    }

    if (close(s) < 0)
    {
        perror("Close");
    }

}
