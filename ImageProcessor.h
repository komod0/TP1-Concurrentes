#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

class ImageProcessor {
private:
  int pixels;
public:
  ImageProcessor(int pixels);

  ~ImageProcessor();

  void process(unsigned int* imageLocation);
};


#endif // IMAGEPROCESSOR_H
