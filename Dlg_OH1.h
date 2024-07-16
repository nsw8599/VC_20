#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "afxcmn.h"
#include "afxwin.h"


// CDlg_OH1 dialog

class CDlg_OH1 : public CDialog
{
	DECLARE_DYNCREATE(CDlg_OH1)

public:
	CDlg_OH1(CWnd* pParent = NULL);
	enum { IDD = IDD_OH1 };
	CString				m_strCode;
	CListCtrl			m_ctrlOutBlock;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
														// Implementation
protected:
	void				InitCtrls();
	void				AdviseOH0(CString strCode);
	void				UnadviseOH0(CString strCode);
	afx_msg	LRESULT	OnXMReceiveRealOH0(WPARAM wParam, LPARAM lParam);
	// Generated message map functions
	//{{AFX_MSG(CDlg_OH1)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg void OnDestroy();
	afx_msg void OnButtonRequest();
	DECLARE_MESSAGE_MAP()

public:
	CEdit m_code;
	afx_msg void OnBnClickedButtonRequest24();
};
