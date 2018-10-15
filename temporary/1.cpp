#include <curses.h>
#include <signal.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include   <unistd.h>
#include   <time.h>
#include   <string.h>
//²Ëµ¥
#define ENTER 10  //žÃ²Ëµ¥Ïî±»Ñ¡ÖÐ
#define ESCAPE 27 //²»ÏÔÊŸ²Ëµ¥Ïî
//ÈË
#define BLANK   ' '
#define PERSON_SYMBOL  'R'  //Žú±íÈË
#define TOP_ROW   3
#define BOT_ROW   LINES-1
#define LEFT_EDGE 1
#define RIGHT_EDGE COLS-1
#define X_INIT  20  //ÈËµÄÆðÊŒÎ»ÖÃ
#define Y_INIT   20 
#define TICKS_PER_SEC   10
#define X_TTM  10 //affects speed
#define Y_TTM   10



struct person{   //ÈËµÄœá¹¹Ìå
	int y_pos,x_pos;
	int y_ttm1,y_ttm2,x_ttm1,x_ttm2;
	int y_ttg1,y_ttg2,x_ttg1,x_ttg2;
	int y_dir,x_dir;
	char symbol;
}the_person;
int valid;//±íÊŸÈËµ±Ç°ÕýÔÚÏòÄÄžö·œÏòÔË¶¯£¬valid=1,ÏòÉÏ£»valid=2,ÏòÏÂ£»valid=3£¬Ïò×ó£»valid=4,ÏòÓÒ¡£
int Score;//ŒÆ·Ö
void set_up();

//Çò
#define	DEVIL_SYMBOL	'M'//±íÊŸÄ§¹í
#define TOTAL       1000  /*  10000 balls in all */
#define X_TTM0 60
#define Y_TTM0 60



#define creat_ball_ttm 2
int creat_ball_ttg;//²úÉúÇòµÄŒäžôÊ±Œä

struct ppball {
	int	y_pos,
		y_ttm,
		y_ttg,
		value,
		color;//color-index

	char	symbol ;
	struct ppball * next;

} ;

int BallColor[] =
{
	COLOR_RED,
	COLOR_GREEN,
	COLOR_YELLOW,
	COLOR_BLUE,
	COLOR_MAGENTA,
	COLOR_CYAN,
};

char BallSymbol[]=//ÇòµÄÐÎ×Ž
{
	'O',
	'%',
	'*',
	'@',
	'$',
	'B'
};
const int xpos[10]={0,10,20,30,40,50,60,65,70,75};//Çò·Ö²ŒµÄx×ø±ê
struct ppball * the_ball[10] ;
//Ä§¹í
struct devil
{
	int x_pos,
		y_pos,
		x_ttm,
		x_ttg,
		y_ttm,
		y_ttg,
		x_dir,
		y_dir;
	char symbol;
};
struct devil dev[5];
int count;//total balls

struct Tmp
{
	int x,y,c;
}tmp;

//Move,×îÖØÒªµÄº¯Êý£¬µœÊ±ŒäŸÍŽ¥·¢Õâžöº¯Êý
void Move(int signum)
{
	//Çò
	int	dx_cur,dy_cur,bucket,i,moved;
	struct ppball * newball, * curball,*preball;

	signal( SIGALRM , SIG_IGN );		/* dont get caught now 	*/



	/*get a new ball */
	if(creat_ball_ttg--==0)
	{
		creat_ball_ttg=creat_ball_ttm;
		count--;
		if(count==-1)return;
		bucket=rand()%10;   //chose the bucket
		newball= (struct ppball *)malloc(sizeof(struct ppball));


		newball->y_ttm=newball->y_ttg=rand()%3;//get speed
		newball->symbol=BallSymbol[rand()%6];//get symbol
		newball->color=rand()%6;//get color index
		newball->value=(newball->color+1)*10;
		newball->y_pos=TOP_ROW;//start from TOP_ROW
		if(the_ball[bucket]==NULL)//insert
		{
			newball->next=NULL;
			the_ball[bucket]=newball;
		}
		else
		{
			newball->next=the_ball[bucket];
			the_ball[bucket]=newball;
		}
	}

	/*deal with other balls*/
	for(i=0;i<10;i++)
	{
		curball=the_ball[i];
		preball=NULL;
		while(curball!=NULL)
		{

			if ( curball->y_ttm > 0 && curball->y_ttg-- == 1 )
			{
				mvaddch( curball->y_pos,xpos[i] , BLANK );
				curball->y_pos += 1 ;	/* move	*/
				if(curball->y_pos<=BOT_ROW)
				{
					curball->y_ttg = curball->y_ttm  ;	/* reset*/
					attron(COLOR_PAIR(curball->color+1));
					mvaddch( curball->y_pos, xpos[i], curball->symbol );
					attroff(COLOR_PAIR(curball->color+1));
				}
				else
				{
					if(preball==NULL)
					{
						free(curball);
						the_ball[i]=0;
						curball=0;
					}
					else
					{
						preball->next=curball->next;
						free(curball);
						curball=preball;
					}
				}
			}
			preball=curball;
			if(curball!=NULL)curball=curball->next;//move forward;

		}
	}

	/*deal with devil*/
	for(i=0;i<5;i++)
	{
		dy_cur = dev[i].y_pos ;		/* old spot		*/
		dx_cur = dev[i].x_pos ;
		if(dev[i].y_ttm>0&&dev[i].y_ttg--==1)
		{
			dev[i].y_pos += dev[i].y_dir ;	/* move	*/
			dev[i].y_dir=rand()%2==1?(i+1):-(i+1);  /* redefine y_dir*/
			if(dev[i].y_pos>=BOT_ROW)
			{
				dev[i].y_pos=BOT_ROW;
				dev[i].y_dir=-1;
			}
			else if(dev[i].y_pos<=TOP_ROW)
			{
				dev[i].y_pos=TOP_ROW;
				dev[i].y_dir=1;
			}
			dev[i].y_ttg = dev[i].y_ttm  ;	/* reset*/
			dev[i].y_ttm=rand()%8+1;/* redefine y_ttm */
			moved = 1;
		}

		if ( dev[i].x_ttm > 0 && dev[i].x_ttg-- == 1 ){
			dev[i].x_pos += dev[i].x_dir ;	/* move	*/
			dev[i].x_dir=rand()%2==1?i+1:-(i+1);  /* redefine x_dir*/
			if(dev[i].x_pos>=RIGHT_EDGE)
			{
				dev[i].x_pos=RIGHT_EDGE;
				dev[i].x_dir=-1;
			}
			else if(dev[i].x_pos<=LEFT_EDGE)
			{
				dev[i].x_pos=LEFT_EDGE;
				dev[i].x_dir=1;
			}
			dev[i].x_ttg = dev[i].x_ttm  ;	/* reset*/
			dev[i].x_ttm=rand()%5+1;/* redefine x_ttm */
			moved = 1;
		}

		if ( moved ){
			mvaddch( dy_cur, dx_cur, BLANK );
			mvaddch( dev[i].y_pos, dev[i].x_pos, dev[i].symbol );

		}
	}




	//ÈË
	int y_cur,x_cur;
	y_cur=the_person.y_pos;
	x_cur=the_person.x_pos;
	moved=0;

	if(the_person.y_ttm1>0&&the_person.y_ttg1--==1)
	{
		the_person.y_pos+=the_person.y_dir;
		the_person.y_ttg1=the_person.y_ttm1;
		moved=1;
	}

	if(the_person.y_ttm2>0&&the_person.y_ttg2--==1)
	{
		the_person.y_pos+=the_person.y_dir;
		the_person.y_ttg2=the_person.y_ttm2;
		moved=1;
	}
	if(the_person.x_ttm1>0&&the_person.x_ttg1--==1)
	{
		the_person.x_pos+=the_person.x_dir;
		the_person.x_ttg1=the_person.x_ttm1;
		moved=1;
	}

	if(the_person.x_ttm2>0&&the_person.x_ttg2--==1)
	{
		the_person.x_pos+=the_person.x_dir;
		the_person.x_ttg2=the_person.x_ttm2;
		moved=1;
	}
	if(moved)
	{

		mvaddch(y_cur,x_cur,BLANK);
		attron(COLOR_PAIR(7)|A_BOLD);
		mvaddch(the_person.y_pos,the_person.x_pos,the_person.symbol);
		attroff(COLOR_PAIR(7)|A_BOLD);
		bounce_or_lose(&the_person);
		if(tmp.c==3)
		{
			mvaddch(tmp.y,tmp.x,BLANK);
			mvaddch(tmp.y,tmp.x+1,BLANK);
			mvaddch(tmp.y,tmp.x+2,BLANK);
		}
		if(tmp.c==4)
		{
			mvaddch(tmp.y,tmp.x,BLANK);
			mvaddch(tmp.y,tmp.x+1,BLANK);
			mvaddch(tmp.y,tmp.x+2,BLANK);
			mvaddch(tmp.y,tmp.x+3,BLANK);
		}

	}



	//ÅÐ¶ÏÈËºÍÇò»òÄ§¹íÊÇ·ñÏàÅö
	struct ppball *p,*q;
	p= (struct ppball *)malloc(sizeof(struct ppball));
	q= (struct ppball *)malloc(sizeof(struct ppball));
	for(i=0;i<10;i++)//¶¹×Ó
	{
		if(the_person.x_pos==xpos[i]&&the_ball[i]!=NULL)
		{//¿ªÊŒ±éÀúžÃÁŽ±í
			p=the_ball[i];//the_ball[i]Ïàµ±ÓÚhead
			if(the_person.y_pos==p->y_pos)//posÊÇintÀàÐÍµÄ
			{
				//ËµÃ÷ÈË³Ôµœ¶¹×ÓÁË£¬ÓÚÊÇ°ÑžÃ¶¹×ÓÒþµô£¬²¢ŽÓÁŽ±íÖÐÉŸ³ý£¬²¢ŒÓ·Ö
				//ŽÓÁŽ±íÖÐÉŸ³ý
				if((p->next)!=NULL)the_ball[i]=p->next;
				else the_ball[i]=NULL;
				//°Ñ¶¹×ÓÒþµô,ŒŽÔÚžÃÎ»ÖÃ»­¿Õ°×
				mvaddch(p->y_pos,xpos[i],BLANK);
				//ŒÓ·Ö
				attrset(A_NORMAL);
				attron(A_BLINK|A_BOLD);
				char s1[4]={'+','1','0'};
				char s2[4]={'+','2','0'};
				char s3[4]={'+','3','0'};
				char s4[4]={'+','4','0'};
				char s5[4]={'+','5','0'};
				char s6[4]={'+','6','0'};
				if(p->value==10)
				{
					mvaddstr(p->y_pos,xpos[i],s1);
					tmp.x=xpos[i];
					tmp.y=p->y_pos;
					tmp.c=3;
				}
				if(p->value==20)
				{
					mvaddstr(p->y_pos,xpos[i],s2);
					tmp.x=xpos[i];
					tmp.y=p->y_pos;
					tmp.c=3;
				}
				if(p->value==30)
				{
					mvaddstr(p->y_pos,xpos[i],s3);
					tmp.x=xpos[i];
					tmp.y=p->y_pos;
					tmp.c=3;
				}
				if(p->value==40)
				{
					mvaddstr(p->y_pos,xpos[i],s4);
					tmp.x=xpos[i];
					tmp.y=p->y_pos;
					tmp.c=3;
				}
				if(p->value==50)
				{
					mvaddstr(p->y_pos,xpos[i],s5);
					tmp.x=xpos[i];
					tmp.y=p->y_pos;
					tmp.c=3;
				}
				if(p->value==60)
				{
					mvaddstr(p->y_pos,xpos[i],s6);
					tmp.x=xpos[i];
					tmp.y=p->y_pos;
					tmp.c=3;
				}
				attroff(A_BLINK|A_BOLD);
				Score+=p->value;
			}
			else
			{

				for(p=the_ball[i];p->next!=NULL;p=p->next)//ŽÓÁŽ±íÍ·¿ªÊŒÑ°ÕÒ£¬Ö±µœÕÒµœÎªÖ¹£»ÕÒ²»µœ£¬ŸÍ²éÑ¯µœÁŽ±íÎ²ÎªÖ¹
				{
					q=p->next;
					if(the_person.y_pos==q->y_pos)
					{
						//ËµÃ÷ÈË³Ôµœ¶¹×ÓÁË£¬ÓÚÊÇ°ÑžÃ¶¹×ÓÒþµô£¬²¢ŽÓÁŽ±íÖÐÉŸ³ý£¬²¢ŒÓ·Ö
						//ŽÓÁŽ±íÖÐÉŸ³ý
						p->next=q->next;
						//°Ñ¶¹×ÓÒþµô£¬ŒŽÔÚÏàÍ¬Î»ÖÃ»­¿Õ°×
						mvaddch(q->y_pos,xpos[i],BLANK);
						//ŒÓ·Ö
						attrset(A_NORMAL);
						attron(A_BLINK|A_BOLD);
						char s1[4]={'+','1','0'};
						char s2[4]={'+','2','0'};
						char s3[4]={'+','3','0'};
						char s4[4]={'+','4','0'};
						char s5[4]={'+','5','0'};
						char s6[4]={'+','6','0'};
						if(q->value==10)
						{
							mvaddstr(q->y_pos,xpos[i],s1);
							tmp.x=xpos[i];
							tmp.y=q->y_pos;
							tmp.c=3;
						}
						if(q->value==20)
						{
							mvaddstr(q->y_pos,xpos[i],s2);
							tmp.x=xpos[i];
							tmp.y=q->y_pos;
							tmp.c=3;
						}
						if(q->value==30)
						{
							mvaddstr(q->y_pos,xpos[i],s3);
							tmp.x=xpos[i];
							tmp.y=q->y_pos;
							tmp.c=3;
						}
						if(q->value==40)
						{
							mvaddstr(q->y_pos,xpos[i],s4);
							tmp.x=xpos[i];
							tmp.y=q->y_pos;
							tmp.c=3;
						}
						if(q->value==50)
						{
							mvaddstr(q->y_pos,xpos[i],s5);
							tmp.x=xpos[i];
							tmp.y=q->y_pos;
							tmp.c=3;
						}
						if(q->value==60)
						{
							mvaddstr(q->y_pos,xpos[i],s6);
							tmp.x=xpos[i];
							tmp.y=q->y_pos;
							tmp.c=3;

						}
						attroff(A_BLINK|A_BOLD);
						Score+=q->value;
						break;
					}
				}
			}
		}
	}
	//Ä§¹í
	int j;
	for(j=0;j<5;++j)
	{
		if(the_person.x_pos==dev[j].x_pos&&the_person.y_pos==dev[j].y_pos)//ËµÃ÷ÅöµœÄ§¹íÁË
		{
			//Œõ·Ö
			Score-=5;
			attrset(A_NORMAL);
			attron(A_BLINK|A_BOLD);
			char s[5]={'-','2','0','0'};
			mvaddstr(dev[j].y_pos,dev[j].x_pos,s);
			tmp.x=dev[j].x_pos;
			tmp.y=dev[j].y_pos;
			tmp.c=4;
			attroff(A_BLINK|A_BOLD);
			//²úÉúÒ»ÖÖÐ§¹û
		}
	}
	move(LINES-1,COLS-1);

	refresh();
	signal(SIGALRM,Move);//for unreliable systems
}






//œçÃæ
void init_curses()
{
	initscr();
	start_color();
	init_pair(7,COLOR_CYAN,COLOR_WHITE);
	init_pair(8,COLOR_BLACK,COLOR_WHITE);
	init_pair(9,COLOR_CYAN,COLOR_WHITE);
	init_pair(10,COLOR_RED,COLOR_WHITE);
	init_pair(11,COLOR_BLUE,COLOR_WHITE);
	curs_set(0);
	noecho();
	keypad(stdscr,TRUE);
}
void draw_menubar(WINDOW *menubar)
{
	wbkgd(menubar,COLOR_PAIR(9));
	waddstr(menubar,"Games");
	wattron(menubar,COLOR_PAIR(10));
	waddstr(menubar,"(F2)");
	wattroff(menubar,COLOR_PAIR(10));
	wmove(menubar,0,20);
	waddstr(menubar,"Help");
	wattron(menubar,COLOR_PAIR(10));
	waddstr(menubar,"(F3)");
	wattroff(menubar,COLOR_PAIR(10));
}
WINDOW **draw_menu(int start_col)
{
	int i;
	WINDOW **items;
	if(start_col==0)
	{
		items=(WINDOW **)malloc(4*sizeof(WINDOW *));
		items[0]=newwin(5,19,1,start_col);
		wbkgd(items[0],COLOR_PAIR(9));
		box(items[0],ACS_VLINE,ACS_HLINE);
		items[1]=subwin(items[0],1,17,2,start_col+1);
		wprintw(items[1],"New");
		items[2]=subwin(items[0],1,17,3,start_col+1);
		wprintw(items[2],"Settings");
		items[3]=subwin(items[0],1,17,4,start_col+1);
		wprintw(items[3],"Quit");
	}
	if(start_col==20)
	{
		items=(WINDOW **)malloc(3*sizeof(WINDOW *));
		items[0]=newwin(4,19,1,start_col);
		wbkgd(items[0],COLOR_PAIR(9));
		box(items[0],ACS_VLINE,ACS_HLINE);
		items[1]=subwin(items[0],1,17,2,start_col+1);
		wprintw(items[1],"How to play?");
		items[2]=subwin(items[0],1,17,3,start_col+1);
		wprintw(items[2],"About Games");

	}
	wbkgd(items[1],COLOR_PAIR(8));
	wrefresh(items[0]);
	return items;
}
void delete_menu(WINDOW **items,int count)
{
	int i;
	for (i=0;i<count;i++)
		delwin(items[i]);
	free(items);
}
int scroll_menu(WINDOW **items,int count,int menu_start_col)
{
	int key;
	int selected=0;
	while (1) {
		key=getch();
		if (key==KEY_DOWN || key==KEY_UP) {
			wbkgd(items[selected+1],COLOR_PAIR(9));
			wnoutrefresh(items[selected+1]);
			if (key==KEY_DOWN) {
				selected=(selected+1) % count;
			} else {
				selected=(selected+count-1) % count;
			}
			wbkgd(items[selected+1],COLOR_PAIR(8));
			wnoutrefresh(items[selected+1]);
			doupdate();
		} else if (key==KEY_LEFT || key==KEY_RIGHT) {
			delete_menu(items,count+1);
			touchwin(stdscr);
			refresh();
			items=draw_menu(20-menu_start_col);
			if(menu_start_col==0)
				return scroll_menu(items,3,20-menu_start_col);
			if(menu_start_col==20)
				return scroll_menu(items,2,20-menu_start_col);
		} else if (key==ESCAPE) {
			return -1;
		} else if (key==ENTER) {
			return selected;
		}
	}
}


int main()
{
   int Sig=0;
	//œçÃæ
	int key;
	WINDOW *menubar,*messagebar;
	init_curses();
	while(1)
  {
	Sig=0;
	erase();
	refresh();
	bkgd(COLOR_PAIR(8));
	menubar=subwin(stdscr,1,80,0,0);
	messagebar=subwin(stdscr,1,79,23,1);
	draw_menubar(menubar);
	move(2,1);
	printw("Press F2 or F3 to open the menus. ");
	printw("ESC quits.");



	//ÈË

	set_up();
	valid=0;//³õÊŒÈË²»¶¯
	Score=0;
	refresh();
    WINDOW *About1=newwin(4,30,LINES/2-3, COLS/2-15);
				wbkgd(About1,COLOR_PAIR(10));
				box(About1,'|','-');
				wmove(About1,1,1);	
				wattron(About1,COLOR_PAIR(11)|A_BOLD);				
				wprintw(About1,"author:ecnu cs");
				wattroff(About1,COLOR_PAIR(11)|A_BOLD);
   WINDOW *About2=newwin(6,30,LINES/2-3,15);
				wbkgd(About2,COLOR_PAIR(10));
				box(About2,'|','-');
				wmove(About2,1,1);	
				wattron(About2,COLOR_PAIR(11)|A_BOLD);				
					
				wprintw(About2,"use direction key"); 
				wmove(About2,2,1);
				wprintw(About2,"to control the R ,");
				wmove(About2,3,1);
				wprintw(About2,"avoiding to touch M, ");
				wmove(About2,4,1);
				wprintw(About2,"chasing characters");
				wattroff(About2,COLOR_PAIR(11)|A_BOLD);

	while((key=getch())!='Q')
	{
		int selected_item;
		WINDOW **menu_items;
		werase(messagebar);
		wrefresh(messagebar);
		if(count==0||Score<0)//ÓÎÏ·œáÊø£¬ÏÔÊŸµÃ·Ö
		{
			break;
		}
		switch(key)
		{
		case KEY_F(2): //ÏÔÊŸ²Ëµ¥
			menu_items=draw_menu(0);
			selected_item=scroll_menu(menu_items,3,0);
			delete_menu(menu_items,4);
			if(selected_item==0)//Start a Game  ×¢Òâ²Ëµ¥ÏîµÄ±àºÅ
			{
	           set_ticker(1000/TICKS_PER_SEC);
			}
			if(selected_item==1)//Settings
			{
                
			}
			if(selected_item==2)//Quit
			{
				Sig=1;
				break;
			}
			touchwin(stdscr);
			refresh();
			break;

		case KEY_F(3):     //ÏÔÊŸ²Ëµ¥
			menu_items=draw_menu(20);
			selected_item=scroll_menu(menu_items,2,20);
			delete_menu(menu_items,3);
			if(selected_item==1)
			{
				
				touchwin(About1);
				wrefresh(About1);
				getch();
				
			}
			if(selected_item==0)
			{
				touchwin(About2);
				wrefresh(About2);
				getch();
			}
			touchwin(stdscr);
			refresh();
			break;

		case KEY_UP:
			the_person.y_dir=-1;
			if(valid==1)
			{
				the_person.y_ttm1--;//ÏòÉÏŒÓËÙ
				the_person.y_ttg1--;
				if(the_person.y_ttm1==0)
				{
					the_person.y_ttm1=1;
					the_person.y_ttg1=1;
				}
			}
			else
			{
				the_person.y_ttm2=0;//ÆäËû·œÏòËÙ¶ÈÉèÎª0 
				the_person.x_ttm1=0;
				the_person.x_ttm2=0;
				the_person.y_ttm1=Y_TTM;//ÏòÉÏ·œÏòÉèÎª³õÊŒËÙ¶È;
				the_person.y_ttg1=Y_TTM;				
				valid=1;
			}
			break;
		case KEY_DOWN:
			the_person.y_dir=1;
			if(valid==2)
			{
				the_person.y_ttm2--;//ÏòÏÂŒÓËÙ
				the_person.y_ttg2--;
				if(the_person.y_ttm2==0)
				{
					the_person.y_ttm2=1;
					the_person.y_ttg2=1;
				}
			}
			else
			{
				the_person.y_ttm1=0;//ÆäËû·œÏòËÙ¶ÈÉèÎª0 
				the_person.x_ttm1=0;
				the_person.x_ttm2=0;
				the_person.y_ttm2=Y_TTM;//ÏòÏÂ·œÏòÉèÎª³õÊŒËÙ¶È;
				the_person.y_ttg2=Y_TTM;
				valid=2;
			}
			break;
		case KEY_LEFT:
			the_person.x_dir=-1;
			if(valid==3)
			{
				the_person.x_ttm1--;//Ïò×óŒÓËÙ
				the_person.x_ttg1--;
				if(the_person.x_ttm1==0)
				{
					the_person.x_ttm1=1;
					the_person.x_ttg1=1;
				}
			}
			else
			{
				the_person.y_ttm1=0;//ÆäËû·œÏòËÙ¶ÈÉèÎª0 
				the_person.y_ttm2=0;
				the_person.x_ttm2=0;
				the_person.x_ttm1=X_TTM;//Ïò×ó·œÏòÉèÎª³õÊŒËÙ¶È;
				the_person.x_ttg1=X_TTM;
				valid=3;
			}
			break;
		case KEY_RIGHT:
			the_person.x_dir=1;
			if(valid==4)
			{
				the_person.x_ttm2--;//ÏòÓÒŒÓËÙ
				the_person.x_ttg2--;
				if(the_person.x_ttm2==0)
				{
					the_person.x_ttm2=1;
					the_person.x_ttg2=1;
				}
			}
			else
			{
				the_person.y_ttm1=0;//ÆäËû·œÏòËÙ¶ÈÉèÎª0 
				the_person.y_ttm2=0;
				the_person.x_ttm1=0;
				the_person.x_ttm2=X_TTM;//ÏòÓÒ·œÏòÉèÎª³õÊŒËÙ¶È;
				the_person.x_ttg2=X_TTM;
				valid=4;
			}
			break;
		}
		if(Sig==1)break;
	}

	set_ticker(0);//Í£Ö¹ÓÎÏ·
	//ÇåÆÁ£¬²¢ÏÔÊŸµÃ·Ö
	
	erase();
	refresh();
	attron(COLOR_PAIR(10)|A_BOLD);				
	mvprintw(5,20,"score for this time: %d",Score);
	attroff(COLOR_PAIR(10)|A_BOLD);
	refresh();
	getch();
	if(getch()==ESCAPE)
	{
	   break;
	}
  }
	delwin(menubar);
	   delwin(messagebar);
	   endwin();
}




int set_ticker(int n_msecs)
{
	struct itimerval new_timeset;
	long n_sec,n_usecs;

	n_sec=n_msecs/1000;
	n_usecs=(n_msecs%1000)*1000;

	new_timeset.it_interval.tv_sec=n_sec;
	new_timeset.it_interval.tv_usec=n_usecs;

	new_timeset.it_value.tv_sec=n_sec;
	new_timeset.it_value.tv_usec=n_usecs;

	return setitimer(ITIMER_REAL,&new_timeset,NULL);
}

void set_up()
{
	void Move(int);

	int i;
	memset(the_ball,0,sizeof(the_ball));
	creat_ball_ttg=1;
	count=TOTAL;
	srand(time(NULL));
	//start_color();
	for(i=1;i<=6;i++)
		init_pair(i,BallColor[i-1],COLOR_WHITE);

	for(i=0;i<5;i++)
	{
		dev[i].y_pos=Y_INIT+5*(i+1);
		dev[i].x_pos=X_INIT+5*(i+1);
		dev[i].y_ttg=dev[i].y_ttm=Y_TTM0;
		dev[i].x_ttg=dev[i].x_ttm=X_TTM0;
		dev[i].y_dir=2;
		dev[i].x_dir=2;
		dev[i].symbol=DEVIL_SYMBOL;
	}


	the_person.y_pos=Y_INIT;
	the_person.x_pos=X_INIT;
	the_person.y_ttg1=the_person.y_ttm1=0;
	the_person.x_ttg1=the_person.x_ttm1=0;
	the_person.y_ttg2=the_person.y_ttm2=0;
	the_person.x_ttg2=the_person.x_ttm2=0;
	the_person.y_dir=1;
	the_person.x_dir=1;
	the_person.symbol=PERSON_SYMBOL;


	initscr();
	noecho();
	//crmode();
	cbreak();//œûÖ¹ÐÐ»º³å£¬Ö±œÓŽ«µÝËùÓÐÊäÈë
	keypad(stdscr,TRUE);

	signal(SIGINT,SIG_IGN);

	attron(COLOR_PAIR(7)|A_BOLD);				
	mvaddch(the_person.y_pos,the_person.x_pos,the_person.symbol);
	attroff(COLOR_PAIR(7)|A_BOLD);
	refresh();

	signal(SIGALRM,Move);
	
}

int bounce_or_lose(struct person *bp)//µ±ÈËÅöµœ±ßœçÊ±µÄŽŠÀí
{
	int return_val=0;
	if(bp->y_pos==TOP_ROW)
	{
		bp->y_dir=1;

		the_person.y_ttm1=0;//ÆäËû·œÏòËÙ¶ÈÉèÎª0 
		the_person.x_ttm1=0;
		the_person.x_ttm2=0;
		the_person.y_ttm2=Y_TTM;//ÏòÏÂ·œÏòÉèÎª³õÊŒËÙ¶È;
		the_person.y_ttg2=Y_TTM;
		valid=2;

		return_val=1;
	}
	else if(bp->y_pos==BOT_ROW)
	{
		bp->y_dir=-1;

		the_person.y_ttm2=0;//ÆäËû·œÏòËÙ¶ÈÉèÎª0 
		the_person.x_ttm1=0;
		the_person.x_ttm2=0;
		the_person.y_ttm1=Y_TTM;//ÏòÉÏ·œÏòÉèÎª³õÊŒËÙ¶È;
		the_person.y_ttg1=Y_TTM;				
		valid=1;

		return_val=1;
	}

	if(bp->x_pos==LEFT_EDGE)
	{
		bp->x_dir=1;

		the_person.y_ttm1=0;//ÆäËû·œÏòËÙ¶ÈÉèÎª0 
		the_person.y_ttm2=0;
		the_person.x_ttm1=0;
		the_person.x_ttm2=X_TTM;//ÏòÓÒ·œÏòÉèÎª³õÊŒËÙ¶È;
		the_person.x_ttg2=X_TTM;
		valid=4;

		return_val=1;
	}
	else if(bp->x_pos==RIGHT_EDGE)
	{
		bp->x_dir=-1;

		the_person.y_ttm1=0;//ÆäËû·œÏòËÙ¶ÈÉèÎª0 
		the_person.y_ttm2=0;
		the_person.x_ttm2=0;
		the_person.x_ttm1=X_TTM;//Ïò×ó·œÏòÉèÎª³õÊŒËÙ¶È;
		the_person.x_ttg1=X_TTM;
		valid=3;

		return_val=1;
	}

	return return_val;
}







