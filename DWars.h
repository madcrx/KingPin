// DWars.h : main header file for the DWARS application
//

#if !defined(AFX_DWARS_H__82F89405_034A_48F3_B6D3_1F71B3B2348F__INCLUDED_)
#define AFX_DWARS_H__82F89405_034A_48F3_B6D3_1F71B3B2348F__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "Defines.h"

/////////////////////////////////////////////////////////////////////////////
// CDWarsApp:
// See DWars.cpp for the implementation of this class
//

class CDWarsApp : public CWinApp
{
public:
	CDWarsApp();

  // Creates the DopeWars.Document registry entry
  void MyRegisterShellFileTypes ();

  // Takes the number in "price" and prints it into the string "buffer"
  // adding commas to split up thousands, and adding a currency symbol
  // to the start.
  void FormatPrice (long price, CString string);

  void PlaySoundFile (CString fileName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDWarsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
  BOOL m_bPlaySounds;

	//{{AFX_MSG(CDWarsApp)
	afx_msg void OnAppAbout();
	afx_msg void OnFileExit();
	afx_msg void OnInfoSound();
	afx_msg void OnUpdateInfoSound(CCmdUI* pCmdUI);
	afx_msg void OnInfoSoundOff();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DWARS_H__82F89405_034A_48F3_B6D3_1F71B3B2348F__INCLUDED_)
