/*----------------------------------【程序说明】-------------------------------------
程序名称:：ORB
开发所用IDE版本：Visual Studio 2013
开发所用OpenCV版本：  3.0
2018.7.20  Create by   VV
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
Mat srcimage1, srcimage2;//输入输出图片




/*----------------------------------【全局函数】-------------------------------------
描述：全局函数声明
-----------------------------------------------------------------------------------*/



/*----------------------------------【main函数】-------------------------------------
描述：程序主函数
-----------------------------------------------------------------------------------*/
int main()
{
	//输入图片
	srcimage1 = imread("1.jpg");
	if (srcimage1.data == NULL){ cout << "图片1读取错误!/r/n" << endl; return false; }
	srcimage2 = imread("2.jpg");
	if (srcimage2.data == NULL){ cout << "图片2读取错误!/r/n" << endl; return false; }

	//创建窗口
	namedWindow("ORB", 1);
	//创建ORB类型数据
	Ptr<ORB> orb = ORB::create();
	//定义关键点
	vector<KeyPoint> keypoints1, keypoints2;
	//特征点检测
	orb->detect(srcimage1, keypoints1);
	orb->detect(srcimage2, keypoints2);
	//定义描述子
	Mat descriptors1, descriptors2;
	//计算描述子
	orb->compute(srcimage1, keypoints1, descriptors1);
	orb->compute(srcimage2, keypoints2, descriptors2);
	//定义关键点输出图像Mat
	Mat dstimage1, dstimage2;
	//这里并没有用到描述子，描述子的作用是用于后面的关键点筛选。
	drawKeypoints(srcimage1, keypoints1, dstimage1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(srcimage2, keypoints2, dstimage2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	//显示ORB特征点
	imshow("ORB特征点1", dstimage1);
	imshow("ORB特征点2", dstimage2);

	//创建一个匹配点数组，用于承接匹配出的DMatch,matches类型为数组，元素类型为DMatch
	vector<DMatch> matches;
	//创建一个BFMatcher匹配器，BFMatcher类构造函数如下：两个参数都有默认值，但是第一个距离类型下面使用的并不是默认值，而是汉明距离
	BFMatcher matcher(NORM_HAMMING);
	//调用matcher的match方法进行匹配,这里用到了描述子，没有用关键点。
	//匹配出来的结果写入上方定义的matches[]数组中
	matcher.match(descriptors1, descriptors2, matches);
	//第四步：遍历matches[]数组，找出匹配点的最大距离和最小距离，用于后面的匹配点筛选。
	//这里的距离是上方求出的汉明距离数组，汉明距离表征了两个匹配的相似程度，所以也就找出了最相似和最不相似的两组点之间的距离。
	double min_dist = 0, max_dist = 0;//定义距离
	for (int i = 0; i < descriptors1.rows; ++i)//遍历
	{
		double dist = matches[i].distance;
		if (dist<min_dist) min_dist = dist;
		if (dist>max_dist) max_dist = dist;
	}
	//输出最大最小汉明距离
	cout << "Max dist:" << max_dist << endl;
	cout << "Min dist:" << min_dist << endl;
	//第五步：根据最小距离，对匹配点进行筛选，
	//当描述子之间的距离大于两倍的min_dist，即认为匹配有误，舍弃掉。
	//但是有时最小距离非常小，比如趋近于0了，所以这样就会导致min_dist到2*min_dist之间没有几个匹配。
	// 所以，在2*min_dist小于30的时候，就取30当上限值，小于30即可，不用2*min_dist这个值了
	std::vector<DMatch> good_matches;
	for (int j = 0; j < descriptors1.rows; ++j)
	{
		if (matches[j].distance <= max(2 * min_dist, 30.0))
			good_matches.push_back(matches[j]);
	}
	Mat img_match;//所有匹配点图
	//这里看一下drawMatches()原型参数，简单用法就是：图1，图1关键点，图2，图2关键点，匹配数组，承接图像，后面的有默认值
	drawMatches(srcimage1, keypoints1, srcimage2, keypoints2, matches, img_match);
	imshow("所有匹配点对", img_match);

	Mat img_goodmatch;//筛选后的匹配点图
	drawMatches(srcimage1, keypoints1, srcimage2, keypoints2, good_matches, img_goodmatch);
	imshow("筛选后的匹配点对", img_goodmatch);

	while (1)
	{
		char c = waitKey(0);
		//按q可退出程序
		if (c == 'q')
			return true;
	}
	return true;
}

