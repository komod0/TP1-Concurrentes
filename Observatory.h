#ifndef OBSERVATORY_H
#define OBSERVATORY_H

#include <vector>

#include "Camera.h"
#include "ImageFlattener.h"
#include "ImageProcessor.h"

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

  // Signal handler para la señal SIGINT, detiene el observatorio de manera
  // ordenada
  static void stopWorking(int signum);  // static for signal handling

  // Inicializa el observatorio junto con la memoria necesaria
  void start();

 private:
  // Inicializa los espacios de memoria compartida a utilizar
  void initSharedMem();

  // Libera la memoria compartida mediante shmctl
  void freeMem();

  // Delega la generacion de las fotos a los objetos Camera
  void takePictures();

  // Delega el procesamiento al objeto ImageProcessor
  void processPictures();

  // Aplana las imagenes con la ayuda de ImageFlattener
  std::vector<std::vector<unsigned int>> imageFlatten();

  // Genera el archivo de la imagen a partir de un vector de vectores que
  // representan los tres canales RGB de la imagen
  void generateImageFile(int imageId,
                         std::vector<std::vector<unsigned int>>& image);
};

#endif  // OBSERVATORY_H
