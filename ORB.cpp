/*----------------------------------������˵����-------------------------------------
��������:��ORB
��������IDE�汾��Visual Studio 2013
��������OpenCV�汾��  3.0
2018.7.20  Create by   VV
-----------------------------------------------------------------------------------*/



/*----------------------------------��ͷ�ļ���---------------------------------------
���������������ͷ�ļ�
-----------------------------------------------------------------------------------*/
#include "stdafx.h"
#include <opencv2/opencv.hpp>


/*----------------------------------�������ռ䡿-------------------------------------
����������ʹ�õ������ռ�
-----------------------------------------------------------------------------------*/
using namespace cv;
using namespace std;


/*----------------------------------��ȫ�ֱ�����-------------------------------------
������ȫ�ֱ���
-----------------------------------------------------------------------------------*/
Mat srcimage1, srcimage2;//�������ͼƬ




/*----------------------------------��ȫ�ֺ�����-------------------------------------
������ȫ�ֺ�������
-----------------------------------------------------------------------------------*/



/*----------------------------------��main������-------------------------------------
����������������
-----------------------------------------------------------------------------------*/
int main()
{
	//����ͼƬ
	srcimage1 = imread("1.jpg");
	if (srcimage1.data == NULL){ cout << "ͼƬ1��ȡ����!/r/n" << endl; return false; }
	srcimage2 = imread("2.jpg");
	if (srcimage2.data == NULL){ cout << "ͼƬ2��ȡ����!/r/n" << endl; return false; }

	//��������
	namedWindow("ORB", 1);
	//����ORB��������
	Ptr<ORB> orb = ORB::create();
	//����ؼ���
	vector<KeyPoint> keypoints1, keypoints2;
	//��������
	orb->detect(srcimage1, keypoints1);
	orb->detect(srcimage2, keypoints2);
	//����������
	Mat descriptors1, descriptors2;
	//����������
	orb->compute(srcimage1, keypoints1, descriptors1);
	orb->compute(srcimage2, keypoints2, descriptors2);
	//����ؼ������ͼ��Mat
	Mat dstimage1, dstimage2;
	//���ﲢû���õ������ӣ������ӵ����������ں���Ĺؼ���ɸѡ��
	drawKeypoints(srcimage1, keypoints1, dstimage1, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	drawKeypoints(srcimage2, keypoints2, dstimage2, Scalar::all(-1), DrawMatchesFlags::DEFAULT);
	//��ʾORB������
	imshow("ORB������1", dstimage1);
	imshow("ORB������2", dstimage2);

	//����һ��ƥ������飬���ڳн�ƥ�����DMatch,matches����Ϊ���飬Ԫ������ΪDMatch
	vector<DMatch> matches;
	//����һ��BFMatcherƥ������BFMatcher�๹�캯�����£�������������Ĭ��ֵ�����ǵ�һ��������������ʹ�õĲ�����Ĭ��ֵ�����Ǻ�������
	BFMatcher matcher(NORM_HAMMING);
	//����matcher��match��������ƥ��,�����õ��������ӣ�û���ùؼ��㡣
	//ƥ������Ľ��д���Ϸ������matches[]������
	matcher.match(descriptors1, descriptors2, matches);
	//���Ĳ�������matches[]���飬�ҳ�ƥ�������������С���룬���ں����ƥ���ɸѡ��
	//����ľ������Ϸ�����ĺ����������飬�����������������ƥ������Ƴ̶ȣ�����Ҳ���ҳ��������ƺ�����Ƶ������֮��ľ��롣
	double min_dist = 0, max_dist = 0;//�������
	for (int i = 0; i < descriptors1.rows; ++i)//����
	{
		double dist = matches[i].distance;
		if (dist<min_dist) min_dist = dist;
		if (dist>max_dist) max_dist = dist;
	}
	//��������С��������
	cout << "Max dist:" << max_dist << endl;
	cout << "Min dist:" << min_dist << endl;
	//���岽��������С���룬��ƥ������ɸѡ��
	//��������֮��ľ������������min_dist������Ϊƥ��������������
	//������ʱ��С����ǳ�С������������0�ˣ����������ͻᵼ��min_dist��2*min_dist֮��û�м���ƥ�䡣
	// ���ԣ���2*min_distС��30��ʱ�򣬾�ȡ30������ֵ��С��30���ɣ�����2*min_dist���ֵ��
	std::vector<DMatch> good_matches;
	for (int j = 0; j < descriptors1.rows; ++j)
	{
		if (matches[j].distance <= max(2 * min_dist, 30.0))
			good_matches.push_back(matches[j]);
	}
	Mat img_match;//����ƥ���ͼ
	//���￴һ��drawMatches()ԭ�Ͳ��������÷����ǣ�ͼ1��ͼ1�ؼ��㣬ͼ2��ͼ2�ؼ��㣬ƥ�����飬�н�ͼ�񣬺������Ĭ��ֵ
	drawMatches(srcimage1, keypoints1, srcimage2, keypoints2, matches, img_match);
	imshow("����ƥ����", img_match);

	Mat img_goodmatch;//ɸѡ���ƥ���ͼ
	drawMatches(srcimage1, keypoints1, srcimage2, keypoints2, good_matches, img_goodmatch);
	imshow("ɸѡ���ƥ����", img_goodmatch);

	while (1)
	{
		char c = waitKey(0);
		//��q���˳�����
		if (c == 'q')
			return true;
	}
	return true;
}

