/*----------------------------------【程序说明】-------------------------------------
程序名称:：Canny
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
Mat srcimage, dstimage;//输入输出图片

int Canny1_threshold1 = 60; //阈值1
int Canny1_threshold2 = 100;//阈值2
int Canny2_threshold1 = 60; //阈值1
int Canny2_threshold2 = 100;//阈值2

/*----------------------------------【全局函数】-------------------------------------
描述：全局函数声明
-----------------------------------------------------------------------------------*/
static void Canny1_Callback(int, void *);
static void Canny2_Callback(int, void *);

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
	namedWindow("canny1", 1);
	namedWindow("canny2", 1);

	//创建滚动条
	createTrackbar("Canny1_threshold1", "canny1", &Canny1_threshold1, 500, Canny1_Callback);
	createTrackbar("Canny1_threshold2", "canny1", &Canny1_threshold2, 500, Canny1_Callback);
	createTrackbar("Canny2_threshold1", "canny2", &Canny2_threshold1, 500, Canny2_Callback);
	createTrackbar("Canny2_threshold2", "canny2", &Canny2_threshold2, 500, Canny2_Callback);

	//执行回调函数
	Canny1_Callback(Canny1_threshold1, 0);
	Canny2_Callback(Canny2_threshold1, 0);


	while (1)
	{
		char c = waitKey(0);
		//按q可退出程序
		if (c == 'q')
			return true;
	}
	return true;
}

/*----------------------------------【Canny1回调函数】----------------------------
描述：Canny1回调函数
-----------------------------------------------------------------------------------*/
static void Canny1_Callback(int, void *)
{
	//Canny算法
	Canny(srcimage, dstimage, Canny1_threshold1, Canny1_threshold2);
	//显示图片
	imshow("canny1", dstimage);
}

/*----------------------------------【Canny2回调函数】----------------------------
描述：Canny2回调函数-高阶的canny用法,转成灰度图，降噪，用canny，最后将得到的边缘作为掩码，拷贝原图到效果图上，得到彩色的边缘图
-----------------------------------------------------------------------------------*/
static void Canny2_Callback(int, void *)
{
	Mat gray, edg, dst;
	//转化为灰度图
	cvtColor(srcimage, gray, COLOR_RGB2GRAY);
	//高斯滤波
	GaussianBlur(gray, edg, Size(3, 3), 0, 0);
	//canny算法
	Canny(edg, edg, Canny2_threshold1, Canny2_threshold2);
	//将Canny算法计算出的edg作为掩膜，将原图srcimage拷到目标图sdt中，得到彩色边缘图
	srcimage.copyTo(dst, edg);
	//显示图片
	imshow("canny2", dst);
}
