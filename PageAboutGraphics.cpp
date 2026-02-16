// PageAboutGraphics.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "PageAboutGraphics.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageAboutGraphics property page

IMPLEMENT_DYNCREATE(CPageAboutGraphics, CPropertyPage)

CPageAboutGraphics::CPageAboutGraphics() : CPropertyPage(CPageAboutGraphics::IDD)
{
	//{{AFX_DATA_INIT(CPageAboutGraphics)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageAboutGraphics::~CPageAboutGraphics()
{
}

void CPageAboutGraphics::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageAboutGraphics)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageAboutGraphics, CPropertyPage)
	//{{AFX_MSG_MAP(CPageAboutGraphics)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageAboutGraphics message handlers
