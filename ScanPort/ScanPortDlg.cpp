
// ScanPortDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ScanPort.h"
#include "ScanPortDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//默认扫描的端口
char *ports[32]={
"21",
"22",
"23",
"25",
"53",
"79",
"80",
"110",
"111",
"113",
"123",
"135",
"139",
"143",
"443",
"512",
"513",
"514",
"515",
"540",
"1080",
"1433",
"1521",
"1524",
"3306",
"3389",
"5631",
"6000",
"6112",
"8000",
"8080",
"12345"
};

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CScanPortDlg 对话框



CScanPortDlg::CScanPortDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CScanPortDlg::IDD, pParent)
	, m_port_start(0)
	, m_port_end(0)
	, m_Result(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CScanPortDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_IP_ONE, m_Single_Control);
	DDX_Control(pDX, IDC_IP_START, m_Control_Start);
	DDX_Control(pDX, IDC_IP_END, m_Control_End);
	DDX_Control(pDX, IDC_IP_ONE, m_Control_Single);
	DDX_Text(pDX, IDC_PORT_START, m_port_start);
	DDV_MinMaxUInt(pDX, m_port_start, 0, 65535);
	DDX_Text(pDX, IDC_PORT_END, m_port_end);
	DDV_MinMaxUInt(pDX, m_port_end, 0, 65535);
	DDX_Text(pDX, IDC_RESULT, m_Result);
}

BEGIN_MESSAGE_MAP(CScanPortDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CScanPortDlg::OnBnClickedCancel)
	ON_BN_CLICKED(ID_RUN, &CScanPortDlg::OnBnClickedRun)
	ON_BN_CLICKED(IDC_SINGLEIP, &CScanPortDlg::OnBnClickedSingleip)
	ON_BN_CLICKED(IDC_MULTIIP, &CScanPortDlg::OnBnClickedMultiip)
	ON_BN_CLICKED(IDC_DEFAULT_PORT, &CScanPortDlg::OnBnClickedDefaultPort)
	ON_BN_CLICKED(IDC_PORT, &CScanPortDlg::OnBnClickedPort)
END_MESSAGE_MAP()


// CScanPortDlg 消息处理程序

BOOL CScanPortDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	((CButton *)GetDlgItem(IDC_SINGLEIP))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_DEFAULT_PORT))->SetCheck(TRUE);

	GetDlgItem(IDC_IP_ONE)->EnableWindow(TRUE);
	GetDlgItem(IDC_IP_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_IP_END)->EnableWindow(FALSE);
	GetDlgItem(IDC_PORT_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_PORT_END)->EnableWindow(FALSE);

	m_config.ip=0;
	m_config.port=0;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CScanPortDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CScanPortDlg::OnPaint()
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
HCURSOR CScanPortDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CScanPortDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}

void CScanPortDlg::OnBnClickedRun()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_RESULT)->SetWindowTextA("");	/* 清空结果框 */
	UpdateData();
	GetDlgItem(ID_RUN)->EnableWindow(FALSE);	/* 开始扫描按钮不可用 */
	BYTE f0,f1,f2,f3;

	//获取ip地址
	if(0==m_config.ip)	//单个IP
	{
		m_Control_Single.GetAddress(f0,f1,f2,f3);
		m_ip_start.Format("%d.%d.%d.%d",f0,f1,f2,f3);
		m_ip_end.SetString(m_ip_start);	/* 开始IP等于结束IP */
	}
	else if(1==m_config.ip)	//IP段
	{
		m_Control_Start.GetAddress(f0,f1,f2,f3);
		m_ip_start.Format("%d.%d.%d.%d",f0,f1,f2,f3);
		m_Control_End.GetAddress(f0,f1,f2,f3);
		m_ip_end.Format("%d.%d.%d.%d",f0,f1,f2,f3);
	}
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2,2), &wsadata) != 0)  //如果初始化错误
	{
		MessageBox("Wsatartup error!","ERROR",MB_ICONERROR);
		return;
	}
		
	int ip_start,ip_end;	//ip地址段的开始与结束
	//计算ip地址，结果为网络字节序
	ip_start=inet_addr(m_ip_start);
	ip_end=inet_addr(m_ip_end);
	
	for (int cur_ip = ip_start; cur_ip <=ip_end; cur_ip++)	/* 循环扫描IP */
	{
		if (0==cur_ip%256||255==cur_ip%256)	//*.*.*.0和*.*.*.255的处理
		{
			continue;
		}
		
		if (0==m_config.port)	/* 设置为默认端口扫描 */
		{
			m_port_start=0;
			m_port_end=31;
		}
		for(int j=m_port_start;j<=m_port_end;j++)
		{
			CSocket socket;
			if(!socket.Create())	/* 套接字创建失败 */
			{
				MessageBox("Socket error!","ERROR",MB_ICONERROR);
				WSACleanup();
				GetDlgItem(ID_RUN)->EnableWindow(TRUE);
				return;
			}
			struct in_addr inaddr;
			inaddr.s_addr=cur_ip;
			if (m_config.port==1&&socket.Connect(inet_ntoa(inaddr),j)) /* 自定义端口扫描 */
			{
				CString str;
				str.Format("[Found] %s: Port %d open.\r\n",inet_ntoa(inaddr),j);
				m_Result+=str;
				UpdateData(FALSE);
			}
			else if (m_config.port==0&&socket.Connect(inet_ntoa(inaddr),atoi(ports[j])))/* 默认端口扫描 */
			{
				CString str;
				str.Format("[Found] %s: Port %d open.\r\n",inet_ntoa(inaddr),atoi(ports[j]));
				m_Result+=str;
				UpdateData(FALSE);
			}
			socket.Close();	/* 关闭套接字 */
		}
	}
	WSACleanup();
	GetDlgItem(ID_RUN)->EnableWindow(TRUE);
	MessageBox("Scan has been completed!","Info",MB_ICONINFORMATION);
}


void CScanPortDlg::OnBnClickedSingleip()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_IP_ONE)->EnableWindow(TRUE);
	GetDlgItem(IDC_IP_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_IP_END)->EnableWindow(FALSE);
	m_config.ip=0;
}


void CScanPortDlg::OnBnClickedMultiip()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_IP_ONE)->EnableWindow(FALSE);
	GetDlgItem(IDC_IP_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_IP_END)->EnableWindow(TRUE);
	m_config.ip=1;
}


void CScanPortDlg::OnBnClickedDefaultPort()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_PORT_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_PORT_END)->EnableWindow(FALSE);
	m_config.port=0;
}


void CScanPortDlg::OnBnClickedPort()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_PORT_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_PORT_END)->EnableWindow(TRUE);
	m_config.port=1;
}
