
// ScanPortDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ScanPort.h"
#include "ScanPortDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//Ĭ��ɨ��Ķ˿�
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

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CScanPortDlg �Ի���



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


// CScanPortDlg ��Ϣ�������

BOOL CScanPortDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	((CButton *)GetDlgItem(IDC_SINGLEIP))->SetCheck(TRUE);
	((CButton *)GetDlgItem(IDC_DEFAULT_PORT))->SetCheck(TRUE);

	GetDlgItem(IDC_IP_ONE)->EnableWindow(TRUE);
	GetDlgItem(IDC_IP_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_IP_END)->EnableWindow(FALSE);
	GetDlgItem(IDC_PORT_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_PORT_END)->EnableWindow(FALSE);

	m_config.ip=0;
	m_config.port=0;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CScanPortDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CScanPortDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CScanPortDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}

void CScanPortDlg::OnBnClickedRun()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_RESULT)->SetWindowTextA("");	/* ��ս���� */
	UpdateData();
	GetDlgItem(ID_RUN)->EnableWindow(FALSE);	/* ��ʼɨ�谴ť������ */
	BYTE f0,f1,f2,f3;

	//��ȡip��ַ
	if(0==m_config.ip)	//����IP
	{
		m_Control_Single.GetAddress(f0,f1,f2,f3);
		m_ip_start.Format("%d.%d.%d.%d",f0,f1,f2,f3);
		m_ip_end.SetString(m_ip_start);	/* ��ʼIP���ڽ���IP */
	}
	else if(1==m_config.ip)	//IP��
	{
		m_Control_Start.GetAddress(f0,f1,f2,f3);
		m_ip_start.Format("%d.%d.%d.%d",f0,f1,f2,f3);
		m_Control_End.GetAddress(f0,f1,f2,f3);
		m_ip_end.Format("%d.%d.%d.%d",f0,f1,f2,f3);
	}
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2,2), &wsadata) != 0)  //�����ʼ������
	{
		MessageBox("Wsatartup error!","ERROR",MB_ICONERROR);
		return;
	}
		
	int ip_start,ip_end;	//ip��ַ�εĿ�ʼ�����
	//����ip��ַ�����Ϊ�����ֽ���
	ip_start=inet_addr(m_ip_start);
	ip_end=inet_addr(m_ip_end);
	
	for (int cur_ip = ip_start; cur_ip <=ip_end; cur_ip++)	/* ѭ��ɨ��IP */
	{
		if (0==cur_ip%256||255==cur_ip%256)	//*.*.*.0��*.*.*.255�Ĵ���
		{
			continue;
		}
		
		if (0==m_config.port)	/* ����ΪĬ�϶˿�ɨ�� */
		{
			m_port_start=0;
			m_port_end=31;
		}
		for(int j=m_port_start;j<=m_port_end;j++)
		{
			CSocket socket;
			if(!socket.Create())	/* �׽��ִ���ʧ�� */
			{
				MessageBox("Socket error!","ERROR",MB_ICONERROR);
				WSACleanup();
				GetDlgItem(ID_RUN)->EnableWindow(TRUE);
				return;
			}
			struct in_addr inaddr;
			inaddr.s_addr=cur_ip;
			if (m_config.port==1&&socket.Connect(inet_ntoa(inaddr),j)) /* �Զ���˿�ɨ�� */
			{
				CString str;
				str.Format("[Found] %s: Port %d open.\r\n",inet_ntoa(inaddr),j);
				m_Result+=str;
				UpdateData(FALSE);
			}
			else if (m_config.port==0&&socket.Connect(inet_ntoa(inaddr),atoi(ports[j])))/* Ĭ�϶˿�ɨ�� */
			{
				CString str;
				str.Format("[Found] %s: Port %d open.\r\n",inet_ntoa(inaddr),atoi(ports[j]));
				m_Result+=str;
				UpdateData(FALSE);
			}
			socket.Close();	/* �ر��׽��� */
		}
	}
	WSACleanup();
	GetDlgItem(ID_RUN)->EnableWindow(TRUE);
	MessageBox("Scan has been completed!","Info",MB_ICONINFORMATION);
}


void CScanPortDlg::OnBnClickedSingleip()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_IP_ONE)->EnableWindow(TRUE);
	GetDlgItem(IDC_IP_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_IP_END)->EnableWindow(FALSE);
	m_config.ip=0;
}


void CScanPortDlg::OnBnClickedMultiip()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_IP_ONE)->EnableWindow(FALSE);
	GetDlgItem(IDC_IP_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_IP_END)->EnableWindow(TRUE);
	m_config.ip=1;
}


void CScanPortDlg::OnBnClickedDefaultPort()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_PORT_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_PORT_END)->EnableWindow(FALSE);
	m_config.port=0;
}


void CScanPortDlg::OnBnClickedPort()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_PORT_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_PORT_END)->EnableWindow(TRUE);
	m_config.port=1;
}
