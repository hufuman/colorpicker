#pragma once


// CColorStatic

class CColorStatic : public CStatic
{
	DECLARE_DYNAMIC(CColorStatic)

public:
	CColorStatic();
	virtual ~CColorStatic();

    void SetPicking(BOOL bPicking);
    void SetColor(COLORREF clrBrush);

protected:
	DECLARE_MESSAGE_MAP()

public:
    virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

private:
    COLORREF    m_clrBrush;
    HBRUSH      m_hBrush;
    BOOL        m_bPicking;
protected:
    virtual void PreSubclassWindow();
};


