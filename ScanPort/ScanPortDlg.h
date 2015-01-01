
// ScanPortDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include <afxwin.h>
#define MAX_THREADS		50  //最大线程数

// CScanPortDlg 对话框
class CScanPortDlg : public CDialogEx
{
// 构造
public:
	CScanPortDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_SCANPORT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMultipleip2();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedRun();
	afx_msg void OnBnClickedSingleip();
	afx_msg void OnBnClickedMultiip();
	afx_msg void OnBnClickedDefaultPort();
	afx_msg void OnBnClickedPort();
//	CIPAddressCtrl m_Single_Control;
private:
	class Config
	{
	public:
		/*ip地址与端口的设置，m_ip=0表示单个IP，m_ip=1表示IP段
		m_port=0表示默认端口（1-1024），m_port=1表示自定义端口
		*/
		int ip,port;	
	};
	CString m_ip_start,m_ip_end;
	Config m_config;
public:
	CIPAddressCtrl m_Control_Start;
	CIPAddressCtrl m_Control_End;
	CIPAddressCtrl m_Control_Single;
	int m_port_start;
	int m_port_end;
	CString m_Result;
};
