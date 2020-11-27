#ifndef OBSERVATORY_H
#define OBSERVATORY_H

#include "Camera.h"
#include "ImageProcessor.h"
#include "ImageFlattener.h"

#include <vector>

class Observatory {
 public:
  static bool keepGoing;

 private:
  unsigned int numberOfCameras;
  unsigned int imageSideLength;
  std::vector<int> shmIds;
  Camera camera;
  ImageProcessor processor;
  ImageFlattener flattener;

 public:
  Observatory(unsigned int numberOfCameras, unsigned int imageSideLength);

  ~Observatory();

  static void stopWorking(int signum); // static for signal handling

  void start();

 private:
  void initSharedMem();

  void freeMem();

  void takePictures();

  void processPictures();

  std::vector<std::vector<unsigned int>> imageFlatten();

  void generateImageFile(int imageId, std::vector<std::vector<unsigned int>> image);
};

#endif  // OBSERVATORY_H
