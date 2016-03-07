#include <opencv2/opencv.hpp>
#include "opencv2/videoio.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d.hpp>
#include "opencv2/imgcodecs.hpp"
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using namespace cv;
using namespace std;

Mat quantizeColor (Mat a);
Mat psyco ( Mat a);
Mat sovrapponi(Mat img);

int main( int argc, char** argv ) {

		VideoCapture cap("video.mp4");

		Mat bella2 = imread("test.jpg", CV_LOAD_IMAGE_COLOR);
		bella2 = psyco(bella2);

	    imwrite( "test2.jpg", bella2 );

		while(1)
		{
			Mat frame;

			bool bSuccess = cap.read(frame); // read a new frame from video

			if (!bSuccess) //if not success, break loop
			{
				 cout << "Cannot read the frame from video file" << endl;
				 break;
			}
			frame = psyco(frame);
			imshow("MyVideo", frame); //show the frame in "MyVideo" window

			if(waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
		   {
					cout << "esc key is pressed by user" << endl;
					break;
		   }
		}


		waitKey(0); //wait for key press

		destroyAllWindows(); //destroy all open windows

		return 0;
}

Mat sovrapponi ( Mat img)
{
		Mat bella = imread("seconda.jpg", CV_LOAD_IMAGE_COLOR); //open and read the image

		for(int i = 0; i < img.rows; i++)
		{
			for(int j = 0; j < img.cols; j++)
			{
				for (int s = 0; s<3; s++)
				{
					img.at<Vec3b>(i,j)[s] = ((img.at<Vec3b>(i,j)[s]/5)*5);//+((bella.at<Vec3b>(i,j)[s]/5)*1);
				}
			}
		}
		return img;
}

Mat psyco ( Mat img)
{
	    Mat ris = img;//quantizeColor(img);
	    Mat noise = Mat (ris.size(), ris.type());

	    randn(noise, 0, 10); //mean and variance

	    ris += noise;

	    ris = sovrapponi(ris);

		double kernel[3][3];
		for (int i=0; i<3; i++)
		{
			for (int a=0; a<3; a++)
			{
				kernel[i][a] = (3.0/9.0);
			}
		}

		for(int i = 0; i < ris.rows; i++)
		{
			for(int j = 0; j < ris.cols; j++)
			{
				for (int s=0; s<3; s++)
				{
					double count = 0;
					for ( int r=-1; r<2; r++)
					{
						for(int c = -1; c<2; c++)
						{
							count = count + (double) kernel[1+r][1+c]* (double)ris.at<Vec3b>(i,j)[s];
							//
						}

					}
					ris.at<Vec3b>(i,j)[s] = (int) count;
				}
			}
		}
		return ris;
}

Mat quantizeColor (Mat a)
{
		Mat img = a.clone();
		vector<Mat> channels;
		Mat img_hist_equalized;

		cvtColor(img, img_hist_equalized, CV_BGR2YCrCb); //change the color image from BGR to YCrCb format

		split(img_hist_equalized,channels); //split the image into channels

		equalizeHist(channels[0], channels[0]); //equalize histogram on the 1st channel (Y)

		merge(channels,img_hist_equalized); //merge 3 channels including the modified 1st channel into one image

		cvtColor(img_hist_equalized, img_hist_equalized, CV_YCrCb2BGR); //change the color image from YCrCb to BGR format (to display image properly)

		return img_hist_equalized;
}
