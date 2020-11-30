#include "FifoReader.h"

#include <fcntl.h>
#include <unistd.h>

FifoReader::FifoReader(const std::string fileName) : Fifo(fileName) {}

FifoReader::~FifoReader() {}

ssize_t FifoReader::read(void* buffer, size_t n) {
  size_t bytes_read = 0;
  while (bytes_read < n) { // Nos aseguramos de que se lean n bytes y no 65536 como max
    bytes_read += ::read(fd, (char*)buffer + bytes_read, n - bytes_read);
  }
  return bytes_read;
}

void FifoReader::open() {
  fd = ::open(fileName.c_str(), O_RDONLY);
}
