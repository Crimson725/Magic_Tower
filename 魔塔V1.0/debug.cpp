#include<iostream>
#include<graphics.h>
#include<cstdio>
#include<cmath>
#include<mmsystem.h>
using namespace std;
FILE * fp;///文件
int mapnum = 1,mapnum1 = 0;///mapnum为当前楼层,mapnum1为之前楼层,因为人物上下楼梯口不同最后显示位置不同用于改变人物位置函数的判断
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
};/**第一关地图*/
///也用作临时地图

///1代表空气墙用作外围封口
typedef struct
{
   int Map[13][13];
} MAPDEFINE;
MAPDEFINE M[12];

int map1[13][13];
typedef struct
{
   char name[20] = {0};
   int hp = 0;
   int ATACK;
   int DEF = 0;
   int money = 0;
   int ex = 0;
   long long int lost = 0;
   //int x;
   //int y;
   PIMAGE img;
} THINGS;
typedef struct
{
   int level = 1;
   int hp = 1000;
   int ATACK = 10;
   int DEF = 10;
   int money = 0;
   int ex = 0;
   int x;
   int y;
   int YELLOWKEY = 1;
   int REDKEY = 1;
   int BLUEKEY = 1;
   PIMAGE img;
} THING;
THINGS BEIJING;/**背景*/

THINGS QINGTOUGUAI,CHUJIFASHI,LVTOUGUAI,XIAOBIANFU,SHOUMIANREN,KULOUSHIBING;
THINGS DABIANFU,CHUJIWEIBING,JINGDUIZHANG,JINGWEISHI,KULOUDUIZHANG,GUAIWANG;
THINGS SHITOUGUAIREN,HONGBIANFU,HONGYIFASHI,GAOJIFASHI,BAIYIWUSHI,MAYIFASHI;
THINGS SHOUMIANWUSHI,SHUANGSHOUJIANSHI,GAOJIWEIBING,MINGWEIBING,LINGWUSHI;
THINGS MINGZHANSHI,LINGFASHI,MINGDUIZHANG,HONGTOUGUAI,KULOUREN,HONGBAOSHI;
THINGS LANBAOSHI,HONGYAOSHI,LANYAOSHI,HUANGYAOSHI,HONGPING,LANPING,HONGMEN;
THINGS HUANGMEN,LANMEN,LOUTIS,LOUTIX,SHENGGUANGHUI,FLOOR,QIANG,BAIFALAOREN;
THINGS HONGYILAOREN,FENGZHILUOPAN,QINGMEN,SHANGDIAN,BAOJIAN,YONGSHI,JINGYAOSHI;
THINGS DUNPAI,DENGJICHIBANG,KAIXINGJINGBI,SHIZIJIA,LIPINGHE;
/**怪物*/

THING PEOPLE;
/**人*/

typedef struct
{
   PIMAGE img;
   int img_index = 1;
} push; ///弹窗各种宝物对话之类

push SHENGGUANGHUI_PUSH,SHANGDIAN_PUSH[4],DAGUAI,YONGSHIDUIHUA[16],BAIFALAOREN_PUSH[4],HONGYILAOREN_PUSH[4],FENGZHILUOPAN_PUSH,THEEND;

void change_map()
{
   ///根据临时地图的变化存储真实地图的函数
   memcpy(M[mapnum-1].Map,map,sizeof(map));
}

void refresh()
{
   memcpy(map1,M[mapnum-1].Map,sizeof(map));
}

void change_peoplexy()///改变每层人物位置
{
   if(mapnum>=mapnum1)///上楼情况
      switch(mapnum)
      {
      case 1:///上楼到1楼(或初始化开局)
         PEOPLE.x = 10;
         PEOPLE.y = 6;
         break;
      case 2:///上楼到2楼
         PEOPLE.x = 2;
         PEOPLE.y = 1;
         break;
      case 3:
         PEOPLE.x = 11;
         PEOPLE.y = 2;
         break;
      case 4:
         PEOPLE.x = 10;
         PEOPLE.y = 11;
         break;
      case 5:
         PEOPLE.x = 10;
         PEOPLE.y = 1;
         break;
      case 6:
         PEOPLE.x = 10;
         PEOPLE.y = 10;
         break;
      case 7:
         PEOPLE.x = 11;
         PEOPLE.y = 6;
         break;
      case 8:
         PEOPLE.x = 2;
         PEOPLE.y = 1;
         break;
      case 9:
         PEOPLE.x = 4;
         PEOPLE.y = 7;
         break;
      case 10:
         PEOPLE.x = 7;
         PEOPLE.y = 5;
         break;
      case 11:
         PEOPLE.x = 11;
         PEOPLE.y = 2;
         break;
      }
   else ///下楼情况
      switch(mapnum)
      {
      case 1:///下楼到1楼
         PEOPLE.x = 1;
         PEOPLE.y = 2;
         break;
      case 2:///下楼到2楼
         PEOPLE.x = 10;
         PEOPLE.y = 1;
         break;
      case 3:
         PEOPLE.x = 10;
         PEOPLE.y = 11;
         break;
      case 4:
         PEOPLE.x = 10;
         PEOPLE.y = 1;
         break;
      case 5:
         PEOPLE.x = 10;
         PEOPLE.y = 10;
         break;
      case 6:
         PEOPLE.x = 10;
         PEOPLE.y = 5;
         break;
      case 7:
         PEOPLE.x = 1;
         PEOPLE.y = 2;
         break;
      case 8:
         PEOPLE.x = 5;
         PEOPLE.y = 8;
         break;
      case 9:
         PEOPLE.x = 8;
         PEOPLE.y = 7;
         break;
      case 10:
         PEOPLE.x = 10;
         PEOPLE.y = 1;
         break;
      }
   Sleep(300);///去除上下楼无限换图BUG
   mapnum1 = mapnum;
   refresh();
}

void init()
{
   /**定义*/
   BEIJING.img =  newimage();
   QINGTOUGUAI.img = newimage();
   HONGTOUGUAI.img = newimage();
   KULOUREN.img = newimage();
   HONGPING.img = newimage();
   HONGBAOSHI.img = newimage();
   HUANGYAOSHI.img = newimage();
   HUANGMEN.img = newimage();
   KULOUSHIBING.img = newimage();
   LANBAOSHI.img = newimage();
   LANYAOSHI.img = newimage();
   LANPING.img = newimage();
   SHENGGUANGHUI.img = newimage();
   HONGYAOSHI.img = newimage();
   PEOPLE.img = newimage();
   LOUTIS.img = newimage();
   LOUTIX.img = newimage();
   CHUJIFASHI.img = newimage();
   LVTOUGUAI.img = newimage();
   XIAOBIANFU.img = newimage();
   SHOUMIANREN.img = newimage();
   FLOOR.img = newimage();;
   QIANG.img = newimage();
   FENGZHILUOPAN.img = newimage();
   HONGMEN.img = newimage();
   BAIFALAOREN.img = newimage();
   HONGYILAOREN.img = newimage();
   JINGWEISHI.img = newimage();
   JINGDUIZHANG.img = newimage();
   QINGMEN.img = newimage();
   LANMEN.img = newimage();
   SHANGDIAN.img = newimage();
   BAOJIAN.img = newimage();
   YONGSHI.img = newimage();
   DABIANFU.img = newimage();
   HONGBIANFU.img = newimage();
   CHUJIWEIBING.img = newimage();
   JINGYAOSHI.img = newimage();
   DUNPAI.img = newimage();
   DENGJICHIBANG.img = newimage();
   KAIXINGJINGBI.img = newimage();
   KULOUDUIZHANG.img = newimage();
   GAOJIFASHI.img = newimage();
   HONGYIFASHI.img = newimage();
   SHITOUGUAIREN.img = newimage();
   GUAIWANG.img = newimage();
   KAIXINGJINGBI.img = newimage();
   SHIZIJIA.img = newimage();
   BAIYIWUSHI.img = newimage();
   MAYIFASHI.img = newimage();
   FENGZHILUOPAN.img = newimage();
   SHOUMIANWUSHI.img = newimage();
   LIPINGHE.img = newimage();
   GAOJIWEIBING.img = newimage();
   MINGWEIBING.img = newimage();
   SHUANGSHOUJIANSHI.img = newimage();

   ///弹窗
   SHENGGUANGHUI_PUSH.img = newimage();
   SHANGDIAN_PUSH[0].img = newimage();
   SHANGDIAN_PUSH[1].img = newimage();
   SHANGDIAN_PUSH[2].img = newimage();
   SHANGDIAN_PUSH[3].img = newimage();
   DAGUAI.img = newimage();
   BAIFALAOREN_PUSH[0].img = newimage();
   BAIFALAOREN_PUSH[1].img = newimage();
   BAIFALAOREN_PUSH[2].img = newimage();
   BAIFALAOREN_PUSH[3].img = newimage();
   HONGYILAOREN_PUSH[0].img = newimage();
   HONGYILAOREN_PUSH[1].img = newimage();
   HONGYILAOREN_PUSH[2].img = newimage();
   HONGYILAOREN_PUSH[3].img = newimage();
   FENGZHILUOPAN_PUSH.img = newimage();
   THEEND.img = newimage();


   /**取图*/
   getimage(BEIJING.img,"picture\\BEIJING.png");
   getimage(QINGTOUGUAI.img,"picture\\QINGTOUGUAI.png");
   getimage(HONGTOUGUAI.img,"picture\\HONGTOUGUAI.png");
   getimage(KULOUREN.img,"picture\\KULOUREN.png");
   getimage(HONGPING.img,"picture\\HONGPING.png");
   getimage(HONGBAOSHI.img,"picture\\HONGBAOSHI.png");
   getimage(HUANGYAOSHI.img,"picture\\HUANGYAOSHI.png");
   getimage(HUANGMEN.img,"picture\\HUANGMEN.png");
   getimage(KULOUSHIBING.img,"picture\\KULOUSHIBING.png");
   getimage(LANBAOSHI.img,"picture\\LANBAOSHI.png");
   getimage(LANYAOSHI.img,"picture\\LANYAOSHI.png");
   getimage(LANPING.img,"picture\\LANPING.png");
   getimage(SHENGGUANGHUI.img,"picture\\SHENGGUANGHUI.png");
   getimage(HONGYAOSHI.img,"picture\\HONGYAOSHI.png");
   getimage(PEOPLE.img,"picture\\PEOPLE.png");
   getimage(LOUTIS.img,"picture\\LOUTIS.png");
   getimage(LOUTIX.img,"picture\\LOUTIX.png");
   getimage(CHUJIFASHI.img,"picture\\CHUJIFASHI.png");
   getimage(LVTOUGUAI.img,"picture\\LVTOUGUAI.png");
   getimage(XIAOBIANFU.img,"picture\\XIAOBIANFU.png");
   getimage(SHOUMIANREN.img,"picture\\SHOUMIANREN.png");
   getimage(FLOOR.img,"picture\\FLOOR.png");
   getimage(QIANG.img,"picture\\QIANG.png");
   getimage(FENGZHILUOPAN.img,"picture\\FENGZHILUOPAN.png");
   getimage(HONGMEN.img,"picture\\HONGMEN.png");
   getimage(BAIFALAOREN.img,"picture\\BAIFALAOREN.png");
   getimage(HONGYILAOREN.img,"picture\\HONGYILAOREN.png");
   getimage(JINGWEISHI.img,"picture\\JINGWEISHI.png");
   getimage(JINGDUIZHANG.img,"picture\\JINGDUIZHANG.png");
   getimage(QINGMEN.img,"picture\\QINGMEN.png");
   getimage(LANMEN.img,"picture\\LANMEN.png");
   getimage(SHANGDIAN.img,"picture\\SHANGDIAN.png");
   getimage(BAOJIAN.img,"picture\\BAOJIAN.png");
   getimage(YONGSHI.img,"picture\\YONGSHI.png");
   getimage(DABIANFU.img,"picture\\DABIANFU.png");
   getimage(HONGBIANFU.img,"picture\\HONGBIANFU.png");
   getimage(CHUJIWEIBING.img,"picture\\CHUJIWEIBING.png");
   getimage(JINGYAOSHI.img,"picture\\JINGYAOSHI.png");
   getimage(DUNPAI.img,"picture\\DUNPAI.png");
   getimage(DENGJICHIBANG.img,"picture\\DENGJICHIBANG.png");
   getimage(KAIXINGJINGBI.img,"picture\\KAIXINGJINGBI.png");
   getimage(KULOUDUIZHANG.img,"picture\\KULOUDUIZHANG.png");
   getimage(GAOJIFASHI.img,"picture\\GAOJIFASHI.png");
   getimage(HONGYIFASHI.img,"picture\\HONGYIFASHI.png");
   getimage(SHITOUGUAIREN.img,"picture\\SHITOUGUAIREN.png");
   getimage(GUAIWANG.img,"picture\\GUAIWANG.png");
   getimage(KAIXINGJINGBI.img,"picture\\KAIXINGJINGBI.png");
   getimage(SHIZIJIA.img,"picture\\SHIZIJIA.png");
   getimage(BAIYIWUSHI.img,"picture\\BAIYIWUSHI.png");
   getimage(MAYIFASHI.img,"picture\\MAYIFASHI.png");
   getimage(FENGZHILUOPAN.img,"picture\\FENGZHILUOPAN.png");
   getimage(SHOUMIANWUSHI.img,"picture\\SHOUMIANWUSHI.png");
   getimage(SHUANGSHOUJIANSHI.img,"picture\\SHUANGSHOUJIANSHI.png");
   getimage(MINGWEIBING.img,"picture\\MINGWEIBING.png");
   getimage(LIPINGHE.img,"picture\\LIPINGHE.png");
   getimage(GAOJIWEIBING.img,"picture\\GAOJIWEIBING.png");

   ///弹窗取图
   getimage(SHENGGUANGHUI_PUSH.img,"picture\\SHENGGUANGHUI_PUSH.png");
   getimage(SHANGDIAN_PUSH[0].img,"picture\\3SHANGDIAN1.png");
   getimage(SHANGDIAN_PUSH[1].img,"picture\\3SHANGDIAN2.png");
   getimage(SHANGDIAN_PUSH[2].img,"picture\\3SHANGDIAN3.png");
   getimage(SHANGDIAN_PUSH[3].img,"picture\\3SHANGDIAN4.png");
   getimage(DAGUAI.img,"picture\\DAGUAI.png");
   getimage(BAIFALAOREN_PUSH[0].img,"picture\\5BAIFALAOREN1.png");
   getimage(BAIFALAOREN_PUSH[1].img,"picture\\5BAIFALAOREN2.png");
   getimage(BAIFALAOREN_PUSH[2].img,"picture\\5BAIFALAOREN3.png");
   getimage(BAIFALAOREN_PUSH[3].img,"picture\\5BAIFALAOREN4.png");
   getimage(HONGYILAOREN_PUSH[0].img,"picture\\5HONGYILAOREN1.png");
   getimage(HONGYILAOREN_PUSH[1].img,"picture\\5HONGYILAOREN2.png");
   getimage(HONGYILAOREN_PUSH[2].img,"picture\\5HONGYILAOREN3.png");
   getimage(HONGYILAOREN_PUSH[3].img,"picture\\5HONGYILAOREN4.png");
   getimage(FENGZHILUOPAN_PUSH.img,"picture\\FENGZHILUOPAN_PUSH.png");
   getimage(THEEND.img,"picture\\THEEND.png");

   ///怪物属性赋值
   QINGTOUGUAI.hp = 200;
   strcpy(QINGTOUGUAI.name,"青头怪");
   QINGTOUGUAI.ATACK = 35;
   QINGTOUGUAI.DEF = 10;
   QINGTOUGUAI.money = 5;
   QINGTOUGUAI.ex=5;
   HONGTOUGUAI.hp = 70;
   strcpy(HONGTOUGUAI.name,"红头怪");
   HONGTOUGUAI.ATACK = 15;
   HONGTOUGUAI.DEF=2;
   HONGTOUGUAI.money=5;
   HONGTOUGUAI.ex=5;
   KULOUREN.hp=110;
   strcpy(KULOUREN.name,"骷髅人");
   KULOUREN.ATACK=25;
   KULOUREN.DEF=5;
   KULOUREN.money=5;
   KULOUREN.ex=5;
   CHUJIFASHI.hp=125;
   CHUJIFASHI.ATACK=50;
   CHUJIFASHI.DEF=25;
   strcpy(CHUJIFASHI.name,"初级法师");
   CHUJIFASHI.money=25;
   CHUJIFASHI.ex=10;
   strcpy(LVTOUGUAI.name,"绿头怪");
   LVTOUGUAI.hp=50;
   LVTOUGUAI.ATACK=20;
   LVTOUGUAI.DEF=1;
   LVTOUGUAI.money=1;
   LVTOUGUAI.ex=1;
   ///小蝙蝠
   XIAOBIANFU.hp=100;
   XIAOBIANFU.ATACK=20;
   XIAOBIANFU.DEF=5;
   XIAOBIANFU.ex=3;
   XIAOBIANFU.money=3;
   strcpy(SHOUMIANREN.name,"兽面人");
   SHOUMIANREN.hp=300;
   SHOUMIANREN.ATACK=75;
   SHOUMIANREN.DEF=45;
   SHOUMIANREN.money=13;
   SHOUMIANREN.ex=10;
   strcpy(KULOUSHIBING.name,"骷髅士兵");
   KULOUSHIBING.hp=150;
   KULOUSHIBING.ATACK=40;
   KULOUSHIBING.DEF=20;
   KULOUSHIBING.money=8;
   KULOUSHIBING.ex=6;
   ///大蝙蝠
   DABIANFU.hp=150;
   DABIANFU.ATACK=65;
   DABIANFU.DEF=30;
   DABIANFU.money=10;
   DABIANFU.ex=8;
   ///初级卫兵
   CHUJIWEIBING.hp=450;
   CHUJIWEIBING.ATACK=150;
   CHUJIWEIBING.DEF=90;
   CHUJIWEIBING.money=22;
   CHUJIWEIBING.ex=19;
   ///金队长
   strcpy(JINGDUIZHANG.name,"金队长");
   JINGDUIZHANG.hp = 900;
   JINGDUIZHANG.ATACK = 750;
   JINGDUIZHANG.DEF = 650;
   JINGDUIZHANG.money = 77;
   JINGDUIZHANG.ex = 70;
   ///金卫士
   strcpy(JINGWEISHI.name,"金卫士");
   JINGWEISHI.hp = 850;
   JINGWEISHI.ATACK = 350;
   JINGWEISHI.DEF = 200;
   JINGWEISHI.money = 45;
   JINGWEISHI.ex = 40;
   ///骷髅队长
   KULOUDUIZHANG.hp=400;
   KULOUDUIZHANG.ATACK=90;
   KULOUDUIZHANG.DEF=50;
   KULOUDUIZHANG.money=15;
   KULOUDUIZHANG.ex=12;
   ///怪王
   GUAIWANG.hp=700;
   GUAIWANG.ATACK=250;
   GUAIWANG.DEF=125;
   GUAIWANG.money=32;
   GUAIWANG.ex=30;
   ///石头怪人
   SHITOUGUAIREN.hp=500;
   SHITOUGUAIREN.ATACK=115;
   SHITOUGUAIREN.DEF=65;
   SHITOUGUAIREN.money=15;
   SHITOUGUAIREN.ex=15;
   ///红蝙蝠
   HONGBIANFU.hp=550;
   HONGBIANFU.ATACK=160;
   HONGBIANFU.DEF=90;
   HONGBIANFU.money=25;
   HONGBIANFU.ex=20;
   ///红衣法师
   HONGYIFASHI.hp=500;
   HONGYIFASHI.ATACK=400;
   HONGYIFASHI.DEF=260;
   HONGYIFASHI.money=47;
   HONGYIFASHI.ex=45;
   ///高级法师
   GAOJIFASHI.hp=100;
   GAOJIFASHI.ATACK=200;
   GAOJIFASHI.DEF=110;
   GAOJIFASHI.money=40;
   GAOJIFASHI.ex=35;
   ///白衣武士
   BAIYIWUSHI.hp=1300;
   BAIYIWUSHI.ATACK=300;
   BAIYIWUSHI.DEF=150;
   BAIYIWUSHI.money=40;
   BAIYIWUSHI.ex=35;
   ///麻衣法师
   MAYIFASHI.hp=250;
   MAYIFASHI.ATACK=120;
   MAYIFASHI.DEF=70;
   MAYIFASHI.money=20;
   MAYIFASHI.ex=17;
   ///兽面武士
   SHOUMIANWUSHI.hp=900;
   SHOUMIANWUSHI.ATACK=450;
   SHOUMIANWUSHI.DEF=330;
   SHOUMIANWUSHI.money=50;
   SHOUMIANWUSHI.ex=50;
   ///双手剑士
   SHUANGSHOUJIANSHI.hp=1200;
   SHUANGSHOUJIANSHI.ATACK=620;
   SHUANGSHOUJIANSHI.DEF=520;
   SHUANGSHOUJIANSHI.money=65;
   SHUANGSHOUJIANSHI.ex=75;
   ///高级卫兵
   GAOJIWEIBING.hp=1500;
   GAOJIWEIBING.ATACK=560;
   GAOJIWEIBING.DEF=460;
   GAOJIWEIBING.money=60;
   GAOJIWEIBING.ex=60;
   ///冥卫兵
   MINGWEIBING.hp=1250;
   MINGWEIBING.ATACK=500;
   MINGWEIBING.DEF=400;
   MINGWEIBING.money=55;
   MINGWEIBING.ex=55;
   ///灵武士
   LINGWUSHI.hp=1200;
   LINGWUSHI.ATACK=980;
   LINGWUSHI.DEF=900;
   LINGWUSHI.money=99;
   LINGWUSHI.ex=75;
   ///冥战士
   MINGZHANSHI.hp=200;
   MINGZHANSHI.ATACK=680;
   MINGZHANSHI.DEF=590;
   MINGZHANSHI.money=70;
   MINGZHANSHI.ex=65;
   ///灵法师
   LINGFASHI.hp=1500;
   LINGFASHI.ATACK=830;
   LINGFASHI.DEF=730;
   LINGFASHI.money=80;
   LINGFASHI.ex=70;
   ///冥队长
   MINGDUIZHANG.hp=2500;
   MINGDUIZHANG.ATACK=900;
   MINGDUIZHANG.DEF=850;
   MINGDUIZHANG.money=84;
   MINGDUIZHANG.ex=75;
}
void read_map()
{
   int MAPNUM;
   fp = fopen("data\\map.txt","r");
   for(int k = 0 ; k < 11 ; k++)
   {
      fscanf(fp,"%d",&MAPNUM);
      for(int i = 0 ; i < 13 ; i++)
      {
         for(int j = 0 ; j < 13 ; j++)
         {
            fscanf(fp,"%d",&M[k].Map[i][j]);
         }
      }
   }
}
void show_map()
{
   memcpy(map,map1,sizeof(map));
   map[PEOPLE.x][PEOPLE.y] = 15;
   putimage(0,0,BEIJING.img);
   for(int i = 0 ; i < 13; i++)
      for(int j = 0 ; j < 13 ; j++)
      {
         if(map[j][i] == 0)
            putimage(60*i+304,60*j+3,FLOOR.img);
         else if(map[j][i] == 2)
            putimage(60*i+304,60*j+3,QIANG.img);
         else if(map[j][i] == 3)
            putimage(60*i+304,60*j+3,HONGMEN.img);
         else if(map[j][i] == 4)
            putimage(60*i+304,60*j+3,HUANGMEN.img);
         else if(map[j][i] == 5)
            putimage(60*i+304,60*j+3,LANMEN.img);
         else if(map[j][i] == 6)
            putimage(60*i+304,60*j+3,HONGPING.img);
         else if(map[j][i] == 7)
            putimage(60*i+304,60*j+3,LANPING.img);
         else if(map[j][i] == 8)
            putimage(60*i+304,60*j+3,SHENGGUANGHUI.img);
         else if(map[j][i] == 9)
            putimage(60*i+304,60*j+3,FENGZHILUOPAN.img);
         else if(map[j][i] == 10)
            putimage(60*i+304,60*j+3,LOUTIS.img);
         else if(map[j][i] == 11)
            putimage(60*i+304,60*j+3,LOUTIX.img);
         else if(map[j][i] == 12)
            putimage(60*i+304,60*j+3,HUANGYAOSHI.img);
         else if(map[j][i] == 13)
            putimage(60*i+304,60*j+3,HONGYAOSHI.img);
         else if(map[j][i] == 14)
            putimage(60*i+304,60*j+3,LANYAOSHI.img);
         else if(map[j][i] == 15)
            putimage(60*i+304,60*j+3,PEOPLE.img);
         else if(map[j][i] == 16)
            putimage(60*i+304,60*j+3,HONGBAOSHI.img);
         else if(map[j][i] == 17)
            putimage(60*i+304,60*j+3,LANBAOSHI.img);
         else if(map[j][i] == 18)
            putimage(60*i+304,60*j+3,BAIFALAOREN.img);
         else if(map[j][i] == 19)
            putimage(60*i+304,60*j+3,HONGYILAOREN.img);
         else if(map[j][i] == 20)
            putimage(60*i+304,60*j+3,QINGMEN.img);
         else if(map[j][i] == 21)
            putimage(60*i+304,60*j+3,BAOJIAN.img);
         else if(map[j][i] == 22)
            putimage(60*i+304,60*j+3,SHANGDIAN.img);
         else if(map[j][i] == 23)
            putimage(60*i+304,60*j+3,YONGSHI.img);
         else if(map[j][i] == 24)
            putimage(60*i+304,60*j+3,JINGYAOSHI.img);
         else if(map[j][i] == 25)
            putimage(60*i+304,60*j+3,DUNPAI.img);
         else if(map[j][i] == 26)
            putimage(60*i+304,60*j+3,DENGJICHIBANG.img);
         else if(map[j][i] == 27)
            putimage(60*i+304,60*j+3,KAIXINGJINGBI.img);
         else if(map[j][i] == 28)
            putimage(60*i+304,60*j+3,SHIZIJIA.img);
         else if(map[j][i] == 29)
            putimage(60*i+304,60*j+3,LIPINGHE.img);
         else if(map[j][i] == 30)
            putimage(60*i+304,60*j+3,QINGTOUGUAI.img);
         else if(map[j][i] == 31)
            putimage(60*i+304,60*j+3,HONGTOUGUAI.img);
         else if(map[j][i] == 32)
            putimage(60*i+304,60*j+3,KULOUREN.img);
         else if(map[j][i] == 33)
            putimage(60*i+304,60*j+3,CHUJIFASHI.img);
         else if(map[j][i] == 34)
            putimage(60*i+304,60*j+3,LVTOUGUAI.img);
         else if(map[j][i] == 35)
            putimage(60*i+304,60*j+3,XIAOBIANFU.img);
         else if(map[j][i] == 36)
            putimage(60*i+304,60*j+3,SHOUMIANREN.img);
         else if(map[j][i] == 37)
            putimage(60*i+304,60*j+3,KULOUSHIBING.img);
         else if(map[j][i] == 38)
            putimage(60*i+304,60*j+3,DABIANFU.img);
         else if(map[j][i] == 39)
            putimage(60*i+304,60*j+3,CHUJIWEIBING.img);
         else if(map[j][i] == 40)
            putimage(60*i+304,60*j+3,JINGDUIZHANG.img);
         else if(map[j][i] == 41)
            putimage(60*i+304,60*j+3,JINGWEISHI.img);
         else if(map[j][i] == 42)
            putimage(60*i+304,60*j+3,KULOUDUIZHANG.img);
         else if(map[j][i] == 43)
            putimage(60*i+304,60*j+3,GUAIWANG.img);
         else if(map[j][i] == 44)
            putimage(60*i+304,60*j+3,SHITOUGUAIREN.img);
         else if(map[j][i] == 45)
            putimage(60*i+304,60*j+3,HONGBIANFU.img);
         else if(map[j][i] == 46)
            putimage(60*i+304,60*j+3,HONGYIFASHI.img);
         else if(map[j][i] == 47)
            putimage(60*i+304,60*j+3,GAOJIFASHI.img);
         else if(map[j][i] == 48)
            putimage(60*i+304,60*j+3,BAIYIWUSHI.img);
         else if(map[j][i] == 49)
            putimage(60*i+304,60*j+3,MAYIFASHI.img);
         else if(map[j][i] == 50)
            putimage(60*i+304,60*j+3,SHOUMIANWUSHI.img);
         else if(map[j][i] == 51)
            putimage(60*i+304,60*j+3,SHUANGSHOUJIANSHI.img);
         else if(map[j][i] == 52)
            putimage(60*i+304,60*j+3,GAOJIWEIBING.img);
         else if(map[j][i] == 53)
            putimage(60*i+304,60*j+3,MINGWEIBING.img);
         else if(map[j][i] == 54)
            putimage(60*i+304,60*j+3,LINGWUSHI.img);
         else if(map[j][i] == 55)
            putimage(60*i+304,60*j+3,MINGZHANSHI.img);
         else if(map[j][i] == 56)
            putimage(60*i+304,60*j+3,LINGFASHI.img);
         else if(map[j][i] == 57)
            putimage(60*i+304,60*j+3,MINGDUIZHANG.img);
      }
   ///下面是打印人物属性栏
   setcolor(RGB(255,255,255));///白色文字
   setbkmode(TRANSPARENT);///文字背景透明
   setfont(-55,0,"黑体");///黑体字
   char YELLOWKEYNUM[3],REDKEYNUM[3],LEVELNUM[3],BLUEKEYNUM[3],ATACKNUM[5],HPNUM[10],EXNUM[5],MONEYNUM[5],DEFNUM[5];
   sprintf(YELLOWKEYNUM,"%d",PEOPLE.YELLOWKEY);///头文件cstdio或stdio.h
   sprintf(REDKEYNUM,"%d",PEOPLE.REDKEY);
   sprintf(BLUEKEYNUM,"%d",PEOPLE.BLUEKEY);
   sprintf(LEVELNUM,"%d",PEOPLE.level);
   sprintf(ATACKNUM,"%d",PEOPLE.ATACK);
   sprintf(HPNUM,"%d",PEOPLE.hp);
   sprintf(EXNUM,"%d",PEOPLE.ex);
   sprintf(MONEYNUM,"%d",PEOPLE.money);
   sprintf(DEFNUM,"%d",PEOPLE.DEF);
   outtextxy(210,405,YELLOWKEYNUM);///黄钥匙打印
   outtextxy(210,530,REDKEYNUM);///红钥匙打印
   outtextxy(210,465,BLUEKEYNUM);///蓝钥匙打印
   outtextxy(210,90,LEVELNUM);///等级打印
   setfont(-35,0,"黑体");///字体变小
   outtextxy(210,165,HPNUM);///血量打印
   outtextxy(210,208,ATACKNUM);///攻击力打印
   outtextxy(210,250,DEFNUM);///防御力打印
   outtextxy(210,295,MONEYNUM);///金钱打印
   outtextxy(210,340,EXNUM);///经验打印
}
void show_DAGUAI(PIMAGE img,int hp,int atack,int def)
{
   putimage(300,200,DAGUAI.img);
   putimage(325,240,80,80,img,0,0,60,60);
   setcolor(RGB(255,255,255));///白色文字
   setbkmode(TRANSPARENT);///文字背景透明
   setfont(-35,0,"黑体");///黑体字
   char HP[10],ATACK[10],DEF[10],PEOPLEHP[10],PEOPLEATACK[10],PEOPLEDEF[10];
   sprintf(HP,"%d",hp);
   sprintf(ATACK,"%d",atack);
   sprintf(DEF,"%d",def);
   sprintf(PEOPLEHP,"%d",PEOPLE.hp);
   sprintf(PEOPLEATACK,"%d",PEOPLE.ATACK);
   sprintf(PEOPLEDEF,"%d",PEOPLE.DEF);
   outtextxy(450,261,HP);
   outtextxy(450,320,ATACK);
   outtextxy(450,380,DEF);
   outtextxy(700,261,PEOPLEHP);
   outtextxy(700,320,PEOPLEATACK);
   outtextxy(700,380,PEOPLEDEF);
}///打怪界面
void atack_monster_hp(int EXCLE,int x,int y,int temhp)///修复人物HP可以为负数的BUG
{
   map[x][y] = EXCLE;
   change_map();
   PEOPLE.hp+=temhp;
}
void atack_monster(int EXCLE,int x,int y)
{
   ///打怪函数
   switch(EXCLE)
   {
   ///青头怪
   case 30:
      if(PEOPLE.ATACK>QINGTOUGUAI.DEF)
      {
         if((PEOPLE.hp-((QINGTOUGUAI.hp/(PEOPLE.ATACK-QINGTOUGUAI.DEF))*(QINGTOUGUAI.ATACK-PEOPLE.DEF)))>0)
         {
            int hp = QINGTOUGUAI.hp;
            int temhp = 0;
            for(int i = 0 ; i < 20000 ; i++)
            {
               PEOPLE.hp-=QINGTOUGUAI.ATACK-PEOPLE.DEF;
               hp-=PEOPLE.ATACK-QINGTOUGUAI.DEF;
               temhp+=QINGTOUGUAI.ATACK-PEOPLE.DEF;
               mciSendString("play audio\\ATACK.wav","",0,NULL);
               if(hp<0)
                  hp = 0;
               show_DAGUAI(QINGTOUGUAI.img,hp,QINGTOUGUAI.ATACK,QINGTOUGUAI.DEF);
               Sleep(300);
               if(hp==0)
                  break;
            }
            if(PEOPLE.hp<=0)
               atack_monster_hp(EXCLE,x,y,temhp);
            //PEOPLE.hp-=QINGTOUGUAI.hp/(PEOPLE.ATACK-QINGTOUGUAI.DEF)*(QINGTOUGUAI.ATACK-PEOPLE.DEF);
            else
            {
               PEOPLE.money+=QINGTOUGUAI.money;
               PEOPLE.ex+=QINGTOUGUAI.ex;

               map[x][y] = 0;
            }
            map[PEOPLE.x][PEOPLE.y] = 0;
            change_map();
            refresh();
            cleardevice();
            show_map();
         }
         break;
      ///红头怪
      case 31:
         if(PEOPLE.ATACK>HONGTOUGUAI.DEF)
            if((PEOPLE.hp-((HONGTOUGUAI.hp/(PEOPLE.ATACK-HONGTOUGUAI.DEF))*(HONGTOUGUAI.ATACK-PEOPLE.DEF)))>0)
            {
               int hp = HONGTOUGUAI.hp;
               int temhp = 0;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=HONGTOUGUAI.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-HONGTOUGUAI.DEF;
                  temhp+=HONGTOUGUAI.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp<0)
                     hp = 0;
                  show_DAGUAI(HONGTOUGUAI.img,hp,HONGTOUGUAI.ATACK,HONGTOUGUAI.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=HONGTOUGUAI.hp/(PEOPLE.ATACK-HONGTOUGUAI.DEF)*(HONGTOUGUAI.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=HONGTOUGUAI.money;
                  PEOPLE.ex+=HONGTOUGUAI.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }
         break;
      ///骷髅人
      case 32:
         if(PEOPLE.ATACK>KULOUREN.DEF)
            if((PEOPLE.hp-(KULOUREN.hp/(PEOPLE.ATACK-KULOUREN.DEF)*(KULOUREN.ATACK-PEOPLE.DEF)))>0)
            {
               int hp = KULOUREN.hp;
               int temhp = 0;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=KULOUREN.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-KULOUREN.DEF;
                  temhp+=KULOUREN.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(KULOUREN.img,hp,KULOUREN.ATACK,KULOUREN.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=KULOUREN.hp/(PEOPLE.ATACK-KULOUREN.DEF)*(KULOUREN.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=KULOUREN.money;
                  PEOPLE.ex+=KULOUREN.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }

         break;
      ///初级法师
      case 33:
         if(PEOPLE.ATACK>CHUJIFASHI.DEF)
            if((PEOPLE.hp-((CHUJIFASHI.hp/(PEOPLE.ATACK-CHUJIFASHI.DEF))*(CHUJIFASHI.ATACK-PEOPLE.DEF)))>0)
            {
               int hp = CHUJIFASHI.hp;
               int temhp = 0;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=CHUJIFASHI.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-CHUJIFASHI.DEF;
                  temhp+=CHUJIFASHI.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(CHUJIFASHI.img,hp,CHUJIFASHI.ATACK,CHUJIFASHI.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=CHUJIFASHI.hp/(PEOPLE.ATACK-CHUJIFASHI.DEF)*(CHUJIFASHI.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=CHUJIFASHI.money;
                  PEOPLE.ex+=CHUJIFASHI.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }

         break;
      ///绿头怪
      case 34:
         if(PEOPLE.ATACK>LVTOUGUAI.DEF)
            if((PEOPLE.hp-((LVTOUGUAI.hp/(PEOPLE.ATACK-LVTOUGUAI.DEF))*(LVTOUGUAI.ATACK-PEOPLE.DEF)))>0)
            {
               int hp = LVTOUGUAI.hp;
               int temhp = 0;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=LVTOUGUAI.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-LVTOUGUAI.DEF;
                  temhp+=LVTOUGUAI.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(LVTOUGUAI.img,hp,LVTOUGUAI.ATACK,LVTOUGUAI.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=LVTOUGUAI.hp/(PEOPLE.ATACK-LVTOUGUAI.DEF)*(LVTOUGUAI.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=QINGTOUGUAI.money;
                  PEOPLE.ex+=QINGTOUGUAI.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }

         break;
      ///小蝙蝠
      case 35:
         if(PEOPLE.ATACK>XIAOBIANFU.DEF)
            if((PEOPLE.hp-((XIAOBIANFU.hp/(PEOPLE.ATACK-XIAOBIANFU.DEF))*(XIAOBIANFU.ATACK-PEOPLE.DEF)))>0)
            {
               int hp = XIAOBIANFU.hp;
               int temhp = 0;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=XIAOBIANFU.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-XIAOBIANFU.DEF;
                  temhp+=XIAOBIANFU.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(XIAOBIANFU.img,hp,XIAOBIANFU.ATACK,XIAOBIANFU.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=XIAOBIANFU.hp/(PEOPLE.ATACK-XIAOBIANFU.DEF)*(XIAOBIANFU.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=XIAOBIANFU.money;
                  PEOPLE.ex+=XIAOBIANFU.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }

         break;
      ///兽面人
      case 36:
         if(PEOPLE.ATACK>SHOUMIANREN.DEF)
            if((PEOPLE.hp-((SHOUMIANREN.hp/(PEOPLE.ATACK-SHOUMIANREN.DEF))*(SHOUMIANREN.ATACK-PEOPLE.DEF)))>0)
            {
               int temhp = 0,hp = SHOUMIANREN.hp;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=SHOUMIANREN.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-SHOUMIANREN.DEF;
                  temhp+=SHOUMIANREN.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(SHOUMIANREN.img,hp,SHOUMIANREN.ATACK,SHOUMIANREN.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=SHOUMIANREN.hp/(PEOPLE.ATACK-SHOUMIANREN.DEF)*(SHOUMIANREN.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=SHOUMIANREN.money;
                  PEOPLE.ex+=SHOUMIANREN.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }

         break;
      ///骷髅士兵
      case 37:
         if(PEOPLE.ATACK>KULOUSHIBING.DEF)
            if((PEOPLE.hp-((KULOUSHIBING.hp/(PEOPLE.ATACK-KULOUSHIBING.DEF))*(KULOUSHIBING.ATACK-PEOPLE.DEF)))>0)
            {
               int temhp = 0,hp = KULOUSHIBING.hp;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=KULOUSHIBING.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-KULOUSHIBING.DEF;
                  temhp+=KULOUSHIBING.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(KULOUSHIBING.img,hp,KULOUSHIBING.ATACK,KULOUSHIBING.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=KULOUSHIBING.hp/(PEOPLE.ATACK-KULOUSHIBING.DEF)*(KULOUSHIBING.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=KULOUSHIBING.money;
                  PEOPLE.ex+=KULOUSHIBING.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }

         break;
      ///大蝙蝠
      case 38:
         if(PEOPLE.ATACK>DABIANFU.DEF)
            if((PEOPLE.hp-((DABIANFU.hp/(PEOPLE.ATACK-DABIANFU.DEF))*(DABIANFU.ATACK-PEOPLE.DEF)))>0)
            {
               int temhp = 0,hp = DABIANFU.hp;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=DABIANFU.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-DABIANFU.DEF;
                  temhp+=DABIANFU.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(DABIANFU.img,hp,DABIANFU.ATACK,DABIANFU.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=DABIANFU.hp/(PEOPLE.ATACK-DABIANFU.DEF)*(DABIANFU.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=DABIANFU.money;
                  PEOPLE.ex+=DABIANFU.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }

         break;
      ///初级卫兵
      case 39:
         if(PEOPLE.ATACK>CHUJIWEIBING.DEF)
            if((PEOPLE.hp-((CHUJIWEIBING.hp/(PEOPLE.ATACK-CHUJIWEIBING.DEF))*(CHUJIWEIBING.ATACK-PEOPLE.DEF)))>0)
            {
               int temhp = 0,hp = CHUJIWEIBING.hp;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=CHUJIWEIBING.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-CHUJIWEIBING.DEF;
                  temhp+=CHUJIWEIBING.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(CHUJIWEIBING.img,hp,CHUJIWEIBING.ATACK,CHUJIWEIBING.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=CHUJIWEIBING.hp/(PEOPLE.ATACK-CHUJIWEIBING.DEF)*(CHUJIWEIBING.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=CHUJIWEIBING.money;
                  PEOPLE.ex+=CHUJIWEIBING.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }

         break;
      ///金队长
      case 40:
         if(PEOPLE.ATACK>JINGDUIZHANG.DEF)
            if((PEOPLE.hp-((JINGDUIZHANG.hp/(PEOPLE.ATACK-JINGDUIZHANG.DEF))*(JINGDUIZHANG.ATACK-PEOPLE.DEF)))>0)
            {
               int temhp = 0,hp = JINGDUIZHANG.hp;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=JINGDUIZHANG.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-JINGDUIZHANG.DEF;
                  temhp+=JINGDUIZHANG.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(JINGDUIZHANG.img,hp,JINGDUIZHANG.ATACK,JINGDUIZHANG.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=JINGDUIZHANG.hp/(PEOPLE.ATACK-JINGDUIZHANG.DEF)*(JINGDUIZHANG.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=JINGDUIZHANG.money;
                  PEOPLE.ex+=JINGDUIZHANG.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }

         break;
      ///金卫士
      case 41:
         if(PEOPLE.ATACK>JINGWEISHI.DEF)
            if((PEOPLE.hp-((JINGWEISHI.hp/(PEOPLE.ATACK-JINGWEISHI.DEF))*(JINGWEISHI.ATACK-PEOPLE.DEF)))>0)
            {
               int temhp = 0,hp = JINGWEISHI.hp;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=JINGWEISHI.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-JINGWEISHI.DEF;
                  temhp+=JINGWEISHI.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(JINGWEISHI.img,hp,JINGWEISHI.ATACK,JINGWEISHI.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=JINGWEISHI.hp/(PEOPLE.ATACK-JINGWEISHI.DEF)*(JINGWEISHI.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=JINGWEISHI.money;
                  PEOPLE.ex+=JINGWEISHI.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }

         break;
      ///骷髅队长
      case 42:
         if(PEOPLE.ATACK>KULOUDUIZHANG.DEF)
            if((PEOPLE.hp-((KULOUDUIZHANG.hp/(PEOPLE.ATACK-KULOUDUIZHANG.DEF))*(KULOUDUIZHANG.ATACK-PEOPLE.DEF)))>0)
            {
               int temhp = 0,hp = KULOUDUIZHANG.hp;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=KULOUDUIZHANG.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-KULOUDUIZHANG.DEF;
                  temhp+=KULOUDUIZHANG.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(KULOUDUIZHANG.img,hp,KULOUDUIZHANG.ATACK,KULOUDUIZHANG.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=KULOUDUIZHANG.hp/(PEOPLE.ATACK-KULOUDUIZHANG.DEF)*(KULOUDUIZHANG.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=KULOUDUIZHANG.money;
                  PEOPLE.ex+=KULOUDUIZHANG.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();

            }
         break;
      ///怪王
      case 43:
         if(PEOPLE.ATACK>GUAIWANG.DEF)
            if((PEOPLE.hp-((GUAIWANG.hp/(PEOPLE.ATACK-GUAIWANG.DEF))*(GUAIWANG.ATACK-PEOPLE.DEF)))>0)
            {
               int temhp = 0,hp = GUAIWANG.hp;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=GUAIWANG.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-GUAIWANG.DEF;
                  temhp+=GUAIWANG.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(GUAIWANG.img,hp,GUAIWANG.ATACK,GUAIWANG.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=GUAIWANG.hp/(PEOPLE.ATACK-GUAIWANG.DEF)*(GUAIWANG.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=GUAIWANG.money;
                  PEOPLE.ex+=GUAIWANG.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();

            }
         break;
      ///石头怪人
      case 44:
         if(PEOPLE.ATACK>SHITOUGUAIREN.DEF)
            if((PEOPLE.hp-((SHITOUGUAIREN.hp/(PEOPLE.ATACK-SHITOUGUAIREN.DEF))*(SHITOUGUAIREN.ATACK-PEOPLE.DEF)))>0)
            {
               int temhp = 0,hp = SHITOUGUAIREN.hp;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=SHITOUGUAIREN.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-SHITOUGUAIREN.DEF;
                  temhp+=SHITOUGUAIREN.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(SHITOUGUAIREN.img,hp,SHITOUGUAIREN.ATACK,SHITOUGUAIREN.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=SHITOUGUAIREN.hp/(PEOPLE.ATACK-SHITOUGUAIREN.DEF)*(SHITOUGUAIREN.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=SHITOUGUAIREN.money;
                  PEOPLE.ex+=SHITOUGUAIREN.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }

         break;
      ///红蝙蝠
      case 45:
         if(PEOPLE.ATACK>HONGBIANFU.DEF)
            if((PEOPLE.hp-((HONGBIANFU.hp/(PEOPLE.ATACK-HONGBIANFU.DEF))*(HONGBIANFU.ATACK-PEOPLE.DEF)))>0)
            {
               int temhp = 0,hp = HONGBIANFU.hp;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=HONGBIANFU.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-HONGBIANFU.DEF;
                  temhp+=HONGBIANFU.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(HONGBIANFU.img,hp,HONGBIANFU.ATACK,HONGBIANFU.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=HONGBIANFU.hp/(PEOPLE.ATACK-HONGBIANFU.DEF)*(HONGBIANFU.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=HONGBIANFU.money;
                  PEOPLE.ex+=HONGBIANFU.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }

         break;
      ///红衣法师
      case 46:
         if(PEOPLE.ATACK>HONGYIFASHI.DEF)
            if((PEOPLE.hp-((HONGYIFASHI.hp/(PEOPLE.ATACK-HONGYIFASHI.DEF))*(HONGYIFASHI.ATACK-PEOPLE.DEF)))>0)
            {
               int temhp = 0,hp = HONGYIFASHI.hp;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=HONGYIFASHI.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-HONGYIFASHI.DEF;
                  temhp+=HONGYIFASHI.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(HONGYIFASHI.img,hp,HONGYIFASHI.ATACK,HONGYIFASHI.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=HONGYIFASHI.hp/(PEOPLE.ATACK-HONGYIFASHI.DEF)*(HONGYIFASHI.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=HONGYIFASHI.money;
                  PEOPLE.ex+=HONGYIFASHI.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }

         break;
      ///高级法师
      case 47:
         if(PEOPLE.ATACK>GAOJIFASHI.DEF)
            if((PEOPLE.hp-((GAOJIFASHI.hp/(PEOPLE.ATACK-GAOJIFASHI.DEF))*(GAOJIFASHI.ATACK-PEOPLE.DEF)))>0)
            {
               int temhp = 0,hp = GAOJIFASHI.hp;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=GAOJIFASHI.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-GAOJIFASHI.DEF;
                  temhp+=GAOJIFASHI.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(GAOJIFASHI.img,hp,GAOJIFASHI.ATACK,GAOJIFASHI.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=GAOJIFASHI.hp/(PEOPLE.ATACK-GAOJIFASHI.DEF)*(GAOJIFASHI.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=GAOJIFASHI.money;
                  PEOPLE.ex+=GAOJIFASHI.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }

         break;
      ///白衣武士
      case 48:
         if(PEOPLE.ATACK>BAIYIWUSHI.DEF)
            if((PEOPLE.hp-((BAIYIWUSHI.hp/(PEOPLE.ATACK-BAIYIWUSHI.DEF))*(BAIYIWUSHI.ATACK-PEOPLE.DEF)))>0)
            {
               int temhp = 0,hp = BAIYIWUSHI.hp;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=BAIYIWUSHI.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-BAIYIWUSHI.DEF;
                  temhp+=BAIYIWUSHI.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(BAIYIWUSHI.img,hp,BAIYIWUSHI.ATACK,BAIYIWUSHI.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=BAIYIWUSHI.hp/(PEOPLE.ATACK-BAIYIWUSHI.DEF)*(BAIYIWUSHI.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=BAIYIWUSHI.money;
                  PEOPLE.ex+=BAIYIWUSHI.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }

         break;
      ///麻衣法师
      case 49:
         if(PEOPLE.ATACK>MAYIFASHI.DEF)
            if((PEOPLE.hp-((MAYIFASHI.hp/(PEOPLE.ATACK-MAYIFASHI.DEF))*(MAYIFASHI.ATACK-PEOPLE.DEF)))>0)
            {
               int temhp = 0,hp = MAYIFASHI.hp;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=MAYIFASHI.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-MAYIFASHI.DEF;
                  temhp+=MAYIFASHI.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(MAYIFASHI.img,hp,MAYIFASHI.ATACK,MAYIFASHI.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=MAYIFASHI.hp/(PEOPLE.ATACK-MAYIFASHI.DEF)*(MAYIFASHI.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=MAYIFASHI.money;
                  PEOPLE.ex+=MAYIFASHI.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }

         break;
      ///兽面武士
      case 50:
         if(PEOPLE.ATACK>SHOUMIANWUSHI.DEF)
            if((PEOPLE.hp-((SHOUMIANWUSHI.hp/(PEOPLE.ATACK-SHOUMIANWUSHI.DEF))*(SHOUMIANWUSHI.ATACK-PEOPLE.DEF)))>0)
            {
               int temhp = 0,hp = SHOUMIANWUSHI.hp;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=SHOUMIANWUSHI.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-SHOUMIANWUSHI.DEF;
                  temhp+=SHOUMIANWUSHI.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(SHOUMIANWUSHI.img,hp,SHOUMIANWUSHI.ATACK,SHOUMIANWUSHI.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=SHOUMIANWUSHI.hp/(PEOPLE.ATACK-SHOUMIANWUSHI.DEF)*(SHOUMIANWUSHI.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=SHOUMIANWUSHI.money;
                  PEOPLE.ex+=SHOUMIANWUSHI.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }

         break;
      ///双手剑士
      case 51:
         if(PEOPLE.ATACK>SHUANGSHOUJIANSHI.DEF)
            if((PEOPLE.hp-((SHUANGSHOUJIANSHI.hp/(PEOPLE.ATACK-SHUANGSHOUJIANSHI.DEF))*(SHUANGSHOUJIANSHI.ATACK-PEOPLE.DEF)))>0)
            {
               int temhp = 0,hp = SHUANGSHOUJIANSHI.hp;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=SHUANGSHOUJIANSHI.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-SHUANGSHOUJIANSHI.DEF;
                  temhp+=SHUANGSHOUJIANSHI.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(SHUANGSHOUJIANSHI.img,hp,SHUANGSHOUJIANSHI.ATACK,SHUANGSHOUJIANSHI.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=SHUANGSHOUJIANSHI.hp/(PEOPLE.ATACK-SHUANGSHOUJIANSHI.DEF)*(SHUANGSHOUJIANSHI.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=SHUANGSHOUJIANSHI.money;
                  PEOPLE.ex+=SHUANGSHOUJIANSHI.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }

         break;
      ///高级卫兵
      case 52:
         if(PEOPLE.ATACK>GAOJIWEIBING.DEF)
            if((PEOPLE.hp-((GAOJIWEIBING.hp/(PEOPLE.ATACK-GAOJIWEIBING.DEF))*(GAOJIWEIBING.ATACK-PEOPLE.DEF)))>0)
            {
               int temhp = 0,hp = GAOJIWEIBING.hp;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=GAOJIWEIBING.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-GAOJIWEIBING.DEF;
                  temhp+=GAOJIWEIBING.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(GAOJIWEIBING.img,hp,GAOJIWEIBING.ATACK,GAOJIWEIBING.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=GAOJIWEIBING.hp/(PEOPLE.ATACK-GAOJIWEIBING.DEF)*(GAOJIWEIBING.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=GAOJIWEIBING.money;
                  PEOPLE.ex+=GAOJIWEIBING.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }

         break;
      ///冥卫兵
      case 53:
         if(PEOPLE.ATACK>MINGWEIBING.DEF)
            if((PEOPLE.hp-((MINGWEIBING.hp/(PEOPLE.ATACK-MINGWEIBING.DEF))*(MINGWEIBING.ATACK-PEOPLE.DEF)))>0)
            {
               int temhp = 0,hp = MINGWEIBING.hp;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=MINGWEIBING.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-MINGWEIBING.DEF;
                  temhp+=MINGWEIBING.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(MINGWEIBING.img,hp,MINGWEIBING.ATACK,MINGWEIBING.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=MINGWEIBING.hp/(PEOPLE.ATACK-MINGWEIBING.DEF)*(MINGWEIBING.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=MINGWEIBING.money;
                  PEOPLE.ex+=MINGWEIBING.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();

            }
         break;
      ///灵武士
      case 54:
         if(PEOPLE.ATACK>LINGWUSHI.DEF)
            if((PEOPLE.hp-((LINGWUSHI.hp/(PEOPLE.ATACK-LINGWUSHI.DEF))*(LINGWUSHI.ATACK-PEOPLE.DEF)))>0)
            {
               int temhp = 0,hp = LINGWUSHI.hp;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=LINGWUSHI.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-LINGWUSHI.DEF;
                  temhp+=LINGWUSHI.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(LINGWUSHI.img,hp,LINGWUSHI.ATACK,LINGWUSHI.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=LINGWUSHI.hp/(PEOPLE.ATACK-LINGWUSHI.DEF)*(LINGWUSHI.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=LINGWUSHI.money;
                  PEOPLE.ex+=LINGWUSHI.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }

         break;
      ///冥战士
      case 55:
         if(PEOPLE.ATACK>MINGZHANSHI.DEF)
            if((PEOPLE.hp-((MINGZHANSHI.hp/(PEOPLE.ATACK-MINGZHANSHI.DEF))*(MINGZHANSHI.ATACK-PEOPLE.DEF)))>0)
            {
               int temhp = 0,hp = MINGZHANSHI.hp;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=MINGZHANSHI.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-MINGZHANSHI.DEF;
                  temhp+=MINGZHANSHI.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(MINGZHANSHI.img,hp,MINGZHANSHI.ATACK,MINGZHANSHI.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=MINGZHANSHI.hp/(PEOPLE.ATACK-MINGZHANSHI.DEF)*(MINGZHANSHI.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=MINGZHANSHI.money;
                  PEOPLE.ex+=MINGZHANSHI.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }

         break;
      ///灵法师
      case 56:
         if(PEOPLE.ATACK>LINGFASHI.DEF)
            if((PEOPLE.hp-((LINGFASHI.hp/(PEOPLE.ATACK-LINGFASHI.DEF))*(LINGFASHI.ATACK-PEOPLE.DEF)))>0)
            {
               int temhp = 0,hp = LINGFASHI.hp;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=LINGFASHI.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-LINGFASHI.DEF;
                  temhp+=LINGFASHI.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(LINGFASHI.img,hp,LINGFASHI.ATACK,LINGFASHI.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=LINGFASHI.hp/(PEOPLE.ATACK-LINGFASHI.DEF)*(LINGFASHI.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=LINGFASHI.money;
                  PEOPLE.ex+=LINGFASHI.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }

         break;
      ///冥队长
      case 57:
         if(PEOPLE.ATACK>MINGDUIZHANG.DEF)
            if((PEOPLE.hp-((MINGDUIZHANG.hp/(PEOPLE.ATACK-MINGDUIZHANG.DEF))*(MINGDUIZHANG.ATACK-PEOPLE.DEF)))>0)
            {
               int temhp = 0,hp = MINGDUIZHANG.hp;
               for(int i = 0 ; i < 20000 ; i++)
               {
                  PEOPLE.hp-=MINGDUIZHANG.ATACK-PEOPLE.DEF;
                  hp-=PEOPLE.ATACK-MINGDUIZHANG.DEF;
                  temhp+=MINGDUIZHANG.ATACK-PEOPLE.DEF;
                  mciSendString("play audio\\ATACK.wav","",0,NULL);
                  if(hp < 0)
                     hp = 0;
                  show_DAGUAI(MINGDUIZHANG.img,hp,MINGDUIZHANG.ATACK,MINGDUIZHANG.DEF);
                  Sleep(300);
                  if(hp==0)
                     break;
               }
               //PEOPLE.hp-=MINGDUIZHANG.hp/(PEOPLE.ATACK-MINGDUIZHANG.DEF)*(MINGDUIZHANG.ATACK-PEOPLE.DEF);
               if(PEOPLE.hp<=0)
                  atack_monster_hp(EXCLE,x,y,temhp);
               else
               {
                  PEOPLE.money+=MINGDUIZHANG.money;
                  PEOPLE.ex+=MINGDUIZHANG.ex;

                  map[x][y] = 0;
               }
               map[PEOPLE.x][PEOPLE.y] = 0;
               change_map();
               refresh();
               cleardevice();
               show_map();
            }

         break;
      }
   }
}
void push_BAIFALAOREN()
{
   putimage(430,210,BAIFALAOREN_PUSH[0].img);
   int a = 1;///记录选择的选项,字母e往下走,字母q往上走,字母j确定
   for(int i = 0 ; i<20000 ; i++)
   {
      if(kbhit())
      {
         char b = getch();
         if(b == 'e' || b == 'E')
         {
            mciSendString("play audio\\EXCHANGE.wav","",0,NULL);
            a++;
            if(a>4)
               a = 1;
            cleardevice();
            show_map();
            putimage(430,210,BAIFALAOREN_PUSH[a-1].img);
         }
         else if(b == 'q' || b == 'Q')
         {
            mciSendString("play audio\\EXCHANGE.wav","",0,NULL);
            a--;
            if(a<1)
               a = 4;
            cleardevice();
            show_map();
            putimage(430,210,BAIFALAOREN_PUSH[a-1].img);
         }
         else if(b == 'j' || b == 'J')
         {
            switch(a)
            {
            case 1:
               if(PEOPLE.ex>99)
               {
                  mciSendString("play audio\\BUY.wav","",0,NULL);
                  PEOPLE.ex-=100;
                  PEOPLE.hp+=800;
                  PEOPLE.ATACK+=3;
                  PEOPLE.DEF+=3;
                  PEOPLE.level++;
               }
               else
               {
                  mciSendString("play audio\\EXCHANGE.wav","",0,NULL);
                  setcolor(RGB(255,255,255));///白色文字
                  setbkmode(TRANSPARENT);///文字背景透明
                  setfont(-55,0,"黑体");///黑体字
                  char WORDS[40];
                  strcpy(WORDS,"经验不够！");
                  cleardevice();
                  outtextxy(0,0,WORDS);
                  getch();
                  show_map();
               }
               break;
            case 2:
               if(PEOPLE.ex>29)
               {
                  mciSendString("play audio\\BUY.wav","",0,NULL);
                  PEOPLE.ex-=30;
                  PEOPLE.ATACK+=5;
               }
               else
               {
                  mciSendString("play audio\\EXCHANGE.wav","",0,NULL);
                  setcolor(RGB(255,255,255));///白色文字
                  setbkmode(TRANSPARENT);///文字背景透明
                  setfont(-55,0,"黑体");///黑体字
                  char WORDS[40];
                  strcpy(WORDS,"经验不够");
                  cleardevice();
                  outtextxy(0,0,WORDS);
                  getch();
                  show_map();
               }
               break;
            case 3:
               if(PEOPLE.ex>29)
               {
                  mciSendString("play audio\\BUY.wav","",0,NULL);
                  PEOPLE.ex-=30;
                  PEOPLE.DEF+=5;
               }
               else
               {
                  mciSendString("play audio\\EXCHANGE.wav","",0,NULL);
                  setcolor(RGB(255,255,255));///白色文字
                  setbkmode(TRANSPARENT);///文字背景透明
                  setfont(-55,0,"黑体");///黑体字
                  char WORDS[40];
                  strcpy(WORDS,"经验不够");
                  cleardevice();
                  outtextxy(0,0,WORDS);
                  getch();
                  show_map();
               }
               break;
            case 4:
               mciSendString("play audio\\PICK.wav","",0,NULL);
               break;
            }
            break;
         }
      }
      Sleep(200);
   }
}
void push_HONGYILAOREN()
{
   putimage(430,210,HONGYILAOREN_PUSH[0].img);
   int a = 1;///记录选择的选项,字母e往下走,字母q往上走,字母j确定
   for(int i = 0 ; i<20000 ; i++)
   {
      if(kbhit())
      {
         char b = getch();
         if(b == 'e' || b == 'E')
         {
            mciSendString("play audio\\EXCHANGE.wav","",0,NULL);
            a++;
            if(a>4)
               a = 1;
            cleardevice();
            show_map();
            putimage(430,210,HONGYILAOREN_PUSH[a-1].img);
         }
         else if(b == 'q' || b == 'Q')
         {
            mciSendString("play audio\\EXCHANGE.wav","",0,NULL);
            a--;
            if(a<1)
               a = 4;
            cleardevice();
            show_map();
            putimage(430,210,HONGYILAOREN_PUSH[a-1].img);
         }
         else if(b == 'j' || b == 'J')
         {
            switch(a)
            {
            case 1:
               if(PEOPLE.money>9)
               {
                  mciSendString("play audio\\BUY.wav","",0,NULL);
                  PEOPLE.money-=10;
                  PEOPLE.YELLOWKEY++;
               }
               else
               {
                  mciSendString("play audio\\EXCHANGE.wav","",0,NULL);
                  setcolor(RGB(255,255,255));///白色文字
                  setbkmode(TRANSPARENT);///文字背景透明
                  setfont(-55,0,"黑体");///黑体字
                  char WORDS[40];
                  strcpy(WORDS,"金钱不够！");
                  cleardevice();
                  outtextxy(0,0,WORDS);
                  getch();
                  show_map();
               }
               break;
            case 2:
               if(PEOPLE.money>50)
               {
                  mciSendString("play audio\\BUY.wav","",0,NULL);
                  PEOPLE.money-=50;
                  PEOPLE.BLUEKEY++;
               }
               else
               {
                  mciSendString("play audio\\EXCHANGE.wav","",0,NULL);
                  setcolor(RGB(255,255,255));///白色文字
                  setbkmode(TRANSPARENT);///文字背景透明
                  setfont(-55,0,"黑体");///黑体字
                  char WORDS[40];
                  strcpy(WORDS,"金钱不够");
                  cleardevice();
                  outtextxy(0,0,WORDS);
                  getch();
                  show_map();
               }
               break;
            case 3:
               if(PEOPLE.money>100)
               {
                  mciSendString("play audio\\BUY.wav","",0,NULL);
                  PEOPLE.money-=100;
                  PEOPLE.REDKEY++;
               }
               else
               {
                  mciSendString("play audio\\EXCHANGE.wav","",0,NULL);
                  setcolor(RGB(255,255,255));///白色文字
                  setbkmode(TRANSPARENT);///文字背景透明
                  setfont(-55,0,"黑体");///黑体字
                  char WORDS[40];
                  strcpy(WORDS,"金钱不够");
                  cleardevice();
                  outtextxy(0,0,WORDS);
                  getch();
                  show_map();
               }
               break;
            case 4:
               mciSendString("play audio\\PICK.wav","",0,NULL);
               break;
            }
            break;
         }
      }
      Sleep(200);
   }
}
void push_SHANGDIAN()///第三层商店
{
   putimage(430,210,SHANGDIAN_PUSH[0].img);
   int a = 1;///记录选择的选项,字母e往下走,字母q往上走,字母j确定
   for(int i = 0 ; i<20000 ; i++)
   {
      if(kbhit())
      {
         char b = getch();
         if(b == 'e' || b == 'E')
         {
            mciSendString("play audio\\EXCHANGE.wav","",0,NULL);
            a++;
            if(a>4)
               a = 1;
            cleardevice();
            show_map();
            putimage(430,210,SHANGDIAN_PUSH[a-1].img);
         }
         else if(b == 'q' || b == 'Q')
         {
            mciSendString("play audio\\EXCHANGE.wav","",0,NULL);
            a--;
            if(a<1)
               a = 4;
            cleardevice();
            show_map();
            putimage(430,210,SHANGDIAN_PUSH[a-1].img);
         }
         else if(b == 'j' || b == 'J')
         {
            switch(a)
            {
            case 1:
               if(PEOPLE.money>24)
               {
                  mciSendString("play audio\\BUY.wav","",0,NULL);
                  PEOPLE.money-=25;
                  PEOPLE.hp+=800;
               }
               else
               {
                  mciSendString("play audio\\EXCHANGE.wav","",0,NULL);
                  setcolor(RGB(255,255,255));///白色文字
                  setbkmode(TRANSPARENT);///文字背景透明
                  setfont(-55,0,"黑体");///黑体字
                  char WORDS[40];
                  strcpy(WORDS,"金钱不够！");
                  cleardevice();
                  outtextxy(0,0,WORDS);
                  getch();
                  show_map();
               }
               break;
            case 2:
               if(PEOPLE.money>24)
               {
                  mciSendString("play audio\\BUY.wav","",0,NULL);
                  PEOPLE.money-=25;
                  PEOPLE.ATACK+=5;
               }
               else
               {
                  mciSendString("play audio\\EXCHANGE.wav","",0,NULL);
                  setcolor(RGB(255,255,255));///白色文字
                  setbkmode(TRANSPARENT);///文字背景透明
                  setfont(-55,0,"黑体");///黑体字
                  char WORDS[40];
                  strcpy(WORDS,"金钱不够");
                  cleardevice();
                  outtextxy(0,0,WORDS);
                  getch();
                  show_map();
               }
               break;
            case 3:
               if(PEOPLE.money>24)
               {
                  mciSendString("play audio\\BUY.wav","",0,NULL);
                  PEOPLE.money-=25;
                  PEOPLE.DEF+=5;
               }
               else
               {
                  mciSendString("play audio\\EXCHANGE.wav","",0,NULL);
                  setcolor(RGB(255,255,255));///白色文字
                  setbkmode(TRANSPARENT);///文字背景透明
                  setfont(-55,0,"黑体");///黑体字
                  char WORDS[40];
                  strcpy(WORDS,"金钱不够");
                  cleardevice();
                  outtextxy(0,0,WORDS);
                  getch();
                  show_map();
               }
               break;
            case 4:
               mciSendString("play audio\\PICK.wav","",0,NULL);
               break;
            }
            break;
         }
      }
      Sleep(200);
   }
}
void push_YONGSHI()///第四层开门勇士对话
{
   for(int i = 0 ; i < 16 ; i++)
      YONGSHIDUIHUA[i].img = newimage();
   getimage(YONGSHIDUIHUA[0].img,"picture\\YONGSHI.png");
   getimage(YONGSHIDUIHUA[1].img,"picture\\YONGSHI2.png");
   getimage(YONGSHIDUIHUA[2].img,"picture\\YONGSHI3.png");
   getimage(YONGSHIDUIHUA[3].img,"picture\\YONGSHI4.png");
   getimage(YONGSHIDUIHUA[4].img,"picture\\YONGSHI5.png");
   getimage(YONGSHIDUIHUA[5].img,"picture\\YONGSHI6.png");
   getimage(YONGSHIDUIHUA[6].img,"picture\\YONGSHI7.png");
   getimage(YONGSHIDUIHUA[7].img,"picture\\YONGSHI8.png");
   getimage(YONGSHIDUIHUA[8].img,"picture\\YONGSHI9.png");
   getimage(YONGSHIDUIHUA[9].img,"picture\\YONGSHI10.png");
   getimage(YONGSHIDUIHUA[10].img,"picture\\YONGSHI11.png");
   getimage(YONGSHIDUIHUA[11].img,"picture\\YONGSHI12.png");
   getimage(YONGSHIDUIHUA[12].img,"picture\\YONGSHI13.png");
   getimage(YONGSHIDUIHUA[13].img,"picture\\YONGSHI14.png");
   getimage(YONGSHIDUIHUA[14].img,"picture\\YONGSHI15.png");
   getimage(YONGSHIDUIHUA[15].img,"picture\\YONGSHI16.png");

   for(int i = 1; i<=16; i++)
   {
      if(i == 1||7||9||11||14)
      {
         putimage(400,400,YONGSHIDUIHUA[i-1].img);
         mciSendString("play audio\\TALK.wav","",0,NULL);
         getch();
         cleardevice();
         show_map();
      }
      else
      {
         putimage(200,200,YONGSHIDUIHUA[i-1].img);
         mciSendString("play audio\\TALK.wav","",0,NULL);
         getch();
         cleardevice();
         show_map();
      }
   }
   M[1].Map[7][2] = 0;///青门消失
   YONGSHI.hp = 1;///用来判断是否已经和勇士说过话
}
void change_state(int EXCLE,int x,int y)///EXCLE代表标号值这个函数用于改变(x,y)的状态
{
   ///以下商店调用函数
   if(map[x][y] == -2 && mapnum == 3)///第三层商店因为访问商店只能从正中间访问用-2表示
   {
      push_SHANGDIAN();
   }
   else if(map[x][y] == -2 && mapnum == 11)
   {
      putimage(430,210,THEEND.img);
      Sleep(500);
      getch();
      map[PEOPLE.x][PEOPLE.y] = 0;
      change_map();
      refresh();
      cleardevice();
      show_map();
   }


   ///以下包含开门和各类道具的获取
   else if(map[x][y] == 3 && PEOPLE.REDKEY>0)
   {
      mciSendString("play audio\\OPENTHEDOOR.wav","",0,NULL);
      map[x][y] = 0;
      map[PEOPLE.x][PEOPLE.y] = 0;
      change_map();
      refresh();
      PEOPLE.REDKEY--;
   }
   else if(map[x][y] == 4 && PEOPLE.YELLOWKEY>0)
   {
      mciSendString("play audio\\OPENTHEDOOR.wav","",0,NULL);
      map[x][y] = 0;
      map[PEOPLE.x][PEOPLE.y] = 0;
      change_map();
      refresh();
      PEOPLE.YELLOWKEY--;
   }
   else if(map[x][y] == 5 && PEOPLE.BLUEKEY>0)
   {
      mciSendString("play audio\\OPENTHEDOOR.wav","",0,NULL);
      map[x][y] = 0;
      map[PEOPLE.x][PEOPLE.y] = 0;
      change_map();
      refresh();
      PEOPLE.BLUEKEY--;
   }
   else if(map[x][y] == 6)
   {
      mciSendString("play audio\\PICK.wav","",0,NULL);
      map[x][y] = 0;
      map[PEOPLE.x][PEOPLE.y] = 0;
      change_map();
      refresh();
      PEOPLE.hp+=200;
   }
   else if(map[x][y] == 7)
   {
      mciSendString("play audio\\PICK.wav","",0,NULL);
      map[x][y] = 0;
      map[PEOPLE.x][PEOPLE.y] = 0;
      change_map();
      refresh();
      PEOPLE.hp+=500;
   }
   else if(map[x][y] == 8)
   {
      map[x][y] = 0;   ///打印圣光徽图片
      putimage(260,230,SHENGGUANGHUI_PUSH.img);
      mciSendString("play audio\\PICK.wav","",0,NULL);
      Sleep(200);
      getch();
      map[PEOPLE.x][PEOPLE.y] = 0;
      change_map();
      refresh();
   }
   else if(map[x][y] == 9)
   {
      map[x][y] = 0;   ///打印风之罗盘图片
      putimage(260,230,FENGZHILUOPAN_PUSH.img);
      mciSendString("play audio\\PICK.wav","",0,NULL);
      Sleep(200);
      getch();
      map[PEOPLE.x][PEOPLE.y] = 0;
      change_map();
      refresh();
   }
   else if(map[x][y] == 10)///上楼梯
   {
      mapnum++;
      refresh();
      change_peoplexy();
      mciSendString("play audio\\PICK.wav","",0,NULL);
   }
   else if(map[x][y] == 11)///下楼梯
   {
      if(mapnum == 1)
      {
         mciSendString("play audio\\PICK.wav","",0,NULL);
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
         show_map();
      }
      else
      {
         mapnum--;
         refresh();
         change_peoplexy();
         mciSendString("play audio\\PICK.wav","",0,NULL);
      }
   }
   else if(map[x][y] == 12)
   {
      map[x][y] = 0;
      map[PEOPLE.x][PEOPLE.y] = 0;
      change_map();
      refresh();
      PEOPLE.YELLOWKEY++;
      mciSendString("play audio\\PICK.wav","",0,NULL);
   }
   else if(map[x][y] == 13)
   {
      map[x][y] = 0;
      map[PEOPLE.x][PEOPLE.y] = 0;
      change_map();
      refresh();
      PEOPLE.REDKEY++;
      mciSendString("play audio\\PICK.wav","",0,NULL);
   }
   else if(map[x][y] == 14)
   {
      map[x][y] = 0;
      map[PEOPLE.x][PEOPLE.y] = 0;
      change_map();
      refresh();
      PEOPLE.BLUEKEY++;
      mciSendString("play audio\\PICK.wav","",0,NULL);
   }
   else if(map[x][y] == 16)
   {
      map[x][y] = 0;
      map[PEOPLE.x][PEOPLE.y] = 0;
      change_map();
      refresh();
      PEOPLE.ATACK+=3;
      mciSendString("play audio\\PICK.wav","",0,NULL);
   }
   else if(map[x][y] == 17)
   {
      map[x][y] = 0;
      map[PEOPLE.x][PEOPLE.y] = 0;
      change_map();
      refresh();
      PEOPLE.DEF+=3;
      mciSendString("play audio\\PICK.wav","",0,NULL);
   }
   else if(map[x][y] == 21 && mapnum == 2)
   {
      map[x][y] = 0;
      map[PEOPLE.x][PEOPLE.y] = 0;
      change_map();
      refresh();
      mciSendString("play audio\\PICK.wav","",0,NULL);
      setcolor(YELLOW);///白色文字
      setbkmode(TRANSPARENT);///文字背景透明
      setfont(-55,0,"黑体");///黑体字
      char WORDS[40];
      strcpy(WORDS,"获得紫砂剑！攻击加60！");
      outtextxy(340,340,WORDS);
      Sleep(200);
      getch();
      cleardevice();
      PEOPLE.ATACK+=60;
      show_map();
   }///当楼层为2时让白发老人消失(已经改成一把剑)
   else if(map[x][y] == 18 && mapnum == 5)
   {
      mciSendString("play audio\\PICK.wav","",0,NULL);
      push_BAIFALAOREN();
   }///当楼层为5时弹出白发老人购买菜单
   else if(map[x][y] == 25 && mapnum == 2)
   {
      map[x][y] = 0;
      map[PEOPLE.x][PEOPLE.y] = 0;
      change_map();
      refresh();
      mciSendString("play audio\\PICK.wav","",0,NULL);
      setcolor(YELLOW);///白色文字
      setbkmode(TRANSPARENT);///文字背景透明
      setfont(-55,0,"黑体");///黑体字
      char WORDS[40];
      strcpy(WORDS,"获得青铜盾！防御加60！");
      outtextxy(340,340,WORDS);
      Sleep(200);
      getch();
      cleardevice();
      PEOPLE.DEF+=60;
      show_map();
   }///当楼层为2时让红衣老人消失(已经改成一盾牌)
   else if(map[x][y] == 19 && mapnum == 5)
   {
      mciSendString("play audio\\PICK.wav","",0,NULL);
      push_HONGYILAOREN();
   }///当楼层为5时弹出红衣老人购买菜单
   else if(map[x][y] == 20)
   {
      mciSendString("play audio\\PICK.wav","",0,NULL);
      setcolor(YELLOW);///白色文字
      setbkmode(TRANSPARENT);///文字背景透明
      setfont(-55,0,"黑体");///黑体字
      char WORDS[40];
      strcpy(WORDS,"你没有打开此门的钥匙！");
      outtextxy(350,350,WORDS);
      Sleep(200);
      getch();
      cleardevice();
      show_map();
      ///碰到青门无动作
   }
   else if(map[x][y] == 21 && mapnum == 3)///第三层的宝剑
   {
      map[x][y] = 0;
      map[PEOPLE.x][PEOPLE.y] = 0;
      change_map();
      refresh();
      mciSendString("play audio\\PICK.wav","",0,NULL);
      PEOPLE.ATACK+=10;
      setcolor(YELLOW);///白色文字
      setbkmode(TRANSPARENT);///文字背景透明
      setfont(-55,0,"黑体");///黑体字
      char WORDS[40];
      strcpy(WORDS,"取得宝剑！攻击力加10！");
      outtextxy(350,350,WORDS);
      Sleep(200);
      getch();
      cleardevice();
      show_map();
   }
   else if(map[x][y] == 21 && mapnum == 9)///第九层的宝剑
   {
      map[x][y] = 0;
      map[PEOPLE.x][PEOPLE.y] = 0;
      change_map();
      refresh();
      mciSendString("play audio\\PICK.wav","",0,NULL);
      PEOPLE.ATACK+=60;
      setcolor(YELLOW);///白色文字
      setbkmode(TRANSPARENT);///文字背景透明
      setfont(-55,0,"黑体");///黑体字
      char WORDS[40];
      strcpy(WORDS,"取得大宝剑！攻击力加60！");
      outtextxy(350,350,WORDS);
      Sleep(200);
      getch();
      cleardevice();
      show_map();
   }
   else if(map[x][y] == 23 && YONGSHI.hp == 0)///勇士
   {
      mciSendString("play audio\\PICK.wav","",0,NULL);
      push_YONGSHI();
   }
   else if(map[x][y] == 24)///金钥匙
   {
      map[x][y] = 0;
      map[PEOPLE.x][PEOPLE.y] = 0;
      change_map();
      refresh();
      mciSendString("play audio\\PICK.wav","",0,NULL);
      PEOPLE.ATACK+=10;
      setcolor(YELLOW);///白色文字
      setbkmode(TRANSPARENT);///文字背景透明
      setfont(-55,0,"黑体");///黑体字
      char WORDS[40];
      strcpy(WORDS,"取得金钥匙！每种钥匙数量加1！");
      outtextxy(340,340,WORDS);
      Sleep(200);
      getch();
      cleardevice();
      PEOPLE.REDKEY++;
      PEOPLE.BLUEKEY++;
      PEOPLE.YELLOWKEY++;
      show_map();
   }
   else if(map[x][y] == 25 && mapnum == 5)
   {
      map[x][y] = 0;
      map[PEOPLE.x][PEOPLE.y] = 0;
      change_map();
      refresh();
      mciSendString("play audio\\PICK.wav","",0,NULL);
      PEOPLE.DEF+=10;
      setcolor(YELLOW);///白色文字
      setbkmode(TRANSPARENT);///文字背景透明
      setfont(-55,0,"黑体");///黑体字
      char WORDS[40];
      strcpy(WORDS,"取得盾牌！防御力加10！");
      outtextxy(350,350,WORDS);
      Sleep(200);
      getch();
      cleardevice();
      show_map();
   }
   else if(map[x][y] == 26)
   {
      map[x][y] = 0;
      map[PEOPLE.x][PEOPLE.y] = 0;
      change_map();
      refresh();
      mciSendString("play audio\\PICK.wav","",0,NULL);
      PEOPLE.level+=1;
      PEOPLE.hp+=800;
      PEOPLE.ATACK+=3;
      PEOPLE.DEF+=3;
      setcolor(YELLOW);///白色文字
      setbkmode(TRANSPARENT);///文字背景透明
      setfont(-55,0,"黑体");///黑体字
      char WORDS[40];
      strcpy(WORDS,"取得等级翅膀！等级加1级！");
      outtextxy(350,350,WORDS);
      Sleep(200);
      getch();
      cleardevice();
      show_map();
   }
   else if(map[x][y] == 27)
   {
      map[x][y] = 0;
      map[PEOPLE.x][PEOPLE.y] = 0;
      change_map();
      refresh();
      mciSendString("play audio\\PICK.wav","",0,NULL);
      PEOPLE.money+=300;
      setcolor(YELLOW);///白色文字
      setbkmode(TRANSPARENT);///文字背景透明
      setfont(-55,0,"黑体");///黑体字
      char WORDS[40];
      strcpy(WORDS,"取得开心金币！金币加300！");
      outtextxy(350,350,WORDS);
      Sleep(200);
      getch();
      cleardevice();
      show_map();
   }
   else if(map[x][y] == 28)
   {
      map[x][y] = 0;
      map[PEOPLE.x][PEOPLE.y] = 0;
      change_map();
      refresh();
      mciSendString("play audio\\PICK.wav","",0,NULL);
      PEOPLE.hp*=1.5;
      PEOPLE.ATACK*=1.5;
      PEOPLE.DEF*=1.5;
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
      show_map();
   }
   else if(map[x][y] == 29)
   {
      map[x][y] = 0;
      map[PEOPLE.x][PEOPLE.y] = 0;
      change_map();
      refresh();
      mciSendString("play audio\\PICK.wav","",0,NULL);
      PEOPLE.level+=3;
      PEOPLE.hp+=2400;
      PEOPLE.ATACK+=9;
      PEOPLE.DEF+=9;
      setcolor(YELLOW);///白色文字
      setbkmode(TRANSPARENT);///文字背景透明
      setfont(-55,0,"黑体");///黑体字
      char WORDS[40];
      strcpy(WORDS,"取得经验盒！等级加3级！");
      outtextxy(350,350,WORDS);
      Sleep(200);
      getch();
      cleardevice();
      show_map();
   }

   ///以下只包含打怪以及调用打怪函数
   else if(map[x][y] == 1);///撞透明墙
   else
      atack_monster(EXCLE,x,y);
}
int decide(int x,int y)///判断(x,y)是什么东西返回它的EXCLE标号值用作碰到调用属性前的判断
{
   return map[x][y];
}
void PEOPLE_move()
{
   if(kbhit())
   {
      char move = getch();
      switch(move)
      {
      case 'w':
         if(map[PEOPLE.x-1][PEOPLE.y] == 0)
         {
            PEOPLE.x -= 1;
            mciSendString("play audio\\WALK.wav","",0,NULL);
            getimage(PEOPLE.img,"picture\\PEOPLEB.png");
         }
         else
            change_state(decide(PEOPLE.x-1,PEOPLE.y),PEOPLE.x-1,PEOPLE.y);
         break;
      case 'a':
         if(map[PEOPLE.x][PEOPLE.y-1] == 0)
         {
            PEOPLE.y -= 1;
            mciSendString("play audio\\WALK.wav","",0,NULL);
            getimage(PEOPLE.img,"picture\\PEOPLEL.png");
         }
         else
            change_state(decide(PEOPLE.x,PEOPLE.y-1),PEOPLE.x,PEOPLE.y-1);
         break;
      case 's':
         if(map[PEOPLE.x+1][PEOPLE.y] == 0)
         {
            PEOPLE.x += 1;
            mciSendString("play audio\\WALK.wav","",0,NULL);
            getimage(PEOPLE.img,"picture\\PEOPLE.png");
         }
         else
            change_state(decide(PEOPLE.x+1,PEOPLE.y),PEOPLE.x+1,PEOPLE.y);
         break;
      case 'd':
         if(map[PEOPLE.x][PEOPLE.y+1] == 0)
         {
            PEOPLE.y += 1;
            mciSendString("play audio\\WALK.wav","",0,NULL);
            getimage(PEOPLE.img,"picture\\PEOPLER.png");
         }
         else
            change_state(decide(PEOPLE.x,PEOPLE.y+1),PEOPLE.x,PEOPLE.y+1);
         break;
      }
   }
   show_map();
}
int main()
{
   PlaySound("audio\\MUSIC.wav",NULL,SND_ASYNC|SND_LOOP);
   INITGRAPH(1080,780);
   refresh();
   init();
   read_map();///初始化开局
   change_peoplexy();///初始化开局人物位置
   while(1)
   {
      PEOPLE_move();
      //show_map();
      Sleep(60);
   }
   getch();
   closegraph();
   return 0;
}

