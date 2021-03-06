#include <functional>
#include <opencv2/opencv.hpp>
#include "asmmodel.h"
#include "modelfile.h"
#include "ITransformation.h"

using namespace std;
using namespace cv;
using namespace StatModel;

class FaceTrack
{
public:
  FaceTrack(string pathASMModel, string pathFaceHaarDetector);
  virtual ~FaceTrack();

  // Make a tracker pipe operation
  virtual function<void (Mat)> createPipe();

protected:
  vector<Rect> haarDetectFaces(Mat& frame);
  vector<ASMFitResult> fitASMFaces(Mat &frame, vector<Rect> faceAreas);

private:
  ASMModel model;
  cv::CascadeClassifier faceDetector;
};