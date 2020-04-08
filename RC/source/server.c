#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sqlite3.h>

#define NRM_SIZE 32
#define MAX_SIZE 65536

extern int errno;

int port = 2405;
int sd;
sqlite3* db;
sqlite3_stmt* stmt;

void hndl_child()
{
	while(waitpid(-1,NULL,WNOHANG) > 0);
}

void hndl_terminate()
{
    printf("\n"); fflush(stdout);
    close(sd);
    exit(0);
}

void init_db()
{
    sqlite3_open("main.db",&db);

    char *content = "CREATE TABLE Accounts(" \
                    "User TEXT NOT NULL," \
                    "Pass TEXT NOT NULL);" \

                    "CREATE TABLE Passwords(" \
                    "User TEXT NOT NULL," \
                    "Username TEXT NOT NULL," \
                    "Password TEXT NOT NULL," \
                    "Title TEXT NOT NULL," \
                    "Category TEXT NOT NULL," \
                    "Url TEXT NOT NULL," \
                    "Notes TEXT NOT NULL);";

    sqlite3_exec(db,content,0,0,0);
}

int main()
{
    init_db();

    struct sockaddr_in server;
    struct sockaddr_in from;
    char msg[MAX_SIZE];

    if((sd = socket(AF_INET,SOCK_STREAM,0)) == -1)
    {
        perror("socket()");
        return errno;
    }

    bzero(&server,sizeof(server));
    bzero(&from,sizeof(from));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(port);

    if(bind(sd,(struct sockaddr*) &server, sizeof(struct sockaddr)) == -1)
    {
        perror("bind()");
        return errno;
    }

    if(listen(sd,5) == -1)
    {
        perror("listen()");
        return errno;
    }

    signal(SIGINT,hndl_terminate);
    signal(SIGQUIT,hndl_terminate);
    signal(SIGTSTP,hndl_terminate);

    printf("server is running\n"); fflush(stdout);

    while (1)
    {
        int client;
        int length = sizeof(from);

        client = accept(sd,(struct sockaddr*) &from,&length);

        if(client < 0)
        {
            perror("accept()");
            continue;
        }

        int pid = fork();

        if(pid < 0)
        {
            perror("fork()");
            continue;
        }

        if(pid == 0)
        {
            close(sd);

            signal(SIGINT,hndl_terminate);
            signal(SIGQUIT,hndl_terminate);
            signal(SIGTSTP,hndl_terminate);

            printf("new client\n"); fflush(stdout);

            char my_user[NRM_SIZE];

            while(1)
            {
                bzero(msg, NRM_SIZE);

                if(read(client,msg,MAX_SIZE) <= 0)
                {
                    perror("read()");
                    continue;
                }

                printf("<%s>: ",msg);fflush(stdout);

                if(strcmp(msg,"exit") == 0)
                {
                    printf("client disconnected\n"); fflush(stdout);
                    close(client);
                    exit(0);
                }
                else if(strstr(msg,"login!"))
                {
                    char user[NRM_SIZE] = {0}, pass[NRM_SIZE] = {0};
                    char *t;
                    t = strtok(msg,"!");
                    t = strtok(NULL,"_"); strcpy(user,t);
                    t = strtok(NULL,"_"); strcpy(pass,t);

                    int ok = 0;
                    char *content = "SELECT User,Pass FROM Accounts;";
                    int ret = sqlite3_prepare_v2(db,content,-1,&stmt,0);
                    do
                    {
                        ret = sqlite3_step(stmt);
                        if(ret == SQLITE_ROW && strcmp(user,sqlite3_column_text(stmt,0)) == 0 && strcmp(pass,sqlite3_column_text(stmt,1)) == 0) ok = 1;
                    } while(ret == SQLITE_ROW);

                    bzero(msg,MAX_SIZE);
                    if(!ok)
                    {
                        printf("login attempt failed by user %s\n",user); fflush(stdout);
                        strcpy(msg,"LOG_NOK");
                    }
                    else
                    {
                        printf("%s logged in\n",user); fflush(stdout);
                        strcpy(msg,"LOG_OK");
                        strcpy(my_user,user);
                    }
                }
                else if(strstr(msg,"register!"))
                {
                    char user[NRM_SIZE] = {0}, pass[NRM_SIZE] = {0};
                    char *t;
                    t = strtok(msg,"!");
                    t = strtok(NULL,"_"); strcpy(user,t);
                    t = strtok(NULL,"_"); strcpy(pass,t);

                    int ok = 1;
                    char *content = "SELECT User FROM Accounts;";
                    int ret = sqlite3_prepare_v2(db,content,-1,&stmt,0);
                    do
                    {
                        ret = sqlite3_step(stmt);
                        if(ret == SQLITE_ROW && strcmp(user,sqlite3_column_text(stmt,0)) == 0) ok = 0;
                    } while(ret == SQLITE_ROW);

                    bzero(msg,MAX_SIZE);
                    if(!ok)
                    {
                        printf("registration attempt failed by user %s\n",user); fflush(stdout);
                        strcpy(msg,"REG_NOK");
                    }
                    else
                    {
                        content = "INSERT INTO Accounts (User,Pass) VALUES (?,?);";
                        sqlite3_prepare_v2(db,content,-1,&stmt,0);
                        sqlite3_bind_text(stmt,1,user,-1,SQLITE_TRANSIENT);
                        sqlite3_bind_text(stmt,2,pass,-1,SQLITE_TRANSIENT);
                        sqlite3_step(stmt);
                        sqlite3_finalize(stmt);

                        printf("new account registered with username %s\n",user); fflush(stdout);
                        strcpy(msg,"REG_OK");
                    }
                }
                else if(strstr(msg,"add!"))
                {
                    char user[NRM_SIZE]={0}, username[NRM_SIZE]={0}, password[NRM_SIZE]={0}, title[NRM_SIZE]={0}, category[NRM_SIZE]={0}, url[NRM_SIZE]={0}, notes[NRM_SIZE]={0};
                    char *t;
                    t = strtok(msg,"!");
                    t = strtok(NULL,"_"); strcpy(user,t);
                    t = strtok(NULL,"_"); strcpy(username,t);
                    t = strtok(NULL,"_"); strcpy(password,t);
                    t = strtok(NULL,"_"); strcpy(title,t);
                    t = strtok(NULL,"_"); strcpy(category,t);
                    t = strtok(NULL,"_"); strcpy(url,t);
                    t = strtok(NULL,"_"); strcpy(notes,t);

                    int ok = 1;
                    char *content = "SELECT Title FROM Passwords;";
                    int ret = sqlite3_prepare_v2(db,content,-1,&stmt,0);
                    do
                    {
                        ret = sqlite3_step(stmt);
                        if(ret == SQLITE_ROW && strcmp(title,sqlite3_column_text(stmt,0)) == 0) ok = 0;
                    } while(ret == SQLITE_ROW && ok);

                    bzero(msg,MAX_SIZE);
                    if(!ok)
                    {
                        printf("addition attempt failed by user %s\n",my_user); fflush(stdout);
                        strcpy(msg,"ADD_NOK");
                    }
                    else
                    {
                        content = "INSERT INTO Passwords (User,Username,Password,Title,Category,Url,Notes) VALUES (?,?,?,?,?,?,?);";
                        ret = sqlite3_prepare_v2(db,content,-1,&stmt,0);
                        sqlite3_bind_text(stmt,1,user,-1,SQLITE_TRANSIENT);
                        sqlite3_bind_text(stmt,2,username,-1,SQLITE_TRANSIENT);
                        sqlite3_bind_text(stmt,3,password,-1,SQLITE_TRANSIENT);
                        sqlite3_bind_text(stmt,4,title,-1,SQLITE_TRANSIENT);
                        sqlite3_bind_text(stmt,5,category,-1,SQLITE_TRANSIENT);
                        sqlite3_bind_text(stmt,6,url,-1,SQLITE_TRANSIENT);
                        sqlite3_bind_text(stmt,7,notes,-1,SQLITE_TRANSIENT);
                        ret = sqlite3_step(stmt);
                        sqlite3_finalize(stmt);

                        printf("new addition by account with username %s\n",my_user); fflush(stdout);
                        strcpy(msg,"ADD_OK");
                    }
                }
                else if(strstr(msg,"view!"))
                {
                    char category[NRM_SIZE] = {0};
                    char *t;
                    t = strtok(msg,"!");
                    t = strtok(NULL,"_"); strcpy(category,t);

                    char content[128] = {0};

                    if(strcmp(category,"all") == 0) strcpy(content,"SELECT Username,Password,Title,Category,Url,Notes FROM Passwords WHERE (User=?) ORDER BY Title ASC;");
                    else strcpy(content,"SELECT Username,Password,Title,Category,Url,Notes FROM Passwords WHERE (User=? AND Category=?) ORDER BY Title ASC;");

                    int ret = sqlite3_prepare_v2(db,content,-1,&stmt,0);
                    sqlite3_bind_text(stmt,1,my_user,-1,SQLITE_TRANSIENT);
                    if(strcmp(category,"all") != 0) sqlite3_bind_text(stmt,2,category,-1,SQLITE_TRANSIENT);

                    int ok = 0;
                    bzero(msg,MAX_SIZE);
                    do
                    {
                        ret = sqlite3_step(stmt);
                        if(ret == SQLITE_ROW)
                        {
                            ok = 1;
                            char username[NRM_SIZE] = {0}; strcpy(username,sqlite3_column_text(stmt,0));
                            char password[NRM_SIZE] = {0}; strcpy(password,sqlite3_column_text(stmt,1));
                            char title[NRM_SIZE] = {0}; strcpy(title,sqlite3_column_text(stmt,2));
                            char category[NRM_SIZE] = {0}; strcpy(category,sqlite3_column_text(stmt,3));
                            char url[NRM_SIZE] = {0}; strcpy(url,sqlite3_column_text(stmt,4));
                            char notes[NRM_SIZE] = {0}; strcpy(notes,sqlite3_column_text(stmt,5));

                            strcat(msg,"\n--------------------------\nTitle: ");
                            strcat(msg,title);
                            strcat(msg,"\nUsername: ");
                            strcat(msg,username);
                            strcat(msg,"\nPassword: ");
                            strcat(msg,password);
                            strcat(msg,"\nCategory: ");
                            strcat(msg,category);
                            strcat(msg,"\nUrl: ");
                            strcat(msg,url);
                            strcat(msg,"\nNotes: ");
                            strcat(msg,notes);
                        }
                    } while(ret == SQLITE_ROW);

                    sqlite3_finalize(stmt);

                    if(!ok)
                    {
                        bzero(msg,MAX_SIZE);
                        strcpy(msg,"VIEW_NOK");
                    }
                    printf("visualisation performed by user %s\n",my_user); fflush(stdout);
                }

                if(write(client,msg,MAX_SIZE) <= 0)
                {
                    perror("write()");
                    continue;
                }
            }

            close(client);
            exit(0);
        }
        else
        {
            signal(SIGCHLD,hndl_child);
        }
    }

    return 0;
}
