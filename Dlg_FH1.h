#pragma once
#include "afxcmn.h"


// CDlg_FH1 dialog

class CDlg_FH1 : public CDialog
{
	DECLARE_DYNAMIC(CDlg_FH1)

public:
	CDlg_FH1(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDlg_FH1();

// Dialog Data
	enum { IDD = IDD_FH1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
														// Implementation
protected:
	CListCtrl m_ctrlOutBlock;
	CString m_strCode;
	void				InitCtrls();
	void				AdviseData();
	void				UnadviseData();

	// Generated message map functions
	//{{AFX_MSG(CDlg_FC0)
	virtual BOOL OnInitDialog();

	//}}AFX_MSG
	//	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonRequest();
	afx_msg	LRESULT	OnXMReceiveRealData(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

};
