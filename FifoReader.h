#ifndef FIFOREADER_H
#define FIFOREADER_H

#include <unistd.h>

#include <string>

#include "Fifo.h"

class FifoReader : public Fifo {
 public:
  FifoReader(const std::string fileName);

  ~FifoReader();

  ssize_t read(void* buffer, size_t n);

  void open();
};

#endif  // FIFOREADER_H
