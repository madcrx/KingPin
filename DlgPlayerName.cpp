// DlgPlayerName.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "DlgPlayerName.h"
#include "DWarsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPlayerName dialog


CDlgPlayerName::CDlgPlayerName(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPlayerName::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPlayerName)
	m_Name = _T("");
	m_Rank = _T("");
	//}}AFX_DATA_INIT
}


void CDlgPlayerName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPlayerName)
	DDX_Text(pDX, IDC_EDIT_NAME, m_Name);
	DDX_Text(pDX, IDC_STATIC_RANK, m_Rank);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPlayerName, CDialog)
	//{{AFX_MSG_MAP(CDlgPlayerName)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPlayerName message handlers

BOOL CDlgPlayerName::OnInitDialog() 
{
	CDialog::OnInitDialog();
  
  CFrameWnd *pWnd = (CFrameWnd*)AfxGetMainWnd ();
  if (pWnd != NULL)
  {
    CDWarsDoc *pDoc = (CDWarsDoc *)pWnd->GetActiveDocument ();
    if (pDoc != NULL)
    {
      pDoc->PlaySoundFile (_T("Sounds\\Clap.wav"));
    }
  }

  // Bring up SIP entry box
  ::SHSipPreference (m_hWnd, SIP_UP);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
