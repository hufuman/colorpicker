// MagnifierDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ColorPicker.h"
#include "MagnifierDlg.h"


// CMagnifierDlg dialog

static const int g_Ratio = 2;

IMPLEMENT_DYNAMIC(CMagnifierDlg, CDialog)

CMagnifierDlg::CMagnifierDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMagnifierDlg::IDD, pParent)
{

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
END_MESSAGE_MAP()


// CMagnifierDlg message handlers

void CMagnifierDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: Add your message handler code here and/or call default

    RECT rcClient;
    GetClientRect(&rcClient);

    RECT rcSrc = rcClient;
    rcSrc.right /= g_Ratio;
    rcSrc.bottom /= g_Ratio;

    POINT Pt;
    ::GetCursorPos(&Pt);
    ::OffsetRect(&rcSrc, Pt.x - rcSrc.right / 2, Pt.y - rcSrc.bottom / 2);

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

    ::StretchBlt(dc,
        0, 0,
        rcClient.right, rcClient.bottom,
        hScreenDC,
        Pt.x - rcClient.right / 4, Pt.y - rcClient.bottom / 4,
        rcClient.right / 2, rcClient.bottom / 2,
        SRCCOPY);

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
