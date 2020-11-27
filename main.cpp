/*version1
1、窗口 
2、素材导入
定义变量：IMAGE img
变量赋值：loadimage(&img,"路径")
图片显示:putimage(int x,int y,&img)
地图：使用二维数组
3、交互（上下左右，触碰）
4、关卡优化*/
#include<stdio.h>
#include<stdlib.h>
#include<graphics.h>//来自ege库
FILE* fp; //全局文件指针
int map_order_now = 1, int map_order_pre = 0;//地图参数 当前为1 前一地图为0 随关卡进行自增
typedef struct Actor
{
	char name[20] = { 0 };//名称
	int level = 1;//初始等级
	int hp = 1000;//初始血量
	int Attack = 10;//初始攻击力
	int Defence = 10;///初始防御力
	int money = 0;//初始金钱
	int exp = 0;//初始经验
	int x;//位置坐标x
	int y;//位置坐标y
	int Ykey = 1;//黄钥匙 初始为1
	int Rkey = 1;//红钥匙 初始为1
	int Bkey = 1;//蓝钥匙 初始为1
	PIMAGE img;//角色对象图片
}role,actor;//全局结构体 玩家角色
typedef struct Object
{
	char nmae[20] = { 0 };
	int hp;//血量
	int exp;//经验值
	int Attack;//攻击力
	int Defence;//防御力
	int money;//金钱
	int x;//x坐标
	int y;//y坐标
	PIMAGE img;//对象图片
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
	initgraph(800, 600);//创建窗口 800*600 ege库函数
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
	//test:连接测试
	getch();
	closegraph();//窗口关闭 ege库函数
	return 0;
}