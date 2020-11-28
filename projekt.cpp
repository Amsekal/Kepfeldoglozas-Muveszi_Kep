#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/photo.hpp>
#include <iostream>


void detailEnhance(cv::Mat &img, cv::Mat &result) {//reszletes elesites
	/*
	cv::Mat dst;
	std::string forras;
	std::cout << "\nHonnan olvassam?: "; std::cin >> forras;//D:\\kepfeldolg\\img\\cow.jpg
	cv::Mat img = cv::imread(forras, 1);
	*/
	float sigma_s;// SIZE OF THE PIXEL NEIGHBORHOOD //BIGGER VALUE -> SMOOTHER IMAGE
	float sigma_r; // COLOR REGION IN NEIGHBORHOOD : BIGGER VALUE -> LARGER REGIONS OF CONSTANT COLOR IN NEIGHBORHOOD
	
	detailEnhance(img, result, sigma_s = 10, sigma_r = 0.15f);
	//cv::imshow("original", img);
	//cv::imshow("detailEnhance", dst);
	//cv::waitKey();
}

void stylization() {//stilizalas, vizfestek effect szeru
	
	cv::Mat dst;
	std::string forras;
	std::cout << "\nHonnan olvassam?: "; std::cin >> forras; //D:\\kepfeldolg\\img\\cow.jpg
	cv::Mat img = cv::imread(forras, 1);


	float sigma_s; // SIZE OF THE PIXEL NEIGHBORHOOD //BIGGER VALUE -> SMOOTHER IMAGE
	float sigma_r; // COLOR REGION IN NEIGHBORHOOD : BIGGER VALUE -> LARGER REGIONS OF CONSTANT COLOR IN NEIGHBORHOOD

	stylization(img, dst, sigma_s = 60, sigma_r = 0.45f);

	cv::imshow("original", img);
	cv::imshow("stylized", dst);
	cv::waitKey();
}

void pencilScetch(){ // rajzolt festmeny szeru

	std::string forras;
	std::cout << "\nHonnan olvassam?: "; std::cin >> forras;//D:\\kepfeldolg\\img\\kep.jpeg
	cv::Mat img = cv::imread(forras, 1);

	cv::Mat dst_gray(img.size(), CV_8UC3);
	cv::Mat dst_color(img.size(), CV_8UC3);

	float sigma_s;// SIZE OF THE PIXEL NEIGHBORHOOD //BIGGER VALUE -> SMOOTHER IMAGE
	float sigma_r; // COLOR REGION IN NEIGHBORHOOD : BIGGER VALUE -> LARGER REGIONS OF CONSTANT COLOR IN NEIGHBORHOOD
	float shade_factor;
	pencilSketch(img, dst_gray, dst_color, sigma_s = 60, sigma_r = 0.07f, shade_factor = 0.02f);
	//shade_factor : vilagossabb az eredmeny ahogy noveljuk az erteket

	cv::imshow("original", img);
	cv::imshow("Colored pencil", dst_color);
	cv::imshow("Gray pencil", dst_gray);
	cv::waitKey();
}

int main() {
	//detailEnhance();
	//pencilScetch();
	stylization();
}