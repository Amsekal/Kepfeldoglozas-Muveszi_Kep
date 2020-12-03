#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "ColorSpaces.h"
#include "ThresholdHandler.h"
#include "CropHandler.h"
#include "MorphologyHandler.h"
#include<iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/utility.hpp>


typedef cv::Mat Image;
typedef cv::MatSize ImageSize;




void ceruzarajz(string bemenet) {
	
	//pencilsketch();
	//cv::waitKey(0);

	cv::Mat image = cv::imread(bemenet); //kép beolvasás az elérési utról,majd az általunk választott képet adjuk meg neki

	//változó,hogy tároljuk majd a kimentett képet
	cv::Mat kimenet;
	//szürke skálásra konvertálom
	cv::Mat grayImage;
	cvtColor(image, grayImage, cv::COLOR_BGR2GRAY);

	//a kép invertálása
	cv::Mat grayImageInv = 255 - grayImage;
	//gauss blur alkalmazása a képre
	GaussianBlur(grayImageInv, grayImageInv, cv::Size(21, 21), 0);
	
	//blend using color dodge
	divide(grayImage, 255 - grayImageInv, kimenet, 256.0);

	//megjelenités
	imshow("image", image);
	imshow("pencilsketch", kimenet);
	cv::waitKey(0);
	
}


