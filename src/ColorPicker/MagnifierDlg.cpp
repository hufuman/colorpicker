// MagnifierDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ColorPicker.h"
#include "MagnifierDlg.h"


// CMagnifierDlg dialog

IMPLEMENT_DYNAMIC(CMagnifierDlg, CDialog)

CMagnifierDlg::CMagnifierDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMagnifierDlg::IDD, pParent)
{
    m_nRatio = 2;
}

CMagnifierDlg::~CMagnifierDlg()
{
}

void CMagnifierDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMagnifierDlg, CDialog)
    ON_WM_TIMER()
    ON_WM_PAINT()
    ON_WM_ERASEBKGND()
    ON_WM_KEYUP()
END_MESSAGE_MAP()


// CMagnifierDlg message handlers

void CMagnifierDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: Add your message handler code here and/or call default
    Invalidate();

    CDialog::OnTimer(nIDEvent);
}

BOOL CMagnifierDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  Add extra initialization here
    SetTimer(100, 100, NULL);

    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CMagnifierDlg::OnPaint()
{
    CPaintDC dc(this);

    RECT rcClient;
    GetClientRect(&rcClient);

    POINT Pt;
    ::GetCursorPos(&Pt);

    HDC hScreenDC = ::GetDC(NULL);

    if(m_nRatio >= 0)
    {
        int ratio = m_nRatio == 0 ? 1 : m_nRatio;
        ::StretchBlt(dc,
            0, 0,
            rcClient.right, rcClient.bottom,
            hScreenDC,
            Pt.x - rcClient.right / ratio / 2, Pt.y - rcClient.bottom / ratio / 2,
            rcClient.right / ratio, rcClient.bottom / ratio,
            SRCCOPY);
    }
    else
    {
        int ratio = m_nRatio == 0 ? 1 : - m_nRatio;
        ::StretchBlt(dc,
            0, 0,
            rcClient.right, rcClient.bottom,
            hScreenDC,
            Pt.x - rcClient.right * ratio / 2, Pt.y - rcClient.bottom * ratio / 2,
            rcClient.right * ratio, rcClient.bottom * ratio,
            SRCCOPY);
    }

    CURSORINFO Cursorinfo = {sizeof(Cursorinfo)};
    if(::GetCursorInfo(&Cursorinfo) && Cursorinfo.flags == CURSOR_SHOWING && Cursorinfo.hCursor != NULL)
    {
        ICONINFO Iconinfo = {0};
        ::GetIconInfo((HICON)Cursorinfo.hCursor, &Iconinfo);
        ::DrawIcon(dc, rcClient.right / 2 - Iconinfo.xHotspot, rcClient.bottom / 2 - Iconinfo.yHotspot, Cursorinfo.hCursor);
        ::DeleteObject(Iconinfo.hbmColor);
        ::DeleteObject(Iconinfo.hbmMask);
    }

    ::ReleaseDC(NULL, hScreenDC);
}

BOOL CMagnifierDlg::OnEraseBkgnd(CDC* pDC)
{
    return NULL;
}

void CMagnifierDlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
    if(nChar == VK_OEM_PLUS || nChar == VK_ADD)
    {
        ++ m_nRatio;
        if(m_nRatio == 0)
            m_nRatio = 2;
    }
    else if(nChar == VK_OEM_MINUS || nChar == VK_SUBTRACT)
    {
        -- m_nRatio;
        if(m_nRatio == 0)
            m_nRatio = -2;
    }
    CDialog::OnKeyUp(nChar, nRepCnt, nFlags);
}
