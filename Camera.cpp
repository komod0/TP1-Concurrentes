#include "Camera.h"

Camera::Camera(unsigned int width, unsigned int height)
    : pictureDimensions(std::make_pair(width, height)) {}

Camera::~Camera() {}

void Camera::takePicture(unsigned int* pictureStorage) {
  int amtPixels = pictureDimensions.first * pictureDimensions.second;
  for (int i = 0; i < amtPixels; i++) {
    pictureStorage[i] =
        i % pictureDimensions.first + (unsigned int)(i / pictureDimensions.second);
  }
}
