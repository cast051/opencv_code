/*----------------------------------������˵����-------------------------------------
��������:��remap && warpAffine
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
Mat srcimage, dstimage, map_x, map_y;//mat��



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
	namedWindow("����ԭͼ�Ľ��ͼ", 1);

	/*---------------------Remap-------------------------*/
	dstimage.create(srcimage.size(), CV_32FC1);
	map_x.create(srcimage.size(), CV_32FC1);
	map_y.create(srcimage.size(), CV_32FC1);
	//������ӳ���������Ӧ
	for (size_t j = 0; j < srcimage.rows; j++)
	{
		for (size_t i = 0; i < srcimage.cols; i++)
		{
			map_x.at<float>(j, i) = static_cast<float>(srcimage.cols - i);
			map_y.at<float>(j, i) = static_cast<float>(srcimage.rows - j);
		}
	}
	//������ӳ��
	remap(srcimage, dstimage, map_x, map_y, INTER_LINEAR);
	imshow("remap���ͼ", dstimage);

	/*------------------warpAffine----------------------*/
	Mat dstimage1, dstimage2, rotmat(3, 4, CV_32FC1), warpmat(3, 4, CV_32FC1);//mat��
	Point2f srcTriangle[3], dstTriangle[3];
	dstimage1 = Mat::zeros(srcimage.rows, srcimage.cols, srcimage.type());
	//��ԭͼ��Ŀ��ͼ�������任
	srcTriangle[0] = Point2f(0, 0);
	srcTriangle[1] = Point2f(srcimage.cols - 1, 0);
	srcTriangle[2] = Point2f(0, srcimage.rows - 1);
	dstTriangle[0] = Point2f(0, 0);
	dstTriangle[1] = Point2f(srcimage.cols*0.32f, srcimage.rows*0.78f);
	dstTriangle[2] = Point2f(srcimage.cols*0.89f, srcimage.rows - 1);
	//�����任����
	warpmat = getAffineTransform(srcTriangle, dstTriangle);
	//����任
	warpAffine(srcimage, dstimage1, warpmat, dstimage1.size());
	//��ʾͼƬ
	imshow("warp1���ͼ", dstimage1);

	//��ȡ��ת����
	rotmat = getRotationMatrix2D(Point2f(srcimage.cols / 2, srcimage.rows / 2), 45, 0.8);
	//����任
	warpAffine(srcimage, dstimage2, rotmat, dstimage2.size());
	//��ʾͼƬ
	imshow("warp2���ͼ", dstimage2);

	while (1)
	{
		char c = waitKey(0);
		//��q���˳�����
		if (c == 'q')
			return true;
	}
	return true;
}


/*�����������ʱ�亯��
Time = getTickCount();
Time = getTickCount() - Time;
if (Time>pow(10, 6))
cout << "remap����ʱ��Ϊ: " << Time / 1000000 << "s\r\n" << endl;
else
cout << "remap����ʱ��Ϊ: " << Time / 1000 << "ms\r\n" << endl;*/