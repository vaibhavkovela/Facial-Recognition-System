#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>
#include<QFileDialog>
#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QPixmap>




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
#include "opencv2/opencv.hpp"
#include <dlib/image_processing/shape_predictor.h>
#define DLIB_USE_CUDA





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->setCentralWidget(ui->textBrowser);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionImage_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Select FIle");
    FaceDetector FD;
    FaceRecognizer FR;
    std::pair<std::vector<Face>,std::vector<dlib::rectangle>> Faces = FD.detectFaces(filename.toStdString());
    std::vector<dlib::loss_metric_::output_label_type> faceDescriptor;
    for (int i = 0; i < Faces.first.size(); i++)
    {
        faceDescriptor.push_back(FR._resnet(Faces.first[i]));
    }
    FaceDB fDB;
    auto Details = fDB.GetallDescriptors();
    std::vector<std::string> Names = Details.first;
    std::vector<dlib::matrix<float,0L,1L>> Descriptors = Details.second;
    std::vector<std::pair<int,std::string>> results = FR.recognise(faceDescriptor,Descriptors,Names);
    cv::Mat img = cv::imread(filename.toStdString());
    cv::cvtColor(img,img,cv::COLOR_BGR2RGB);
    cv::pyrUp(img,img,cv::Size( img.cols*2, img.rows*2 ));
    for(int i=0;i<results.size();i++)
    {
        auto detections = Faces.second[results[i].first];
        cv::rectangle(img ,cv::Point2i(detections.left()+1,detections.top()+1), cv::Point2i(detections.right(),detections.bottom()),
              cv::Scalar(255, 0, 0),
              0.3, cv::LINE_8);
        cv::putText(img, results[i].second,cv::Point2i(detections.left()+1,detections.top()+1),cv::FONT_HERSHEY_SIMPLEX, 0.6,(255,255,255), 1);
    }
    ui->label->setPixmap(QPixmap::fromImage(QImage(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888)));
    ui->label->setScaledContents( true );
    ui->label->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
}

void MainWindow::on_actionVideo_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Select FIle");
    FaceDetector FD;
    FaceRecognizer FR;
    FaceDB fDB;
    auto Details = fDB.GetallDescriptors();
    std::vector<std::string> Names = Details.first;
    std::vector<dlib::matrix<float,0L,1L>> Descriptors = Details.second;
    cv::VideoCapture cap(filename.toStdString());
    if (!cap.isOpened())
    {
        cout << "Error opening video stream or file" << endl;
    }
    while (1)
    {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty())
            break;
        FaceDetector FD;
        FaceRecognizer FR;
        std::pair<std::vector<Face>,std::vector<dlib::rectangle>> Faces = FD.detectFaces(frame);
        if(Faces.first.size()==0) continue;
        std::vector<dlib::loss_metric_::output_label_type> faceDescriptor;
        for (int i = 0; i < Faces.first.size(); i++)
        {
            faceDescriptor.push_back(FR._resnet(Faces.first[i]));
        }
        auto results = FR.recognise(faceDescriptor,Descriptors,Names);
        cv::cvtColor(frame,frame,cv::COLOR_BGR2RGB);
        cv::pyrUp(frame,frame,cv::Size( frame.cols*2, frame.rows*2 ));
        for(int i=0;i<results.size();i++)
        {
            auto detections = Faces.second[results[i].first];
            cv::rectangle(frame ,cv::Point2i(detections.left()+1,detections.top()+1), cv::Point2i(detections.right(),detections.bottom()),
                cv::Scalar(255, 0, 0),
                0.3, cv::LINE_8);
            cv::putText(frame, results[i].second,cv::Point2i(detections.left()+1,detections.top()+1),cv::FONT_HERSHEY_SIMPLEX, 0.6,(255,255,255), 1);
        }
        ui->label->setPixmap(QPixmap::fromImage(QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888)));
        ui->label->setScaledContents( true );
        ui->label->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
        char c = (char)cv::waitKey(25);
        if (c == 27)
            break;
    }
    cap.release();
    cv::destroyAllWindows();

}

void MainWindow::on_actionWeb_Camera_triggered()
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
    }
    while (1)
    {
        cv::Mat frame;
        cap >> frame;
        if (frame.empty())
            break;
        FaceDetector FD;
        FaceRecognizer FR;
        std::pair<std::vector<Face>,std::vector<dlib::rectangle>> Faces = FD.detectFaces(frame);
        if(Faces.first.size()==0) continue;
        std::vector<dlib::loss_metric_::output_label_type> faceDescriptor;
        for (int i = 0; i < Faces.first.size(); i++)
        {
            faceDescriptor.push_back(FR._resnet(Faces.first[i]));
        }
        auto results = FR.recognise(faceDescriptor,Descriptors,Names);
        cv::cvtColor(frame,frame,cv::COLOR_BGR2RGB);
        cv::pyrUp(frame,frame,cv::Size( frame.cols*2, frame.rows*2 ));
        for(int i=0;i<results.size();i++)
        {
            auto detections = Faces.second[results[i].first];
            cv::rectangle(frame ,cv::Point2i(detections.left()+1,detections.top()+1), cv::Point2i(detections.right(),detections.bottom()),
                cv::Scalar(255, 0, 0),
                0.3, cv::LINE_8);
            cv::putText(frame, results[i].second,cv::Point2i(detections.left()+1,detections.top()+1),cv::FONT_HERSHEY_SIMPLEX, 1.2,(255,255,255), 1.5);
        }
        ui->label->setPixmap(QPixmap::fromImage(QImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888)));
        ui->label->setScaledContents( true );
        ui->label->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
        char c = (char)cv::waitKey(25);
        if (c == 27)
            break;
    }
    cap.release();
    cv::destroyAllWindows();

}

void MainWindow::on_actionAdd_New_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,"Select FIle");
    FaceDB fdb=FaceDB();
    fdb.AddFace(filename.toStdString(),"");
}