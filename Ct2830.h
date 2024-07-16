#pragma once


// Ct2830

class Ct2830 : public CWnd
{
	DECLARE_DYNAMIC(Ct2830)

public:
	Ct2830();
	virtual ~Ct2830();

protected:
	DECLARE_MESSAGE_MAP()
	void				RequestData(BOOL bNext = FALSE);
	afx_msg	LRESULT		OnXMReceiveData(WPARAM wParam, LPARAM lParam);
	afx_msg	LRESULT		OnXMTimeoutData(WPARAM wParam, LPARAM lParam);
};


