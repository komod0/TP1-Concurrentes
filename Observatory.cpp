#include "Observatory.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <utility>

#include <string>

#include "Camera.h"
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
      flattener(imageSideLength, imageSideLength) {
  signal(SIGINT, stopWorking);
  initSharedMem();
}

Observatory::~Observatory() {}

void Observatory::stopWorking(int signum) { Observatory::keepGoing = false; }

void Observatory::initSharedMem() {
  debugLog("Creando memoria para guardar las imagenes");
  for (unsigned int i = 0; i < numberOfCameras; i++) {
    key_t memKey = ftok("/bin/bash", i);
    shmIds.push_back(
        shmget(memKey, imageSideLength * imageSideLength * sizeof(unsigned int),
               IPC_CREAT | 0666));
  }
}

void Observatory::freeMem() {
  for (auto& id : shmIds) {
    shmctl(id, IPC_RMID, NULL);
  }
}

void Observatory::start() {
  unsigned i = 0;
  while (Observatory::keepGoing) {
    takePictures();
    processPictures();
    std::vector<std::vector<unsigned int>> image = std::move(imageFlatten());
    generateImageFile(i, image);
    i++;
  }
  freeMem();
}

void Observatory::takePictures() {
  debugLog("Capturando imagenes en distintas frecuencias");
  for (unsigned int i = 0; i < numberOfCameras; i++) {
    float* imageStorage = (float*)shmat(shmIds[i], NULL, 0);
    camera.takePicture(imageStorage, i);
    shmdt(imageStorage);
  }
  debugLog("Captura exitosa");
}

void Observatory::processPictures() {
  int r;
  debugLog("Procesando las imagenes");
  fflush(debugFile);
  for (unsigned int i = 0; i < numberOfCameras; i++) {
    if ((r = fork()) == 0) {
      float* imageStorage = (float*)shmat(shmIds[i], NULL, 0);
      processor.process(imageStorage);
      shmdt(imageStorage);
      exit(0);
    }
  }
  for (unsigned int i = 0; i < numberOfCameras; i++) {
    wait(NULL);
  }
}

std::vector<std::vector<unsigned int>> Observatory::imageFlatten() {
  debugLog("Uniendo las imagenes");
  std::vector<float*> imageLayers;
  for (unsigned int i = 0; i < numberOfCameras; i++) {
    float* currentLayer = (float*)shmat(shmIds[i], NULL, 0);
    imageLayers.push_back(currentLayer);
  }
  std::vector<std::vector<unsigned int>> image = std::move(flattener.flatten(imageLayers));
  
  for (auto& layer: imageLayers) {
    shmdt(layer);
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
