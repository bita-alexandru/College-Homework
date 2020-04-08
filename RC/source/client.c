#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <signal.h>

#define NRM_SIZE 32
#define MAX_SIZE 65536

extern int errno;

int port;
int sd;

void hndl_terminate()
{
    printf("\n"); fflush(stdout);

    if(write(sd,"exit",NRM_SIZE) <= 0)
    {
        perror("write()");
        exit(-1);
    }
    close(sd);
    exit(0);
}

int main(int argc,char *argv[])
{
    struct sockaddr_in server;
    char msg[MAX_SIZE];

    if(argc != 3)
    {
        printf("Syntax: %s <server_address> <port>\n",argv[0]); fflush(stdout);
        return -1;
    }

    port = atoi(argv[2]);

    if((sd = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        perror("socket()");
        return errno;
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_port = htons(port);

    if(connect(sd,(struct sockaddr*) &server, sizeof(struct sockaddr)) == -1)
    {
        perror("connect()");
        return errno;
    }

    signal(SIGINT,hndl_terminate);
    signal(SIGQUIT,hndl_terminate);
    signal(SIGTSTP,hndl_terminate);

    printf("Welcome! Type 'help' to see a list of the available commands.\n"); fflush(stdout);

    int status = 1;
    int connected = 0;
    char user[NRM_SIZE] = {0};

    while(status == 1)
    {
        bzero(msg,MAX_SIZE);

        printf("> "); fflush(stdout);
        read(0,msg,NRM_SIZE); msg[strlen(msg)-1] = '\0'; fflush(stdin);

        if(connected == 0)
        {
            if(strcmp(msg,"help") == 0)
            {
                printf("Here are the commands you can use:\n'login' - to log into your account\n'register' - to register a new account\n'exit' - to close the program\n");
                continue;
            }
            else if(strcmp(msg,"login") == 0)
            {
                int ok_user = 1;
                char username[NRM_SIZE] = {0};
                printf("username: "); fflush(stdout);
                read(0,username,NRM_SIZE); username[strlen(username)-1] = '\0'; fflush(stdin);

                if(strlen(username) < 3 || strlen(username) > 15) ok_user = 0;

                for(int i = 0; i < strlen(username) && ok_user; i++)
                    if(!((username[i] >= '0' && username[i] <= '9') || (username[i] >= 'A' && username[i] <= 'Z') || (username[i] >= 'a' && username[i] <= 'z'))) ok_user = 0;

                int ok_pass = 1;
                char password[NRM_SIZE] = {0};
                printf("password: "); fflush(stdout);
                read(0,password,NRM_SIZE); password[strlen(password)-1] = '\0'; fflush(stdin);

                if(strlen(password) < 3 || strlen(password) > 15) ok_pass = 0;

                for(int i = 0; i < strlen(password) && ok_pass; i++)
                    if(!((password[i] >= '0' && password[i] <= '9') || (password[i] >= 'A' && password[i] <= 'Z') || (password[i] >= 'a' && password[i] <= 'z'))) ok_pass = 0;


                if(!ok_user || !ok_pass)
                {
                    if(!ok_user && !ok_pass)
                    {
                        printf("The username and password are not valid! Try again.\n");
                        fflush(stdout);
                    }
                    else if(!ok_user)
                    {
                        printf("The username is not valid! Try again.\n");
                        fflush(stdout);
                    }
                    else if(!ok_pass)
                    {
                        printf("The password is not valid! Try again.\n");
                        fflush(stdout);
                    }

                    continue;
                }
                else
                {
                    strcpy(msg,"login!");
                    strcat(msg,username);
                    strcat(msg,"_");
                    strcat(msg,password);

                    bzero(user,NRM_SIZE);
                    strcpy(user,username);
                }
            }
            else if(strcmp(msg,"register") == 0)
            {
                printf("Only numbers and english alphabet letters are allowed! (3-15 characters)\n");

                int ok_user = 1;
                char username[NRM_SIZE] = {0};
                printf("username: "); fflush(stdout);
                read(0,username,NRM_SIZE); username[strlen(username)-1] = '\0'; fflush(stdin);

                if(strlen(username) < 3 || strlen(username) > 15) ok_user = 0;

                for(int i = 0; i < strlen(username) && ok_user; i++)
                    if(!((username[i] >= '0' && username[i] <= '9') || (username[i] >= 'A' && username[i] <= 'Z') || (username[i] >= 'a' && username[i] <= 'z'))) ok_user = 0;

                int ok_pass = 1;
                char password[NRM_SIZE] = {0};
                printf("password: "); fflush(stdout);
                read(0,password,NRM_SIZE); password[strlen(password)-1] = '\0'; fflush(stdin);

                if(strlen(password) < 3 || strlen(password) > 15) ok_pass = 0;

                for(int i = 0; i < strlen(password) && ok_pass; i++)
                    if(!((password[i] >= '0' && password[i] <= '9') || (password[i] >= 'A' && password[i] <= 'Z') || (password[i] >= 'a' && password[i] <= 'z'))) ok_pass = 0;


                if(!ok_user || !ok_pass)
                {
                    if(!ok_user && !ok_pass)
                    {
                        printf("The username and password are not valid! Try again.\n");
                        fflush(stdout);
                    }
                    else if(!ok_user)
                    {
                        printf("The username is not valid! Try again.\n");
                        fflush(stdout);
                    }
                    else if(!ok_pass)
                    {
                        printf("The password is not valid! Try again.\n");
                        fflush(stdout);
                    }

                    continue;
                }
                else
                {
                    strcpy(msg,"register!");
                    strcat(msg,username);
                    strcat(msg,"_");
                    strcat(msg,password);
                }
            }
            else if(strcmp(msg,"exit") == 0) status = 0;
            else
            {
                printf("Invalid command.\n");
                fflush(stdout);
                continue;
            }
        }
        else
        {
            if(strcmp(msg,"help") == 0)
            {
                printf("Here are the commands you can use:\n'add' - to save a new password\n'view' - to view your saved passwords\n'exit' - to close the program\n");
                continue;
            }
            else if(strcmp(msg,"exit") == 0) status = 0;
            else if(strcmp(msg,"add") == 0)
            {
                printf("Use at most 32 characters for each field and don't leave any fields empty!\n"); fflush(stdout);
                char username[NRM_SIZE] = {0};
                printf("username: "); fflush(stdout);
                read(0,username,NRM_SIZE); username[strlen(username)-1] = '\0'; fflush(stdin);

                char password[NRM_SIZE] = {0};
                printf("password: "); fflush(stdout);
                read(0,password,NRM_SIZE); password[strlen(password)-1] = '\0'; fflush(stdin);

                char title[NRM_SIZE] = {0};
                printf("title: "); fflush(stdout);
                read(0,title,NRM_SIZE); title[strlen(title)-1] = '\0'; fflush(stdin);

                char category[NRM_SIZE] = {0};
                printf("category: "); fflush(stdout);
                read(0,category,NRM_SIZE); category[strlen(category)-1] = '\0'; fflush(stdin);

                char url[NRM_SIZE] = {0};
                printf("url: "); fflush(stdout);
                read(0,url,NRM_SIZE); url[strlen(url)-1] = '\0'; fflush(stdin);

                char notes[NRM_SIZE] = {0};
                printf("notes: "); fflush(stdout);
                read(0,notes,NRM_SIZE); notes[strlen(notes)-1] = '\0'; fflush(stdin);

                if(strlen(username) < 1 || strlen(password) < 1 || strlen(title) < 1 || strlen(category) < 1 || strlen(url) < 1 || strlen(notes) < 1)
                {
                    printf("No field can be left empty! Try again.\n");
                    fflush(stdout);
                    continue;
                }
                else
                {
                    strcpy(msg,"add!");
                    strcat(msg,user);
                    strcat(msg,"_");
                    strcat(msg,username);
                    strcat(msg,"_");
                    strcat(msg,password);
                    strcat(msg,"_");
                    strcat(msg,title);
                    strcat(msg,"_");
                    strcat(msg,category);
                    strcat(msg,"_");
                    strcat(msg,url);
                    strcat(msg,"_");
                    strcat(msg,notes);
                }
            }
            else if(strcmp(msg,"view") == 0)
            {
                char category[NRM_SIZE] = {0};
                printf("category (or type 'all'): "); fflush(stdout);
                read(0,category,NRM_SIZE); category[strlen(category)-1] = '\0'; fflush(stdin);

                strcpy(msg,"view!");
                strcat(msg,category);
            }
            else
            {
                printf("Invalid command.\n");
                fflush(stdout);
                continue;
            }
        }

        if(write(sd,msg,MAX_SIZE) <= 0)
        {
            perror("write() - server might be down");
            close(sd);
            return errno;
        }

        bzero(msg,MAX_SIZE);

        if(status && read(sd,msg,MAX_SIZE) <= 0)
        {
            perror("read() - server might be down");
            close(sd);
            return errno;
        }

        if(strcmp(msg,"LOG_OK") == 0)
        {
            printf("You've succesfully logged in! Type 'help' for a list of new available commands.\n"); fflush(stdout);
            connected = 1;
        }
        else if(strcmp(msg,"LOG_NOK") == 0)
        {
            printf("The username or the password does not exist in the database! Try again.\n");
            fflush(stdout);
        }
        else if(strcmp(msg,"REG_OK") == 0)
        {
            printf("You've succesfully registered! Type 'login' to log into your account.\n");
            fflush(stdout);
        }
        else if(strcmp(msg,"REG_NOK") == 0)
        {
            printf("The username is already taken! Try again.\n");
            fflush(stdout);
        }
        else if(strcmp(msg,"VIEW_NOK") == 0)
        {
            printf("No passwords to view!\n");
            fflush(stdout);
        }
        else if(strcmp(msg,"ADD_OK") == 0)
        {
            printf("Operation succesfully completed!\n");
            fflush(stdout);
        }
        else if(strcmp(msg,"ADD_NOK") == 0)
        {
            printf("You've already used this title! Try another one.\n");
            fflush(stdout);
        }
        else if(strlen(msg) > 47)
        {
            printf("%s\n",msg);
            fflush(stdout);
        }
    }

    close(sd);
    printf("Have a nice day!\n"); fflush(stdout);

    return 0;
}
