/*----------------------------------【程序说明】-------------------------------------
程序名称:：SURF
开发所用IDE版本：Visual Studio 2013
开发所用OpenCV版本：  3.0
2018.7.13  Create by   VV
-----------------------------------------------------------------------------------*/



/*----------------------------------【头文件】---------------------------------------
描述：程序包含的头文件
-----------------------------------------------------------------------------------*/
#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

/*----------------------------------【命名空间】-------------------------------------
描述：程序使用的命名空间
-----------------------------------------------------------------------------------*/
using namespace cv;
using namespace std;
using namespace xfeatures2d;


/*----------------------------------【全局变量】-------------------------------------
描述：全局变量
-----------------------------------------------------------------------------------*/
Mat srcimage1, srcimage2,dstimage;//mat类
Mat descriptors1, descriptors2;   //描述符
vector<KeyPoint> KeyPoint1, KeyPoint2;//关键点



#define Hessian_Threshold 700


/*----------------------------------【全局函数】-------------------------------------
描述：全局函数声明
-----------------------------------------------------------------------------------*/



/*----------------------------------【main函数】-------------------------------------
描述：程序主函数
-----------------------------------------------------------------------------------*/
int main()
{
	//定义一个SurfFeatureDetector（SURF） 特征检测类对象
	SurfFeatureDetector detect_key(Hessian_Threshold);
	//定义描述符（特征向量）
	SurfDescriptorExtractor extractor;
	//使用BruteForce进行匹配
	// 实例化一个匹配器
	BruteForceMatcher< L2<float> > matcher;
	vector< DMatch > matches;
	//输入图片
	srcimage1 = imread("im1.png");
	if (srcimage1.data == NULL){ cout << "图片1读取错误!/r/n" << endl; return false; }
	srcimage2 = imread("im2.png");
	if (srcimage1.data == NULL){ cout << "图片2读取错误!/r/n" << endl; return false; }
	//显示原图片
	//imshow("原图1", srcimage1);
	//imshow("原图2", srcimage2);
	//创建窗口
	namedWindow("加载原图的结果图", 1);
	//检测特征点
	detect_key.detect(srcimage1, KeyPoint1);
	detect_key.detect(srcimage2, KeyPoint2);
	//计算描述符
	extractor.compute(srcimage1, KeyPoint1, descriptors1);
	extractor.compute(srcimage2, KeyPoint2, descriptors2);
	//匹配描述子
	matcher.match(descriptors1, descriptors2, matches);
	//绘制从两个图像中匹配出的关键点
	drawMatches(srcimage1, KeyPoint1, srcimage2, KeyPoint2, matches, dstimage);//进行绘制
	//显示效果图
	imshow("匹配图", dstimage);

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