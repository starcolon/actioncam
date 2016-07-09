/**
 * Main app entry point of ActionCam
 * @author StarColon Projects
 * @copyRight 2016-now 
 */

#include <functional>
#include "FilterTransformation.h"
#include "Transformations.h"
#include "VideoCamera.h"
#include "FaceTrack.h"

using namespace std;

int main(int argc, char** argv)
{
  // Prepare processors
  IdentityTransformation ti;
  FilterTransformation grayscale = FilterTransformation(
    FilterType::Gray,
    160,
    255
  );
  FilterTransformation thresh = FilterTransformation(
    FilterType::TruncateThreshold,
    120,
    255
  );
  function<void (Mat)> idle = [](Mat){};

  // Prepare face tracking plugin
  string pathAsmModel  = "./models/grey_asm.model";
  string pathHaarModel = "./models/haarcascade_frontalface_alt.xml";
  FaceTrack ft         = FaceTrack(pathAsmModel, pathHaarModel);
  function<void (Mat)> tracking = ft.createPipe();

  VideoCamera cam("cam");
  cam.captureRealtimeWith(thresh, tracking);
  return 0;
}