/*version1
1、窗口 
2、素材导入
定义变量：IMAGE img
变量赋值：loadimage(&img,"路径")
图片显示:putimage(int x,int y,&img)
地图：使用二维数组
3、交互（上下左右，触碰）
4、关卡优化*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>						  //来自ege库
FILE *fp;									  //全局文件指针
int map_order_now = 1, int map_order_pre = 0; //地图参数 当前为1 前一地图为0 随关卡进行自增
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
typedef struct Actor
{
	char name[20] = {0}; //名称
	int level = 1;		 //初始等级
	int hp = 1000;		 //初始血量
	int Attack = 10;	 //初始攻击力
	int Defence = 10;	 ///初始防御力
	int money = 0;		 //初始金钱
	int exp = 0;		 //初始经验
	int x;				 //位置坐标x
	int y;				 //位置坐标y
	int Ykey = 1;		 //黄钥匙 初始为1
	int Rkey = 1;		 //红钥匙 初始为1
	int Bkey = 1;		 //蓝钥匙 初始为1
	PIMAGE img;			 //角色对象图片
} role, actor;			 //全局结构体 玩家角色
typedef struct Object
{
	char nmae[20] = {0};
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
enemy GreenSlime, RedSlime, BlackSlime;																											   //敌人 史莱姆类
enemy BigBat, SmallBat, RedBat;																													   //敌人 蝙蝠类
enemy Witch_1, Witch_2;																															   //敌人 巫师类
enemy Guard_1, Guard_2, Guard_3;																												   //敌人 卫兵类
enemy BoneMan, BoneGuard, BoneWarrior;																											   //敌人 骷髅类
enemy GBoss, MonsterKing, RBoss;																												   //敌人 Boss类
enemy Orc, OrcWarrior;																															   //敌人 兽人类
actors OldMan, SwordMan, Warrior, Witch_R, Witch_Y, WhiteWitch, RedMan;																			   //任务 角色类
object RKey, BKey, YKey, GKey, Sword, Shield, TreasureBox, WindOrient, GoldCoin, Level_Up, Cross, CrossEmblem, HP, BigHP, BlueDiamond, RedDiamond; //道具类
background Background, Blcok, Floor, Wall, YellowDoor, GreenDoor, RedDoor, BlueDoor, Upstairs, Downstairs, Shop, Stars;							   //地图 背景模块类
role People;																																	   //主角
push CrossEmblem_PUSH, Shop_PUSH[4], Versus, Warrior_PUSH[16], OldMan_PUSH[4], RedMan_PUSH[4], WindOrient_PUSH, End;							   //弹出窗口类
//地图切换核心函数（待完善）
void changemap()
{
	memcpy(M[map_order_now - 1].Map, map, sizeof(map)); //string.h 函数 地图切换函数
}
void floor_changes_role_xy() //不同层楼之间的任务地图切换(初始位置待定）
{
}
void initImage() //图像初始化函数
{
	GreenSlime.img = newimage();
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
	Blcok.img = newimage();
	Floor.img = newimage();
	Wall.img = newimage();
	YellowDoor.img = newimage();
	GreenDoor.img = newimage();
	BlueDoor.img = newimage();
	Upstairs.img = newimage();
	Downstairs.img = newimage();
	Shop.img = newimage();
	Stars.img = newimage();
	People.img = newimage();
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
	getimage(GreenSlime.img,"/picture1/GreenSlime.png");
	getimage(BlueSlime.img,"/picture1/BlueSlime.png");
	getimage(RedSlime.img,"/picture1/RedSlime.png");
	getimage(SmallBat.img,"/picture1/SmallBat.png");
	getimage(BigBat.img,"/picture1/BigBat.png");
	getimage(RedBat.img,"/picture1/RedBat.png");
	getimage(Witch_1.img,"/picture1/Witch_1.png");
	getimage(Witch_2.img,"/picture1/Witch_2.png");
	getimage(Guard_1.img,"/picture1/Guard_1.png");
	getimage(Guard_2.img,"/picture1/Guard_2.png");
	getimage(Guard_3.img,"/picture1/Guard_3.png");
	getimage(BoneMan.img,"/picture1/BoneMan.png");
	getimage(BoneWarrior.img,"/picture1/BoneWarrior.png");
	getimage(BoneGuard.img,"/picture1/BoneGuard.png");
	getimage(GBoss.img,"/picture1/GBoss.png");
	getimage(MonsterKing.img,"/picture1/MonsterKing.png");
	getimage(RBoss.img,"/picture1/RBoss.png");
	getimage(Orc.img,"/picture1/Orc.png");
	getimage(OrcWarrior.img,"/picture1/OrcWarrior.png");
	getimage(OldMan.img,"/picture1/OldMan.png");
	getiamge(RedMan.img,"/picture1/RedMan.png");
	getimage(SwordMan.img,"/picture1/SwordMan.png");
	getimage(Warrior.img,"/picture1/Warrior.png");
	getimage(Witch_R.img,"/picture1/Witch_R.png");
	getimage(Witch_Y.img,"/picture1/Witch_Y.png");
	getimage(WhiteWitch.img,"/picture1/WhiteWitch.png");
	getimage(RKey.img,"/picture1/RKey.png");
	getimage(YKey.img,"/picture1/YKey.png");
	getimage(BKey.img,"/picture1/BKey.png");
	getimage(GKey.img,"/picture1/GKey.png");
	getimage(Sword.img,"/picture1/Sword.png");
	getimage(Shield.img,"/picture1/Shield.png");
	getimage(TreasureBox.img,"/picture1/TreasureBox.png");
	getimage(WindOrient.img,"/picture1/WindOrient.png");
	getimage(Level_Up.img,"/picture1/Level_Up.png");
	getimage(GoldCoin.img,"/picture1/GoldCoin.png");
	getimage(HP.img,"/picture1/HP.png");
	getimage(BigHP.img,"/picture1/BigHP.png");
	getimage(CrossEmblem.img,"/picture1/CrossEmblem.png");
	getimage(Block.img,"/picture1/Block.png");
	getimage(Background.img,"/picture1/Background.png");
	getimage(Floor.img,"/picture1/Floor.png");
	getimage(Wall.img,"/picture1/Wall.png");
	getimage(YellowDoor.img,"/picture1/YellowDoor.png");
	getimage(BlueDoor.img,"/picture1/BlueDoor.png");
	getimage(GreenDoor.img,"/picture1/GreenDoor.png");
	getimage(Upstairs.img,"/picture1/Upstairs.png");
	getimage(Downstairs.img,"/picture1/Downstairs.png");
	getimage(Shop.img,"/picture1/Shop.png");
	getimage(Stars.img,"/picture1/Stars.png");
	getimage(People.img,"/picture1/actor.png");
	//弹窗图片
	getimage(CrossEmblem_PUSH.img,"/picture1/CrossEmblem_PUSH.png");
	getimage(Shop_PUSH[0].img,"/picture1/Shop1.png");
	getimage(Shop_PUSH[1].img,"/picture1/Shop2.png");
	getimage(Shop_PUSH[2].img,"/picture1/Shop3.png");
	getimage(Shop_PUSH[3].img,"/picture1/Shop4.png");
	getimage(Versus.img,"/picture1/Versus.png");
	getimage(OldMan_PUSH[0],"/picture/OldManOption1.png");
	getimage(OldMan_PUSH[1],"/picture/OldManOption2.png");
	getimage(OldMan_PUSH[2],"/picture/OldManOption3.png");
	getimage(OldMan_PUSH[3],"/picture/OldManOption4.png");
	getinmage(End.img,"/picture1/End.png");
	getimage(WindOrient_PUSH.img,"/picture1/WindOrient.png");
	getiage(RedMan_PUSH[0].img,"/picture1/RedManOption1.png");
	getiage(RedMan_PUSH[1].img,"/picture1/RedManOption2.png");
	getiage(RedMan_PUSH[2].img,"/picture1/RedManOption3.png");
	getiage(RedMan_PUSH[3].img,"/picture1/RedManOption4.png");
	getimage(Warrior_PUSH[0].img,"/picture/Warrior1.png");
	getimage(Warrior_PUSH[1].img,"/picture/Warrior2.png");
	getimage(Warrior_PUSH[2].img,"/picture/Warrior3.png");
	getimage(Warrior_PUSH[3].img,"/picture/Warrior4.png");
	getimage(Warrior_PUSH[4].img,"/picture/Warrior5.png");
	getimage(Warrior_PUSH[5].img,"/picture/Warrior6.png");
	getimage(Warrior_PUSH[6].img,"/picture/Warrior7.png");
	getimage(Warrior_PUSH[7].img,"/picture/Warrior8.png");
	getimage(Warrior_PUSH[8].img,"/picture/Warrior9.png");
	getimage(Warrior_PUSH[9].img,"/picture/Warrior10.png");
	getimage(Warrior_PUSH[10].img,"/picture/Warrior11.png");
	getimage(Warrior_PUSH[11].img,"/picture/Warrior12.png");
	getimage(Warrior_PUSH[12].img,"/picture/Warrior13.png");
	getimage(Warrior_PUSH[13].img,"/picture/Warrior14.png");
	getimage(Warrior_PUSH[14].img,"/picture/Warrior15.png");
	getimage(Warrior_PUSH[15].img,"/picture/Warrior16.png");
}
int main()
{
	initgraph(800, 600); //创建窗口 800*600 ege库函数
	//PIMAGE xxx = newimage();

	//getimage(xxx, "/testResources/0_1.jpg");
	//putimage(0, 0, xxx);

	//system("pause");//stdlib.h
	//test:连接测试
	getch();
	closegraph(); //窗口关闭 ege库函数
	return 0;
}