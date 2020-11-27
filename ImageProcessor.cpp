#include "ImageProcessor.h"

#include <cmath>

ImageProcessor::ImageProcessor(int pixels) : pixels(pixels) {}

ImageProcessor::~ImageProcessor() {}

void ImageProcessor::process(unsigned int* imageLocation) {
  for (int i = 0; i < pixels; i++) {
    imageLocation[i] = pow(imageLocation[i], 1.2);
  }
}

