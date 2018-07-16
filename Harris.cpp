/*----------------------------------������˵����-------------------------------------
��������:��Harris
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
Mat srcimage, dstimage, dstimage1,corner_harris_iamge, grayimage, normalimage;//�������ͼƬ
int Harris_thresh=1;

/*----------------------------------��ȫ�ֺ�����-------------------------------------
������ȫ�ֺ�������
-----------------------------------------------------------------------------------*/
static void Harris_Callback(int, void *);


/*----------------------------------��main������-------------------------------------
����������������
-----------------------------------------------------------------------------------*/
int main()
{
	//����ͼƬ
	srcimage = imread("dog.png");
	if (srcimage.data == NULL){ cout << "ͼƬ��ȡ����!/r/n" << endl; return false; }
	//��¡
	dstimage1 = srcimage.clone();
	//ת��Ϊ�Ҷ�ͼ
	cvtColor(srcimage, grayimage, COLOR_BGR2GRAY);
	//��˹�˲�
	//GaussianBlur(grayimage,grayimage,Size(3,3),1);
	//��ʾԭͼƬ
	imshow("ԭͼ", srcimage);
	//��������
	namedWindow("����ԭͼ�Ľ��ͼ", 1);
	//����������
	createTrackbar("Harris_thresh", "����ԭͼ�Ľ��ͼ", &Harris_thresh, 10, Harris_Callback);
	//ִ�лص�����
	Harris_Callback(0, 0);

	while (1)
	{
		char c = waitKey(0);
		//��q���˳�����
		if (c == 'q')
			return true;
	}
	return true;
}

/*----------------------------------��Harris�ص�������----------------------------
������Harris�ص�����
-----------------------------------------------------------------------------------*/
static void Harris_Callback(int, void *)
{
	corner_harris_iamge = Mat::zeros(srcimage.size(), CV_32FC1);

	//harris�ǵ���
	cornerHarris(grayimage, corner_harris_iamge, 2, 3, 0.04, BORDER_DEFAULT);

	if (Harris_thresh < 1)  Harris_thresh = 1;
	//�Ҷ�ͼ������ֵ�����õ���ֵͼ
	threshold(corner_harris_iamge, dstimage, Harris_thresh/100000.0f, 255, THRESH_BINARY);
	////��һ��
	//normalize(corner_harris_iamge, normalimage, 0, 175, NORM_MINMAX, CV_32FC1, Mat());
	////ȡ����ֵת��Ϊuchar
	//convertScaleAbs(normalimage, dstimage);

	// ����⵽�ģ��ҷ�����ֵ�����Ľǵ���Ƴ���
	for (size_t j = 0; j < dstimage.rows; j++)
	{
		for (size_t i = 0; i < dstimage.cols; i++)
		{
			if ((int)dstimage.at<float>(j, i) != 0)
			{
				circle(dstimage1, Point(i, j), 5, Scalar(0, 255, 0), 2, 8, 0);
				circle(dstimage, Point(i, j), 5, Scalar(0, 255, 0), 2, 8, 0);
			}
		}

	}
	//��ʾͼƬ
	imshow("������ԭͼ�Ľ��ͼ", dstimage1);
	//��ʾͼƬ
	imshow("Harris���ͼ", dstimage);
}

