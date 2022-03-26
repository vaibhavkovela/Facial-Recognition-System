#include "FaceDetector.hpp"
#include "FaceRecognizer.hpp"
#include "FaceDB.hpp"
#include <iostream>
#include "FaceDetector.hpp"
#include "opencv2/opencv.hpp"
#include <dlib/matrix.h>
int main()
{
    FaceDetector FD;
    FaceRecognizer FR;
    FaceDB fDB;
    auto Details = fDB.GetallDescriptors();
    std::vector<std::string> Names = Details.first;
    std::vector<dlib::matrix<float,0L,1L>> Descriptors = Details.second;
    cv::VideoCapture cap(0);
    if (!cap.isOpened())
    {
        cout << "Error opening video stream or file" << endl;
        return -1;
    }
    while (1)
    {
        cv::Mat frame;
        cap >> frame;
        // cv::cvtColor(frame, frame, BGR2RGB);
        if (frame.empty())
            break;
        FaceDetector FD;
        FaceRecognizer FR;
        std::vector<Face> Faces = FD.detectFaces(frame);
        if(Faces.size()==0) continue;
        std::vector<dlib::loss_metric_::output_label_type> faceDescriptor;
        for (int i = 0; i < Faces.size(); i++)
        {
            faceDescriptor.push_back(FR._resnet(Faces[i]));
        }
        FR.recognise(faceDescriptor,Descriptors,Names);
        cv::imshow("Frame", frame);
        char c = (char)cv::waitKey(25);
        if (c == 27)
            break;
    }
    cap.release();
    cv::destroyAllWindows();

    return 0;
}