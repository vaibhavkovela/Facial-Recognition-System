#include"FaceDB.hpp"
#include<dlib/matrix.h>
#define DLIB_USE_CUDA

int main()
{
    FaceDB fdb=FaceDB();
    //std::pair<std::vector<std::string> ,std::vector<dlib::matrix<float,0L,1L>>> dets = fdb.GetallDescriptors();
   // std::cout<<dets.second.size();

      fdb.AddFace("/media/weibo/ProgDisk/code/Facial_Recognition/images/photo.jpeg","Vaibhav");
      fdb.AddFace("/media/weibo/ProgDisk/code/Facial_Recognition/images/rishika.jpeg","Rishika");
      fdb.AddFace("/media/weibo/ProgDisk/code/Facial_Recognition/images/samantha.jpeg","Samantha");

}
