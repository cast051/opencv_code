/*----------------------------------【程序说明】-------------------------------------
程序名称:：pyramid
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
	namedWindow("金字塔", 1);

	while (1)
	{
		char c = waitKey(0);
		switch (c)
		{
			case 'q':
				return true;
				break;
			case '1':
				cout << "resize放大1倍\r\n" << endl;
				resize(srcimage, dstimage, Size(srcimage.cols * 2, srcimage.rows * 2));
				break;
			case '2':
				cout << "resize缩小1倍\r\n" << endl;
				resize(srcimage, dstimage, Size(srcimage.cols / 2, srcimage.rows / 2));
				break;
			case '3':
				cout << "pyrUP放大1倍\r\n" << endl;
				pyrUp(srcimage, dstimage, Size(srcimage.cols * 2, srcimage.rows * 2));
				break;
			case '4':
				cout << "pyrDown缩小1倍\r\n" << endl;
				pyrDown(srcimage, dstimage, Size(srcimage.cols / 2, srcimage.rows / 2));
				break;
			default:
				cout << "无效指令\r\n" << endl;
				break;		
		}
		imshow("缩放图", dstimage);
	}
	return true;
}

