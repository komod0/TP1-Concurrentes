#include <string.h>
#include <unistd.h>

#include <csignal>
#include <cstdlib>
#include <iostream>
#include <string>

#include "Logging.h"
#include "Observatory.h"

#define DEBUG_FLAG "-d"

bool debugMode = false;
FILE* debugFile;

void debugLog(const char* msj) {
  if (debugMode) {
    fprintf(debugFile, "%s\n", msj);
  }
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cout << "Ingrese los parametros correctamente" << std::endl;
    return -1;
  }
  unsigned int numberOfCameras = atoi(argv[1]);
  unsigned int imageSideLength = atoi(argv[2]);

  if ((numberOfCameras == 0) || (imageSideLength == 0)) {
    std::cout << "Ingrese valores apropiados para los parametros" << std::endl;
    return -1;
  }
  std::cout << argc << std::endl;
  if (argc == 5 && (strcmp(argv[3], DEBUG_FLAG) == 0)) {
    debugMode = true;
    std::cout << argv[3] << std::endl;
    if ((debugFile = fopen(argv[4], "w+")) == NULL) {
      perror("Hubo un problema al abrir el archivo especificado: ");
      return -1;
    }
  }

  Observatory obs = Observatory(numberOfCameras, imageSideLength);
  debugLog("Observatorio creado");
  std::cout << "Pase por aca" << std::endl;
  debugLog("Observatorio funcionando");
  obs.start();

  if (debugMode) {
    fclose(debugFile);
  }
  return 0;
}
