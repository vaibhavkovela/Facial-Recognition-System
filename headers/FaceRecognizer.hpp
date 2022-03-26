#ifndef FACERECOGNIZER_HPP
#define FACERECOGNIZER_HPP

#include<iostream>
#include<string>
#include<vector>
#include <opencv2/imgproc.hpp>
#include"FaceDetector.hpp"
#define THRESHOLD 0.2
#include "ResNetwork.hpp"
#define DLIB_USE_CUDA
#include <dlib/dnn.h>
#include <dlib/gui_widgets.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <chrono>
#define RESNETFILE "/media/weibo/ProgDisk/code/Facial_Recognition/models/dlib_face_recognition_resnet_model_v1.dat"
//typedef Face std::pair<cv::Rect , dlib::matrix<dlib::rgb_pixel>>;
using namespace std::chrono;
class FaceRecognizer
{
    public:
        FaceRecognizer()
        {
            dlib::deserialize(RESNETFILE)>> _resnet;
        }

        std::vector<std::pair<int,std::string>> recognise(std::vector<dlib::loss_metric_::output_label_type> FrameAppearances ,std::vector<dlib::loss_metric_::output_label_type> DB ,std::vector<std::string> Names)
        {
            std::vector<std::pair<int,std::string>> Result;
            std::cout<<"number of people found in the image:"<<std::endl;
            for(int i =0 ;i<FrameAppearances.size();i++)
            {
                for(int j=0;j<DB.size();j++)
                {
                    float dist = dlib::length(FrameAppearances[i] - DB[j]);
                    if(dist < 0.6)  
                    {
                        Result.push_back(std::make_pair(i,Names[j]));
                        std::cout<<dist<<std::endl<<Names[j]<<std::endl;
                    }
                }
            }
            return Result;
        
        }

       resnet::ResNetDNN _resnet;

};
#endif