#include "ImageProcessor.h"

#include <cmath>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

#define MAX_SLEEP_TIME 3
#define MIN_SLEEP_TIME 1

ImageProcessor::ImageProcessor(int pixels) : pixels(pixels) {}

ImageProcessor::~ImageProcessor() {}

void ImageProcessor::process(float* imageLocation) {
  for (int i = 0; i < pixels; i++) {
    imageLocation[i] = pow(imageLocation[i], 1.1);
  }
  // Simular procesamiento pesado
  srand(time(NULL));
  int sleep_time = (rand() % MAX_SLEEP_TIME) + 1;
  sleep(sleep_time);
}

