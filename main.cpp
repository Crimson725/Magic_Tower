/*
version2
1�������ƶ��Ż�
2���ؿ��л�
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h> //����ege��
#include <conio.h>
#include <string>

FILE* fp; //ȫ���ļ�ָ��
int map_order_now = 1;
int map_order_pre = 0; //��ͼ���� ��ǰΪ1 ǰһ��ͼΪ0 ��ؿ���������

int map[13][13] =
{
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 10, 0, 12, 34, 31, 34, 0, 0, 0, 0, 0, 1},
	{1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 1},
	{1, 6, 0, 32, 4, 0, 2, 6, 12, 6, 2, 0, 1},
	{1, 12, 32, 16, 2, 0, 2, 6, 12, 6, 2, 0, 1},
	{1, 2, 4, 2, 2, 0, 2, 2, 2, 30, 2, 0, 1},
	{1, 12, 37, 0, 2, 0, 4, 33, 34, 35, 2, 0, 1},
	{1, 17, 0, 14, 2, 0, 2, 2, 2, 2, 2, 0, 1},
	{1, 2, 4, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 37, 0, 2, 2, 3, 2, 2, 2, 4, 2, 1},
	{1, 6, 7, 12, 2, 13, 0, 0, 2, 12, 36, 14, 1},
	{1, 6, 8, 12, 2, 0, 11, 0, 2, 12, 12, 12, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
}; //��ʼ��ͼ ��ͼ1
typedef struct
{
	int Map[13][13];
} MAP;
MAP M[15]; //ʮ����ͼ����ʱ��

int map1[13][13];

typedef struct Actor
{
	char name[20] = "����"; //����; //����
	int level = 1;			  //��ʼ�ȼ�
	int hp = 1000;			  //��ʼѪ��
	int Attack = 30;		  //��ʼ������
	int Defence = 30;		  ///��ʼ������
	int money = 0;			  //��ʼ��Ǯ
	int exp = 0;			  //��ʼ����
	int x;					  //λ������x
	int y;					  //λ������y
	int Ykey = 1;			  //��Կ�� ��ʼΪ1
	int Rkey = 1;			  //��Կ�� ��ʼΪ1
	int Bkey = 1;			  //��Կ�� ��ʼΪ1
	PIMAGE img;				  //��ɫ����ͼƬ
} role, actor;				  //ȫ�ֽṹ�� ��ҽ�ɫ
typedef struct Object
{
	char name[20] = { 0 };
	int hp;		 //Ѫ��
	int exp;	 //����ֵ
	int Attack;	 //������
	int Defence; //������
	int money;	 //��Ǯ
	int x;		 //x����
	int y;		 //y����
	PIMAGE img;	 //����ͼƬ
} enemy, object, actors, background;
typedef struct PUSH
{
	PIMAGE img;
	//img_index;
} push;
enemy GreenSlime, RedSlime, BlackSlime; //���� ʷ��ķ��
enemy BigBat, SmallBat, RedBat;			//���� ������
enemy Witch_1, Witch_2;					//���� ��ʦ��
enemy Guard_1, Guard_2, Guard_3;		//���� ������
enemy BoneMan, BoneGuard, BoneWarrior;	//���� ������
enemy GBoss, MonsterKing, RBoss;		//���� Boss��
enemy Orc, OrcWarrior;
enemy StoneMan;																																	   //���� ������
actors OldMan, SwordMan, Warrior, Witch_R, Witch_Y, WhiteWitch, RedMan;																			   //���� ��ɫ��
object RKey, BKey, YKey, GKey, Sword, Shield, TreasureBox, WindOrient, GoldCoin, Level_Up, Cross, CrossEmblem, HP, BigHP, BlueDiamond, RedDiamond; //������
background Background, Block, Floor, Wall, YellowDoor, GreenDoor, RedDoor, BlueDoor, Upstairs, Downstairs, Shop, Stars;							   //��ͼ ����ģ����
role People;																																	   //����
push CrossEmblem_PUSH, Shop_PUSH[4], Versus, Warrior_PUSH[16], OldMan_PUSH[4], RedMan_PUSH[4], WindOrient_PUSH, End;							   //����������
//��ͼ�л����ĺ����������ƣ�

void changemap()
{
	memcpy(M[map_order_now - 1].Map, map, sizeof(map)); //string.h ���� ��ͼ�л�����
}//����λ���л����ĺ���(������)

void refresh()
{
	memcpy(map1, M[map_order_now - 1].Map, sizeof(map));
}
//ˢ�º��������о�

int get_x_y(int x, int y)
{
	return map[x][y];
}

void floor_changes_role_xy() //��ͬ��¥֮��������ͼ�л�(��ʼλ�ô�����
{
	if (map_order_now >= map_order_pre) ///��¥���
		switch (map_order_now)
		{
		case 1: ///��¥��1¥(���ʼ������)
			People.x = 10;
			People.y = 6;
			break;
		case 2: ///��¥��2¥
			People.x = 2;
			People.y = 1;
			break;
		case 3:
			People.x = 11;
			People.y = 2;
			break;
		case 4:
			People.x = 10;
			People.y = 11;
			break;
		case 5:
			People.x = 10;
			People.y = 1;
			break;
		case 6:
			People.x = 10;
			People.y = 10;
			break;
		case 7:
			People.x = 11;
			People.y = 6;
			break;
		case 8:
			People.x = 2;
			People.y = 1;
			break;
		case 9:
			People.x = 4;
			People.y = 7;
			break;
		case 10:
			People.x = 7;
			People.y = 5;
			break;
		case 11:
			People.x = 11;
			People.y = 2;
			break;
		}
	else ///��¥���
		switch (map_order_now)
		{
		case 1: ///��¥��1¥
			People.x = 1;
			People.y = 2;
			break;
		case 2: ///��¥��2¥WW
			People.x = 10;
			People.y = 1;
			break;
		case 3:
			People.x = 10;
			People.y = 11;
			break;
		case 4:
			People.x = 10;
			People.y = 1;
			break;
		case 5:
			People.x = 10;
			People.y = 10;
			break;
		case 6:
			People.x = 10;
			People.y = 5;
			break;
		case 7:
			People.x = 1;
			People.y = 2;
			break;
		case 8:
			People.x = 5;
			People.y = 8;
			break;
		case 9:
			People.x = 8;
			People.y = 7;
			break;
		case 10:
			People.x = 10;
			People.y = 1;
			break;
		}
	Sleep(300); ///ȥ������¥���޻�ͼBUG
	map_order_pre = map_order_now;
	refresh();
};

void initImage() //ͼ���ʼ������
{
	Background.img = newimage();
	GreenSlime.img = newimage();
	RedDiamond.img = newimage();
	RedDoor.img = newimage();
	RedSlime.img = newimage();
	BlackSlime.img = newimage();
	BigBat.img = newimage();
	RedBat.img = newimage();
	SmallBat.img = newimage();
	Witch_1.img = newimage();
	Witch_2.img = newimage();
	Guard_3.img = newimage();
	Guard_2.img = newimage();
	Guard_1.img = newimage();
	BoneMan.img = newimage();
	BoneWarrior.img = newimage();
	BoneGuard.img = newimage();
	GBoss.img = newimage();
	MonsterKing.img = newimage();
	RBoss.img = newimage();
	Orc.img = newimage();
	OrcWarrior.img = newimage();
	OldMan.img = newimage();
	RedMan.img = newimage();
	SwordMan.img = newimage();
	Warrior.img = newimage();
	Witch_Y.img = newimage();
	Witch_R.img = newimage();
	WhiteWitch.img = newimage();
	RKey.img = newimage();
	BKey.img = newimage();
	YKey.img = newimage();
	GKey.img = newimage();
	Sword.img = newimage();
	Shield.img = newimage();
	TreasureBox.img = newimage();
	WindOrient.img = newimage();
	GoldCoin.img = newimage();
	HP.img = newimage();
	BigHP.img = newimage();
	Cross.img = newimage();
	CrossEmblem.img = newimage();
	Level_Up.img = newimage();
	Background.img = newimage();
	Block.img = newimage();
	Floor.img = newimage();
	Wall.img = newimage();
	YellowDoor.img = newimage();
	GreenDoor.img = newimage();
	BlueDoor.img = newimage();
	BlueDiamond.img = newimage();
	Upstairs.img = newimage();
	Downstairs.img = newimage();
	Shop.img = newimage();
	Stars.img = newimage();
	People.img = newimage();
	StoneMan.img = newimage();
	//����
	CrossEmblem_PUSH.img = newimage();
	Shop_PUSH[0].img = newimage();
	Shop_PUSH[1].img = newimage();
	Shop_PUSH[2].img = newimage();
	Shop_PUSH[3].img = newimage();
	WindOrient_PUSH.img = newimage();
	End.img = newimage();
	Versus.img = newimage();
	Warrior_PUSH[0].img = newimage();
	Warrior_PUSH[1].img = newimage();
	Warrior_PUSH[2].img = newimage();
	Warrior_PUSH[3].img = newimage();
	Warrior_PUSH[4].img = newimage();
	Warrior_PUSH[5].img = newimage();
	Warrior_PUSH[6].img = newimage();
	Warrior_PUSH[7].img = newimage();
	Warrior_PUSH[8].img = newimage();
	Warrior_PUSH[9].img = newimage();
	Warrior_PUSH[10].img = newimage();
	Warrior_PUSH[11].img = newimage();
	Warrior_PUSH[12].img = newimage();
	Warrior_PUSH[13].img = newimage();
	Warrior_PUSH[14].img = newimage();
	Warrior_PUSH[15].img = newimage();
	OldMan_PUSH[0].img = newimage();
	OldMan_PUSH[1].img = newimage();
	OldMan_PUSH[2].img = newimage();
	OldMan_PUSH[3].img = newimage();
	RedMan_PUSH[0].img = newimage();
	RedMan_PUSH[1].img = newimage();
	RedMan_PUSH[2].img = newimage();
	RedMan_PUSH[3].img = newimage();
	//��ȡͼ��
	getimage(GreenSlime.img, "picture1/GreenSlime.png");
	getimage(Background.img, "picture1/Background.png");
	getimage(BlackSlime.img, "picture1/BlackSlime.png");
	getimage(RedSlime.img, "picture1/RedSlime.png");
	getimage(RedDoor.img, "picture1/RedDoor.png");
	getimage(RedDiamond.img, "picture1/RedDiamond.png");
	getimage(SmallBat.img, "picture1/SmallBat.png");
	getimage(BigBat.img, "picture1/BigBat.png");
	getimage(RedBat.img, "picture1/RedBat.png");
	getimage(Witch_1.img, "picture1/Witch_1.png");
	getimage(Witch_2.img, "picture1/Witch_2.png");
	getimage(Guard_1.img, "picture1/Guard_1.png");
	getimage(Guard_2.img, "picture1/Guard_2.png");
	getimage(Guard_3.img, "picture1/Guard_3.png");
	getimage(BoneMan.img, "picture1/BoneMan.png");
	getimage(BoneWarrior.img, "picture1/BoneWarrior.png");
	getimage(BoneGuard.img, "picture1/BoneGuard.png");
	getimage(GBoss.img, "picture1/GBoss.png");
	getimage(MonsterKing.img, "picture1/MonsterKing.png");
	getimage(RBoss.img, "picture1/RBoss.png");
	getimage(Orc.img, "picture1/Orc.png");
	getimage(OrcWarrior.img, "picture1/OrcWarrior.png");
	getimage(OldMan.img, "picture1/OldMan.png");
	getimage(RedMan.img, "picture1/RedMan.png");
	getimage(SwordMan.img, "picture1/SwordMan.png");
	getimage(Warrior.img, "picture1/Warrior.png");
	getimage(Witch_R.img, "picture1/Witch_R.png");
	getimage(Witch_Y.img, "picture1/Witch_Y.png");
	getimage(WhiteWitch.img, "picture1/WhiteWitch.png");
	getimage(RKey.img, "picture1/RKey.png");
	getimage(YKey.img, "picture1/YKey.png");
	getimage(BKey.img, "picture1/BKey.png");
	getimage(GKey.img, "picture1/GKey.png");
	getimage(Sword.img, "picture1/Sword.png");
	getimage(Shield.img, "picture1/Shield.png");
	getimage(TreasureBox.img, "picture1/TreasureBox.png");
	getimage(WindOrient.img, "picture1/WindOrient.png");
	getimage(Level_Up.img, "picture1/Level_Up.png");
	getimage(GoldCoin.img, "picture1/GoldCoin.png");
	getimage(HP.img, "picture1/HP.png");
	getimage(BigHP.img, "picture1/BigHP.png");
	getimage(CrossEmblem.img, "picture1/CrossEmblem.png");
	getimage(Block.img, "picture1/Block.png");
	getimage(Background.img, "picture1/Background.png");
	getimage(Floor.img, "picture1/Floor.png");
	getimage(Wall.img, "picture1/Wall.png");
	getimage(YellowDoor.img, "picture1/YellowDoor.png");
	getimage(BlueDoor.img, "picture1/BlueDoor.png");
	getimage(BlueDiamond.img, "picture1/BlueDiamond.png");
	getimage(GreenDoor.img, "picture1/GreenDoor.png");
	getimage(Upstairs.img, "picture1/Upstairs.png");
	getimage(Downstairs.img, "picture1/Downstairs.png");
	getimage(Shop.img, "picture1/Shop.png");
	getimage(Stars.img, "picture1/Stars.png");
	getimage(People.img, "picture1/actor.png");
	getimage(StoneMan.img, "picture1/StoneMan.png");
	//����ͼƬ
	getimage(CrossEmblem_PUSH.img, "picture1/CrossEmblem_PUSH.png");
	getimage(Shop_PUSH[0].img, "picture1/Shop1.png");
	getimage(Shop_PUSH[1].img, "picture1/Shop2.png");
	getimage(Shop_PUSH[2].img, "picture1/Shop3.png");
	getimage(Shop_PUSH[3].img, "picture1/Shop4.png");
	getimage(Versus.img, "picture1/Versus.png");
	getimage(OldMan_PUSH[0].img, "picture1/OldManOption1.png");
	getimage(OldMan_PUSH[1].img, "picture1/OldManOption2.png");
	getimage(OldMan_PUSH[2].img, "picture1/OldManOption3.png");
	getimage(OldMan_PUSH[3].img, "picture1/OldManOption4.png");
	getimage(End.img, "picture1/End.png");
	getimage(WindOrient_PUSH.img, "picture1/WindOrient.png");
	getimage(RedMan_PUSH[0].img, "picture1/RedManOption1.png");
	getimage(RedMan_PUSH[1].img, "picture1/RedManOption2.png");
	getimage(RedMan_PUSH[2].img, "picture1/RedManOption3.png");
	getimage(RedMan_PUSH[3].img, "picture1/RedManOption4.png");
	getimage(Warrior_PUSH[0].img, "picture1/Warrior1.png");
	getimage(Warrior_PUSH[1].img, "picture1/Warrior2.png");
	getimage(Warrior_PUSH[2].img, "picture1/Warrior3.png");
	getimage(Warrior_PUSH[3].img, "picture1/Warrior4.png");
	getimage(Warrior_PUSH[4].img, "picture1/Warrior5.png");
	getimage(Warrior_PUSH[5].img, "picture1/Warrior6.png");
	getimage(Warrior_PUSH[6].img, "picture1/Warrior7.png");
	getimage(Warrior_PUSH[7].img, "picture1/Warrior8.png");
	getimage(Warrior_PUSH[8].img, "picture1/Warrior9.png");
	getimage(Warrior_PUSH[9].img, "picture1/Warrior10.png");
	getimage(Warrior_PUSH[10].img, "picture1/Warrior11.png");
	getimage(Warrior_PUSH[11].img, "picture1/Warrior12.png");
	getimage(Warrior_PUSH[12].img, "picture1/Warrior13.png");
	getimage(Warrior_PUSH[13].img, "picture1/Warrior14.png");
	getimage(Warrior_PUSH[14].img, "picture1/Warrior15.png");
	getimage(Warrior_PUSH[15].img, "picture1/Warrior16.png");
}
void InitEnemy() //���˽�ɫ��ʼ��
{
	//��ʷ��ķ
	GreenSlime.hp = 200;
	GreenSlime.Attack = 35;
	GreenSlime.Defence = 10;
	GreenSlime.exp = 5;
	GreenSlime.money = 5;
	strcpy(GreenSlime.name, "��ʷ��ķ");
	//��ʷ��ķ
	RedSlime.hp = 70;
	RedSlime.Attack = 15;
	RedSlime.Defence = 2;
	RedSlime.exp = 5;
	RedSlime.money = 5;
	strcpy(RedSlime.name, "��ʷ��ķ");
	//��ʷ��ķ
	BlackSlime.hp = 50;
	BlackSlime.Attack = 10;
	BlackSlime.Defence = 1;
	BlackSlime.exp = 3;
	BlackSlime.money = 3;
	strcpy(BlackSlime.name, "��ʷ��ķ");
	//����
	BoneMan.hp = 5;
	BoneMan.Attack = 25;
	BoneMan.Defence = 10;
	BoneMan.money = 5;
	BoneMan.exp = 5;
	strcpy(BoneMan.name, "������");
	//����ʿ��
	BoneWarrior.hp = 150;
	BoneWarrior.Attack = 40;
	BoneWarrior.Defence = 20;
	BoneWarrior.money = 20;
	BoneWarrior.exp = 20;
	strcpy(BoneWarrior.name, "����ʿ��");
	//������ʿ
	BoneGuard.hp = 300;
	BoneGuard.Attack = 50;
	BoneGuard.Defence = 30;
	BoneGuard.money = 50;
	BoneGuard.exp = 40;
	strcpy(BoneGuard.name, "������ʿ");
	//������ʦ
	Witch_1.hp = 10;
	Witch_1.money = 25;
	Witch_1.Attack = 50;
	Witch_1.exp = 10;
	strcpy(Witch_1.name, "������ʦ");
	//�߼���ʦ
	Witch_2.hp = 100;
	Witch_2.Attack = 200;
	Witch_2.Defence = 100;
	Witch_2.money = 100;
	Witch_2.exp = 55;
	strcpy(Witch_2.name, "�߼���ʦ");
	//���·�ʦ
	Witch_R.hp = 500;
	Witch_R.Attack = 400;
	Witch_R.Defence = 250;
	Witch_R.money = 120;
	Witch_R.exp = 100;
	strcpy(Witch_R.name, "���·�ʦ");
	//���·�ʦ
	Witch_Y.hp = 250;
	Witch_Y.Attack = 300;
	Witch_Y.Defence = 150;
	Witch_Y.money = 100;
	Witch_Y.exp = 80;
	strcpy(Witch_Y.name, "���·�ʦ");
	//С����
	SmallBat.hp = 80;
	SmallBat.Attack = 20;
	SmallBat.Defence = 10;
	SmallBat.exp = 5;
	SmallBat.money = 5;
	strcpy(SmallBat.name, "С����");
	//������
	BigBat.hp = 150;
	BigBat.Attack = 55;
	BigBat.Defence = 20;
	BigBat.money = 15;
	BigBat.exp = 15;
	strcpy(BigBat.name, "������");
	//������
	RedBat.hp = 200;
	RedBat.Attack = 150;
	RedBat.Defence = 60;
	RedBat.money = 30;
	RedBat.exp = 30;
	strcpy(RedBat.name, "������");
	//����
	Orc.hp = 250;
	Orc.Attack = 80;
	Orc.Defence = 60;
	Orc.money = 30;
	Orc.exp = 20;
	strcpy(Orc.name, "����");
	//����սʿ
	OrcWarrior.hp = 800;
	OrcWarrior.Attack = 300;
	OrcWarrior.Defence = 300;
	OrcWarrior.money = 100;
	OrcWarrior.exp = 80;
	strcpy(OrcWarrior.name, "����սʿ");
	//ʯͷ��
	StoneMan.hp = 2000;
	StoneMan.Attack = 20;
	StoneMan.Defence = 600;
	StoneMan.exp = 100;
	StoneMan.money = 100;
	strcpy(StoneMan.name, "ʯͷ��");
	//��������
	Guard_1.hp = 200;
	Guard_1.Attack = 100;
	Guard_1.Defence = 100;
	Guard_1.exp = 30;
	Guard_1.money = 30;
	strcpy(Guard_1.name, "��������");
	//�߼�����
	Guard_2.hp = 200;
	Guard_2.Attack = 400;
	Guard_2.Defence = 200;
	Guard_2.exp = 50;
	Guard_2.money = 60;
	strcpy(Guard_2.name, "�߼�����");
	//�߼���ʿ
	Guard_3.hp = 1200;
	Guard_3.Attack = 600;
	Guard_3.Defence = 400;
	Guard_3.exp = 100;
	Guard_3.money = 200;
	strcpy(Guard_3.name, "�߼���ʿ");
	//��ɫ�ӳ�
	RBoss.hp = 2000;
	RBoss.Attack = 800;
	RBoss.Defence = 1000;
	RBoss.exp = 300;
	RBoss.money = 300;
	strcpy(RBoss.name, "��ɫ�ӳ�");
	//��ɫ�ӳ�
	GBoss.hp = 1500;
	GBoss.Attack = 1200;
	GBoss.Defence = 1000;
	GBoss.exp = 300;
	GBoss.money = 300;
	strcpy(GBoss.name, "��ɫ�ӳ�");
	//��ʿ
	SwordMan.hp = 1000;
	SwordMan.Attack = 2500;
	SwordMan.Defence = 300;
	SwordMan.exp = 200;
	SwordMan.money = 400;
	strcpy(SwordMan.name, "��ʿ");
	//������ʦ
	WhiteWitch.hp = 1500;
	WhiteWitch.Attack = 2000;
	WhiteWitch.Defence = 200;
	WhiteWitch.exp = 200;
	WhiteWitch.money = 400;
	strcpy(WhiteWitch.name, "������ʦ");
	//ʷ��ķ��
	MonsterKing.hp = 800;
	MonsterKing.Attack = 200;
	MonsterKing.Defence = 200;
	MonsterKing.exp = 50;
	MonsterKing.money = 30;
	strcpy(MonsterKing.name, "ʷ��ķ��");
}
void Show_Map()
{


	// changemap();
	// refresh();
	memcpy(map, map1, sizeof(map));
	map[People.x][People.y] = 15;
	putimage(0, 0, Background.img);
	//changemap();
	//refresh();

	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			if (map[j][i] == 0)
				putimage(60 * i + 304, 60 * j + 3, Floor.img);
			else if (map[j][i] == 2)
				putimage(60 * i + 304, 60 * j + 3, Wall.img);
			else if (map[j][i] == 3)
				putimage(60 * i + 304, 60 * j + 3, RedDoor.img);
			else if (map[j][i] == 4)
				putimage(60 * i + 304, 60 * j + 3, YellowDoor.img);
			else if (map[j][i] == 5)
				putimage(60 * i + 304, 60 * j + 3, BlueDoor.img);
			else if (map[j][i] == 6)
				putimage(60 * i + 304, 60 * j + 3, HP.img);
			else if (map[j][i] == 7)
				putimage(60 * i + 304, 60 * j + 3, BigHP.img);
			else if (map[j][i] == 8)
				putimage(60 * i + 304, 60 * j + 3, CrossEmblem.img);
			else if (map[j][i] == 9)
				putimage(60 * i + 304, 60 * j + 3, WindOrient.img);
			else if (map[j][i] == 10)
				putimage(60 * i + 304, 60 * j + 3, Upstairs.img);
			else if (map[j][i] == 11)
				putimage(60 * i + 304, 60 * j + 3, Downstairs.img);
			else if (map[j][i] == 12)
				putimage(60 * i + 304, 60 * j + 3, YKey.img);
			else if (map[j][i] == 13)
				putimage(60 * i + 304, 60 * j + 3, RKey.img);
			else if (map[j][i] == 14)
				putimage(60 * i + 304, 60 * j + 3, BKey.img);
			else if (map[j][i] == 15)
				putimage(60 * i + 304, 60 * j + 3, People.img);
			else if (map[j][i] == 16)
				putimage(60 * i + 304, 60 * j + 3, RedDiamond.img);
			else if (map[j][i] == 17)
				putimage(60 * i + 304, 60 * j + 3, BlueDiamond.img);
			else if (map[j][i] == 18)
				putimage(60 * i + 304, 60 * j + 3, OldMan.img);
			else if (map[j][i] == 19)
				putimage(60 * i + 304, 60 * j + 3, RedMan.img);
			else if (map[j][i] == 20)
				putimage(60 * i + 304, 60 * j + 3, GreenDoor.img);
			else if (map[j][i] == 21)
				putimage(60 * i + 304, 60 * j + 3, Sword.img);
			else if (map[j][i] == 22)
				putimage(60 * i + 304, 60 * j + 3, Shop.img);
			else if (map[j][i] == 23)
				putimage(60 * i + 304, 60 * j + 3, Warrior.img);
			else if (map[j][i] == 24)
				putimage(60 * i + 304, 60 * j + 3, GKey.img);
			else if (map[j][i] == 25)
				putimage(60 * i + 304, 60 * j + 3, Shield.img);
			else if (map[j][i] == 26)
				putimage(60 * i + 304, 60 * j + 3, Level_Up.img);
			else if (map[j][i] == 27)
				putimage(60 * i + 304, 60 * j + 3, GoldCoin.img);
			else if (map[j][i] == 28)
				putimage(60 * i + 304, 60 * j + 3, Cross.img);
			else if (map[j][i] == 29)
				putimage(60 * i + 304, 60 * j + 3, TreasureBox.img);
			else if (map[j][i] == 30)
				putimage(60 * i + 304, 60 * j + 3, BlackSlime.img);
			else if (map[j][i] == 31)
				putimage(60 * i + 304, 60 * j + 3, RedSlime.img);
			else if (map[j][i] == 32)
				putimage(60 * i + 304, 60 * j + 3, BoneMan.img);
			else if (map[j][i] == 33)
				putimage(60 * i + 304, 60 * j + 3, Witch_1.img);
			else if (map[j][i] == 34)
				putimage(60 * i + 304, 60 * j + 3, GreenSlime.img);
			else if (map[j][i] == 35)
				putimage(60 * i + 304, 60 * j + 3, SmallBat.img);
			else if (map[j][i] == 36)
				putimage(60 * i + 304, 60 * j + 3, Orc.img);
			else if (map[j][i] == 37)
				putimage(60 * i + 304, 60 * j + 3, BoneWarrior.img);
			else if (map[j][i] == 38)
				putimage(60 * i + 304, 60 * j + 3, BigBat.img);
			else if (map[j][i] == 39)
				putimage(60 * i + 304, 60 * j + 3, Guard_1.img);
			else if (map[j][i] == 40)
				putimage(60 * i + 304, 60 * j + 3, RBoss.img);
			else if (map[j][i] == 41)
				putimage(60 * i + 304, 60 * j + 3, GBoss.img);
			else if (map[j][i] == 42)
				putimage(60 * i + 304, 60 * j + 3, BoneGuard.img);
			else if (map[j][i] == 43)
				putimage(60 * i + 304, 60 * j + 3, MonsterKing.img);
			else if (map[j][i] == 44)
				putimage(60 * i + 304, 60 * j + 3, StoneMan.img);
			else if (map[j][i] == 45)
				putimage(60 * i + 304, 60 * j + 3, RedBat.img);
			else if (map[j][i] == 46)
				putimage(60 * i + 304, 60 * j + 3, Witch_R.img);
			else if (map[j][i] == 47)
				putimage(60 * i + 304, 60 * j + 3, Witch_2.img);
			else if (map[j][i] == 48)
				putimage(60 * i + 304, 60 * j + 3, WhiteWitch.img);
			else if (map[j][i] == 49)
				putimage(60 * i + 304, 60 * j + 3, Witch_Y.img);
			else if (map[j][i] == 50)
				putimage(60 * i + 304, 60 * j + 3, OrcWarrior.img);
			else if (map[j][i] == 51)
				putimage(60 * i + 304, 60 * j + 3, SwordMan.img);
			else if (map[j][i] == 52)
				putimage(60 * i + 304, 60 * j + 3, Guard_2.img);
			else if (map[j][i] == 53)
				putimage(60 * i + 304, 60 * j + 3, Guard_3.img);
			/*else if (map[j][i] == 54)
				putimage(60 * i + 304, 60 * j + 3, LINGWUSHI.img);
			else if (map[j][i] == 55)
				putimage(60 * i + 304, 60 * j + 3, MINGZHANSHI.img);
			else if (map[j][i] == 56)
				putimage(60 * i + 304, 60 * j + 3, LINGFASHI.img);
			else if (map[j][i] == 57)
				putimage(60 * i + 304, 60 * j + 3, MINGDUIZHANG.img);*/
		}
		///������������ӡ
		setcolor(RGB(255, 255, 255)); ///��ɫ����
		setbkmode(TRANSPARENT);		  ///���ֱ���͸��
		setfont(-55, 0, "����");	  ///������
		char YELLOWKEYNUM[3], REDKEYNUM[3], LEVELNUM[3], BLUEKEYNUM[3], ATACKNUM[5], HPNUM[10], EXNUM[5], MONEYNUM[5], DEFNUM[5];
		sprintf(YELLOWKEYNUM, "%d", People.Ykey); ///ͷ�ļ�cstdio��stdio.h
		sprintf(REDKEYNUM, "%d", People.Rkey);
		sprintf(BLUEKEYNUM, "%d", People.Bkey);
		sprintf(LEVELNUM, "%d", People.level);
		sprintf(ATACKNUM, "%d", People.Attack);
		sprintf(HPNUM, "%d", People.hp);
		sprintf(EXNUM, "%d", People.exp);
		sprintf(MONEYNUM, "%d", People.money);
		sprintf(DEFNUM, "%d", People.Defence);
		outtextxy(210, 405, YELLOWKEYNUM); ///��Կ�״�ӡ
		outtextxy(210, 530, REDKEYNUM);	   ///��Կ�״�ӡ
		outtextxy(210, 465, BLUEKEYNUM);   ///��Կ�״�ӡ
		outtextxy(210, 90, LEVELNUM);	   ///�ȼ���ӡ
		setfont(-35, 0, "����");		   ///�����С
		outtextxy(210, 165, HPNUM);		   ///Ѫ����ӡ
		outtextxy(210, 208, ATACKNUM);	   ///��������ӡ
		outtextxy(210, 250, DEFNUM);	   ///��������ӡ
		outtextxy(210, 295, MONEYNUM);	   ///��Ǯ��ӡ
		outtextxy(210, 340, EXNUM);		   ///�����ӡ
	}

}

void show_attack_monster(PIMAGE img, int hp, int atack, int def)
{
	putimage(300, 200, Versus.img);
	putimage(325, 240, 80, 80, img, 0, 0, 60, 60);
	setcolor(RGB(255, 255, 255));///��ɫ����
	setbkmode(TRANSPARENT);///���ֱ���͸��
	setfont(-35, 0, "����");///������
	char HP[10], Attack[10], Defence[10], PeopleHP[10], PeopleAttack[10], PeopleDefence[10];
	sprintf(HP, "%d", hp);
	sprintf(Attack, "%d", atack);
	sprintf(Defence, "%d", def);
	sprintf(PeopleHP, "%d", People.hp);
	sprintf(PeopleAttack, "%d", People.Attack);
	sprintf(PeopleDefence, "%d", People.Defence);
	outtextxy(450, 261, HP);
	outtextxy(450, 320, Attack);
	outtextxy(450, 380, Defence);
	outtextxy(700, 261, PeopleHP);
	outtextxy(700, 320, PeopleAttack);
	outtextxy(700, 380, PeopleDefence);
}///��ֽ���

void atack_monster_hp(int EXCLE, int x, int y, int temhp)
{
	map[x][y] = EXCLE;
	changemap();
	People.hp += temhp;
}///�޸�����HP����Ϊ������BUG


void atack_monster(int EXCLE, int x, int y)
{
	///��ֺ���
	switch (EXCLE)
	{
		///��ʷ��ķ
	case 30:
		if (People.Attack > GreenSlime.Defence)
			if ((People.hp - ((GreenSlime.hp / (People.Attack - GreenSlime.Defence)) * (GreenSlime.Attack - People.Defence))) > 0)
			{
				int hp = GreenSlime.hp;
				int temhp = 0;
				for (int i = 0; i < 20000; i++)
				{
					People.hp -= GreenSlime.Attack - People.Defence;
					hp -= People.Attack - GreenSlime.Defence;
					temhp += GreenSlime.Attack - People.Defence;
					//mciSendString("play audio\\Attack.wav", "", 0, NULL);
					if (hp < 0)
						hp = 0;
					show_attack_monster(GreenSlime.img, hp, GreenSlime.Attack, GreenSlime.Defence);
					Sleep(300);
					if (hp == 0)
						break;
				}
				if (People.hp <= 0)
					atack_monster_hp(EXCLE, x, y, temhp);
				//People.hp-=GreenSlime.hp/(People.Attack-GreenSlime.Defence)*(GreenSlime.Attack-People.Defence);
				else
				{
					People.money += GreenSlime.money;
					People.exp += GreenSlime.exp;

					map[x][y] = 0;
				}
				map[People.x][People.y] = 0;
				changemap();
				refresh();
				cleardevice();
				Show_Map();
			}
		break;

		///��ͷ��
	case 31:
		if (People.Attack > RedSlime.Defence)
			if ((People.hp - ((RedSlime.hp / (People.Attack - RedSlime.Defence)) * (RedSlime.Attack - People.Defence))) > 0)
			{
				int hp = RedSlime.hp;
				int temhp = 0;
				for (int i = 0; i < 20000; i++)
				{
					People.hp -= RedSlime.Attack - People.Defence;
					hp -= People.Attack - RedSlime.Defence;
					temhp += RedSlime.Attack - People.Defence;
					//mciSendString("play audio\\Attack.wav", "", 0, NULL);
					if (hp < 0)
						hp = 0;
					show_attack_monster(RedSlime.img, hp, RedSlime.Attack, RedSlime.Defence);
					Sleep(300);
					if (hp == 0)
						break;
				}
				//People.hp-=RedSlime.hp/(People.Attack-RedSlime.Defence)*(RedSlime.Attack-People.Defence);
				if (People.hp <= 0)
					atack_monster_hp(EXCLE, x, y, temhp);
				else
				{
					People.money += RedSlime.money;
					People.exp += RedSlime.exp;

					map[x][y] = 0;
				}
				map[People.x][People.y] = 0;
				changemap();
				refresh();
				cleardevice();
				Show_Map();
			}
		break;
		///������
	case 32:
		if (People.Attack > BoneMan.Defence)
			if ((People.hp - (BoneMan.hp / (People.Attack - BoneMan.Defence) * (BoneMan.Attack - People.Defence))) > 0)
			{
				int hp = BoneMan.hp;
				int temhp = 0;
				for (int i = 0; i < 20000; i++)
				{
					People.hp -= BoneMan.Attack - People.Defence;
					hp -= People.Attack - BoneMan.Defence;
					temhp += BoneMan.Attack - People.Defence;
					//mciSendString("play audio\\Attack.wav", "", 0, NULL);
					if (hp < 0)
						hp = 0;
					show_attack_monster(BoneMan.img, hp, BoneMan.Attack, BoneMan.Defence);
					Sleep(300);
					if (hp == 0)
						break;
				}
				//People.hp-=BoneMan.hp/(People.Attack-BoneMan.Defence)*(BoneMan.Attack-People.Defence);
				if (People.hp <= 0)
					atack_monster_hp(EXCLE, x, y, temhp);
				else
				{
					People.money += BoneMan.money;
					People.exp += BoneMan.exp;

					map[x][y] = 0;
				}
				map[People.x][People.y] = 0;
				changemap();
				refresh();
				cleardevice();
				Show_Map();
			}

		break;
		///������ʦ
	case 33:
		if (People.Attack > Witch_1.Defence)
			if ((People.hp - ((Witch_1.hp / (People.Attack - Witch_1.Defence)) * (Witch_1.Attack - People.Defence))) > 0)
			{
				int hp = Witch_1.hp;
				int temhp = 0;
				for (int i = 0; i < 20000; i++)
				{
					People.hp -= Witch_1.Attack - People.Defence;
					hp -= People.Attack - Witch_1.Defence;
					temhp += Witch_1.Attack - People.Defence;
					//mciSendString("play audio\\Attack.wav", "", 0, NULL);
					if (hp < 0)
						hp = 0;
					show_attack_monster(Witch_1.img, hp, Witch_1.Attack, Witch_1.Defence);
					Sleep(300);
					if (hp == 0)
						break;
				}
				//People.hp-=Witch_1.hp/(People.Attack-Witch_1.Defence)*(Witch_1.Attack-People.Defence);
				if (People.hp <= 0)
					atack_monster_hp(EXCLE, x, y, temhp);
				else
				{
					People.money += Witch_1.money;
					People.exp += Witch_1.exp;

					map[x][y] = 0;
				}
				map[People.x][People.y] = 0;
				changemap();
				refresh();
				cleardevice();
				Show_Map();
			}

		break;
		///��ͷ��
	case 34:
		if (People.Attack > GreenSlime.Defence)
			if ((People.hp - ((GreenSlime.hp / (People.Attack - GreenSlime.Defence)) * (GreenSlime.Attack - People.Defence))) > 0)
			{
				int hp = GreenSlime.hp;
				int temhp = 0;
				for (int i = 0; i < 20000; i++)
				{
					People.hp -= GreenSlime.Attack - People.Defence;
					hp -= People.Attack - GreenSlime.Defence;
					temhp += GreenSlime.Attack - People.Defence;
					//mciSendString("play audio\\Attack.wav", "", 0, NULL);
					if (hp < 0)
						hp = 0;
					show_attack_monster(GreenSlime.img, hp, GreenSlime.Attack, GreenSlime.Defence);
					Sleep(300);
					if (hp == 0)
						break;
				}
				//People.hp-=GreenSlime.hp/(People.Attack-GreenSlime.Defence)*(GreenSlime.Attack-People.Defence);
				if (People.hp <= 0)
					atack_monster_hp(EXCLE, x, y, temhp);
				else
				{
					People.money += GreenSlime.money;
					People.exp += GreenSlime.exp;

					map[x][y] = 0;
				}
				map[People.x][People.y] = 0;
				changemap();
				refresh();
				cleardevice();
				Show_Map();
			}

		break;
		///С����
	case 35:
		if (People.Attack > SmallBat.Defence)
			if ((People.hp - ((SmallBat.hp / (People.Attack - SmallBat.Defence)) * (SmallBat.Attack - People.Defence))) > 0)
			{
				int hp = SmallBat.hp;
				int temhp = 0;
				for (int i = 0; i < 20000; i++)
				{
					People.hp -= SmallBat.Attack - People.Defence;
					hp -= People.Attack - SmallBat.Defence;
					temhp += SmallBat.Attack - People.Defence;
					//mciSendString("play audio\\Attack.wav", "", 0, NULL);
					if (hp < 0)
						hp = 0;
					show_attack_monster(SmallBat.img, hp, SmallBat.Attack, SmallBat.Defence);
					Sleep(300);
					if (hp == 0)
						break;
				}
				//People.hp-=SmallBat.hp/(People.Attack-SmallBat.Defence)*(SmallBat.Attack-People.Defence);
				if (People.hp <= 0)
					atack_monster_hp(EXCLE, x, y, temhp);
				else
				{
					People.money += SmallBat.money;
					People.exp += SmallBat.exp;

					map[x][y] = 0;
				}
				map[People.x][People.y] = 0;
				changemap();
				refresh();
				cleardevice();
				Show_Map();
			}

		break;
		///������
	case 36:
		if (People.Attack > Orc.Defence)
			if ((People.hp - ((Orc.hp / (People.Attack - Orc.Defence)) * (Orc.Attack - People.Defence))) > 0)
			{
				int temhp = 0, hp = Orc.hp;
				for (int i = 0; i < 20000; i++)
				{
					People.hp -= Orc.Attack - People.Defence;
					hp -= People.Attack - Orc.Defence;
					temhp += Orc.Attack - People.Defence;
					//mciSendString("play audio\\Attack.wav", "", 0, NULL);
					if (hp < 0)
						hp = 0;
					show_attack_monster(Orc.img, hp, Orc.Attack, Orc.Defence);
					Sleep(300);
					if (hp == 0)
						break;
				}
				//People.hp-=Orc.hp/(People.Attack-Orc.Defence)*(Orc.Attack-People.Defence);
				if (People.hp <= 0)
					atack_monster_hp(EXCLE, x, y, temhp);
				else
				{
					People.money += Orc.money;
					People.exp += Orc.exp;

					map[x][y] = 0;
				}
				map[People.x][People.y] = 0;
				changemap();
				refresh();
				cleardevice();
				Show_Map();
			}

		break;
		///����ʿ��
	case 37:
		if (People.Attack > BoneWarrior.Defence)
			if ((People.hp - ((BoneWarrior.hp / (People.Attack - BoneWarrior.Defence)) * (BoneWarrior.Attack - People.Defence))) > 0)
			{
				int temhp = 0, hp = BoneWarrior.hp;
				for (int i = 0; i < 20000; i++)
				{
					People.hp -= BoneWarrior.Attack - People.Defence;
					hp -= People.Attack - BoneWarrior.Defence;
					temhp += BoneWarrior.Attack - People.Defence;
					//mciSendString("play audio\\Attack.wav", "", 0, NULL);
					if (hp < 0)
						hp = 0;
					show_attack_monster(BoneWarrior.img, hp, BoneWarrior.Attack, BoneWarrior.Defence);
					Sleep(300);
					if (hp == 0)
						break;
				}
				//People.hp-=BoneWarrior.hp/(People.Attack-BoneWarrior.Defence)*(BoneWarrior.Attack-People.Defence);
				if (People.hp <= 0)
					atack_monster_hp(EXCLE, x, y, temhp);
				else
				{
					People.money += BoneWarrior.money;
					People.exp += BoneWarrior.exp;

					map[x][y] = 0;
				}
				map[People.x][People.y] = 0;
				changemap();
				refresh();
				cleardevice();
				Show_Map();
			}

		break;
		///������
	case 38:
		if (People.Attack > BigBat.Defence)
			if ((People.hp - ((BigBat.hp / (People.Attack - BigBat.Defence)) * (BigBat.Attack - People.Defence))) > 0)
			{
				int temhp = 0, hp = BigBat.hp;
				for (int i = 0; i < 20000; i++)
				{
					People.hp -= BigBat.Attack - People.Defence;
					hp -= People.Attack - BigBat.Defence;
					temhp += BigBat.Attack - People.Defence;
					//mciSendString("play audio\\Attack.wav", "", 0, NULL);
					if (hp < 0)
						hp = 0;
					show_attack_monster(BigBat.img, hp, BigBat.Attack, BigBat.Defence);
					Sleep(300);
					if (hp == 0)
						break;
				}
				//People.hp-=BigBat.hp/(People.Attack-BigBat.Defence)*(BigBat.Attack-People.Defence);
				if (People.hp <= 0)
					atack_monster_hp(EXCLE, x, y, temhp);
				else
				{
					People.money += BigBat.money;
					People.exp += BigBat.exp;

					map[x][y] = 0;
				}
				map[People.x][People.y] = 0;
				changemap();
				refresh();
				cleardevice();
				Show_Map();
			}

		break;
		///��������
	case 39:
		if (People.Attack > Guard_1.Defence)
			if ((People.hp - ((Guard_1.hp / (People.Attack - Guard_1.Defence)) * (Guard_1.Attack - People.Defence))) > 0)
			{
				int temhp = 0, hp = Guard_1.hp;
				for (int i = 0; i < 20000; i++)
				{
					People.hp -= Guard_1.Attack - People.Defence;
					hp -= People.Attack - Guard_1.Defence;
					temhp += Guard_1.Attack - People.Defence;
					//mciSendString("play audio\\Attack.wav", "", 0, NULL);
					if (hp < 0)
						hp = 0;
					show_attack_monster(Guard_1.img, hp, Guard_1.Attack, Guard_1.Defence);
					Sleep(300);
					if (hp == 0)
						break;
				}
				//People.hp-=Guard_1.hp/(People.Attack-Guard_1.Defence)*(Guard_1.Attack-People.Defence);
				if (People.hp <= 0)
					atack_monster_hp(EXCLE, x, y, temhp);
				else
				{
					People.money += Guard_1.money;
					People.exp += Guard_1.exp;

					map[x][y] = 0;
				}
				map[People.x][People.y] = 0;
				changemap();
				refresh();
				cleardevice();
				Show_Map();
			}

		break;
		///��ӳ�
	case 40:
		if (People.Attack > GBoss.Defence)
			if ((People.hp - ((GBoss.hp / (People.Attack - GBoss.Defence)) * (GBoss.Attack - People.Defence))) > 0)
			{
				int temhp = 0, hp = GBoss.hp;
				for (int i = 0; i < 20000; i++)
				{
					People.hp -= GBoss.Attack - People.Defence;
					hp -= People.Attack - GBoss.Defence;
					temhp += GBoss.Attack - People.Defence;
					//mciSendString("play audio\\Attack.wav", "", 0, NULL);
					if (hp < 0)
						hp = 0;
					show_attack_monster(GBoss.img, hp, GBoss.Attack, GBoss.Defence);
					Sleep(300);
					if (hp == 0)
						break;
				}
				//People.hp-=GBoss.hp/(People.Attack-GBoss.Defence)*(GBoss.Attack-People.Defence);
				if (People.hp <= 0)
					atack_monster_hp(EXCLE, x, y, temhp);
				else
				{
					People.money += GBoss.money;
					People.exp += GBoss.exp;

					map[x][y] = 0;
				}
				map[People.x][People.y] = 0;
				changemap();
				refresh();
				cleardevice();
				Show_Map();
			}

		break;
		///����ʿ
	case 41:
		if (People.Attack > Guard_3.Defence)
			if ((People.hp - ((Guard_3.hp / (People.Attack - Guard_3.Defence)) * (Guard_3.Attack - People.Defence))) > 0)
			{
				int temhp = 0, hp = Guard_3.hp;
				for (int i = 0; i < 20000; i++)
				{
					People.hp -= Guard_3.Attack - People.Defence;
					hp -= People.Attack - Guard_3.Defence;
					temhp += Guard_3.Attack - People.Defence;
					//mciSendString("play audio\\Attack.wav", "", 0, NULL);
					if (hp < 0)
						hp = 0;
					show_attack_monster(Guard_3.img, hp, Guard_3.Attack, Guard_3.Defence);
					Sleep(300);
					if (hp == 0)
						break;
				}
				//People.hp-=Guard_3.hp/(People.Attack-Guard_3.Defence)*(Guard_3.Attack-People.Defence);
				if (People.hp <= 0)
					atack_monster_hp(EXCLE, x, y, temhp);
				else
				{
					People.money += Guard_3.money;
					People.exp += Guard_3.exp;

					map[x][y] = 0;
				}
				map[People.x][People.y] = 0;
				changemap();
				refresh();
				cleardevice();
				Show_Map();
			}

		break;
		///���öӳ�
	case 42:
		if (People.Attack > BoneGuard.Defence)
			if ((People.hp - ((BoneGuard.hp / (People.Attack - BoneGuard.Defence)) * (BoneGuard.Attack - People.Defence))) > 0)
			{
				int temhp = 0, hp = BoneGuard.hp;
				for (int i = 0; i < 20000; i++)
				{
					People.hp -= BoneGuard.Attack - People.Defence;
					hp -= People.Attack - BoneGuard.Defence;
					temhp += BoneGuard.Attack - People.Defence;
					//mciSendString("play audio\\Attack.wav", "", 0, NULL);
					if (hp < 0)
						hp = 0;
					show_attack_monster(BoneGuard.img, hp, BoneGuard.Attack, BoneGuard.Defence);
					Sleep(300);
					if (hp == 0)
						break;
				}
				//People.hp-=BoneGuard.hp/(People.Attack-BoneGuard.Defence)*(BoneGuard.Attack-People.Defence);
				if (People.hp <= 0)
					atack_monster_hp(EXCLE, x, y, temhp);
				else
				{
					People.money += BoneGuard.money;
					People.exp += BoneGuard.exp;

					map[x][y] = 0;
				}
				map[People.x][People.y] = 0;
				changemap();
				refresh();
				cleardevice();
				Show_Map();

			}
		break;
		///����
	case 43:
		if (People.Attack > MonsterKing.Defence)
			if ((People.hp - ((MonsterKing.hp / (People.Attack - MonsterKing.Defence)) * (MonsterKing.Attack - People.Defence))) > 0)
			{
				int temhp = 0, hp = MonsterKing.hp;
				for (int i = 0; i < 20000; i++)
				{
					People.hp -= MonsterKing.Attack - People.Defence;
					hp -= People.Attack - MonsterKing.Defence;
					temhp += MonsterKing.Attack - People.Defence;
					//mciSendString("play audio\\Attack.wav", "", 0, NULL);
					if (hp < 0)
						hp = 0;
					show_attack_monster(MonsterKing.img, hp, MonsterKing.Attack, MonsterKing.Defence);
					Sleep(300);
					if (hp == 0)
						break;
				}
				//People.hp-=MonsterKing.hp/(People.Attack-MonsterKing.Defence)*(MonsterKing.Attack-People.Defence);
				if (People.hp <= 0)
					atack_monster_hp(EXCLE, x, y, temhp);
				else
				{
					People.money += MonsterKing.money;
					People.exp += MonsterKing.exp;

					map[x][y] = 0;
				}
				map[People.x][People.y] = 0;
				changemap();
				refresh();
				cleardevice();
				Show_Map();

			}
		break;
		///ʯͷ����
	case 44:
		if (People.Attack > StoneMan.Defence)
			if ((People.hp - ((StoneMan.hp / (People.Attack - StoneMan.Defence)) * (StoneMan.Attack - People.Defence))) > 0)
			{
				int temhp = 0, hp = StoneMan.hp;
				for (int i = 0; i < 20000; i++)
				{
					People.hp -= StoneMan.Attack - People.Defence;
					hp -= People.Attack - StoneMan.Defence;
					temhp += StoneMan.Attack - People.Defence;
					//mciSendString("play audio\\Attack.wav", "", 0, NULL);
					if (hp < 0)
						hp = 0;
					show_attack_monster(StoneMan.img, hp, StoneMan.Attack, StoneMan.Defence);
					Sleep(300);
					if (hp == 0)
						break;
				}
				//People.hp-=StoneMan.hp/(People.Attack-StoneMan.Defence)*(StoneMan.Attack-People.Defence);
				if (People.hp <= 0)
					atack_monster_hp(EXCLE, x, y, temhp);
				else
				{
					People.money += StoneMan.money;
					People.exp += StoneMan.exp;

					map[x][y] = 0;
				}
				map[People.x][People.y] = 0;
				changemap();
				refresh();
				cleardevice();
				Show_Map();
			}

		break;
		///������
	case 45:
		if (People.Attack > RedBat.Defence)
			if ((People.hp - ((RedBat.hp / (People.Attack - RedBat.Defence)) * (RedBat.Attack - People.Defence))) > 0)
			{
				int temhp = 0, hp = RedBat.hp;
				for (int i = 0; i < 20000; i++)
				{
					People.hp -= RedBat.Attack - People.Defence;
					hp -= People.Attack - RedBat.Defence;
					temhp += RedBat.Attack - People.Defence;
					//mciSendString("play audio\\Attack.wav", "", 0, NULL);
					if (hp < 0)
						hp = 0;
					show_attack_monster(RedBat.img, hp, RedBat.Attack, RedBat.Defence);
					Sleep(300);
					if (hp == 0)
						break;
				}
				//People.hp-=RedBat.hp/(People.Attack-RedBat.Defence)*(RedBat.Attack-People.Defence);
				if (People.hp <= 0)
					atack_monster_hp(EXCLE, x, y, temhp);
				else
				{
					People.money += RedBat.money;
					People.exp += RedBat.exp;

					map[x][y] = 0;
				}
				map[People.x][People.y] = 0;
				changemap();
				refresh();
				cleardevice();
				Show_Map();
			}

		break;
		///���·�ʦ
	case 46:
		if (People.Attack > Witch_R.Defence)
			if ((People.hp - ((Witch_R.hp / (People.Attack - Witch_R.Defence)) * (Witch_R.Attack - People.Defence))) > 0)
			{
				int temhp = 0, hp = Witch_R.hp;
				for (int i = 0; i < 20000; i++)
				{
					People.hp -= Witch_R.Attack - People.Defence;
					hp -= People.Attack - Witch_R.Defence;
					temhp += Witch_R.Attack - People.Defence;
					//mciSendString("play audio\\Attack.wav", "", 0, NULL);
					if (hp < 0)
						hp = 0;
					show_attack_monster(Witch_R.img, hp, Witch_R.Attack, Witch_R.Defence);
					Sleep(300);
					if (hp == 0)
						break;
				}
				//People.hp-=Witch_R.hp/(People.Attack-Witch_R.Defence)*(Witch_R.Attack-People.Defence);
				if (People.hp <= 0)
					atack_monster_hp(EXCLE, x, y, temhp);
				else
				{
					People.money += Witch_R.money;
					People.exp += Witch_R.exp;

					map[x][y] = 0;
				}
				map[People.x][People.y] = 0;
				changemap();
				refresh();
				cleardevice();
				Show_Map();
			}

		break;
		///�߼���ʦ
	case 47:
		if (People.Attack > Witch_2.Defence)
			if ((People.hp - ((Witch_2.hp / (People.Attack - Witch_2.Defence)) * (Witch_2.Attack - People.Defence))) > 0)
			{
				int temhp = 0, hp = Witch_2.hp;
				for (int i = 0; i < 20000; i++)
				{
					People.hp -= Witch_2.Attack - People.Defence;
					hp -= People.Attack - Witch_2.Defence;
					temhp += Witch_2.Attack - People.Defence;
					//mciSendString("play audio\\Attack.wav", "", 0, NULL);
					if (hp < 0)
						hp = 0;
					show_attack_monster(Witch_2.img, hp, Witch_2.Attack, Witch_2.Defence);
					Sleep(300);
					if (hp == 0)
						break;
				}
				//People.hp-=Witch_2.hp/(People.Attack-Witch_2.Defence)*(Witch_2.Attack-People.Defence);
				if (People.hp <= 0)
					atack_monster_hp(EXCLE, x, y, temhp);
				else
				{
					People.money += Witch_2.money;
					People.exp += Witch_2.exp;

					map[x][y] = 0;
				}
				map[People.x][People.y] = 0;
				changemap();
				refresh();
				cleardevice();
				Show_Map();
			}

		break;
		///������ʿ
	case 48:
		if (People.Attack > WhiteWitch.Defence)
			if ((People.hp - ((WhiteWitch.hp / (People.Attack - WhiteWitch.Defence)) * (WhiteWitch.Attack - People.Defence))) > 0)
			{
				int temhp = 0, hp = WhiteWitch.hp;
				for (int i = 0; i < 20000; i++)
				{
					People.hp -= WhiteWitch.Attack - People.Defence;
					hp -= People.Attack - WhiteWitch.Defence;
					temhp += WhiteWitch.Attack - People.Defence;
					//mciSendString("play audio\\Attack.wav", "", 0, NULL);
					if (hp < 0)
						hp = 0;
					show_attack_monster(WhiteWitch.img, hp, WhiteWitch.Attack, WhiteWitch.Defence);
					Sleep(300);
					if (hp == 0)
						break;
				}
				//People.hp-=WhiteWitch.hp/(People.Attack-WhiteWitch.Defence)*(WhiteWitch.Attack-People.Defence);
				if (People.hp <= 0)
					atack_monster_hp(EXCLE, x, y, temhp);
				else
				{
					People.money += WhiteWitch.money;
					People.exp += WhiteWitch.exp;

					map[x][y] = 0;
				}
				map[People.x][People.y] = 0;
				changemap();
				refresh();
				cleardevice();
				Show_Map();
			}

		break;
		///���·�ʦ
	case 49:
		if (People.Attack > Witch_Y.Defence)
			if ((People.hp - ((Witch_Y.hp / (People.Attack - Witch_Y.Defence)) * (Witch_Y.Attack - People.Defence))) > 0)
			{
				int temhp = 0, hp = Witch_Y.hp;
				for (int i = 0; i < 20000; i++)
				{
					People.hp -= Witch_Y.Attack - People.Defence;
					hp -= People.Attack - Witch_Y.Defence;
					temhp += Witch_Y.Attack - People.Defence;
					//mciSendString("play audio\\Attack.wav", "", 0, NULL);
					if (hp < 0)
						hp = 0;
					show_attack_monster(Witch_Y.img, hp, Witch_Y.Attack, Witch_Y.Defence);
					Sleep(300);
					if (hp == 0)
						break;
				}
				//People.hp-=Witch_Y.hp/(People.Attack-Witch_Y.Defence)*(Witch_Y.Attack-People.Defence);
				if (People.hp <= 0)
					atack_monster_hp(EXCLE, x, y, temhp);
				else
				{
					People.money += Witch_Y.money;
					People.exp += Witch_Y.exp;

					map[x][y] = 0;
				}
				map[People.x][People.y] = 0;
				changemap();
				refresh();
				cleardevice();
				Show_Map();
			}

		break;
		//    ///������ʿ
		//case 50:
		//    if (People.Attack > SHOUMIANWUSHI.Defence)
		//        if ((People.hp - ((SHOUMIANWUSHI.hp / (People.Attack - SHOUMIANWUSHI.Defence)) * (SHOUMIANWUSHI.Attack - People.Defence))) > 0)
		//        {
		//            int temhp = 0, hp = SHOUMIANWUSHI.hp;
		//            for (int i = 0; i < 20000; i++)
		//            {
		//                People.hp -= SHOUMIANWUSHI.Attack - People.Defence;
		//                hp -= People.Attack - SHOUMIANWUSHI.Defence;
		//                temhp += SHOUMIANWUSHI.Attack - People.Defence;
		//                //mciSendString("play audio\\Attack.wav", "", 0, NULL);
		//                if (hp < 0)
		//                    hp = 0;
		//                show_attack_monster(SHOUMIANWUSHI.img, hp, SHOUMIANWUSHI.Attack, SHOUMIANWUSHI.Defence);
		//                Sleep(300);
		//                if (hp == 0)
		//                    break;
		//            }
		//            //People.hp-=SHOUMIANWUSHI.hp/(People.Attack-SHOUMIANWUSHI.Defence)*(SHOUMIANWUSHI.Attack-People.Defence);
		//            if (People.hp <= 0)
		//                atack_monster_hp(EXCLE, x, y, temhp);
		//            else
		//            {
		//                People.money += SHOUMIANWUSHI.money;
		//                People.exp += SHOUMIANWUSHI.exp;

		//                map[x][y] = 0;
		//            }
		//            map[People.x][People.y] = 0;
		//            changemap();
		//            refresh();
		//            cleardevice();
		//            Show_Map();
		//        }

		//    break;
			///˫�ֽ�ʿ
	case 51:
		if (People.Attack > SwordMan.Defence)
			if ((People.hp - ((SwordMan.hp / (People.Attack - SwordMan.Defence)) * (SwordMan.Attack - People.Defence))) > 0)
			{
				int temhp = 0, hp = SwordMan.hp;
				for (int i = 0; i < 20000; i++)
				{
					People.hp -= SwordMan.Attack - People.Defence;
					hp -= People.Attack - SwordMan.Defence;
					temhp += SwordMan.Attack - People.Defence;
					//mciSendString("play audio\\Attack.wav", "", 0, NULL);
					if (hp < 0)
						hp = 0;
					show_attack_monster(SwordMan.img, hp, SwordMan.Attack, SwordMan.Defence);
					Sleep(300);
					if (hp == 0)
						break;
				}
				//People.hp-=SwordMan.hp/(People.Attack-SwordMan.Defence)*(SwordMan.Attack-People.Defence);
				if (People.hp <= 0)
					atack_monster_hp(EXCLE, x, y, temhp);
				else
				{
					People.money += SwordMan.money;
					People.exp += SwordMan.exp;

					map[x][y] = 0;
				}
				map[People.x][People.y] = 0;
				changemap();
				refresh();
				cleardevice();
				Show_Map();
			}

		break;
		///�߼�����
	case 52:
		if (People.Attack > Guard_2.Defence)
			if ((People.hp - ((Guard_2.hp / (People.Attack - Guard_2.Defence)) * (Guard_2.Attack - People.Defence))) > 0)
			{
				int temhp = 0, hp = Guard_2.hp;
				for (int i = 0; i < 20000; i++)
				{
					People.hp -= Guard_2.Attack - People.Defence;
					hp -= People.Attack - Guard_2.Defence;
					temhp += Guard_2.Attack - People.Defence;
					//mciSendString("play audio\\Attack.wav", "", 0, NULL);
					if (hp < 0)
						hp = 0;
					show_attack_monster(Guard_2.img, hp, Guard_2.Attack, Guard_2.Defence);
					Sleep(300);
					if (hp == 0)
						break;
				}
				//People.hp-=Guard_2.hp/(People.Attack-Guard_2.Defence)*(Guard_2.Attack-People.Defence);
				if (People.hp <= 0)
					atack_monster_hp(EXCLE, x, y, temhp);
				else
				{
					People.money += Guard_2.money;
					People.exp += Guard_2.exp;

					map[x][y] = 0;
				}
				map[People.x][People.y] = 0;
				changemap();
				refresh();
				cleardevice();
				Show_Map();
			}

		break;
		//        ///ڤ����
		//    case 53:
		//        if (People.Attack > MINGWEIBING.Defence)
		//            if ((People.hp - ((MINGWEIBING.hp / (People.Attack - MINGWEIBING.Defence)) * (MINGWEIBING.Attack - People.Defence))) > 0)
		//            {
		//                int temhp = 0, hp = MINGWEIBING.hp;
		//                for (int i = 0; i < 20000; i++)
		//                {
		//                    People.hp -= MINGWEIBING.Attack - People.Defence;
		//                    hp -= People.Attack - MINGWEIBING.Defence;
		//                    temhp += MINGWEIBING.Attack - People.Defence;
		//                    //mciSendString("play audio\\Attack.wav", "", 0, NULL);
		//                    if (hp < 0)
		//                        hp = 0;
		//                    show_attack_monster(MINGWEIBING.img, hp, MINGWEIBING.Attack, MINGWEIBING.Defence);
		//                    Sleep(300);
		//                    if (hp == 0)
		//                        break;
		//                }
		//                //People.hp-=MINGWEIBING.hp/(People.Attack-MINGWEIBING.Defence)*(MINGWEIBING.Attack-People.Defence);
		//                if (People.hp <= 0)
		//                    atack_monster_hp(EXCLE, x, y, temhp);
		//                else
		//                {
		//                    People.money += MINGWEIBING.money;
		//                    People.exp += MINGWEIBING.exp;
		//
		//                    map[x][y] = 0;
		//                }
		//                map[People.x][People.y] = 0;
		//                changemap();
		//                refresh();
		//                cleardevice();
		//                Show_Map();
		//
		//            }
		//        break;
		//        ///����ʿ
		//    case 54:
		//        if (People.Attack > LINGWUSHI.Defence)
		//            if ((People.hp - ((LINGWUSHI.hp / (People.Attack - LINGWUSHI.Defence)) * (LINGWUSHI.Attack - People.Defence))) > 0)
		//            {
		//                int temhp = 0, hp = LINGWUSHI.hp;
		//                for (int i = 0; i < 20000; i++)
		//                {
		//                    People.hp -= LINGWUSHI.Attack - People.Defence;
		//                    hp -= People.Attack - LINGWUSHI.Defence;
		//                    temhp += LINGWUSHI.Attack - People.Defence;
		//                    //mciSendString("play audio\\Attack.wav", "", 0, NULL);
		//                    if (hp < 0)
		//                        hp = 0;
		//                    show_attack_monster(LINGWUSHI.img, hp, LINGWUSHI.Attack, LINGWUSHI.Defence);
		//                    Sleep(300);
		//                    if (hp == 0)
		//                        break;
		//                }
		//                //People.hp-=LINGWUSHI.hp/(People.Attack-LINGWUSHI.Defence)*(LINGWUSHI.Attack-People.Defence);
		//                if (People.hp <= 0)
		//                    atack_monster_hp(EXCLE, x, y, temhp);
		//                else
		//                {
		//                    People.money += LINGWUSHI.money;
		//                    People.exp += LINGWUSHI.exp;
		//
		//                    map[x][y] = 0;
		//                }
		//                map[People.x][People.y] = 0;
		//                changemap();
		//                refresh();
		//                cleardevice();
		//                Show_Map();
		//            }
		//
		//        break;
		//        ///ڤսʿ
		//    case 55:
		//        if (People.Attack > MINGZHANSHI.Defence)
		//            if ((People.hp - ((MINGZHANSHI.hp / (People.Attack - MINGZHANSHI.Defence)) * (MINGZHANSHI.Attack - People.Defence))) > 0)
		//            {
		//                int temhp = 0, hp = MINGZHANSHI.hp;
		//                for (int i = 0; i < 20000; i++)
		//                {
		//                    People.hp -= MINGZHANSHI.Attack - People.Defence;
		//                    hp -= People.Attack - MINGZHANSHI.Defence;
		//                    temhp += MINGZHANSHI.Attack - People.Defence;
		//                    mciSendString("play audio\\Attack.wav", "", 0, NULL);
		//                    if (hp < 0)
		//                        hp = 0;
		//                    show_attack_monster(MINGZHANSHI.img, hp, MINGZHANSHI.Attack, MINGZHANSHI.Defence);
		//                    Sleep(300);
		//                    if (hp == 0)
		//                        break;
		//                }
		//                //People.hp-=MINGZHANSHI.hp/(People.Attack-MINGZHANSHI.Defence)*(MINGZHANSHI.Attack-People.Defence);
		//                if (People.hp <= 0)
		//                    atack_monster_hp(EXCLE, x, y, temhp);
		//                else
		//                {
		//                    People.money += MINGZHANSHI.money;
		//                    People.exp += MINGZHANSHI.exp;
		//
		//                    map[x][y] = 0;
		//                }
		//                map[People.x][People.y] = 0;
		//                changemap();
		//                refresh();
		//                cleardevice();
		//                Show_Map();
		//            }
		//
		//        break;
		//        ///�鷨ʦ
		//    case 56:
		//        if (People.Attack > LINGFASHI.Defence)
		//            if ((People.hp - ((LINGFASHI.hp / (People.Attack - LINGFASHI.Defence)) * (LINGFASHI.Attack - People.Defence))) > 0)
		//            {
		//                int temhp = 0, hp = LINGFASHI.hp;
		//                for (int i = 0; i < 20000; i++)
		//                {
		//                    People.hp -= LINGFASHI.Attack - People.Defence;
		//                    hp -= People.Attack - LINGFASHI.Defence;
		//                    temhp += LINGFASHI.Attack - People.Defence;
		//                    mciSendString("play audio\\Attack.wav", "", 0, NULL);
		//                    if (hp < 0)
		//                        hp = 0;
		//                    show_attack_monster(LINGFASHI.img, hp, LINGFASHI.Attack, LINGFASHI.Defence);
		//                    Sleep(300);
		//                    if (hp == 0)
		//                        break;
		//                }
		//                //People.hp-=LINGFASHI.hp/(People.Attack-LINGFASHI.Defence)*(LINGFASHI.Attack-People.Defence);
		//                if (People.hp <= 0)
		//                    atack_monster_hp(EXCLE, x, y, temhp);
		//                else
		//                {
		//                    People.money += LINGFASHI.money;
		//                    People.exp += LINGFASHI.exp;
		//
		//                    map[x][y] = 0;
		//                }
		//                map[People.x][People.y] = 0;
		//                changemap();
		//                refresh();
		//                cleardevice();
		//                Show_Map();
		//            }
		//
		//        break;
		//        ///ڤ�ӳ�
		//    case 57:
		//        if (People.Attack > MINGDUIZHANG.Defence)
		//            if ((People.hp - ((MINGDUIZHANG.hp / (People.Attack - MINGDUIZHANG.Defence)) * (MINGDUIZHANG.Attack - People.Defence))) > 0)
		//            {
		//                int temhp = 0, hp = MINGDUIZHANG.hp;
		//                for (int i = 0; i < 20000; i++)
		//                {
		//                    People.hp -= MINGDUIZHANG.Attack - People.Defence;
		//                    hp -= People.Attack - MINGDUIZHANG.Defence;
		//                    temhp += MINGDUIZHANG.Attack - People.Defence;
		//                    mciSendString("play audio\\Attack.wav", "", 0, NULL);
		//                    if (hp < 0)
		//                        hp = 0;
		//                    show_attack_monster(MINGDUIZHANG.img, hp, MINGDUIZHANG.Attack, MINGDUIZHANG.Defence);
		//                    Sleep(300);
		//                    if (hp == 0)
		//                        break;
		//                }
		//                //People.hp-=MINGDUIZHANG.hp/(People.Attack-MINGDUIZHANG.Defence)*(MINGDUIZHANG.Attack-People.Defence);
		//                if (People.hp <= 0)
		//                    atack_monster_hp(EXCLE, x, y, temhp);
		//                else
		//                {
		//                    People.money += MINGDUIZHANG.money;
		//                    People.exp += MINGDUIZHANG.exp;
		//
		//                    map[x][y] = 0;
		//                }
		//                map[People.x][People.y] = 0;
		//                changemap();
		//                refresh();
		//                cleardevice();
		//                Show_Map();
		//            }
		//
		//        break;
	}
}


void push_OldMan()
{
	putimage(430, 210, OldMan_PUSH[0].img);
	int a = 1;///��¼ѡ���ѡ��,��ĸe������,��ĸq������,��ĸjȷ��
	for (int i = 0; i < 20000; i++)
	{
		if (kbhit())
		{
			char b = getch();
			if (b == 'e' || b == 'E')
			{
				//mciSendString("play audio\\EXCHANGE.wav", "", 0, NULL);
				a++;
				if (a > 4)
					a = 1;
				cleardevice();
				Show_Map();
				putimage(430, 210, OldMan_PUSH[a - 1].img);
			}
			else if (b == 'q' || b == 'Q')
			{
				//mciSendString("play audio\\EXCHANGE.wav", "", 0, NULL);
				a--;
				if (a < 1)
					a = 4;
				cleardevice();
				Show_Map();
				putimage(430, 210, OldMan_PUSH[a - 1].img);
			}
			else if (b == 'j' || b == 'J')
			{
				switch (a)
				{
				case 1:
					if (People.exp > 99)
					{
						//mciSendString("play audio\\BUY.wav", "", 0, NULL);
						People.exp -= 100;
						People.hp += 800;
						People.Attack += 3;
						People.Defence += 3;
						People.level++;
					}
					else
					{
						// mciSendString("play audio\\EXCHANGE.wav", "", 0, NULL);
						setcolor(RGB(255, 255, 255));///��ɫ����
						setbkmode(TRANSPARENT);///���ֱ���͸��
						setfont(-55, 0, "����");///������
						char WORDS[40];
						strcpy(WORDS, "���鲻����");
						cleardevice();
						outtextxy(0, 0, WORDS);
						getch();
						Show_Map();
					}
					break;
				case 2:
					if (People.exp > 29)
					{
						//mciSendString("play audio\\BUY.wav", "", 0, NULL);
						People.exp -= 30;
						People.Attack += 5;
					}
					else
					{
						//mciSendString("play audio\\EXCHANGE.wav", "", 0, NULL);
						setcolor(RGB(255, 255, 255));///��ɫ����
						setbkmode(TRANSPARENT);///���ֱ���͸��
						setfont(-55, 0, "����");///������
						char WORDS[40];
						strcpy(WORDS, "���鲻��");
						cleardevice();
						outtextxy(0, 0, WORDS);
						getch();
						Show_Map();
					}
					break;
				case 3:
					if (People.exp > 29)
					{
						//mciSendString("play audio\\BUY.wav", "", 0, NULL);
						People.exp -= 30;
						People.Defence += 5;
					}
					else
					{
						//mciSendString("play audio\\EXCHANGE.wav", "", 0, NULL);
						setcolor(RGB(255, 255, 255));///��ɫ����
						setbkmode(TRANSPARENT);///���ֱ���͸��
						setfont(-55, 0, "����");///������
						char WORDS[40];
						strcpy(WORDS, "���鲻��");
						cleardevice();
						outtextxy(0, 0, WORDS);
						getch();
						Show_Map();
					}
					break;
				case 4:
					//mciSendString("play audio\\PICK.wav", "", 0, NULL);
					break;
				}
				break;
			}
		}
		Sleep(200);
	}
}
void push_RedMan()
{
	putimage(430, 210, RedMan_PUSH[0].img);
	int a = 1;///��¼ѡ���ѡ��,��ĸe������,��ĸq������,��ĸjȷ��
	for (int i = 0; i < 20000; i++)
	{
		if (kbhit())
		{
			char b = getch();
			if (b == 'e' || b == 'E')
			{
				// mciSendString("play audio\\EXCHANGE.wav", "", 0, NULL);
				a++;
				if (a > 4)
					a = 1;
				cleardevice();
				Show_Map();
				putimage(430, 210, RedMan_PUSH[a - 1].img);
			}
			else if (b == 'q' || b == 'Q')
			{
				//mciSendString("play audio\\EXCHANGE.wav", "", 0, NULL);
				a--;
				if (a < 1)
					a = 4;
				cleardevice();
				Show_Map();
				putimage(430, 210, RedMan_PUSH[a - 1].img);
			}
			else if (b == 'j' || b == 'J')
			{
				switch (a)
				{
				case 1:
					if (People.money > 9)
					{
						//mciSendString("play audio\\BUY.wav", "", 0, NULL);
						People.money -= 10;
						People.Ykey++;
					}
					else
					{
						//mciSendString("play audio\\EXCHANGE.wav", "", 0, NULL);
						setcolor(RGB(255, 255, 255));///��ɫ����
						setbkmode(TRANSPARENT);///���ֱ���͸��
						setfont(-55, 0, "����");///������
						char WORDS[40];
						strcpy(WORDS, "��Ǯ�������޷�����");
						cleardevice();
						outtextxy(0, 0, WORDS);
						getch();
						Show_Map();
					}
					break;
				case 2:
					if (People.money > 50)
					{
						//mciSendString("play audio\\BUY.wav", "", 0, NULL);
						People.money -= 50;
						People.Bkey++;
					}
					else
					{
						//mciSendString("play audio\\EXCHANGE.wav", "", 0, NULL);
						setcolor(RGB(255, 255, 255));///��ɫ����
						setbkmode(TRANSPARENT);///���ֱ���͸��
						setfont(-55, 0, "����");///������
						char WORDS[40];
						strcpy(WORDS, "��Ǯ�������޷�����");
						cleardevice();
						outtextxy(0, 0, WORDS);
						getch();
						Show_Map();
					}
					break;
				case 3:
					if (People.money > 100)
					{
						//mciSendString("play audio\\BUY.wav", "", 0, NULL);
						People.money -= 100;
						People.Rkey++;
					}
					else
					{
						//mciSendString("play audio\\EXCHANGE.wav", "", 0, NULL);
						setcolor(RGB(255, 255, 255));///��ɫ����
						setbkmode(TRANSPARENT);///���ֱ���͸��
						setfont(-55, 0, "����");///������
						char WORDS[40];
						strcpy(WORDS, "��Ǯ����");
						cleardevice();
						outtextxy(0, 0, WORDS);
						getch();
						Show_Map();
					}
					break;
				case 4:
					//mciSendString("play audio\\PICK.wav", "", 0, NULL);
					break;
				}
				break;
			}
		}
		Sleep(200);
	}
}
void push_Shop()///�������̵�
{
	putimage(430, 210, Shop_PUSH[0].img);
	int a = 1;///��¼ѡ���ѡ��,��ĸe������,��ĸq������,��ĸjȷ��
	for (int i = 0; i < 20000; i++)
	{
		if (kbhit())
		{
			char b = getch();
			if (b == 'e' || b == 'E')
			{
				//mciSendString("play audio\\EXCHANGE.wav", "", 0, NULL);
				a++;
				if (a > 4)
					a = 1;
				cleardevice();
				Show_Map();
				putimage(430, 210, Shop_PUSH[a - 1].img);
			}
			else if (b == 'q' || b == 'Q')
			{
				//mciSendString("play audio\\EXCHANGE.wav", "", 0, NULL);
				a--;
				if (a < 1)
					a = 4;
				cleardevice();
				Show_Map();
				putimage(430, 210, Shop_PUSH[a - 1].img);
			}
			else if (b == 'j' || b == 'J')
			{
				switch (a)
				{
				case 1:
					if (People.money > 24)
					{
						//mciSendString("play audio\\BUY.wav", "", 0, NULL);
						People.money -= 25;
						People.hp += 800;
					}
					else
					{
						//mciSendString("play audio\\EXCHANGE.wav", "", 0, NULL);
						setcolor(RGB(255, 255, 255));///��ɫ����
						setbkmode(TRANSPARENT);///���ֱ���͸��
						setfont(-55, 0, "����");///������
						char WORDS[40];
						strcpy(WORDS, "��Ǯ������");
						cleardevice();
						outtextxy(0, 0, WORDS);
						getch();
						Show_Map();
					}
					break;
				case 2:
					if (People.money > 24)
					{
						//mciSendString("play audio\\BUY.wav", "", 0, NULL);
						People.money -= 25;
						People.Attack += 5;
					}
					else
					{
						//mciSendString("play audio\\EXCHANGE.wav", "", 0, NULL);
						setcolor(RGB(255, 255, 255));///��ɫ����
						setbkmode(TRANSPARENT);///���ֱ���͸��
						setfont(-55, 0, "����");///������
						char WORDS[40];
						strcpy(WORDS, "��Ǯ����");
						cleardevice();
						outtextxy(0, 0, WORDS);
						getch();
						Show_Map();
					}
					break;
				case 3:
					if (People.money > 24)
					{
						//mciSendString("play audio\\BUY.wav", "", 0, NULL);
						People.money -= 25;
						People.Defence += 5;
					}
					else
					{
						//mciSendString("play audio\\EXCHANGE.wav", "", 0, NULL);
						setcolor(RGB(255, 255, 255));///��ɫ����
						setbkmode(TRANSPARENT);///���ֱ���͸��
						setfont(-55, 0, "����");///������
						char WORDS[40];
						strcpy(WORDS, "��Ǯ����");
						cleardevice();
						outtextxy(0, 0, WORDS);
						getch();
						Show_Map();
					}
					break;
				case 4:
					//mciSendString("play audio\\PICK.wav", "", 0, NULL);
					break;
				}
				break;
			}
		}
		Sleep(200);
	}
}


void VersusWindow(PIMAGE img, int hp, int attack, int def) //ս������(RPG��ʽ)
{
	putimage(300, 200, Versus.img);
	putimage(325, 240, 80, 80, img, 0, 0, 60, 60); //ͼƬ���� ��ȡ
	setcolor(RGB(255, 240, 245));				   //����
	setfont(-35, 0, "����");
	// setbkmode(TRANSPARENT);͸����������
	char HP[10], ATTACK[10], Defence[10], People_HP[10], People_ATTACK[10], People_DEF[10]; //�ַ������飬�����ӡ����
	sprintf(HP, "%d", hp);
	sprintf(ATTACK, "%d", attack);
	sprintf(Defence, "%d", def);
	sprintf(People_HP, "%d", People.hp);
	sprintf(People_DEF, "%d", People.Defence);
	sprintf(People_ATTACK, "%d", People.Attack);
	outtextxy(450, 250, HP);
	outtextxy(450, 320, ATTACK);
	outtextxy(450, 380, Defence);
	outtextxy(700, 250, People_HP);
	outtextxy(700, 320, People_ATTACK);
	outtextxy(700, 380, People_DEF);
	//������
}
//void key_down() //����
//{
//	char userkey;
//	for (int i = 0; i < 13; i++)
//	{
//		for (int j = 0; j < 13; j++)
//		{
//			if (map[i][j] == 15)
//				;
//			break;
//		}
//		if (map[i][j] == 15)
//			;
//		break;
//	}
//	userkey = getch();
//	switch (userkey)
//	{
//	case 'A':
//	case 'a':
//	case 75:
//		break;
//	case 'D':
//	case 'd':
//	case 77:
//		break;
//	case 'W':
//	case 'w':
//	case 72:
//		break;
//	case 'S':
//	case 's':
//		case 80��
//			break;
//	 }
//}
void change_state(int EXCLE, int x, int y)///EXCLE������ֵ����������ڸı�(x,y)��״̬
{
	if (map[x][y] == -2 && map_order_now == 3)///�������̵���Ϊ�����̵�ֻ�ܴ����м������-2��ʾ
	{
		//   push_SHANGDIAN();
	}
	else if (map[x][y] == -2 && map_order_now == 11)
	{
		putimage(430, 210, End.img);
		Sleep(500);
		getch();
		map[People.x][People.y] = 0;
		changemap();
		refresh();
		cleardevice();
		Show_Map();
	}


	///���°������ź͸�����ߵĻ�ȡ
	else if (map[x][y] == 3 && People.Rkey > 0)
	{
		//   mciSendString("play audio\\OPENTHEDOOR.wav","",0,NULL);
		map[x][y] = 0;
		map[People.x][People.y] = 0;
		changemap();
		refresh();
		People.Rkey--;
	}
	else if (map[x][y] == 4 && People.Ykey > 0)
	{
		//   mciSendString("play audio\\OPENTHEDOOR.wav","",0,NULL);
		map[x][y] = 0;
		map[People.x][People.y] = 0;
		changemap();
		refresh();
		People.Ykey--;
	}
	else if (map[x][y] == 5 && People.Bkey > 0)
	{
		//   mciSendString("play audio\\OPENTHEDOOR.wav","",0,NULL);
		map[x][y] = 0;
		map[People.x][People.y] = 0;
		changemap();
		refresh();
		People.Bkey--;
	}
	else if (map[x][y] == 6)
	{
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
		map[x][y] = 0;
		map[People.x][People.y] = 0;
		changemap();
		refresh();
		People.hp += 200;
	}
	else if (map[x][y] == 7)
	{
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
		map[x][y] = 0;
		map[People.x][People.y] = 0;
		changemap();
		refresh();
		People.hp += 500;
	}
	else if (map[x][y] == 8)
	{
		map[x][y] = 0;   ///��ӡʥ���ͼƬ
		putimage(260, 230, CrossEmblem_PUSH.img);
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
		Sleep(200);
		getch();
		map[People.x][People.y] = 0;
		changemap();
		refresh();
	}
	else if (map[x][y] == 9)
	{
		map[x][y] = 0;   ///��ӡ��֮����ͼƬ
		putimage(260, 230, WindOrient_PUSH.img);
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
		Sleep(200);
		getch();
		map[People.x][People.y] = 0;
		changemap();
		refresh();
	}
	else if (map[x][y] == 10)///��¥��
	{
		map_order_now++;
		refresh();
		floor_changes_role_xy();
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
	}
	else if (map[x][y] == 11)///��¥��
	{
		if (map_order_now == 1)
		{
			//  mciSendString("play audio\\PICK.wav","",0,NULL);
			setcolor(YELLOW);///��ɫ����
			setbkmode(TRANSPARENT);///���ֱ���͸��
			setfont(-55, 0, "����");///������
			char WORDS[40];
			char words[40];
			//<<<<<< < HEAD
			strcpy(WORDS, "�޷���¥��");
			//====== =
			strcpy(WORDS, "�ѵ���1���޷���¥��������");
			strcpy(words, "��������Ϸ��");
			//>>>>>> > parent of b2f4824... Update main.cpp
			outtextxy(340, 340, WORDS);
			outtextxy(500, 420, words);
			Sleep(200);
			getch();
			cleardevice();
			Show_Map();
		}
		else
		{
			map_order_now--;
			refresh();
			floor_changes_role_xy();
			//  mciSendString("play audio\\PICK.wav","",0,NULL);
		}
	}
	else if (map[x][y] == 12)
	{
		map[x][y] = 0;
		map[People.x][People.y] = 0;
		changemap();
		refresh();
		People.Ykey++;
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
	}
	else if (map[x][y] == 13)
	{
		map[x][y] = 0;
		map[People.x][People.y] = 0;
		changemap();
		refresh();
		People.Rkey++;
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
	}
	else if (map[x][y] == 14)
	{
		map[x][y] = 0;
		map[People.x][People.y] = 0;
		changemap();
		refresh();
		People.Bkey++;
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
	}
	else if (map[x][y] == 16)
	{
		map[x][y] = 0;
		map[People.x][People.y] = 0;
		changemap();
		refresh();
		People.Attack += 3;
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
	}
	else if (map[x][y] == 17)
	{
		map[x][y] = 0;
		map[People.x][People.y] = 0;
		changemap();
		refresh();
		People.Defence += 3;
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
	}
	else if (map[x][y] == 21 && map_order_now == 2)
	{
		map[x][y] = 0;
		map[People.x][People.y] = 0;
		changemap();
		refresh();
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
		setcolor(YELLOW);///��ɫ����
		setbkmode(TRANSPARENT);///���ֱ���͸��
		setfont(-55, 0, "����");///������
		char WORDS[40];
		strcpy(WORDS, "��ý���������60��");
		outtextxy(340, 340, WORDS);
		Sleep(200);
		getch();
		cleardevice();
		People.Attack += 60;
		Show_Map();
	}///��¥��Ϊ2ʱ�ð׷�������ʧ(�Ѿ��ĳ�һ�ѽ�)
	else if (map[x][y] == 18 && map_order_now == 5)
	{
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
	//      push_BAIFALAOREN();
	}///��¥��Ϊ5ʱ�����׷����˹���˵�
	else if (map[x][y] == 25 && map_order_now == 2)
	{
		map[x][y] = 0;
		map[People.x][People.y] = 0;
		changemap();
		refresh();
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
		setcolor(YELLOW);///��ɫ����
		setbkmode(TRANSPARENT);///���ֱ���͸��
		setfont(-55, 0, "����");///������
		char WORDS[40];
		strcpy(WORDS, "��öܣ�������60��");
		outtextxy(340, 340, WORDS);
		Sleep(200);
		getch();
		cleardevice();
		People.Defence += 60;
		Show_Map();
	}///��¥��Ϊ2ʱ�ú���������ʧ(�Ѿ��ĳ�һ����)
	else if (map[x][y] == 19 && map_order_now == 5)
	{
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
		 // push_HONGYILAOREN();
	}///��¥��Ϊ5ʱ�����������˹���˵�
	else if (map[x][y] == 20)
	{
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
		setcolor(YELLOW);///��ɫ����
		setbkmode(TRANSPARENT);///���ֱ���͸��
		setfont(-55, 0, "����");///������
		char WORDS[40];
		strcpy(WORDS, "��û�д򿪴��ŵ�Կ�ף�");
		outtextxy(350, 350, WORDS);
		Sleep(200);
		getch();
		cleardevice();
		Show_Map();
		///���������޶���
	}
	else if (map[x][y] == 21 && map_order_now == 3)///������ı���
	{
		map[x][y] = 0;
		map[People.x][People.y] = 0;
		changemap();
		refresh();
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
		People.Attack += 10;
		setcolor(YELLOW);///��ɫ����
		setbkmode(TRANSPARENT);///���ֱ���͸��
		setfont(-55, 0, "����");///������
		char WORDS[40];
		strcpy(WORDS, "ȡ�ñ�������������10��");
		outtextxy(350, 350, WORDS);
		Sleep(200);
		getch();
		cleardevice();
		Show_Map();
	}
	else if (map[x][y] == 21 && map_order_now == 9)///�ھŲ�ı���
	{
		map[x][y] = 0;
		map[People.x][People.y] = 0;
		changemap();
		refresh();
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
		People.Attack += 60;
		setcolor(YELLOW);///��ɫ����
		setbkmode(TRANSPARENT);///���ֱ���͸��
		setfont(-55, 0, "����");///������
		char WORDS[40];
		strcpy(WORDS, "ȡ�ô󱦽�����������60��");
		outtextxy(350, 350, WORDS);
		Sleep(200);
		getch();
		cleardevice();
		Show_Map();
	}
	else if (map[x][y] == 23 && Warrior.hp == 0)///��ʿ
	{
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
		//   push_YONGSHI();
	}
	else if (map[x][y] == 24)///��Կ��
	{
		map[x][y] = 0;
		map[People.x][People.y] = 0;
		changemap();
		refresh();
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
		People.Attack += 10;
		setcolor(YELLOW);///��ɫ����
		setbkmode(TRANSPARENT);///���ֱ���͸��
		setfont(-55, 0, "����");///������
		char WORDS[40];
		strcpy(WORDS, "ȡ�ý�Կ�ף�ÿ��Կ��������1��");
		outtextxy(340, 340, WORDS);
		Sleep(200);
		getch();
		cleardevice();
		People.Rkey++;
		People.Bkey++;
		People.Ykey++;
		Show_Map();
	}
	else if (map[x][y] == 25 && map_order_now == 5)
	{
		map[x][y] = 0;
		map[People.x][People.y] = 0;
		changemap();
		refresh();
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
		People.Defence += 10;
		setcolor(YELLOW);///��ɫ����
		setbkmode(TRANSPARENT);///���ֱ���͸��
		setfont(-55, 0, "����");///������
		char WORDS[40];
		strcpy(WORDS, "ȡ�ö��ƣ���������10��");
		outtextxy(350, 350, WORDS);
		Sleep(200);
		getch();
		cleardevice();
		Show_Map();
	}
	else if (map[x][y] == 26)
	{
		map[x][y] = 0;
		map[People.x][People.y] = 0;
		changemap();
		refresh();
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
		People.level += 1;
		People.hp += 800;
		People.Attack += 3;
		People.Defence += 3;
		setcolor(YELLOW);///��ɫ����
		setbkmode(TRANSPARENT);///���ֱ���͸��
		setfont(-55, 0, "����");///������
		char WORDS[40];
		strcpy(WORDS, "ȡ�õȼ���򣡵ȼ���1����");
		outtextxy(350, 350, WORDS);
		Sleep(200);
		getch();
		cleardevice();
		Show_Map();
	}
	else if (map[x][y] == 27)
	{
		map[x][y] = 0;
		map[People.x][People.y] = 0;
		changemap();
		refresh();
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
		People.money += 300;
		setcolor(YELLOW);///��ɫ����
		setbkmode(TRANSPARENT);///���ֱ���͸��
		setfont(-55, 0, "����");///������
		char WORDS[40];
		strcpy(WORDS, "ȡ�ÿ��Ľ�ң���Ҽ�300��");
		outtextxy(350, 350, WORDS);
		Sleep(200);
		getch();
		cleardevice();
		Show_Map();
	}
	else if (map[x][y] == 28)
	{
		map[x][y] = 0;
		map[People.x][People.y] = 0;
		changemap();
		refresh();
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
		People.hp *= 1.5;
		People.Attack *= 1.5;
		People.Defence *= 1.5;
		setcolor(YELLOW);///��ɫ����
		setbkmode(TRANSPARENT);///���ֱ���͸��
		setfont(-55, 0, "����");///������
		char WORDS[40];
		char words[40];
		strcpy(WORDS, "���ʮ�ּܣ��������Ա�Ϊ");
		strcpy(words, "ԭ����1.5��!");
		outtextxy(340, 340, WORDS);
		outtextxy(500, 420, words);
		Sleep(200);
		getch();
		cleardevice();
		Show_Map();
	}
	else if (map[x][y] == 29)
	{
		map[x][y] = 0;
		map[People.x][People.y] = 0;
		changemap();
		refresh();
		//   mciSendString("play audio\\PICK.wav","",0,NULL);
		People.level += 3;
		People.hp += 2400;
		People.Attack += 9;
		People.Defence += 9;
		setcolor(YELLOW);///��ɫ����
		setbkmode(TRANSPARENT);///���ֱ���͸��
		setfont(-55, 0, "����");///������
		char WORDS[40];
		strcpy(WORDS, "ȡ�þ���У��ȼ���3����");
		outtextxy(350, 350, WORDS);
		Sleep(200);
		getch();
		cleardevice();
		Show_Map();
	}
	///����ֻ��������Լ����ô�ֺ���
	else if (map[x][y] == 1);///ײ͸��ǽ
	else
		atack_monster(EXCLE, x, y);

}
/*�߼���1���ж�����ǰ����ʲô
		2�����������ƶ� ͼƬ�ı䣨ʵʱ��
		3��ԭλ��ͼƬ�ָ�Ϊ1
		*/
void control_move()
{
	changemap();

	if (kbhit())
	{
		char userkey;
		// for (int i = 0; i <13;i++)
		// {
		// 	for (int j =0;j<13;j++)
		// 		{
		// 			if (map[i][j]==15);
		// 			break;
		// 		}
		// 	if (map[i][j]==15);
		// 			break;
		// }
		userkey = getch();
		switch (userkey)
		{
		case 'A':
		case 'a':
			// case 75:
			if (map[People.x][People.y - 1] == 0)
			{
				People.y -= 1;
				getimage(People.img, "picture1/actorL.png");
			}
			else
			{
				change_state(get_x_y(People.x, People.y - 1), People.x, People.y - 1);
			}

			break;
		case 'D':
		case 'd':
			// case 77:
			if (map[People.x][People.y + 1] == 0)
			{
				People.y += 1;
				getimage(People.img, "picture1/actorR.png");
			}
			else
			{
				change_state(get_x_y(People.x, People.y + 1), People.x, People.y + 1);
			}

			break;
		case 'W':
		case 'w':
			// case 72:
			if (map[People.x - 1][People.y] == 0)
			{
				People.x -= 1;
				getimage(People.img, "picture1/actorB.png");
			}
			else
			{
				change_state(get_x_y(People.x - 1, People.y), People.x - 1, People.y);
			}
			break;
		case 'S':
		case 's':
			// case 80:
			if (map[People.x + 1][People.y] == 0)
			{
				People.x += 1;
				getimage(People.img, "picture1/actor.png");
			}
			else
			{
				change_state(get_x_y(People.x + 1, People.y), People.x + 1, People.y);
			}

			break;
		}


	}
	Show_Map();
}
void Enter_Or_Not()
{
	setcolor(RED);
	setfont(100,50, "����");
	outtextxy(400, 200, "Wanna play Magic Tower? Y OR N");

	while (!kbhit())
	{
		char ch;
		ch = getch();
		if (ch == 'Y')
			break;
		else if (ch == 'N')
			closegraph();
	}
}
int main()
{
	initgraph(1080, 780); //�������� 1080*780 ege�⺯��
	setcaption("Magic_Tower");
	initImage();
	InitEnemy();
	changemap();
	floor_changes_role_xy();
	Enter_Or_Not();

	while (1)
	{



		control_move();
		Sleep(60);
	}
	//getch();
	closegraph(); //���ڹر� ege�⺯��
	return 0;
}
