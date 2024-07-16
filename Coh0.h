#pragma once


// Coh0

class Coh0 : public CWnd
{
	DECLARE_DYNAMIC(Coh0)

public:
	Coh0();
	virtual ~Coh0();

protected:
	CString				m_strCode;
	void				AdviseOH0();
	void				UnadviseOH0();
	afx_msg	LRESULT		OnXMReceiveRealOH0(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};


