// PageAboutGeneral.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "PageAboutGeneral.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageAboutGeneral property page

IMPLEMENT_DYNCREATE(CPageAboutGeneral, CPropertyPage)

CPageAboutGeneral::CPageAboutGeneral() : CPropertyPage(CPageAboutGeneral::IDD)
{
	//{{AFX_DATA_INIT(CPageAboutGeneral)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageAboutGeneral::~CPageAboutGeneral()
{
}

void CPageAboutGeneral::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageAboutGeneral)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageAboutGeneral, CPropertyPage)
	//{{AFX_MSG_MAP(CPageAboutGeneral)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageAboutGeneral message handlers
