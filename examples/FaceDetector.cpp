#include "FaceDetector.hpp"
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <iostream>
#define DLIB_USE_CUDA
int main(int argc, char** argv)
{
    FaceDetector FD;
    std::string fname = argv[1];
    std::vector<Face> Faces = FD.detectFaces(fname);
}