#ifndef IMAGEFLATTENER_H
#define IMAGEFLATTENER_H

#define MAX_PIXEL_LIMIT 255

#include <vector>

class ImageFlattener {
 private:
  unsigned int width;
  unsigned int height;

 public:
  ImageFlattener(unsigned int width, unsigned int height);

  ~ImageFlattener();

  // Une todas las imagenes tomadas por las camaras en una sola y la devuelve en
  // forma de vector de vectores
  std::vector<std::vector<unsigned int>> flatten(std::vector<float*>& layers);

 private:
  // Funcion auxiliar que devuelve un vector de la forma {R, G, B} (con RGB
  // enteros entre 0 y 255) en base al valor del pixel.
  std::vector<unsigned int> getRGBValueOf(float pixel);
};

#endif  // IMAGEFLATTENER_H
