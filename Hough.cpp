/*----------------------------------������˵����-------------------------------------
��������:��Hough
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
Mat srcimage, srcimage1, dstimage, dstimage1, midimage, midimage1;//�������ͼƬ

int Canny1_threshold1 = 60; //��ֵ1
int Canny1_threshold2 = 100;//��ֵ2


/*----------------------------------��ȫ�ֺ�����-------------------------------------
������ȫ�ֺ�������
-----------------------------------------------------------------------------------*/


/*----------------------------------��main������-------------------------------------
����������������
-----------------------------------------------------------------------------------*/
int main()
{
	//����line
	vector<Vec2f> lines;
	vector<Vec4i> linesP;
	//����ͼƬ
	srcimage = imread("line.png");
	if (srcimage.data == NULL){ cout << "ͼƬ��ȡ����!/r/n" << endl; return false; }
	srcimage1 = imread("circle.jpg");
	if (srcimage1.data == NULL){ cout << "ͼƬ��ȡ����!/r/n" << endl; return false; }
	//��������
	namedWindow("HoughLines", 1);
	//��ʾԭͼƬ
	imshow("ԭͼ", srcimage);
	imshow("ԭͼ", srcimage1);

	//Canny�㷨�����ֵͼ
	Canny(srcimage, midimage, Canny1_threshold1, Canny1_threshold2);
	//��ʾcanny��Ե�����ͼƬ
	imshow("��Ե�����ͼƬ", midimage);
	//ת��Ϊ�Ҷ�ͼ
	cvtColor(midimage, dstimage, COLOR_GRAY2BGR);


	//�����߱任
	HoughLines(midimage, lines, 1, CV_PI / 180, 150, 0, 0);
	//������ȡ����line
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		//�����߱任ֻ�ܼ����ֱ�ߣ����ܼ����߶Σ�1000���Զ����
		pt1.x = cvRound(rho*cos(theta) - 1000 * sin(theta));
		pt1.y = cvRound(rho*sin(theta) + 1000 * cos(theta));
		pt2.x = cvRound(rho*cos(theta) + 1000 * sin(theta));
		pt2.y = cvRound(rho*sin(theta) - 1000 * cos(theta));

		line(dstimage, pt1, pt2, Scalar(55, 100, 195), 1);
	}
	//��ʾͼƬ
	imshow("houghlines���ͼƬ", dstimage);


	//���ʻ���任
	HoughLinesP(midimage, linesP,1,CV_PI/180,80,50,10);
	//������ȡ����lineP
	for (size_t i = 0; i < linesP.size(); i++)
	{
		line(dstimage, Point(linesP[i][0], linesP[i][1]), Point(linesP[i][2], linesP[i][3]), Scalar(55, 100, 195), 1);
	}
	//��ʾͼƬ
	imshow("houghlinesP���ͼƬ", dstimage);

	//����Բ
	vector<Vec3f> circles;
	//ת��Ϊ�Ҷ�ͼ
	cvtColor(srcimage1, midimage1, COLOR_BGR2GRAY);
	//��˹�˲�
	GaussianBlur(midimage1, dstimage1,Size(9,9),2,2);
	//����Բ�任
	HoughCircles(dstimage1, circles, HOUGH_GRADIENT, 1.5, 40, 200, 100, 0, 0);
	for (size_t i = 0; i < circles.size(); i++)
	{
		//����Բ��
		circle(srcimage1, Point(circles[i][0], circles[i][1]), 3, Scalar(0, 255, 0), -1, 8, 0);
		//����Բ
		circle(srcimage1, Point(circles[i][0], circles[i][1]), circles[i][2], Scalar(155, 50, 255), 3, 8, 0);
	}
	//��ʾͼƬ
	imshow("����Բ�任���ͼ",srcimage1);

	while (1)
	{
		char c = waitKey(0);
		//��q���˳�����
		if (c == 'q')
			return true;
	}
	return true;
}


