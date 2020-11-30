#include "Observatory.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <utility>

#include <iostream>
#include <string>

#include "Camera.h"
#include "Fifo.h"
#include "FifoReader.h"
#include "FifoWriter.h"
#include "Logging.h"

#define IMAGE_PATH "img/imagen"
#define IMG_EXTENSION ".ppm"

extern bool debugMode;
extern FILE* debugFile;
bool Observatory::keepGoing = true;

Observatory::Observatory(unsigned int numberOfCameras,
                         unsigned int imageSideLength)
    : numberOfCameras(numberOfCameras),
      imageSideLength(imageSideLength),
      camera(imageSideLength, imageSideLength),
      processor(imageSideLength * imageSideLength),
      flattener(imageSideLength, imageSideLength),
      waitingProcess(0) {
  signal(SIGINT, stopWorking);
  initFifoFiles();
}

Observatory::~Observatory() {}

void Observatory::stopWorking(int signum) { Observatory::keepGoing = false; }

void Observatory::initFifoFiles() {
  debugLog("Creando los archivos correspondientes a los fifos para cada imagen");
  for (unsigned int i = 0; i < numberOfCameras; i++) {
    std::string fileName = std::string("imagen") + std::to_string(i);
    mknod(fileName.c_str(), S_IFIFO|0666, 0);
    fifoFiles.push_back(fileName);
  }
}

void Observatory::unlinkFiles() {
  for (auto& fileName : fifoFiles) {
    unlink(fileName.c_str());
  }
}

void Observatory::start() {
  unsigned i = 0;
  while (Observatory::keepGoing) {
    takePictures();
    processPictures();
    std::vector<std::vector<unsigned int>> image = std::move(imageFlatten());
    waitForAllChilds();
    generateImageFile(i, image);
    i++;
  }
  unlinkFiles();
}

void Observatory::waitForAllChilds() {
  for (unsigned int i = 0; i < waitingProcess; i++) {
    wait(NULL);
  }
  waitingProcess = 0;
}


void Observatory::takePictures() {
  debugLog("Capturando imagenes en distintas frecuencias");
  fflush(debugFile);
  if (fork() == 0) {
    float* imageStorage = (float*)malloc(imageSideLength*imageSideLength*sizeof(float));

    for (unsigned int i = 0; i < numberOfCameras; i++) {
      FifoWriter writer(fifoFiles[i]);
      camera.takePicture(imageStorage, i);
      writer.open();
      writer.write(imageStorage, imageSideLength*imageSideLength*sizeof(float));
      writer.close();
    }

    free(imageStorage);
    exit(0);
  }
  debugLog("Captura exitosa");
  waitingProcess++;
}

void Observatory::processPictures() {
  debugLog("Procesando las imagenes");
  fflush(debugFile);
  std::vector<float*> images;
  for (unsigned int i = 0; i < numberOfCameras; i++) {
      float* imageStorage = (float*)malloc(imageSideLength*imageSideLength*sizeof(float));
      FifoReader reader(fifoFiles[i]);
      reader.open();
      reader.read(imageStorage, imageSideLength*imageSideLength*sizeof(float));
      reader.close();
      images.push_back(imageStorage);
  }

  for (unsigned int i = 0; i < numberOfCameras; i++) {
    if (fork() == 0) {
      processor.process(images[i]);

      FifoWriter writer(fifoFiles[i]);
      writer.open();
      writer.write(images[i], imageSideLength*imageSideLength*sizeof(float));
      writer.close();
      for (auto& image: images) {
        free(image);
      }
      exit(0);
    }
    waitingProcess++;
  }
  for (auto& image: images) {
    free(image);
  }
}

std::vector<std::vector<unsigned int>> Observatory::imageFlatten() {
  debugLog("Uniendo las imagenes");
  fflush(debugFile);
  std::vector<float*> imageLayers;
  for (unsigned int i = 0; i < numberOfCameras; i++) {
    float* imageStorage = (float*)malloc(imageSideLength*imageSideLength*sizeof(float));
    FifoReader reader(fifoFiles[i]);
    reader.open();
    reader.read(imageStorage, imageSideLength*imageSideLength*sizeof(float));
    reader.close();
    imageLayers.push_back(imageStorage);
  }
  std::vector<std::vector<unsigned int>> image = std::move(flattener.flatten(imageLayers));
  
  for (auto& layer: imageLayers) {
    free(layer);
  }
  return image;
}

void Observatory::generateImageFile(int imageId, std::vector<std::vector<unsigned int>>& image) {
  debugLog("Escribiendo la imagen en disco");
  std::string imgName =
      std::string(IMAGE_PATH) + std::to_string(imageId) + IMG_EXTENSION;
  FILE* imageFile = fopen(imgName.c_str(), "w+");
  fprintf(imageFile, "P3\n%u %u\n%u\n", imageSideLength, imageSideLength,
          MAX_PIXEL_LIMIT);

  std::vector<unsigned int> redChannel = image[0];
  std::vector<unsigned int> greenChannel = image[1];
  std::vector<unsigned int> blueChannel = image[2];

  for (unsigned int i = 0; i < redChannel.size(); i++) {
    fprintf(imageFile, "%u %u %u\n", redChannel[i], greenChannel[i],
            blueChannel[i]);
  }
  fclose(imageFile);
  debugLog("Escritura finalizada\n");
}
