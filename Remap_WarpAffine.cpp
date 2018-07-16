/*----------------------------------【程序说明】-------------------------------------
程序名称:：remap && warpAffine
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
Mat srcimage, dstimage, map_x, map_y;//mat类



/*----------------------------------【全局函数】-------------------------------------
描述：全局函数声明
-----------------------------------------------------------------------------------*/



/*----------------------------------【main函数】-------------------------------------
描述：程序主函数
-----------------------------------------------------------------------------------*/
int main()
{
	//输入图片
	srcimage = imread("dog.png");
	if (srcimage.data == NULL){ cout << "图片读取错误!/r/n" << endl; return false; }
	//显示原图片
	imshow("原图", srcimage);
	//创建窗口
	namedWindow("加载原图的结果图", 1);

	/*---------------------Remap-------------------------*/
	dstimage.create(srcimage.size(), CV_32FC1);
	map_x.create(srcimage.size(), CV_32FC1);
	map_y.create(srcimage.size(), CV_32FC1);
	//设置重映射后的坐标对应
	for (size_t j = 0; j < srcimage.rows; j++)
	{
		for (size_t i = 0; i < srcimage.cols; i++)
		{
			map_x.at<float>(j, i) = static_cast<float>(srcimage.cols - i);
			map_y.at<float>(j, i) = static_cast<float>(srcimage.rows - j);
		}
	}
	//进行重映射
	remap(srcimage, dstimage, map_x, map_y, INTER_LINEAR);
	imshow("remap结果图", dstimage);

	/*------------------warpAffine----------------------*/
	Mat dstimage1, dstimage2, rotmat(3, 4, CV_32FC1), warpmat(3, 4, CV_32FC1);//mat类
	Point2f srcTriangle[3], dstTriangle[3];
	dstimage1 = Mat::zeros(srcimage.rows, srcimage.cols, srcimage.type());
	//在原图和目标图计算仿射变换
	srcTriangle[0] = Point2f(0, 0);
	srcTriangle[1] = Point2f(srcimage.cols - 1, 0);
	srcTriangle[2] = Point2f(0, srcimage.rows - 1);
	dstTriangle[0] = Point2f(0, 0);
	dstTriangle[1] = Point2f(srcimage.cols*0.32f, srcimage.rows*0.78f);
	dstTriangle[2] = Point2f(srcimage.cols*0.89f, srcimage.rows - 1);
	//求仿射变换矩阵
	warpmat = getAffineTransform(srcTriangle, dstTriangle);
	//仿射变换
	warpAffine(srcimage, dstimage1, warpmat, dstimage1.size());
	//显示图片
	imshow("warp1结果图", dstimage1);

	//求取旋转矩阵
	rotmat = getRotationMatrix2D(Point2f(srcimage.cols / 2, srcimage.rows / 2), 45, 0.8);
	//仿射变换
	warpAffine(srcimage, dstimage2, rotmat, dstimage2.size());
	//显示图片
	imshow("warp2结果图", dstimage2);

	while (1)
	{
		char c = waitKey(0);
		//按q可退出程序
		if (c == 'q')
			return true;
	}
	return true;
}


/*计算程序运行时间函数
Time = getTickCount();
Time = getTickCount() - Time;
if (Time>pow(10, 6))
cout << "remap运行时间为: " << Time / 1000000 << "s\r\n" << endl;
else
cout << "remap运行时间为: " << Time / 1000 << "ms\r\n" << endl;*/