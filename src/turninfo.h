#ifndef TURNINFO_H
#define TURNINFO_H

#include <sys/socket.h>
#include <turnclient.h>

enum turn_ip_type{
    turn_44 = 1,
    turn_46 = 2,
    turn_64 = 4,
    turn_66 = 8,
};

#define FQDN_MAX_LEN 1024


struct turn_allocation_result{
    int sockfd;
    struct sockaddr_storage activeTurnServerAddr;
    struct sockaddr_storage hostAddr;
    struct sockaddr_storage rflxAddr;
    struct sockaddr_storage relAddr;
    
    void (*update_turninfo)(void);

};

struct turn_info{
    int numPending;


    //Fully Qualified Domain Name
    char fqdn[FQDN_MAX_LEN];

    char user[STUN_MSG_MAX_USERNAME_LENGTH];
    char pass[STUN_MSG_MAX_PASSWORD_LENGTH];

    //TURN server IP adresses (As resolved by the FQDN)
    struct sockaddr_storage remoteIp4;
    struct sockaddr_storage remoteIp6;


    //Local IP adresses
    struct sockaddr_storage localIp4;
    struct sockaddr_storage localIp6;

    
    struct turn_allocation_result turnAlloc_44;
    struct turn_allocation_result turnAlloc_46;
    struct turn_allocation_result turnAlloc_64;
    struct turn_allocation_result turnAlloc_66;


};


void printAllocationResult(struct turn_allocation_result *result);
void printTurnInfo( struct turn_info *turnInfo );



#endif
