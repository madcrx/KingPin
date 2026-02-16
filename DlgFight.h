#if !defined(AFX_DLGFIGHT_H__75CB374F_ABDD_4996_B0C6_971570676259__INCLUDED_)
#define AFX_DLGFIGHT_H__75CB374F_ABDD_4996_B0C6_971570676259__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgFight.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFight dialog

class CDlgFight : public CDialog
{
// Construction
public:
	CDlgFight(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFight)
	enum { IDD = IDD_DIALOG_FIGHT };
	CStatic	m_GunsCtrl;
	CProgressCtrl	m_HealthCtrl;
	CButton	m_FightButtonCtrl;
	CString	m_Health;
	CString	m_Text;
	//}}AFX_DATA

  int m_nCops;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFight)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
  CString PoliceAttack ();

	// Generated message map functions
	//{{AFX_MSG(CDlgFight)
	afx_msg void OnButtonFight();
	afx_msg void OnButtonRun();
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnButtonStay();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFIGHT_H__75CB374F_ABDD_4996_B0C6_971570676259__INCLUDED_)
