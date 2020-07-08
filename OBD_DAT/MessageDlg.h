/*
** Author: Ivan Chapkailo
** Date:   23.08.2017
**
** 2017 © Ivan Chapkailo for Avtonomic
**
** Updated 23.08.2017: Added new constructor for sending parameters for dialog window - title and message.
**/

#pragma once
#include "afxcmn.h"


// CMessageDlg dialog

class CMessageDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMessageDlg)

public:
	CMessageDlg(CWnd* pParent = NULL);   // standard constructor
	CMessageDlg(LPCTSTR message, LPCTSTR title, CWnd* pParent = NULL); // non standard cstr
	virtual ~CMessageDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MESSAGE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

private:
	// message label control
	//
	CLinkCtrl m_linkCtrl;

	LPCTSTR m_message, m_title;
};
