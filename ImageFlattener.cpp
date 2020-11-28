#include "ImageFlattener.h"

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <utility>

ImageFlattener::ImageFlattener(unsigned int width, unsigned int height)
    : width(width), height(height) {}

ImageFlattener::~ImageFlattener() {}

std::vector<std::vector<unsigned int>> ImageFlattener::flatten(std::vector<float*>& layers) {

  float maxPixelValue = 0;
  float minPixelValue = layers.size();
  std::vector<float> imageAux;
  std::vector<std::vector<unsigned int>> image;
  std::vector<unsigned int> redChanel;
  std::vector<unsigned int> greenChanel;
  std::vector<unsigned int> blueChanel;

  for (unsigned int i = 0; i < width*height; i++) {
    float currentPixel = 0;
    for(unsigned int layer = 0; layer < layers.size(); layer++) {
      unsigned int frequency = (unsigned int)pow(2, layer % 20);
      currentPixel += (1.0f/frequency)*layers[layer][i];
    }
    currentPixel = log(pow(currentPixel, 3) + 1);
    imageAux.push_back(currentPixel);
    maxPixelValue = std::max(maxPixelValue, currentPixel);
    minPixelValue = std::min(minPixelValue, currentPixel);
  }

  for (unsigned int i = 0; i < width*height; i++) {
    float scaledPixelValue = (imageAux[i] - minPixelValue)/(maxPixelValue - minPixelValue);
    std::vector<unsigned int> pixelRGBValues = getRGBValueOf(scaledPixelValue);

    redChanel.emplace_back(pixelRGBValues[0]);
    greenChanel.emplace_back(pixelRGBValues[1]);
    blueChanel.emplace_back(pixelRGBValues[2]);
  }

  image.push_back(std::move(redChanel));
  image.push_back(std::move(greenChanel));
  image.push_back(std::move(blueChanel));

  return std::move(image);
}

std::vector<unsigned int> ImageFlattener::getRGBValueOf(float pixel) {
  if (pixel < 0.3) return {0, 62, 178};
  else if (pixel < 0.35) return {9, 82, 198};
  else if (pixel < 0.4) return {186, 170, 121};
  else if (pixel < 0.43) return {133, 117, 68};
  else if (pixel < 0.6) return {90, 127, 50};
  else if (pixel < 0.7) return {66, 97, 24};
  else if (pixel < 0.75) return {40, 77, 0};
  else if (pixel < 0.8) return {140, 142, 123};
  else if (pixel < 0.9) return {154, 156, 137};
  return {255, 250, 250};
}
