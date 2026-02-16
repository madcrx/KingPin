#if !defined(AFX_PAGEABOUTGENERAL_H__71ED985B_9009_494E_8B91_0796A6498C61__INCLUDED_)
#define AFX_PAGEABOUTGENERAL_H__71ED985B_9009_494E_8B91_0796A6498C61__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PageAboutGeneral.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageAboutGeneral dialog

class CPageAboutGeneral : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageAboutGeneral)

// Construction
public:
	CPageAboutGeneral();
	~CPageAboutGeneral();

// Dialog Data
	//{{AFX_DATA(CPageAboutGeneral)
	enum { IDD = IDD_PAGE_ABOUT_GENERAL };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageAboutGeneral)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageAboutGeneral)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEABOUTGENERAL_H__71ED985B_9009_494E_8B91_0796A6498C61__INCLUDED_)
