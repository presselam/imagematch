#include <iostream>
#include <algorithm>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

typedef cv::Point3_<uint8_t> Pixel;


bool use_mask;
Mat img;
Mat templ;
Mat mask;
Mat result;
const char* image_window = "Source Image";
const char* result_window = "Result window";
int match_method =0;
int max_Trackbar = 5;

void MatchingMethod(char);

int main(int argc, char** argv) {
//  if (argc < 3) {
//    cout << "Not enough parameters" << endl;
//    cout << "Usage:\n"
//         << argv[0] << " <image_name> <template_name> [<mask_name>]" << endl;
//    return -1;
//  }

  string srcPath = "data/board.png";

  img = imread(srcPath, IMREAD_COLOR);
  if (img.empty()) {
    cout << "Can't read one of the images" << endl;
    return EXIT_FAILURE;
  }
  namedWindow(image_window, WINDOW_AUTOSIZE);
//  namedWindow(result_window, WINDOW_AUTOSIZE);
//  const char* trackbar_label =
//      "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n "
//      "4: TM COEFF \n 5: TM COEFF NORMED";
//  createTrackbar(trackbar_label, image_window, &match_method, max_Trackbar,
//                 MatchingMethod);
  imshow(image_window, img);
  while(true){
   char key = waitKey(0);
   if( key >= '1' && key <= '9' ){
     std::cout << "matching: " << key << std::endl;
     MatchingMethod(key); // ascii offset;
   }
   if( key == 'q' ){
     return EXIT_SUCCESS;
   }
  }
  return EXIT_FAILURE;
}

void MatchingMethod(char matchNumber) {
  Mat img_display;
  img.copyTo(img_display);

  string tmplPath = "data/tmpl.X.png";
  std::replace(tmplPath.begin(), tmplPath.end(), 'X', matchNumber);
  templ = imread(tmplPath, IMREAD_COLOR);
  if( templ.empty() ){
    cout << "Can't read image:[" << tmplPath<< "]" << endl;
    return;
  }

  int result_cols = img.cols - templ.cols + 1;
  int result_rows = img.rows - templ.rows + 1;
  result.create(result_rows, result_cols, CV_32FC1);

    matchTemplate(img, templ, result, TM_CCOEFF_NORMED, mask);

  std::cout << "result r:" << result.rows << " c:" << result.cols << " ch:" << result.channels() << std::endl;
  
  for( int r=0; r<result.rows; ++r){
  for( int c=0; c<result.cols; ++c){
    float intensity = result.at<float>(r,c);
    if( intensity >= 0.9 ){
      std::cout << "[" << r << "][" << c << "] => " << intensity << std::endl;
      rectangle( img_display, Point(c,r), Point( c + templ.cols , r + templ.rows ), Scalar::all(0), 2, 8, 0 );
    }
  }
  }


  

 imshow(image_window, img_display);

  return;
}
