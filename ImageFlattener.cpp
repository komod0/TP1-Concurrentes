#include "ImageFlattener.h"

#include <iostream>
#include <random>

ImageFlattener::ImageFlattener(unsigned int width, unsigned int height)
    : width(width), height(height) {}

ImageFlattener::~ImageFlattener() {}

std::vector<std::vector<unsigned int>> ImageFlattener::flatten(
    std::vector<unsigned int*> layers) {

  std::vector<std::vector<unsigned int>> image;
  std::vector<unsigned int> redChanel;
  std::vector<unsigned int> greenChanel;
  std::vector<unsigned int> blueChanel;


  for (unsigned int i = 0; i < width * height; i++) {
    unsigned int pixelSum = 0;
    for (auto& layer : layers) {
      pixelSum += layer[i];
    }
    unsigned int pixelMean = pixelSum / layers.size();
    unsigned int red, green, blue;

    std::default_random_engine generator;
    std::normal_distribution<float> distribution(pixelMean, width*height);

    red = getPixelValue(distribution(generator), MAX_PIXEL_LIMIT);
    green = getPixelValue(distribution(generator), MAX_PIXEL_LIMIT);
    blue = getPixelValue(distribution(generator), MAX_PIXEL_LIMIT);

    redChanel.push_back(red);
    greenChanel.push_back(green);
    blueChanel.push_back(blue);
  }

  image.push_back(redChanel);
  image.push_back(greenChanel);
  image.push_back(blueChanel);

  return image;
}

unsigned int ImageFlattener::getPixelValue(int generatedValue, int maxCap) {
  if (generatedValue > maxCap) {
    return (unsigned int)(generatedValue % maxCap);
  }
  return generatedValue;
}
