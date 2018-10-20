/*
 * @Samaritan_infi
 */
#include <bits/stdc++.h>
#include <curses.h>
#include <sys/time.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

using namespace std;
/* I/O */
int connect_to_server (char *host, int portnumber = 8080);
int init_input_output (int server_fd);
void * handle_input(void * p_server);
void * handle_output(void * p_server);
void init_curse ();
void lose();
void debug (string arr = "debug test", int x = 5, int y = 70);
/* GAME */
bool game_start, game_over;
class Player;
class Bubble;
static void show_change (int x, int y, char m);
void game_init ();
/* CMD */
void CMD_handle_signal (char *);
void CMD_handle_change (char *);
void CMD_handle_bubble (char *);
/* GENERAL */
vector <char *> split (char * arr, const char* token = " ");

int main () {
    char host[] = "127.0.0.1";
    int server_fd = connect_to_server(host);
    init_curse (); /* without this getch will return -1 */
    /* allocate a pthread must not exchange with last line */
    game_init();
    init_input_output(server_fd);
    while (true) {

    }
    endwin();
    return 0;
}


#define ITEM_FRAGILE    '&'
#define BUBBLE          '@'
#define EMPTY           ' '
#define WALL_TRAVERSE   '-'
#define WALL_ERECT      '|'
#define PLAYER          'P'
#define msleep(x)       usleep((x)*100000)  // ms

const char Bubble_change[] = {"QOQO@ "};
char Bubble_picture[2][2][2] = {{'.','|','|','.'},{'-','.','.','-'}};
int dx[] = {-1, 0, 1,  0};
int dy[] = { 0, 1, 0, -1};

struct message_package {
    vector<int> pos;
    char mark;
    char buffer[1024];
    int fd;
};

class Bubble {
public:
    /* QOQOQ@ */
    /* -- -. -- */
    int pos_x, pos_y;
    bool already;
    pthread_t threadID = 0;
	pthread_attr_t attr;
    Bubble (int x, int y) : pos_x(x), pos_y(y), already(false) {
    }
    static void * show_bomb (void * cursor) {
        /* memory cannot allocate in pthread using vector
        vector <pair<pair<int, int>, char>> *pp = (vector <pair<pair<int, int>, char>> *)cursor;
        vector <pair<pair<int, int>, char>> arr = *pp; */
        char *buffer = (char *)cursor;
        //cout << "buffer : "<<buffer << endl; fflush(stdout);
        vector <char *> buf = split(buffer);
//        for (int i = 0; i < buf.size(); i ++)
//            cout << buf[i] << endl;
//        cout << buf.size() <<">>> "<< endl;
        pair<pair<int, int>, char> arr[5];

        for (int i = 0; i < 5; ++i) {
            arr[i] = (make_pair(make_pair(atoi(buf[i * 3]), atoi(buf[i * 3 + 1])), buf[i * 3 + 2][0]));
        }
//for (int i = 0; i < 5; ++i) {
//    printf("!! %d %d %c\n", arr[i].first.first, arr[i].first.second, arr[i].second);
//}
//fflush(stdout);
        pair<int, int> pos[5];
        for (int i = 0; i < 5; ++i) {
            pos[i] = arr[i].first;
        }
        /* pos[0] center */
        int x = pos[0].first, y = pos[0].second;
        for (int i = 0; i < 5; ++i) {
            mvaddch(x, y, Bubble_change[i]);
            msleep(5);
            refresh();
        }
        for (int time = 0; time < 12; time++) {
            for (int id = 1; id <= 4; id++) {
                int dx = pos[id].first - x, dy = pos[id].second - y;
                if (dx) dx = dx / abs(dx);
                if (dy) dy = dy / abs(dy);
                int ex = pos[id].first, ey = pos[id].second;
                int sx = x, sy = y;
                while (sx + dx != ex || sy + dy != ey) {
                        sx += dx;
                        sy += dy;
                        mvaddch(sx, sy, Bubble_picture[(id+1) & 1][time & 1][(sx+sy) & 1]);
                }
            }
            refresh();
            msleep(1);
        }

        mvaddch(x, y, EMPTY);

        for (int id = 1; id <= 4; id++) {
            int dx = pos[id].first - x, dy = pos[id].second - y;
            if (dx) dx = dx / abs(dx);
            if (dy) dy = dy / abs(dy);
            int ex = pos[id].first, ey = pos[id].second;
            int sx = x, sy = y;
            while (sx + dx != ex || sy + dy != ey) {
                    sx += dx;
                    sy += dy;
                    mvaddch(sx, sy, EMPTY);
            }
        }
        for (int i = 0; i < 5; ++i) {
            if (arr[i].second == 'E')
                arr[i].second = EMPTY;
            mvaddch(pos[i].first, pos[i].second, arr[i].second);
        }
        refresh();
    }
};


class Player {
public:
    int pos_x, pos_y;
    char mark;
    bool live;
    Bubble * bubble;
    Player () {
        /* random check possible */
    }

    void make_bubble () {
        if (bubble == NULL || bubble->already == true) {
            bubble = new Bubble(pos_x, pos_y);
        }
    }

    void show_move (int x, int y) {
        mvaddch(x, y, mark);
        refresh();
    }

    static char mark_buffer[];
private:
};
char Player::mark_buffer[] = "PMD";

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

int init_input_output (int server_fd) {
    pthread_t thread_in = 0, thread_out = 1;
	pthread_attr_t attr_in, attr_out;
	pthread_attr_init(& attr_in);
    pthread_attr_setdetachstate(& attr_in, PTHREAD_CREATE_DETACHED);
    pthread_attr_init(& attr_out);
    pthread_attr_setdetachstate(& attr_out, PTHREAD_CREATE_DETACHED);
    pthread_create(&thread_in, &attr_in, handle_input, (void *) &server_fd);
    pthread_create(&thread_out, &attr_out, handle_output, (void *) &server_fd);
}

void * handle_input(void * p_server) {
    int * temp_p = (int *) p_server;
    int server_fd = *temp_p;
    char buffer[64];
    while (true) {
        memset(buffer, 0, sizeof buffer);
        int ret = read(server_fd, buffer, 64);
        /*
         * bubble (pair<int, int> char) * 5
         * change n (pair<int, int> char)
         * signal win/ die int fd /kill int fd/ show char*
         */
        if (ret > 0) {
            //printf("%.*s\n", ret, buffer);
            fflush(stdout);
            if (ret < 6) continue;
            char operation[10];
            sscanf(buffer, "%6s", operation);
            message_package pack;
            if (! strcmp(operation, "bubble")) {
                CMD_handle_bubble(buffer + 7);
            }
            else if (! strcmp(operation, "change")) {
                CMD_handle_change(buffer + 7);
            }
            else if (! strcmp(operation, "signal")) {
                CMD_handle_signal(buffer + 7);
            }
            else {

            }
        }
    }
}

void * handle_output(void * p_server) {
    int * temp_p = (int *) p_server;
    int server_fd = *temp_p;
    char buffer[64];
    int ch;
    while (true) {
        ch = getch();
        if (game_over) {
            if (ch == 'Q') {
                endwin();
                write(server_fd, buffer, 0);
                close(server_fd);
                exit(0);
            }
            continue;
        }
        if (! game_start) {
            snprintf(buffer, 6, "%s", "start");
            write(server_fd, buffer, 5);
            continue;
        }
        /* on linux 10 == enter */
        if (ch == 'w' || ch == 'a' || ch == 's' || ch == 'd' || ch == 'j') {
            buffer[0] = ch;
            buffer[1] = '\0';
            //printf("input : %d %c\n", ch, ch);
            write(server_fd, buffer, 1);
        //send(server_fd, buffer, 1, MSG_NOSIGNAL);
        }
    }
}

static void show_change (int x, int y, char m) {
    mvaddch(x, y, m);
    refresh();
}

void init_curse () {
	initscr();
	crmode();
	noecho();
	clear();
	curs_set(0);
}

void lose () {
    flash();
    msleep(800);
    flash();
    msleep(800);
    flash();
    sleep(1);
    flash();
}

void debug (string arr, int x, int y) {
    move(x, y);
    const char * a = arr.data();
	addstr(a);
	refresh();
}

vector <char *> split (char * arr, const char* token) {
    char * tokenPtr = strtok(arr, token);
    vector <char *> res;
    while (tokenPtr != NULL) {
        res.push_back(tokenPtr);
        tokenPtr = strtok(NULL, " ");
    }
    return res;
}

/* signal win/ die int fd / show char*(kill / junior) */
void CMD_handle_signal(char * buffer) {
    vector <char *> buf = split(buffer);
    if (! strcmp(buf[0], "start")) {
        int num_player = atoi(buf[1]);
        for (int i = 0; i < num_player; ++i) {
            int x = atoi(buf[2 + i * 3]), y = atoi(buf[3 + i * 3]);
            char mark = buf[4 + i * 3][0];
            show_change(x, y, mark);
        }
        game_start = true;
        for (int curx = 11; curx <= 15; curx += 2) {
            mvaddstr(curx, 53, "                           ");
        }
        mvaddstr(11, 53, "Attention!!!");
        mvaddstr(14, 53, "Game start!!!");

    } else if (!strcmp(buf[0], "win")) {
        for (int curx = 11; curx <= 15; curx += 2) {
            mvaddstr(curx, 53, "                           ");
        }
        game_over = true;
        mvaddstr(11, 53, "Congratulations!!!");
        mvaddstr(14, 53, "You win!!!");
        mvaddstr(17, 53, "Q to quit");
    } else if (!strcmp(buf[0], "die")) {
        for (int curx = 11; curx <= 15; curx += 2) {
            mvaddstr(curx, 53, "                           ");
        }
        game_over = true;
        mvaddstr(11, 53, "Sorry...");
        mvaddstr(14, 53, "You lose!!!");
        mvaddstr(17, 53, "Q to quit");
        lose();
    } else if (!strcmp(buf[0], "show")) {
        for (int curx = 11; curx <= 15; curx += 2) {
            mvaddstr(curx, 53, "                           ");
        }
        int curx = 11, cury = 0;
        for (int i = 1; i < buf.size(); ++i) {
            mvaddstr(curx, 53 + cury, buf[i]);
            cury += strlen(buf[i]) + 1;
            if (cury >= 21) {
                cury = 0;
                curx += 2;
            }
        }

    }
    refresh();
}

void CMD_handle_change (char * buffer) {
    vector <char *> buf = split(buffer);
    int num_change = atoi(buf[0]);
    for (int i = 0; i < num_change; ++i) {
        int x = atoi(buf[1 + i * 3]), y = atoi(buf[2 + i * 3]);
        char c = buf[3 + i * 3][0];
        if (c == 'E')
            c = EMPTY;
        if (c == 'P' || c == 'M' || c == 'D') {
            attron(A_BOLD);
            attron(A_UNDERLINE);
            mvaddch(x, y, c);
            attroff(A_BOLD);
            attroff(A_UNDERLINE);
        } else {
            mvaddch(x, y, c);
        }
    }
    refresh();
}

void CMD_handle_bubble (char * buffer) {
    pthread_t threadID;
    char temp_buffer[256];
    strcpy(temp_buffer, buffer);
    //problem
//    vector <char *> buf = split(buffer);
//    vector <pair<pair<int, int>, char>> input;
//    for (int i = 0; i < 5; ++i) {
//        input.push_back(make_pair(make_pair(atoi(buf[i * 3]), atoi(buf[i * 3 + 1])), buf[i * 3 + 2][0]));
//    }
    /* create (pointer to thread, set attribute, function, input into the function) */
    pthread_create(&threadID, NULL, Bubble::show_bomb, (void *) temp_buffer);
}

char GAME_MAP[24][60] = {};
void game_init () {
    game_start = false;
    game_over = false;
    init_pair(1, COLOR_BLUE, COLOR_WHITE);
    //memset(GAME_MAP, 0, sizeof GAME_MAP);
    char TEMP_MAP[24][48] ={{'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'},
                            {'|','&',' ',' ','&',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ','&',' ',' ','&','|'},
                            {'|',' ',' ','&',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ','&',' ',' ','|'},
                            {'|',' ','&',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ',' ',' ',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ','&',' ','|'},
                            {'|','&',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ',' ',' ',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ','&','|'},
                            {'|',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','&','&','-','-','-','-','-','-','-','-','-','-','-','&','&','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ','|'},
                            {'|',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ','&','&',' ',' ',' ',' ',' ',' ',' ','&','&',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ','|'},
                            {'|','&',' ',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','&','&',' ',' ',' ',' ',' ',' ',' ',' ',' ','&','&',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ',' ','&','|'},
                            {'|',' ',' ',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ',' ',' ','|'},
                            {'|',' ',' ',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ','&','&','&','&','&','&',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ',' ',' ','|'},
                            {'|',' ',' ',' ','&','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ','&',' ',' ',' ',' ','&',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ','&','&',' ',' ',' ','|'},
                            {'|',' ',' ',' ','&','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','&',' ',' ','&',' ',' ',' ',' ','&',' ',' ',' ','&',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ','&','&',' ',' ',' ','|'},
                            {'|',' ',' ',' ','&','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','&',' ',' ','&',' ',' ',' ',' ','&',' ',' ',' ','&',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ','&','&',' ',' ',' ','|'},
                            {'|',' ',' ',' ','&','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ','&',' ',' ',' ',' ','&',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ','&','&',' ',' ',' ','|'},
                            {'|',' ',' ',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ',' ',' ','&','&','&','&','&','&',' ',' ',' ',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ',' ',' ','|'},
                            {'|',' ',' ',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ',' ',' ','|'},
                            {'|','&',' ',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ','&','&',' ',' ',' ',' ',' ',' ',' ',' ',' ','&','&',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ',' ','&','|'},
                            {'|',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|',' ',' ','&','&',' ',' ',' ',' ',' ',' ',' ','&','&',' ',' ','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ','|'},
                            {'|',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','&','&','-','-','-','-','-','-','-','-','-','-','-','&','&','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ','|'},
                            {'|','&',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ',' ',' ',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ','&','|'},
                            {'|',' ','&',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ',' ',' ',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ','&',' ','|'},
                            {'|',' ',' ','&',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ','&',' ',' ','|'},
                            {'|','&',' ',' ','&',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ',' ',' ','&',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','&',' ',' ','&',' ',' ','&','|'},
                            {'-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-','-'}
                            };

    for (int i = 0; i < 24; ++i) {
        for (int j = 0; j < 48; ++j)
            mvaddch(i, j, TEMP_MAP[i][j]);
            //printf("%c ", TEMP_MAP[i][j]);
    }
    //fflush(stdout);

    mvaddstr(5, 53, "BBN super game");
    mvaddstr(7, 53, "[w a s d control; j bubble]");
    mvaddstr(11, 53, "press any key try to start");
    mvaddstr(14, 53, "                        ");
    mvaddstr(17, 53, "                        ");
    refresh();
}
