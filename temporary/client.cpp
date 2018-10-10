#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
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
int p1,p2;
int in_win;
int in_lose;

int left_board;
int right_board;
int d_left_board;
int d_right_board;
int is_lose=0;
int is_win=0;
int rsize;
int sock;
int delay=100;
int ndelay;
void moveBall();
struct winsize size;
int listenfd, connfd;
int     n;
struct sockaddr_in     servaddr = {0};
char    rbuf[128];
char    wbuf[128] = "hello client";

void control();
void sent_pos();
void lose();
void win();

FILE *fp;



int main(int argc,char **argv)
{
	fp=fopen("res.txt","w");

	ioctl(STDIN_FILENO, TIOCGWINSZ, &size);
	char wbuf[] = "hello server";
	char rbuf[128];
	int i;
	p1=0;
	p2=0;
	struct sockaddr_in	server = {0};
	struct timeval timeo;
	char cmd[200]; 

	timeo.tv_sec  = 0;
	timeo.tv_usec = 1000 * 1000;		//
	socklen_t len = sizeof(timeo);
	if( argc != 2)
	{
		printf("usage: ./client <ipaddress>\n");
		return -1;
	}

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("Create TCP Socket");

		return -1;
	}

	setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeo, len);

	server.sin_family = AF_INET;
	server.sin_port = htons(30000);
	inet_pton(AF_INET,  argv[1], &(server.sin_addr));

	int res = connect(sock, (struct sockaddr*)&server, sizeof(server));
	if (res < 0)
	{
		if(res == EINPROGRESS)	
			perror("connecting stream socket time out:");
		else
			perror("connecting stream socket error:");
		close(sock);
		return -1;
	}
	else
	{
		printf("Connect Server@%s\n",argv[1]);
		//for(i=0;i<100;i++)
		//{       
		strcpy(wbuf,"got");
		int wsize = send(sock,wbuf,sizeof(wbuf),0);
		if(wsize<=0)
		{

			perror("write error:");
			close(sock);
			return -1;
		}
		//printf("1111111i=%d\n",i);

		rsize=recv(sock,rbuf,sizeof(rbuf),0);
		if(rsize>0)
		{
			rbuf[rsize]='\0';
			//printf("recv msg from server: %s\n",rbuf);
			//sprintf(cmd, "%s", rbuf);
			//system(cmd); 
			if (rbuf[0]=='s')
			{
				initscr();
				crmode();
				noecho();
				control();
				endwin();
			}
		}
		if(rsize<0)
		{
			close(sock);				
			perror("read error:");
			return -1;
		}			
		//}
		close(sock); fclose(fp);
		return 0;
	}

}

void init(){
	int i,j;
	in_win=0;
	in_lose=0;
	clear();

	//init ball
	pos_X =size.ws_col-(0.5*COLS+1);
	pos_Y =size.ws_row-(0.5*size.ws_row+1); 
	hdir=-1;
	vdir=1;

	//init board
	left_board=0.5*COLS-1-0.5*BOARD_LENGTH;
	right_board=left_board+BOARD_LENGTH-1;
	for(i=left_board;i<=right_board;i++){
		move(BOTTOM,i);
		addch('=');
	}
	d_left_board=0.5*COLS-1-0.5*BOARD_LENGTH;
	d_right_board=left_board+BOARD_LENGTH-1;
	for(i=d_left_board;i<=d_right_board;i++){
		move(TOP-1,i);
		addch('=');
	}
	move(BOTTOM,0);
	for (i=0;i<=14;i++){
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
	rsize=recv(sock,rbuf,sizeof(rbuf),0);
	//init time
	ndelay=2;
	signal(SIGALRM,moveBall);
	set_ticker(delay*ndelay);

	keypad(stdscr,TRUE);
	attroff(A_BLINK);
	is_lose=0;is_win=0;

	move(pos_Y,pos_X);
	addch(BALL);
	move(LINES-1, COLS-1);
	//refresh();
	//usleep(100000);
	move(LINES-1,COLS-1); //printf("++!!++%d %d\n",pos_X, pos_Y);
	refresh(); // printf("++++!!!!!!!!!\n"); 
	//fprintf(fp,"init++!!++%d %d\n",pos_X,pos_Y); fflush(fp);
}

void moveBall(){
	if(is_lose || is_win) { ungetch('q'); return;}
	signal(SIGALRM,moveBall); //printf("++!!++%d %d\n",pos_X, pos_Y);
	sent_pos(pos_Y, pos_X, left_board, right_board);   //fprintf(fp,"sent %d %d %d %d\n",pos_Y, pos_X, left_board, right_board);
	move(pos_Y,pos_X);
	addch(BLANK);  //refresh(); 
	//pos_Y += vdir;	
	//pos_X += hdir;
	//fprintf(fp,"++!!++%d %d\n",pos_X,pos_Y); fflush(fp); //fsync(fp);

	//printf("++!!++%d %d\n",pos_X, pos_Y);  refresh();
	rsize=recv(sock,rbuf,sizeof(rbuf),0); //fprintf(fp,"after recv %d %d\n",pos_X,pos_Y); fflush(fp);
	if(rsize>0)
	{	//fprintf(fp,"before recv %d %d\n",pos_X,pos_Y); fflush(fp);
		//fprintf(fp,"recv msg from server: %s\n",rbuf);
		//rbuf[rsize]='\0'; 
		//fprintf(fp,"recv msg from server: %s\n",rbuf);
		//sprintf(cmd, "%s", rbuf);
		//system(cmd); 

		if (rbuf[0]=='f') 
		{
			is_win=1;
		}
		else if (rbuf[0]=='w')
		{
			is_lose=1;
		}
		else
		{
			int j=0; int tmp=0; int i=0; 
			for (i=0;i<4;i++)
			{	//fprintf(fp,"after recv %d %d\n",pos_X,pos_Y); fflush(fp);
				while (rbuf[j]!=' ')
				{
					tmp=tmp*10+(rbuf[j]-48);
					j++;	
				}   //printf("++++%d %d\n",tmp,size.ws_col);
				if (i==0) pos_X=size.ws_col-tmp-1;
				else if (i==1) pos_Y=size.ws_row-tmp-1-2;
				else if (i==2) d_right_board=size.ws_col-tmp-1;
				else if (i==3) d_left_board=size.ws_col-tmp-1;
				tmp=0;j++;  
			}   //printf("++++%d %d\n",d_left_board,d_right_board);

			move(TOP-1,0); j=0; //printf("++++%d %d\n",size.ws_row,size.ws_col);
			for (j=0;j<size.ws_col;j++)
			{
				move(TOP-1,j);
				addch(BLANK);

			}   
			move(TOP-1,d_left_board); 
			addstr("==========");  
			move(LINES-1,COLS-1); //printf("++++!!!!!!!\n");
			refresh();  //printf("++!!++%d %d\n",pos_X, pos_Y);  refresh();
		}	


	}
	else if(rsize<0)
	{
		close(sock);				
		perror("read error:");
		return;
	}
	// fprintf(fp,"++!!++++%d %d %d %d\n",pos_X,pos_Y,hdir,vdir); fflush(fp);
	//改变方向 
	//if(pos_X >= RIGHT)
	hdir = -1;
	//if(pos_X <= LEFT)
	hdir = 1;
	//if(pos_Y <= TOP)
	//	vdir = 1;


	//printf("++++%d %d\n",pos_X, pos_Y);
	move(pos_Y,pos_X); 
	addch(BALL);
	move(LINES-1, COLS-1); 

	//printf("++++%s\n",wbuf);
	refresh();
	if(pos_Y >= BOTTOM-1){
		if(pos_X>=left_board&&pos_X<=right_board)
			vdir=-1;
		else{
			is_lose=1;
			p1=p1+1;
			move(BOTTOM+2,4);
			addch(p1+'0');
			move(LINES-1,COLS-1);
			refresh();
			in_lose=1;
			lose();
			//sent_pos(pos_Y, pos_X, left_board, right_board);

			/*move(pos_Y,pos_X);
			  addch(BALL);
			  move(LINES-1, COLS-1);
			  refresh();
			  usleep(delay*ndelay*1000);
			  move(pos_Y,pos_X);
			  addch(BLANK);
			  pos_X += hdir;
			  pos_Y += vdir;
			  move(pos_Y,pos_X);
			  addch(BALL);
			  move(LINES-1, COLS-1);
			  refresh();*/
		}
	}

	if(pos_Y<=TOP)
	{
		if (pos_X>=d_left_board&&pos_X<=d_right_board)
			vdir=1;
		else
		{
			is_win=1;
			p2=p2+1;
			move(BOTTOM+2,11);
			addch(p2+'0');
			move(LINES-1,COLS-1);
			refresh();
			in_win=1;
			win();
			//sent_pos(pos_Y, pos_X, left_board, right_board);
			/*move(pos_Y,pos_X);
			  addch(BALL);
			  move(LINES-1, COLS-1);
			  refresh();
			  usleep(delay*ndelay*1000);
			  move(pos_Y,pos_X);
			  addch(BLANK);
			  pos_X += hdir;
			  pos_Y += vdir;
			  move(pos_Y,pos_X);
			  addch(BALL);
			  move(LINES-1, COLS-1);
			  refresh();*/
		}

	}



}
void control(){
	init(); 
	//moveBall();
	int cmd;   	
	while (!in_lose && !in_win)
	{	
		if(!is_lose && !is_win){
			cmd=getch();
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
					move(LINES-1,COLS-1);;
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
					move(LINES-1,COLS-1);;
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
		/*else if(is_lose){
		  lose();
		  break;
		  }
		  else if(is_win)
		  {
		  win();
		  break;
		  }*/
	}
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
	addstr("Server got one point. Press 'y' to continue, 'n' to quit\n");
	refresh();
	choice=getch();


	while(flag){
		if(choice=='y'||choice=='Y'||choice=='n'||choice=='N')
			flag=0;
		else  choice=getch();
	}
	if(choice=='y'||choice=='Y'){
		if (p1==TOTAL){
			move(6,10);
			addstr("                                                               ");
			move(6,10);
			addstr("You lose the game. Press ay key to quit...");
			refresh();
		}
		else {  
			is_win=0;
			is_lose=0; 
			endwin();

			initscr();
			crmode();
			noecho();
			//control();
			int wsize = send(sock,wbuf,sizeof(wbuf),0);
			//fprintf(fp,"%d: \n",wsize); fflush(fp);
			init();



		}

	}
	else if(choice=='n'||choice=='N'){
		move(6,10);
		addstr("                                                                               ");
		move(6,10);
		addstr("Game over! Press any key to quit...");	
		refresh();				
	}
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
		if (p2==TOTAL){
			move(6,10);
			addstr("                                                               ");
			move(6,10);
			addstr("You won the game. Press ay key to quit...");
			refresh();
		}
		else {
			is_win=0;
			is_lose=0;
			endwin();
			initscr();
			crmode();
			noecho();
			//control();
			int wsize = send(sock,wbuf,sizeof(wbuf),0);
			//fprintf(fp,"%d: \n",wsize); fflush(fp);
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




	n = send(sock,wbuf,sizeof(wbuf),0);
	// printf("++++%s\n",wbuf);

	if(n<=0)
	{
		perror("sned error:");
		close(connfd);
		//break;
	}


}

//void sent_msg(char *msg)

/*void recv_pos(int bod_x, int bod_y)
  {
  n = recv(connfd, rbuf, sizeof(rbuf), 0);
  if(n>0)
  {
  rbuf[n] = '\0';
//printf("recvmsg from client: %s\n", rbuf);

}
int j=0; int tmp=0; int i=0;
for (i=0;i<4;i++)
{
while (rbuf[j]!=' ')
{
tmp=tmp*10+(rbuf[j]-48);
j++;	
}
if (i==0) pos_X=2*size.ws_col-tmp;
else if (i==1) pos_Y=2*size.ws_row-tmp;
else if (i==2) d_left_board=2*size.ws_col-tmp;
else if (i==3) d_right_board=2*size.ws_row-tmp;

tmp=0;
}




}

*/
