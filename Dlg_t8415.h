
#include "afxwin.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Dlg_t8415.h : header file

class CDlg_t8415 : public CDialog
{
	DECLARE_DYNCREATE(CDlg_t8415)
public:
	CDlg_t8415(CWnd* pParent = NULL);
	enum { IDD = IDD_t8415 };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
protected:
	void				Request8415(BOOL bNext = FALSE);
	void				Receive8415(LPRECV_PACKET pRpData);
	virtual BOOL		OnInitDialog();
	afx_msg void		OnDestroy();
	afx_msg void		OnButtonRequest();
	afx_msg	LRESULT		OnXMReceiveData(WPARAM wParam, LPARAM lParam);
	afx_msg	LRESULT		OnXMTimeoutData(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()

public:
	int ID8415;
	CString *arrs1;
	CString *arrs2;
	float *arr1;
	float *arr2;
	float *arr3;
	long *arr4;
	float *arr5;
	float *arr6;
	float *arr7;
	float *arr8;
	float *arr9;
	float *arr10;
	long *arra;
	long *arrb;
};
