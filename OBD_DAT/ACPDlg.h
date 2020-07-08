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

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "afxbutton.h"
#include "ObdMainClass.h"

// CACPDlg dialog

class CACPDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CACPDlg)

public:
	CACPDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CACPDlg();
	void setObdMainData(ObdMainClass *pObdMainData, unsigned int carId);

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ACP_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

protected:
	void SetColumns();
	void CACPDlg::WriteColumn(string pid_can, string matchdismatch, string values, string probability);
	ObdMainClass *obdMain;
	unsigned int carIdToAnalyze;

private:
	CEdit m_editParameterType;	// control for edit box of types (left upper corner on dialog)
	CEdit m_editMinVal;			// control for edit box for min value
	CEdit m_editMaxVal;			// control for edit box of max value

	void deleteListItems();

	// list control
	//
	LVCOLUMN m_lvColumn;
	LVITEM m_lvItem;
	int m_nItem;
	CListCtrl m_ListACP;		// list control (look how to use it in SetPopulation() funtion in NODADlg.cpp - m_ListNODA there)
	
	unsigned int m_counter;

public:
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedButtonSkip();
	afx_msg void OnBnClickedButtonAnalyze();
	afx_msg void OnBnClickedCancel();
};
