// CMyEdit.cpp: 实现文件
//

#include "pch.h"
#include "CMyEdit.h"

#define ID_MENU_CLEAR_LOG 1001  // 清空日志菜单项 ID
#define ID_MENU_EXPORT_LOG 1002 // 导出日志菜单项 ID

BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	ON_WM_CONTEXTMENU() // 右键菜单消息处理
END_MESSAGE_MAP()

// CMyEdit

IMPLEMENT_DYNAMIC(CMyEdit, CEdit)

CMyEdit::CMyEdit()
{

}

CMyEdit::~CMyEdit()
{
}

void CMyEdit::AddLog(const CString& logText)
{
	CTime currentTime = CTime::GetCurrentTime();
	CString timeStr = currentTime.Format(_T("[%Y-%m-%d %H:%M:%S] "));
	CString newLog = timeStr + logText + _T("\r\n");
	// 获取当前日志内容的长度
	int nLength = GetWindowTextLength();

	// 设置光标位置到文本末尾
	SetSel(nLength, nLength);

	// 添加新的日志
	ReplaceSel(newLog);

	// 自动滚动到底部
	LineScroll(GetLineCount());
}

void CMyEdit::OnClearLog()
{
	SetWindowText(_T("")); // 清空文本内容
}

void CMyEdit::OnExportLog()
{
	CString text;
	GetWindowText(text);

	// 如果编辑框为空，则直接返回
	if (text.IsEmpty())
	{
		AfxMessageBox(_T("没有可导出的日志！"));
		return;
	}

	// 获取当前时间
	CTime currentTime = CTime::GetCurrentTime();
	CString timeStr = currentTime.Format(_T("log-%Y%m%d-%H%M%S.txt")); // 例如：log-20250116-123045.txt

	// 打开文件保存对话框
	CFileDialog fileDlg(FALSE, _T("txt"), timeStr,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("文本文件 (*.txt)|*.txt|所有文件 (*.*)|*.*||"), this);

	if (fileDlg.DoModal() == IDOK)
	{
		CString filePath = fileDlg.GetPathName();

		// 将日志内容写入文件
		try
		{
			CStdioFile file(filePath, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
			file.WriteString(text);
			file.Close();

			AfxMessageBox(_T("日志导出成功！"));
		}
		catch (CFileException* e)
		{
			AfxMessageBox(_T("导出日志失败！"));
			e->Delete();
		}
	}
}

void CMyEdit::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu menu;
	menu.CreatePopupMenu();

	CString text;
	GetWindowText(text);

	// 动态添加菜单项
	if (!text.IsEmpty())
	{
		menu.AppendMenu(MF_STRING, ID_MENU_CLEAR_LOG, _T("清空日志"));
		menu.AppendMenu(MF_STRING, ID_MENU_EXPORT_LOG, _T("导出日志"));
	}
	else
	{
		menu.AppendMenu(MF_GRAYED, ID_MENU_CLEAR_LOG, _T("清空日志"));
		menu.AppendMenu(MF_GRAYED, ID_MENU_EXPORT_LOG, _T("导出日志"));
	}

	// 如果右键通过键盘触发，调整菜单弹出位置
	if (point.x == -1 && point.y == -1)
	{
		CRect rect;
		GetClientRect(&rect);
		ClientToScreen(&rect);
		point = rect.CenterPoint();
	}

	// 显示菜单
	int cmd = menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD, point.x, point.y, this);

	// 根据菜单项 ID 执行不同的操作
	switch (cmd)
	{
	case ID_MENU_CLEAR_LOG:
		OnClearLog();
		break;
	case ID_MENU_EXPORT_LOG:
		OnExportLog();
		break;
	default:
		break;
	}
}
