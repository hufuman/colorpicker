
// ColorPickerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ColorPicker.h"
#include "ColorPickerDlg.h"

#include "LinkStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
    virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()

    CLinkStatic m_LinkAuthor;
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

BOOL CAboutDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_LinkAuthor.SubclassWindow(GetDlgItem(IDC_LINK_AUTHOR)->GetSafeHwnd());
    m_LinkAuthor.SetLink(_T("https://github.com/hufuman"));

    return TRUE;
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CColorPickerDlg dialog




CColorPickerDlg::CColorPickerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorPickerDlg::IDD, pParent)
{
    m_bPicking = TRUE;
    m_HotKey = 0;
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CColorPickerDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_COLOR, m_ColorStatic);
}

BEGIN_MESSAGE_MAP(CColorPickerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_WM_TIMER()
    ON_WM_HOTKEY()
    ON_EN_SETFOCUS(IDC_EDIT_DECIMAL, &CColorPickerDlg::OnEnSetfocusEditDecimal)
    ON_EN_SETFOCUS(IDC_EDIT_HEX, &CColorPickerDlg::OnEnSetfocusEditHex)
    ON_WM_MOVE()
    ON_STN_CLICKED(IDC_COLOR, &CColorPickerDlg::OnStnClickedColor)
END_MESSAGE_MAP()


// CColorPickerDlg message handlers

BOOL CColorPickerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
    SetTimer(100, 100, NULL);
    m_HotKey = ::GlobalAddAtom(_T("ColorPickerHotKey"));
    ::RegisterHotKey(m_hWnd, m_HotKey, MOD_CONTROL, L'1');

    m_MagnifierDlg.Create(IDD_MAGNIFIERDLG, this);
    m_MagnifierDlg.ShowWindow(SW_SHOW);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CColorPickerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CColorPickerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CColorPickerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CColorPickerDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: Add your message handler code here and/or call default
    BOOL bControlPressed = (::GetAsyncKeyState(VK_CONTROL) & 0x80000000);
    CStatic* pPickingTag = (CStatic*)GetDlgItem(IDC_PICKING_TAG);
    pPickingTag->ModifyStyle(bControlPressed ? SS_GRAYRECT : SS_WHITERECT, bControlPressed ? SS_WHITERECT : SS_GRAYRECT, 0);
    pPickingTag->Invalidate();

    if(!m_bPicking)
        return;

    POINT Pt = {0};
    ::GetCursorPos(&Pt);

    HWND hWnd = ::WindowFromPoint(Pt);
    if(hWnd == m_hWnd || ::GetParent(hWnd) == m_hWnd)
        return;

    HDC hScreenDC = ::GetDC(NULL);
    COLORREF clrPixel = ::GetPixel(hScreenDC, Pt.x, Pt.y);

    m_ColorStatic.SetColor(clrPixel);

    SetDlgItemInt(IDC_EDIT_X, Pt.x, FALSE);
    SetDlgItemInt(IDC_EDIT_Y, Pt.y, FALSE);

    CString strTemp;

    strTemp.Format(_T("RGB(%d, %d, %d)"), GetRValue(clrPixel), GetGValue(clrPixel), GetBValue(clrPixel));
    SetDlgItemText(IDC_EDIT_DECIMAL, strTemp);
    strTemp.Format(_T("RGB(0x%02X, 0x%02X, 0x%02X)"), GetRValue(clrPixel), GetGValue(clrPixel), GetBValue(clrPixel));
    SetDlgItemText(IDC_EDIT_HEX, strTemp);

    ::ReleaseDC(NULL, hScreenDC);
    CDialog::OnTimer(nIDEvent);
}

void CColorPickerDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
    if(m_HotKey == nHotKeyId)
    {
        m_bPicking = !m_bPicking;
        m_ColorStatic.SetPicking(m_bPicking);
        m_ColorStatic.Invalidate();
    }
    CDialog::OnHotKey(nHotKeyId, nKey1, nKey2);
}

void CColorPickerDlg::OnEnSetfocusEditDecimal()
{
    ::PostMessage(::GetDlgItem(m_hWnd, IDC_EDIT_DECIMAL), EM_SETSEL, 0, -1);
}

void CColorPickerDlg::OnEnSetfocusEditHex()
{
    ::PostMessage(::GetDlgItem(m_hWnd, IDC_EDIT_HEX), EM_SETSEL, 0, -1);
}

void CColorPickerDlg::OnMove(int x, int y)
{
    CDialog::OnMove(x, y);

    if(m_MagnifierDlg.m_hWnd != NULL)
    {
        RECT rcWnd;
        GetWindowRect(&rcWnd);
        m_MagnifierDlg.SetWindowPos(&wndTopMost, rcWnd.right + 1, rcWnd.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
    }
}

void CColorPickerDlg::OnStnClickedColor()
{
    m_MagnifierDlg.ShowWindow(m_MagnifierDlg.IsWindowVisible() ? SW_HIDE : SW_SHOW);
}
