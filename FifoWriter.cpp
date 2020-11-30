#include "FifoWriter.h"

#include <fcntl.h>
#include <unistd.h>

FifoWriter::FifoWriter(const std::string fileName) : Fifo(fileName) {}

FifoWriter::~FifoWriter() {}

ssize_t FifoWriter::write(const void* buffer, size_t n) {
  return ::write(fd, buffer, n);
}

void FifoWriter::open() {
  fd = ::open(fileName.c_str(), O_WRONLY);
}
