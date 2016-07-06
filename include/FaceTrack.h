#include <functional>
#include <opencv2/opencv.hpp>
#include "asmmodel.h"
#include "modelfile.h"
#include "ITransformation.h"

class FaceTrack
{
public:
  FaceTrack(string pathASMModel);
  virtual ~FaceTrack();

  // Get a tracker pipe operation
  virtual function<void (Mat)> getPipe();

private:
  ASMModel model;
}