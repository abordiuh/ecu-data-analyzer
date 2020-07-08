/*
** Author: Ivan Chapkailo
** Date:   02.08.2017
**
** 2017 © Ivan Chapkailo for Avtonomic
**/

// OBD_DATDlg.h : header file
//

#pragma once


// COBD_DATDlg dialog
class COBD_DATDlg : public CDialogEx
{
// Construction
public:
	COBD_DATDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_OBD_DAT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	CStatic* m_Label; // var for controlling static title text
	HICON m_hIcon;
	CBrush m_clr;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMClickAbout(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedLsc();
	afx_msg void OnBnClickedNod();
};
