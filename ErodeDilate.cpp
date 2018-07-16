/*----------------------------------【程序说明】-------------------------------------
程序名称:：膨胀与腐蚀、开运算、闭运算、形态学梯度、顶帽、黑帽
开发所用IDE版本：Visual Studio 2013
开发所用OpenCV版本：  3.0
2018.7.10  Create by   VV
-----------------------------------------------------------------------------------*/



/*----------------------------------【头文件】---------------------------------------
描述：程序包含的头文件
-----------------------------------------------------------------------------------*/
#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <vector>


/*----------------------------------【命名空间】-------------------------------------
描述：程序使用的命名空间
-----------------------------------------------------------------------------------*/
using namespace cv;
using namespace std;


/*----------------------------------【全局变量】-------------------------------------
描述：全局变量
-----------------------------------------------------------------------------------*/
Mat srcimage, dstimage;//输入输出图片

int MaxIterationNum = 10;//最大内核=MaxIterationNum*2+1
int ErodeDilateNum = 0;//内核=ErodeDilateNum*2+1
int ErodeDilateSwitch = 0;//腐蚀/膨胀
int OpenCloseNum = 0;//内核=OpenCloseNum*2+1
int OpenCloseSwitch = 0;//开/闭
int TopBlackHatNum = 0;//内核=TopBlackHatNum*2+1
int TopBlackHatSwitch = 0;//顶帽/黑帽

MorphShapes MorShape = MORPH_RECT;//元素结构形状

/*----------------------------------【全局函数】-------------------------------------
描述：全局函数声明
-----------------------------------------------------------------------------------*/
static void ErodeDilate_Callback(int, void *);
static void OpenClose_Callback(int, void *);
static void TopBlackHat_Callback(int, void *);
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
	namedWindow("腐蚀/膨胀", 1);
	namedWindow("开运算/闭运算", 1);
	namedWindow("顶帽/黑帽", 1);

	//创建滚动条
	createTrackbar("腐蚀/膨胀", "腐蚀/膨胀", &ErodeDilateSwitch, 1);
	createTrackbar("迭代值", "腐蚀/膨胀", &ErodeDilateNum, MaxIterationNum * 2 + 1, ErodeDilate_Callback);
	createTrackbar("开运算/闭运算", "开运算/闭运算", &OpenCloseSwitch, 1);
	createTrackbar("迭代值", "开运算/闭运算", &OpenCloseNum, MaxIterationNum * 2 + 1, OpenClose_Callback);
	createTrackbar("顶帽/黑帽", "顶帽/黑帽", &TopBlackHatSwitch, 1);
	createTrackbar("迭代值", "顶帽/黑帽", &TopBlackHatNum, MaxIterationNum * 2 + 1, TopBlackHat_Callback);

	//执行回调函数
	ErodeDilate_Callback(ErodeDilateNum, 0);
	OpenClose_Callback(OpenCloseNum, 0);
	TopBlackHat_Callback(TopBlackHatNum, 0);

	while (1)
	{
		char c = waitKey(0);
		//按q可退出程序,按数字1，2，3可切换元素结构
		if (c == 'q')
			return true;
		else if (c == '1')
			MorShape = MORPH_RECT;
		else if (c == '2')
			MorShape = MORPH_CROSS;
		else if (c == '3')
			MorShape = MORPH_ELLIPSE;
	}
	return true;
}

/*----------------------------------【腐蚀/膨胀回调函数】----------------------------
描述：腐蚀/膨胀回调函数
-----------------------------------------------------------------------------------*/
static void ErodeDilate_Callback(int, void *)
{
	//定义核
	Mat element = getStructuringElement(MorShape, Size(ErodeDilateNum * 2 + 1, ErodeDilateNum * 2 + 1));
	if (ErodeDilateSwitch == 0)
		//腐蚀
		morphologyEx(srcimage, dstimage, MORPH_ERODE, element);
	else if (ErodeDilateSwitch == 1)
		//膨胀
		morphologyEx(srcimage, dstimage, MORPH_DILATE, element);

	imshow("腐蚀/膨胀", dstimage);

}
/*----------------------------------【腐蚀/膨胀回调函数】----------------------------
描述：开运算/闭运算
-----------------------------------------------------------------------------------*/
static void OpenClose_Callback(int, void *)
{
	//定义核
	Mat element = getStructuringElement(MorShape, Size(OpenCloseNum * 2 + 1, OpenCloseNum * 2 + 1));
	if (OpenCloseSwitch == 0)
		//开运算
		morphologyEx(srcimage, dstimage, MORPH_OPEN, element);
	else if (OpenCloseSwitch == 1)
		//闭运算
		morphologyEx(srcimage, dstimage, MORPH_CLOSE, element);

	imshow("开运算/闭运算", dstimage);


}
/*----------------------------------【顶帽/礼帽回调函数】----------------------------
描述：顶帽/礼帽
-----------------------------------------------------------------------------------*/
static void TopBlackHat_Callback(int, void *)
{
	//定义核
	Mat element = getStructuringElement(MorShape, Size(TopBlackHatNum * 2 + 1, TopBlackHatNum * 2 + 1));
	if (TopBlackHatSwitch == 0)
		//顶帽
		morphologyEx(srcimage, dstimage, MORPH_TOPHAT, element);
	else if (TopBlackHatSwitch == 1)
		//礼帽
		morphologyEx(srcimage, dstimage, MORPH_BLACKHAT, element);

	imshow("顶帽/黑帽", dstimage);
}

/*----------------------------------【重要函数】-------------------------------------
描述：实现腐蚀、膨胀、开运算、闭运算、形态学梯度、顶帽、黑帽函数
-----------------------------------------------------------------------------------*/

/*实现腐蚀、膨胀、开运算、闭运算、形态学梯度、顶帽、黑帽函数
morphologyEx(srcimage, dstimage, MORPH_ERODE, element);
MORPH_ERODE = 0, //!< see cv::erode
MORPH_DILATE = 1, //!< see cv::dilate
MORPH_OPEN = 2, //!< an opening operation
MORPH_CLOSE = 3, //!< a closing operation
MORPH_GRADIENT = 4, //!< a morphological gradient
MORPH_TOPHAT = 5, //!< "top hat"
MORPH_BLACKHAT = 6  //!< "black hat"*/