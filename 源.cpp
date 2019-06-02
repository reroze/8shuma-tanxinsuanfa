#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
局部最优贪心算法
*/
struct point {
	int caozuo_last;
	int juzhen[3][3];
	int option[4];
	int zuobiaor;
	int zuobiaol;
	struct point*form;
	struct point*next;
	struct point*fu;
	int g_x;
	int h_x;
};

int bushu = 0;
typedef struct point pin;
pin *front0=NULL, *pi;
pin *open0 = NULL;
pin *close0 = NULL;
pin*buffer0 = NULL;
pin *open, *close, *buffer;
int format[3][3] = { {2,8,3},{1,6,4},{7,0,5} };
int mubiao[3][3] = { {1,2,3},{8,0,4},{7,6,5} };
void create(pin*pi, int i);
void fuzhi_juzhen(pin*p, int now[3][3]);
void enqueue_open(pin*p);
void enqueue_buffer(pin*p);
void dequeue_open();
void enqueue_close(pin*p);
void dequeue_close();
void chushihua(pin*p);
void swap(int buffle[3][3], pin*pi, pin*p, int i);
int panduan(pin*p,int i);
void p_option(pin*p);
int bijiao(int now[3][3], int mubiao[3][3]);
int count = 0;
void print(int now[3][3]);
void Wx(pin*p);
void Gx(pin*p);
void buffer_to_open(pin*p);
void main()
{
	
	front0 = (pin*)malloc(sizeof(pin));
	pin *p;
	fuzhi_juzhen(front0, format);
	chushihua(front0);
	front0->caozuo_last = -5;
	p_option(front0);
	pi = front0;
	front0->fu = NULL;
	enqueue_close(front0);
	while (1)
	{
		for (int i = 0; i < 4; i++)
		{
			if (panduan(close0, i) == 1)
			{
				create(close0, i);
			}
			
		}
		buffer_to_open(buffer0);
		open0->fu = close0;
		count++;
		if (bijiao(open0->juzhen, mubiao) == 1)
			break;
		//dequeue_close();
		close0 = open0;
		buffer0 = NULL;
		open0 = NULL;
		/*if (close0 == NULL)
		{
			close0 = open0;
			open0 = NULL;
		}*/
	}
	printf("%d", count);
	pin*ye = open0;
	printf("\n");
	print(open->juzhen);
	printf("\n");
	ye = ye->fu;
	int length = 0;
	while (ye)
	{
		length++;
		printf("\n");
		print(ye->juzhen);
		printf("\n");
		ye = ye->fu;
	}
	printf("\n$%d$", length);
	system("pause");
}

void Wx(pin*p)
{
	int c = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (p->juzhen[i][j] != mubiao[i][j])
				c++;
		}
	}
	p->h_x = c;

}

void Gx(pin*p)
{
	int c = -1;
	pin*p2 = p;
	while (p2)
	{
		p2 = p2->fu;
		c++;
	}
}

int bijiao(int now[3][3], int mubiao[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (now[i][j] != mubiao[i][j])
				return 0;
		}
	}
	return 1;
}

void dequeue_open()
{
	open0 = open0->next;
}

void dequeue_close()
{
	close0 = close0->next;
}

void p_option(pin*p)
{
	int r = p->zuobiaor;
	int l = p->zuobiaol;
	for (int i = 0; i < 4; i++)
	{
		if (i+p->caozuo_last!=1 && i+p->caozuo_last!=5)
		{
			switch (i)
			{
			case 0:
				if (r - 1 >= 0)
					p->option[0] = 1;
				break;
			case 1:
				if (r + 1 < 3)
					p->option[1] = 1;
				break;
			case 2:
				if (l - 1 >= 0)
					p->option[2] = 1;
				break;
			case 3:
				if (l + 1 < 3)
					p->option[3] = 1;
				break;
			}
		}
	}
}

int panduan(pin*p, int i)
{
	if (p->option[i] == 1)
		return 1;
	return 0;
}

void fuzhi_juzhen(pin*p, int now[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			p->juzhen[i][j] = now[i][j];
			if (now[i][j] == 0)
			{
				p->zuobiaor = i;
				p->zuobiaol = j;
			}
		}
	}
}

void chushihua(pin*p)
{
	for (int i = 0; i < 4; i++)
		p->option[i] = 0;
	p->next = NULL;
	p->fu = NULL;
}

void swap(int buffle[3][3],pin *pi,pin*p, int i)
{
	int term = 0;
	p->caozuo_last = i;
	int r = pi->zuobiaor;
	int l = pi->zuobiaol;
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 3; y++)
		{
			buffle[x][y] = pi->juzhen[x][y];
		}
	}
	switch (i)
	{
	case 0:
		term = buffle[r - 1][l];
		buffle[r - 1][l] = 0;
		buffle[r][l] = term;
		break;
	case 1:
		term = buffle[r + 1][l];
		buffle[r + 1][l] = 0;
		buffle[r][l] = term;
		break;
	case 2:
		term = buffle[r][l-1];
		buffle[r][l-1] = 0;
		buffle[r][l] = term;
		break;
	case 3:
		term = buffle[r][l+1];
		buffle[r][l+1] = 0;
		buffle[r][l] = term;
		break;
	}
}

void enqueue_open(pin*p)
{
	//int buffle[3][3] = { 0 };
	if (open0 == NULL)
	{
		open0 = p;
		open = open0;
	}
	else {
		open->next = p;
		open = open->next;
	}
	//swap(buffle, zi, i);

}

void enqueue_buffer(pin*p)
{
	if (buffer0 == NULL)
	{
		buffer0 = p;
		buffer = buffer0;
	}
	else {
		buffer->next = p;
		buffer = buffer->next;
	}
}

void enqueue_close(pin*p)
{
	//int buffle[3][3] = { 0 };
	if (close0 == NULL)
	{
		close0 = p;
		close = close0;
	}
	else {
		close->next = p;
		close = close->next;
	}
	//swap(buffle, zi, i);

}

void create(pin*pi, int i)
{
	int buffle[3][3] = { 0 };
	pin *p = (pin*)malloc(sizeof(pin));
	p->fu = pi;
	chushihua(p);
	swap(buffle, pi,p, i);
	fuzhi_juzhen(p, buffle);
	p_option(p);
	Wx(p);
	Gx(p);
	enqueue_buffer(p);

}

void print(int now[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			printf("%2d", now[i][j]);
		}
		printf("\n");
	}
}

void buffer_to_open(pin*p)//p为buffer0
{
	int fx = p->g_x+p->h_x;
	pin *p3 = p;
	while (p3)
	{
		if (fx > p3->g_x + p3->h_x)
			fx = p3->g_x + p3->h_x;
		p3 = p3->next;
	}
	p3 = p;
	while (p3)
	{
		if (fx == p3->g_x + p3->h_x)
		{
			enqueue_open(p3);
			break;
		}
		p3 = p3->next;
	}
}