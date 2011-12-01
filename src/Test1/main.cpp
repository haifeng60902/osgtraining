#include <iostream>

#include "DX11Renderer.h"

int main()
{ 
	DX11Renderer *dx11=new DX11Renderer();

	std::cout << dx11->getBackendName() << "\n";
}