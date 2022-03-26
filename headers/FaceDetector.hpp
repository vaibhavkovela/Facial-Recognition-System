#ifndef FACEDETECTOR_HPP
#define FACEDETECTOR_HPP

#include <vector>
#include <string>
#include <dlib/dnn.h>
#include <dlib/gui_widgets.h>
#include <dlib/clustering.h>
#include <dlib/string.h>

#include <dlib/image_processing/shape_predictor.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/opencv/cv_image.h>
#include <opencv2/imgproc.hpp>
#include <dlib/image_io.h>
#include"opencv2/opencv.hpp"
#include<iostream>
#define shapePredLocation "/media/weibo/ProgDisk/code/Facial_Recognition/models/shape_predictor_5_face_landmarks.dat"
#define DLIB_USE_CUDA

typedef dlib::matrix<dlib::rgb_pixel> Face; //cv::Rect std::pair

class FaceDetector
{
public:
        FaceDetector()
        {
            _faceDetector = dlib::get_frontal_face_detector();
            loadShapePredictor(shapePredLocation);
        }
        // ~FaceDetector();
        std::pair<std::vector<Face>,std::vector<dlib::rectangle>> detectFaces(std::string fname)
        {
            std::vector<Face> Result;
            dlib::array2d<unsigned char> img;
            load_image(img, fname);
            dlib::pyramid_up(img);
            std::vector<dlib::rectangle> detections = _faceDetector(img);
            // dlib::image_window win(img); 
                       
            for(int i=0;i<detections.size();i++)
            {
                // win.add_overlay(detections[0]);
                // win.wait_until_closed();
                auto shape = _shapePredictor(img,detections[i]);
                dlib::matrix<dlib::rgb_pixel> faceChip;
                dlib::extract_image_chip(img,dlib::get_face_chip_details(shape, 150, 0.25),faceChip);
                cv::Rect Position (cv::Point2i(detections[i].left(),detections[i].top()),cv::Point2i(detections[i].right()+1,detections[i].bottom()+1));
                Result.push_back(faceChip);
            }
            return std::make_pair(Result,detections);
        }
        std::pair<std::vector<Face>,std::vector<dlib::rectangle>> detectFaces(cv::Mat img)
        {
            dlib::matrix<dlib::rgb_pixel> dlibFrame;
            dlib::assign_image(dlibFrame, dlib::cv_image<dlib::bgr_pixel>(img));
            std::vector<Face> Result;
            dlib::pyramid_up(dlibFrame);
            std::vector<dlib::rectangle> detections = _faceDetector(dlibFrame);
            if(detections.size()==0)
            {
                return std::make_pair(Result,detections);
            }
            dlib::image_window win(dlibFrame); 
            for(int i=0;i<detections.size();i++)
            {
                auto shape = _shapePredictor(dlibFrame,detections[i]);
                dlib::matrix<dlib::rgb_pixel> faceChip;
                dlib::extract_image_chip(dlibFrame,dlib::get_face_chip_details(shape, 150, 0.25),faceChip);
                cv::Rect Position (cv::Point2i(detections[i].left(),detections[i].top()),cv::Point2i(detections[i].right()+1,detections[i].bottom()+1));
                Result.push_back(faceChip);
            }
            return std::make_pair(Result,detections);
        }

private:
    dlib::frontal_face_detector _faceDetector;
    dlib::shape_predictor _shapePredictor;
    void loadShapePredictor(const std::string file)
    {
        dlib::deserialize(file) >> _shapePredictor;
    }
};

#endif // FACEDETECTOR_HPP
