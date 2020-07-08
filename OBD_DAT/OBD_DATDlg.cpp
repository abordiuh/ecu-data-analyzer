/*
** Author: Ivan Chapkailo
** Date:   02.08.2017
**
** 2017 © Ivan Chapkailo for Avtonomic
**/

// OBD_DATDlg.cpp : implementation file
//
/*
 * Author: Ivan Chapkailo - https://github.com/septimomend
 * Date:   02.08.2017
 * 2017 © Ivan Chapkailo for Avtonomic
 */


#include "stdafx.h"
#include "OBD_DAT.h"
#include "OBD_DATDlg.h"
#include "ListCarDlg.h"
#include "NODADlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// COBD_DATDlg dialog



COBD_DATDlg::COBD_DATDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_OBD_DAT_DIALOG, pParent)
	, m_Label(NULL)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_LOGO);
}

void COBD_DATDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COBD_DATDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_NOTIFY(NM_CLICK, IDC_ABOUT, &COBD_DATDlg::OnNMClickAbout)
	ON_BN_CLICKED(IDLSC, &COBD_DATDlg::OnBnClickedLsc)
	ON_BN_CLICKED(IDNOD, &COBD_DATDlg::OnBnClickedNod)
END_MESSAGE_MAP()


// COBD_DATDlg message handlers

BOOL COBD_DATDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_clr.CreateSolidBrush(RGB(255, 255, 255));	// create brush

	// set font for title
	//
	CFont *m_FontTitle = new CFont;
	m_FontTitle->CreatePointFont(300, L"Times New Roman");
	m_Label = (CStatic *)GetDlgItem(IDC_TITLE_STRING);
	m_Label->SetFont(m_FontTitle);
	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

HBRUSH COBD_DATDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{	
	return m_clr;	// return brush
}

void COBD_DATDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COBD_DATDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COBD_DATDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void COBD_DATDlg::OnNMClickAbout(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}

void COBD_DATDlg::OnBnClickedLsc()
{
	// TODO: Add your control notification handler code here
	SendMessage(WM_CLOSE);
	CListCarDlg dlgListCar;
	dlgListCar.DoModal();
}


void COBD_DATDlg::OnBnClickedNod()
{
	// TODO: Add your control notification handler code here
	SendMessage(WM_CLOSE);
	CNODADlg dlgNoda;
	dlgNoda.DoModal();
}
