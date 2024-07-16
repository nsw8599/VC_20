
#include "afxwin.h"
#include "afxcmn.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_CFOAQ10100.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_CFOAQ10100 dialog

class CDlg_CFOAQ10100 : public CDialog
{
	DECLARE_DYNCREATE(CDlg_CFOAQ10100)
	// Construction
public:
	CDlg_CFOAQ10100(CWnd* pParent = NULL);   // standard constructor

										// Dialog Data
										//{{AFX_DATA(CDlg_CFOAQ10100)
	enum { IDD = IDD_CFOAQ10100 };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_CFOAQ10100)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
														//}}AFX_VIRTUAL

														// Implementation
protected:
	void				InitCtrls();
	void				RequestData(BOOL bNext = FALSE);
	//void				Request0167(BOOL bNext = FALSE);

	// Generated message map functions
	//{{AFX_MSG(CDlg_CFOAQ10100)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg void		OnButtonRequest();
	afx_msg void OnBnClickedButtonRequestNext();
	afx_msg	LRESULT		OnXMReceiveData(WPARAM wParam, LPARAM lParam);
	afx_msg	LRESULT		OnXMTimeoutData(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	CString m_RecCnt;
	CString m_AcntNo;
	CString m_Pwd;
	CString m_QryTp;
	CString m_OrdAmt;
	CString m_RatVal;
	CString m_BnsTpCode;
	CString m_FnoOrdprcPtnCode;
	CEdit m_code;
	CEdit m_price;
	CListCtrl m_ctrlOutBlock1;
	CListCtrl m_ctrlOutBlock2;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
