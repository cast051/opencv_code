/*----------------------------------【程序说明】-------------------------------------
程序名称:：Laplace
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

int Laplacian_KernelSize = 1; //Soble算子内核


/*----------------------------------【全局函数】-------------------------------------
描述：全局函数声明
-----------------------------------------------------------------------------------*/
static void Laplace_Callback(int, void *);


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
	namedWindow("Laplacian", 1);
	//创建滚动条
	createTrackbar("Laplacian_KernelSize", "Laplacian", &Laplacian_KernelSize, 3, Laplace_Callback);
	//执行回调函数
	Laplace_Callback(Laplacian_KernelSize, 0);

	while (1)
	{
		char c = waitKey(0);
		//按q可退出程序
		if (c == 'q')
			return true;
	}
	return true;
}

/*----------------------------------【Laplace回调函数】----------------------------
描述：Laplace回调函数
-----------------------------------------------------------------------------------*/
static void Laplace_Callback(int, void *)
{
	Mat gray, abs_dst;
	//高斯滤波
	GaussianBlur(srcimage, srcimage, Size(3,3), 0, 0);
	//转化为灰度图
	cvtColor(srcimage, gray, COLOR_BGR2GRAY);
	//Sobel算子
	Laplacian(gray, dstimage, CV_16S, Laplacian_KernelSize*2+1);
	//取绝对值
	convertScaleAbs(dstimage, abs_dst);

	//显示图片
	imshow("Laplacian", abs_dst);
}

