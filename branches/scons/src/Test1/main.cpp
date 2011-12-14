#include <iostream>

#include <windows.h>
#include "DX11Renderer.h"

int main()
{ 
	DX11Renderer *dx11=new DX11Renderer();

	std::cout << dx11->getBackendName() << "\n";

	GetActiveWindow();

	bool bRes=dx11->InitDevice(512,512);

	delete dx11;
}