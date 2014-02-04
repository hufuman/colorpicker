#pragma once


// CMagnifierDlg dialog

class CMagnifierDlg : public CDialog
{
	DECLARE_DYNAMIC(CMagnifierDlg)

public:
	CMagnifierDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMagnifierDlg();

// Dialog Data
	enum { IDD = IDD_MAGNIFIERDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    virtual BOOL OnInitDialog();
    afx_msg void OnPaint();
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};
