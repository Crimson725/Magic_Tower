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
int main()
{
	initgraph(800, 600);//创建窗口 800*600 ege库函数
	//PIMAGE xxx = newimage();

	//getimage(xxx, "/testResources/0_1.jpg");
	//putimage(0, 0, xxx);
	printf("Hello") ;

	//system("pause");//stdlib.h
	//test:连接测试
	getch();
	closegraph();//窗口关闭 ege库函数
	return 0;
}
