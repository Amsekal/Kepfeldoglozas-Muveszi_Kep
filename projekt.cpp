#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core/utility.hpp>
#include <opencv2/photo.hpp>
using namespace std;


void colorEffects(cv::Mat& I) {

	cv::Mat I2(I.size(), CV_8UC3);
	cv::Mat I3(I.size(), CV_8UC3);
	cv::Mat I4(I.size(), CV_8UC3);
	cv::Mat Best(I.size(), CV_8UC3);
	cv::Mat Filter(I.size(), CV_8UC3);
	cv::Mat Filter2(I.size(), CV_8UC3);
	cv::Mat Filter3(I.size(), CV_8UC3);

	cv::GaussianBlur(I, Filter3, cv::Size(53, 53), -1);
	cv::addWeighted(I, 1.5, Filter3, -0.5, 0, Filter3);
	cv::boxFilter(I, Filter, -1, cv::Size(53, 53));

	Filter2 = I - Filter;
	Best = I - Filter2;
	for (int i = 0; i < I.rows; ++i) {
		for (int j = 0; j < I.cols; ++j) {
			cv::Vec3b currentPixelGroup = I.at<cv::Vec3b>(i, j);
			cv::Vec3b nextPixelGroup = Filter2.at<cv::Vec3b>(i, j);
			currentPixelGroup[2] = nextPixelGroup[2] + nextPixelGroup[1] + nextPixelGroup[0];



			I2.at<cv::Vec3b>(i, j) = currentPixelGroup;
		}
	}

	for (int i = 0; i < I.rows; ++i) {
		for (int j = 0; j < I.cols; ++j) {
			cv::Vec3b currentPixelGroup = I.at<cv::Vec3b>(i, j);
			cv::Vec3b nextPixelGroup = Filter2.at<cv::Vec3b>(i, j);

			currentPixelGroup[0] = nextPixelGroup[2] + nextPixelGroup[1] + nextPixelGroup[0];



			I3.at<cv::Vec3b>(i, j) = currentPixelGroup;
		}
	}

	for (int i = 0; i < I.rows; ++i) {
		for (int j = 0; j < I.cols; ++j) {
			cv::Vec3b currentPixelGroup = I.at<cv::Vec3b>(i, j);
			cv::Vec3b nextPixelGroup = Filter2.at<cv::Vec3b>(i, j);

			currentPixelGroup[1] = nextPixelGroup[2] + nextPixelGroup[1] + nextPixelGroup[0];
			I4.at<cv::Vec3b>(i, j) = currentPixelGroup;
		}
	}
	cv::imshow("Eredeti", I);
	cv::imshow("BlueChannel", I2);
	cv::imshow("Sarga", I3);
	cv::imshow("Kepregeny", Best);
	cv::imshow("Gold", Filter3 + I3);
	cv::waitKey();


}

void ceruzarajz(cv::Mat &img) { //david


	//változó,hogy tároljuk majd a kimentett képet
	cv::Mat kimenet;
	//szürke skálásra konvertálom
	cv::Mat grayImage;
	cvtColor(img, grayImage, cv::COLOR_BGR2GRAY);

	//a kép invertálása
	cv::Mat grayImageInv = 255 - grayImage;
	//gauss blur alkalmazása a képre
	GaussianBlur(grayImageInv, grayImageInv, cv::Size(21, 21), 0);

	//blend using color dodge
	divide(grayImage, 255 - grayImageInv, kimenet, 256.0);

	//megjelenités
	imshow("image", img);
	imshow("pencilsketch", kimenet);
	cv::waitKey(0);

}

void detailEnhance(cv::Mat &img) {//reszletes elesites

	float sigma_s;// SIZE OF THE PIXEL NEIGHBORHOOD //BIGGER VALUE -> SMOOTHER IMAGE
	float sigma_r; // COLOR REGION IN NEIGHBORHOOD : BIGGER VALUE -> LARGER REGIONS OF CONSTANT COLOR IN NEIGHBORHOOD

	cv::Mat result;
	detailEnhance(img, result, sigma_s = 10, sigma_r = 0.15f);
	cv::imshow("original", img);
	cv::imshow("detailEnhance", result);
	cv::waitKey();
}

void stylization(cv::Mat &img) {//stilizalas, vizfestek effect szeru

	cv::Mat dst;

	float sigma_s; // SIZE OF THE PIXEL NEIGHBORHOOD //BIGGER VALUE -> SMOOTHER IMAGE
	float sigma_r; // COLOR REGION IN NEIGHBORHOOD : BIGGER VALUE -> LARGER REGIONS OF CONSTANT COLOR IN NEIGHBORHOOD

	stylization(img, dst, sigma_s = 60, sigma_r = 0.45f);

	cv::imshow("original", img);
	cv::imshow("stylized", dst);
	cv::waitKey();
}

void pencilScetch(cv::Mat &img) { // rajzolt festmeny szeru

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

void festett(cv::Mat &image) { //ruben

	cv::Mat kernel = cv::Mat::ones(cv::Size(3, 3), (0, 1, 0, 1, 1, 1, 0, 1, 0));

	cv::Mat eroded, dilated;


	cv::Mat boxFiltered;
	cv::Mat unsharped;
	boxFilter(image, boxFiltered, -1, cv::Size(35, 35));
	cv::addWeighted(image, 1.5, boxFiltered, -0.5, 0, unsharped);


	erode(unsharped, eroded, kernel);       // eroded
	dilate(unsharped, dilated, kernel);     // dilated

	cv::Mat kontur_kinyeres = dilated - eroded;

	imshow("original", image);
	imshow("original", unsharped);
	imshow("contured", kontur_kinyeres);

	cv::waitKey();
}

void csillag() {
	std::cout << "\n************************************************************************************************************************\n";
}

int main() {

	std::string forras;

	int ans;
	cv::Mat img;
	std::cout << "\nHonnan olvassam?: "; std::cin >> forras;//D:\\kepfeldolg\\img\\DE2.jpg

	img = cv::imread(forras, 1);


	while (true) {
		cout << "\n  Valaszd ki hogy mit vegezzek el a kepeden!";
		cout << "\n     1.Grafit effect";
		cout << "\n     2.Reszletes elesites";
		cout << "\n     3.Vizfestek szeru stilizalas";
		cout << "\n     4.Rajzolt festmeny";
		cout << "\n     5.Konturizalt";
		cout << "\n     6.Szin effectek";
		cout << "\n     7. Uj kep megadasa";
		cout << "\n     0 - kilepes";
		cout << "\n  valasz: ";
		cin >> ans;
		csillag();
		cout << endl;

		switch (ans) {
			case 1: 
			{ceruzarajz(img); csillag(); break; }
			case 2: 
			{detailEnhance(img); csillag(); break; }
			case 3: 
			{stylization(img); csillag(); break; }
			case 4: 
			{pencilScetch(img); csillag(); break; }
			case 5: 
			{festett(img); csillag(); break; }
			case 6: {
				colorEffects(img); csillag(); break; }
			case 7: {
				csillag();
				std::cout << "\nHonnan olvassam?: "; std::cin >> forras;//D:\\kepfeldolg\\img\\kep.jpeg
				img = cv::imread(forras, 1);  break;
			}
			case 0: return 0;

			default: cout << "A felsorolt szamokat varom el!\n"; break;
		}
	}

	return 0;

}

