#include "pch.h"
#include "RegistryHelper.h"

CRegistry::CRegistry(HKEY hRootKey)
	: m_hRootKey(hRootKey)
{
}

CRegistry::~CRegistry()
{
}

BOOL CRegistry::CreateKey(LPCTSTR lpSubKey)
{
	HKEY hKey;
	LONG lResult = RegCreateKeyEx(m_hRootKey, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL);
	if (lResult == ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return TRUE;
	}
	return FALSE;
}

BOOL CRegistry::DeleteKey(LPCTSTR lpSubKey)
{
	LONG lResult = RegDeleteKey(m_hRootKey, lpSubKey);
	return (lResult == ERROR_SUCCESS);
}

BOOL CRegistry::SetValue(LPCTSTR lpSubKey, LPCTSTR lpValueName, LPCTSTR lpValue)
{
	HKEY hKey;
	LONG lResult = RegCreateKeyEx(m_hRootKey, lpSubKey, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hKey, NULL);
	if (lResult == ERROR_SUCCESS)
	{
		lResult = RegSetValueEx(hKey, lpValueName, 0, REG_SZ, (const BYTE*)lpValue, (_tcslen(lpValue) + 1) * sizeof(TCHAR));
		RegCloseKey(hKey);
		return (lResult == ERROR_SUCCESS);
	}
	return FALSE;
}

BOOL CRegistry::GetValue(LPCTSTR lpSubKey, LPCTSTR lpValueName, CString& value)
{
	HKEY hKey;
	LONG lResult = RegOpenKeyEx(m_hRootKey, lpSubKey, 0, KEY_READ, &hKey);
	if (lResult == ERROR_SUCCESS)
	{
		TCHAR szBuffer[1024] = { 0 };
		DWORD dwBufferSize = sizeof(szBuffer);
		lResult = RegQueryValueEx(hKey, lpValueName, NULL, NULL, (LPBYTE)szBuffer, &dwBufferSize);
		if (lResult == ERROR_SUCCESS)
		{
			value = szBuffer;
		}
		RegCloseKey(hKey);
		return (lResult == ERROR_SUCCESS);
	}
	return FALSE;
}

BOOL CRegistry::DeleteValue(LPCTSTR lpSubKey, LPCTSTR lpValueName)
{
	HKEY hKey;
	LONG lResult = RegOpenKeyEx(m_hRootKey, lpSubKey, 0, KEY_SET_VALUE, &hKey);
	if (lResult == ERROR_SUCCESS)
	{
		lResult = RegDeleteValue(hKey, lpValueName);
		RegCloseKey(hKey);
		return (lResult == ERROR_SUCCESS);
	}
	return FALSE;
}


BOOL CRegistry::AddToStartup(LPCTSTR lpAppName)
{
	// 获取当前应用程序的路径
	TCHAR szAppPath[MAX_PATH] = { 0 };
	if (GetModuleFileName(NULL, szAppPath, MAX_PATH) == 0)
	{
		return FALSE; // 获取路径失败
	}

	// 检查是否已存在相同的启动项
	CString existingPath;
	if (GetValue(_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), lpAppName, existingPath))
	{
		// 如果现有值与当前路径相同，则不添加
		if (existingPath.CompareNoCase(szAppPath) == 0)
		{
			return TRUE;  // 已存在相同的启动项，直接返回
		}
	}

	// 将应用程序路径添加到注册表中的启动项
	return SetValue(_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), lpAppName, szAppPath);
}


BOOL CRegistry::RemoveFromStartup(LPCTSTR lpAppName)
{
	// 检查是否存在该启动项
	CString existingPath;
	if (!GetValue(_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), lpAppName, existingPath))
	{
		return FALSE; // 启动项不存在
	}

	// 删除该启动项
	return DeleteValue(_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run"), lpAppName);
}
