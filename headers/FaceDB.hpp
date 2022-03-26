#ifndef FACEDB_HPP
#define FACEDB_HPP

#include <vector>
#include <string>
#include"FaceDetector.hpp"
#include <dlib/dnn.h>
#include <dlib/gui_widgets.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>
#include <dlib/image_processing/shape_predictor.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/opencv/cv_image.h>
#include <opencv2/imgproc.hpp>
#include <dlib/image_io.h>
#include <dlib/matrix.h>
#include"ResNetwork.hpp"
#include<iostream>
#include<iomanip>
#include<string>
#include<ctime>
#include<fstream>
#include<sstream>
using namespace dlib;
using namespace std;
#define ResnetFile "/media/weibo/ProgDisk/code/Facial_Recognition/models/dlib_face_recognition_resnet_model_v1.dat"
#define DLIB_USE_CUDA

class FaceDB
{
    public:
        FaceDB()
        {
           dlib::deserialize(ResnetFile)>>_resnet;
           GetNames();
        }
        std::vector<float> ToVector(dlib::matrix<float,0L,1L>mat)
        {
            std::vector<float> x;
            for (unsigned int r = 0; r < mat.nr(); r += 1) {
                x.push_back(mat(r,0));
                }
            return x;
        }
        bool AddFace(std::string Filename , std::string Name)
        {
            FaceDetector FD;
            std::pair<std::vector<Face>,std::vector<dlib::rectangle>> Faces = FD.detectFaces(Filename);
            dlib::loss_metric_::output_label_type Netop =_resnet(Faces.first[0]);
            std::string filename = "/media/weibo/ProgDisk/code/Facial_Recognition/DB/";
            std::string GenId = GetID();
            filename.append(GenId);
            filename.append(".txt");
            dlib::serialize(filename)<<Netop;
            std::cout<<filename;
            _DBLink[Name] = filename;
            addEntry(Name,filename);
            return true;
            }
        std::string GetID()
        {
            auto t = std::time(nullptr);
            auto tm = *std::localtime(&t);
            std::ostringstream oss;
            oss << std::put_time(&tm, "%H%M%S");
            return oss.str();
        }
        std::pair<std::vector<std::string> ,std::vector<dlib::matrix<float,0L,1L>>> GetallDescriptors()
        {
            std::vector<dlib::matrix<float,0L,1L>> Descriptors;
            std::vector<std::string> Names; 
            for(std::map<std::string , std::string>::iterator it = _DBLink.begin();it!=_DBLink.end();it++)
            { 
                dlib::matrix<float,0L,1L> face ;
                dlib::deserialize(it->second)>>face;
                Descriptors.push_back(face);
                Names.push_back(it->first);
            }
            return std::make_pair(Names,Descriptors);
        }
        static cv::Rect dlibRectangleToOpenCV(dlib::rectangle detections)
        {
        return cv::Rect(cv::Point2i(detections.left()+1,detections.top()+1),cv::Point2i(detections.right(),detections.bottom()));
        }
    private:
        void addEntry(std::string Name,std::string Fileloc)
        {
            ofstream myfile;
            myfile.open ("/media/weibo/ProgDisk/code/Facial_Recognition/DB/FaceNames.txt",std::ios_base::app);
            myfile<<Name<<" "<<Fileloc<<"\n";
            myfile.close();
        }
        std::map<std::string , std::string> _DBLink;
        resnet::ResNetDNN _resnet;
        
        void GetNames()
        {
          std::ifstream file("/media/weibo/ProgDisk/code/Facial_Recognition/DB/FaceNames.txt"); 
          while(!file.eof())
          {
            std::string str,str1;         
            getline(file,str);
            std::stringstream ss;
            ss << str;
            ss>>str;
            ss>>str1;        
            _DBLink.insert({str,str1});
          }
        }
    };

#endif