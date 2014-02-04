#pragma once


// CLinkStatic

class CLinkStatic : public CStatic
{
	DECLARE_DYNAMIC(CLinkStatic)

public:
	CLinkStatic();
	virtual ~CLinkStatic();

    void SetLink(LPCTSTR szLink);

protected:
	DECLARE_MESSAGE_MAP()

    CString     m_strLink;
    HCURSOR     m_hCursor;
    CFont       m_Font;

public:
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT /*nCtlColor*/);
protected:
    virtual void PreSubclassWindow();
public:
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


