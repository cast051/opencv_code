/*----------------------------------������˵����-------------------------------------
��������:�������븯ʴ�������㡢�����㡢��̬ѧ�ݶȡ���ñ����ñ
��������IDE�汾��Visual Studio 2013
��������OpenCV�汾��  3.0
2018.7.10  Create by   VV
-----------------------------------------------------------------------------------*/



/*----------------------------------��ͷ�ļ���---------------------------------------
���������������ͷ�ļ�
-----------------------------------------------------------------------------------*/
#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <vector>


/*----------------------------------�������ռ䡿-------------------------------------
����������ʹ�õ������ռ�
-----------------------------------------------------------------------------------*/
using namespace cv;
using namespace std;


/*----------------------------------��ȫ�ֱ�����-------------------------------------
������ȫ�ֱ���
-----------------------------------------------------------------------------------*/
Mat srcimage, dstimage;//�������ͼƬ

int MaxIterationNum = 10;//����ں�=MaxIterationNum*2+1
int ErodeDilateNum = 0;//�ں�=ErodeDilateNum*2+1
int ErodeDilateSwitch = 0;//��ʴ/����
int OpenCloseNum = 0;//�ں�=OpenCloseNum*2+1
int OpenCloseSwitch = 0;//��/��
int TopBlackHatNum = 0;//�ں�=TopBlackHatNum*2+1
int TopBlackHatSwitch = 0;//��ñ/��ñ

MorphShapes MorShape = MORPH_RECT;//Ԫ�ؽṹ��״

/*----------------------------------��ȫ�ֺ�����-------------------------------------
������ȫ�ֺ�������
-----------------------------------------------------------------------------------*/
static void ErodeDilate_Callback(int, void *);
static void OpenClose_Callback(int, void *);
static void TopBlackHat_Callback(int, void *);
/*----------------------------------��main������-------------------------------------
����������������
-----------------------------------------------------------------------------------*/
int main()
{
	//����ͼƬ
	srcimage = imread("dog.png");
	if (srcimage.data == NULL){ cout << "ͼƬ��ȡ����!/r/n" << endl; return false; }
	//��ʾԭͼƬ
	imshow("ԭͼ", srcimage);

	//��������
	namedWindow("��ʴ/����", 1);
	namedWindow("������/������", 1);
	namedWindow("��ñ/��ñ", 1);

	//����������
	createTrackbar("��ʴ/����", "��ʴ/����", &ErodeDilateSwitch, 1);
	createTrackbar("����ֵ", "��ʴ/����", &ErodeDilateNum, MaxIterationNum * 2 + 1, ErodeDilate_Callback);
	createTrackbar("������/������", "������/������", &OpenCloseSwitch, 1);
	createTrackbar("����ֵ", "������/������", &OpenCloseNum, MaxIterationNum * 2 + 1, OpenClose_Callback);
	createTrackbar("��ñ/��ñ", "��ñ/��ñ", &TopBlackHatSwitch, 1);
	createTrackbar("����ֵ", "��ñ/��ñ", &TopBlackHatNum, MaxIterationNum * 2 + 1, TopBlackHat_Callback);

	//ִ�лص�����
	ErodeDilate_Callback(ErodeDilateNum, 0);
	OpenClose_Callback(OpenCloseNum, 0);
	TopBlackHat_Callback(TopBlackHatNum, 0);

	while (1)
	{
		char c = waitKey(0);
		//��q���˳�����,������1��2��3���л�Ԫ�ؽṹ
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

/*----------------------------------����ʴ/���ͻص�������----------------------------
��������ʴ/���ͻص�����
-----------------------------------------------------------------------------------*/
static void ErodeDilate_Callback(int, void *)
{
	//�����
	Mat element = getStructuringElement(MorShape, Size(ErodeDilateNum * 2 + 1, ErodeDilateNum * 2 + 1));
	if (ErodeDilateSwitch == 0)
		//��ʴ
		morphologyEx(srcimage, dstimage, MORPH_ERODE, element);
	else if (ErodeDilateSwitch == 1)
		//����
		morphologyEx(srcimage, dstimage, MORPH_DILATE, element);

	imshow("��ʴ/����", dstimage);

}
/*----------------------------------����ʴ/���ͻص�������----------------------------
������������/������
-----------------------------------------------------------------------------------*/
static void OpenClose_Callback(int, void *)
{
	//�����
	Mat element = getStructuringElement(MorShape, Size(OpenCloseNum * 2 + 1, OpenCloseNum * 2 + 1));
	if (OpenCloseSwitch == 0)
		//������
		morphologyEx(srcimage, dstimage, MORPH_OPEN, element);
	else if (OpenCloseSwitch == 1)
		//������
		morphologyEx(srcimage, dstimage, MORPH_CLOSE, element);

	imshow("������/������", dstimage);


}
/*----------------------------------����ñ/��ñ�ص�������----------------------------
��������ñ/��ñ
-----------------------------------------------------------------------------------*/
static void TopBlackHat_Callback(int, void *)
{
	//�����
	Mat element = getStructuringElement(MorShape, Size(TopBlackHatNum * 2 + 1, TopBlackHatNum * 2 + 1));
	if (TopBlackHatSwitch == 0)
		//��ñ
		morphologyEx(srcimage, dstimage, MORPH_TOPHAT, element);
	else if (TopBlackHatSwitch == 1)
		//��ñ
		morphologyEx(srcimage, dstimage, MORPH_BLACKHAT, element);

	imshow("��ñ/��ñ", dstimage);
}

/*----------------------------------����Ҫ������-------------------------------------
������ʵ�ָ�ʴ�����͡������㡢�����㡢��̬ѧ�ݶȡ���ñ����ñ����
-----------------------------------------------------------------------------------*/

/*ʵ�ָ�ʴ�����͡������㡢�����㡢��̬ѧ�ݶȡ���ñ����ñ����
morphologyEx(srcimage, dstimage, MORPH_ERODE, element);
MORPH_ERODE = 0, //!< see cv::erode
MORPH_DILATE = 1, //!< see cv::dilate
MORPH_OPEN = 2, //!< an opening operation
MORPH_CLOSE = 3, //!< a closing operation
MORPH_GRADIENT = 4, //!< a morphological gradient
MORPH_TOPHAT = 5, //!< "top hat"
MORPH_BLACKHAT = 6  //!< "black hat"*/