#include <iostream>
#include <fstream>
#include <string>
using namespace std;
  
int main(int argc, char** argv)
{
  string text;
  ifstream file("program.cy");
  while (getline (file, text)) {
    cout << text;
  }
  file.close();

  return 0;
}