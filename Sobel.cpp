/*----------------------------------������˵����-------------------------------------
��������:��Sobel
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

int Sobel_KernelSize = 1; //Soble�����ں�


/*----------------------------------��ȫ�ֺ�����-------------------------------------
������ȫ�ֺ�������
-----------------------------------------------------------------------------------*/
static void Sobel_Callback(int, void *);


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
	namedWindow("Sobel", 1);
	//����������
	createTrackbar("Sobel_KernelSize", "Sobel", &Sobel_KernelSize, 3, Sobel_Callback);
	//ִ�лص�����
	Sobel_Callback(Sobel_KernelSize, 0);

	while (1)
	{
		char c = waitKey(0);
		//��q���˳�����
		if (c == 'q')
			return true;
	}
	return true;
}

/*----------------------------------��Sobel�ص�������----------------------------
������Sobel�ص�����
-----------------------------------------------------------------------------------*/
static void Sobel_Callback(int, void *)
{
	Mat grad_x, grad_y, abs_grad_x, abs_grad_y;
	//Sobel����
	//��ȡx��y�����ݶ�
	Sobel(srcimage, grad_x, CV_16S, 1, 0, Sobel_KernelSize*2+1, 1, 1, BORDER_DEFAULT);
	Sobel(srcimage, grad_y, CV_16S, 0, 1, Sobel_KernelSize*2+1, 1, 1, BORDER_DEFAULT);
	//ȡ����ֵ
	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dstimage);
	//��ʾͼƬ
	imshow("grad_x", grad_x);
	imshow("grad_y", grad_y);
	imshow("Sobel", dstimage);
}

