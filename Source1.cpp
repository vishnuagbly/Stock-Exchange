#include<string>
#include"graphics.h"
#include<windows.h>
#include<fstream>
#include<stdio.h>
#include<time.h>
#include<iostream>
#pragma comment(lib, "winmm.lib")
using namespace std;
int w1, nply = 0, x2 = 0, y2 = 0, max;
int sum[7] = { 0,0,0,0,0,0, -70 }, bpr[6] = { 20,25,40,55,75,80 };
char *names[] = { "", "your" , "vishnu'", "varun'", "player 4'", "player 5'", "player 6'" }, pl_names[7][20];
string a[10] = { "workhardt","HDFC","TATA","ONGC","Reliance","Infosys","currency","debenture","share suspend","pig" };
FILE *f;
class card
{
	int name;
	int num;
public:
	card()
	{
		name = 0;
		num = 1;
	}
	bool select = false;
	void asval(int i, int n)
	{
		name = i;
		num = n;
	}
	int gname() { return name; }
	void cval(int n) { num = n; }
	int gval() { return num; }
	void output()
	{
		cout << select << endl;
		cout << "name : " << a[name] << endl;
		cout << "value : " << num << "\n\n\n";
	}
	bool check(card &c)
	{
		if (name == c.gname() && num == c.gval())return true;
		else return false;
	}
};
class player
{
	int currency, share[6];
public:
	player()
	{
		currency = 600000;
		for (int i = 0; i < 6; i++)
		{
			share[i] = 0;
		}
	}
	void ishare(int s, int n)
	{
		share[n] = s;
	}
	int gshar(int n)
	{
		return share[n];
	}
	void ibalance(int n) { currency = n; }
	int gbalance() { return currency; }
};
player p;
player cmp[7];
card b[7];
card cd[107];
card scd[61];
card pcd[11];
int tshare[6];
void *cards_image[2];
void *logo[10];
void empty_map();
void enter_name(int a)
{
	char ch = 0;
	for (int i = 0; names[a][i] != '\0';)
	{
		pl_names[a][i++] = NULL;
	}
	for (int i = -1; ch != 13;)
	{
		ch = getch();
		if (((ch >= 'a' && ch <= 'z') || ch == ' ' || (ch >= 'A' && ch <= 'Z')) && i < 20)
			pl_names[a][++i] = ch;
		else if (ch == 8)
		{
			pl_names[a][i] = ' ';
			i--;
			bar(10, 55, 100, 75);
		}
		else if (ch == 13)pl_names[a][++i] = 39;
		outtextxy(10, 60, pl_names[a]);
	}
}
int cursor(int x, int y)
{
	char ch, c[40];
	int sum = 0;
	while (1)
	{
	a:
		ch = getch();
		if (ch >= '0' && ch <= '9')
		{
			sum = sum * 10 + (ch - '0');
			sprintf_s(c, "%d", sum);
			outtextxy(x, y, c);
		}
		else if (ch == 8)
		{
			sum = sum / 10;
			setcolor(15);
			bar(x, y, x + 200, y + 15);
			setcolor(0);
			sprintf_s(c, "%d", sum);
			outtextxy(x, y, c);
		}
		else if (ch == 13)
		{
			sum = (sum / 1000) * 1000;
			setcolor(15);
			bar(x, y, x + 200, y + 15);
			setcolor(0);
			sprintf_s(c, "%d", sum);
			outtextxy(x, y, c);
			delay(500);
			return sum;
		}
		else if (ch == 'm' || ch == 'M')
		{
			sum = max;
			setcolor(15);
			bar(x, y, x + 200, y + 15);
			setcolor(0);
			sprintf_s(c, "%d", sum);
			outtextxy(x, y, c);
		}
		else goto a;
	}
}
int input()
{
	char ch;
	int n;
	while (1)
	{
		ch = getch();
		if (ch > 48 && ch <= 57) { n = ch - 48; return n; }
	}
}
void screen()
{
	int j = -1;
	cleardevice();
	setcolor(0);
	line(200, 0, 200, 600);
	line(400, 0, 400, 600);
	line(0, 200, 400, 200);
	line(0, 400, 400, 400);
	for (int i = 0; i < 3; i++)
	{
		putimage(50, i * 200 + 50, logo[++j], COPY_PUT);
		putimage(250, i * 200 + 50, logo[++j], COPY_PUT);
	}
}
int mouse(int x2, int y2)
{
	char ch;
	while (1)
	{
		ch = getch();
		switch (ch)
		{
		case KEY_UP: {
			if (y2 != 0)y2--;
			screen();
			rectangle(x2 * 200 + 20, y2 * 200 + 20, x2 * 200 + 180, y2 * 200 + 180);
			break;
		}
		case KEY_DOWN: {
			if (y2 != 2)y2++;
			screen();
			rectangle(x2 * 200 + 20, y2 * 200 + 20, x2 * 200 + 180, y2 * 200 + 180);
			break;
		}
		case KEY_LEFT: {
			if (x2 != 0)x2--;
			screen();
			rectangle(x2 * 200 + 20, y2 * 200 + 20, x2 * 200 + 180, y2 * 200 + 180);
			break;
		}
		case KEY_RIGHT: {
			if (x2 != 1)x2++;
			screen();
			rectangle(x2 * 200 + 20, y2 * 200 + 20, x2 * 200 + 180, y2 * 200 + 180);
			break;
		}
		case 13: {return x2 + y2 * 2; }
		case 8: return -1;
		}
	}
}
bool sell(bool db = false)
{
	int n, w, shares, price;
	char pr[30], ch;
	w = initwindow(1000, 600, "sell");
	setbkcolor(15);
	screen();
	n = mouse(0, 0);
	if (n == -1)goto b;
a:
	if (p.gshar(n) > 0)
	{
		screen();
		outtextxy(410, 20, "how many shares you want to sell");
		max = p.gshar(n);
		shares = cursor(410, 40);
		if (shares > p.gshar(n))
		{
			screen();
			outtextxy(410, 20, "you do not have enogh shares to sell");
			getch();
			goto a;
		}
		else if (shares <= p.gshar(n)) {
			screen();
			outtextxy(410, 20, "you will get money : ");
			if (db == false)price = shares * b[n].gval();
			else price = shares * bpr[n];
			sprintf_s(pr, "%d", price);
			outtextxy(textwidth("you will get money : ") + 410, 20, pr);
			outtextxy(410, 40, "to cancel press backspace");
			ch = getch();
			if (ch == 8)goto b;
			mciSendString(TEXT("stop mp3"), NULL, 0, NULL);
			mciSendString(TEXT("close mp3"), NULL, 0, NULL);
			mciSendString(TEXT("open \"win.mp3\" type mpegvideo alias mp3"), NULL, 0, NULL);
			mciSendString(TEXT("play mp3 wait"), NULL, 0, NULL);
			p.ibalance(price + p.gbalance());
			p.ishare(p.gshar(n) - shares, n);
			tshare[n] -= shares;
			mciSendString(TEXT("stop mp3"), NULL, 0, NULL);
			mciSendString(TEXT("close mp3"), NULL, 0, NULL);
			mciSendString(TEXT("open \"all.mp3\" type mpegvideo alias mp3"), NULL, 0, NULL);
			mciSendString(TEXT("play mp3 repeat"), NULL, 0, NULL);
			closegraph(w);
			setcurrentwindow(w1);
			return true;
		}
	}
b:
	closegraph(w);
	setcurrentwindow(w1);
	return false;
}
bool enter()
{
	int w, j = -1, n, price, shares;
	char ch, pr[50];
	w = initwindow(1000, 600, "enter");
	setbkcolor(15);
	screen();
	setcolor(GREEN);
	rectangle(x2 * 200 + 20, y2 * 200 + 20, x2 * 200 + 180, y2 * 200 + 180);
c:
	n = mouse(x2, y2);
	if (n == -1)goto d;
	if (tshare[n] < 200000 && b[n].gval() > 0)
	{
	b:
		max = p.gbalance() / b[n].gval();
		if (max + tshare[n] > 200000)max = 200000 - tshare[n];
		outtextxy(410, 20, "enter number of shares: ");
		shares = cursor(410, 40);
		if (shares + tshare[n] <= 200000)
		{
			screen();
			price = b[n].gval() * shares;
			if (p.gbalance() >= price) {
				outtextxy(410, 20, "it will cost: ");
				sprintf_s(pr, "%d", price);
				outtextxy(textwidth("it will cost: ") + 430, 20, pr);
				outtextxy(410, 40, "press enter to buy");
				outtextxy(410, 60, "press backspace to go back");
			e:
				ch = getch();
				if (ch == 13) {
					mciSendString(TEXT("stop mp3"), NULL, 0, NULL);
					mciSendString(TEXT("close mp3"), NULL, 0, NULL);
					mciSendString(TEXT("open \"win.mp3\" type mpegvideo alias mp3"), NULL, 0, NULL);
					mciSendString(TEXT("play mp3 wait"), NULL, 0, NULL);
					p.ishare(p.gshar(n) + shares, n);
					tshare[n] += shares;
					p.ibalance(p.gbalance() - price);
					mciSendString(TEXT("stop mp3"), NULL, 0, NULL);
					mciSendString(TEXT("close mp3"), NULL, 0, NULL);
					mciSendString(TEXT("open \"all.mp3\" type mpegvideo alias mp3"), NULL, 0, NULL);
					mciSendString(TEXT("play mp3 repeat"), NULL, 0, NULL);
					closegraph(w);
					setcurrentwindow(w1);
					return true;
				}
				else if (ch == 8) goto d;
				else goto e;
			}
			else
			{
				screen();
				outtextxy(410, 20, "you don,t have enough money");
				goto b;
			}
		}
		else {
			screen();
			outtextxy(410, 20, "there is not enough shares left");
			goto b;
		}
	}
	else
	{
		screen();
		outtextxy(410, 20, "you cannot put shares on this company");
		goto c;
	}
	getch();
d:
	closegraph(w);
	setcurrentwindow(w1);
	return false;
}
void define_companys()
{
	b[0].asval(0, 20);
	b[1].asval(1, 25);
	b[2].asval(2, 40);
	b[3].asval(3, 55);
	b[4].asval(4, 75);
	b[5].asval(5, 80);
}
void totaling(bool normal = true)
{
	int j = 0, l = 0;
	int big[6], bigd[6];
	char bal[20];
	for (int i = 0; i < 6; i++)sum[i] = 0;
	cout << "done\n";
	cmp[1] = p;
	for (int i = 0; i < 6; i++)
	{
		big[i] = 60, bigd[i] = 60;
		for (int k = 1; k <= 6; k++)
		{
			if (cmp[k].gshar(i) >= 100000)
			{
				for (int j = 0; j < nply * 10; j++)
				{
					if (scd[j].gname() == i)
					{
						cout << i << " " << j << " " <<  k << " " << scd[j].gval() << " " << big[i] << " " << scd[big[i]].gval() << "\n";
						if (scd[j].gval() <= scd[big[i]].gval())big[i] = j;
					}
				}
			}
			else if (cmp[k].gshar(i) >= 50000)
			{
				for (int j = (k - 1) * 10; j < k*10; j++)
				{
					if (scd[j].gname() == i)
					{
						cout << "came here " << names[k] << " " << j << " = j = " << scd[j].gval() << " bigd[i], i =" << bigd[i] << " " << i << " = " << scd[bigd[i]].gval();
						if (scd[j].gval() <= scd[bigd[i]].gval())bigd[i] = j;
						cout << "gone from here";
					}
				}
			}
		}
		for (int j = 0; j < nply * 10; j++)
		{
			if (scd[j].gname() == i && j != big[i])
			{
				sum[i] += scd[j].gval();
				cout << a[scd[j].gname()] << ": " << scd[j].gval() << " " << &sum[i] << "\n";
			}
			else if (j == big[i] || j == bigd[i])
			{
				cout << a[scd[j].gname()] << ": " << scd[j].gval() << " " << &sum[i] << "  not counted\n";
			}
		}
		if (b[i].gval() + sum[i] <= 0)sum[i] = 0;
		if (normal == true)
		{
			b[i].cval(sum[i] + b[i].gval());
			cout << a[i] << ": " << sum[i] << "\n\n\n\n";
		}
	}
	for (int i = 0; i < 10; i++)
	{
		if (pcd[i].gname() == 6)j += pcd[i].gval();
	}
	if (j != 0 && normal == true)
	{
		cout << j;
		empty_map();
		outtextxy(10, 40, "due to currency card your balance is ");
		p.ibalance(p.gbalance() + (p.gbalance()*j / 100000) * 1000);
		sprintf_s(bal, "%d", p.gbalance());
		outtextxy(10, 60, bal);
		getch();
		for (int i = 2; i <= nply; i++)
		{
			l = 0;
			for (int k = (i - 1) * 10; k < i * 10; k++)
			{
				if (scd[k].gname() == 6)l += scd[k].gval();
			}
			cmp[i].ibalance(cmp[i].gbalance() + cmp[i].gbalance()*(l / 100000) * 1000);
		}
	}
	cout << " - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n";
}
void dcard(card c, int row, int column);
void init_images()
{
	int card_size, size;
	readimagefile("cards.jpg", 0, 0, 400, 250);
	card_size = imagesize(0, 0, 200, 250);
	cards_image[0] = malloc(card_size);
	cards_image[1] = malloc(card_size);
	getimage(0, 0, 200, 250, cards_image[0]);
	getimage(200, 0, 400, 250, cards_image[1]);
	readimagefile("workhardt.jpg", 0, 0, 100, 50);
	readimagefile("infosys.jpg", 100, 0, 200, 50);
	size = imagesize(0, 0, 100, 50);
	logo[0] = malloc(size);
	logo[5] = malloc(size);
	getimage(0, 0, 100, 50, logo[0]);
	getimage(100, 0, 200, 50, logo[5]);
	readimagefile("reliance.jpg", 0, 0, 100, 75);
	size = imagesize(0, 0, 100, 75);
	logo[4] = malloc(size);
	getimage(0, 0, 100, 75, logo[4]);
	putimage(500, 500, logo[4], COPY_PUT);
	readimagefile("tata.jpg", 101, 0, 201, 100);
	readimagefile("ONGC.jpg", 202, 0, 302, 100);
	readimagefile("HDFC.jpg", 0, 0, 100, 100);
	size = imagesize(0, 0, 100, 100);
	for (int i = 0; i < 3; i++)
	{
		logo[i + 1] = malloc(size);
		getimage(i * 100 + i, 0, i * 100 + 100 + i, 100, logo[i + 1]);
	}
	readimagefile("currency.jpg", 0, 0, 100, 100);
	logo[6] = malloc(size);
	getimage(0, 0, 100, 100, logo[6]);
	readimagefile("spc.jpg", 0, 0, 600, 250);
	size = imagesize(0, 0, 200, 250);
	for (int i = 7; i < 10; i++)
	{
		logo[i] = malloc(size);
		getimage((i - 7) * 200, 0, (i - 7) * 200 + 200, 250, logo[i]);
	}
	cleardevice();
}
void select_card()
{
	int s, s1;
	srand(time(NULL));
	for (int i = 0; i < nply * 10; i++)
	{
	a:
		s = rand() % 106 + 1;
		scd[i] = cd[s];
		if (cd[s].select == true)goto a;
		else cd[s].select = true;
	}
	for (int i = 0; i < nply * 10; i++)
	{
		for (int j = 0; j < nply * 10; j++)
		{
			if (scd[i].check(scd[j]) == true) {
				if (i != j) cout << i << " " << j << endl;
			}
		}
	}
	for (int i = 0; i < 10; i++)pcd[i] = scd[i];
	for (int i = 0; i < 107; i++)cd[i].select = false;
}
void companytable()
{
	int w3 = initwindow(400, 600, "company_table"), n;
	char ch;
	setbkcolor(15);
	cleardevice();
	setcolor(0);
	char c[6][6];
	for (int i = 0; i < 6; i++) { sprintf_s(c[i], "%d", b[i].gval()); }
	setcolor(0);
	line(400, 0, 400, 600);
	line(200, 0, 200, 600);
	for (int i = 1; i < 3; i++)line(0, i * 200, 400, i * 200);
	int j = -1;
	settextjustify(1, 1);
	for (int i = 0; i < 3; i++)
	{
		putimage(10, i * 200 + 50, logo[++j], COPY_PUT);
		outtextxy(150, i * 200 + 100, c[j]);
		putimage(210, i * 200 + 50, logo[++j], COPY_PUT);
		outtextxy(350, i * 200 + 100, c[j]);
	}
	settextjustify(0, 1);
	getch();
	closegraph(w3);
	setcurrentwindow(w1);
}
void map(int pl = 1)
{
	cleardevice();
	setcolor(RED);
	settextjustify(1, 1);
	settextstyle(10, HORIZ_DIR, 3);
	outtextxy(300, 20, "STOCK EXCHANGE");
	settextstyle(8, HORIZ_DIR, 1);
	settextjustify(0, 1);
	setcolor(0);
	int j = -1;
	char s[6][20];
	setcolor(0);
	if(pl == 1)for (int i = 0; i < 6; i++)sprintf_s(s[i], "%d", p.gshar(i));
	else for (int i = 0; i < 6; i++)sprintf_s(s[i], "%d", cmp[pl].gshar(i));
	line(600, 0, 600, 700);
	line(1000, 0, 1000, 700);
	line(600, 466, 1400, 466);
	line(600, 233, 1400, 233);
	settextjustify(0, 1);
	for (int i = 0; i < 3; i++)
	{
		putimage(610, i * 233 + 50, logo[++j], COPY_PUT);
		setcolor(RED);
		if (pl == 1)
		{
			if (p.gshar(j) >= 100000)outtextxy(750, i * 233 + 160, "Chairman");
			else if (p.gshar(j) >= 50000)outtextxy(750, i * 233 + 160, "Director");
		}
		else
		{
			if (cmp[pl].gshar(j) >= 100000)outtextxy(750, i * 233 + 160, "Chairman");
			else if (cmp[pl].gshar(j) >= 50000)outtextxy(750, i * 233 + 160, "Director");
		}
		setcolor(0);
		outtextxy(750, i * 233 + 100, s[j]);
		putimage(1010, i * 233 + 50, logo[++j], COPY_PUT);
		setcolor(RED);
		if (pl == 1)
		{
			if (p.gshar(j) >= 100000)outtextxy(1150, i * 233 + 160, "Chairman");
			else if (p.gshar(j) >= 50000)outtextxy(1150, i * 233 + 160, "Director");
		}
		else
		{
			if (cmp[pl].gshar(j) >= 100000)outtextxy(1150, i * 233 + 160, "Chairman");
			else if (cmp[pl].gshar(j) >= 50000)outtextxy(1150, i * 233 + 160, "Director");
		}
		setcolor(0);
		outtextxy(1150, i * 233 + 100, s[j]);
	}
	settextjustify(0, 1);
}
void empty_map()
{
	cleardevice();
	setcolor(RED);
	settextjustify(1, 1);
	settextstyle(10, HORIZ_DIR, 3);
	outtextxy(300, 20, "STOCK EXCHANGE");
	settextstyle(8, HORIZ_DIR, 1);
	settextjustify(0, 1);
	setcolor(0);
	map();
}
int show_cards()
{
	int k = 0, special_card;
	char sch = NULL;
	int i = 0, j = 0, s;
	int w2 = initwindow(1000, 500, "cards");
	setbkcolor(WHITE);
	cleardevice();
	setcolor(0);
	line(200, 0, 200, 500);
	line(400, 0, 400, 500);
	line(600, 0, 600, 500);
	line(800, 0, 800, 500);
	line(0, 250, 1000, 250);
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			dcard(pcd[k], j, i);
			k++;
		}
	}
	while (1)
	{
		cout << "came input: ";
		sch = getch();
		s = sch;
		cout << s;
		cout << ": ";
		setfillstyle(SOLID_FILL, GREEN);
		if (sch == 72)
		{
			dcard(pcd[i * 2 + j], j, i);
			if (j != 0)j--;
			setcolor(GREEN);
			bar(i * 200 + 75, j * 250 + 100, i * 200 + 125, j * 250 + 150);
		}
		else if (sch == 80)
		{
			dcard(pcd[i * 2 + j], j, i);
			if (j != 1)j++;
			setcolor(GREEN);
			bar(i * 200 + 75, j * 250 + 100, i * 200 + 125, j * 250 + 150);
		}
		else if (sch == 75)
		{
			dcard(pcd[i * 2 + j], j, i);
			if (i != 0)i--;
			setcolor(GREEN);
			bar(i * 200 + 75, j * 250 + 100, i * 200 + 125, j * 250 + 150);

		}
		else if (sch == 77)
		{
			dcard(pcd[i * 2 + j], j, i);
			if (i != 4)i++;
			setcolor(GREEN);
			bar(i * 200 + 75, j * 250 + 100, i * 200 + 125, j * 250 + 150);

		}
		else if (sch == 13)
		{
			if (pcd[i * 2 + j].gname() == 7)special_card = i * 2 + j;
			else if (pcd[i * 2 + j].gname() == 9)special_card = i * 2 + j;
			else special_card = 10;
			break;
		}
		else if (sch == 'h')
		{
			special_card = 11;
			break;
		}
		else if (sch == 8 || sch == 'c')
		{
			special_card = 10;
			break;
		}
	}
	b:
	setcolor(0);
	closegraph(w2);
	setcurrentwindow(w1);
	return special_card;
}
void define_cards()
{
	f = fopen("c1.dat", "rb");
	fread(&cd, sizeof(card), 107, f);
	for (int i = 0; i < 107; i++)
	{
		cout << a[cd[i].gname()] << ":\t" << cd[i].gval() << "\n";
	}
	fclose(f);
}
void dcard(card c, int row, int column)
{
	setcolor(0);
	string s = a[c.gname()];
	int val = c.gval();
	int lnum = c.gname();
	char value[4];
	settextjustify(1, 1);
	if (lnum > 6 && lnum < 10)
	{
		putimage(column * 200, row * 250, logo[lnum], COPY_PUT);
	}
	else if (lnum == 10);
	else
	{
		if (val < 0)sprintf_s(value, "%d", val);
		else sprintf_s(value, "+%d", val);
		if (val < 0)putimage(column * 200, row * 250, cards_image[1], COPY_PUT);
		else putimage(column * 200, row * 250, cards_image[0], COPY_PUT);
		putimage(column * 200 + 50, row * 250 + 100, logo[lnum], COPY_PUT);
		outtextxy(column * 200 + 100, row * 250 + 225, value);
	}
}
void arrange(int arr[6], int aar[6], int n)
{
	int i, j, ar[6];
	for (i = 0; i < 6; i++)
	{
		arr[i] = INT_MIN;
		ar[i] = 0;
	}
	cout << n << " player's cards :-\n";
	for (i = 0; i < 6; i++)
	{
		for (j = (n-1) * 10; j < n * 10; j++) {
			if (scd[j].gname() == i)
			{
				ar[i] += scd[j].gval();
				cout << a[scd[j].gname()] << " " << scd[j].gval() << " " << ar[i] << endl;
			}
		}
		cout << ar[i] << " " << b[i].gval() << "\n\n";
	}
	for (i = 0; i < 6; i++)
	{
		ar[i] = ar[i] * 100 / b[i].gval();
		cout << i << ": " << ar[i] << endl;
	}
	for (i = 0; i < 6; i++)
	{
		for (j = 0; j < 6; j++)
		{
			if (ar[j] >= arr[i])
			{
				if (i == 0)
				{
					arr[i] = ar[j];
					aar[i] = j;
				}
				else
				{
					if (ar[j] < arr[i - 1])
					{
						arr[i] = ar[j];
						aar[i] = j;
					}
				}
			}
		}
	}
}
void AI(bool enter = true)
{
	static int count = -1;
	int arr[6], aar[6], dcount;
	cout << "enterd in ai\n";
	if (enter == true)
	{
		count++;
		dcount = count;
		cout << dcount << " going from ai" << endl;
		totaling(false);
		cout << "came back to ai\n";
		for (int i = 0; i < 6; i++)cout << sum[i] * 100 / b[i].gval() << " " << i << endl;
		int big[6] = { 6,6,6,6,6,6 }, max_shares;
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 6; j++)
			{
				if (b[j].gval() != 0)
				{
					if ((sum[j] * 100) / b[j].gval() >= (sum[big[i]] * 100) / b[big[i]].gval())
					{
						if (i == 0)
							big[i] = j;
						else
						{
							if ((sum[j] * 100) / b[j].gval() < (sum[big[i - 1]] * 100) / b[big[i - 1]].gval())
								big[i] = j;
						}
					}
				}
			}
			cout << i << ": " << big[i] << " " << sum[big[i]] << endl;
		}
	a:
		cout << dcount << " " << sum[big[dcount]] << endl;
		if (sum[big[dcount]] >= 0)
		{
			max_shares = ((cmp[2].gbalance() / b[big[dcount]].gval()) / 1000) * 1000;
			if (max_shares + tshare[big[dcount]] >= 200000)max_shares = 200000 - tshare[big[dcount]];
			if (max_shares == 0)
			{
				dcount++;
				goto a;
			}
			cmp[2].ishare(cmp[2].gshar(big[dcount]) + max_shares, big[dcount]);
			cmp[2].ibalance(cmp[2].gbalance() - max_shares * b[big[dcount]].gval());
			tshare[big[dcount]] += max_shares;
		}
		for (int i = 3; i <= nply; i++)
		{
			dcount = count;
			cout << dcount << " going from ai" << endl;
			arrange(arr, aar, i);
			cout << "came back to ai\n";
			for (int j = 0; j < 6; j++)cout << aar[j] << " " << arr[j] << endl;
		b:
			cout << "dcount: " << dcount << " " << aar[dcount] << " " << arr[dcount] << endl;
			if (arr[dcount] >= 0)
			{
				max_shares = ((cmp[i].gbalance() / b[aar[dcount]].gval()) / 1000) * 1000;
				if (max_shares + tshare[aar[dcount]] >= 200000)max_shares = 200000 - tshare[aar[dcount]];
				if (max_shares == 0)
				{
					dcount++;
					goto b;
				}
				cout << i << " player max shares: " << max_shares << " " << aar[dcount] << " balance: " << cmp[i].gbalance() << endl;
				cmp[i].ishare(cmp[i].gshar(aar[dcount]) + max_shares, aar[dcount]);
				cmp[i].ibalance(cmp[i].gbalance() - max_shares * b[aar[dcount]].gval());
				tshare[aar[dcount]] += max_shares;
				cout << i << " player balance: " << cmp[i].gbalance() << " " << aar[dcount] << " total shares: " << tshare[aar[dcount]] << endl;
			}
		}
	}
	else
	{
		for (int j = 2; j <= 6; j++)
		{
			for (int i = 0; i < 6; i++)
			{
				count = -1;
				cmp[j].ibalance(cmp[j].gbalance() + cmp[j].gshar(i)*b[i].gval());
				tshare[i] -= cmp[j].gshar(i);
				cmp[j].ishare(0, i);
			}
		}
	}
	cout << "getting lost from ai";
}
void hscores()
{
	cmp[1] = p;
	cout << cmp[1].gbalance() << endl;
	cmp[0].ibalance(0);
	int hscore[6] = { 0,0,0,0,0,0 }, i = 0, j = 0;
	for (i = 1; i <= nply; i++)
	{
		for (j = 0; j < 6; j++)
		{
			cout << i << ": " << cmp[i].gshar(j) << " * " << b[j].gval() << " + " << cmp[i].gbalance();
			cmp[i].ibalance(cmp[i].gshar(j) * b[j].gval() + cmp[i].gbalance());
			cout << " = " << cmp[i].gbalance() << "\n";
			cmp[i].ishare(0, j);
		}
		cout << "\n total budget = " << cmp[i].gbalance() << "\n\n\n";
	}
	for (i = 0; i <= 6; i++)cout << i << " " << cmp[i].gbalance() << endl;
	getch();
	for (i = 1; i <= nply; i++)
	{
		for (j = 1; j <= nply; j++)
		{
			if (i == 1 && cmp[j].gbalance() >= cmp[hscore[i - 1]].gbalance())
			{
				cout << i << " " << "came\n";
				hscore[i - 1] = j;
			}
			else if (i != 1 && cmp[j].gbalance() < cmp[hscore[i - 2]].gbalance() && cmp[j].gbalance() >= cmp[hscore[i - 1]].gbalance())
			{
				cout << i << " " << "came2\n";
				hscore[i - 1] = j;
			}
		}
	}
	for (i = 0; i < nply; i++)cout << names[hscore[i]] << ": " << cmp[hscore[i]].gbalance() << endl;
	getch();
}
void main()
{
	int pr = 0, n, ep[6], nlsmc = 0, barg, pl = 1;
	char ch = 0, price[13], bp[4];
	bool s, e, found = false;
	w1 = initwindow(1400, 700, "stock", -3, -3);
	cd[0].asval(10, 0);
	setbkcolor(15);
	init_images();
	define_cards();
	define_companys();
	cleardevice();
	empty_map();
	outtextxy(10, 40, "enter your name: ");
	enter_name(1);
	names[1] = pl_names[1];
	mciSendString(TEXT("open \"all.mp3\" type mpegvideo alias mp3"), NULL, 0, NULL);
	mciSendString(TEXT("play mp3 repeat"), NULL, 0, NULL);
	empty_map();
a:
	outtextxy(10, 40, "enter no. of players including you(2-6)");
	nply = input();
	if (nply > 6 || nply < 2)goto a;
	for (int i = 0; ; i++)
	{
		cout << i << endl;
		empty_map();
		sprintf_s(bp, "%d", (i + 1));
		select_card();
		nlsmc = 0;
		if (i > 0)
		{
		f:
			map();
			outtextxy(10, 60, "to see cards press (C)");
			outtextxy(10, 120, "to sell some of shares press (L)");
			outtextxy(10, 100, "to not sell press(P)");
			outtextxy(10, 80, "to see price of shares press (S)");
			outtextxy(10, 140, "to quit press (Q)");
			outtextxy(100, 400, "bargon period: ");
			outtextxy(textwidth("bargon period: ") + 100, 400, bp);
			outtextxy(100, 500, "your balance is : ");
			AI(false);
			bar(textwidth("bargon period: ") + 100, 400, textwidth("bargon period: ") + 300, 410);
			sprintf_s(price, "%d", p.gbalance());
			outtextxy(textwidth("your balance is : ") + 120, 500, price);
			ch = getch();
		re1:
			if (ch == 'c' || ch == 'C')show_cards();
			else if (ch == 'l' || ch == 'L')sell();
			else if (ch == 'P' || ch == 'p')goto g;
			else if (ch == 'S' || ch == 's')companytable();
			else if (ch == 'q' || ch == 'Q')goto end;
			else if (ch == KEY_LEFT)
			{
				cmp[1] = p;
				if (pl > 1)pl -= 1;
				map(pl);
				outtextxy(10, 60, names[pl]);
				outtextxy(10 + textwidth(names[pl]), 60, "s board");
				outtextxy(100, 500, "balance : ");
				sprintf_s(price, "%d", cmp[pl].gbalance());
				outtextxy(textwidth("your balance is : ") + 120, 500, price);
				ch = getch();
				if (ch == KEY_LEFT || ch == KEY_RIGHT)
				{
					goto re1;
				}
			}
			else if (ch == KEY_RIGHT)
			{
				if (pl < nply)pl += 1;
				map(pl);
				cmp[1] = p;
				outtextxy(10, 60, names[pl]);
				outtextxy(10 + textwidth(names[pl]), 60, "s board");
				outtextxy(100, 500, "balance : ");
				sprintf_s(price, "%d", cmp[pl].gbalance());
				outtextxy(textwidth("your balance is : ") + 120, 500, price);
				ch = getch();
				if (ch == KEY_LEFT || ch == KEY_RIGHT)
				{
					goto re1;
				}
			}
			else goto f;
			goto f;
		}
	g:
		map();
		barg = i + 1;
		for (int i = 0; i <3; i++) {
			if(i != 0 && barg %2 == 0)AI();
			else if (barg % 2 == 1)AI();
		b:
			found = false;
			outtextxy(10, 60, "to see cards press (C)");
			outtextxy(10, 80, "to see price of shares (S)");
			outtextxy(10, 140, "to enter shares press (E)");
			outtextxy(10, 120, "to sell some of shares press (L)");
			outtextxy(10, 100, "to pass this turn press(P)");
			outtextxy(10, 200, "to quit press(Q)");
			outtextxy(100, 400, "bargon period: ");
			outtextxy(textwidth("bargon period: ") + 100, 400, bp);
			sprintf_s(price, "%d", p.gbalance());
			cout << p.gbalance() << endl;
			cout << price;
			outtextxy(100, 500, "your balance is : ");
			outtextxy(textwidth("your balance is : ") + 110, 500, price);
			ch = getch();
		re:
			if (ch == 'C' || ch == 'c')
			{
				int special_card = show_cards();
				cout << special_card << endl;
				if (special_card == 11)
				{
					for (int i = 1; i <= nply; i++)
					{
						if (i != 2)
						{
							empty_map();
							outtextxy(10, 40, names[i]);
							outtextxy(textwidth(names[i]) + 10, 40, "s new name : ");
							enter_name(i);
							names[i] = pl_names[i];
						}
					}
					map();
					goto b;
				}
				if (pcd[special_card].gname() == 7)
				{
					if (sell(true) == true) { pcd[special_card] = cd[0]; map(); }
					else goto b;
				}
				else if (pcd[special_card].gname() == 9)
				{
					p.ibalance(p.gbalance() + 100000);
					pcd[special_card] = cd[0];
				}
				else goto b;
			}
			else if (ch == 'S' || ch == 's')
			{
				companytable();
				goto b;
			}
			else if (ch == 'e' || ch == 'E')
			{
				e = enter();
				map();
				if (e == false)goto b;
			}
			else if (ch == 'l' || ch == 'L')
			{
				s = sell();
				map();
				if (s == false)goto b;
			}
			else if (ch == 'p' || ch == 'P');
			else if (ch == 'q' || ch == 'Q')goto end;
			else if (ch == KEY_LEFT)
			{
				cmp[1] = p;
				if (pl > 1)pl -= 1;
				map(pl);
				outtextxy(10, 60, names[pl]);
				outtextxy(10 + textwidth(names[pl]), 60, "s board");
				outtextxy(100, 500, "balance : ");
				sprintf_s(price, "%d", cmp[pl].gbalance());
				outtextxy(textwidth("your balance is : ") + 120, 500, price);
				ch = getch();
				if (ch == KEY_LEFT || ch == KEY_RIGHT)
				{
					goto re;
				}
				else
				{
					map();
					goto b;
				}
			}
			else if (ch == KEY_RIGHT)
			{
				if (pl < nply)pl += 1;
				map(pl);
				cmp[1] = p;
				outtextxy(10, 60, names[pl]);
				outtextxy(10 + textwidth(names[pl]), 60, "s board");
				outtextxy(100, 500, "balance : ");
				sprintf_s(price, "%d", cmp[pl].gbalance());
				outtextxy(textwidth("your balance is : ") + 120, 500, price);
				ch = getch();
				if (ch == KEY_LEFT || ch == KEY_RIGHT)
				{
					goto re;
				}
				else
				{
					map();
					goto b;
				}
			}
			else goto b;
		}
	c:
		empty_map();
		for (int i = 0; i < 6; i++)ep[i] = b[i].gval();
		outtextxy(10, 60, "press any key to see results");
		outtextxy(100, 500, "your balance is : ");
		sprintf_s(price, "%d", p.gbalance());
		outtextxy(textwidth("your balance is : ") + 120, 500, price);
		getch();
		totaling();
		companytable();
		for (int i = 0; i < 10; i++)
		{
			if (pcd[i].gname() == 8)
			{
			sharesuspend:
				empty_map();
				outtextxy(10, 60, "to see price of shares press(S)");
				outtextxy(10, 80, "you have share suspend to us press(U)");
				outtextxy(10, 100, "else press (N)");
				ch = getch();
				if (ch == 'u' || ch == 'U')
				{
					screen();
					n = mouse(0, 0);
					b[n].cval(ep[n]);
					companytable();
				}
				if (ch == 's' || ch == 'S')
				{
					companytable();
					goto sharesuspend;
				}
			}
		}
	}
end:
	empty_map();
	outtextxy(100, 400, "bargon period: ");
	outtextxy(textwidth("bargon period: ") + 100, 400, bp);
	getch();
	hscores();
	closegraph();
	mciSendString(TEXT("stop mp3"), NULL, 0, NULL);
	mciSendString(TEXT("close mp3"), NULL, 0, NULL);
	for (int i = 0; i < 10; i++)
	{
		if (i < 2)
		{
			free(cards_image[i]);
		}
		free(logo[i]);
	}
	cout << "bye";

}