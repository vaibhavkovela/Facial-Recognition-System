#include "FaceDetector.hpp"
#include "FaceRecognizer.hpp"
#include "FaceDB.hpp"
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>
#include "FaceDetector.hpp"
#include <dlib/dnn.h>
#include <dlib/gui_widgets.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>
#include <dlib/image_processing/shape_predictor.h>
#define DLIB_USE_CUDA
int main(int argc, char **argv)
{
    FaceDetector FD;
    FaceRecognizer FR;
    std::string fname = argv[1];
    std::vector<Face> Faces = FD.detectFaces(fname);
    std::vector<dlib::loss_metric_::output_label_type> faceDescriptor;
    for (int i = 0; i < Faces.size(); i++)
    {
        faceDescriptor.push_back(FR._resnet(Faces[i]));
    }
    FaceDB fDB;
    auto Details = fDB.GetallDescriptors();
    std::vector<std::string> Names = Details.first;
    std::vector<dlib::matrix<float,0L,1L>> Descriptors = Details.second;
    FR.recognise(faceDescriptor,Descriptors,Names);
    return 0;
}