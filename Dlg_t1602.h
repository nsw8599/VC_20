#include "afxwin.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_t1602.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_t1602 dialog

class CDlg_t1602 : public CDialog
{
	DECLARE_DYNCREATE(CDlg_t1602)
	// Construction
public:
	CDlg_t1602(CWnd* pParent = NULL);   // standard constructor

										// Dialog Data
										//{{AFX_DATA(CDlg_t1602)
	enum { IDD = IDD_t1602 };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_t1602)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
														//}}AFX_VIRTUAL

														// Implementation
protected:
	CListCtrl			m_ctrlOutBlock;
	CListCtrl			m_ctrlOutBlock1;
	void				InitCtrls();
	void				Request1602(BOOL bNext = FALSE);

	// Generated message map functions
	//{{AFX_MSG(CDlg_t1602)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg void		OnButtonRequest();
	afx_msg void		OnButtonRequestNext();
	afx_msg	LRESULT		OnXMReceive1602(WPARAM wParam, LPARAM lParam);
	afx_msg	LRESULT		OnXMTimeout1602(WPARAM wParam, LPARAM lParam);
	void ExportToCSVFile(const CListCtrl *plistctrlContent, BOOL bIncludeHeaderNames, char cDelimiter);
	CString GetColumnName(const CListCtrl * listctrl, int iCol);
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_cts;
	afx_msg void OnBnClickedButtonSave();
	long *arr1;
	long *arr2;
	afx_msg void OnDestroy();
};