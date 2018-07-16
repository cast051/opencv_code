/*----------------------------------【程序说明】-------------------------------------
程序名称:：Sobel
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

int Sobel_KernelSize = 1; //Soble算子内核


/*----------------------------------【全局函数】-------------------------------------
描述：全局函数声明
-----------------------------------------------------------------------------------*/
static void Sobel_Callback(int, void *);


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
	namedWindow("Sobel", 1);
	//创建滚动条
	createTrackbar("Sobel_KernelSize", "Sobel", &Sobel_KernelSize, 3, Sobel_Callback);
	//执行回调函数
	Sobel_Callback(Sobel_KernelSize, 0);

	while (1)
	{
		char c = waitKey(0);
		//按q可退出程序
		if (c == 'q')
			return true;
	}
	return true;
}

/*----------------------------------【Sobel回调函数】----------------------------
描述：Sobel回调函数
-----------------------------------------------------------------------------------*/
static void Sobel_Callback(int, void *)
{
	Mat grad_x, grad_y, abs_grad_x, abs_grad_y;
	//Sobel算子
	//求取x、y方向梯度
	Sobel(srcimage, grad_x, CV_16S, 1, 0, Sobel_KernelSize*2+1, 1, 1, BORDER_DEFAULT);
	Sobel(srcimage, grad_y, CV_16S, 0, 1, Sobel_KernelSize*2+1, 1, 1, BORDER_DEFAULT);
	//取绝对值
	convertScaleAbs(grad_x, abs_grad_x);
	convertScaleAbs(grad_y, abs_grad_y);
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, dstimage);
	//显示图片
	imshow("grad_x", grad_x);
	imshow("grad_y", grad_y);
	imshow("Sobel", dstimage);
}

