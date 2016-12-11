#include <iostream>
#include "color_detection.h"
 
#define DISPLAY_WIDTH	640
#define DISPLAY_HEIGHT	480

using namespace std;
using namespace cv;

Point g_avgRectPos;

void Test_image(int argc,char **argv)
{

	if(argc != 2)
	{
		cout << "provide an image" <<endl;
		return;
	}


	Mat inputImage,binaryImage,extractedObjectsImage;

	inputImage = imread( argv[1], CV_LOAD_IMAGE_COLOR);

	ExtractColoredObjects( inputImage, binaryImage);
	drawBoundaryAroundObjects(binaryImage,inputImage,extractedObjectsImage,g_avgRectPos);

	cout << "middle Red Rectangle location[x,y]: " <<"[ "<< g_avgRectPos.x << " , "<< g_avgRectPos.y << " ]" <<endl;

	namedWindow("src_image",0);
	namedWindow("binary_image",0);
	namedWindow("withObjects",0);

 	resizeWindow( "src_image", DISPLAY_WIDTH, DISPLAY_HEIGHT);
 	resizeWindow( "binary_image", DISPLAY_WIDTH, DISPLAY_HEIGHT);
	resizeWindow( "withObjects", DISPLAY_WIDTH, DISPLAY_HEIGHT);

	imshow( "src_image", inputImage);
	imshow( "binary_image", binaryImage);
	imshow ("withObjects",extractedObjectsImage);

	waitKey(0);
}

void Test_video()
{
	VideoCapture cap;
	Mat frame;
	Mat binaryFrame,extractedObjectsFrame;
	bool frameReadSuccess;
	cap.open(0);

	if (!cap.isOpened())  // if not success, exit program
	{
		cout << "ERROR INITIALIZING VIDEO CAPTURE" << endl;
		return;
	}

	namedWindow("outputFrame",0);
	namedWindow("binaryFrame",0);
	while(1)
	{
		frameReadSuccess = cap.read(frame);
		if(frameReadSuccess == false)
		{
			cout<<"ERROR READING FRAME FROM CAMERA FEED"<<endl;
			break;
		}

		ExtractColoredObjects( frame, binaryFrame);
		drawBoundaryAroundObjects(binaryFrame,frame,extractedObjectsFrame,g_avgRectPos);

		imshow("outputFrame",extractedObjectsFrame);
		imshow("binaryFrame",binaryFrame);

		cout << "middle Red Rectangle location[x,y]: " <<"[ "<< g_avgRectPos.x << " , "<< g_avgRectPos.y << " ]" <<endl;
		waitKey(30);

	}
	
}

int main (int argc,char ** argv)
{
	//choose which test to apply
//	Test_image(argc,argv);
	Test_video();

	return 0;
}