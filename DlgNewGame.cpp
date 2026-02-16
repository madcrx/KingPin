// DlgNewGame.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "DlgNewGame.h"
#include "DWarsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgNewGame dialog


CDlgNewGame::CDlgNewGame(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgNewGame::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgNewGame)
	//}}AFX_DATA_INIT
  m_nLocation = 0;
  m_bShowExit = TRUE;
}


void CDlgNewGame::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgNewGame)
	DDX_Control(pDX, IDCANCEL, m_CancelCtrl);
	DDX_Control(pDX, IDC_LIST_DISTRICTS, m_DistrictsCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgNewGame, CDialog)
	//{{AFX_MSG_MAP(CDlgNewGame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgNewGame message handlers

BOOL CDlgNewGame::OnInitDialog() 
{
	CDialog::OnInitDialog();

  CFrameWnd *pWnd = (CFrameWnd*)AfxGetMainWnd ();
  if (pWnd != NULL)
  {
    CDWarsDoc *pDoc = (CDWarsDoc *)pWnd->GetActiveDocument ();
    if (pDoc != NULL)
    {
      for (int i = NUM_LOCATIONS - 1; i >= 0; i--)
      {
        // Add it to the list
        m_DistrictsCtrl.InsertString (0, pDoc->m_LocationList [i].Name);
      }
    }
  }

  m_DistrictsCtrl.SetCurSel (0);

  if (m_bShowExit)
  {
    m_CancelCtrl.SetWindowText (_T("Exit"));
  }
  else
  {
    m_CancelCtrl.SetWindowText (_T("Cancel"));
  }

  m_bShowExit = FALSE;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgNewGame::OnOK() 
{
  m_nLocation	= m_DistrictsCtrl.GetCurSel ();

	CDialog::OnOK();
}
