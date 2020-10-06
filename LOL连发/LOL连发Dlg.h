﻿
// LOL连发Dlg.h: 头文件
//

#pragma once


// CLOL连发Dlg 对话框
class CLOL连发Dlg : public CDialogEx
{
// 构造
public:
	CLOL连发Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOL连发_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	DWORD m_hotKeyActive;//用于热键重复触发卡屏解决
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void myHotKey();
	afx_msg void OnBnClickedCancel();
};
