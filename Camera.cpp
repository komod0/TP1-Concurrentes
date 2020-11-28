#include "Camera.h"
#include <cmath>
#include <time.h>
#include <stdlib.h>

#define STB_PERLIN_IMPLEMENTATION
#include "stb_perlin.h"

#define SCALE 7

Camera::Camera(unsigned int width, unsigned int height)
    : pictureDimensions(std::make_pair(width, height)) {}

Camera::~Camera() {}

void Camera::takePicture(float* pictureStorage,
                         unsigned int numberOfCamera) {
  int amtPixels = pictureDimensions.first * pictureDimensions.second;
  unsigned int frequency = (unsigned int)pow(2, numberOfCamera % 20);
  srand(time(NULL));
  unsigned int noise_seed = rand();

  for (int i = 0; i < amtPixels; i++) {
    float x = ((i % pictureDimensions.first) / ((float)pictureDimensions.first)) * SCALE;
    float y = ((i / (float)pictureDimensions.first) / pictureDimensions.second) * SCALE;
    pictureStorage[i] = (stb_perlin_noise3_seed(x * frequency, y * frequency, 0,
                                               pictureDimensions.first, 
                                               pictureDimensions.second, 
                                               0, noise_seed) + 1) / 2;
  }
}
