// DWarsDoc.cpp : implementation of the CDWarsDoc class
//

#include "stdafx.h"
#include "DWars.h"

#include "DWarsDoc.h"
#include "DWarsView.h"
#include "DlgFight.h"
#include "DlgPlayerName.h"
#include "PageConfigDrugs.h"
#include "PageConfigCops.h"
#include "PageConfigGame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDWarsDoc

IMPLEMENT_DYNCREATE(CDWarsDoc, CDocument)

BEGIN_MESSAGE_MAP(CDWarsDoc, CDocument)
	//{{AFX_MSG_MAP(CDWarsDoc)
	ON_COMMAND(ID_FILE_OPTIONS, OnFileOptions)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDWarsDoc construction/destruction

CDWarsDoc::CDWarsDoc()
{
  m_bShowExit = FALSE;
  m_bMakeLoan = TRUE;
  m_bSellGun = TRUE;

  m_PlayerName = "";
  for (int i = 0; i < NUM_DRUGS; i++)
  {
    m_Drugs [i].Number = 0;
    m_Drugs [i].Price = 0;
    m_DrugPrices [i] = 0;
    m_DrugSpecials [i] = 0;
  }

  for (i = 0; i < NUM_GUNS; i++)
  {
    m_Guns [i].Number = 0;
    m_Guns [i].Price = 0;
  }
  m_NumGuns = 0;

  m_Cash = 2000;
  m_Debt = 5500;
  m_Bank = 0;
  m_Total = -3500;
  m_CoatSize = 100;
  m_CoatUsed = 0;
  m_Health = 100;

  // Game stats
  m_CurrentDay = 1;
  m_TotalDays = 30;
  m_Location = 0;
  m_CopCount = 3;

  // Constants
  m_LocationList [0].Name = _T("Bronx");
  m_LocationList [0].PolicePresence = 10;
  m_LocationList [0].MinDrug = NUM_DRUGS/2+1;
  m_LocationList [0].MaxDrug = NUM_DRUGS;

  m_LocationList [1].Name = _T("Ghetto");
  m_LocationList [1].PolicePresence = 5;
  m_LocationList [1].MinDrug = NUM_DRUGS/2+2;
  m_LocationList [1].MaxDrug = NUM_DRUGS;
    
  m_LocationList [2].Name = _T("Central Park");
  m_LocationList [2].PolicePresence = 15;
  m_LocationList [2].MinDrug = NUM_DRUGS/2;
  m_LocationList [2].MaxDrug = NUM_DRUGS;
  
  m_LocationList [3].Name = _T("Manhattan");
  m_LocationList [3].PolicePresence = 90;
  m_LocationList [3].MinDrug = NUM_DRUGS/2-2;
  m_LocationList [3].MaxDrug = NUM_DRUGS-2;
  
  m_LocationList [4].Name = _T("Coney Island");
  m_LocationList [4].PolicePresence = 20;
  m_LocationList [4].MinDrug = NUM_DRUGS/2;
  m_LocationList [4].MaxDrug = NUM_DRUGS;
  
  m_LocationList [5].Name = _T("Brooklyn");
  m_LocationList [5].PolicePresence = 70;
  m_LocationList [5].MinDrug = NUM_DRUGS/2-2;
  m_LocationList [5].MaxDrug = NUM_DRUGS-1;
  
  m_LocationList [6].Name = _T("Queens");
  m_LocationList [6].PolicePresence = 50;
  m_LocationList [6].MinDrug = NUM_DRUGS/2;
  m_LocationList [6].MaxDrug = NUM_DRUGS;

  m_LocationList [7].Name = _T("Staten Island");
  m_LocationList [7].PolicePresence = 20;
  m_LocationList [7].MinDrug = NUM_DRUGS/2;
  m_LocationList [7].MaxDrug = NUM_DRUGS;

  m_GunList [0].Name = _T("Baretta");
  m_GunList [0].Price = 3000;
  m_GunList [0].Space = 4;
  m_GunList [0].Damage = 5;

  m_GunList [1].Name = _T(".38");
  m_GunList [1].Price = 3500;
  m_GunList [1].Space = 4;
  m_GunList [1].Damage = 9;
    
  m_GunList [2].Name = _T("Ruger");
  m_GunList [2].Price = 2900;
  m_GunList [2].Space = 4;
  m_GunList [2].Damage = 4;
  
  m_GunList [3].Name = _T("Saturday Night Special");
  m_GunList [3].Price = 3100;
  m_GunList [3].Space = 4;
  m_GunList [3].Damage = 7;

  m_StoppedToList [0] = _T("have a beer");
  m_StoppedToList [1] = _T("smoke a joint");
  m_StoppedToList [2] = _T("smoke a cigar");
  m_StoppedToList [3] = _T("smoke a Djarum");
  m_StoppedToList [4] = _T("smoke a cigarette");

  m_CheapDivide = 4;
  m_ExpensiveMultiply = 4;
  m_MinTrenchcoatPrice = 200;
  m_MaxTrenchcoatPrice = 300;

  LoadPreferences ();
}

CDWarsDoc::~CDWarsDoc()
{
}

BOOL CDWarsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CDWarsDoc serialization

void CDWarsDoc::Serialize(CArchive& ar)
{
  CDWarsView *pView = NULL;
  POSITION pos = GetFirstViewPosition ();
  if (pos != NULL)
  {
    pView = (CDWarsView*)GetNextView (pos);
  }

	if (ar.IsStoring())
	{
    float fVersion = (float) 1.00;
    ar << fVersion;

    for (int i = 0; i < NUM_DRUGS; i++)
    {
      ar << m_Drugs [i].Number;
      ar << m_Drugs [i].Price;
      ar << m_DrugPrices [i];
      ar << m_DrugSpecials [i];
    }
    for (i = 0; i < NUM_GUNS; i++)
    {
      ar << m_Guns [i].Number;
      ar << m_Guns [i].Price;
    }
    ar << m_NumGuns;

    ar << m_Cash;
    ar << m_Debt;
    ar << m_Bank;
    ar << m_Total;
    ar << m_CoatSize;
    ar << m_CoatUsed;
    ar << m_Health;

    ar << m_CurrentDay;
    ar << m_Location;
    ar << m_bMakeLoan;
    ar << m_bSellGun;

    CString output = _T("");
    if (pView != NULL)
    {
      pView->m_OutputCtrl.GetWindowText (output);
    }
    ar << output;
	}
	else
	{
    float fVersion;
    ar >> fVersion;

    if (fVersion != (float)1.00)
    {
      AfxMessageBox (_T("Incorrect version or bad file.  Starting a new game...."));
      m_Location = 0;
      if (pView != NULL)
      {
        pView->m_OutputCtrl.SetWindowText (_T(""));
      }

      FirstDay ();
      return;
    }

    for (int i = 0; i < NUM_DRUGS; i++)
    {
      ar >> m_Drugs [i].Number;
      ar >> m_Drugs [i].Price;
      ar >> m_DrugPrices [i];
      ar >> m_DrugSpecials [i];
    }
    for (i = 0; i < NUM_GUNS; i++)
    {
      ar >> m_Guns [i].Number;
      ar >> m_Guns [i].Price;
    }
    ar >> m_NumGuns;

    ar >> m_Cash;
    ar >> m_Debt;
    ar >> m_Bank;
    ar >> m_Total;
    ar >> m_CoatSize;
    ar >> m_CoatUsed;
    ar >> m_Health;

    ar >> m_CurrentDay;
    ar >> m_Location;
    ar >> m_bMakeLoan;
    ar >> m_bSellGun;

    CString output = _T("");
    ar >> output;
    if (pView != NULL)
    {
      pView->m_Output = output;
    }
    UpdateAllViews (NULL);
  }

  m_bShowExit = FALSE;
}

/////////////////////////////////////////////////////////////////////////////
// CDWarsDoc diagnostics

#ifdef _DEBUG
void CDWarsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDWarsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDWarsDoc commands
void CDWarsDoc::PlaySoundFile (CString fileName)
{
  CDWarsApp *pApp = (CDWarsApp *)AfxGetApp ();
  if (pApp == NULL)
  {
    return;
  }

  pApp->PlaySoundFile (fileName);
}

int CDWarsDoc::IsCarryingRandom (int amount) 
{
  // Returns an index into the drugs array of a random drug that the player
  // is carrying at least "amount" of. If no suitable drug is found after 5
  // attempts, returns -1.
  int i, ind;
  for (i=0; i<5; i++) 
  {
    ind = brandom (0, NUM_DRUGS);
    if (m_Drugs [ind].Number >= amount)
    {
      return ind;
    }
  }
  return -1;
}

void CDWarsDoc::FirstDay ()
{
  for (int i = 0; i < NUM_DRUGS; i++)
  {
    m_Drugs [i].Number = 0;
    m_Drugs [i].Price = 0;
    m_DrugPrices [i] = 0;
    m_DrugSpecials [i] = 0;
  }
  for (i = 0; i < NUM_GUNS; i++)
  {
    m_Guns [i].Number = 0;
    m_Guns [i].Price = 0;
  }
  m_NumGuns = 0;

  m_Cash = 2000;
  m_Debt = 5500;
  m_Bank = 0;
  m_Total = -3500;
  m_CoatSize = 100;
  m_CoatUsed = 0;
  m_Health = 100;

  m_CurrentDay = 1;
  m_bMakeLoan = TRUE;
  m_bSellGun = TRUE;

  Events ();
  GenerateDrugs ();
}

void CDWarsDoc::NewDay (int nNewLocation)
{
  m_CurrentDay++;
  m_Location = nNewLocation;
  m_Debt = (long)(m_Debt*1.1);
  m_Bank = (long)(m_Bank*1.05);
  m_Total = m_Cash + m_Bank - m_Debt;
  m_bMakeLoan = TRUE;
  m_bSellGun = TRUE;

  Events ();
  
  // Check to make sure player is alive
  if (m_Health <= 0)
  {
    return;
  }

  // Make sure current day haven't crossed over allowed days
  if (m_CurrentDay > m_TotalDays)
  {
    m_CurrentDay = m_TotalDays;
  }

  GenerateDrugs ();
}

void CDWarsDoc::Events ()
{
  int i = 0;
  
  if (m_Total > 3000000) 
  { i = 130;  }
  else if (m_Total > 1000000)
  { i = 115;  }
  else
  { i = 100;  }
  
  if (brandom (0, i) > 75) 
  {
    i = brandom (0,100);
    
    if ( i < 33) 
    { 
      OfferObject (FALSE); 
    } 
    else if (i<50) 
    { 
      RandomOffer ();
    } 
    else 
    {
      StartOfficerHardAss (_T(""), _T(""));
    }
  }
}

void CDWarsDoc::OfferObject(BOOL ForceContainer)
{
  int gunIndex = 0;
  int price = 0;
  CString text;
  int ret = 0;

  if (brandom (0, 100) < 50 || ForceContainer)
  { // Offer trenchcoat
    price = brandom (m_MinTrenchcoatPrice, m_MaxTrenchcoatPrice);
    if (price <= m_Cash)
    {
      text.Format (_T("Would you like to buy a bigger trenchcoat for $%d?"), price);
      ret = AfxMessageBox (text, MB_YESNO);
      if (ret == IDYES)
      {
        m_CoatSize += 20;
        m_Cash -= price;
        m_Total = m_Cash + m_Bank - m_Debt;
      }
    }
  }
  else
  {  // Offer gun
    gunIndex = brandom (0, NUM_GUNS);
    price = m_GunList [gunIndex].Price / 10;
    if (price <= m_Cash)
    {
      if (m_GunList [gunIndex].Space > (m_CoatSize - m_CoatUsed))
      {
        //text = _T("Not enough room for a gun");
      }
      else
      {
        text.Format (_T("Would you like to buy a %s for $%d?"), 
          m_GunList [gunIndex].Name, price);

        ret = AfxMessageBox (text, MB_YESNO);
        if (ret == IDYES)
        {
          // Remove the cost from cash
          m_Cash -= price;
          m_Total = m_Cash + m_Bank - m_Debt;

          // Adjust the price of the gun in the player's inventory
          int nTotalInv = m_Guns [gunIndex].Price * 
            m_Guns [gunIndex].Number;
          int nTotalPurchase = price;

          m_Guns [gunIndex].Price = 
            (nTotalInv + nTotalPurchase) / 
            (m_Guns [gunIndex].Number + 1);

          // Add gun quantity to player's inventory
          m_Guns [gunIndex].Number ++;
          m_NumGuns++;

          // Add quantity to coat filled space
          m_CoatUsed += m_GunList [gunIndex].Space;
        }
      }
    }
  }
}

void CDWarsDoc::RandomOffer()
{
  int r, amount, ind;
  CString text;
  
  r = brandom(0,100);
  
  if (r < 10) 
  {
    text = _T("You were mugged in the subway!");
    m_Cash = m_Cash * (long) brandom (80, 95) / 1001;
  } 
  else if (r < 30) 
  {  // Friend tries to give you drugs
    // Get a random amount of drugs
    amount = brandom (3,7);
    
    // See if the player is carrying that amount of a drug
    ind = IsCarryingRandom (amount);
    
    // Can not fit the amount of drugs in your coat
    if (amount > (m_CoatSize - m_CoatUsed))
    {
      if (ind == -1)
      {
        ind = brandom (0, NUM_DRUGS);
      }

      text.Format (_T("Your friend tries to give you %d "), amount);
      text += m_DrugList [ind].Name;
      text += _T(", but you don't have enough room!");
    }
    else if (ind == -1) 
    {
      // Player does not have enough of the drug, so friend donates
      ind = brandom (0, NUM_DRUGS);
      text.Format (_T("You meet a friend! He gives you %d "), amount);
      text += m_DrugList [ind].Name;
      m_Drugs [ind].Number += amount;
      m_CoatUsed += amount;
    } 
    else 
    {
      // Player has the drug, so gives it to friend
      text.Format (_T("You meet a friend! You give him %d "), amount);
      text += m_DrugList [ind].Name;
      m_Drugs [ind].Number -= amount;
      m_CoatUsed -= amount;
    }
  } 
  else if (r < 50) 
  {  // Police dogs chase, causing drug drop
    amount = brandom (3,7);
    
    // See if the player is carrying that amount of a drug
    ind = IsCarryingRandom (amount);
    
    if (ind != -1) 
    { // Player is carrying that amount of a drug
      text.Format (_T("Police dogs chase you for %d blocks! You dropped some "),
        brandom (3, 7));
      text += m_DrugList [ind].Name;
      text += _T("!  That's a drag, man!");
      
      m_Drugs [ind].Number -= amount;
      m_CoatUsed -= amount;
    } 
    else 
    { // Player doesn't have that drug, so the player finds a random drug
      ind = brandom (0, NUM_DRUGS);
      amount = brandom (3,7);
      
      text.Format (_T("You find %d "), amount);
      text += m_DrugList [ind].Name;
      text += _T(" on a dead dude in the subway");

      if (amount > (m_CoatSize - m_CoatUsed))
      {
        text += _T(", but you don't have room for it!");
      }
      else
      {
        text += _T("!");
        m_Drugs [ind].Number += amount;
        m_CoatUsed += amount;
      }
    }
  }
  else if (r < 60 && ((m_Drugs [11].Number + m_Drugs [2].Number) > 0))
  {  // m_Drugs [11] = Weed and m_Drugs[2] = Hashish
    ind = (m_Drugs [11].Number > m_Drugs [2].Number) ? 11 : 2;
    amount = brandom (2,6);
    
    if (amount > m_Drugs [ind].Number) 
    {
      amount = m_Drugs [ind].Number;
    }
    
    text = _T("Your mama made brownies with some of your ");
    text += m_DrugList [ind].Name;
    text += _T("!  They were great!");
    
    m_Drugs [ind].Number -= amount;
    m_CoatUsed -= amount;
  }
  else if (r < 65) 
  {
    /*
    strcpy(text,"YN^There is some weed that smells like paraquat here!");
    strcat(text,"^It looks good! Will you smoke it? ");
    To->EventNum=E_WEED;
    SendQuestion(NULL,C_NONE,To,text);
    */
  }
  else 
  {
    amount = brandom (1, 10);

    if (m_Cash >= amount)
    {
      text += _T("You stopped to ");
      text += m_StoppedToList [brandom (0, NUM_STOPPED_TO)];
      m_Cash -= amount;
    }
    else
    {
      text += _T("You would have liked to ");
      text += m_StoppedToList [brandom (0, NUM_STOPPED_TO)];
      text += _T(", but you don't have the cash!");
    }
  }

  CDWarsView *pView = NULL;
  POSITION pos = GetFirstViewPosition ();
  if (pos != NULL)
  {
    pView = (CDWarsView*)GetNextView (pos);
  }

  if (pView != NULL)
  {
    if (text != _T(""))
    {
      // Add text to the output control and display box with info
      pView->AddOutputText (text);
      pView->AddOutputText (_T("\r\n"));

      if (m_bShowMessages)
      {
        AfxMessageBox (text);
      }
    }
  }
}

void CDWarsDoc::GenerateDrugs ()
{ 
  int NumEvents = 0, NumDrugs = 0, i = 0;
  int Deal [NUM_DRUGS];
  CString message = "";

  // Clean out any previous drugs and initialize what drugs have deals
  for (i=0; i < NUM_DRUGS; i++) 
  {
    m_DrugPrices [i] = 0;
    m_DrugSpecials [i] = 0;
    Deal [i] = 0;
  }
  
  // Determine the number of events
  if (brandom (0,100) < 70) 
  {  NumEvents = 1;  }
  
  if (brandom (0, 100) < 40 && NumEvents == 1) 
  {  NumEvents = 2;  }
  
  if (brandom (0, 100) < 5 && NumEvents == 2) 
  {  NumEvents = 3;  }
  
  // Determine prices for each event
  while (NumEvents > 0) 
  {
    i = brandom (0, NUM_DRUGS);
    
    if (Deal [i] !=0) 
    {
      continue;
    }
    
    if (m_DrugList [i].Expensive && 
      (!m_DrugList [i].Cheap || brandom (0,100) < 50) )
    {
      Deal[i] = brandom (1, 3);
      m_DrugPrices [i] = brandom 
        (m_DrugList [i].MinPrice, m_DrugList [i].MaxPrice) *
        m_ExpensiveMultiply;
      NumDrugs++;
      NumEvents--;
    } 
    else if (m_DrugList [i].Cheap) 
    {
      Deal [i] = 1;
      m_DrugPrices [i] = brandom 
        (m_DrugList [i].MinPrice, m_DrugList [i].MaxPrice) /
        m_CheapDivide;
      NumDrugs++;
      NumEvents--;
    }
  }
  
  // Figure out how many drugs to have
  NumDrugs = brandom (m_LocationList [m_Location].MinDrug,
    m_LocationList [m_Location].MaxDrug) 
    - NumDrugs;
  
  if (NumDrugs >= NUM_DRUGS) 
  {
    NumDrugs = NUM_DRUGS;
  }
  
  // Determine the price for the other drugs that didn't have an event
  while (NumDrugs > 0) 
  {
    // Randomly choose a drug
    i = brandom (0, NUM_DRUGS);
    
    // If not already assigned, give a price to the drug
    if (m_DrugPrices [i] == 0) 
    {
      m_DrugPrices [i] = brandom (m_DrugList [i].MinPrice, m_DrugList [i].MaxPrice);
      NumDrugs--;
    }
  }
    
  // For each of the drugs that had a special event/deal, output a text string and flag it as special
  for (i = 0; i < NUM_DRUGS; i++) 
  {
    if (Deal [i]) 
    {
      if (m_DrugList [i].Expensive) 
      {
        if (Deal [i] == 1)
        {
          message += _T("Cops made a big ");
          message += m_DrugList [i].Name;
          message += _T(" bust! Prices are outrageous!");
        }
        else
        {
          message += _T("Addicts are buying ");
          message += m_DrugList [i].Name;
          message += _T(" at ridiculous prices!");
        }
        m_DrugSpecials [i] = 1;
      } 
      else if (m_DrugList [i].Cheap) 
      {
        message += m_DrugList[i].CheapStr;
        m_DrugSpecials [i] = 2;
      }
      message += _T("\r\n");
    }
  }

  CDWarsView *pView = NULL;
  POSITION pos = GetFirstViewPosition ();
  if (pos != NULL)
  {
    pView = (CDWarsView*)GetNextView (pos);
  }
  
  if (pView != NULL)
  {
    if (message != _T(""))
    {
      // Add text to the output control and display box with info
      pView->AddOutputText (message);
      pView->AddOutputText (_T("\r\n"));

      if (m_bShowMessages)
      {
        AfxMessageBox (message);
      }
    }
  }
}

void CDWarsDoc::StartOfficerHardAss (CString loneStr, CString deputyStr)
{
  long Money = m_Cash + m_Bank - m_Debt;
  int Cops = 0;
  CString text;

  if (Money > 3000000)
  {
    Cops = brandom (11, 27);
  }
  else if (Money > 1000000)
  {
    Cops = brandom (7, 14);
  }
  else if (Money > 500000)
  {
    Cops = brandom (6, 12);
  }
  else if (Money > 100000)
  {
    Cops = brandom (2, 8);
  }
  else 
  {
    Cops = brandom (1,5);
  }
  
  if (Cops > 1)
  {
    if (deputyStr != _T(""))
    {
      text = deputyStr;
    }
  }
  else
  {
    if (loneStr != _T(""))
    {
      text = loneStr;
    }
  }

  CDlgFight dlg;
  dlg.m_nCops = Cops;
  dlg.m_Text = text;

  dlg.DoModal (); 
}

CString CDWarsDoc::FinishGame ()
{
  CDWarsApp *pApp = (CDWarsApp *)AfxGetApp ();
  if (pApp == NULL)
  {
    return _T("");
  }

  CString Key = _T("");
  CString Name, Alive, PrevName, PrevAlive;
  long nMoney, nPrevMoney;
  int nPlace = -1;
  CString Text = _T("");
  CString Health = _T("");

  for (int index = 1; index <= 11; index ++)
  {
    Key.Format (_T("HiScores\\%d"), index);

    // Read the name
    Name = pApp->GetProfileString (Key, _T("Name"), _T("01110001"));

    // Read the amount of money
    nMoney = pApp->GetProfileInt (Key, _T("Money"), -999999999);

    // Read the player's state at the end of the game 
    Alive = pApp->GetProfileString (Key, _T("Alive"), _T(""));

    if (nMoney <= m_Total)
    {
      nPlace = index;
      break;
    }
  }

  if (nPlace == -1)
  {
    Text.Format (_T("You didn't place this time"));
    return Text;
  }

  // Format text
  Text.Format (_T("You kick ass!  You rank number %d"), nPlace);
  
  if (m_Health > 0)
  {
    Health = _T("Yes");
  }
  else
  {
    Health = _T("No");
  }

  CDlgPlayerName dlg;
  dlg.m_Name = m_PlayerName;
  dlg.m_Rank.Format (_T("Number %d"), nPlace);

  int ret = dlg.DoModal ();
  if (ret == IDOK)
  {
    m_PlayerName = dlg.m_Name;
  }

  // Insert new entry
  pApp->WriteProfileString (Key, _T("Name"), m_PlayerName);
  pApp->WriteProfileInt (Key, _T("Money"), m_Total);
  pApp->WriteProfileString (Key, _T("Alive"), Health);

  // Bump down the entries after the new one
  for (index = nPlace + 1; index <= 11; index++)
  {
    Key.Format (_T("HiScores\\%d"), index);

    PrevName = pApp->GetProfileString (Key, _T("Name"), _T("01110001"));
    nPrevMoney = pApp->GetProfileInt (Key, _T("Money"), -999999999);
    PrevAlive = pApp->GetProfileString (Key, _T("Alive"), _T(""));

    if (nMoney == -999999999 && Name == _T("01110001") && Alive == _T(""))
    {
      // No more entries, the rest are unfilled
      break;
    }

    pApp->WriteProfileString (Key, _T("Name"), Name);
    pApp->WriteProfileInt (Key, _T("Money"), nMoney);
    pApp->WriteProfileString (Key, _T("Alive"), Alive);

    Name = PrevName;
    nMoney = nPrevMoney;
    Alive = PrevAlive;
  }

  return Text;
}

BOOL CDWarsDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

  POSITION pos = GetFirstViewPosition ();
  if (pos == NULL)
  {
    return FALSE;
  }

  CDWarsView *pView = (CDWarsView*)GetNextView (pos);

  if (pView == NULL)
  {
    return FALSE;
  }

  // Allow display of values
  pView->m_bInitialScreen = FALSE;
  
  // Refresh values on screen
  pView->LoadScreen ();
  
  // See if at bank/loan area
  pView->m_FinanceCtrl.EnableWindow ((m_Location == 0));
  
  // See if at gun shop location
  pView->m_GunsCtrl.EnableWindow ((m_Location == 1));

  // See if at hospital location
  pView->m_HospitalCtrl.EnableWindow ((m_Location == 6));


  // See if number of days is up
  if (m_CurrentDay == m_TotalDays)
  {
    pView->m_JetCtrl.ShowWindow (SW_HIDE);
    pView->m_EndCtrl.ShowWindow (SW_SHOW);
  }
  else if ((m_CurrentDay + 1) == m_TotalDays)
  {
    AfxMessageBox (_T("You have only one day left!"));
    pView->m_JetCtrl.ShowWindow (SW_SHOW);
    pView->m_EndCtrl.ShowWindow (SW_HIDE);
  }
	
	return TRUE;
}

void CDWarsDoc::OnFileOptions() 
{
  CPropertySheet sheet;
  CPageConfigDrugs pageDrugs;
  CPageConfigCops pageCops;
  CPageConfigGame pageGame;

  for (int i = 0; i < NUM_DRUGS; i++)
  {
    pageDrugs.m_DrugList [i].Name = m_DrugList [i].Name;
    pageDrugs.m_DrugList [i].Cheap = m_DrugList [i].Cheap;
    pageDrugs.m_DrugList [i].CheapStr = m_DrugList [i].CheapStr;
    pageDrugs.m_DrugList [i].Expensive = m_DrugList [i].Expensive;
    pageDrugs.m_DrugList [i].MaxPrice = m_DrugList [i].MaxPrice;
    pageDrugs.m_DrugList [i].MinPrice = m_DrugList [i].MinPrice;
  }

  sheet.AddPage (&pageDrugs);

  pageCops.m_Escape = m_CopInfo.EscapeProb;
  pageCops.m_DeputyEscape = m_CopInfo.DeputyEscape;
  pageCops.m_Hit = m_CopInfo.HitProb;
  pageCops.m_DeputyHit = m_CopInfo.DeputyHit;
  pageCops.m_Damage = m_CopInfo.Damage;
  pageCops.m_Toughness = m_CopInfo.Toughness;
  pageCops.m_Drop = m_CopInfo.DropProb;
  pageCops.m_Jail = m_JailCardProb;

  sheet.AddPage (&pageCops);

  pageGame.m_bMessages = m_bShowMessages;

  sheet.AddPage (&pageGame);

  int ret = sheet.DoModal ();
  if (ret == IDOK)
  {
    for (i = 0; i < NUM_DRUGS; i++)
    {
      m_DrugList [i].Name = pageDrugs.m_DrugList [i].Name;
      m_DrugList [i].Cheap = pageDrugs.m_DrugList [i].Cheap;
      m_DrugList [i].CheapStr = pageDrugs.m_DrugList [i].CheapStr;
      m_DrugList [i].Expensive = pageDrugs.m_DrugList [i].Expensive;
      m_DrugList [i].MaxPrice = pageDrugs.m_DrugList [i].MaxPrice;
      m_DrugList [i].MinPrice = pageDrugs.m_DrugList [i].MinPrice;
    }

    m_CopInfo.EscapeProb = pageCops.m_Escape;
    m_CopInfo.DeputyEscape = pageCops.m_DeputyEscape;
    m_CopInfo.HitProb = pageCops.m_Hit;
    m_CopInfo.DeputyHit = pageCops.m_DeputyHit;
    m_CopInfo.Damage = pageCops.m_Damage;
    m_CopInfo.Toughness = pageCops.m_Toughness;
    m_CopInfo.DropProb = pageCops.m_Drop;
    m_JailCardProb = pageCops.m_Jail;

    m_bShowMessages = pageGame.m_bMessages;

    SavePreferences ();
  }
}

void CDWarsDoc::LoadPreferences ()
{
  CDWarsApp *pApp = (CDWarsApp *)AfxGetApp ();

  if (pApp == NULL)
  {
    return;
  }

  CString key = _T("");
  for (int index = 0; index < NUM_DRUGS; index ++)
  {
    key.Format (_T("Preferences\\Drugs\\Drug%d"), index);
  
    m_DrugList [index].Name = pApp->GetProfileString (key, _T("Name"), _T(""));
    m_DrugList [index].MinPrice = pApp->GetProfileInt (key, _T("MinPrice"), -1);
    m_DrugList [index].MaxPrice = pApp->GetProfileInt (key, _T("MaxPrice"), -1);
    m_DrugList [index].Cheap = pApp->GetProfileInt (key, _T("Cheap"), 0);
    m_DrugList [index].Expensive = pApp->GetProfileInt (key, _T("Expensive"), 0);
    m_DrugList [index].CheapStr = pApp->GetProfileString (key, _T("CheapStr"), _T(""));
  }

  key = _T("Preferences\\Cops");
  m_CopInfo.EscapeProb = pApp->GetProfileInt (key, _T("EscapeProb"), -1);
  m_CopInfo.DeputyEscape = pApp->GetProfileInt (key, _T("DeputyEscape"), -1);
  m_CopInfo.HitProb = pApp->GetProfileInt (key, _T("HitProb"), -1);
  m_CopInfo.DeputyHit = pApp->GetProfileInt (key, _T("DeputyHit"), -1);
  m_CopInfo.Damage = pApp->GetProfileInt (key, _T("Damage"), -1);
  m_CopInfo.Toughness = pApp->GetProfileInt (key, _T("Toughness"), -1);
  m_CopInfo.DropProb = pApp->GetProfileInt (key, _T("DropProb"), -1);
  m_JailCardProb = pApp->GetProfileInt (key, _T("JailCard"), -1);

  m_bShowMessages = pApp->GetProfileInt (_T("Preferences"), _T("ShowMessages"), 1);

  // Check to make sure all entries loaded correctly
  if (m_CopInfo.EscapeProb == -1)
  {
    m_CopInfo.EscapeProb = 70;
  }
  if (m_CopInfo.DeputyEscape == -1)
  {
    m_CopInfo.DeputyEscape = 2;
  }
  if (m_CopInfo.HitProb == -1)
  {
    m_CopInfo.HitProb = 65;
  }
  if (m_CopInfo.DeputyHit == -1)
  {
    m_CopInfo.DeputyHit = 2;
  }
  if (m_CopInfo.Damage == -1)
  {
    m_CopInfo.Damage = 5;
  }
  if (m_CopInfo.Toughness == -1)
  {
    m_CopInfo.Toughness = 2;
  }
  if (m_CopInfo.DropProb == -1)
  {
    m_CopInfo.DropProb = 30;
  }
  if (m_JailCardProb == -1)
  {
    m_JailCardProb = 10;
  }

  if (m_DrugList [0].Name == _T("") && m_DrugList [0].MinPrice == -1 &&
    m_DrugList [0].MaxPrice == -1 && m_DrugList [0].CheapStr == _T(""))
  {
    m_DrugList [0].Name = _T("Acid");
    m_DrugList [0].MinPrice = 1000;
    m_DrugList [0].MaxPrice = 4400;
    m_DrugList [0].Cheap = TRUE;
    m_DrugList [0].Expensive = FALSE;
    m_DrugList [0].CheapStr = _T("The market is flooded with cheap home-made acid!");
  }
  if (m_DrugList [1].Name == _T("") && m_DrugList [1].MinPrice == -1 &&
    m_DrugList [1].MaxPrice == -1 && m_DrugList [1].CheapStr == _T(""))
  {
    m_DrugList [1].Name = _T("Cocaine");
    m_DrugList [1].MinPrice = 15000;
    m_DrugList [1].MaxPrice = 29000;
    m_DrugList [1].Cheap = FALSE;
    m_DrugList [1].Expensive = TRUE;
    m_DrugList [1].CheapStr = _T("");
  }
  if (m_DrugList [2].Name == _T("") && m_DrugList [2].MinPrice == -1 &&
    m_DrugList [2].MaxPrice == -1 && m_DrugList [2].CheapStr == _T(""))
  {
    m_DrugList [2].Name = _T("Hashish");
    m_DrugList [2].MinPrice = 480;
    m_DrugList [2].MaxPrice = 1280;
    m_DrugList [2].Cheap = TRUE;
    m_DrugList [2].Expensive = FALSE;
    m_DrugList [2].CheapStr = _T("The Marrakesh Express has arrived!");
  }
  if (m_DrugList [3].Name == _T("") && m_DrugList [3].MinPrice == -1 &&
    m_DrugList [3].MaxPrice == -1 && m_DrugList [3].CheapStr == _T(""))
  {
    m_DrugList [3].Name = _T("Heroin");
    m_DrugList [3].MinPrice = 5500;
    m_DrugList [3].MaxPrice = 13000;
    m_DrugList [3].Cheap = FALSE;
    m_DrugList [3].Expensive = TRUE;
    m_DrugList [3].CheapStr = _T("");
  } 
  if (m_DrugList [4].Name == _T("") && m_DrugList [4].MinPrice == -1 &&
    m_DrugList [4].MaxPrice == -1 && m_DrugList [4].CheapStr == _T(""))
  {
    m_DrugList [4].Name = _T("Ecstasy");
    m_DrugList [4].MinPrice = 11;
    m_DrugList [4].MaxPrice = 60;
    m_DrugList [4].Cheap = TRUE;
    m_DrugList [4].Expensive = FALSE;
    m_DrugList [4].CheapStr = _T("Rival drug dealers raided a pharmacy and are selling cheap ecstasy!");
  }
  if (m_DrugList [5].Name == _T("") && m_DrugList [5].MinPrice == -1 &&
    m_DrugList [5].MaxPrice == -1 && m_DrugList [5].CheapStr == _T(""))
  {
    m_DrugList [5].Name = _T("Xanax");
    m_DrugList [5].MinPrice = 1500;
    m_DrugList [5].MaxPrice = 4400;
    m_DrugList [5].Cheap = FALSE;
    m_DrugList [5].Expensive = FALSE;
    m_DrugList [5].CheapStr = _T("");
  }
  if (m_DrugList [6].Name == _T("") && m_DrugList [6].MinPrice == -1 &&
    m_DrugList [6].MaxPrice == -1 && m_DrugList [6].CheapStr == _T(""))
  {
    m_DrugList [6].Name = _T("Special K");
    m_DrugList [6].MinPrice = 540;
    m_DrugList [6].MaxPrice = 1250;
    m_DrugList [6].Cheap = FALSE;
    m_DrugList [6].Expensive = TRUE;
    m_DrugList [6].CheapStr = _T("");
  }
  if (m_DrugList [7].Name == _T("") && m_DrugList [7].MinPrice == -1 &&
    m_DrugList [7].MaxPrice == -1 && m_DrugList [7].CheapStr == _T(""))
  {
    m_DrugList [7].Name = _T("GHB");
    m_DrugList [7].MinPrice = 1000;
    m_DrugList [7].MaxPrice = 2500;
    m_DrugList [7].Cheap = FALSE;
    m_DrugList [7].Expensive = FALSE;
    m_DrugList [7].CheapStr = _T("");
  }
  if (m_DrugList [8].Name == _T("") && m_DrugList [8].MinPrice == -1 &&
    m_DrugList [8].MaxPrice == -1 && m_DrugList [8].CheapStr == _T(""))
  {
    m_DrugList [8].Name = _T("Viagra");
    m_DrugList [8].MinPrice = 220;
    m_DrugList [8].MaxPrice = 700;
    m_DrugList [8].Cheap = FALSE;
    m_DrugList [8].Expensive = FALSE;
    m_DrugList [8].CheapStr = _T("");
  }
  if (m_DrugList [9].Name == _T("") && m_DrugList [9].MinPrice == -1 &&
    m_DrugList [9].MaxPrice == -1 && m_DrugList [9].CheapStr == _T(""))
  {
    m_DrugList [9].Name = _T("Morphine");
    m_DrugList [9].MinPrice = 630;
    m_DrugList [9].MaxPrice = 1300;
    m_DrugList [9].Cheap = FALSE;
    m_DrugList [9].Expensive = FALSE;
    m_DrugList [9].CheapStr = _T("");
  }
  if (m_DrugList [10].Name == _T("") && m_DrugList [10].MinPrice == -1 &&
    m_DrugList [10].MaxPrice == -1 && m_DrugList [10].CheapStr == _T(""))
  {
    m_DrugList [10].Name = _T("Speed");
    m_DrugList [10].MinPrice = 90;
    m_DrugList [10].MaxPrice = 250;
    m_DrugList [10].Cheap = FALSE;
    m_DrugList [10].Expensive = TRUE;
    m_DrugList [10].CheapStr = _T("");
  }
  if (m_DrugList [11].Name == _T("") && m_DrugList [11].MinPrice == -1 &&
    m_DrugList [11].MaxPrice == -1 && m_DrugList [11].CheapStr == _T(""))
  {
    m_DrugList [11].Name = _T("Pot");
    m_DrugList [11].MinPrice = 315;
    m_DrugList [11].MaxPrice = 890;
    m_DrugList [11].Cheap = TRUE;
    m_DrugList [11].Expensive = FALSE;
    m_DrugList [11].CheapStr = _T("Columbian freighter dusted the Coast Guard!  Pot prices have bottomed out!");
  }
}

void CDWarsDoc::SavePreferences ()
{
  CDWarsApp *pApp = (CDWarsApp *)AfxGetApp ();

  if (pApp == NULL)
  {
    return;
  }

  CString key = _T("");
  for (int index = 0; index < NUM_DRUGS; index ++)
  {
    key.Format (_T("Preferences\\Drugs\\Drug%d"), index);
  
    pApp->WriteProfileString (key, _T("Name"), m_DrugList [index].Name);
    pApp->WriteProfileInt (key, _T("MinPrice"), m_DrugList [index].MinPrice);
    pApp->WriteProfileInt (key, _T("MaxPrice"), m_DrugList [index].MaxPrice);
    pApp->WriteProfileInt (key, _T("Cheap"), m_DrugList [index].Cheap);
    pApp->WriteProfileInt (key, _T("Expensive"), m_DrugList [index].Expensive);
    pApp->WriteProfileString (key, _T("CheapStr"), m_DrugList [index].CheapStr);
  }

  key = _T("Preferences\\Cops");
  pApp->WriteProfileInt (key, _T("EscapeProb"), m_CopInfo.EscapeProb);
  pApp->WriteProfileInt (key, _T("DeputyEscape"), m_CopInfo.DeputyEscape);
  pApp->WriteProfileInt (key, _T("HitProb"), m_CopInfo.HitProb);
  pApp->WriteProfileInt (key, _T("DeputyHit"), m_CopInfo.DeputyHit);
  pApp->WriteProfileInt (key, _T("Damage"), m_CopInfo.Damage);
  pApp->WriteProfileInt (key, _T("Toughness"), m_CopInfo.Toughness);
  pApp->WriteProfileInt (key, _T("DropProb"), m_CopInfo.DropProb);
  pApp->WriteProfileInt (key, _T("JailCard"), m_JailCardProb);

  pApp->WriteProfileInt (_T("Preferences"), _T("ShowMessages"), m_bShowMessages);
}
