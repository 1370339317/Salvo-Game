
// LOL连发Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "LOL连发.h"
#include "LOL连发Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



#include"Driver Control.h"
#ifdef _DEBUG
#ifdef _WIN64 
#pragma comment(lib,"../x64/Debug/DRIVERCONTROL.lib")
#else
#pragma comment(lib,"../Debug/DRIVERCONTROL.lib")
#endif // _WIN64 

#else
#ifdef _WIN64 
#pragma comment(lib,"../x64/Release/DRIVERCONTROL.lib")
#else
#pragma comment(lib,"../Release/DRIVERCONTROL.lib")
#endif // _WIN64 
#endif // _DEBUG


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLOL连发Dlg 对话框



CLOL连发Dlg::CLOL连发Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOL, pParent)
{
	m_hotKeyActive = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLOL连发Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLOL连发Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CLOL连发Dlg::OnBnClickedOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &CLOL连发Dlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CLOL连发Dlg 消息处理程序

BOOL CLOL连发Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标



	//加载驱动
	bool bRet = XHX_DriverLoad();
	bRet = XHX_CheckDriverIsSuccess();

	CString str;
	str.Format(L"驱动加载中");

	for (size_t i = 0; i < 10; i++)
	{
		str += L".";
		bRet = XHX_CheckDriverIsSuccess();
		if (bRet)
		{
			break;
		}
		SetDlgItemText(IDC_STATICMB, str);
		Sleep(500);
	}
	SetDlgItemText(IDC_STATICMB, str);

	if (!bRet)
	{
		MessageBoxA(0, "驱动加载失败", "error", MB_OK);
		OnBnClickedCancel();
		return FALSE;
	}

	SetDlgItemText(IDC_STATICMB, L"驱动加载成功!如非必要，无需调节上方参数。");


	//设置代码
	SetDlgItemText(IDC_EDIT2, L"10");
	//设置代码
	SetDlgItemText(IDC_EDIT3, L"50");
	//设置代码
	SetDlgItemText(IDC_EDIT4, L"10");
	//设置代码
	SetDlgItemText(IDC_EDIT5, L"15");


	// TODO: 在此添加额外的初始化代码

	SetTimer(1, 40, NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CLOL连发Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLOL连发Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLOL连发Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLOL连发Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}

#define KEY_HAS_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) //必要的，我是背下来的 
void CLOL连发Dlg::myHotKey()
{
	if (KEY_HAS_DOWN('W'))
	{
		m_hotKeyActive = 1;
	}
	else if (KEY_HAS_DOWN(VK_SPACE))
	{
		m_hotKeyActive = 8;
	}
}

void CLOL连发Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	myHotKey();


	//有热键功能
	if (m_hotKeyActive)
	{
		switch (m_hotKeyActive)
		{
		case 1: {
			//前置
			SIZE_T w1counts = GetDlgItemInt(IDC_EDIT2);
			//后置
			SIZE_T w2counts = GetDlgItemInt(IDC_EDIT3);
			//间隔
			SIZE_T timecount = GetDlgItemInt(IDC_EDIT4);
			//间隔
			SIZE_T timesetdown = GetDlgItemInt(IDC_EDIT5);

			//连续按W
			for (size_t i = 0; i < w1counts; i++)
			{
				XHX_KeyClick('W', timesetdown);
				Sleep(timecount);
			}

			XHX_KeyClick('Q', timesetdown);

			for (size_t i = 0; i < w2counts; i++)
			{
				XHX_KeyClick('W', timesetdown);
				Sleep(timecount);
			}

		}break;
		case 2: {

		}break;

		default:break;
		}
		m_hotKeyActive = 0;
	}

	CDialogEx::OnTimer(nIDEvent);
}


void CLOL连发Dlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
