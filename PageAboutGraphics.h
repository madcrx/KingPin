#if !defined(AFX_PAGEABOUTGRAPHICS_H__0B3A8E80_9EF3_4ACE_95B1_A23524284F61__INCLUDED_)
#define AFX_PAGEABOUTGRAPHICS_H__0B3A8E80_9EF3_4ACE_95B1_A23524284F61__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PageAboutGraphics.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageAboutGraphics dialog

class CPageAboutGraphics : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageAboutGraphics)

// Construction
public:
	CPageAboutGraphics();
	~CPageAboutGraphics();

// Dialog Data
	//{{AFX_DATA(CPageAboutGraphics)
	enum { IDD = IDD_PAGE_ABOUT_GRAPHICS };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageAboutGraphics)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageAboutGraphics)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEABOUTGRAPHICS_H__0B3A8E80_9EF3_4ACE_95B1_A23524284F61__INCLUDED_)
