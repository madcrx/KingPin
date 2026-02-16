// DlgFight.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "DWarsDoc.h"
#include "DlgFight.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFight dialog


CDlgFight::CDlgFight(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFight::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFight)
	m_Health = _T("");
	m_Text = _T("");
	//}}AFX_DATA_INIT
}


void CDlgFight::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFight)
	DDX_Control(pDX, IDC_STATIC_GUNS, m_GunsCtrl);
	DDX_Control(pDX, IDC_PROGRESS_HEALTH, m_HealthCtrl);
	DDX_Control(pDX, IDC_BUTTON_FIGHT, m_FightButtonCtrl);
	DDX_Text(pDX, IDC_STATIC_HEALTH, m_Health);
	DDX_Text(pDX, IDC_STATIC_TEXT, m_Text);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFight, CDialog)
	//{{AFX_MSG_MAP(CDlgFight)
	ON_BN_CLICKED(IDC_BUTTON_FIGHT, OnButtonFight)
	ON_BN_CLICKED(IDC_BUTTON_RUN, OnButtonRun)
	ON_BN_CLICKED(IDC_BUTTON_STAY, OnButtonStay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFight message handlers

BOOL CDlgFight::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
  if (m_nCops == 1)
  {
    m_Text = _T("Office HardAss is chasing you!");
  }
  else
  {
    m_Text.Format (_T("Officer HardAss and %d of his deputies are  chasing you!"), m_nCops);
  }

  CFrameWnd *pWnd = (CFrameWnd*)AfxGetMainWnd ();
  if (pWnd != NULL)
  {
    CDWarsDoc *pDoc = (CDWarsDoc *)pWnd->GetActiveDocument ();
    if (pDoc != NULL)
    {
      pDoc->PlaySoundFile (_T("Sounds\\CopChase.wav"));

      if (pDoc->m_NumGuns > 0)
      {
        m_FightButtonCtrl.EnableWindow (TRUE);
      }

      CString temp;
      temp.Format (_T("%d"), pDoc->m_NumGuns);
      m_GunsCtrl.SetWindowText (temp);
      
      m_Health.Format (_T("%d"), pDoc->m_Health);
      m_HealthCtrl.SetPos (pDoc->m_Health);
      
      UpdateData (FALSE);
    }
  }

  return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgFight::OnButtonFight() 
{
  CDWarsDoc *pDoc = NULL;
  CFrameWnd *pWnd = (CFrameWnd*)AfxGetMainWnd ();
  if (pWnd != NULL)
  {
    pDoc = (CDWarsDoc *)pWnd->GetActiveDocument ();
    if (pDoc == NULL)
    {
      CDialog::OnCancel ();
      return;
    }
  }
  else
  {
    CDialog::OnCancel ();
    return;
  }
  
  CString text = _T("");;
  
  // Figure out damage base figure
  int nDamage = 100 - (brandom (0, m_nCops) * pDoc->m_CopInfo.Toughness);
  
  // Add in damage for each gun
  for (int i = 0; i < NUM_GUNS; i++)
  {
    for (int j = 0; j < pDoc->m_Guns [i].Number; j++)
    {
      nDamage += brandom (0, pDoc->m_GunList [i].Damage);
    }
  }
  
  // Figure out if player has killed any cops
  if (nDamage >= 100)
  {
    if (m_nCops == 1)
    {
      // Add money to cash
      int nMoney = brandom (1500, 3000);
      text.Format (_T("You killed Officer HardAss! \n\n You find $%d on his corpse!"), nMoney);
      pDoc->m_Cash += nMoney;
      
      AfxMessageBox (text);
      
      // Figure out doctor fee
      nMoney = brandom (1000, (2000 - (5 * pDoc->m_Health)));
      if (brandom (0, 100) < 75
        && pDoc->m_Cash >= nMoney
        && pDoc->m_Health < 100)
      {
        text.Format (_T("Do you pay a doctor $%d to sew you up?"), nMoney);
        int ret = AfxMessageBox (text, MB_YESNO);
        if (ret == IDYES)
        {
          pDoc->m_Health = 100;
          pDoc->m_Cash -= nMoney;
          pDoc->m_Total = pDoc->m_Cash + pDoc->m_Bank - pDoc->m_Debt;
        }
      }
      
      // Player lives to deal and die another day
      CDialog::OnOK ();
      return;
    }
    else
    {
      text += _T("You got one, man!");
      
      // Reduce number of cops by one
      m_nCops --;
      if (m_nCops == 1)
      {
        m_Text = _T("Office HardAss is chasing you!");
      }
      else
      {
        m_Text.Format (_T("Officer HardAss and %d of his deputies are  chasing you!"), m_nCops);
      }
      
      // Update screen
      UpdateData (FALSE);
    }
  }
  else
  {
    text = _T("You missed!");
  }

  text += _T("\n\n");

  // Now let the law have its turn!
  text += PoliceAttack ();

  // Update screen
  m_Health.Format (_T("%d"), pDoc->m_Health);
  UpdateData (FALSE);
  m_HealthCtrl.SetPos (pDoc->m_Health);

  // Show any data from encounter
  AfxMessageBox (text);

  // Check to see if player is dead
  if (pDoc->m_Health == 0)
  {
    CDialog::OnOK ();
  }
}

void CDlgFight::OnButtonRun() 
{
  CDWarsDoc *pDoc = NULL;
  CFrameWnd *pWnd = (CFrameWnd*)AfxGetMainWnd ();
  if (pWnd != NULL)
  {
    pDoc = (CDWarsDoc *)pWnd->GetActiveDocument ();
    if (pDoc == NULL)
    {
      CDialog::OnCancel ();
      return;
    }
  }
  else
  {
    CDialog::OnCancel ();
    return;
  }

  CString text = "";
  int nEscapeProp = pDoc->m_CopInfo.EscapeProb - ((m_nCops -1) * (pDoc->m_CopInfo.DeputyEscape));

  // Test to see if the player can get away
  if (brandom (0, 100) < nEscapeProp)
  { 
    text = _T("You lose him in the alleys.");
    AfxMessageBox (text);
    CDialog::OnOK ();
    return;
  }

  if (m_nCops <= 1)
  {
    text = _T("You can't lose him!");
  }
  else
  {
    text = _T("You can't lose them!");
  }

  text += _T("\n\n");

  // Now let the law have its turn!
  text += PoliceAttack ();

  // Update screen
  m_Health.Format (_T("%d"), pDoc->m_Health);
  UpdateData (FALSE);
  m_HealthCtrl.SetPos (pDoc->m_Health);

  // Show any data from encounter
  AfxMessageBox (text);

  // Check to see if player is dead
  if (pDoc->m_Health == 0)
  {
    CDialog::OnOK ();
  }
}

CString CDlgFight::PoliceAttack ()
{
  CDWarsDoc *pDoc = NULL;
  CFrameWnd *pWnd = (CFrameWnd*)AfxGetMainWnd ();
  if (pWnd != NULL)
  {
    pDoc = (CDWarsDoc *)pWnd->GetActiveDocument ();
    if (pDoc == NULL)
    {
      return _T("");
    }
  }
  else
  {
    return _T("");
  }

  int nDamage = 0;
  CString text = "";
  if (m_nCops <= 1)
  {
    text = _T("He's firing on you, man!\n");
  }
  else
  {
    text = _T("They're firing on you, man!\n");
  }

  // Calculate the hit probablility
  int nHitProb = pDoc->m_CopInfo.HitProb + ((m_nCops - 1) * pDoc->m_CopInfo.DeputyHit);

  // See if cops hit
  if (brandom (0, 100) < nHitProb)
  {
    // Calculate damage from each cop
    for (int i = 0; i < m_nCops; i++)
    {
      nDamage += brandom (0, pDoc->m_CopInfo.Damage);
    }
    if (nDamage == 0)
    {
      nDamage = 1;
    }

    CString temp;
    temp.Format (_T("You've been hit for %d!\n"), nDamage);
    text += temp;

    // See if the cops killed the player
    if (nDamage >= pDoc->m_Health)
    {
      if (m_nCops <= 1)
      {
        text += _T("He wasted you, man!  What a drag!");
      }
      else
      {
        text += _T("They wasted you, man!  What a drag!");
      }
      pDoc->m_Health = 0;
    }
    else
    {
      pDoc->m_Health -= nDamage;
    }
  }
  else
  {
    if (m_nCops <= 1)
    {
      text += _T("He missed!");
    }
    else
    {
      text += _T("They missed!");
    }
  }

  return text;
}

void CDlgFight::OnCancel() 
{
//	CDialog::OnCancel();
}

void CDlgFight::OnOK() 
{
//	CDialog::OnOK();
}

void CDlgFight::OnButtonStay() 
{
  CDWarsDoc *pDoc = NULL;
  CFrameWnd *pWnd = (CFrameWnd*)AfxGetMainWnd ();
  if (pWnd != NULL)
  {
    pDoc = (CDWarsDoc *)pWnd->GetActiveDocument ();
    if (pDoc == NULL)
    {
      CDialog::OnOK ();
      return;
    }
  }
  else
  {
    CDialog::OnOK ();
    return;
  }

  BOOL bHasDrugs = FALSE;
  for (int i = 0; i < NUM_DRUGS; i++)
  {
    if (pDoc->m_Drugs [i].Number != 0)
    {
      bHasDrugs = TRUE;
      break;
    }
  }

  if (!bHasDrugs)
  {
    AfxMessageBox (_T("The police frisk you, but you are not carrying any drugs!  They let you go with a reluctant apology."));
    CDialog::OnOK ();
    return;
  }

  CString text;

  int nGetAway = brandom (0, 100);
  int nCost = brandom ((int)pDoc->m_Total / 8, (int)pDoc->m_Total / 4);

  if (nCost <= 0)
  {
    nCost = 5000;
  }

  if (nGetAway < pDoc->m_JailCardProb)
  {    
    text.Format (_T("The police confiscate all your drugs, but your lawyer gets the criminal charges dropped on a technicality!  Court fees are $%d."), nCost);
  }
  else 
  {
    int nDays = brandom (1, 4);
    if (nDays == 1)
    {
      text.Format (_T("The police confiscate all your drugs and you spend %d day in jail.  You are charged $%d in fines"), nDays, nCost);
    }
    else
    {
      text.Format (_T("The police confiscate all your drugs and you spend %d days in jail.  You are charged $%d in fines"), nDays, nCost);
    }
    pDoc->PlaySoundFile (_T("Sounds\\jaildoor.wav"));
    pDoc->m_CurrentDay += nDays;
  }

  // Take out cost from player's money
  pDoc->m_Cash -= nCost;
  if (pDoc->m_Cash < 0)
  {
    pDoc->m_Bank += pDoc->m_Cash;
    pDoc->m_Cash = 0;
    if (pDoc->m_Bank <= 0)
    {
      pDoc->m_Debt -= pDoc->m_Bank;
      pDoc->m_Bank = 0;
    }
  }
  pDoc->m_Total = pDoc->m_Cash + pDoc->m_Bank - pDoc->m_Debt;


  // Remove all drugs off the player
  for (i = 0; i < NUM_DRUGS; i++)
  {
    pDoc->m_Drugs [i].Number = 0;
    pDoc->m_Drugs [i].Price = 0;
  }
//fix arrest bug
  int numberofguns = 0;
  for (i = 0; i < NUM_GUNS; i++)
  {
 
      numberofguns = numberofguns + pDoc->m_Guns [i].Number;
    
  }

  pDoc->m_CoatUsed = numberofguns * 4;
  AfxMessageBox (text);
 //     text.Format (_T("You have %d guns.  You have %d space"), numberofguns, pDoc->m_CoatUsed);
 // AfxMessageBox (text);

  CDialog::OnOK ();
}
