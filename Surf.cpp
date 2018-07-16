/*----------------------------------������˵����-------------------------------------
��������:��SURF
��������IDE�汾��Visual Studio 2013
��������OpenCV�汾��  3.0
2018.7.13  Create by   VV
-----------------------------------------------------------------------------------*/



/*----------------------------------��ͷ�ļ���---------------------------------------
���������������ͷ�ļ�
-----------------------------------------------------------------------------------*/
#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d/nonfree.hpp>

/*----------------------------------�������ռ䡿-------------------------------------
����������ʹ�õ������ռ�
-----------------------------------------------------------------------------------*/
using namespace cv;
using namespace std;
using namespace xfeatures2d;


/*----------------------------------��ȫ�ֱ�����-------------------------------------
������ȫ�ֱ���
-----------------------------------------------------------------------------------*/
Mat srcimage1, srcimage2,dstimage;//mat��
Mat descriptors1, descriptors2;   //������
vector<KeyPoint> KeyPoint1, KeyPoint2;//�ؼ���



#define Hessian_Threshold 700


/*----------------------------------��ȫ�ֺ�����-------------------------------------
������ȫ�ֺ�������
-----------------------------------------------------------------------------------*/



/*----------------------------------��main������-------------------------------------
����������������
-----------------------------------------------------------------------------------*/
int main()
{
	//����һ��SurfFeatureDetector��SURF�� ������������
	SurfFeatureDetector detect_key(Hessian_Threshold);
	//����������������������
	SurfDescriptorExtractor extractor;
	//ʹ��BruteForce����ƥ��
	// ʵ����һ��ƥ����
	BruteForceMatcher< L2<float> > matcher;
	vector< DMatch > matches;
	//����ͼƬ
	srcimage1 = imread("im1.png");
	if (srcimage1.data == NULL){ cout << "ͼƬ1��ȡ����!/r/n" << endl; return false; }
	srcimage2 = imread("im2.png");
	if (srcimage1.data == NULL){ cout << "ͼƬ2��ȡ����!/r/n" << endl; return false; }
	//��ʾԭͼƬ
	//imshow("ԭͼ1", srcimage1);
	//imshow("ԭͼ2", srcimage2);
	//��������
	namedWindow("����ԭͼ�Ľ��ͼ", 1);
	//���������
	detect_key.detect(srcimage1, KeyPoint1);
	detect_key.detect(srcimage2, KeyPoint2);
	//����������
	extractor.compute(srcimage1, KeyPoint1, descriptors1);
	extractor.compute(srcimage2, KeyPoint2, descriptors2);
	//ƥ��������
	matcher.match(descriptors1, descriptors2, matches);
	//���ƴ�����ͼ����ƥ����Ĺؼ���
	drawMatches(srcimage1, KeyPoint1, srcimage2, KeyPoint2, matches, dstimage);//���л���
	//��ʾЧ��ͼ
	imshow("ƥ��ͼ", dstimage);

	while (1)
	{
		char c = waitKey(0);
		//��q���˳�����
		if (c == 'q')
			return true;
	}
	return true;
}


/*�����������ʱ�亯��
Time = getTickCount();
Time = getTickCount() - Time;
if (Time>pow(10, 6))
cout << "remap����ʱ��Ϊ: " << Time / 1000000 << "s\r\n" << endl;
else
cout << "remap����ʱ��Ϊ: " << Time / 1000 << "ms\r\n" << endl;*/