#include "Fifo.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

Fifo::Fifo(const std::string fileName) : fileName(fileName), fd(-1) {}

Fifo::~Fifo() {}

void Fifo::close() {
  if (fd != -1) ::close(fd);
  fd = -1;
}
