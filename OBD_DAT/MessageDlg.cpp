/*
** Author: Ivan Chapkailo
** Date:   23.08.2017
**
** 2017 © Ivan Chapkailo for Avtonomic
**
** Updated 23.08.2017: Added new constructor for sending parameters for dialog window - title and message.
**/

// MessageDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OBD_DAT.h"
#include "MessageDlg.h"
#include "afxdialogex.h"


// CMessageDlg dialog

IMPLEMENT_DYNAMIC(CMessageDlg, CDialogEx)

CMessageDlg::CMessageDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MESSAGE_DIALOG, pParent)
{

}

CMessageDlg::CMessageDlg(LPCTSTR message, LPCTSTR title, CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MESSAGE_DIALOG, pParent)
{
	m_message = message;
	m_title = title;
}

CMessageDlg::~CMessageDlg()
{
}

void CMessageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MESSAGE_LBL, m_linkCtrl);
}


BEGIN_MESSAGE_MAP(CMessageDlg, CDialogEx)
END_MESSAGE_MAP()


// CMessageDlg message handlers
BOOL CMessageDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_linkCtrl.SetWindowTextW(m_message);
	SetWindowText(m_title);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}