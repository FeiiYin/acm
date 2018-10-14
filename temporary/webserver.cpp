/*
 * @Samaritan_infi
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <time.h>
#include <string.h>
#include <signal.h>

#define HOSTLEN 256
#define BACKLOG 1

int make_server_socket(int portnumber, int backlog = BACKLOG);
int connect_to_server(char *, int);
void read_til_crnl(FILE *);
void process_request(char *, int);
void header (FILE * fp, const char * content_type);
void do_404 (char *item, int fd);
inline bool Is_Dir (char * file_name);
inline bool not_exist (char * file_name);
void do_ls (char * dir, int fd);
char * file_type (char * file_name);
inline bool ends_in_cgi (char * file_name);
void do_exec (char * prog, int fd);
void do_cat (char *file_name, int fd);
void can_not_do (int fd);

int main (int argc, char * argv[]) {
    int socket_number;
    char request[BUFSIZ], buffer[BUFSIZ];
    if (argc == 1) {
        fprintf(stderr, "usage: loss portnum\n");
        exit(EXIT_FAILURE);
    }
    if ((socket_number = make_server_socket(atoi(argv[1]))) == -1) {
        fprintf(stderr, "usage: port occupied\n");
        exit(EXIT_FAILURE);
    }
    /* 避免僵尸进程 */
    signal(SIGCHLD, SIG_IGN);
    while (true) {
        /* accept (服务器端套接字, 保存客户端IP和端口信息, 参数2的占地大小), 返回客户端套接字句柄 */
        sockaddr addr_client;
        socklen_t client_len;
        int fd = accept(socket_number, &addr_client, &client_len);
        /* 使一个标准的文件描述符与I/O流结合 */
        FILE * fpin = fdopen(fd, "r");
        /* 从文件流中获取信息 */
        fgets(request, BUFSIZ, fpin);
        printf("%s", request);
        /* 直接获取整个文件信息 */
        /* int n = read(fd, request, sizeof(request)); */
        read_til_crnl(fpin);
        process_request(request, fd);
        fclose(fpin);
    }
    return 0;
}

int make_server_socket (int portnumber, int backlog) {
    struct sockaddr_in saddr;
    struct hostent * hp;
    char hostname[HOSTLEN];
    int socket_id;
    /*
     * socket (协议族, 协议类型, 协议编号)
     */
    if ((socket_id = socket(PF_INET, SOCK_STREAM, 0)) == -1) { /* get a socket */
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    bzero((void *) &saddr, sizeof (saddr)); /* memset */
    /* 返回本地主机名 */
    gethostname(hostname, HOSTLEN);
    printf("local host name: %s\n", hostname);
    hp = gethostbyname(hostname);
    /* bcopy(void * src, void * dest, int len) */
    bcopy((void *) hp->h_addr, (void *)&saddr.sin_addr, hp->h_length);
    //saddr.sin_addr.s_addr = inet_addr("192.0.0.1");
    /* 将主机字节顺序转换成网络字节顺序，整数存储高位置于低地址处，大端 */
    saddr.sin_port = htons(portnumber);
    saddr.sin_family = AF_INET;
    /* 给未命名套接口进行本地捆绑 */
    if (bind(socket_id, (struct sockaddr *) &saddr, sizeof(saddr)) != 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    /* 监控请求队列 */
    if (listen(socket_id, backlog) != 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
    return socket_id;
}

int connect_to_server (char *host, int portnumber) {
    int                 socket_number;
    struct sockaddr_in  servaddr;
    struct hostent      * hp;
    if ((socket_number = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    bzero(&servaddr, sizeof servaddr);
    if ((hp = gethostbyname(host)) == NULL) {
        perror("host failed");
        exit(EXIT_FAILURE);
    }
    bcopy(hp->h_addr, (struct sockaddr *)&servaddr.sin_addr, hp->h_length);
    servaddr.sin_port = htons(portnumber);
    servaddr.sin_family = AF_INET;
    if (connect(socket_number, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }
    return socket_number;
}

/*
 * skip over all request info until a CRNL is seen
 */
void read_til_crnl (FILE *fp) {
    char buf[BUFSIZ];
    while (fgets(buf, BUFSIZ, fp) != NULL && strcmp(buf, "\r\n") != 0)
        printf("%s", buf);
    puts("");
}

/*
 * handle request in a new process
 * GET / HTTP/1.0
 */
void process_request (char * request, int fd) {
    char cmd[BUFSIZ], arg[BUFSIZ];
    if (fork() != 0) return; /* 父亲返回 */
    strcpy(arg, ".");
    if (sscanf(request, "%s %s", cmd, arg + 1) != 2)
        return;

    if (strcmp(cmd, "GET") != 0)
        can_not_do(fd);
    else if (not_exist(arg))
        do_404(arg, fd);
    else if (Is_Dir(arg))
        do_ls(arg, fd);
    else if (ends_in_cgi(arg))
        do_exec(arg, fd);
    else
        do_cat(arg, fd);
}

void can_not_do (int fd) {
    FILE * fp = fdopen(fd, "w");
    fprintf(fp, "HTTP/1.0 501 Not Implemented\r\n");
    fprintf(fp, "Content-type: text/plain\r\n");
    fprintf(fp, "\r\n");
    fprintf(fp, "That command is not yet implemented\r\n");
    fclose(fp);
}

void header (FILE * fp, const char * content_type) {
    fprintf(fp, "HTTP/1.0 200 OK\r\n");
    if (content_type)
        fprintf(fp, "Content-type: %s\r\n", content_type);
}

inline bool not_exist (char * file_name) {
    struct stat info;
    return (stat(file_name, &info) == -1);
}

void do_404 (char * file_name, int fd) {
    FILE * fp = fdopen(fd, "w");
    fprintf(fp, "HTTP/1.0 404 Not Found\r\n");
    fprintf(fp, "Content-type: text/plain\r\n");
    fprintf(fp, "\r\n");
    fprintf(fp, "The item you requested: %s\r\nis not found\r\n", file_name);
    fclose(fp);
}

inline bool Is_Dir (char * file_name) {
    struct stat info;
    return (stat(file_name, &info) != -1 && S_ISDIR((info.st_mode)));
}

void do_ls (char * dir, int fd) {
    FILE * fp;
    fp = fdopen(fd, "w");
    header(fp, "text/plain");
    fprintf(fp, "\r\n");
    fflush(fp);
    /*  */
    dup2(fd, 1); /* 标准输出 */
    dup2(fd, 2); /* 标准错误输出 */
    close(fd);
    execlp("ls", "ls", "-l", dir, NULL);
    perror(dir);
    return;
}

char * file_type (char * f) {
    char * cp;
    if ((cp = strrchr(f, '.')) != NULL)
        return cp + 1;
    return cp;
}

inline bool ends_in_cgi (char * file_name) {
    return (strcmp(file_type(file_name), "cgi") == 0);
}

void do_exec (char * prog, int fd) { /// 浏览器输出不出来
    printf("sdhfasldf\n");

    FILE * fp;
    fp = fdopen(fd, "w");
    header(fp, NULL);
    fflush(fp);
    dup2(fd, 1);
    dup2(fd, 2);
    close(fd);
    execl(prog, prog, NULL);
    perror(prog);
    return;
}

void do_cat (char *file_name, int fd) {
    char * extension = file_type(file_name);
    const char * content_type = "text/plain";
    int c;
    if (strcmp(extension, "html") == 0)
        content_type = "text/html";
    else if (strcmp(extension, "gif") == 0)
        content_type = "image/gif";
    else if (strcmp(extension, "jpg") == 0)
        content_type = "image/jpg";
    else if (strcmp(extension, "jpeg") == 0)
        content_type = "image/jpeg";

    FILE * fpsend = fdopen(fd, "w");
    FILE * fpfile = fopen(file_name, "r");
    if (fpsend != NULL && fpfile != NULL) {
        header(fpsend, content_type);
        fprintf(fpsend, "\r\n");
        while ((c = getc(fpfile)) != EOF)
            putc(c, fpsend);
        fclose(fpfile);
        fclose(fpsend);
    }
    return;
}
