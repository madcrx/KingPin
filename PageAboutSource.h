#if !defined(AFX_PAGEABOUTSOURCE_H__FB01442C_ED4C_4FC5_87A6_113E531EE729__INCLUDED_)
#define AFX_PAGEABOUTSOURCE_H__FB01442C_ED4C_4FC5_87A6_113E531EE729__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// PageAboutSource.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageAboutSource dialog

class CPageAboutSource : public CPropertyPage
{
	DECLARE_DYNCREATE(CPageAboutSource)

// Construction
public:
	CPageAboutSource();
	~CPageAboutSource();

// Dialog Data
	//{{AFX_DATA(CPageAboutSource)
	enum { IDD = IDD_PAGE_ABOUT_SOURCE };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(CPageAboutSource)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CPageAboutSource)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEABOUTSOURCE_H__FB01442C_ED4C_4FC5_87A6_113E531EE729__INCLUDED_)
