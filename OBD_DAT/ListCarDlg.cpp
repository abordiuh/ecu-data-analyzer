/*
** Author: Ivan Chapkailo
** Date:   03.08.2017
**
** 2017 © Ivan Chapkailo for Avtonomic
**
** Updated 09.08.2017: Added file reader and parser
**/

// ListCarDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OBD_DAT.h"
#include "OBD_DATDlg.h"
#include "ListCarDlg.h"
#include "afxdialogex.h"

using namespace std;

// CAboutDlg dialog used for App About

class CAboutDlgLSC : public CDialogEx
{
public:
	CAboutDlgLSC();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

														// Implementation
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedMfclink3();
};

CAboutDlgLSC::CAboutDlgLSC() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlgLSC::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlgLSC, CDialogEx)
	ON_BN_CLICKED(IDC_MFCLINK3, &CAboutDlgLSC::OnBnClickedMfclink3)
END_MESSAGE_MAP()


// CListCarDlg dialog

IMPLEMENT_DYNAMIC(CListCarDlg, CDialogEx)

CListCarDlg::CListCarDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LIST_CAR, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_LOGO);
}

CListCarDlg::~CListCarDlg()
{
}

void CListCarDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STORE_ITEMS, m_List);
}


BEGIN_MESSAGE_MAP(CListCarDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CLICK, IDC_ABOUT, &CListCarDlg::OnNMClickAbout)
	ON_BN_CLICKED(IDBACK, &CListCarDlg::OnBnClickedBack)
	ON_BN_CLICKED(IDEXIT, &CListCarDlg::OnBnClickedExit)
END_MESSAGE_MAP()


// CListCarDlg message handlers


BOOL CListCarDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO:  Add extra initialization here

	// fill list
	//
	SetColumns();
	SetPopulation();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CListCarDlg::OnPaint()
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

void CListCarDlg::SetColumns()
{
	// Setting of columns inside list control
	//
	m_lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt = LVCFMT_LEFT;
	m_lvColumn.cx = 80;
	m_lvColumn.pszText = L"Brand";
	m_List.InsertColumn(0, &m_lvColumn);

	m_lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt = LVCFMT_LEFT;
	m_lvColumn.cx = 90;
	m_lvColumn.pszText = L"Car Model";
	m_List.InsertColumn(1, &m_lvColumn);

	m_lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt = LVCFMT_LEFT;
	m_lvColumn.cx = 70;
	m_lvColumn.pszText = L"Year";
	m_List.InsertColumn(2, &m_lvColumn);

	m_lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt = LVCFMT_LEFT;
	m_lvColumn.cx = 100;
	m_lvColumn.pszText = L"Car Model ID";
	m_List.InsertColumn(3, &m_lvColumn);

	m_lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt = LVCFMT_LEFT;
	m_lvColumn.cx = 75;
	m_lvColumn.pszText = L"Speed";
	m_List.InsertColumn(4, &m_lvColumn);

	m_lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt = LVCFMT_LEFT;
	m_lvColumn.cx = 75;
	m_lvColumn.pszText = L"RPM";
	m_List.InsertColumn(5, &m_lvColumn);

	m_lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt = LVCFMT_LEFT;
	m_lvColumn.cx = 90;
	m_lvColumn.pszText = L"Turn signal";
	m_List.InsertColumn(6, &m_lvColumn);

	m_lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt = LVCFMT_LEFT;
	m_lvColumn.cx = 75;
	m_lvColumn.pszText = L"Brake";
	m_List.InsertColumn(7, &m_lvColumn);

	m_lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt = LVCFMT_LEFT;
	m_lvColumn.cx = 90;
	m_lvColumn.pszText = L"Accelerator";
	m_List.InsertColumn(8, &m_lvColumn);

	m_lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt = LVCFMT_LEFT;
	m_lvColumn.cx = 80;
	m_lvColumn.pszText = L"Steering";
	m_List.InsertColumn(9, &m_lvColumn);

	m_lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt = LVCFMT_LEFT;
	m_lvColumn.cx = 130;
	m_lvColumn.pszText = L"Standard OBD (TBD)";
	m_List.InsertColumn(10, &m_lvColumn);

	m_lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt = LVCFMT_LEFT;
	m_lvColumn.cx = 100;
	m_lvColumn.pszText = L"Updated date";
	m_List.InsertColumn(11, &m_lvColumn);
}

void CListCarDlg::SetPopulation()
{
	// Setting of data inside list control
	//
	string line;
	ifstream myfile("lscDB.lsc");

	if (myfile.is_open())
	{
		// fill list
		//
		while (getline(myfile, line))
		{
			wstring wstr(line.begin(), line.end());			// for converting string to LPCTSTR
			wstring buff;									// buffer for words
			int j = 0;										// global counter variable

			// set start item
			//
			m_lvItem.mask = LVIF_TEXT;
			m_lvItem.iItem = 0;
			m_lvItem.iSubItem = 0;
			++m_lvItem.iItem;

			// filling list with opened file
			//
			for (int k = 0; k < 12; ++k)
			{
				for (; j < wstr.length(); ++j)
				{
					if (wstr[j] != '\t')
					{
						buff += wstr[j];
					}
					else if (wstr[j] == '\t')
						break;
				}
				switch (k)
				{
				case 0:
					m_lvItem.pszText = &buff[0];
					m_nItem = m_List.InsertItem(&m_lvItem);
				case 1:
					m_List.SetItemText(m_nItem, 1, &buff[0]);
					break;
				case 2:
					m_List.SetItemText(m_nItem, 2, &buff[0]);
					break;
				case 3:
					m_List.SetItemText(m_nItem, 3, &buff[0]);
					break;
				case 4:
					m_List.SetItemText(m_nItem, 4, &buff[0]);
					break;
				case 5:
					m_List.SetItemText(m_nItem, 5, &buff[0]);
					break;
				case 6:
					m_List.SetItemText(m_nItem, 6, &buff[0]);
					break;
				case 7:
					m_List.SetItemText(m_nItem, 7, &buff[0]);
					break;
				case 8:
					m_List.SetItemText(m_nItem, 8, &buff[0]);
					break;
				case 9:
					m_List.SetItemText(m_nItem, 9, &buff[0]);
					break;
				case 10:
					m_List.SetItemText(m_nItem, 10, &buff[0]);
					break;
				case 11:
					m_List.SetItemText(m_nItem, 11, &buff[0]);
					break;
				}
				++j;
				buff.clear();
			}

			// check for empty
			//
			if (line.empty())
			{
				for (int j = 0; j < 12; ++j)
					m_List.SetItemText(m_nItem, j, L"No data - file is empty");
			}
		}
		myfile.close();
	}
	else
	{
		m_lvItem.mask = LVIF_TEXT;
		m_lvItem.iItem = 0;
		m_lvItem.iSubItem = 0;
		m_lvItem.pszText = L"Unable to open file";
		m_nItem = m_List.InsertItem(&m_lvItem);
		for (int j = 0; j < 12; ++j)
			m_List.SetItemText(m_nItem, j, L"Unable to open file");
	}
}

void CListCarDlg::OnNMClickAbout(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	CAboutDlgLSC dlgAbout;
	dlgAbout.DoModal();
}


void CListCarDlg::OnBnClickedBack()
{
	// TODO: Add your control notification handler code here
	SendMessage(WM_CLOSE);
	COBD_DATDlg cbdlg;
	cbdlg.DoModal();
}


void CListCarDlg::OnBnClickedExit()
{
	// TODO: Add your control notification handler code here
	SendMessage(WM_CLOSE);
}

HCURSOR CListCarDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CAboutDlgLSC::OnBnClickedMfclink3()
{
	// TODO: Add your control notification handler code here
}
