#include <stdio.h>
#include <windows.h>
#include <wbemidl.h>
#include <combaseapi.h>

#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "user32.lib")
#pragma comment(lib, "ole32.lib")
#pragma comment(lib, "oleaut32.lib")

BOOL hasThermalZoneTemp();

int main()
{
	if ( !hasThermalZoneTemp() )
	{
		MessageBox(NULL, "Proceeding with non-malicious activities...", "VM Detected" , MB_OK);
		return 0;
	}

	MessageBox(NULL, "Proceeding with malicious activities...", "Starting malware", MB_OK);
	return 0;
}

BOOL hasThermalZoneTemp()
{
	IWbemLocator* pLoc = NULL;
	IWbemServices* pSvc = NULL;
	IEnumWbemClassObject* pEnumerator = NULL;
	IWbemClassObject* pclsObj = (IWbemClassObject*)malloc(sizeof(IWbemClassObject));
	
	ULONG uReturn = 0;

	HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
	hr = CoInitializeSecurity(NULL, -1,	NULL, NULL,	RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE,	NULL, EOAC_NONE, NULL);
	hr = CoCreateInstance(CLSID_WbemLocator, NULL, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
	hr = pLoc->ConnectServer(L"root\\wmi", NULL, NULL, 0, NULL,	0, 0, &pSvc);
	hr = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT,	RPC_C_AUTHZ_NONE, NULL,	RPC_C_AUTHN_LEVEL_CALL,	RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
	hr = pSvc->ExecQuery(L"WQL", L"SELECT * FROM MSAcpi_ThermalZoneTemperature", WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,	NULL, &pEnumerator);

	while (pEnumerator)
	{
		hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
		if (uReturn == 0)
		{
			return 0;
		}

		VARIANT vtProp;

		hr = pclsObj->Get(L"CurrentTemperature", 0, &vtProp, 0, 0);
		if (SUCCEEDED(hr))
		{
			printf("Thermal Zone Temperature: %d\n", vtProp.intVal);
			return 1;
		}

		VariantClear(&vtProp);
		pclsObj->Release();
	}

	pEnumerator->Release();
	pSvc->Release();
	pLoc->Release();
	
	CoUninitialize();

    return 0;
}