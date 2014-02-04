// LinkStatic.cpp : implementation file
//

#include "stdafx.h"
#include "LinkStatic.h"


// CLinkStatic

IMPLEMENT_DYNAMIC(CLinkStatic, CStatic)

CLinkStatic::CLinkStatic()
{
    m_hCursor = LoadCursor(NULL, MAKEINTRESOURCE(IDC_HAND));
}

CLinkStatic::~CLinkStatic()
{
    if(m_hCursor != NULL)
    {
        DestroyCursor(m_hCursor);
        m_hCursor = NULL;
    }
}

void CLinkStatic::SetLink(LPCTSTR szLink)
{
    m_strLink = szLink;
}

BEGIN_MESSAGE_MAP(CLinkStatic, CStatic)
    ON_WM_SETCURSOR()
    ON_WM_CTLCOLOR_REFLECT()
    ON_WM_LBUTTONUP()
END_MESSAGE_MAP()



// CLinkStatic message handlers



BOOL CLinkStatic::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
    if(m_hCursor != NULL)
    {
        ::SetCursor(m_hCursor);
        return TRUE;
    }

    return CStatic::OnSetCursor(pWnd, nHitTest, message);
}

HBRUSH CLinkStatic::CtlColor(CDC* pDC, UINT /*nCtlColor*/)
{
    pDC->SetTextColor(RGB(0, 0, 255));
    pDC->SetBkMode(TRANSPARENT);
    return (HBRUSH)GetStockObject(NULL_BRUSH);
}

void CLinkStatic::PreSubclassWindow()
{
    // TODO: Add your specialized code here and/or call the base class
    CStatic::PreSubclassWindow();
    ModifyStyle(0, SS_NOTIFY, 0);

    CFont* pFont = GetFont();

    LOGFONT LogFont = {0};
    pFont->GetLogFont(&LogFont);

    LogFont.lfUnderline = TRUE;
    m_Font.CreateFontIndirect(&LogFont);
    SetFont(&m_Font);
}

void CLinkStatic::OnLButtonUp(UINT nFlags, CPoint point)
{
    if(m_strLink.GetLength() > 0)
        ShellExecute(NULL, _T("open"), m_strLink, NULL, NULL, SW_SHOW);

    CStatic::OnLButtonUp(nFlags, point);
}
