/*
** Author: Ivan Chapkailo
** Date:   03.08.2017
**
** 2017 © Ivan Chapkailo for Avtonomic
**/

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CListCarDlg dialog

class CListCarDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CListCarDlg)

public:
	CListCarDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CListCarDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LIST_CAR };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	void SetColumns();									// sets columns in list control
	void SetPopulation();								// fills list

public:
	afx_msg void OnNMClickAbout(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBack();
	afx_msg void OnBnClickedExit();

private:
	CListCtrl m_List;
	LVCOLUMN m_lvColumn;
	LVITEM m_lvItem;
	int m_nItem;
	HICON m_hIcon;
};
