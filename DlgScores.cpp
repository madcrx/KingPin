// DlgScores.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "DWars.h"
#include "DlgScores.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgScores dialog


CDlgScores::CDlgScores(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgScores::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgScores)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgScores::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgScores)
	DDX_Control(pDX, IDC_LIST_SCORES, m_ScoresCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgScores, CDialog)
	//{{AFX_MSG_MAP(CDlgScores)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnButtonClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgScores message handlers

BOOL CDlgScores::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Insert Columns
  m_ScoresCtrl.InsertColumn (0, _T("Name"), LVCFMT_LEFT, 110);
  m_ScoresCtrl.InsertColumn (1, _T("Money"), LVCFMT_RIGHT, 75);
  m_ScoresCtrl.InsertColumn (2, _T("Alive"), LVCFMT_CENTER, 38);

  // Make selections extend across all columns
  CListCtrl* pListCtrl = (CListCtrl*) GetDlgItem(IDC_LIST_SCORES);
  DWORD dwStyle = ::SendMessage(pListCtrl->m_hWnd,
    LVM_GETEXTENDEDLISTVIEWSTYLE,0,0);
  dwStyle |= LVS_EX_FULLROWSELECT;
  ::SendMessage(pListCtrl->m_hWnd,LVM_SETEXTENDEDLISTVIEWSTYLE,0,dwStyle);

  CDWarsApp *pApp = (CDWarsApp *)AfxGetApp ();

  if (pApp == NULL)
  {
    AfxMessageBox (_T("Error with application class during initialization"));
    CDialog::OnCancel ();
  }

  CString key = _T("");
  CString name = _T("");
  CString money = _T("");
  CString alive = _T("");
  int nMoney = 0;
  for (int index = 0; index < 11; index ++)
  {
    key.Format (_T("HiScores\\%d"), index+1);
    
    // Read the name
    name = pApp->GetProfileString (key, _T("Name"), _T("01110001"));
    
    // Read the amount of money
    nMoney = pApp->GetProfileInt (key, _T("Money"), -999999999);
    
    // Read the player's state at the end of the game 
    alive = pApp->GetProfileString (key, _T("Alive"), _T(""));

    if (!(nMoney == -999999999 && name == _T("01110001") && alive == _T("")))
    {
      m_ScoresCtrl.InsertItem (index, name);
      money.Format (_T("%d"), nMoney);
      m_ScoresCtrl.SetItemText (index, 1, money);
      m_ScoresCtrl.SetItemText (index, 2, alive);
    }
  }
  
  return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgScores::OnButtonClear() 
{
  CDWarsApp *pApp = (CDWarsApp *)AfxGetApp ();

  if (pApp == NULL)
  {
    CDialog::OnCancel ();
  }

  int ret = AfxMessageBox (_T("Are you sure you wish to erase all the high scores?"), MB_YESNO);

  if (IDYES == ret)
  {
    CString key = _T("");
    for (int index = 0; index < 11; index ++)
    {
      key.Format (_T("HiScores\\%d"), index+1);
    
      pApp->WriteProfileString (key, _T("Name"), NULL);
      pApp->WriteProfileInt (key, _T("Money"), -999999999);
      pApp->WriteProfileString (key, _T("Alive"), NULL);
    }
    m_ScoresCtrl.DeleteAllItems ();
  }
}
