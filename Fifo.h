#ifndef FIFO_H
#define FIFO_H

#include <string>

class Fifo {
 protected:
  std::string fileName;
  int fd;

 public:
  Fifo(const std::string fileName);

  ~Fifo();

  void close();
};

#endif  // FIFO_H
