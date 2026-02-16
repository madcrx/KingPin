#if !defined(AFX_DLGNEWGAME_H__158A9D38_F338_428A_8D64_BB84E2B7E6F9__INCLUDED_)
#define AFX_DLGNEWGAME_H__158A9D38_F338_428A_8D64_BB84E2B7E6F9__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgNewGame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgNewGame dialog

class CDlgNewGame : public CDialog
{
// Construction
public:
	CDlgNewGame(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgNewGame)
	enum { IDD = IDD_DIALOG_NEW_GAME };
	CButton	m_CancelCtrl;
	CListBox	m_DistrictsCtrl;
	//}}AFX_DATA

  BOOL m_bShowExit;
  int m_nLocation;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgNewGame)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgNewGame)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGNEWGAME_H__158A9D38_F338_428A_8D64_BB84E2B7E6F9__INCLUDED_)
