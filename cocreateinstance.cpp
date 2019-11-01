#define INITGUID
#define DBINITCONSTANTS

#include "iostream"
#include "oledb.h"

const GUID CLSID_MSDASQL = {0xC8B522CBL,0x5CF3,0x11CE,{0xAD,0xE5,0x00,0xAA,0x00,0x44,0x77,0x3D}};

int main() {
	// Инициализация COM
	if (FAILED( CoInitialize(NULL) )) {
		std::cout << "Unable to initialize COM" << std::endl;
		return 1;
	}

	IDBInitialize *pIDBInitialize  = NULL;

	HRESULT hr;
	hr = CoCreateInstance(CLSID_MSDASQL,NULL,CLSCTX_INPROC_SERVER, IID_IDBInitialize, (void**) &pIDBInitialize);
	
	if (FAILED(hr)) {
		std::cout << "CoCreateInstance Failed" << std::endl;
		return 1;
	}

	std::cout << "CoCreateInstance Success" << std::endl;

	pIDBInitialize->Release();
	// Деинициализация COM
	CoUninitialize();

	system("pause");
	return 0;
};
