#if !defined(AFX_DLGSCORES_H__42BC49DB_C132_485D_9ACD_069DC9066904__INCLUDED_)
#define AFX_DLGSCORES_H__42BC49DB_C132_485D_9ACD_069DC9066904__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgScores.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgScores dialog

class CDlgScores : public CDialog
{
// Construction
public:
	CDlgScores(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgScores)
	enum { IDD = IDD_DIALOG_HISCORES };
	CListCtrl	m_ScoresCtrl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgScores)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgScores)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonClear();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSCORES_H__42BC49DB_C132_485D_9ACD_069DC9066904__INCLUDED_)
