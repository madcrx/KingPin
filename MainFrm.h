// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__CBD43436_FD95_4DC0_82E8_C9ACD3F9360B__INCLUDED_)
#define AFX_MAINFRM_H__CBD43436_FD95_4DC0_82E8_C9ACD3F9360B__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

// Array for the toolbar buttons

#if (_WIN32_WCE < 201)
static TBBUTTON g_arCBButtons[] = {
	{ 0,	ID_FILE_NEW,	TBSTATE_ENABLED, TBSTYLE_BUTTON,	0, 0, 0,  0},
	{ 1,    ID_FILE_OPEN,	TBSTATE_ENABLED, TBSTYLE_BUTTON,	0, 0, 0,  1},
	{ 2,	ID_FILE_SAVE,	TBSTATE_ENABLED, TBSTYLE_BUTTON,	0, 0, 0,  2},
	{ 0,	0,				TBSTATE_ENABLED, TBSTYLE_SEP,		0, 0, 0, -1},
	{ 3,	ID_FILE_NEWGAME,	TBSTATE_ENABLED, TBSTYLE_BUTTON,	0, 0, 0,  3},
	{ 4,    ID_FILE_OPENGAME,	TBSTATE_ENABLED, TBSTYLE_BUTTON,	0, 0, 0,  4},
	{ 5,	ID_FILE_SAVEGAME,	TBSTATE_ENABLED, TBSTYLE_BUTTON,	0, 0, 0,  5},
	{ 0,	0,				TBSTATE_ENABLED, TBSTYLE_SEP,		0, 0, 0, -1},
	{ 6,    ID_INFO_SOUND,	TBSTATE_ENABLED, TBSTYLE_BUTTON,	0, 0, 0,  6},
	{ 7,	ID_APP_ABOUT,	TBSTATE_ENABLED, TBSTYLE_BUTTON,	0, 0, 0,  7}
};
#endif

#if defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 212)
#define NUM_TOOL_TIPS 8
#endif


class CMainFrame : public CFrameWnd
{
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:
  void ToggleSound (BOOL bOn);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CCeCommandBar	m_wndCommandBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

  LPTSTR MakeString(UINT stringID);
  LPTSTR m_ToolTipsTable[NUM_TOOL_TIPS];
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__CBD43436_FD95_4DC0_82E8_C9ACD3F9360B__INCLUDED_)
