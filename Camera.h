#ifndef CAMERA_H
#define CAMERA_H

#include <utility>


class Camera {
private:
  std::pair<unsigned int, unsigned int> pictureDimensions;
public:
  Camera(unsigned int width, unsigned int height);

  ~Camera();

  void takePicture(unsigned int* pictureStorage);
};

#endif // CAMERA_H
