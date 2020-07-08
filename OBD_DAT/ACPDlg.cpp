/*
** Author: Ivan Chapkailo
** Modidfied by: Artem Bordiuh
**
** Date:   23.08.2017
**
** 2017 © Ivan Chapkailo for Avtonomic
**
** Updated 23.08.2017: Added new dialog. Implemented edit box and 'next' button. Added functions to fill list
**/

// ACPDlg.cpp : implementation file
//

#include "stdafx.h"
#include "OBD_DAT.h"
#include "ACPDlg.h"
#include "afxdialogex.h"
#include "GUIBridge.h"
#include "MessageDlg.h"
#include <string>
#include <sstream>
#include <vector>
#include <iterator>


// CACPDlg dialog

IMPLEMENT_DYNAMIC(CACPDlg, CDialogEx)

CACPDlg::CACPDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ACP_DLG, pParent)
{
	m_counter = 0;
}

CACPDlg::~CACPDlg()
{
}

void CACPDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_PARAMTYPE, m_editParameterType);
	DDX_Control(pDX, IDC_LIST_ACP, m_ListACP);
	DDX_Control(pDX, IDC_EDIT_MIN_VAL, m_editMinVal);
	DDX_Control(pDX, IDC_EDIT_MAX_VAL, m_editMaxVal);
}


BEGIN_MESSAGE_MAP(CACPDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CACPDlg::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_SKIP, &CACPDlg::OnBnClickedButtonSkip)
	ON_BN_CLICKED(IDC_BUTTON_ANALYZE, &CACPDlg::OnBnClickedButtonAnalyze)
	ON_BN_CLICKED(IDCANCEL, &CACPDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

BOOL CACPDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	AnalyzeInfo info;
	SetColumns();


	if (obdMain != NULL && obdMain->startNewAnalyze(carIdToAnalyze) != OBDM_ERROR) {
		++m_counter;
		OnBnClickedButtonNext();
	}
	else {
		++m_counter;
		++m_counter;
		CMessageDlg msg(L"Error message. Error when analyzing car!", L"Error analyzing car");
		msg.DoModal();
		CDialogEx::OnCancel();
		return TRUE;
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

// CACPDlg message handlers

void CACPDlg::SetColumns()
{
	// Setting of columns inside list control
	//
	m_lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt = LVCFMT_LEFT;
	m_lvColumn.cx = 150;
	m_lvColumn.pszText = L"PID Candidate";
	m_ListACP.InsertColumn(0, &m_lvColumn);

	m_lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt = LVCFMT_LEFT;
	m_lvColumn.cx = 120;
	m_lvColumn.pszText = L"Dismatched/Matched";
	m_ListACP.InsertColumn(1, &m_lvColumn);

	m_lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt = LVCFMT_LEFT;
	m_lvColumn.cx = 350;
	m_lvColumn.pszText = L" Value Normal / Value Triggered";
	m_ListACP.InsertColumn(2, &m_lvColumn);

	m_lvColumn.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	m_lvColumn.fmt = LVCFMT_LEFT;
	m_lvColumn.cx = 150;
	m_lvColumn.pszText = L"Probability";
	m_ListACP.InsertColumn(3, &m_lvColumn);
}

void CACPDlg::WriteColumn(string pid_can, string matchdismatch, string values, string probability) {
	
	wstring tmp = GUIBridge::s2ws(pid_can);

	m_lvItem.mask = LVIF_TEXT;
	m_lvItem.iItem = 0;
	m_lvItem.iSubItem = 0;
	m_lvItem.pszText = (LPWSTR)(LPCTSTR)&tmp[0];
	m_nItem = m_ListACP.InsertItem(&m_lvItem);
	
	tmp = GUIBridge::s2ws(matchdismatch);
	m_ListACP.SetItemText(m_nItem, 1, &tmp[0]);
	tmp = GUIBridge::s2ws(values);
	m_ListACP.SetItemText(m_nItem, 2, &tmp[0]);
	tmp = GUIBridge::s2ws(probability);
	m_ListACP.SetItemText(m_nItem, 3, &tmp[0]);
}

void CACPDlg::deleteListItems() {
	int nCount = m_ListACP.GetItemCount();

	// Delete all of the items from the list view contr6ol.
	for (int i = 0; i < nCount; i++)
	{
		m_ListACP.DeleteItem(0);
	}
}

std::vector<std::string> split(const std::string &s, char delim) {
	
	std::istringstream ss(s);
	std::string token;


	vector<string> vectorstr;
	while (std::getline(ss, token, delim)) {
		vectorstr.push_back(token);
	}
	return vectorstr;
}

void CACPDlg::OnBnClickedButtonNext()
{
	AnalyzeInfo analyzeInfoToShow;
	static ObdInfoMessage oim = OBDM_OK;

	if (m_counter == 1)
	{
		
		if (oim != OBDM_ERROR && oim != OBDM_FINISHED && oim != OBDM_NO_SUCH_A_CAR_ID) {
			oim = obdMain->analyzeNext(analyzeInfoToShow, -1, -1);
		wstring tmp = GUIBridge::s2ws(analyzeInfoToShow.parameterName) + L" - " + GUIBridge::s2ws(analyzeInfoToShow.carId);
			m_editParameterType.SetWindowTextW(&tmp[0]);
			
			deleteListItems();
			
			for (size_t i = 0; i < analyzeInfoToShow.data.size(); i++) {
				vector<string> tokens = split(analyzeInfoToShow.data.at(i), '\t');

				if (tokens.size() >= 4)
					WriteColumn(tokens.at(0).c_str(), tokens.at(1).c_str(), tokens.at(2).c_str(), tokens.at(3).c_str());
			}
		}
		else
			CDialogEx::OnCancel();
	}
}


void CACPDlg::OnBnClickedButtonSkip()
{
	// write here description for 'Skip' button
}


void CACPDlg::OnBnClickedButtonAnalyze()
{
	// write here description for 'Analyze' button
}


void CACPDlg::OnBnClickedCancel()
{
	// this is 'Cancel' button
	CDialogEx::OnCancel();
}

void CACPDlg::setObdMainData(ObdMainClass *pObdMainData, unsigned int carId) {
	obdMain = pObdMainData;
	carIdToAnalyze = carId;
}
