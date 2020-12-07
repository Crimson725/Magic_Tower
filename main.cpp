/*version1
1、窗口
2、素材导入
定义变量：IMAGE img
变量赋值：loadimage(&img,"路径")
图片显示:putimage(int x,int y,&img)
地图：使用二维数组
3、交互（上下左右，触碰）
4、关卡优化*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h> //来自ege库
#include <conio.h>
#include <string>

FILE *fp; //全局文件指针
int map_order_now = 1;
int map_order_pre = 0; //地图参数 当前为1 前一地图为0 随关卡进行自增

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
}; //初始地图 地图1
typedef struct
{
	int Map[13][13];
} MAP;
MAP M[15]; //十五层地图（临时）

int map1[13][13];
typedef struct Actor
{
	char name[20] = "打工人"; //名称; //名称
	int level = 1;			  //初始等级
	int hp = 1000;			  //初始血量
	int Attack = 30;		  //初始攻击力
	int Defence = 30;		  ///初始防御力
	int money = 0;			  //初始金钱
	int exp = 0;			  //初始经验
	int x;					  //位置坐标x
	int y;					  //位置坐标y
	int Ykey = 1;			  //黄钥匙 初始为1
	int Rkey = 1;			  //红钥匙 初始为1
	int Bkey = 1;			  //蓝钥匙 初始为1
	PIMAGE img;				  //角色对象图片
} role, actor;				  //全局结构体 玩家角色
typedef struct Object
{
	char name[20] = {0};
	int hp;		 //血量
	int exp;	 //经验值
	int Attack;	 //攻击力
	int Defence; //防御力
	int money;	 //金钱
	int x;		 //x坐标
	int y;		 //y坐标
	PIMAGE img;	 //对象图片
} enemy, object, actors, background;
typedef struct PUSH
{
	PIMAGE img;
	//img_index;
} push;
enemy GreenSlime, RedSlime, BlackSlime; //敌人 史莱姆类
enemy BigBat, SmallBat, RedBat;			//敌人 蝙蝠类
enemy Witch_1, Witch_2;					//敌人 巫师类
enemy Guard_1, Guard_2, Guard_3;		//敌人 卫兵类
enemy BoneMan, BoneGuard, BoneWarrior;	//敌人 骷髅类
enemy GBoss, MonsterKing, RBoss;		//敌人 Boss类
enemy Orc, OrcWarrior;
enemy StoneMan;																																	   //敌人 兽人类
actors OldMan, SwordMan, Warrior, Witch_R, Witch_Y, WhiteWitch, RedMan;																			   //任务 角色类
object RKey, BKey, YKey, GKey, Sword, Shield, TreasureBox, WindOrient, GoldCoin, Level_Up, Cross, CrossEmblem, HP, BigHP, BlueDiamond, RedDiamond; //道具类
background Background, Block, Floor, Wall, YellowDoor, GreenDoor, RedDoor, BlueDoor, Upstairs, Downstairs, Shop, Stars;							   //地图 背景模块类
role People;																																	   //主角
push CrossEmblem_PUSH, Shop_PUSH[4], Versus, Warrior_PUSH[16], OldMan_PUSH[4], RedMan_PUSH[4], WindOrient_PUSH, End;							   //弹出窗口类
//地图切换核心函数（待完善）
void changemap()
{
	memcpy(M[map_order_now - 1].Map, map, sizeof(map)); //string.h 函数 地图切换函数
}
//人物位置切换核心函数(待完善)

void refresh()
{
	memcpy(map1, M[map_order_now - 1].Map, sizeof(map));
}
//刷新函数，待研究
int get_x_y(int x, int y)
{
	return map[x][y];
}
void floor_changes_role_xy() //不同层楼之间的任务地图切换(初始位置待定）
{
	if (map_order_now >= map_order_pre) ///上楼情况
		switch (map_order_now)
		{
		case 1: ///上楼到1楼(或初始化开局)
			People.x = 10;
			People.y = 6;
			break;
		case 2: ///上楼到2楼
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
	else ///下楼情况
		switch (map_order_now)
		{
		case 1: ///下楼到1楼
			People.x = 1;
			People.y = 2;
			break;
		case 2: ///下楼到2楼
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
	Sleep(300); ///去除上下楼无限换图BUG
	map_order_pre = map_order_now;
	//refresh();
}

void initImage() //图像初始化函数
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
	//弹窗
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
	//获取图像
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
	//弹窗图片
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
void InitEnemy() //敌人角色初始化
{
	//绿史莱姆
	GreenSlime.hp = 200;
	GreenSlime.Attack = 35;
	GreenSlime.Defence = 10;
	GreenSlime.exp = 5;
	GreenSlime.money = 5;
	strcpy(GreenSlime.name, "绿史莱姆");
	//红史莱姆
	RedSlime.hp = 70;
	RedSlime.Attack = 15;
	RedSlime.Defence = 2;
	RedSlime.exp = 5;
	RedSlime.money = 5;
	strcpy(RedSlime.name, "红史莱姆");
	//黑史莱姆
	BlackSlime.hp = 50;
	BlackSlime.Attack = 10;
	BlackSlime.Defence = 1;
	BlackSlime.exp = 3;
	BlackSlime.money = 3;
	strcpy(BlackSlime.name, "黑史莱姆");
	//骷髅
	BoneMan.hp = 5;
	BoneMan.Attack = 25;
	BoneMan.Defence = 10;
	BoneMan.money = 5;
	BoneMan.exp = 5;
	strcpy(BoneMan.name, "骷髅人");
	//骷髅士兵
	BoneWarrior.hp = 150;
	BoneWarrior.Attack = 40;
	BoneWarrior.Defence = 20;
	BoneWarrior.money = 20;
	BoneWarrior.exp = 20;
	strcpy(BoneWarrior.name, "骷髅士兵");
	//骷髅卫士
	BoneGuard.hp = 300;
	BoneGuard.Attack = 50;
	BoneGuard.Defence = 30;
	BoneGuard.money = 50;
	BoneGuard.exp = 40;
	strcpy(BoneGuard.name, "骷髅卫士");
	//初级法师
	Witch_1.hp = 10;
	Witch_1.money = 25;
	Witch_1.Attack = 50;
	Witch_1.exp = 10;
	strcpy(Witch_1.name, "初级法师");
	//高级法师
	Witch_2.hp = 100;
	Witch_2.Attack = 200;
	Witch_2.Defence = 100;
	Witch_2.money = 100;
	Witch_2.exp = 55;
	strcpy(Witch_2.name, "高级法师");
	//红衣法师
	Witch_R.hp = 500;
	Witch_R.Attack = 400;
	Witch_R.Defence = 250;
	Witch_R.money = 120;
	Witch_R.exp = 100;
	strcpy(Witch_R.name, "红衣法师");
	//黄衣法师
	Witch_Y.hp = 250;
	Witch_Y.Attack = 300;
	Witch_Y.Defence = 150;
	Witch_Y.money = 100;
	Witch_Y.exp = 80;
	strcpy(Witch_Y.name, "黄衣法师");
	//小蝙蝠
	SmallBat.hp = 80;
	SmallBat.Attack = 20;
	SmallBat.Defence = 10;
	SmallBat.exp = 5;
	SmallBat.money = 5;
	strcpy(SmallBat.name, "小蝙蝠");
	//大蝙蝠
	BigBat.hp = 150;
	BigBat.Attack = 55;
	BigBat.Defence = 20;
	BigBat.money = 15;
	BigBat.exp = 15;
	strcpy(BigBat.name, "大蝙蝠");
	//红蝙蝠
	RedBat.hp = 200;
	RedBat.Attack = 150;
	RedBat.Defence = 60;
	RedBat.money = 30;
	RedBat.exp = 30;
	strcpy(RedBat.name, "红蝙蝠");
	//兽人
	Orc.hp = 250;
	Orc.Attack = 80;
	Orc.Defence = 60;
	Orc.money = 30;
	Orc.exp = 20;
	strcpy(Orc.name, "兽人");
	//兽人战士
	OrcWarrior.hp = 800;
	OrcWarrior.Attack = 300;
	OrcWarrior.Defence = 300;
	OrcWarrior.money = 100;
	OrcWarrior.exp = 80;
	strcpy(OrcWarrior.name, "兽人战士");
	//石头人
	StoneMan.hp = 2000;
	StoneMan.Attack = 20;
	StoneMan.Defence = 600;
	StoneMan.exp = 100;
	StoneMan.money = 100;
	strcpy(StoneMan.name, "石头人");
	//初级卫兵
	Guard_1.hp = 200;
	Guard_1.Attack = 100;
	Guard_1.Defence = 100;
	Guard_1.exp = 30;
	Guard_1.money = 30;
	strcpy(Guard_1.name, "初级卫兵");
	//高级卫兵
	Guard_2.hp = 200;
	Guard_2.Attack = 400;
	Guard_2.Defence = 200;
	Guard_2.exp = 50;
	Guard_2.money = 60;
	strcpy(Guard_2.name, "高级卫兵");
	//高级武士
	Guard_3.hp = 1200;
	Guard_3.Attack = 600;
	Guard_3.Defence = 400;
	Guard_3.exp = 100;
	Guard_3.money = 200;
	strcpy(Guard_3.name, "高级武士");
	//红色队长
	RBoss.hp = 2000;
	RBoss.Attack = 800;
	RBoss.Defence = 1000;
	RBoss.exp = 300;
	RBoss.money = 300;
	strcpy(RBoss.name, "红色队长");
	//金色队长
	GBoss.hp = 1500;
	GBoss.Attack = 1200;
	GBoss.Defence = 1000;
	GBoss.exp = 300;
	GBoss.money = 300;
	strcpy(GBoss.name, "金色队长");
	//剑士
	SwordMan.hp = 1000;
	SwordMan.Attack = 2500;
	SwordMan.Defence = 300;
	SwordMan.exp = 200;
	SwordMan.money = 400;
	strcpy(SwordMan.name, "剑士");
	//白衣巫师
	WhiteWitch.hp = 1500;
	WhiteWitch.Attack = 2000;
	WhiteWitch.Defence = 200;
	WhiteWitch.exp = 200;
	WhiteWitch.money = 400;
	strcpy(WhiteWitch.name, "白衣巫师");
	//史莱姆王
	MonsterKing.hp = 800;
	MonsterKing.Attack = 200;
	MonsterKing.Defence = 200;
	MonsterKing.exp = 50;
	MonsterKing.money = 30;
	strcpy(MonsterKing.name, "史莱姆王");
}
void Show_Map()
{
	//memcpy(map, map1, sizeof(map));
	map[People.x][People.y] = 15;
	putimage(0, 0, Background.img);

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
		///人物属性栏打印
		setcolor(RGB(255, 255, 255)); ///白色文字
		setbkmode(TRANSPARENT);		  ///文字背景透明
		setfont(-55, 0, "宋体");	  ///黑体字
		char YELLOWKEYNUM[3], REDKEYNUM[3], LEVELNUM[3], BLUEKEYNUM[3], ATACKNUM[5], HPNUM[10], EXNUM[5], MONEYNUM[5], DEFNUM[5];
		sprintf(YELLOWKEYNUM, "%d", People.Ykey); ///头文件cstdio或stdio.h
		sprintf(REDKEYNUM, "%d", People.Rkey);
		sprintf(BLUEKEYNUM, "%d", People.Bkey);
		sprintf(LEVELNUM, "%d", People.level);
		sprintf(ATACKNUM, "%d", People.Attack);
		sprintf(HPNUM, "%d", People.hp);
		sprintf(EXNUM, "%d", People.exp);
		sprintf(MONEYNUM, "%d", People.money);
		sprintf(DEFNUM, "%d", People.Defence);
		outtextxy(210, 405, YELLOWKEYNUM); ///黄钥匙打印
		outtextxy(210, 530, REDKEYNUM);	   ///红钥匙打印
		outtextxy(210, 465, BLUEKEYNUM);   ///蓝钥匙打印
		outtextxy(210, 90, LEVELNUM);	   ///等级打印
		setfont(-35, 0, "宋体");		   ///字体变小
		outtextxy(210, 165, HPNUM);		   ///血量打印
		outtextxy(210, 208, ATACKNUM);	   ///攻击力打印
		outtextxy(210, 250, DEFNUM);	   ///防御力打印
		outtextxy(210, 295, MONEYNUM);	   ///金钱打印
		outtextxy(210, 340, EXNUM);		   ///经验打印
	}
}

void push_OldMan()
{
    putimage(430, 210, OldMan_PUSH[0].img);
    int a = 1;///记录选择的选项,字母e往下走,字母q往上走,字母j确定
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
                show_map();
                putimage(430, 210, OldMan_PUSH[a - 1].img);
            }
            else if (b == 'q' || b == 'Q')
            {
                //mciSendString("play audio\\EXCHANGE.wav", "", 0, NULL);
                a--;
                if (a < 1)
                    a = 4;
                cleardevice();
                show_map();
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
                        setcolor(RGB(255, 255, 255));///白色文字
                        setbkmode(TRANSPARENT);///文字背景透明
                        setfont(-55, 0, "黑体");///黑体字
                        char WORDS[40];
                        strcpy(WORDS, "经验不够！");
                        cleardevice();
                        outtextxy(0, 0, WORDS);
                        getch();
                        show_map();
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
                        setcolor(RGB(255, 255, 255));///白色文字
                        setbkmode(TRANSPARENT);///文字背景透明
                        setfont(-55, 0, "黑体");///黑体字
                        char WORDS[40];
                        strcpy(WORDS, "经验不够");
                        cleardevice();
                        outtextxy(0, 0, WORDS);
                        getch();
                        show_map();
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
                        setcolor(RGB(255, 255, 255));///白色文字
                        setbkmode(TRANSPARENT);///文字背景透明
                        setfont(-55, 0, "黑体");///黑体字
                        char WORDS[40];
                        strcpy(WORDS, "经验不够");
                        cleardevice();
                        outtextxy(0, 0, WORDS);
                        getch();
                        show_map();
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
    int a = 1;///记录选择的选项,字母e往下走,字母q往上走,字母j确定
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
                show_map();
                putimage(430, 210, RedMan_PUSH[a - 1].img);
            }
            else if (b == 'q' || b == 'Q')
            {
                //mciSendString("play audio\\EXCHANGE.wav", "", 0, NULL);
                a--;
                if (a < 1)
                    a = 4;
                cleardevice();
                show_map();
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
                        setcolor(RGB(255, 255, 255));///白色文字
                        setbkmode(TRANSPARENT);///文字背景透明
                        setfont(-55, 0, "黑体");///黑体字
                        char WORDS[40];
                        strcpy(WORDS, "金钱不够！");
                        cleardevice();
                        outtextxy(0, 0, WORDS);
                        getch();
                        show_map();
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
                        setcolor(RGB(255, 255, 255));///白色文字
                        setbkmode(TRANSPARENT);///文字背景透明
                        setfont(-55, 0, "黑体");///黑体字
                        char WORDS[40];
                        strcpy(WORDS, "金钱不够");
                        cleardevice();
                        outtextxy(0, 0, WORDS);
                        getch();
                        show_map();
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
                        setcolor(RGB(255, 255, 255));///白色文字
                        setbkmode(TRANSPARENT);///文字背景透明
                        setfont(-55, 0, "黑体");///黑体字
                        char WORDS[40];
                        strcpy(WORDS, "金钱不够");
                        cleardevice();
                        outtextxy(0, 0, WORDS);
                        getch();
                        show_map();
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
void push_Shop()///第三层商店
{
    putimage(430, 210, Shop_PUSH[0].img);
    int a = 1;///记录选择的选项,字母e往下走,字母q往上走,字母j确定
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
                show_map();
                putimage(430, 210, Shop_PUSH[a - 1].img);
            }
            else if (b == 'q' || b == 'Q')
            {
                //mciSendString("play audio\\EXCHANGE.wav", "", 0, NULL);
                a--;
                if (a < 1)
                    a = 4;
                cleardevice();
                show_map();
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
                        setcolor(RGB(255, 255, 255));///白色文字
                        setbkmode(TRANSPARENT);///文字背景透明
                        setfont(-55, 0, "黑体");///黑体字
                        char WORDS[40];
                        strcpy(WORDS, "金钱不够！");
                        cleardevice();
                        outtextxy(0, 0, WORDS);
                        getch();
                        show_map();
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
                        setcolor(RGB(255, 255, 255));///白色文字
                        setbkmode(TRANSPARENT);///文字背景透明
                        setfont(-55, 0, "黑体");///黑体字
                        char WORDS[40];
                        strcpy(WORDS, "金钱不够");
                        cleardevice();
                        outtextxy(0, 0, WORDS);
                        getch();
                        show_map();
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
                        setcolor(RGB(255, 255, 255));///白色文字
                        setbkmode(TRANSPARENT);///文字背景透明
                        setfont(-55, 0, "黑体");///黑体字
                        char WORDS[40];
                        strcpy(WORDS, "金钱不够");
                        cleardevice();
                        outtextxy(0, 0, WORDS);
                        getch();
                        show_map();
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


void VersusWindow(PIMAGE img, int hp, int attack, int def) //战斗界面(RPG形式)
{
	putimage(300, 200, Versus.img);
	putimage(325, 240, 80, 80, img, 0, 0, 60, 60); //图片放置 截取
	setcolor(RGB(255, 240, 245));				   //淡红
	setfont(-35, 0, "楷体");
	// setbkmode(TRANSPARENT);透明背景文字
	char HP[10], ATTACK[10], Defence[10], People_HP[10], People_ATTACK[10], People_DEF[10]; //字符型数组，定义打印内容
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
	//待测试
}
//void key_down() //备用
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
//		case 80：
//			break;
//	 }
//}
void change_state(int EXCLE,int x,int y)///EXCLE代表标号值这个函数用于改变(x,y)的状态
{
   ///以下商店调用函数
   if(map[x][y] == -2 && map_order_now == 3)///第三层商店因为访问商店只能从正中间访问用-2表示
   {
    //   push_SHANGDIAN();
   }
   else if(map[x][y] == -2 && map_order_now == 11)
   {
      putimage(430,210,End.img);
      Sleep(500);
      getch();
      map[People.x][People.y] = 0;
    //   change_map();
      refresh();
      cleardevice();
      Show_Map();
   }


   ///以下包含开门和各类道具的获取
   else if(map[x][y] == 3 && People.Rkey>0)
   {
    //   mciSendString("play audio\\OPENTHEDOOR.wav","",0,NULL);
      map[x][y] = 0;
      map[People.x][People.y] = 0;
    //   change_map();
      refresh();
      People.Rkey--;
   }
   else if(map[x][y] == 4 && People.Ykey>0)
   {
    //   mciSendString("play audio\\OPENTHEDOOR.wav","",0,NULL);
      map[x][y] = 0;
      map[People.x][People.y] = 0;
    //   change_map();
      refresh();
      People.Ykey--;
   }
   else if(map[x][y] == 5 && People.Bkey>0)
   {
    //   mciSendString("play audio\\OPENTHEDOOR.wav","",0,NULL);
      map[x][y] = 0;
      map[People.x][People.y] = 0;
    //   change_map();
      refresh();
      People.Bkey--;
   }
   else if(map[x][y] == 6)
   {
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
      map[x][y] = 0;
      map[People.x][People.y] = 0;
    //   change_map();
      refresh();
      People.hp+=200;
   }
   else if(map[x][y] == 7)
   {
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
      map[x][y] = 0;
      map[People.x][People.y] = 0;
    //   change_map();
      refresh();
      People.hp+=500;
   }
   else if(map[x][y] == 8)
   {
      map[x][y] = 0;   ///打印圣光徽图片
      putimage(260,230,CrossEmblem_PUSH.img);
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
      Sleep(200);
      getch();
      map[People.x][People.y] = 0;
    //   change_map();
      refresh();
   }
   else if(map[x][y] == 9)
   {
      map[x][y] = 0;   ///打印风之罗盘图片
      putimage(260,230,WindOrient_PUSH.img);
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
      Sleep(200);
      getch();
      map[People.x][People.y] = 0;
    //   change_map();
      refresh();
   }
   else if(map[x][y] == 10)///上楼梯
   {
      map_order_now++;
      refresh();
      floor_changes_role_xy();
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
   }
   else if(map[x][y] == 11)///下楼梯
   {
      if(map_order_now == 1)
      {
        //  mciSendString("play audio\\PICK.wav","",0,NULL);
         setcolor(YELLOW);///白色文字
         setbkmode(TRANSPARENT);///文字背景透明
         setfont(-55,0,"黑体");///黑体字
         char WORDS[40];
         char words[40];
         strcpy(WORDS,"已到第1层无法下楼！按任意");
         strcpy(words,"键返回游戏！");
         outtextxy(340,340,WORDS);
         outtextxy(500,420,words);
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
   else if(map[x][y] == 12)
   {
      map[x][y] = 0;
      map[People.x][People.y] = 0;
    //   change_map();
      refresh();
      People.Ykey++;
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
   }
   else if(map[x][y] == 13)
   {
      map[x][y] = 0;
      map[People.x][People.y] = 0;
    //   change_map();
      refresh();
      People.Rkey++;
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
   }
   else if(map[x][y] == 14)
   {
      map[x][y] = 0;
      map[People.x][People.y] = 0;
    //   change_map();
      refresh();
      People.Bkey++;
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
   }
   else if(map[x][y] == 16)
   {
      map[x][y] = 0;
      map[People.x][People.y] = 0;
    //   change_map();
      refresh();
      People.Attack+=3;
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
   }
   else if(map[x][y] == 17)
   {
      map[x][y] = 0;
      map[People.x][People.y] = 0;
    //   change_map();
      refresh();
      People.Defence+=3;
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
   }
   else if(map[x][y] == 21 && map_order_now == 2)
   {
      map[x][y] = 0;
      map[People.x][People.y] = 0;
    //   change_map();
      refresh();
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
      setcolor(YELLOW);///白色文字
      setbkmode(TRANSPARENT);///文字背景透明
      setfont(-55,0,"黑体");///黑体字
      char WORDS[40];
      strcpy(WORDS,"获得剑！攻击加60！");
      outtextxy(340,340,WORDS);
      Sleep(200);
      getch();
      cleardevice();
      People.Attack+=60;
      Show_Map();
   }///当楼层为2时让白发老人消失(已经改成一把剑)
   else if(map[x][y] == 18 && map_order_now == 5)
   {
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
//      push_BAIFALAOREN();
   }///当楼层为5时弹出白发老人购买菜单
   else if(map[x][y] == 25 && map_order_now == 2)
   {
      map[x][y] = 0;
      map[People.x][People.y] = 0;
    //   change_map();
      refresh();
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
      setcolor(YELLOW);///白色文字
      setbkmode(TRANSPARENT);///文字背景透明
      setfont(-55,0,"黑体");///黑体字
      char WORDS[40];
      strcpy(WORDS,"获得盾！防御加60！");
      outtextxy(340,340,WORDS);
      Sleep(200);
      getch();
      cleardevice();
      People.Defence+=60;
      Show_Map();
   }///当楼层为2时让红衣老人消失(已经改成一盾牌)
   else if(map[x][y] == 19 && map_order_now == 5)
   {
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
     // push_HONGYILAOREN();
   }///当楼层为5时弹出红衣老人购买菜单
   else if(map[x][y] == 20)
   {
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
      setcolor(YELLOW);///白色文字
      setbkmode(TRANSPARENT);///文字背景透明
      setfont(-55,0,"黑体");///黑体字
      char WORDS[40];
      strcpy(WORDS,"你没有打开此门的钥匙！");
      outtextxy(350,350,WORDS);
      Sleep(200);
      getch();
      cleardevice();
      Show_Map();
      ///碰到青门无动作
   }
   else if(map[x][y] == 21 && map_order_now == 3)///第三层的宝剑
   {
      map[x][y] = 0;
      map[People.x][People.y] = 0;
    //   change_map();
      refresh();
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
      People.Attack+=10;
      setcolor(YELLOW);///白色文字
      setbkmode(TRANSPARENT);///文字背景透明
      setfont(-55,0,"黑体");///黑体字
      char WORDS[40];
      strcpy(WORDS,"取得宝剑！攻击力加10！");
      outtextxy(350,350,WORDS);
      Sleep(200);
      getch();
      cleardevice();
      Show_Map();
   }
   else if(map[x][y] == 21 && map_order_now == 9)///第九层的宝剑
   {
      map[x][y] = 0;
      map[People.x][People.y] = 0;
    //   change_map();
      refresh();
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
      People.Attack+=60;
      setcolor(YELLOW);///白色文字
      setbkmode(TRANSPARENT);///文字背景透明
      setfont(-55,0,"黑体");///黑体字
      char WORDS[40];
      strcpy(WORDS,"取得大宝剑！攻击力加60！");
      outtextxy(350,350,WORDS);
      Sleep(200);
      getch();
      cleardevice();
      Show_Map();
   }
   else if(map[x][y] == 23 && Warrior.hp == 0)///勇士
   {
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
    //   push_YONGSHI();
   }
   else if(map[x][y] == 24)///金钥匙
   {
      map[x][y] = 0;
      map[People.x][People.y] = 0;
    //   change_map();
      refresh();
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
      People.Attack+=10;
      setcolor(YELLOW);///白色文字
      setbkmode(TRANSPARENT);///文字背景透明
      setfont(-55,0,"黑体");///黑体字
      char WORDS[40];
      strcpy(WORDS,"取得金钥匙！每种钥匙数量加1！");
      outtextxy(340,340,WORDS);
      Sleep(200);
      getch();
      cleardevice();
      People.Rkey++;
      People.Bkey++;
      People.Ykey++;
      Show_Map();
   }
   else if(map[x][y] == 25 && map_order_now == 5)
   {
      map[x][y] = 0;
      map[People.x][People.y] = 0;
    //   change_map();
      refresh();
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
      People.Defence+=10;
      setcolor(YELLOW);///白色文字
      setbkmode(TRANSPARENT);///文字背景透明
      setfont(-55,0,"黑体");///黑体字
      char WORDS[40];
      strcpy(WORDS,"取得盾牌！防御力加10！");
      outtextxy(350,350,WORDS);
      Sleep(200);
      getch();
      cleardevice();
      Show_Map();
   }
   else if(map[x][y] == 26)
   {
      map[x][y] = 0;
      map[People.x][People.y] = 0;
    //   change_map();
      refresh();
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
      People.level+=1;
      People.hp+=800;
      People.Attack+=3;
      People.Defence+=3;
      setcolor(YELLOW);///白色文字
      setbkmode(TRANSPARENT);///文字背景透明
      setfont(-55,0,"黑体");///黑体字
      char WORDS[40];
      strcpy(WORDS,"取得等级翅膀！等级加1级！");
      outtextxy(350,350,WORDS);
      Sleep(200);
      getch();
      cleardevice();
      Show_Map();
   }
   else if(map[x][y] == 27)
   {
      map[x][y] = 0;
      map[People.x][People.y] = 0;
    //   change_map();
      refresh();
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
      People.money+=300;
      setcolor(YELLOW);///白色文字
      setbkmode(TRANSPARENT);///文字背景透明
      setfont(-55,0,"黑体");///黑体字
      char WORDS[40];
      strcpy(WORDS,"取得开心金币！金币加300！");
      outtextxy(350,350,WORDS);
      Sleep(200);
      getch();
      cleardevice();
      Show_Map();
   }
   else if(map[x][y] == 28)
   {
      map[x][y] = 0;
      map[People.x][People.y] = 0;
    //   change_map();
      refresh();
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
      People.hp*=1.5;
      People.Attack*=1.5;
      People.Defence*=1.5;
      setcolor(YELLOW);///白色文字
      setbkmode(TRANSPARENT);///文字背景透明
      setfont(-55,0,"黑体");///黑体字
      char WORDS[40];
      char words[40];
      strcpy(WORDS,"获得十字架！所有属性变为");
      strcpy(words,"原来的1.5倍!");
      outtextxy(340,340,WORDS);
      outtextxy(500,420,words);
      Sleep(200);
      getch();
      cleardevice();
      Show_Map();
   }
   else if(map[x][y] == 29)
   {
      map[x][y] = 0;
      map[People.x][People.y] = 0;
    //   change_map();
      refresh();
    //   mciSendString("play audio\\PICK.wav","",0,NULL);
      People.level+=3;
      People.hp+=2400;
      People.Attack+=9;
      People.Defence+=9;
      setcolor(YELLOW);///白色文字
      setbkmode(TRANSPARENT);///文字背景透明
      setfont(-55,0,"黑体");///黑体字
      char WORDS[40];
      strcpy(WORDS,"取得经验盒，等级加3级！");
      outtextxy(350,350,WORDS);
      Sleep(200);
      getch();
      cleardevice();
      Show_Map();
   }
   else if(map[x][y] == 1);//撞墙
   //else
     // atack_monster(EXCLE,x,y);
}
/*逻辑：1、判断人物前部是什么
		2、人物坐标移动 图片改变（实时）
		3、原位置图片恢复为1
		*/
void control_move()
{
	if(kbhit())
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
	 userkey =getch();
	 switch (userkey)
	 {
		 case 'A':
		case 'a':
		case 75:
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
		case 77:
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
		case 72:
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
		case 80:
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
}

int main()
{
	initgraph(1080, 780); //创建窗口 800*600 ege库函数
	setcaption("Magic_Tower");
	initImage();
	floor_changes_role_xy();
	Show_Map();
	while (1)
	{
		control_move();
		Sleep(20);
	}

	/*PIMAGE a = newimage();
	getimage(a, "picture1/BoneGuard.png");
	putimage(0, 0, a);*/

	//PIMAGE xxx = newimage();
	//getimage(xxx, "/testResources/0_1.jpg");
	//putimage(0, 0, xxx);

	getch();
	closegraph(); //窗口关闭 ege库函数
	return 0;
}
