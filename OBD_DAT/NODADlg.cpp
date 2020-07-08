/*
** Author: Ivan Chapkailo
** Date:   05.08.2017
**
** 2017 © Ivan Chapkailo for Avtonomic
**
** Updated 08.08.2017: Implemented file reading
** Updated 09.08.2017: Added file reader and parser
** Updated 10.08.2017: Linked with MainDataClass and created SortMethods instance
**					   and calling sorting functions by clicking 'Sort by PID' button
** Updated 11.08.2017: Implemented sort algorithm and optimized code
** Updated 14.08.2017: Fixed displaying of data after sorting and optimized some functions and code
** Updated 15.08.2017: Changed sorting algorithm and reading logic. Added analyzer instance
**					   Implemented Analyzer with New Data - comparation with Turn Signal
** Updated 16.08.2017: Implemented Analyse with New fully. Implemented Analysis with Two Files. 
**					   Optimized code and fixed errors
** Updated 17.08.2017: Added reading folder within files
** Updated 21.08.2017: Added new column for car ID and parameter info. Implemented "Input data" chapter from new requirements
** Updated 22.08.2017: Added parameter info. Implemented "Input data" chapter from new requirements. Optimized. Added try-catch block
**					   for prevent of file reading error
** Updated 23.08.2017: Changed architecture and logic. Added menu and new dialog
** Updated 25.08.2017: Implemented Sort -> Normal. Optimized. UPD: Added all sorting methods (normal/brake/.../steering wheel)
** Updated 01.09.2017: Fixed memory leaks. Added sort by PID and sort by Car ID operations.
**/

// NODADlg.cpp : implementation file
//

#include "stdafx.h"
#include "OBD_DAT.h"
#include "OBD_DATDlg.h"
#include "NODADlg.h"
#include "afxdialogex.h"

using namespace std;


// CAboutDlg dialog used for App About

class CAboutDlgNODA : public CDialogEx
{
public:
	CAboutDlgNODA();

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

CAboutDlgNODA::CAboutDlgNODA() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlgNODA::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlgNODA, CDialogEx)
END_MESSAGE_MAP()

// CNODADlg dialog

IMPLEMENT_DYNAMIC(CNODADlg, CDialogEx)

CNODADlg::CNODADlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_NOD_ANALYSIS, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_LOGO);

	m_strPath = _T("");
	m_strName = _T("");
	m_strRememberPath = _T("");
	m_strRememberName = _T("");
	m_smFilename = _T("");
	m_strFilter = _T("*.txt;*.noda;*.log");
	m_title = _T("Files extension - *.noda;*.log;*.txt");
	m_bFilter = TRUE;
	m_pToolTip = NULL;
	m_prevStrPath = _T("");
	m_rowNumber = 0;
	m_canClear = false;

	m_pSM = m_mdc.getSM();
	m_pOA = m_mdc.getOA();
	m_pOFR = m_mdc.getOFR();
}

CNODADlg::~CNODADlg()
{
	SAFE_DELETE(m_pToolTip);
}

void CNODADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STORE_ITEMS_NODA, m_ListNODA);

	DDX_Control(pDX, IDC_EDIT_PATH, m_wndPath);
	DDX_Text(pDX, IDC_EDIT_PATH, m_strPath);
	DDV_MaxChars(pDX, m_strPath, _MAX_PATH);
	DDX_Control(pDX, IDC_ND_TAB, m_ndTab);
	DDX_Control(pDX, IDC_SYSLINK1, m_textCW);
	DDX_Control(pDX, IDC_EDIT_PID, m_editPID);
	DDX_Control(pDX, IDC_EDIT_CARID, m_editCarID);
}


BEGIN_MESSAGE_MAP(CNODADlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDBACKNODA, &CNODADlg::OnBnClickedBacknoda)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_STORE_ITEMS_NODA, &CNODADlg::OnLvnItemchangedStoreItemsNoda)
	ON_BN_CLICKED(IDC_SORT_PID_BUTTON, &CNODADlg::OnBnClickedSortPidButton)
	ON_NOTIFY(TCN_SELCHANGE, IDC_ND_TAB, &CNODADlg::OnTcnSelchangeNdTab)
	ON_COMMAND(ID_MORE_ABOUT, &CNODADlg::OnMoreAbout)
	ON_COMMAND(ID_DATA_EXIT, &CNODADlg::OnDataExit)
	ON_COMMAND(ID_DATA_SELECTFILE, &CNODADlg::OnDataSelectfile)
	ON_COMMAND(ID_DATA_SELECTFOLDER, &CNODADlg::OnDataSelectfolder)
	ON_COMMAND(ID_ANALYZE_COMPARETWOF, &CNODADlg::OnAnalyzeComparetwof)
	ON_COMMAND(ID_ANALYZE_COMPAREWITHDB, &CNODADlg::OnAnalyzeComparewithdb)
	ON_COMMAND(ID_SORT_SHOWALL, &CNODADlg::OnSortShowall)
	ON_COMMAND(ID_ANALYZE_ANALYZECARPARAMETERS, &CNODADlg::OnAnalyzeAnalyzecarparameters)
	ON_COMMAND(ID_SORT_SHOWNORMAL, &CNODADlg::OnSortShownormal)
	ON_COMMAND(ID_SORT_SHOWTURNSIGNAL, &CNODADlg::OnSortShowturnsignal)
	ON_COMMAND(ID_SORT_SHOWBRAKE, &CNODADlg::OnSortShowbrake)
	ON_COMMAND(ID_SORT_SHOWACCELERATOR, &CNODADlg::OnSortShowaccelerator)
	ON_COMMAND(ID_SORT_SHOWSTEERINGWHEEL, &CNODADlg::OnSortShowsteeringwheel)
	ON_BN_CLICKED(IDC_SORT_PID_BUTTON2, &CNODADlg::OnBnClickedSortPidButton2)
	ON_EN_CHANGE(IDC_EDIT_CARID, &CNODADlg::OnEnChangeEditCarid)
END_MESSAGE_MAP()


// CNODADlg message handlers

BOOL CNODADlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO:  Add extra initialization here
	//ShowWindow(SW_MAXIMIZE);
	SetColumns();
	m_textCW.ShowWindow(SW_HIDE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CNODADlg::CreateToolTips()
{
	ASSERT_VALID(this);
	ASSERT(m_pToolTip == NULL);

	m_pToolTip = new CToolTipCtrl;
	ASSERT(m_pToolTip != NULL);

	if (m_pToolTip)
	{
		BOOL bCreated = m_pToolTip->Create(this);
		ASSERT(bCreated != FALSE);

		if (bCreated)
		{
			CRect rcMargins(3, 3, 3, 3);
			m_pToolTip->SetMargin(&rcMargins);

			VERIFY(m_pToolTip->AddTool(&m_wndPath, m_wndRoot.GetDlgCtrlID()));

			CWnd* pWndTmp = GetDlgItem(IDOK);
			ASSERT(pWndTmp != NULL);

			if (pWndTmp)
				VERIFY(m_pToolTip->AddTool(pWndTmp, pWndTmp->GetDlgCtrlID()));

			m_pToolTip->Activate(TRUE);
			return (TRUE);
		}
	}

	return (FALSE);
}

void CNODADlg::OnPaint()
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
HCURSOR CNODADlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CNODADlg::SetColumns()
{
	// Setting of columns inside list control
	//
	m_lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt = LVCFMT_LEFT;
	m_lvColumn.cx = 160;
	m_lvColumn.pszText = L"File Name";
	m_ListNODA.InsertColumn(0, &m_lvColumn);

	m_lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt = LVCFMT_LEFT;
	m_lvColumn.cx = 100;
	m_lvColumn.pszText = L"OBD message";
	m_ListNODA.InsertColumn(1, &m_lvColumn);

	m_lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt = LVCFMT_LEFT;
	m_lvColumn.cx = 150;
	m_lvColumn.pszText = L"PID";
	m_ListNODA.InsertColumn(2, &m_lvColumn);

	m_lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt = LVCFMT_LEFT;
	m_lvColumn.cx = 300;
	m_lvColumn.pszText = L"OBD Data";
	m_ListNODA.InsertColumn(3, &m_lvColumn);

	m_lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt = LVCFMT_LEFT;
	m_lvColumn.cx = 151;
	m_lvColumn.pszText = L"Data";
	m_ListNODA.InsertColumn(4, &m_lvColumn);

	m_lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt = LVCFMT_LEFT;
	m_lvColumn.cx = 150;
	m_lvColumn.pszText = L"Parameter Name";
	m_ListNODA.InsertColumn(5, &m_lvColumn);

	m_lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt = LVCFMT_LEFT;
	m_lvColumn.cx = 100;
	m_lvColumn.pszText = L"Car ID";
	m_ListNODA.InsertColumn(6, &m_lvColumn);
}

void CNODADlg::SetPopulation()
{
	// clear buffer
	//
	if (m_strPath != m_prevStrPath)
	{
		m_pSM->clear();	
		m_pOA->clear();
	}
	if (m_smFilename == "sm.noda")
		m_strPath = m_smFilename;
	//
	m_rowNumber = 0;
	string line, path;
	size_t k = 0;

	// reverse vectors
	//
	reverse(m_wsFilenames.begin(), m_wsFilenames.end());
	reverse(m_wsID.begin(), m_wsID.end());
	reverse(m_wsNames.begin(), m_wsNames.end());

	if (!m_wsFilenames.empty())
	{
		vector<wstring>::const_iterator iter, itid;

		for (iter = m_wsFilenames.begin(), itid = m_wsID.begin();
			iter != m_wsFilenames.end(), itid != m_wsID.end(); ++iter, ++itid)
		{
			path = m_gb.ws2s(*iter);							// convert path to file from wstring to string
			replace(path.begin(), path.end(), '\\', '/');		// replcae \\ to /
			m_strName = m_wsNames[k].c_str();					// get name of file
			++k;
			m_strPath = path.c_str();							// set the path
			CT2CA convname(m_strName);
			string namestr(convname);

			ifstream myfile(m_strPath);							// open file using the path

			if (myfile.is_open())
			{
				wstring buff;									// buffer for words
				size_t j = 0;									// global counter variable

				// fill first row
				//
				m_lvItem.mask = LVIF_TEXT;
				m_lvItem.iItem = 0;
				m_lvItem.iSubItem = 0;
				m_lvItem.pszText = (LPWSTR)(LPCTSTR)m_strName;	// print filename
				m_nItem = m_ListNODA.InsertItem(&m_lvItem);		// insert item in list

				getline(myfile, line);							// get first line
				wstring wfirststr(line.begin(), line.end());	// and convert to wstring
				m_pSM->setAllData(namestr, line);

				for (; j < wfirststr.length(); ++j)
				{
					if (wfirststr[j] != '\t')
						buff += wfirststr[j];
					else if (wfirststr[j] == '\t')
						break;
				}
				m_ListNODA.SetItemText(m_nItem, 3, &buff[0]);
				buff.clear();
				for (size_t i = 6; i < 14; ++i)
					buff += wfirststr[i];
				m_ListNODA.SetItemText(m_nItem, 2, &buff[0]);
				buff.clear();
				for (size_t i = 16; i < 32; ++i)
					buff += wfirststr[i];
				m_ListNODA.SetItemText(m_nItem, 4, &buff[0]);
				++j;
				m_ListNODA.SetItemText(m_nItem, 6, itid->c_str());
				CT2CA convForInfo(m_strName);
				string nameinfo(convForInfo);
				string info = m_pOFR->setParameterInfo(nameinfo);
				wstring winfo = m_gb.s2ws(info);
				m_ListNODA.SetItemText(m_nItem, 5, winfo.c_str());
				buff.clear();

				// fill list
				//
				while (getline(myfile, line))
				{
					wstring wstr(line.begin(), line.end());			// for converting string to LPCTSTR
					j = 0;

					try
					{
						if (wstr.length() < 31)
							throw 155;
						
						m_pSM->setAllData(namestr, line);
						++m_lvItem.iItem;

						m_lvItem.pszText = L"";
						m_nItem = m_ListNODA.InsertItem(&m_lvItem);

						// filling list with opened file
						//
						for (; j < wstr.length(); ++j)
						{
							if (wstr[j] != '\t')
								buff += wstr[j];
							else if (wstr[j] == '\t')
								break;
						}
						m_ListNODA.SetItemText(m_nItem, 3, &buff[0]);
						buff.clear();
						for (size_t i = 6; i < 14; ++i)
							buff += wstr[i];
						m_ListNODA.SetItemText(m_nItem, 2, &buff[0]);
						buff.clear();
						for (size_t i = 16; i < 32; ++i)
							buff += wstr[i];
						m_ListNODA.SetItemText(m_nItem, 4, &buff[0]);
						++j;
						buff.clear();
					}
					catch (int i)
					{
						if (i == 155)
						{
							wstring werr = L"Error# 155\nDetected wrong data format - " + wstr;
							werr += L"\nFile: " + m_strName;
							if (MessageBox(werr.c_str(), L"File reading error", MB_ICONERROR | MB_CANCELTRYCONTINUE) == IDCANCEL)
								break;
						}
					}
				}

				m_rowNumber += m_lvItem.iItem;							// get number of rows

				if (m_canClear)
					myfile.clear();
				myfile.close();
			}
			else
			{
				m_lvItem.mask = LVIF_TEXT;
				m_lvItem.iItem = 0;
				m_lvItem.iSubItem = 0;
				m_lvItem.pszText = L"Wrong file extension";
				m_nItem = m_ListNODA.InsertItem(&m_lvItem);
				for (size_t i = 1; i <= 3; ++i)
					m_ListNODA.SetItemText(m_nItem, i, L"Unable to open file");
			}
		}
	}
	else
	{
		// else if this is not folder but single file
		//
		ifstream myfile(m_strPath);

		CT2CA convName(m_strName);
		string strn(convName);
		string buffer;

		if (strn.find("_D") != std::string::npos)
		{
			for (size_t i = 0; i < strn.length(); ++i)
			{
				if (strn[i] != '_')
					buffer += strn[i];
				else
					break;
			}
			if (!buffer.empty())
				m_carID = m_gb.s2ws(buffer);
			else
				m_carID = L"Wrong filename";
		}
		else
			m_carID = L"Car ID is unknown";

		if (myfile.is_open())
		{
			wstring buff;									// buffer for words
			size_t j = 0;									// global counter variable

			// fill first row
			//
			m_lvItem.mask = LVIF_TEXT;
			m_lvItem.iItem = 0;
			m_lvItem.iSubItem = 0;
			m_lvItem.pszText = (LPWSTR)(LPCTSTR)m_strName;			// print filename
			m_nItem = m_ListNODA.InsertItem(&m_lvItem);				// insert item in list

			getline(myfile, line);									// get first line
			wstring wfirststr(line.begin(), line.end());			// and convert to wstring

			m_pSM->setAllData(strn, line);

			for (; j < wfirststr.length(); ++j)
			{
				if (wfirststr[j] != '\t')
					buff += wfirststr[j];
				else if (wfirststr[j] == '\t')
					break;
			}
			m_ListNODA.SetItemText(m_nItem, 3, &buff[0]);
			buff.clear();
			for (size_t i = 6; i < 14; ++i)
				buff += wfirststr[i];
			m_ListNODA.SetItemText(m_nItem, 2, &buff[0]);
			buff.clear();
			for (size_t i = 16; i < 32; ++i)
				buff += wfirststr[i];
			m_ListNODA.SetItemText(m_nItem, 4, &buff[0]);
			m_ListNODA.SetItemText(m_nItem, 6, m_carID.c_str());
			CT2CA convForInfo(m_strName);
			string nameinfo(convForInfo);
			string info = m_pOFR->setParameterInfo(nameinfo);
			wstring winfo = m_gb.s2ws(info);
			m_ListNODA.SetItemText(m_nItem, 5, winfo.c_str());
			++j;
			buff.clear();

			// fill list
			//
			while (getline(myfile, line))
			{
				wstring wstr(line.begin(), line.end());			// for converting string to LPCTSTR
				j = 0;

				try
				{
					if (wstr.length() < 31)
						throw 155;

					m_pSM->setAllData(strn, line);
					++m_lvItem.iItem;
					m_lvItem.pszText = L"";
					m_nItem = m_ListNODA.InsertItem(&m_lvItem);

					// filling list with opened file
					//
					for (; j < wstr.length(); ++j)
					{
						if (wstr[j] != '\t')
							buff += wstr[j];
						else if (wstr[j] == '\t')
							break;
					}
					m_ListNODA.SetItemText(m_nItem, 3, &buff[0]);
					buff.clear();
					for (size_t i = 6; i < 14; ++i)
						buff += wstr[i];
					m_ListNODA.SetItemText(m_nItem, 2, &buff[0]);
					buff.clear();
					for (size_t i = 16; i < 32; ++i)
						buff += wstr[i];
					m_ListNODA.SetItemText(m_nItem, 4, &buff[0]);
					++j;
					buff.clear();
				}
				catch (int i)
				{
					if (i == 155)
					{
						wstring werr = L"Error# 155\nDetected wrong data format - " + wstr;
						werr += L"\nFile: " + m_strName;
						if (MessageBox(werr.c_str(), L"File reading error", MB_ICONERROR | MB_CANCELTRYCONTINUE) == IDCANCEL)
							break;
					}
				}
			}

			m_rowNumber = m_lvItem.iItem;							// get number of rows

			if (m_canClear)
				myfile.clear();
			myfile.close();
		}
		else
		{
			m_lvItem.mask = LVIF_TEXT;
			m_lvItem.iItem = 0;
			m_lvItem.iSubItem = 0;
			m_lvItem.pszText = L"Wrong file extension";
			m_nItem = m_ListNODA.InsertItem(&m_lvItem);
			for (size_t i = 1; i <= 5; ++i)
				m_ListNODA.SetItemText(m_nItem, i, L"Unable to open file");
		}
	}
	m_prevStrPath = m_strPath;
	m_bSorted = false;
	m_canClear = false;
	//m_wsFilenames.clear();
}

void CNODADlg::SetSortedData()
{
	// clear buffer
	//
	if (m_strPath != m_prevStrPath)
	{
		m_pSM->clear();
		m_pOA->clear();
	}
	//
	m_rowNumber = 0;
	string line, buffer;

	m_lvItem.mask = LVIF_TEXT;
	m_lvItem.iItem = 0;
	m_lvItem.iSubItem = 0;

	if (!(m_mapCarPID.empty()))
	{
		vector<string>::const_iterator vecit = m_vCarID.begin();
		multimap<string, string>::const_iterator iter = m_mapCarPID.begin();
		for (; iter != m_mapCarPID.end(), vecit != m_vCarID.end(); ++iter, ++vecit)
		{
			m_strName = vecit->c_str();
			CT2CA convName(m_strName);
			string strn(convName);

			if (strn.find("_D") != std::string::npos)
			{
				for (size_t i = 0; i < strn.length(); ++i)
				{
					if (strn[i] != '_')
						buffer += strn[i];
					else
						break;
				}
				if (!buffer.empty())
					m_carID = m_gb.s2ws(buffer);
				else
					m_carID = L"Wrong filename";
				buffer.clear();
			}
			else
				m_carID = L"Car ID is unknown";

			wstring buff;									// buffer for words
			size_t j = 0;									// global counter variable

			m_lvItem.pszText = (LPWSTR)(LPCTSTR)m_strName;			// print filename
			m_nItem = m_ListNODA.InsertItem(&m_lvItem);				// insert item in list

			line = iter->second;									// get first line
			wstring wfirststr(line.begin(), line.end());			// and convert to wstring

			wstring wstr(line.begin(), line.end());			// for converting string to LPCTSTR
			j = 0;

			try
			{
				if (wstr.length() < 31)
					throw 155;

				// filling list with opened file
				//
				for (; j < wfirststr.length(); ++j)
				{
					if (wfirststr[j] != '\t')
						buff += wfirststr[j];
					else if (wfirststr[j] == '\t')
						break;
				}
				m_ListNODA.SetItemText(m_nItem, 3, &buff[0]);
				buff.clear();
				for (size_t i = 6; i < 14; ++i)
					buff += wfirststr[i];
				m_ListNODA.SetItemText(m_nItem, 2, &buff[0]);
				buff.clear();
				for (size_t i = 16; i < 32; ++i)
					buff += wfirststr[i];
				m_ListNODA.SetItemText(m_nItem, 4, &buff[0]);
				m_ListNODA.SetItemText(m_nItem, 6, m_carID.c_str());
				CT2CA convForInfo(m_strName);
				string nameinfo(convForInfo);
				string info = m_pOFR->setParameterInfo(nameinfo);
				wstring winfo = m_gb.s2ws(info);
				m_ListNODA.SetItemText(m_nItem, 5, winfo.c_str());
				++j;
				buff.clear();
			}
			catch (int i)
			{
				if (i == 155)
				{
					wstring werr = L"Error# 155\nDetected wrong data format - " + wstr;
					werr += L"\nFile: " + m_strName;
					if (MessageBox(werr.c_str(), L"File reading error", MB_ICONERROR | MB_CANCELTRYCONTINUE) == IDCANCEL)
						break;
				}
			}
			++m_lvItem.iItem;
			m_rowNumber = m_lvItem.iItem;							// get number of rows
		}
	}
	else
	{
		m_lvItem.mask = LVIF_TEXT;
		m_lvItem.iItem = 0;
		m_lvItem.iSubItem = 0;
		m_lvItem.pszText = L"Wrong file extension";
		m_nItem = m_ListNODA.InsertItem(&m_lvItem);
		for (size_t i = 1; i <= 5; ++i)
			m_ListNODA.SetItemText(m_nItem, i, L"Unable to open file");
	}
	m_prevStrPath = m_strPath;
	m_bSorted = false;
	m_canClear = false;
}

void CNODADlg::ClearList()
{
	// clear block of data with row count size of opened file for replacing on sorted data
	//
	for (int i = (m_rowNumber); i >= 0; i--)
			m_ListNODA.DeleteItem(i);
	//m_ListNODA.DeleteAllItems();				// remove all items on list control
}

void CNODADlg::OnBnClickedBacknoda()
{
	SendMessage(WM_CLOSE);
	COBD_DATDlg cbdlg;
	cbdlg.DoModal();
}

void CNODADlg::OnLvnItemchangedStoreItemsNoda(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;
}


void CNODADlg::OnBnClickedSortPidButton()
{
	if (m_editPID.GetWindowTextLengthW() == 0)
	{
		MessageBox(L"Please, enter PID value.", L"No value", MB_OK);
		return;
	}
	CString pid;
	m_editPID.GetWindowText(pid);						// get text from edit box
	CT2CA conpid(pid);									// convert
	string matchedPid(conpid);							// to string
	m_mapCarPID = m_pSM->sortByPID(matchedPid);			// sort by PID
	// if no searched PID data - exit
	if (m_mapCarPID.empty())
	{
		wstring werr = L"No matching PIDs for " + m_gb.s2ws(matchedPid) + L"\nPlease, check searching data.";
		MessageBox(werr.c_str(), L"Searching", MB_OK);
		return;
	}
	m_vCarID = m_pSM->getCarIDVecFromMap();				// get car ID
	ClearList();
	SetSortedData();									// fill list
	m_mapCarPID.clear();
	m_vCarID.clear();
	m_strName = m_strRememberName;
	m_strPath = m_strRememberPath;
	m_wsFilenames = m_rememberFilenames;
}

void CNODADlg::OnTcnSelchangeNdTab(NMHDR *pNMHDR, LRESULT *pResult)
{
	int iSel = m_ndTab.GetCurSel();

	CT2CA pszConvertedAnsiString(m_strPath);	// convert from CString to string
	string path(pszConvertedAnsiString);
	m_pOA->setNormalLogPath(path);

	analyzeWithNew(iSel);						// do analyze

	*pResult = 0;
}

void CNODADlg::analyzeWithNew(int sel)
{
	m_pOA->analyzeNew(sel);
	m_strPath = "Analysis.log";
	switch (sel)
	{
	case 0:
		m_strName = "Analysis with turn signals";
		break;
	case 1:
		m_strName = "Analysis with brake";
		break;
	case 2:
		m_strName = "Analysis with accelerometer";
		break;
	case 3:
		m_strName = "Analysis with RPM";
		break;
	case 4:
		m_strName = "Analysis with speed";
		break;
	case 5:
		m_strName = "Analysis with steering wheel";
		break;
	default:
		perror(__FILE__" Wrong number in");
		return;
	}
	m_canClear = true;
	SetPopulation();
	m_strPath = m_strRememberPath;
	m_strName = m_strRememberName;
}

void CNODADlg::OnMoreAbout()
{
	CAboutDlgNODA dlgAbout;
	dlgAbout.DoModal();
}


void CNODADlg::OnDataExit()
{
	SendMessage(WM_CLOSE);
}


void CNODADlg::OnDataSelectfile()
{
	UpdateData();
	m_wsFilenames.clear();
	m_wsNames.clear();
	m_wsID.clear();

	CFileDialog* file = new CFileDialog(true);

	if (file->DoModal() == IDOK)
	{
		m_strPath = file->GetFolderPath();
		m_strName = file->GetFileName();

		CT2CA convertPath(m_strPath);
		string path(convertPath);
		CT2CA convertName(m_strName);
		string name(convertName);
		string fullpath = path + "\\" + name;
		replace(fullpath.begin(), fullpath.end(), '\\', '/');
		wstring wpath = m_gb.s2ws(fullpath);
		m_strPath = wpath.c_str();
		m_strRememberPath = m_strPath;
		m_strRememberName = m_strName;
		m_ndTab.DeleteAllItems();
		m_textCW.ShowWindow(SW_HIDE);
		UpdateData(FALSE);
		//m_wndPath.SetWindowTextW(m_strPath);
		if (m_pToolTip)
			m_pToolTip->UpdateTipText(m_strPath, &m_wndPath);

		SetPopulation();
	}


	SAFE_DELETE(file);
}


void CNODADlg::OnDataSelectfolder()
{
	UpdateData();
	m_wsFilenames.clear();
	m_wsNames.clear();
	m_wsID.clear();

	LPCTSTR lpszTitle = m_title;
	UINT	uFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI;

	CFolderDialog* pFolderDlg = NULL;

#ifdef USE_XP_FILTRATION

	if (m_bFilter == FALSE)
	{
#endif USE_XP_FILTRATION
		pFolderDlg = new CFolderDialog(lpszTitle, m_strPath, this, uFlags);
#ifdef USE_XP_FILTRATION
	}
	else
	{
		pFolderDlg = (CFolderDialog*)new CFilteredFolderDialog(lpszTitle, m_strPath,
			this, uFlags | BIF_BROWSEINCLUDEFILES);

		((CFilteredFolderDialog*)pFolderDlg)->SetFilter(m_strFilter);
	}

#endif // USE_XP_FILTRATION

	ASSERT(pFolderDlg != NULL);

	if (pFolderDlg != NULL)
	{
		pFolderDlg->SetRootFolder(NULL);

		if (pFolderDlg->DoModal() == IDOK)
		{
			m_strPath = pFolderDlg->GetFolderPath();
			m_strName = pFolderDlg->GetFolderName();
			m_strRememberPath = m_strPath;
			m_strRememberName = m_strName;
			CT2CA convertPath(m_strPath);
			string path(convertPath);
			CT2CA convertName(m_strName);
			string name(convertName);
			if (name.substr(name.find_last_of(".") + 1) != "txt" && name.substr(name.find_last_of(".") + 1) != "log")	// if this is not file
			{
				m_wsFilenames = m_gb.getFilenames(path);	// get filenames
				m_rememberFilenames = m_wsFilenames;
				m_wsNames = m_gb.getFilename();					// name of file
				m_rememberNames = m_wsNames;
				m_wsID = m_gb.getCarID();						// car ID
				m_rememberID = m_wsID;
			}
			m_ndTab.DeleteAllItems();
			m_textCW.ShowWindow(SW_HIDE);
			UpdateData(FALSE);

			if (m_pToolTip)
				m_pToolTip->UpdateTipText(m_strPath, &m_wndPath);
		
			//Upload files to analyze storage
			mainObdClass.uploadCars(GUIBridge::cStrToStr(m_strPath));

			SetPopulation();
		}
		//m_wsFilenames.clear();
		SAFE_DELETE(pFolderDlg);
	}
}


void CNODADlg::OnAnalyzeComparetwof()
{
	//CT2CA pszConvertedFirstStr(m_strPath);				// convert from CString to string
	//string pathFirst(pszConvertedFirstStr);
	//CT2CA pszConvertedFName(m_strName);
	//string nameFirst(pszConvertedFName);
	//if (pathFirst.empty())
	//{
	//	// if file is not chosen - lead out message about it and choose file or cancel operation
	//	//
	//	if (MessageBox(L"File is not chosen.\nPlease, press OK for choosing file or Cancel to cancel.",
	//		L"Warning", MB_ICONWARNING | MB_OKCANCEL) != IDCANCEL)
	//	{
	//		m_title = _T("Please, choose file");
	//		OnDataSelectfile();
	//		CT2CA pszConvertedFirstStr2(m_strPath);
	//		pathFirst = pszConvertedFirstStr2;
	//		CT2CA pszConvertedFName2(m_strName);
	//		nameFirst = pszConvertedFName2;
	//	}
	//	else
	//		return;
	//}
	//m_pOA->setNormalLogPath(pathFirst);

	//// select second file
	////
	//m_title = _T("Please, choose second file for comparison with first");
	//OnDataSelectfile();
	//CT2CA pszConvertedSecondStr(m_strPath);
	//string pathSecond(pszConvertedSecondStr);
	//CT2CA pszConvertedSName(m_strName);
	//string nameSecond(pszConvertedSName);				// read second file
	//m_pOA->setSecondFilePath(pathSecond);				// second file

	//m_pOA->analyzeWithTwoFiles();						// analysis between two files
	//string files = nameFirst + " & " + nameSecond;
	//m_strPath = "Analysis.log";
	//m_strName = files.c_str();
	//SetPopulation();									// output of analysis
	//m_strPath = m_strRememberPath;
	//m_title = _T("Files extension - *.noda;*.log;*.txt");

}


void CNODADlg::OnAnalyzeComparewithdb()
{
	CT2CA pszConvertedAnsiString(m_strPath);	// convert from CString to string
	string path(pszConvertedAnsiString);
	if (path.empty())
	{
		// if file is not chosen - lead out message about it and choose file or cancel operation
		//
		if (MessageBox(L"File is not chosen.\nPlease, press OK for choosing file or Cancel to cancel.",
			L"Warning", MB_ICONWARNING | MB_OKCANCEL) != IDCANCEL)
		{
			m_title = _T("Please, choose file");
			OnDataSelectfile();
			CT2CA pszConvertedFirstStr(m_strPath);
			path = pszConvertedFirstStr;
		}
		else
			return;
	}
	m_textCW.ShowWindow(SW_SHOW);
	m_ndTab.InsertItem(0, _T(""));
	m_ndTab.InsertItem(1, _T("Turn signal"));
	m_ndTab.InsertItem(2, _T("Brake"));
	m_ndTab.InsertItem(3, _T("Accelerator"));
	m_ndTab.InsertItem(4, _T("RPM"));
	m_ndTab.InsertItem(5, _T("Speed"));
	m_ndTab.InsertItem(6, _T("Steering wheel"));
	m_ndTab.DeleteItem(0);
}


void CNODADlg::OnSortShowall()
{
	ClearList();
	SetPopulation();
	//SetSortedData();
	//m_strName = m_strRememberName;
}


void CNODADlg::OnAnalyzeAnalyzecarparameters()
{
	CACPDlg acpDlg;
	acpDlg.setObdMainData(&mainObdClass, carIdToAnalyze);
	acpDlg.DoModal();
}


void CNODADlg::OnSortShownormal()
{
	vector<wstring> inter = m_wsFilenames;
	m_pSM->normal(inter);
	m_wsFilenames = m_pSM->getSortedWstr();
	m_wsNames = m_pSM->getFilename();
	m_wsID = m_pSM->getCarID();
	ClearList();
	SetPopulation();
	m_wsFilenames = m_rememberFilenames;
	m_wsNames = m_rememberNames;
	m_wsID = m_rememberID;
	m_pSM->clear();
}


void CNODADlg::OnSortShowturnsignal()
{
	vector<wstring> inter = m_wsFilenames;
	m_pSM->turnSignal(inter);
	m_wsFilenames = m_pSM->getSortedWstr();
	m_wsNames = m_pSM->getFilename();
	m_wsID = m_pSM->getCarID();
	ClearList();
	SetPopulation();
	m_wsFilenames = m_rememberFilenames;
	m_wsNames = m_rememberNames;
	m_wsID = m_rememberID;
	m_pSM->clear();
}


void CNODADlg::OnSortShowbrake()
{
	vector<wstring> inter = m_wsFilenames;
	m_pSM->brake(inter);
	m_wsFilenames = m_pSM->getSortedWstr();
	m_wsNames = m_pSM->getFilename();
	m_wsID = m_pSM->getCarID();
	ClearList();
	SetPopulation();
	m_wsFilenames = m_rememberFilenames;
	m_wsNames = m_rememberNames;
	m_wsID = m_rememberID;
	m_pSM->clear();
}


void CNODADlg::OnSortShowaccelerator()
{
	vector<wstring> inter = m_wsFilenames;
	m_pSM->accelerator(inter);
	m_wsFilenames = m_pSM->getSortedWstr();
	m_wsNames = m_pSM->getFilename();
	m_wsID = m_pSM->getCarID();
	ClearList();
	SetPopulation();
	m_wsFilenames = m_rememberFilenames;
	m_wsNames = m_rememberNames;
	m_wsID = m_rememberID;
	m_pSM->clear();
}


void CNODADlg::OnSortShowsteeringwheel()
{
	vector<wstring> inter = m_wsFilenames;
	m_pSM->steeringWheel(inter);
	m_wsFilenames = m_pSM->getSortedWstr();
	m_wsNames = m_pSM->getFilename();
	m_wsID = m_pSM->getCarID();
	ClearList();
	SetPopulation();
	m_wsFilenames = m_rememberFilenames;
	m_wsNames = m_rememberNames;
	m_wsID = m_rememberID;
	m_pSM->clear();
}


void CNODADlg::OnBnClickedSortPidButton2()
{
	if (m_editCarID.GetWindowTextLengthW() == 0)
	{
		MessageBox(L"Please, enter Car ID value.", L"No value", MB_OK);
		return;
	}

	CString id;
	m_editCarID.GetWindowText(id);						// get text from edit box
	CT2CA convid(id);									// convert
	string matchedID(convid);							// to string
	vector<wstring> inter = m_wsFilenames;
	m_pSM->sortByID(inter, matchedID);
	m_wsFilenames = m_pSM->getSortedWstr();
	m_wsNames = m_pSM->getFilename();
	m_wsID = m_pSM->getCarID();
	if (m_wsFilenames.empty())
	{
		wstring werr = L"No matching Car ID for " + m_gb.s2ws(matchedID) + L"\nPlease, check searching data.";
		MessageBox(werr.c_str(), L"Searching", MB_OK);
		return;
	}
	ClearList();
	SetPopulation();									// fill list
	m_wsFilenames = m_rememberFilenames;
	m_wsNames = m_rememberNames;
	m_wsID = m_rememberID;
}



void CNODADlg::OnEnChangeEditCarid()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	CString csText;
	GetDlgItemText(IDC_EDIT_CARID, csText);
	carIdToAnalyze = atoi(GUIBridge::cStrToStr(csText).c_str());

	// TODO:  Add your control notification handler code here
}
