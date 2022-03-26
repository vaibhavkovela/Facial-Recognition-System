#include<fstream>
#include<iostream>
#include<string>
#include<sstream>
int main()
{
    std::string str;
    std::ifstream file("../DB/FaceNames.txt");
    while(!file.eof())
    {
        getline(file,str);
        std::stringstream ss;
        ss << str;
        ss>>str;
        std::cout<<str<<"   vnfjn   ";
        ss>>str;        
        std::cout<<str<<std::endl;
    }
    return 0;
}






// -----------------------------------------------------------------------]]]

// #include "FaceDetector.hpp"
// #include "FaceRecognizer.hpp"
// #include "FaceDB.hpp"
// #include <dlib/image_processing/frontal_face_detector.h>
// #include <dlib/gui_widgets.h>
// #include <dlib/image_io.h>
// #include <iostream>
// #include "FaceDetector.hpp"
// #include <dlib/dnn.h>
// #include <dlib/gui_widgets.h>
// #include <dlib/clustering.h>
// #include <dlib/string.h>
// #include <dlib/image_io.h>
// #include <dlib/image_processing/shape_predictor.h>
// #include "opencv2/opencv.hpp"
// #include <iostream>

// using namespace std;
// int main()
// {
//     FaceDetector FD;
//     FaceRecognizer FR;
//     FaceDB fDB;
//     auto Details = fDB.GetallDescriptors();
//     std::vector<std::string> Names = Details.first;
//     std::vector<dlib::matrix<float,0L,1L>> Descriptors = Details.second;
//     cv::VideoCapture cap("/media/weibo/ProgDisk/code/FaceRecognition_Dlib/chaplin.mp4");
//     if (!cap.isOpened())
//     {
//         cout << "Error opening video stream or file" << endl;
//         return -1;
//     }
//     while (1)
//     {
//         cv::Mat frame;
//         cap >> frame;
//         // cv::cvtColor(frame, frame, BGR2RGB);
//         dlib::matrix<dlib::rgb_pixel> dlibFrame;
//         dlib::assign_image(dlibFrame, dlib::cv_image<bgr_pixel>(frame));
//         if (frame.empty())
//             break;
//         FaceDetector FD;
//         FaceRecognizer FR;
//         std::vector<Face> Faces = FD.detectFaces(dlibFrame);
//         std::vector<dlib::loss_metric_::output_label_type> faceDescriptor;
//         for (int i = 0; i < Faces.size(); i++)
//         {
//             faceDescriptor.push_back(FR._resnet(Faces[i]));
//         }
//         FR.recognise(faceDescriptor,Descriptors,Names);
//         cv::imshow("Frame", frame);
//         char c = (char)cv::waitKey(25);
//         if (c == 27)
//             break;
//     }
//     cap.release();
//     cv::destroyAllWindows();

//     return 0;
// }