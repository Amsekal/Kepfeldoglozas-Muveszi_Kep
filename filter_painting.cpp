#include <iostream>
#include <opencv2/core.hpp>    // osztalyok, strukturak, alapveto funkciok
#include <opencv2/highgui.hpp> // felulet
#include <opencv2/imgproc.hpp> // kepfeld. konyvtar, gyakran kell majd

using namespace std;
using namespace cv;

//////// Paramter is a Mat obj ////////
void festett(Mat image) {

	Mat kernel = Mat::ones(Size(3, 3), (0, 1, 0, 1, 1, 1, 0, 1, 0));

	Mat eroded, dilated;

	erode(image, eroded, kernel);       // eroded
	dilate(image, dilated, kernel);     // dilated

	Mat kontur_kinyeres = dilated - eroded;
	Mat k2 = eroded - dilated;
  
  /// Filtered ///
	Mat boxFiltered_k2, boxFiltered_image;
	boxFilter(k2, boxFiltered_k2, -1, cv::Size(41, 41));
	boxFilter(image, boxFiltered_image, -1, cv::Size(7, 7));

	Mat boxFiltered_ketto;
	boxFilter(k2+image, boxFiltered_ketto, -1, cv::Size(35, 35));

	imshow("original", image);
	imshow("filtered_ketto", boxFiltered_ketto);
	imshow("filtered_k2", boxFiltered_k2);
	imshow("maszk", boxFiltered_image + boxFiltered_k2);

	waitKey();
}
