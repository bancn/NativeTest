#pragma once


// CMyEdit

class CMyEdit : public CEdit
{
	DECLARE_DYNAMIC(CMyEdit)

public:
	CMyEdit();
	virtual ~CMyEdit();

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnClearLog(); // 自定义菜单项的处理函数
	afx_msg void OnExportLog(); // 自定义菜单项的处理函数
private:
public:
	void AddLog(const CString& logText);
};
