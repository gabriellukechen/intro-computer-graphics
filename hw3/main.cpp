/******************************************************************************/
/* This is the program skeleton for homework 2 in CSE167 by Ravi Ramamoorthi  */
/* Extends HW 1 to deal with shading, more transforms and multiple objects    */
/******************************************************************************/

// You shouldn't have to edit this file at all!

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>
#include "Transform.h"
#include <FreeImage.h>

using namespace std; 

// Main variables in the program.  
#define MAINPROGRAM 
#include "variables.h" 
#include "readfile.h" // prototypes for readfile.cpp

void saveScreenshot(BYTE * pixels, string outputfilename) {
  FIBITMAP *img = FreeImage_ConvertFromRawBits(pixels, w, h, w * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);

  std::cout << "Saving screenshot: " << outputfilename << "\n";

  FreeImage_Save(FIF_PNG, img, outputfilename.c_str(), 0);
  delete[] pixels;
}

void init() {

}

void trackProgress(int totalpixels, int * currentpixel) {
  int currentprogress = (*currentpixel / totalpixels) * 100; // current progress in percent
  printf("Done %i %%\n", currentprogress);
}

int main(int argc, char* argv[]) {
  BYTE *pixels = new BYTE[3*totalpixels];
  readfile(argv[1]);

  FreeImage_Initialise();

  if (fname.empty()) {
    saveScreenshot(pixels, "Untitled.png");
  } else {
    saveScreenshot(pixels, fname);
  }

  FreeImage_DeInitialise();
  return 0;
}
