#include "FaceTrack.h"

FaceTrack::FaceTrack(string pathASMModel, string pathFaceHaarDetector)
{
  this->model.loadFromFile(pathASMModel);
  this->faceDetector.load(pathFaceHaarDetector);
}

FaceTrack::~FaceTrack()
{
}

/**
 * Generate a tracking function which takes a frame 
 */
function<void (Mat)> FaceTrack::createPipe()
{
  // TAOTODO:
}

vector<Rect> FaceTrack::haarDetectFaces()
{
  vector<Rect> faces = 
  objCascadeClassfifier.detectMultiScale( img, faces,
    1.2, 
    2, 
    CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE, 
    Size(60, 60) 
  );
  return faces;
}

vector<ASMFitResult> FaceTrack::fitASMFaces(Mat& frame, vector<Rect> faceAreas)
{
  return this->model.fitAll(frame, faceAreas, false);
}