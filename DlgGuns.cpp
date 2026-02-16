// DlgGuns.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "DlgGuns.h"
#include "DWarsDoc.h"
#include "DlgQuantity.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGuns dialog


CDlgGuns::CDlgGuns(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGuns::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGuns)
	m_Coat = _T("");
	m_Money = _T("");
	//}}AFX_DATA_INIT
}


void CDlgGuns::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGuns)
	DDX_Control(pDX, IDC_BUTTON_DUMP, m_DumpCtrl);
	DDX_Control(pDX, IDC_BUTTON_SELL, m_SellCtrl);
	DDX_Control(pDX, IDC_BUTTON_BUY, m_BuyCtrl);
	DDX_Control(pDX, IDC_LIST_SELL, m_ListSellCtrl);
	DDX_Control(pDX, IDC_LIST_BUY, m_ListBuyCtrl);
	DDX_Text(pDX, IDC_STATIC_COAT, m_Coat);
	DDX_Text(pDX, IDC_STATIC_MONEY, m_Money);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGuns, CDialog)
	//{{AFX_MSG_MAP(CDlgGuns)
	ON_BN_CLICKED(IDC_BUTTON_BUY, OnButtonBuy)
	ON_BN_CLICKED(IDC_BUTTON_DUMP, OnButtonDump)
	ON_BN_CLICKED(IDC_BUTTON_SELL, OnButtonSell)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGuns message handlers

BOOL CDlgGuns::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
  CDWarsDoc *pDoc = NULL;
  CFrameWnd *pWnd = (CFrameWnd*)AfxGetMainWnd ();
  if (pWnd != NULL)
  {
    pDoc = (CDWarsDoc *)pWnd->GetActiveDocument ();
    if (pDoc != NULL)
    {
      pDoc->PlaySoundFile (_T("Sounds\\Store.wav"));
    }
  }

  // Insert Columns
  m_ListBuyCtrl.InsertColumn (0, _T("Name"), LVCFMT_LEFT, 129);
  m_ListBuyCtrl.InsertColumn (1, _T("Price"), LVCFMT_RIGHT, 60);
  m_ListBuyCtrl.InsertColumn (2, _T("S"), LVCFMT_CENTER, 20);
  m_ListBuyCtrl.InsertColumn (3, _T("D"), LVCFMT_CENTER, 20);
  m_ListSellCtrl.InsertColumn (0, _T("Name"), LVCFMT_LEFT, 129);
  m_ListSellCtrl.InsertColumn (1, _T("Price"), LVCFMT_RIGHT, 70);
  m_ListSellCtrl.InsertColumn (2, _T("#"), LVCFMT_CENTER, 30);

  // Make selections extend across all columns
  CListCtrl* pListCtrl = (CListCtrl*) GetDlgItem(IDC_LIST_BUY);
  DWORD dwStyle = ::SendMessage(pListCtrl->m_hWnd,
    LVM_GETEXTENDEDLISTVIEWSTYLE,0,0);
  dwStyle |= LVS_EX_FULLROWSELECT;
  ::SendMessage(pListCtrl->m_hWnd,LVM_SETEXTENDEDLISTVIEWSTYLE,0,dwStyle);
  
  pListCtrl = (CListCtrl*) GetDlgItem(IDC_LIST_SELL);
  dwStyle = ::SendMessage(pListCtrl->m_hWnd,
    LVM_GETEXTENDEDLISTVIEWSTYLE,0,0);
  dwStyle |= LVS_EX_FULLROWSELECT;
  ::SendMessage(pListCtrl->m_hWnd,LVM_SETEXTENDEDLISTVIEWSTYLE,0,dwStyle);

  FillStrings ();
  FillLists ();
  EnableButtons ();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgGuns::FillLists ()
{
  CDWarsDoc *pDoc = NULL;
  CFrameWnd *pWnd = (CFrameWnd*)AfxGetMainWnd ();
  if (pWnd != NULL)
  {
    pDoc = (CDWarsDoc *)pWnd->GetActiveDocument ();
    if (pDoc == NULL)
    {
      return;
    }
  }
  else
  {
    return;
  }
  
  // Empty List
  m_ListBuyCtrl.DeleteAllItems ();
  m_ListSellCtrl.DeleteAllItems ();

  // Insert Items
  int count = 0;
  CString numString;

  for (int i = 0; i < NUM_GUNS; i++)
  {
    // Add the gun name to the list
    m_ListBuyCtrl.InsertItem (count, pDoc->m_GunList [i].Name);

    // Add the price to the list
    numString.Format (_T("$%d"), pDoc->m_GunList [i].Price);
    m_ListBuyCtrl.SetItemText (count, 1, numString);

    // Add the space
    numString.Format (_T("%d"), pDoc->m_GunList [i].Space);
    m_ListBuyCtrl.SetItemText (count, 2, numString);

    // Add the damage
    numString.Format (_T("%d"), pDoc->m_GunList [i].Damage);
    m_ListBuyCtrl.SetItemText (count, 3, numString);

    count++;
  }

  count = 0;

  for (i = 0; i < NUM_GUNS; i++)
  {
    if (pDoc->m_Guns [i].Number != 0) // Is here
    {
      // Add the gun name to the list
      m_ListSellCtrl.InsertItem (count, pDoc->m_GunList [i].Name);

      // Add the price to the list
      numString.Format (_T("%d"), pDoc->m_Guns [i].Price);
      m_ListSellCtrl.SetItemText (count, 1, numString);

      // Add the number
      numString.Format (_T("%d"), pDoc->m_Guns [i].Number);
      m_ListSellCtrl.SetItemText (count, 2, numString);

      count++;
    }
  }
}

void CDlgGuns::FillStrings ()
{
  CDWarsDoc *pDoc = NULL;
  CFrameWnd *pWnd = (CFrameWnd*)AfxGetMainWnd ();
  if (pWnd != NULL)
  {
    pDoc = (CDWarsDoc *)pWnd->GetActiveDocument ();
    if (pDoc == NULL)
    {
      return;
    }
  }
  else
  {
    return;
  }

  m_Money.Format (_T("Cash $%d"), pDoc->m_Cash);
  m_Coat.Format (_T("Coat (%d/%d)"), pDoc->m_CoatUsed, pDoc->m_CoatSize);

  // Update Screen
  UpdateData (FALSE);
}

void CDlgGuns::EnableButtons ()
{
  CDWarsDoc *pDoc = NULL;
  CFrameWnd *pWnd = (CFrameWnd*)AfxGetMainWnd ();
  if (pWnd != NULL)
  {
    pDoc = (CDWarsDoc *)pWnd->GetActiveDocument ();
    if (pDoc == NULL)
    {
      return;
    }
  }
  else
  {
    return;
  }

  m_SellCtrl.EnableWindow (pDoc->m_NumGuns > 0);
  m_DumpCtrl.EnableWindow (pDoc->m_NumGuns > 0);
  m_BuyCtrl.EnableWindow (pDoc->m_bSellGun);
}

void CDlgGuns::OnButtonBuy() 
{
  CDWarsDoc *pDoc = NULL;
  CFrameWnd *pWnd = (CFrameWnd*)AfxGetMainWnd ();
  if (pWnd != NULL)
  {
    pDoc = (CDWarsDoc *)pWnd->GetActiveDocument ();
    if (pDoc == NULL)
    {
      return;
    }
  }
  else
  {
    return;
  }

  POSITION pos = m_ListBuyCtrl.GetFirstSelectedItemPosition();
  if (pos == NULL)
  {
    //  Nothing selected
    return;
  }

  int nSelection = m_ListBuyCtrl.GetNextSelectedItem (pos);
  CString text = m_ListBuyCtrl.GetItemText (nSelection, 0);
  int nGunPosition = -1;
  for (int i = 0; i < NUM_GUNS; i++)
  {
    if (pDoc->m_GunList [i].Name == text)
    {
      nGunPosition = i;
    }
  }

  if (nGunPosition == -1)
  {
    // Not found
    return;
  }
 
  int  nSpace = 0;
  nSpace = pDoc->m_CoatSize - pDoc->m_CoatUsed;

  if ((pDoc->m_Cash - pDoc->m_GunList [nGunPosition].Price) <= 0)
  {
    AfxMessageBox (_T("You can not afford this gun!"));
    return;
  }
  if ((nSpace - pDoc->m_GunList [nGunPosition].Space) < 0)
  {
    AfxMessageBox (_T("You do not have enough room!"));
    return;
  }

  // Remove the cost from cash
  pDoc->m_Cash -= pDoc->m_GunList [nGunPosition].Price;
  pDoc->m_Total = pDoc->m_Cash + pDoc->m_Bank - pDoc->m_Debt;

  // Adjust the price of the gun in the player's inventory
  int nTotalInv = pDoc->m_Guns [nGunPosition].Price * 
    pDoc->m_Guns [nGunPosition].Number;
  int nTotalPurchase = pDoc->m_GunList [nGunPosition].Price * 1;

  pDoc->m_Guns [nGunPosition].Price = 
    (nTotalInv + nTotalPurchase) / 
    (pDoc->m_Guns [nGunPosition].Number + 1);

  // Add gun quantity to player's inventory
  pDoc->m_Guns [nGunPosition].Number += 1;
  pDoc->m_NumGuns++;

  // Add quantity to coat filled space
  pDoc->m_CoatUsed += pDoc->m_GunList [nGunPosition].Space;

  pDoc->m_bSellGun = FALSE;
  FillStrings ();
  FillLists ();
  EnableButtons ();
}

void CDlgGuns::OnButtonDump() 
{
  CDWarsDoc *pDoc = NULL;
  CFrameWnd *pWnd = (CFrameWnd*)AfxGetMainWnd ();
  if (pWnd != NULL)
  {
    pDoc = (CDWarsDoc *)pWnd->GetActiveDocument ();
    if (pDoc == NULL)
    {
      return;
    }
  }
  else
  {
    return;
  }

  POSITION pos = m_ListSellCtrl.GetFirstSelectedItemPosition();
  if (pos == NULL)
  {
    //  Nothing selected
    return;
  }

  int nSelection = m_ListSellCtrl.GetNextSelectedItem (pos);
  CString text = m_ListSellCtrl.GetItemText (nSelection, 0);
  int nGunPosition = -1;
  for (int i = 0; i < NUM_GUNS; i++)
  {
    if (pDoc->m_GunList [i].Name == text)
    {
      nGunPosition = i;
    }
  }

  if (nGunPosition == -1)
  {
    // Not found
    return;
  }

  CDlgQuantity dlg;

  CString Fact1;
  Fact1.Format (_T("\nYou are carrying %d"), pDoc->m_Guns [nGunPosition].Number);
  dlg.m_Fact1 = Fact1;
  dlg.m_Question = _T("How many do you drop?");
  dlg.m_Title = _T("Drop Guns");
  dlg.m_nMin = 1;
  dlg.m_nMax = pDoc->m_Guns [nGunPosition].Number;
  dlg.m_nNum = 1;

  int ret = dlg.DoModal ();
  if (IDOK == ret)
  {
    int nQuantity = min (pDoc->m_Guns [nGunPosition].Number, dlg.m_nNum);

    // Remove guns from inventory
    pDoc->m_Guns [nGunPosition].Number -= nQuantity;
    pDoc->m_NumGuns -= nQuantity;

    // Remove quantity from coat filled space
    pDoc->m_CoatUsed -= (nQuantity * pDoc->m_GunList [nGunPosition].Space);

    if (pDoc->m_Guns [nGunPosition].Number <= 0)
    {
      pDoc->m_Guns [nGunPosition].Number = 0;
      pDoc->m_Guns [nGunPosition].Price = 0;

      m_ListSellCtrl.DeleteItem (nSelection);
    }
    else
    {
      CString numString;
      numString.Format (_T("%d"), pDoc->m_Guns [nGunPosition].Number);
      m_ListSellCtrl.SetItemText (nSelection, 2, numString);    
    }

    FillStrings ();
    EnableButtons ();
  }
}

void CDlgGuns::OnButtonSell() 
{
  CDWarsDoc *pDoc = NULL;
  CFrameWnd *pWnd = (CFrameWnd*)AfxGetMainWnd ();
  if (pWnd != NULL)
  {
    pDoc = (CDWarsDoc *)pWnd->GetActiveDocument ();
    if (pDoc == NULL)
    {
      return;
    }
  }
  else
  {
    return;
  }

  POSITION pos = m_ListSellCtrl.GetFirstSelectedItemPosition();
  if (pos == NULL)
  {
    //  Nothing selected
    return;
  }

  int nSelection = m_ListSellCtrl.GetNextSelectedItem (pos);
  CString text = m_ListSellCtrl.GetItemText (nSelection, 0);
  int nGunPosition = -1;
  for (int i = 0; i < NUM_GUNS; i++)
  {
    if (pDoc->m_GunList [i].Name == text)
    {
      nGunPosition = i;
    }
  }

  if (nGunPosition == -1)
  {
    // Not found
    return;
  }

  CDlgQuantity dlg;

  CString Fact1;
  Fact1.Format (_T("\nYou are carrying %d"), pDoc->m_Guns [nGunPosition].Number);
  dlg.m_Fact1 = Fact1;
  dlg.m_Question = _T("How many do you sell?");
  dlg.m_Title = _T("Sell Guns");
  dlg.m_nMin = 1;
  dlg.m_nMax = pDoc->m_Guns [nGunPosition].Number;
  dlg.m_nNum = 1;

  int ret = dlg.DoModal ();
  if (IDOK == ret)
  {
    long nQuantity = min (pDoc->m_Guns [nGunPosition].Number, dlg.m_nNum);
    long nMoney = nQuantity * pDoc->m_GunList [nGunPosition].Price;

    // Remove guns from inventory
    pDoc->m_Guns [nGunPosition].Number -= nQuantity;
    pDoc->m_NumGuns -= nQuantity;

    // Remove quantity from coat filled space
    pDoc->m_CoatUsed -= (nQuantity * pDoc->m_GunList [nGunPosition].Space);

    if (pDoc->m_Guns [nGunPosition].Number <= 0)
    {
      pDoc->m_Guns [nGunPosition].Number = 0;
      pDoc->m_Guns [nGunPosition].Price = 0;

      m_ListSellCtrl.DeleteItem (nSelection);
    }
    else
    {
      CString numString;
      numString.Format (_T("%d"), pDoc->m_Guns [nGunPosition].Number);
      m_ListSellCtrl.SetItemText (nSelection, 2, numString);    
    }

    // Add the money to cash
    pDoc->m_Cash += nMoney;
    pDoc->m_Total = pDoc->m_Cash + pDoc->m_Bank - pDoc->m_Debt;

    FillStrings ();
    EnableButtons ();
  }
}
