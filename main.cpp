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
int main()
{
	initgraph(800, 600);//�������� 800*600 ege�⺯��
	//PIMAGE xxx = newimage();

	//getimage(xxx, "/testResources/0_1.jpg");
	//putimage(0, 0, xxx);
	printf("Hello") ;

	//system("pause");//stdlib.h
	//test:���Ӳ���
	getch();
	closegraph();//���ڹر� ege�⺯��
	return 0;
}
