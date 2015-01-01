
// ScanPortDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include <afxwin.h>
#define MAX_THREADS		50  //����߳���

// CScanPortDlg �Ի���
class CScanPortDlg : public CDialogEx
{
// ����
public:
	CScanPortDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_SCANPORT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
		/*ip��ַ��˿ڵ����ã�m_ip=0��ʾ����IP��m_ip=1��ʾIP��
		m_port=0��ʾĬ�϶˿ڣ�1-1024����m_port=1��ʾ�Զ���˿�
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
