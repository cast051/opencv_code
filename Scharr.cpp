/*----------------------------------������˵����-------------------------------------
��������:��Scharr
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
Mat srcimage, dstimage,grad_x,abs_grad_x,grad_y,abs_grad_y;//�������ͼƬ



/*----------------------------------��ȫ�ֺ�����-------------------------------------
������ȫ�ֺ�������
-----------------------------------------------------------------------------------*/



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
	namedWindow("Scharr", 1);
	//��X����Scharr
	Scharr(srcimage, grad_x,CV_16S,1,0);
	//ȡ����ֵ
	convertScaleAbs(grad_x,abs_grad_x);
	//��Y����Scharr	
	Scharr(srcimage, grad_y, CV_16S, 0, 1);
	//ȡ����ֵ
	convertScaleAbs(grad_y, abs_grad_y);
	//�ϲ��ݶ�
	addWeighted(abs_grad_x, 0.5, abs_grad_y,0.5,0,dstimage);
	//��ʾЧ��ͼ
	imshow("x����Scharr",abs_grad_x);
	imshow("y����Scharr", abs_grad_y);
	imshow("dstimage", dstimage);

	while (1)
	{
		char c = waitKey(0);
		//��q���˳�����
		if (c == 'q')
			return true;
	}
	return true;
}

