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
  auto pipe = [&](Mat im)
  {
    // Detect faces in the frame and draw
    auto faces  = haarDetectFaces(im);
    auto asmRes = fitASMFaces(im, faces);
    auto canvas = im.clone();

    // TAOTODO: Draw all features detected
    for (auto asmModel : asmRes)
    {
      vector<Point> vertices;
      asmModel.toPointList(vertices);

      // Draw points on the canvas
      CvScalar color = Scalar(100,255,0);
      for (auto p : vertices)
      {
        circle(canvas, p, 2, color, 1);
      }
    }
    
    namedWindow("tracked", CV_WINDOW_AUTOSIZE);
    imshow("tracked", canvas);
  };

  return pipe;
}

/**
 * Detect multiple bounding boxes, each of them containin a face
 * using classical cascaded Haar feature detection.
 */
vector<Rect> FaceTrack::haarDetectFaces(Mat& frame)
{
  vector<Rect> faces;
  this->faceDetector.detectMultiScale( frame, faces,
    1.2, 
    2, 
    CV_HAAR_FIND_BIGGEST_OBJECT | CV_HAAR_SCALE_IMAGE, 
    Size(60, 60) 
  );
  return faces;
}

/**
 * Given the bounding boxes containing faces, 
 * fit the ASM.
 */
vector<ASMFitResult> FaceTrack::fitASMFaces(Mat& frame, vector<Rect> faceAreas)
{
  if (faceAreas.size()==0)
    cout << "No face detected by Haar" << endl;
  else
    cout << faceAreas.size() << " faces detected by Haar" << endl;

  return this->model.fitAll(frame, faceAreas, false);
}