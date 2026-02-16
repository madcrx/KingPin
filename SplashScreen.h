#if !defined(AFX_SPLASHSCREEN_H__B68054B2_7E60_44C8_AD8E_07CB0A158697__INCLUDED_)
#define AFX_SPLASHSCREEN_H__B68054B2_7E60_44C8_AD8E_07CB0A158697__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// SplashScreen.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSplashScreen window

class CSplashScreen : public CWnd
{
// Construction
public:
	CSplashScreen();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSplashScreen)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSplashScreen();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSplashScreen)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

  CBitmap m_Bitmap;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLASHSCREEN_H__B68054B2_7E60_44C8_AD8E_07CB0A158697__INCLUDED_)
