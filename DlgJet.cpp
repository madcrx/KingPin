// DlgJet.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "DlgJet.h"
#include "DWars.h"
#include "DWarsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgJet dialog


CDlgJet::CDlgJet(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgJet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgJet)
	m_Place = _T("");
	//}}AFX_DATA_INIT
  m_nLocation = 0;
}


void CDlgJet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgJet)
	DDX_Control(pDX, IDC_LIST_DISTRICTS, m_ListCtrl);
	DDX_Text(pDX, IDC_STATIC_PLACE, m_Place);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgJet, CDialog)
	//{{AFX_MSG_MAP(CDlgJet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgJet message handlers

BOOL CDlgJet::OnInitDialog() 
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
        if (pDoc->m_Location != i)
        {
          // Add it to the list
          m_ListCtrl.InsertString (0, pDoc->m_LocationList [i].Name);
        }
      }
    }
  }

  m_ListCtrl.SetCurSel (0);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgJet::OnOK() 
{
  CFrameWnd *pWnd = (CFrameWnd*)AfxGetMainWnd ();
  if (pWnd != NULL)
  {
    CDWarsDoc *pDoc = (CDWarsDoc *)pWnd->GetActiveDocument ();
    if (pDoc != NULL)
    {
      m_nLocation = m_ListCtrl.GetCurSel ();
      if (m_nLocation == LB_ERR)
      {
        // Nothing selected
        return;
      }
      
      CString text;
      m_ListCtrl.GetText (m_nLocation, text);
      for (int i = 0; i < NUM_LOCATIONS; i++)
      {
        if (text == pDoc->m_LocationList [i].Name)
        {
          m_nLocation = i;
          CDialog::OnOK();
        }
      }
    }
  }
}
