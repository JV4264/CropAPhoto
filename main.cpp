#include "tools.hpp"

int main() {
  banner();
  ifstream mid, mid2;
  ofstream turkey;
  string type;
  int width, height, greyscale, filepos;
  int psize;
  int min_x = 948; 
  int min_y = 582;
  int max_x = 2085;
  int max_y = 1581;
//--------------------------------------------------------------
  mid2.open("midday.txt"); // opens
  mid2 >> type;
  mid2 >> width >> height >> greyscale;
  psize = width * height;
  while (mid2.get() != '\n');
  filepos = mid2.tellg();
  cout << type << " " << width << " " << height << " " << greyscale << endl;
  mid2.close();
//--------------------------------------------------------------
  mid.open("midday.txt", ios_base::in | ios_base::binary);
  mid.seekg(filepos);
//--------------------------------------------------------------
  char* pix = new char[psize];
  mid.read(pix, psize);
  if(!mid.good()){
    fatal("file is corrupted");
  }
  mid.get();
  if(mid.eof()){
    cout << "End of file reached successfully" << endl;
  }
  mid.close(); 
//---------------------------------------------------------------
  turkey.open("cropped.pgm");
  turkey << type << endl;
  turkey << (max_x - min_x + 1) << " " << (max_y - min_y + 1) << endl;
  turkey << greyscale << endl;

  for(int y = 0; y <= height; y++) {
    if (y >= min_y && y <= max_y) {
      for (int x = 0; x <= width; x++) {
        if(x >= min_x && x <= max_x) {
          int index = width * y + x;
          turkey << pix[index];
        }
      }
    }
  }
  turkey.close();
  bye();
}
