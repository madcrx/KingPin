#if !defined(AFX_DLGPLAYERNAME_H__F2D95D67_B1BF_4078_A6A2_06BFEE28E805__INCLUDED_)
#define AFX_DLGPLAYERNAME_H__F2D95D67_B1BF_4078_A6A2_06BFEE28E805__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgPlayerName.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPlayerName dialog

class CDlgPlayerName : public CDialog
{
// Construction
public:
	CDlgPlayerName(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPlayerName)
	enum { IDD = IDD_DIALOG_PLAYER_NAME };
	CString	m_Name;
	CString	m_Rank;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPlayerName)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPlayerName)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPLAYERNAME_H__F2D95D67_B1BF_4078_A6A2_06BFEE28E805__INCLUDED_)
