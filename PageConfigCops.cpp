// PageConfigCops.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "PageConfigCops.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageConfigCops property page

IMPLEMENT_DYNCREATE(CPageConfigCops, CPropertyPage)

CPageConfigCops::CPageConfigCops() : CPropertyPage(CPageConfigCops::IDD)
{
	//{{AFX_DATA_INIT(CPageConfigCops)
	m_Damage = 0;
	m_DeputyEscape = 0;
	m_DeputyHit = 0;
	m_Drop = 0;
	m_Escape = 0;
	m_Hit = 0;
	m_Jail = 0;
	m_Toughness = 0;
	//}}AFX_DATA_INIT
}

CPageConfigCops::~CPageConfigCops()
{
}

void CPageConfigCops::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageConfigCops)
	DDX_Text(pDX, IDC_EDIT_DAMAGE, m_Damage);
	DDV_MinMaxInt(pDX, m_Damage, 1, 10);
	DDX_Text(pDX, IDC_EDIT_DEPUTY_ESCAPE, m_DeputyEscape);
	DDV_MinMaxInt(pDX, m_DeputyEscape, 1, 8);
	DDX_Text(pDX, IDC_EDIT_DEPUTY_HIT, m_DeputyHit);
	DDV_MinMaxInt(pDX, m_DeputyHit, 1, 8);
	DDX_Text(pDX, IDC_EDIT_DROP, m_Drop);
	DDV_MinMaxInt(pDX, m_Drop, 1, 100);
	DDX_Text(pDX, IDC_EDIT_ESCAPE, m_Escape);
	DDV_MinMaxInt(pDX, m_Escape, 1, 100);
	DDX_Text(pDX, IDC_EDIT_HIT, m_Hit);
	DDV_MinMaxInt(pDX, m_Hit, 1, 100);
	DDX_Text(pDX, IDC_EDIT_JAIL, m_Jail);
	DDV_MinMaxInt(pDX, m_Jail, 1, 100);
	DDX_Text(pDX, IDC_EDIT_TOUGHNESS, m_Toughness);
	DDV_MinMaxInt(pDX, m_Toughness, 1, 8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageConfigCops, CPropertyPage)
	//{{AFX_MSG_MAP(CPageConfigCops)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageConfigCops message handlers
