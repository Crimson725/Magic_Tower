/*version1
1������ 
2���زĵ���
���������IMAGE img
������ֵ��loadimage(&img,"·��")
ͼƬ��ʾ:putimage(int x,int y,&img)
��ͼ��ʹ�ö�ά����
3���������������ң�������
4���ؿ��Ż�*/
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>//����ege��
FILE* fp; //ȫ���ļ�ָ��
int map_order_now = 1, int map_order_pre = 0;//��ͼ���� ��ǰΪ1 ǰһ��ͼΪ0 ��ؿ���������
typedef struct Actor
{
	char name[20] = { 0 };//����
	int level = 1;//��ʼ�ȼ�
	int hp = 1000;//��ʼѪ��
	int Attack = 10;//��ʼ������
	int Defence = 10;///��ʼ������
	int money = 0;//��ʼ��Ǯ
	int exp = 0;//��ʼ����
	int x;//λ������x
	int y;//λ������y
	int Ykey = 1;//��Կ�� ��ʼΪ1
	int Rkey = 1;//��Կ�� ��ʼΪ1
	int Bkey = 1;//��Կ�� ��ʼΪ1
	PIMAGE img;//��ɫ����ͼƬ
}role,actor;//ȫ�ֽṹ�� ��ҽ�ɫ
typedef struct Object
{
	char nmae[20] = { 0 };
	int hp;//Ѫ��
	int exp;//����ֵ
	int Attack;//������
	int Defence;//������
	int money;//��Ǯ
	int x;//x����
	int y;//y����
	PIMAGE img;//����ͼƬ
}enemy,object,actors,background;
enemy GreenSlime, RedSlime, BlackSlime;
enemy BigBat, SmallBat, RedBat;
enemy Witch_1, Witch_2;
enemy Guard_1, Guard_2, Guard_3;
enemy BoneMan, BoneGuard, BoneWarrior;
enemy GBoss, MonsterKing, RBoss;
enemy Orc, OrcWarrior;
actors OldMan, SwordMan, Warrior,Witch_R,Witch_Y,WhiteWitch,RedMan;
object RKey, BKey, YKey, GKey, Sword, Shield, TreasureBox, WindOrient, GoldCoin, Level_Up, Cross, CrossEmblem, HP, BigHP, BlueDiamond, RedDiamond;
background Background, Blcok, Floor, Wall, YellowDoor, GreenDoor, RedDoor, BlueDoor, Upstairs, Downstairs, Shop, Stars;



int main()
{
	initgraph(800, 600);//�������� 800*600 ege�⺯��
	//PIMAGE xxx = newimage();

	//getimage(xxx, "/testResources/0_1.jpg");
	//putimage(0, 0, xxx);
	int map[13][13] =
	{
	   {1,1,1,1,1,1,1,1,1,1,1,1,1},
	   {1,10,0,12,34,31,34,0,0,0,0,0,1},
	   {1,2,2,2,2,2,2,2,2,2,2,0,1},
	   {1,6,0,32,4,0,2,6,12,6,2,0,1},
	   {1,12,32,16,2,0,2,6,12,6,2,0,1},
	   {1,2,4,2,2,0,2,2,2,30,2,0,1},
	   {1,12,37,0,2,0,4,33,34,35,2,0,1},
	   {1,17,0,14,2,0,2,2,2,2,2,0,1},
	   {1,2,4,2,2,0,0,0,0,0,0,0,1},
	   {1,0,37,0,2,2,3,2,2,2,4,2,1},
	   {1,6,7,12,2,13,0,0,2,12,36,14,1},
	   {1,6,8,12,2,0,11,0,2,12,12,12,1},
	   {1,1,1,1,1,1,1,1,1,1,1,1,1},
	};
	


	//system("pause");//stdlib.h
	//test:���Ӳ���
	getch();
	closegraph();//���ڹر� ege�⺯��
	return 0;
}