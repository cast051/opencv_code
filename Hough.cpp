/*----------------------------------【程序说明】-------------------------------------
程序名称:：Hough
开发所用IDE版本：Visual Studio 2013
开发所用OpenCV版本：  3.0
2018.7.10  Create by   VV
-----------------------------------------------------------------------------------*/



/*----------------------------------【头文件】---------------------------------------
描述：程序包含的头文件
-----------------------------------------------------------------------------------*/
#include "stdafx.h"
#include <opencv2/opencv.hpp>


/*----------------------------------【命名空间】-------------------------------------
描述：程序使用的命名空间
-----------------------------------------------------------------------------------*/
using namespace cv;
using namespace std;


/*----------------------------------【全局变量】-------------------------------------
描述：全局变量
-----------------------------------------------------------------------------------*/
Mat srcimage, srcimage1, dstimage, dstimage1, midimage, midimage1;//输入输出图片

int Canny1_threshold1 = 60; //阈值1
int Canny1_threshold2 = 100;//阈值2


/*----------------------------------【全局函数】-------------------------------------
描述：全局函数声明
-----------------------------------------------------------------------------------*/


/*----------------------------------【main函数】-------------------------------------
描述：程序主函数
-----------------------------------------------------------------------------------*/
int main()
{
	//定义line
	vector<Vec2f> lines;
	vector<Vec4i> linesP;
	//输入图片
	srcimage = imread("line.png");
	if (srcimage.data == NULL){ cout << "图片读取错误!/r/n" << endl; return false; }
	srcimage1 = imread("circle.jpg");
	if (srcimage1.data == NULL){ cout << "图片读取错误!/r/n" << endl; return false; }
	//创建窗口
	namedWindow("HoughLines", 1);
	//显示原图片
	imshow("原图", srcimage);
	imshow("原图", srcimage1);

	//Canny算法输出二值图
	Canny(srcimage, midimage, Canny1_threshold1, Canny1_threshold2);
	//显示canny边缘检测后的图片
	imshow("边缘检测后的图片", midimage);
	//转变为灰度图
	cvtColor(midimage, dstimage, COLOR_GRAY2BGR);


	//霍夫线变换
	HoughLines(midimage, lines, 1, CV_PI / 180, 150, 0, 0);
	//画出提取出的line
	for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		Point pt1, pt2;
		//霍夫线变换只能计算出直线，不能计算线段，1000是自定义的
		pt1.x = cvRound(rho*cos(theta) - 1000 * sin(theta));
		pt1.y = cvRound(rho*sin(theta) + 1000 * cos(theta));
		pt2.x = cvRound(rho*cos(theta) + 1000 * sin(theta));
		pt2.y = cvRound(rho*sin(theta) - 1000 * cos(theta));

		line(dstimage, pt1, pt2, Scalar(55, 100, 195), 1);
	}
	//显示图片
	imshow("houghlines输出图片", dstimage);


	//概率霍夫变换
	HoughLinesP(midimage, linesP,1,CV_PI/180,80,50,10);
	//画出提取出的lineP
	for (size_t i = 0; i < linesP.size(); i++)
	{
		line(dstimage, Point(linesP[i][0], linesP[i][1]), Point(linesP[i][2], linesP[i][3]), Scalar(55, 100, 195), 1);
	}
	//显示图片
	imshow("houghlinesP输出图片", dstimage);

	//定义圆
	vector<Vec3f> circles;
	//转变为灰度图
	cvtColor(srcimage1, midimage1, COLOR_BGR2GRAY);
	//高斯滤波
	GaussianBlur(midimage1, dstimage1,Size(9,9),2,2);
	//霍夫圆变换
	HoughCircles(dstimage1, circles, HOUGH_GRADIENT, 1.5, 40, 200, 100, 0, 0);
	for (size_t i = 0; i < circles.size(); i++)
	{
		//绘制圆心
		circle(srcimage1, Point(circles[i][0], circles[i][1]), 3, Scalar(0, 255, 0), -1, 8, 0);
		//绘制圆
		circle(srcimage1, Point(circles[i][0], circles[i][1]), circles[i][2], Scalar(155, 50, 255), 3, 8, 0);
	}
	//显示图片
	imshow("霍夫圆变换结果图",srcimage1);

	while (1)
	{
		char c = waitKey(0);
		//按q可退出程序
		if (c == 'q')
			return true;
	}
	return true;
}


