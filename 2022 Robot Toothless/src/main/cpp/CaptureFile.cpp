
//Author: Sebastian Roman (Programming Lead)
//Co Author: 3229 Programming

#include "CaptureFile.h"

CaptureFile::CaptureFile() {}

CaptureFile::~CaptureFile() {
  // Close file
  Close();
  delete fileHandle;
  delete fileName;
}

void CaptureFile::Open(std::string name, bool forWrite) {
  // Setup the name and full path to file
  fileName = name.c_str();
  debugCons("Concat file path: " << fileName << "\n");
  str_filePath = std::string(fileName);

  // Setup r/w perms
  isWrite = forWrite;
  const char *perms = "rb";
  if (isWrite)
    perms = "wb";

  // Open the file for read or write
  fileHandle = fopen(fileName, perms);

  // Verify file opened, print debug output on status
  if (fileHandle != NULL) {
    if(isWrite) {
      debugCons("Opened file " + str_filePath + " for write.\n")
    } else {
      debugCons("Opened file " + str_filePath + " for read.\n")
    }
  } else {
    debugCons("Error opening file " + str_filePath);
  }
}

void CaptureFile::Close() {
  if (fileHandle != NULL) {
    fflush(fileHandle);
    fclose(fileHandle);
  }
  // Set reference to null
  fileHandle = NULL;
}

void CaptureFile::Read(void *buffer, int bufsize) {
  if (fileHandle != NULL && buffer != NULL) {
    fread(buffer, CHARSIZE, bufsize, fileHandle);
  }
}

void CaptureFile::Write(void *buffer, int bufsize) {
  if (fileHandle != NULL && buffer != NULL) {
    fwrite(buffer, CHARSIZE, bufsize, fileHandle);
  }
}
