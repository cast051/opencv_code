/*----------------------------------【程序说明】-------------------------------------
程序名称:：Harris
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
Mat srcimage, dstimage, dstimage1,corner_harris_iamge, grayimage, normalimage;//输入输出图片
int Harris_thresh=1;

/*----------------------------------【全局函数】-------------------------------------
描述：全局函数声明
-----------------------------------------------------------------------------------*/
static void Harris_Callback(int, void *);


/*----------------------------------【main函数】-------------------------------------
描述：程序主函数
-----------------------------------------------------------------------------------*/
int main()
{
	//输入图片
	srcimage = imread("dog.png");
	if (srcimage.data == NULL){ cout << "图片读取错误!/r/n" << endl; return false; }
	//克隆
	dstimage1 = srcimage.clone();
	//转化为灰度图
	cvtColor(srcimage, grayimage, COLOR_BGR2GRAY);
	//高斯滤波
	//GaussianBlur(grayimage,grayimage,Size(3,3),1);
	//显示原图片
	imshow("原图", srcimage);
	//创建窗口
	namedWindow("加载原图的结果图", 1);
	//创建滚动条
	createTrackbar("Harris_thresh", "加载原图的结果图", &Harris_thresh, 10, Harris_Callback);
	//执行回调函数
	Harris_Callback(0, 0);

	while (1)
	{
		char c = waitKey(0);
		//按q可退出程序
		if (c == 'q')
			return true;
	}
	return true;
}

/*----------------------------------【Harris回调函数】----------------------------
描述：Harris回调函数
-----------------------------------------------------------------------------------*/
static void Harris_Callback(int, void *)
{
	corner_harris_iamge = Mat::zeros(srcimage.size(), CV_32FC1);

	//harris角点检测
	cornerHarris(grayimage, corner_harris_iamge, 2, 3, 0.04, BORDER_DEFAULT);

	if (Harris_thresh < 1)  Harris_thresh = 1;
	//灰度图进行阈值操作得到二值图
	threshold(corner_harris_iamge, dstimage, Harris_thresh/100000.0f, 255, THRESH_BINARY);
	////归一化
	//normalize(corner_harris_iamge, normalimage, 0, 175, NORM_MINMAX, CV_32FC1, Mat());
	////取绝对值转化为uchar
	//convertScaleAbs(normalimage, dstimage);

	// 将检测到的，且符合阈值条件的角点绘制出来
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
	//显示图片
	imshow("加载至原图的结果图", dstimage1);
	//显示图片
	imshow("Harris结果图", dstimage);
}

