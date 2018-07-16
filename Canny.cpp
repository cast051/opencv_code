/*----------------------------------������˵����-------------------------------------
��������:��Canny
��������IDE�汾��Visual Studio 2013
��������OpenCV�汾��  3.0
2018.7.10  Create by   VV
-----------------------------------------------------------------------------------*/



/*----------------------------------��ͷ�ļ���---------------------------------------
���������������ͷ�ļ�
-----------------------------------------------------------------------------------*/
#include "stdafx.h"
#include <opencv2/opencv.hpp>


/*----------------------------------�������ռ䡿-------------------------------------
����������ʹ�õ������ռ�
-----------------------------------------------------------------------------------*/
using namespace cv;
using namespace std;


/*----------------------------------��ȫ�ֱ�����-------------------------------------
������ȫ�ֱ���
-----------------------------------------------------------------------------------*/
Mat srcimage, dstimage;//�������ͼƬ

int Canny1_threshold1 = 60; //��ֵ1
int Canny1_threshold2 = 100;//��ֵ2
int Canny2_threshold1 = 60; //��ֵ1
int Canny2_threshold2 = 100;//��ֵ2

/*----------------------------------��ȫ�ֺ�����-------------------------------------
������ȫ�ֺ�������
-----------------------------------------------------------------------------------*/
static void Canny1_Callback(int, void *);
static void Canny2_Callback(int, void *);

/*----------------------------------��main������-------------------------------------
����������������
-----------------------------------------------------------------------------------*/
int main()
{
	//����ͼƬ
	srcimage = imread("dog.png");
	if (srcimage.data == NULL){ cout << "ͼƬ��ȡ����!/r/n" << endl; return false; }
	//��ʾԭͼƬ
	imshow("ԭͼ", srcimage);
	

	//��������
	namedWindow("canny1", 1);
	namedWindow("canny2", 1);

	//����������
	createTrackbar("Canny1_threshold1", "canny1", &Canny1_threshold1, 500, Canny1_Callback);
	createTrackbar("Canny1_threshold2", "canny1", &Canny1_threshold2, 500, Canny1_Callback);
	createTrackbar("Canny2_threshold1", "canny2", &Canny2_threshold1, 500, Canny2_Callback);
	createTrackbar("Canny2_threshold2", "canny2", &Canny2_threshold2, 500, Canny2_Callback);

	//ִ�лص�����
	Canny1_Callback(Canny1_threshold1, 0);
	Canny2_Callback(Canny2_threshold1, 0);


	while (1)
	{
		char c = waitKey(0);
		//��q���˳�����
		if (c == 'q')
			return true;
	}
	return true;
}

/*----------------------------------��Canny1�ص�������----------------------------
������Canny1�ص�����
-----------------------------------------------------------------------------------*/
static void Canny1_Callback(int, void *)
{
	//Canny�㷨
	Canny(srcimage, dstimage, Canny1_threshold1, Canny1_threshold2);
	//��ʾͼƬ
	imshow("canny1", dstimage);
}

/*----------------------------------��Canny2�ص�������----------------------------
������Canny2�ص�����-�߽׵�canny�÷�,ת�ɻҶ�ͼ�����룬��canny����󽫵õ��ı�Ե��Ϊ���룬����ԭͼ��Ч��ͼ�ϣ��õ���ɫ�ı�Եͼ
-----------------------------------------------------------------------------------*/
static void Canny2_Callback(int, void *)
{
	Mat gray, edg, dst;
	//ת��Ϊ�Ҷ�ͼ
	cvtColor(srcimage, gray, COLOR_RGB2GRAY);
	//��˹�˲�
	GaussianBlur(gray, edg, Size(3, 3), 0, 0);
	//canny�㷨
	Canny(edg, edg, Canny2_threshold1, Canny2_threshold2);
	//��Canny�㷨�������edg��Ϊ��Ĥ����ԭͼsrcimage����Ŀ��ͼsdt�У��õ���ɫ��Եͼ
	srcimage.copyTo(dst, edg);
	//��ʾͼƬ
	imshow("canny2", dst);
}
