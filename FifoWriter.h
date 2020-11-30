#ifndef FIFOWRITER_H
#define FIFOWRITER_H

#include <unistd.h>

#include <string>

#include "Fifo.h"

class FifoWriter : public Fifo {
 public:
  FifoWriter(const std::string fileName);

  ~FifoWriter();

  ssize_t write(const void* buffer, size_t n);

  void open();
};

#endif  // FIFOWRITER_H
