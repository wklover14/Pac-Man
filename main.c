#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<conio.h>


/*DEFINITIONS DES STRUCTURES*/
struct Points
{
	int x;
	int y;
};
typedef struct Points Point;

struct Fantomes 
{
	int x;
	int y;
	Point d;
};
typedef struct Fantomes Fantome;

struct Gains
{
	int x;
	int y;
	int etat;
};
typedef struct Gains Gain;

struct Xfantome
{
	int x;
	int y;
	Point a;
	Point b;
	Point d;
};
typedef struct Xfantome xfantome;

struct Payers
{
	char nom[15];
	int code;
	int scoremax;
};
typedef struct Payers Player;
/* le fichier des joueurs est pac_players.s*/
/*Variables globales */

int matrice[60][150]={0};
Point pacman;
Point dirige;

/*FONCTION GLOBALE*/

void gotoxy(int lign,int col)
{
    COORD myCOORD;
    myCOORD.X=col;
    myCOORD.Y=lign;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),myCOORD);
}

Point Orientation()/* genere une direction aleatoire */
{
	int n;
	Point pos;
	n=1+rand()%4;
		if(n==1) {pos.x=-1; pos.y=0;}
		if(n==2) {pos.x=0; pos.y=-1;}
		if(n==3) {pos.x=1; pos.y=0;}
		if(n==4) {pos.x=0; pos.y=1;}
	

	return pos;
}

int libre(int x,int y)/*cette fonction retourne 1 si l'emplacement x,y de la console est libre */
{
	if(matrice[x][y]!=1)
		return(1);
	else
		return(0);
}

/*  GESTION DU CADRE ET MR PACMAN '-' */
void Mr_Pac(int x, int y)
{
	gotoxy(x,y);
	printf("%c",2);
	gotoxy(x,y-1); printf("%c",219); gotoxy(x,y+1); printf("%c",219); /* on essaye d'encadre le petit pacman*/ 
	/*gotoxy(x-1,y-1); for (i=1;i<=3;i++) printf("%c",219);*/
}

int libre_pac(int x,int y)
{
	if(libre(x,y))
		if(libre(x,y-1)&&libre(x,y+1))
				return 1;
		else
			return 0;
	else
		return 0;
}

void Delate_pac(int x, int y)
{
	gotoxy(x,y);
	printf(" ");
	gotoxy(x,y-1); printf(" "); gotoxy(x,y+1); printf(" "); /* on essaye d'encadre le petit pacman*/
	/*gotoxy(x-1,y-1); for (i=1;i<=3;i++) printf(" ");*/	
}

Point direction() /*cette fonction attend la saisie au clavier et  retourne la direction correspondante*/
{
 int c,n=1;
 Point pos;
 pos.x=0; pos.y=0;
 c=getch();
 if(c=='d'||c=='D'||c==77) { pos.x=0;  pos.y=1; n=2;}
 if(c=='q'||c=='Q'||c==75) { pos.x=0; pos.y=-1; n=2; }
 if(c=='s'||c=='S'|| c==80) { pos.x=1;  pos.y=0; n=2; }
 if(c=='z'||c=='Z'|| c==72) { pos.x=-1;  pos.y=0; n=4; }
 if(n==1){ pos.x=0;  pos.y=0;} 
 return pos;
}

void mouv_pac_continue()
{
	if(libre_pac(pacman.x+dirige.x,pacman.y+dirige.y))/*on verifie si la destination est valide et on affiche pacman*/
	{
		Delate_pac(pacman.x,pacman.y);
		pacman.x+=dirige.x;
		pacman.y+=dirige.y;
		Mr_Pac(pacman.x,pacman.y);
		gotoxy(37,2);
	}
}

void cadre()
{
	int i;
	gotoxy(1,2);/*premire ligne est 1*/
	for(i=2;i<121;i++)/*premiere colonne est 2 et la derniere est 120*/
		{ printf("%c",219); matrice[1][i]=1;}/* la modification de la matrice signifie que ce point est occupe*/
	gotoxy(2,2);
	for ( i = 1; i < 35; ++i)/*derniere ligne est 35 et on trace une ligne verticale*/
	{
		printf("%c\n",219); matrice[2+i-1][2]=1;
		gotoxy(i+2,2);
	}
	/*gotoxy(i,3);*/ gotoxy(35,3);
	for(i=2;i<120;i++)
		{printf("%c",219); matrice[35][3+i-2]=1;}/* ! */
	gotoxy(2,120);
	for ( i = 1; i < 35; i++)
		{	
			printf("%c\n",219); matrice[2+i-1][120]=1;
			gotoxy(i+2,120);
		}

	/*gotoxy(35,2); printf("%c",4);*/
	gotoxy(5,10); for(i=1;i<=20;i++) { printf("%c",219); matrice[5][10+i-1]=1; matrice[4][10+i-1]=0; }/*les trois barres horizontales du dessus sont les trois suivantes*/
	gotoxy(5,120-10-20); for(i=1;i<=20;i++) {printf("%c",219); matrice[5][120-10-20+i-1]=1;}
	gotoxy(5,42); for(i=1;i<=35;i++)  { printf("%c",219); matrice[5][42+i-1]=1;}

	gotoxy(35-4,10); for(i=1;i<=20;i++) { printf("%c",219); matrice[35-4][10+i-1]=1;}/*les trois barres horizontales du dessous sont les trois suivantes*/
	gotoxy(35-4,120-10-20); for(i=1;i<=20;i++) {printf("%c",219); matrice[35-4][90+i-1]=1;}
	gotoxy(35-4,42); for(i=1;i<=35;i++) { printf("%c",219); matrice[35-4][42+i-1]=1;}

	gotoxy(6,10); for(i=1;i<=5;i++)  {printf("%c",219); matrice[6+i-1][10]=1; gotoxy(i+6,10); }/*les barres verticales extremes */
	gotoxy(6,120-11); for(i=1;i<=5;i++)  {printf("%c",219); matrice[6+i-1][120-11]=1; gotoxy(i+6,120-11);} 

	gotoxy(35-4,10); for(i=1;i<=5;i++)  {printf("%c",219); matrice[31-i][10]=1; gotoxy(35-4-i,10);}/*les barres verticales extremes*/ 
	gotoxy(35-4,120-11); for(i=1;i<=5;i++)  {printf("%c",219); matrice[31-i][120-11]=1; gotoxy(35-4-i,120-11);}
	
	gotoxy(15,10);  for(i=1;i<=8;i++)  {printf("%c",219); matrice[15+i-1][10]=1; gotoxy(15+i,10);}/*les barres verticales du milieu*/
	gotoxy(15,120-11);  for(i=1;i<=8;i++)  {printf("%c",219); matrice[15+i-1][120-11]=1; gotoxy(15+i,120-11);}

	gotoxy(15,42); for(i=1;i<=8;i++) {printf("%c",219); matrice[15][42+i-1]=1;}/* ls barres du horizontale du cetnre*/ 
	gotoxy(15,69); for(i=1;i<=8;i++) {printf("%c",219); matrice[15][69+i-1]=1;}

	gotoxy(10,42); for(i=1;i<=35;i++) {printf("%c",219); matrice[10][42+i-1]=1; }/*barres horizontales centre */
	gotoxy(27,42); for(i=1;i<=35;i++) {printf("%c",219); matrice[27][42+i-1]=1;}

	gotoxy(16,42); for(i=1;i<=3;i++) { printf("%c",219); matrice[16+i-1][42]=1; gotoxy(i+16,42); } /*barres verticales du centre*/
	gotoxy(16,76); for(i=1;i<=3;i++) { printf("%c",219); matrice[16+i-1][76]=1; gotoxy(i+16,76); } 

	gotoxy(9,25); for(i=1;i<=19;i++) { printf("%c",219); matrice[9+i-1][25]=1; gotoxy(i+9,25); }/*le cadre du centre*/
	gotoxy(9,92); for(i=1;i<=19;i++) { printf("%c",219); matrice[9+i-1][92]=1; gotoxy(i+9,92); }

	gotoxy(23,42); for(i=1;i<=8;i++) {printf("%c",219); matrice[23][42+i-1]=1;} 
	gotoxy(23,69); for(i=1;i<=8;i++) {printf("%c",219 ); matrice[23][69+i-1]=1;}

    gotoxy(18,55); for(i=1;i<=10;i++) {printf("%c",219 ); matrice[18][55+i-1]=1;}
    gotoxy(19,55); for(i=1;i<=2;i++) { printf("%c",219); matrice[19+i-1][55]=1; gotoxy(i+19,55); }
    gotoxy(19,64); for(i=1;i<=2;i++) { printf("%c",219); matrice[19+i-1][64]=1; gotoxy(i+19,64); }

    gotoxy(5,35); for(i=1;i<=3;i++) { printf("%c",219); matrice[5+i-1][35]=1; gotoxy(i+5,35); }
    gotoxy(28,35); for(i=1;i<=3;i++) { printf("%c",219); matrice[28+i-1][35]=1; gotoxy(i+28,35); }
    gotoxy(5,83);  for(i=1;i<=3;i++) { printf("%c",219); matrice[5+i-1][83]=1; gotoxy(i+5,83); }
    gotoxy(28,83);  for(i=1;i<=3;i++) { printf("%c",219); matrice[28+i-1][83]=1; gotoxy(i+28,83); }

    gotoxy(20,29);  for(i=1;i<=12;i++) {printf("%c",219); matrice[20][29+i-1]=1;}
    gotoxy(20,77);   for(i=1;i<=12;i++) {printf("%c",219); matrice[20][77+i-1]=1;}


    gotoxy(26,60); printf("%c",219); matrice[26][60]=1;
	matrice[26][10]=0; matrice[26][120-11]=0;/* cette initialisition est faite par a cause d'un constat graphique a l'ecran*/

	gotoxy(32,1);
}



 /* GESTION DES FANTOMES */

int libre_fantome(int x,int y)/*cette fonction retourne 1 si l'emplacement x,y de la console est libre pour une structure fantome */
{
	if(matrice[x][y]!=1)
		if(matrice[x+1][y]!=1)
			return(1);
		else
			return(0);
	else
		return 0;
}

Fantome New_fantome()/*initialiser les coordonnées de casper de maniere aleatoire*/
{
 	Point p;
 	Fantome casper;
 	do
 	{
 		casper.x=(rand()%30)+2;
 		casper.y=(rand()%118)+2;
 	}while(libre_fantome(casper.x,casper.y)==0);
    p=Orientation(rand()%4+1);
    casper.d.x=p.x; casper.d.y=p.y; 

 	return(casper);
}

void Mr_fantome(Fantome casper) /*faire apparaitre casper*/
{
	gotoxy(casper.x,casper.y); printf("%c",224);
	gotoxy(1+casper.x,casper.y); printf("%c",197);
	gotoxy(37,2);
}

void Delate_fantome(Fantome casper)
{
	gotoxy(casper.x,casper.y); printf(" ");
	gotoxy(1+casper.x,casper.y); printf(" ");
}

void mouv_fantome(Fantome *casper)
{
	Point p;

	Delate_fantome(*casper); /*on efface d'abord l'ancien casper*/
	while(!libre_fantome( casper->x + casper->d.x , casper->y + casper->d.y ))/*On genere une nouvelle une position jusqu'a la bonne */
	{
		p=Orientation();
		casper->d.x = p.x; casper->d.y = p.y;
	}
	casper->x += casper->d.x ;
	casper->y += casper->d.y ; /* on reinitialise les coordonnes du fantome*/
		if ( casper->x <= 0 || casper->x >= 34)
			{
				casper->x = 30;/*repositionement au centre du jeu */
				casper->y = 106;	
			}
		if( casper->y <=1 || casper->y >= 119)/* s'il est hors du cadre ou sur les bordures*/
			{
				casper->x = 20;/*repositionement au centre du jeu */
				casper->y = 60;	
			}
	Mr_fantome(*casper);/*on affiche le nouveau f*/	
}

/*FONCTION POUR LES BONUS */

Gain New_bonus()
{
	Gain b;
	do
		{
			b.x=1+rand()%33;
			b.y=2+rand()%117;
		} while (!libre(b.x,b.y));
		b.etat=1;
	return b;	
}
void init_gain(Gain b[50])
{
	int i;
	for ( i = 0; i < 50; i++)
	{
	    gotoxy(b[i].x,b[i].y);
	    printf("%c",4);
	}
}

void affiche_bonus(Gain b[50])
{
	int i;
	for (i = 0; i < 50; i++)
	{
		if(b[i].etat==1)
		  {
			gotoxy(b[i].x,b[i].y);
			printf("%c",4);
		  }
	} gotoxy(37,2);
}

void bonus_mange(Gain b[20],int *score)
{
	int i;
	for ( i = 0; i < 50; i++)
	{
		if( b[i].x == pacman.x && b[i].y == pacman.y && b[i].etat==1)/*les coordonnes du centre de pacman sont egales a celles d'un bonus*/
		{ 
			b[i].etat=0; 
			*score+=1;
		}
		if( b[i].x == pacman.x && ( b[i].y == pacman.y + 1 || b[i].y == pacman.y - 1) && b[i].etat==1  )
		{ 
				b[i].etat=0; 
				*score+=1;
		}

	}
}

/* fonction pour les fantomes x qui se deplacent sur une ligne bien defini*/

void xinit_fantome(xfantome f[5])
{
	f[1].a.x=25; f[1].a.y=4; f[1].b.x=25; f[1].b.y=22; f[1].d.x=0; f[1].d.y=1; 
	f[1].x=25; f[1].y=4;
	f[2].a.x=25; f[2].a.y=94; f[2].b.x=25; f[2].b.y=118; f[2].d.x=0; f[2].d.y=1; 
	f[2].x=25; f[2].y=94;

	f[3].a.x=12; f[3].a.y=94; f[3].b.x=12; f[3].b.y=118; f[3].d.x=0; f[3].d.y=1; 
	f[3].x=12; f[3].y=118;
	f[4].a.x=12; f[4].a.y=4; f[4].b.x=12; f[4].b.y=23; f[4].d.x=0; f[4].d.y=1; 
	f[4].x=12; f[4].y=23;

	f[0].a.x=17; f[0].a.y=59; f[0].b.x=11; f[0].b.y=59; f[0].d.x=-1; f[0].d.y=0; 
	f[0].x=17; f[0].y=59;	 
}

void xaffiche_fantome(xfantome f[5])
{
	int i;
	for (i = 0; i < 5; i++)
	{
		if(libre(f[i].x+f[i].d.x,f[i].y+f[i].d.y))/*on ne n'affiche que si l'emplacement est libre*/
		{
			f[i].x+=f[i].d.x; f[i].y+=f[i].d.y;/*on initialise les coordonees*/
			gotoxy(f[i].x,f[i].y);
			printf("%c",219);/*on affiche le nouveau xfantome*/
		}
	} gotoxy(37,2);
}

void xmouv_fantome(xfantome f[5])
{
	int i;
	for (i = 0; i < 5; i++)
	{
		gotoxy(f[i].x,f[i].y);  printf(" ");/*on efface l'ancien xfantome */
		if (f[i].a.y==f[i].b.y)/* le deplacement est vertical*/
		{ /* on change direction lorsque nous soes dans des points extremes ie a ou b*/
			if (f[i].x==f[i].a.x)
			{
				f[i].d.x=-1; f[i].d.y=0; 
			}
			if(f[i].x==f[i].b.x)
			{
				f[i].d.x=1; f[i].d.y=0;	
			}
		}
		if (f[i].a.x==f[i].b.x)/* si le deplacement est horizontale*/
		{
			if (f[i].y <= f[i].a.y)
			{
				f[i].d.x=0; f[i].d.y=1; 
			}

			if( f[i].y >= f[i].b.y)
			{
				f[i].d.x=0; f[i].d.y=-1; 	
			}
		}
	}
}

/*fonction mort du packman*/

int tamponement(int x,int y)/*cette verifie si pacman est au point x,y */
{
	if(pacman.x!=x)
		return 0;
	else
		if(y!=pacman.y && y!=1+pacman.y && y!=-1+pacman.y)
			return 0;

	return 1;
}

int mort_pacman(Fantome c[10],xfantome f[5])
{
	int i;
	for (i = 0; i < 5; i++)
	{
		if (tamponement(c[i].x,c[i].y) || tamponement(f[i].x,f[i].y) || tamponement(1+c[i].x,c[i].y))
			return 1;
	}
	for ( i = 5; i < 10; i++)
	{
		if (tamponement(c[i].x,c[i].y) || tamponement(1+c[i].x,c[i].y))
			return 1;	
	}
	return 0 ;
}

/*fonction qui lance et gere le deroulement du jeu*/

int gameplay()
{
	int i,j=1,score=0;
	int dead=0;
	Fantome casper[10];
	Gain b[120];
	xfantome f[5];

	srand(time(NULL));
	pacman.x=4; pacman.y=6;
	Mr_Pac(pacman.x,pacman.y);
	cadre();


	for (i = 0; i < 10; i++)/* creation des fantomes*/
		{ casper[i]=New_fantome(); }
	xinit_fantome(f);/* initialisation des xfantomes*/

	for (i = 0; i < 50; i++) b[i]=New_bonus(); /* creation et affichage des bonus*/
		init_gain(b);
	
	dirige=direction();/*on attend qu'il definisse la direction pour lancer le mouvement*/

	while( !mort_pacman(casper,f) && dead==0 )
	{
		while( (!kbhit() || j==1) && dead==0 )
		{
			/*cadre();*/
			if(j==0) Sleep(100); /*fait en sorte qu'il n'y ait pas un delai lorsque le joueur vient de se deplacer */
			for ( i = 0; i < 10; i++)
			{
				mouv_fantome(&casper[i]);
				Mr_fantome(casper[i]);  
			}
			xmouv_fantome(f);
			xaffiche_fantome(f);/*affichage des x fantomes*/
			dead=mort_pacman(casper,f);
			if(dead==0) 
			{	mouv_pac_continue();
				bonus_mange(b,&score); /*on verifie si un bonus est mange lors du deplacement continue*/
				gotoxy(6,125); printf("score = %d ",score);
				affiche_bonus(b);
			}
			j=0; 
		}
		
		if(dead==0)
		{	
			dirige=direction();/*on retient la nouvelle direction*/
			mouv_pac_continue();
			bonus_mange(b,&score);
			gotoxy(6,125); printf("score = %d ",score);
			dead=(mort_pacman(casper,f));
			affiche_bonus(b);
			gotoxy(6,125); printf("score = %d ",score);
		}
		/*/affiche_bonus(b);/*on reaffiche les bonus en particulier ceux qui sont encore la*/
		j=1;
		if(score >= 50) dead=1;
	}	
    gotoxy(37,2);
    /*if(dead==1) puts("Game over Man");
    else
    	if(score==50) puts("Tu as gagne frere, hooneur a la patrie");*/
    return score;
}
 
 void cls_zone()
{
	int i,j;
	for(i=9;i<=30;i++)
		for ( j=20; j<120;j++)
		{
			gotoxy(i,j); printf(" ");
		}
}

void affichage_joueurs()
{
	FILE *f=NULL;
	Player p;
	int i=0;
	f=fopen("Pac_player.ess","r");
	if (f!=NULL)
	{
		while(!feof(f))
		{
			fread(&p,sizeof(p),1,f);
			if (!feof(f))
			{
				gotoxy(15+i,22); printf("%s",p.nom);
				gotoxy(15+i,20); printf("%d",p.code);
				i++;
			}
		}
		fclose(f);
		gotoxy(16+i,20);
	} else puts("erreur d'ouverture");
}

int menu_pacman()
{
	int i,c,a,b,x;
	system("cls");
	gotoxy(0,100);
	for(i=0;i<=3;i++)
	{
		gotoxy(0+i,100); 
		printf("%c",219);
	}
	for (i =100; i > 16 ; i--)
	{
		gotoxy(3,i-1); printf("%c",220);
	}
	for ( i = 0; i < 40; i++)
	{
		gotoxy(4+i,16); printf("%c",219);
	}
	gotoxy(2,17); printf(" P  A  C  _  M  A  N   G e n e s i s ");

	gotoxy(9,20);   printf(" Nouveau Jeu ");
	gotoxy(10,20);  printf("*------------*");
	gotoxy(12,20);  printf(" Ajouter un joueur ");
	gotoxy(13,20);  printf("*-----------------* ");
	gotoxy(15,20);  printf(" Meilleur score ");
	gotoxy(16,20);  printf("*---------------*");
	gotoxy(18,20);  printf(" Aide ");
	gotoxy(19,20);  printf("*------*");
	gotoxy(21,20); 	printf(" Quitter le jeu ");
	gotoxy(22,20); 	printf("*--------------*  ");
	a=9; b=0;
	gotoxy(a,42); printf("%c%c%c%c",60,60,60,7);
	c=getch(); i=1;/* i est l'option 1 donc jouer*/
	while(c!=13)
	{
		if(c=='s'||c=='S'||c==80 ) 
			if(a==21)
				{  x=9-21; i=1; b=1; } 
			else
				{ x=3; i+=1; b=1; }
		if(c=='z'||c=='Z'|| c==72)
			if(a==9)
				{ x=-9+21; i=4; b=1;}
			else
				{ x=-3; i-=1; b=1;}
		if(b==1)
		{
			gotoxy(a,42); printf("    ");
			a+=x; b=0;			
			gotoxy(a,42); printf("%c%c%c%c",60,60,60,7);
		}
		c=getch();
	}
	gotoxy(40,30); printf("developpe par WK & EEM"); 
	return i;
}
void Ajout_joueur()
{
	FILE* f=fopen("Pac_player.ess","a+");
	Player p,t;
	int c=0;
	if (f!=NULL)
	{
		gotoxy(13,20); printf("Entrer votre nom: "); gets(p.nom);
		p.scoremax=0;
		while(!feof(f))/*On compte le nombre de joueur du jeu*/
		{
			fread(&t,sizeof(t),1,f);
			c++;
		}
		p.code=c;
		fwrite(&p,sizeof(p),1,f);/*On enregistre e joueur dans le fichier*/
		fclose(f);
		gotoxy(15,20); printf("%s ajouter",p.nom);
	} else { gotoxy(13,20); printf("erreur d'ouverture"); }
}
Player selection_joueur()
{
	int i,a;
	Player p;
	FILE* f=fopen("Pac_player.ess","r");

	i=0;
	if (f==NULL)
	{
		printf("erreur d'ouverture");
	}else
	{
		do
		{
			cls_zone();
			gotoxy(9,20);   printf(" Nouveau Jeu ");
			gotoxy(10,20);  printf("*------------*");
			gotoxy(12,20);  printf(" Selectionner le joueur ");
			gotoxy(13,20);  printf("*-----------------------*");
			affichage_joueurs();
			printf("votre choix : ");
			scanf("%d",&a);
			while(!feof(f) && i==0)
			{
				fread(&p,sizeof(p),1,f);
				if( p.code==a && !feof(f))
					i=1;
			} 
		}while(i==0);
		fclose(f);
		return(p);
	}
}
void Nouveau_joueur()
{
	cls_zone();
	gotoxy(9,20);   printf(" Nouveau Joueur ");
	gotoxy(10,20);  printf("*------------*");
	Ajout_joueur();		
}

void aide()
{
	cls_zone();
	gotoxy(9,20);   printf("  AIDE ");
	gotoxy(10,20);  printf("*------*");
	gotoxy(13,20);  printf(" Haut= fleche haut/z, bas= fleche bas/s, gauche=fleche gauche/q, droite=fleche droite/d ");
	gotoxy(40,30);
}

void Meilleur_score()
{
	FILE* f=fopen("Pac_player.ess","r");
	Player p;
	int max=0,code=0;

	if (f!=NULL)
	{
		cls_zone();
		gotoxy(9,20);   printf(" Meilleur score ");
		gotoxy(10,20);  printf("*------------*");
		while (!feof(f))/*on parcours le fichier a la recherhce du max*/
		{
			fread(&p,sizeof(p),1,f);
			if(p.scoremax > max) { max=p.scoremax; code=p.code; }
		}
		fseek(f,0,SEEK_SET);
		fread(&p,(code)*sizeof(p),1,f);
		fclose(f);
		gotoxy(12,20);
		printf(" The GOAT is %s : %d ",p.nom,p.scoremax);		
	}
	else
	{
		gotoxy(44,50); printf("Erreur d'ouverture");
	}
}

void init_score(Player p)/* cette fonction change le score max de joueur au mm code que celui entre en parametre*/
{
	int a=0,i;
	FILE* f=fopen("Pac_player.ess","r+");
	Player d;
	if (f!=NULL)
	{
		while(!feof(f) && a==0)
		{
			fread(&d,sizeof(d),1,f);
			if (p.code==d.code)
				{ a=1; break;}
		} 
		d.scoremax=p.scoremax;
		fseek(f,-1*sizeof(d),SEEK_CUR);
		/*rewind(f);*/
		fwrite(&d,sizeof(d),1,f);  
		fseek(f,0,SEEK_END);
		fclose(f);
	} 
	else
	{
		gotoxy(30,30); printf("erreur d'enregistrement du score");
	} 
}

int main(int argc, char const *argv[])
{
	int a,score;
	Player p;
	system("mode con: cols=150 lines=50");
	do
	{
		a=menu_pacman();/*Mettre tout ca dans un do while*/
		switch(a)
		{
			case 1:
					p=selection_joueur();
					system("cls");
					gotoxy(2,125); printf("Joueur : %s",p.nom);
					gotoxy(4,125); printf("score_max=%d",p.scoremax);
					score=gameplay();/* Lancement du jeu */
					gotoxy(8,125);
					if(score==50) printf(" Niveau termine bravo");
					else printf(" Tu as perdu man ");

					if( score > p.scoremax ) { p.scoremax=score; init_score(p); gotoxy(10,125); printf(" la condition est ok");}  /*on verifie si le score est superieur au max et on remplace si besoin*/
					break;/* on doit faire un menu qui boucle pour demander s'il veut sortir ou recommencer*/
			case 2:
					Nouveau_joueur();
					/* cherher un moyen d'appeler la fonction gameplay directement ici*/
					cls_zone();
					//gotoxy(9,20);   printf(" D�sol� vous ne pouvez ajouter de joueur dans cette version ");
					break;
			case 3:
					Meilleur_score();
					break;
			case 4:
					aide();
					break;

		} 
		gotoxy(40,20);
		system("pause");
		cls_zone();
	}while(a!=5);
	gotoxy(9,20);   printf("  AUREVOIR ");
	gotoxy(10,20);  printf("*----------*");
	gotoxy(40,20);
	return 0;
}
