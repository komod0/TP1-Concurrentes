#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

class ImageProcessor {
 private:
  int pixels;

 public:
  ImageProcessor(int pixels);

  ~ImageProcessor();

  // Recibe un espacio de memoria donde se encuentra una imagen de "pixels" de
  // largo(width*height) y aplica un procesamiento sobre el mismo espacio.
  void process(float* imageLocation);
};

#endif  // IMAGEPROCESSOR_H
