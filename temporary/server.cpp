#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <curses.h>
#include <sys/time.h>
#include <signal.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <termios.h>

#define LEFT 0
#define RIGHT (COLS-1)
#define TOP 1
#define BOTTOM (LINES-1-2)
#define WIDE RIGHT-LEFT+1
#define BOARD_LENGTH   10
#define TOTAL 3

char BALL= 'O';
char BLANK= ' ';

int hdir;
int vdir;
int pos_X ;
int pos_Y;

int left_board;
int right_board;
int d_left_board;
int d_right_board;
int is_lose=0;
int is_win=0;
int p1,p2;
int in_win,in_lose;

int delay=100;
int ndelay;
void moveBall();
struct winsize size;
int listenfd, connfd;
int     n;
int cn=0;
struct sockaddr_in     servaddr = {0};
char    rbuf[128];
char    wbuf[128] = "hello client";

void control();
void sent_pos();
void recv_pos();
void lose();
void win();

FILE *fp;

int main(int argc, char** argv)
{
	fp=fopen("res.txt","w");
	ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
	//printf("%d\n", size.ws_col);
	//printf("%d\n", size.ws_row);
	int tmp_col, tmp_row, tmp_i;


	p1=0;
	p2=0;
	hdir=1;
	vdir=-1;
	in_win=0;
	in_lose=0;
	tmp_col=size.ws_col;
	tmp_row=size.ws_row;
	tmp_i=1000;
	if( (listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1 )
	{
		perror("Create TCP Socket");
		return -1;
	}

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(30000);

	if( bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1)
	{
		perror("bind socket error:");
		return -1;
	}

	if( listen(listenfd, 10) == -1)
	{
		perror("listen socket error:");
		return -1;
	}

	printf("======waiting for client's request======\n");

	while( (connfd = accept(listenfd, (struct sockaddr*)NULL, NULL)) == -1 )
	{
		perror("accept socket error:");

	}
	n = recv(connfd, rbuf, sizeof(rbuf), 0);
	if(n>0)
	{
		//rbuf[n] = '\0';
		fprintf(fp,"recvmsg from client: %s\n", rbuf); fflush(fp);
		if (strcmp(rbuf,"got"))
		{
			fprintf(fp,"Connected\n");
		}


		strcpy(wbuf,"s");
		n = send(connfd, wbuf, sizeof(wbuf),0);
		if(n<=0)
		{
			perror("sned error:");
			close(connfd);
			//break;
		}
	}
	else if(n < 0)
	{
		perror("recv error:");
		close(connfd);
		//break;
	}

	initscr();
	crmode();
	noecho();
	control();
	endwin(); // printf("++++%s\n",wbuf);
	close(connfd);
	fclose(fp);
	close(listenfd);
	return 0;
}

void init(){
	int i,j;
	clear();
	in_win=0;
	in_lose=0;
	is_lose=0;is_win=0;

	//init ball
	pos_X =0.5*COLS;
	pos_Y = 0.5*(BOTTOM+1);
	hdir=-hdir;
	vdir=-vdir;

	//init board
	left_board=0.5*COLS-1-0.5*BOARD_LENGTH;
	right_board=left_board+BOARD_LENGTH-1;
	for(i=left_board;i<=right_board;i++){
		move(BOTTOM,i);
		addch('=');
	}
	//sent_pos(pos_Y, pos_X, left_board, right_board);
	//printf("!!!!!!!!!%d %d\n", left_board,right_board); system("pause");
	d_left_board=0.5*COLS-1-0.5*BOARD_LENGTH;
	d_right_board=left_board+BOARD_LENGTH-1;
	for(i=d_left_board;i<=d_right_board;i++){
		move(TOP-1,i);
		addch('=');
	}
	move(BOTTOM+1,0);
	for(i=0;i<=14;i++){
		move(BOTTOM,i);
		addch('_');
	}
	move(BOTTOM+1,1);
	addstr("server:client");
	move(BOTTOM+1,15);
	addstr("|");
	move(BOTTOM+2,3);
	addstr("0");
	addch(p1+'0');
	move(BOTTOM+2,7);
	addstr(":");
	move(BOTTOM+2,10);
	addstr("0");
	addch(p2+'0');
	move(BOTTOM+2,15);
	addstr("|");

	move(LINES-1,COLS-1);
	//refresh();
	sent_pos(pos_X, pos_Y, left_board, right_board);
	//init time
	ndelay=2;
	signal(SIGALRM,moveBall);
	set_ticker(delay*ndelay);

	keypad(stdscr,TRUE);
	attroff(A_BLINK);

	move(pos_Y,pos_X);
	addch(BALL);
	move(LINES-1, COLS-1);
	//refresh();
	//usleep(100000);
	move(LINES-1,COLS-1);
	refresh();
	//fprintf(fp,"Init finished is_lose:%d is_win:%d\n",is_lose,is_win); fflush(fp);
}

void moveBall(){
	if(is_lose || is_win) { return;}
	recv_pos();
	signal(SIGALRM,moveBall);
	move(pos_Y,pos_X);
	addch(BLANK);
	pos_X += hdir;
	pos_Y += vdir;

	//change dir
	if(pos_X >= RIGHT)
		hdir = -1;
	if(pos_X <= LEFT)
		hdir = 1;
	//if(pos_Y <= TOP)
	//	vdir = 1;

	move(pos_Y,pos_X);
	addch(BALL);
	move(LINES-1, COLS-1);
	sent_pos(pos_X, pos_Y, left_board, right_board); // fprintf(fp,"sent %s\n",wbuf); fflush(fp);
	//printf("++++%s\n",wbuf);
	refresh(); //refresh(); fprintf(fp,"pos_Y %d\n",pos_Y); fflush(fp);
	//bottom or top process
	if(pos_Y >= BOTTOM-1){
		if(pos_X>=left_board&&pos_X<=right_board)
			vdir=-1;
		else{
			is_lose=1;
			p2=p2+1;
			//strcpy(wbuf,"f");
			//n = send(connfd, wbuf, sizeof(wbuf),0);
			move(pos_Y,pos_X);
			addch(BALL);
			move(LINES-1, COLS-1);
			refresh();
			usleep(delay*ndelay*1000);
			move(pos_Y,pos_X);
			addch(BLANK);
			//pos_X += hdir;
			//pos_Y += vdir;
			move(pos_Y,pos_X);
			addch(BALL);
			move(LINES-1, COLS-1);
			refresh();
			move(BOTTOM+2,11);
			addch(p2+'0');
			initscr();
			crmode();
			noecho();	move(LINES-1, COLS-1);
			refresh();
			in_lose=1;
			lose();
		}
	}

	if(pos_Y<=TOP)
	{
		if (pos_X>=d_left_board&&pos_X<=d_right_board)
			vdir=1;
		else
		{
			is_win=1;
			p1=p1+1;
			//strcpy(wbuf,"w");
			//n = send(connfd, wbuf, sizeof(wbuf),0);
			move(pos_Y,pos_X);
			addch(BALL);
			move(LINES-1, COLS-1);
			refresh();
			usleep(delay*ndelay*1000);
			move(pos_Y,pos_X);
			addch(BLANK);
			//pos_X += hdir;
			//pos_Y += vdir;
			move(pos_Y,pos_X);
			addch(BALL);
			move(LINES-1, COLS-1);
			refresh(); //fprintf(fp,"pos_Y pos_X%d %d\n",pos_Y,pos_X); fflush(fp);
			move(BOTTOM+2,4);
			addch(p1+'0');
			move(LINES-1, COLS-1);
			refresh();
			in_win=1;
			win();
		}

	}



}
void control(){
	init(); //moveBall();
	int cmd;   int cnl=cn+1; cn=cn+1;
	while (!in_lose && !in_win)
	{
		//recv_pos();
		if(!is_lose && !is_win){

			//fprintf(fp,"%d Getch1\n",cnl); fflush(fp);
			cmd = getch();
			//if( cmd == 0 || cmd == 0xE0 )
			//cmd = getch();
			//fprintf(fp,"%d Getch2 %d\n",cnl,cmd); fflush(fp);
			if(cmd==113) break;//exit
			//board->left
			else if(cmd==KEY_LEFT){
				if(left_board>0){
					move(BOTTOM,right_board);
					addch(' ');
					right_board--;
					left_board--;
					move(BOTTOM,left_board);
					addch('=');
					move(LINES-1, COLS-1);
					refresh();
				}
			}
			//board->right
			else if(cmd==KEY_RIGHT){
				if(right_board<RIGHT){
					move(BOTTOM,left_board);
					addch(' ');
					right_board++;
					left_board++;
					move(BOTTOM,right_board);
					addch('=');
					move(LINES-1, COLS-1);
					refresh();
				}
			}
			else if(cmd==KEY_UP){
				delay=delay/2;
				if(delay<10)delay=delay*2;
			}
			else if(cmd==KEY_DOWN){
				delay=delay*2;
				if(delay>200)delay=delay/2;
			}


		}
		/*	else if(is_lose){


			lose();
			break;
			}
			else if(is_win)
			{
			win();
			break;
			}*/
		//printf("++++%d %d\n",left_board,right_board);
	}
	//fprintf(fp,"Control finished\n"); fflush(fp);
}

int set_ticker(int n_msecs){
	struct itimerval new_timeset;
	long n_sec,n_usecs;
	n_sec=n_msecs/1000;
	n_usecs=(n_msecs%1000)*1000L;
	new_timeset.it_interval.tv_sec=n_sec;
	new_timeset.it_interval.tv_usec=n_usecs;
	new_timeset.it_value.tv_sec=n_sec;
	new_timeset.it_value.tv_usec=n_usecs;
	return setitimer(ITIMER_REAL,&new_timeset,NULL);

}

void lose()
{
	int flag=1;
	char choice;
	move(6,10);
	addstr("Client got one point. Press 'y' to continue, 'n' to quit\n");
	refresh();
	choice=getch();


	while(flag){
		if(choice=='y'||choice=='Y'||choice=='n'||choice=='N')
			flag=0;
		else  choice=getch();
	}
	if(choice=='y'||choice=='Y'){
		if (p2==TOTAL) {
			move(6,10);
			addstr("                                                          ");
			move(6,10);
			addstr("You lose the game. Press any key to quit...");
			refresh();
		}
		else {

			is_win=0;
			is_lose=0; //ungetch('q');
			endwin();
			initscr();
			crmode();
			noecho();
			recv(connfd, rbuf, sizeof(rbuf), 0);
			//control();
			init();

		}

	}
	else if(choice=='n'||choice=='N'){
		move(6,10);
		addstr("                                                                 ");
		move(6,10);
		addstr("Game over! Press any key to quit...");
		refresh();
	}
	//fprintf(fp,"Lose finished\n"); fflush(fp);
}

void win()
{
	int flag=1;
	char choice;
	move(6,10);
	addstr("You got one point. Press 'y' to continue, 'n' to quit\n");
	refresh();
	choice=getch();


	while(flag){
		if(choice=='y'||choice=='Y'||choice=='n'||choice=='N')
			flag=0;
		else  choice=getch();
	}
	if(choice=='y'||choice=='Y'){
		if (p1==TOTAL) {
			move(6,10);
			addstr("                                                       ");
			move(6,10);
			addstr("You won the game. Press any key to quit...");
			refresh();
		}
		else {

			is_win=0;
			is_lose=0; //ungetch('q');
			endwin();
			initscr();
			crmode();
			noecho();
			recv(connfd, rbuf, sizeof(rbuf), 0);
			//control();
			init();

		}
	}
	else if(choice=='n'||choice=='N'){
		move(6,10);
		addstr("                                                               ");
		move(6,10);
		addstr("Game over! Press any key to quit...");
		refresh();
	}
}


void sent_pos(int x, int y, int bod_x, int bod_y)
{

	int tmp_x, tmp_y, tmp_bod_x, tmp_bod_y, tmp_i=1000, tmp=0;
	strcpy(wbuf,"");
	tmp_i=1000;
	tmp=0;
	tmp_x=x; tmp_y=y;  tmp_bod_x=bod_x; tmp_bod_y=bod_y;
	while (tmp_i!=0 && tmp_x / tmp_i==0)
		tmp_i=tmp_i/10;
	if (tmp_i==0) strcat(wbuf,"0");
	while (tmp_i>0)
	{

		tmp=tmp_x / tmp_i + 48;
		strcat(wbuf,(char*)&tmp);
		tmp_x=tmp_x%tmp_i;
		tmp_i=tmp_i/10;
	}
	strcat(wbuf," ");

	tmp_i=1000;
	tmp=0;
	while (tmp_i!=0 && tmp_y / tmp_i==0)
		tmp_i=tmp_i/10;
	if (tmp_i==0) strcat(wbuf,"0");
	while (tmp_i>0)
	{

		tmp=tmp_y / tmp_i + 48;
		strcat(wbuf,(char*)&tmp);
		tmp_y=tmp_y%tmp_i;
		tmp_i=tmp_i/10;
	}
	strcat(wbuf," ");

	tmp_i=1000;
	tmp=0;
	while (tmp_i!=0 && tmp_bod_x / tmp_i==0)
		tmp_i=tmp_i/10;
	if (tmp_i==0) strcat(wbuf,"0");
	while (tmp_i>0)
	{

		tmp=tmp_bod_x / tmp_i + 48;
		strcat(wbuf,(char*)&tmp);
		tmp_bod_x=tmp_bod_x%tmp_i;
		tmp_i=tmp_i/10;
	}
	strcat(wbuf," ");

	tmp_i=1000;
	tmp=0;
	while (tmp_i!=0 && tmp_bod_y / tmp_i==0)
		tmp_i=tmp_i/10;
	if (tmp_i==0) strcat(wbuf,"0");
	while (tmp_i>0)
	{

		tmp=tmp_bod_y / tmp_i + 48;
		strcat(wbuf,(char*)&tmp);
		tmp_bod_y=tmp_bod_y%tmp_i;
		tmp_i=tmp_i/10;
	}
	strcat(wbuf," ");




	n = send(connfd, wbuf, sizeof(wbuf),0);
	//	printf("++++%s\n",wbuf);

	if(n<=0)
	{
		perror("sned error:");
		close(connfd);
		//break;
	}


}

//void sent_msg(char *msg)

void recv_pos()
{
	n = recv(connfd, rbuf, sizeof(rbuf), 0);
	if(n>0)
	{
		// rbuf[n] = '\0';
		//fprintf(fp,"recvmsg from client: %s\n", rbuf);

		//printf("++++%s\n",rbuf);
		int j=0; int tmp=0; int i=0;

		for (i=0;i<4;i++)
		{
			while (rbuf[j]!=' ')
			{
				tmp=tmp*10+(rbuf[j]-48);
				j++;
			}
			//if (i==0) pos_X=2*size.ws_col-tmp-1;
			//else if (i==1) pos_Y=2*size.ws_row-tmp-1;
			//fprintf(fp,"tmp %d\n",tmp); fflush(fp);
			if (i==2) d_right_board=size.ws_col-tmp-1;
			else if (i==3) d_left_board=size.ws_col-tmp-1;
			tmp=0;j++;
		}
		//fprintf(fp,"recv l_b r_b %d %d\n",d_left_board,d_right_board); fflush(fp);
		move(TOP-1,0); j=0;
		for (j=0;j<size.ws_col;j++)
		{
			move(TOP-1,j);
			addch(' ');
		}
		move(TOP-1,d_left_board);
		addstr("==========");
		move(LINES-1, COLS-1);
		refresh();

	}



}
