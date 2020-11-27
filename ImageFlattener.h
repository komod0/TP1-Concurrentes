#ifndef IMAGEFLATTENER_H
#define IMAGEFLATTENER_H

#define MAX_PIXEL_LIMIT 65535

#include <vector>


class ImageFlattener {
private:
 unsigned int width;
 unsigned int height;

public:
  ImageFlattener(unsigned int width, unsigned int height);
  
  ~ImageFlattener();

  std::vector<std::vector<unsigned int>> flatten(std::vector<unsigned int*> layers);

private:
  unsigned int getPixelValue(int generatedValue, int maxCap);
};

#endif // IMAGEFLATTENER_H
