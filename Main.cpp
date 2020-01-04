#include <iostream>
#include <string>
#include <vector>
#include "OpenGL.h"
using namespace std;


int main(int argc, char* argv[])
{
	OpenGL *openGL = new OpenGL();
	openGL->Render();
	
}