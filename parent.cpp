#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <thread>
#include <tchar.h>
#pragma warning(disable:4996)

int main() {
	int size;
	std::cout << "Input size of array: ";
	std::cin >> size;

	unsigned int* array = new unsigned int[size];
	for (int i = 0; i < size; i++) {
		std::cin >> array[i];
	}

	std::string cmd_args;
	
	
	cmd_args += std::to_string(size);
	cmd_args += " ";
	for (int i = 0; i < size; i++) {
		cmd_args += std::to_string(array[i]);
		if (i != size - 1) {
			cmd_args += " ";
		}
	}
	std::wstring stemp = std::wstring(cmd_args.begin(), cmd_args.end());
	//LPCTSTR lpszAppName = L"childdd.exe";
	LPCTSTR lpszAppName = L"C:\\Users\\Lenovo\\source\\repos\\parenttt\\x64\\Debug\\childdd.exe";
	STARTUPINFOA arrSizeSi;
	PROCESS_INFORMATION arrSizePi;

	ZeroMemory(&arrSizeSi, sizeof(STARTUPINFO));
	arrSizeSi.cb = sizeof(STARTUPINFO);
	arrSizeSi.dwFlags = STARTF_USECOUNTCHARS;
	arrSizeSi.dwXCountChars = 160;



	if (!CreateProcess(lpszAppName,
		&stemp[0],
		NULL,
		NULL, 
		FALSE,
		CREATE_NEW_CONSOLE, 
		NULL, 
		NULL,
		(LPSTARTUPINFO)&arrSizeSi,
		&arrSizePi))
	{
		std::cout << "New process is not created" << std::endl;
		return 0;
	}

	std::cout << "New process is created" << std::endl;
	WaitForSingleObject(arrSizePi.hProcess, INFINITE);

	CloseHandle(arrSizePi.hThread);
	CloseHandle(arrSizePi.hProcess);
	delete[]array;
	return 0;
}

