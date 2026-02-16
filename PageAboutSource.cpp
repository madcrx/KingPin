// PageAboutSource.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "PageAboutSource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageAboutSource property page

IMPLEMENT_DYNCREATE(CPageAboutSource, CPropertyPage)

CPageAboutSource::CPageAboutSource() : CPropertyPage(CPageAboutSource::IDD)
{
	//{{AFX_DATA_INIT(CPageAboutSource)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPageAboutSource::~CPageAboutSource()
{
}

void CPageAboutSource::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageAboutSource)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageAboutSource, CPropertyPage)
	//{{AFX_MSG_MAP(CPageAboutSource)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageAboutSource message handlers
