
#include "afxwin.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_CEXAQ21200.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlg_CEXAQ21200 dialog

class CDlg_CEXAQ21200 : public CDialog
{
	DECLARE_DYNCREATE(CDlg_CEXAQ21200)
	// Construction
public:
	CDlg_CEXAQ21200(CWnd* pParent = NULL);   // standard constructor

											 // Dialog Data
											 //{{AFX_DATA(CDlg_CEXAQ21200)
	enum { IDD = IDD_CEXAQ21200 };
	// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlg_CEXAQ21200)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
														//}}AFX_VIRTUAL

														// Implementation
protected:
	void				InitCtrls();
	void				RequestData(BOOL bNext = FALSE);
	//void				Request0167(BOOL bNext = FALSE);

	// Generated message map functions
	//{{AFX_MSG(CDlg_CEXAQ21200)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg void		OnButtonRequest();
	afx_msg void		OnButtonRequestNext();
	afx_msg	LRESULT		OnXMReceiveData(WPARAM wParam, LPARAM lParam);
	afx_msg	LRESULT		OnXMTimeoutData(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_RecCnt;
	CString m_AcntNo;
	CString m_Pwd;
	CString m_QryTp;
	CString m_OrdAmt;
	CString m_RatVal;
	CString m_BnsTpCode;
	CString m_ErxPrcCndiTpCode;
	CEdit m_code;
	CEdit m_price;
};
