#include "capture.hpp"
#include <opencv2/cudaobjdetect.hpp>
#include <opencv2/cudaimgproc.hpp>
#include <opencv2/cudawarping.hpp>
#include <stdio.h>

int main()
{
  /*
  Please note this file structure
  **/
  printf("GPU COUNT : %d\n",cv::cuda::getCudaEnabledDeviceCount());

  /*
  cv::cuda::CascadeClassifier *upper_body =
    cv::cuda::CascadeClassifier::create("../haarcascade_upperbody.xml");
    */
  cv::CascadeClassifier upper_body;
  upper_body.load("../haarcascade_upperbody.xml");

  ScreenShot screen(0,0,1920,1080);

  cv::Point lu,rl;
  cv::Mat img;
  //cv::cuda::GpuMat objbuf;
  while(1)
  {
    screen(img);
    //cv::cuda::GpuMat imgg(img);
    cv::resize(img,img,cv::Size(640,360));


    //cv::cuda::cvtColor(imgg,imgg,cv::COLOR_BGR2GRAY);
    //cv::cvtColor(img,img,cv::COLOR_BGR2GRAY);
    std::vector<cv::Rect>aims;
    //upper_body->detectMultiScale( imgg, objbuf );
    upper_body.detectMultiScale(img,aims);
    //upper_body->convert(objbuf,aims);

    for(size_t i=0;i<aims.size();i++)
    {
      cv::rectangle(
        img,cv::Point(aims[i].x,aims[i].y),
        cv::Point(aims[i].x+aims[i].width,aims[i].y+aims[i].height),
        cv::Scalar(0, 255, 0));
    }

    cv::imshow("img", img);
    cv::waitKey(20);

  }
}
