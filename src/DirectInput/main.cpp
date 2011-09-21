#include <iostream>

#include<d3d11.h>
#include<d3dx11.h>
#include<DxErr.h>
#include<dinput.h>

int main()
{
	LPDIRECTINPUT8 directInputObject;
	
	HRESULT hr = DirectInput8Create( 1, DIRECTINPUT_VERSION,
		IID_IDirectInput8, ( void** )&directInputObject, 0 );
	if FAILED( hr )
	{
		return false;
	}

	std::cout << "ok\n";
}