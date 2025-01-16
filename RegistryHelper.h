#pragma once
#include "pch.h"
#include <Windows.h>
#include <tchar.h>

class CRegistry
{
public:
	CRegistry(HKEY hRootKey = HKEY_CURRENT_USER);
	~CRegistry();

	BOOL CreateKey(LPCTSTR lpSubKey);
	BOOL DeleteKey(LPCTSTR lpSubKey);
	BOOL SetValue(LPCTSTR lpSubKey, LPCTSTR lpValueName, LPCTSTR lpValue);
	BOOL GetValue(LPCTSTR lpSubKey, LPCTSTR lpValueName, CString& value);
	BOOL DeleteValue(LPCTSTR lpSubKey, LPCTSTR lpValueName);
	BOOL RemoveFromStartup(LPCTSTR lpAppName);
	BOOL AddToStartup(LPCTSTR lpAppName);

private:
	HKEY m_hRootKey; 
};
