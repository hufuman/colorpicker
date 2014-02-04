// ColorStatic.cpp : implementation file
//

#include "stdafx.h"
#include "ColorPicker.h"
#include "ColorStatic.h"


// CColorStatic

IMPLEMENT_DYNAMIC(CColorStatic, CStatic)

CColorStatic::CColorStatic()
{
    m_bPicking = TRUE;
    m_clrBrush = RGB(0xEE, 0xEE, 0xEE);
    m_hBrush = ::CreateSolidBrush(m_clrBrush);
}

CColorStatic::~CColorStatic()
{
}


BEGIN_MESSAGE_MAP(CColorStatic, CStatic)
END_MESSAGE_MAP()



// CColorStatic message handlers

void CColorStatic::SetColor(COLORREF clrBrush)
{
    if(m_clrBrush != clrBrush)
    {
        ::DeleteObject(m_hBrush);
        m_clrBrush = clrBrush;
        m_hBrush = ::CreateSolidBrush(m_clrBrush);
        Invalidate();
    }
}

void CColorStatic::SetPicking(BOOL bPicking)
{
    if((!!m_bPicking) != (!!bPicking))
    {
        m_bPicking = bPicking;
        Invalidate();
    }
}

void CColorStatic::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    RECT rcClient;
    GetClientRect(&rcClient);
    ::FillRect(lpDrawItemStruct->hDC, &rcClient, m_hBrush);

    ::SetBkMode(lpDrawItemStruct->hDC, TRANSPARENT);
    LPCTSTR szText = m_bPicking ? _T("Picking") : _T("Stopped");
    ::DrawText(lpDrawItemStruct->hDC, szText, _tcslen(szText), &rcClient, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
}

void CColorStatic::PreSubclassWindow()
{
    // TODO: Add your specialized code here and/or call the base class

    ModifyStyle(0, SS_OWNERDRAW);
    CStatic::PreSubclassWindow();
}
