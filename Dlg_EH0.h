#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "afxcmn.h"
#include "afxwin.h"


// CDlg_EH0 dialog

class CDlg_EH0 : public CDialog
{
	DECLARE_DYNCREATE(CDlg_EH0)

public:
	CDlg_EH0(CWnd* pParent = NULL);
	enum { IDD = IDD_EH0 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
														// Implementation
protected:
	CString				m_strCode;
	CListCtrl			m_ctrlOutBlock;
	void				InitCtrls();
	void				AdviseEH0();
	void				UnadviseEH0();

	// Generated message map functions
	//{{AFX_MSG(CDlg_EH0)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	afx_msg void OnDestroy();
	afx_msg void OnButtonRequest();
	afx_msg	LRESULT	OnXMReceiveRealEH0(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	CEdit m_code;
};
