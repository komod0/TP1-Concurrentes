#ifndef CAMERA_H
#define CAMERA_H

#include <utility>

class Camera {
 private:
  std::pair<unsigned int, unsigned int> pictureDimensions;

 public:
  Camera(unsigned int width, unsigned int height);

  ~Camera();

  // Recibe un espacio de memoria y almacena la imagen tomada alli, el espacio
  // debe ser de al menos width*height de tamaño, el parametro numberOfCamera es el 
  // numero de camara y es usado con motivos de generación de la imagen.
  void takePicture(float* pictureStorage, unsigned int numberOfCamera);
};

#endif  // CAMERA_H
