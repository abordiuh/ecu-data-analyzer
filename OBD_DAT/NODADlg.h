/*
** Author: Ivan Chapkailo
** Date:   05.08.2017
**
** 2017 © Ivan Chapkailo for Avtonomic
**
** Updated 08.08.2017: Implemented file reading
** Updated 10.08.2017: Linked with MainDataClass and created SortMethods instance
**					   and calling sorting functions by clicking 'Sort by PID' button
** Updated 14.08.2017: Fixed displaying of data after sorting and optimized some functions and code
** Updated 15.08.2017: Changed sorting algorithm and reading logic. Added analyzer instance
**					   Added intermediate vars for remembering path and name
** Updated 16.08.2017: Implemented Analyse with New fully. Implemented Analysis with Two Files. Optimized code
** Updated 22.08.2017: Added parameter info. Implemented "Input data" chapter from new requirements
** Updated 23.08.2017: Changed architecture and logic. Added menu and new dialog
** Updated 25.08.2017: Implemented Sort -> Normal. Optimized. UPD: Added all sorting methods (normal/brake/.../steering wheel)
** Updated 01.09.2017: Optimized. Added controls for sorting and edit boxes.
**/

#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "FolderDlg.h"
#include "FilteredFolderDlg.h"
#include "MainDataClass.h"
#include "GUIBridge.h"
#include "ACPDlg.h"
#include "MessageDlg.h"
#include "ObdMainClass.h"

// CNODADlg dialog

class CNODADlg : public CDialogEx
{
	DECLARE_DYNAMIC(CNODADlg)

public:
	CNODADlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNODADlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NOD_ANALYSIS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	BOOL CreateToolTips();

	void SetColumns();									// sets columns in list control
	void SetPopulation();								// fills list
	void ClearList();									// clears list by num of rows
	void SetSortedData();
	void analyzeWithNew(int sel);

private:
	// list control
	//
	LVCOLUMN m_lvColumn;
	LVITEM m_lvItem;
	int m_nItem;
	CListCtrl m_ListNODA;

	// button control
	//
	CTabCtrl m_ndTab;			// tab control

	// select folder control
	//
	CString	m_strName;
	CString m_strPath;
	CString	m_strFilter;
	CString m_strRememberPath;
	CString m_strRememberName;
	CString m_smFilename;
	CString m_prevStrPath;
	
	CToolTipCtrl* m_pToolTip;
	
	// edit control
	//
	CEdit m_wndPath;		// path edit box control
	CEdit m_wndRoot;		// root path
	CEdit m_editPID;		// control for PID edit box
	CEdit m_editCarID;		// control for car ID edit box

	// other
	//
	size_t m_rowNumber;

	BOOL m_bSorted;
	BOOL m_canClear;
	BOOL m_bFilter;

	LPCTSTR m_title;
	wstring m_carID;
	CLinkCtrl m_textCW;

	// containers
	//
	vector<wstring> m_wsFilenames, m_rememberFilenames;
	vector<wstring> m_wsNames, m_rememberNames;
	vector<wstring> m_wsID, m_rememberID;

	multimap<string, string> m_mapCarPID;
	vector<string> m_vCarID;

	HICON m_hIcon;

	// objects
	GUIBridge m_gb;
	MainDataClass m_mdc;
	SortMethods* m_pSM;
	OBDAnalyzer* m_pOA;
	OBDFileReader* m_pOFR;
	
	ObdMainClass mainObdClass;
	int carIdToAnalyze;
	

public:
	afx_msg void OnBnClickedBacknoda();
	afx_msg void OnLvnItemchangedStoreItemsNoda(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedSortPidButton();
	afx_msg void OnTcnSelchangeNdTab(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMoreAbout();
	afx_msg void OnDataExit();
	afx_msg void OnDataSelectfile();
	afx_msg void OnDataSelectfolder();
	afx_msg void OnAnalyzeComparetwof();
	afx_msg void OnAnalyzeComparewithdb();
	afx_msg void OnSortShowall();
	afx_msg void OnAnalyzeAnalyzecarparameters();
	afx_msg void OnSortShownormal();
	afx_msg void OnSortShowturnsignal();
	afx_msg void OnSortShowbrake();
	afx_msg void OnSortShowaccelerator();
	afx_msg void OnSortShowsteeringwheel();
	afx_msg void OnBnClickedSortPidButton2();

	afx_msg void OnEnChangeEditCarid();
};
