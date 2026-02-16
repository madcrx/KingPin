// PageConfigGame.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "PageConfigGame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageConfigGame property page

IMPLEMENT_DYNCREATE(CPageConfigGame, CPropertyPage)

CPageConfigGame::CPageConfigGame() : CPropertyPage(CPageConfigGame::IDD)
{
	//{{AFX_DATA_INIT(CPageConfigGame)
	m_bMessages = FALSE;
	//}}AFX_DATA_INIT
}

CPageConfigGame::~CPageConfigGame()
{
}

void CPageConfigGame::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageConfigGame)
	DDX_Check(pDX, IDC_CHECK_MESSAGES, m_bMessages);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageConfigGame, CPropertyPage)
	//{{AFX_MSG_MAP(CPageConfigGame)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageConfigGame message handlers
