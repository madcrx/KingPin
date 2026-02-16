// DWarsView.h : interface of the CDWarsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DWARSVIEW_H__8998234C_60E8_474D_9068_34E39BDAC7A5__INCLUDED_)
#define AFX_DWARSVIEW_H__8998234C_60E8_474D_9068_34E39BDAC7A5__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "SplashScreen.h"

class CDWarsView : public CFormView
{
protected: // create from serialization only
	CDWarsView();
	DECLARE_DYNCREATE(CDWarsView)

public:
	//{{AFX_DATA(CDWarsView)
	enum { IDD = IDD_DWARS_FORM };
	CButton	m_HospitalCtrl;
	CButton	m_GunsCtrl;
	CButton	m_BuySellCtrl;
	CButton	m_EndCtrl;
	CStatic	m_GunCtrl;
	CStatic	m_TotalCtrl;
	CStatic	m_HealthTextCtrl;
	CStatic	m_DistrictCtrl;
	CStatic	m_DebtCtrl;
	CStatic	m_DayCtrl;
	CStatic	m_CashCtrl;
	CStatic	m_BankCtrl;
	CEdit	m_OutputCtrl;
	CButton	m_JetCtrl;
	CButton	m_FinanceCtrl;
	CProgressCtrl	m_HealthCtrl;
	CString	m_Output;
	//}}AFX_DATA

// Attributes
public:
	CDWarsDoc* GetDocument();

  BOOL m_bInitialScreen;
  CSplashScreen *m_pSplashScreen;

protected:
  CFont m_Font;

// Operations
public:
  void SetOutputText (CString text);
  void AddOutputText (CString text);
  void LoadScreen ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDWarsView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDWarsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDWarsView)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnButtonBuysell();
	afx_msg void OnButtonFinances();
	afx_msg void OnButtonJet();
	afx_msg void OnFileNewgame();
	afx_msg void OnInfoHighscores();
	afx_msg void OnButtonEndgame();
	afx_msg void OnFileOpengame();
	afx_msg void OnFileSaveasgame();
	afx_msg void OnFileSavegame();
	afx_msg void OnButtonHospital();
	afx_msg void OnButtonGuns();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in DWarsView.cpp
inline CDWarsDoc* CDWarsView::GetDocument()
   { return (CDWarsDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DWARSVIEW_H__8998234C_60E8_474D_9068_34E39BDAC7A5__INCLUDED_)
