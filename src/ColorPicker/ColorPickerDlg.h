
// ColorPickerDlg.h : header file
//

#pragma once
#include "colorstatic.h"

#include "MagnifierDlg.h"

// CColorPickerDlg dialog
class CColorPickerDlg : public CDialog
{
// Construction
public:
	CColorPickerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_COLORPICKER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON   m_hIcon;
    ATOM    m_HotKey;
    BOOL    m_bPicking;
    CMagnifierDlg   m_MagnifierDlg;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    CColorStatic m_ColorStatic;
    afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
    afx_msg void OnEnSetfocusEditDecimal();
    afx_msg void OnEnSetfocusEditHex();
    afx_msg void OnMove(int x, int y);
    afx_msg void OnStnClickedColor();
};
