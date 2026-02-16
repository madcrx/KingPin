// DlgDrugs.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "DlgDrugs.h"

#include "DWarsDoc.h"
#include "DlgQuantity.h"
#include "DlgSelling.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDrugs dialog


CDlgDrugs::CDlgDrugs(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDrugs::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDrugs)
	m_Coat = _T("");
	m_Money = _T("");
	//}}AFX_DATA_INIT
}


void CDlgDrugs::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDrugs)
	DDX_Control(pDX, IDC_LIST_SELL, m_ListSellCtrl);
	DDX_Control(pDX, IDC_LIST_BUY, m_ListBuyCtrl);
	DDX_Text(pDX, IDC_STATIC_COAT, m_Coat);
	DDX_Text(pDX, IDC_STATIC_MONEY, m_Money);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDrugs, CDialog)
	//{{AFX_MSG_MAP(CDlgDrugs)
	ON_BN_CLICKED(IDC_BUTTON_BUY, OnButtonBuy)
	ON_BN_CLICKED(IDC_BUTTON_DUMP, OnButtonDump)
	ON_BN_CLICKED(IDC_BUTTON_SELL, OnButtonSell)
  ON_NOTIFY ( NM_CUSTOMDRAW, IDC_LIST_BUY, OnCustomDrawBuyList )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDrugs message handlers

BOOL CDlgDrugs::OnInitDialog() 
{
	CDialog::OnInitDialog();

  // Insert Columns
  m_ListBuyCtrl.InsertColumn (0, _T("Drug"), LVCFMT_LEFT, 49);
  m_ListBuyCtrl.InsertColumn (1, _T("Price"), LVCFMT_RIGHT, 51);
  m_ListSellCtrl.InsertColumn (0, _T("Drug"), LVCFMT_LEFT, 49);
  m_ListSellCtrl.InsertColumn (1, _T("Qty"), LVCFMT_CENTER, 33);
  m_ListSellCtrl.InsertColumn (2, _T("Price"), LVCFMT_RIGHT, 51);

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

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgDrugs::FillLists ()
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

  for (int i = 0; i < NUM_DRUGS; i++)
  {
    if (pDoc->m_DrugPrices [i] != 0) // Is here
    {
      // Add the drug name to the list
      m_ListBuyCtrl.InsertItem (count, pDoc->m_DrugList [i].Name);

      // Add the price to the list
      numString.Format (_T("%d"), pDoc->m_DrugPrices [i]);
      m_ListBuyCtrl.SetItemText (count, 1, numString);

      count++;
    }
  }

  count = 0;

  for (i = 0; i < NUM_DRUGS; i++)
  {
    if (pDoc->m_Drugs [i].Number != 0)
    {
      // Add the drug name to the list
      m_ListSellCtrl.InsertItem (count, pDoc->m_DrugList [i].Name);

      // Add the quantity to the list
      numString.Format (_T("%d"), pDoc->m_Drugs [i].Number);
      m_ListSellCtrl.SetItemText (count, 1, numString);

      // Add the price to the list
      numString.Format (_T("%d"), pDoc->m_Drugs [i].Price);
      m_ListSellCtrl.SetItemText (count, 2, numString);

      count++;
    }
  }
}

void CDlgDrugs::FillStrings ()
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

void CDlgDrugs::OnButtonBuy() 
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
  int nDrugPosition = -1;
  for (int i = 0; i < NUM_DRUGS; i++)
  {
    if (pDoc->m_DrugList [i].Name == text)
    {
      nDrugPosition = i;
    }
  }

  if (nDrugPosition == -1)
  {
    // Not found
    return;
  }
 
  int nMax = 0, nSpace = 0;
  CString Fact1;
  nMax = (int) pDoc->m_Cash / pDoc->m_DrugPrices [nDrugPosition];
  nSpace = pDoc->m_CoatSize - pDoc->m_CoatUsed;

  if (nMax <= 0)
  {
    AfxMessageBox (_T("You can not afford this drug"));
    return;
  }
  if (nSpace <= 0)
  {
    AfxMessageBox (_T("You have no more room!"));
    return;
  }
  
  // Cap max amount by coat space
  if (nSpace < nMax)
  {
    nMax = nSpace;
  }

  Fact1.Format (_T("You can afford %d\nYou have enough room for %d"), nMax, nSpace);

  CDlgQuantity dlg;

  dlg.m_Fact1 = Fact1;
  dlg.m_Question = _T("How many do you buy?");
  dlg.m_Title = _T("Buy Drugs");
  dlg.m_nMin = 1;
  dlg.m_nMax = nMax;
  dlg.m_nNum = 1;

  int ret = dlg.DoModal ();
  if (IDOK == ret)
  {
    long nMoney = 0;

    // Remove the cost from cash
    nMoney = dlg.m_nNum * pDoc->m_DrugPrices [nDrugPosition];
    pDoc->m_Cash -= nMoney;
    pDoc->m_Total = pDoc->m_Cash + pDoc->m_Bank - pDoc->m_Debt;

    // Adjust the price of the drug in the player's inventory
    int nTotalInv = pDoc->m_Drugs [nDrugPosition].Price * 
      pDoc->m_Drugs [nDrugPosition].Number;
    int nTotalPurchase = pDoc->m_DrugPrices [nDrugPosition] * dlg.m_nNum;

    pDoc->m_Drugs [nDrugPosition].Price = 
      (nTotalInv + nTotalPurchase) / 
      (pDoc->m_Drugs [nDrugPosition].Number + dlg.m_nNum);

    // Add drug quantity to player's inventory
    pDoc->m_Drugs [nDrugPosition].Number += dlg.m_nNum;

    // Add quantity to coat filled space
    pDoc->m_CoatUsed += dlg.m_nNum;

    FillStrings ();
    FillLists ();
  }
}

void CDlgDrugs::OnButtonDump() 
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
  int nDrugPosition = -1;
  for (int i = 0; i < NUM_DRUGS; i++)
  {
    if (pDoc->m_DrugList [i].Name == text)
    {
      nDrugPosition = i;
    }
  }

  if (nDrugPosition == -1)
  {
    // Not found
    return;
  }

  CDlgQuantity dlg;

  CString Fact1;
  Fact1.Format (_T("\nYou are carrying %d"), pDoc->m_Drugs [nDrugPosition].Number);
  dlg.m_Fact1 = Fact1;
  dlg.m_Question = _T("How many do you drop?");
  dlg.m_Title = _T("Drop Drugs");
  dlg.m_nMin = 1;
  dlg.m_nMax = pDoc->m_Drugs [nDrugPosition].Number;
  dlg.m_nNum = 1;

  int ret = dlg.DoModal ();
  if (IDOK == ret)
  {
    pDoc->PlaySoundFile (_T("Sounds\\dump.wav"));

    int nQuantity = min (pDoc->m_Drugs [nDrugPosition].Number, dlg.m_nNum);

    // Remove drugs from inventory
    pDoc->m_Drugs [nDrugPosition].Number -= nQuantity;

    // Remove quantity from coat filled space
    pDoc->m_CoatUsed -= nQuantity;

    if (pDoc->m_Drugs [nDrugPosition].Number <= 0)
    {
      pDoc->m_Drugs [nDrugPosition].Number = 0;
      pDoc->m_Drugs [nDrugPosition].Price = 0;

      m_ListSellCtrl.DeleteItem (nSelection);
    }
    else
    {
      CString numString;
      numString.Format (_T("%d"), pDoc->m_Drugs [nDrugPosition].Number);
      m_ListSellCtrl.SetItemText (nSelection, 1, numString);    
    }

    FillStrings ();

    // Check to see if the cops spot you dropping drugs
    if (brandom (0, 100) < pDoc->m_CopInfo.DropProb)
    {
      CString loneStr, deputyStr;
      loneStr.Format (_T("Officer %%s spots you dropping %s, and chases you!"), 
        pDoc->m_DrugList [nDrugPosition].Name);
      deputyStr.Format (_T("Officer %%s and %%d of his deputies spot you dropping %s, and chase you!"),
        pDoc->m_DrugList [nDrugPosition].Name);
      
      pDoc->StartOfficerHardAss (loneStr, deputyStr);

      if (pDoc->m_Health <= 0)
      {
        CDialog::OnCancel ();
      }
    }
  }
}

void CDlgDrugs::OnButtonSell() 
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
  int nDrugPosition = -1;
  for (int i = 0; i < NUM_DRUGS; i++)
  {
    if (pDoc->m_DrugList [i].Name == text)
    {
      nDrugPosition = i;
    }
  }

  if (nDrugPosition == -1)
  {
    // Not found
    return;
  }

  CDlgSelling dlg;

  CString Fact1;
  Fact1.Format (_T("You are carrying %d"), pDoc->m_Drugs [nDrugPosition].Number);
  dlg.m_Fact1 = Fact1;
  dlg.m_nMin = 1;
  dlg.m_nMax = pDoc->m_Drugs [nDrugPosition].Number;
  dlg.m_nNum = 1;
  dlg.m_nBoughtPrice = pDoc->m_Drugs [nDrugPosition].Price;
  dlg.m_nCurPrice = pDoc->m_DrugPrices [nDrugPosition];
  dlg.m_Profit.Format (_T("$%d"), (dlg.m_nCurPrice - dlg.m_nBoughtPrice));
  dlg.m_Worth.Format (_T("$%d"), dlg.m_nCurPrice);

  int ret = dlg.DoModal ();
  if (IDOK == ret)
  {
    long nQuantity = min (pDoc->m_Drugs [nDrugPosition].Number, dlg.m_nNum);
    long nMoney = nQuantity * pDoc->m_DrugPrices [nDrugPosition];

    // Remove drugs from inventory
    pDoc->m_Drugs [nDrugPosition].Number -= nQuantity;

    // Remove quantity from coat filled space
    pDoc->m_CoatUsed -= nQuantity;

    if (pDoc->m_Drugs [nDrugPosition].Number <= 0)
    {
      pDoc->m_Drugs [nDrugPosition].Number = 0;
      pDoc->m_Drugs [nDrugPosition].Price = 0;

      m_ListSellCtrl.DeleteItem (nSelection);
    }
    else
    {
      CString numString;
      numString.Format (_T("%d"), pDoc->m_Drugs [nDrugPosition].Number);
      m_ListSellCtrl.SetItemText (nSelection, 1, numString);    
    }

    // Add the money to cash
    pDoc->m_Cash += nMoney;
    pDoc->m_Total = pDoc->m_Cash + pDoc->m_Bank - pDoc->m_Debt;

    FillStrings ();
  }
}

void CDlgDrugs::OnCustomDrawBuyList ( NMHDR* pNMHDR, LRESULT* pResult )
{
  NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
  
  // Take the default processing unless we set this to something else below.
  *pResult = CDRF_DODEFAULT;
  
  // First thing - check the draw stage. If it's the control's prepaint
  // stage, then tell Windows we want messages for every item.
  
  if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
  {
    *pResult = CDRF_NOTIFYITEMDRAW;
  }
  else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
  {
    // This is the prepaint stage for an item. Here's where we set the
    // item's text color. Our return value will tell Windows to draw the
    // item itself, but it will use the new color we set here.
    // Drugs that were special and cheap are red, special and expensive are blue

    COLORREF crText;
    crText = RGB (0, 0, 0);

    CDWarsDoc *pDoc = NULL;
    CFrameWnd *pWnd = (CFrameWnd*)AfxGetMainWnd ();
    if (pWnd != NULL)
    {
      pDoc = (CDWarsDoc *)pWnd->GetActiveDocument ();
      if (pDoc != NULL)
      {
        CString text = m_ListBuyCtrl.GetItemText (pLVCD->nmcd.dwItemSpec, 0);
        int nDrugPosition = -1;
        for (int i = 0; i < NUM_DRUGS; i++)
        {
          if (pDoc->m_DrugList [i].Name == text)
          {
            nDrugPosition = i;
          }
        }

        if (nDrugPosition != -1)
        {
          if (pDoc->m_DrugSpecials [nDrugPosition] == 1)
          {
            crText = RGB (0, 0, 255);
          }
          else if (pDoc->m_DrugSpecials [nDrugPosition] == 2)
          {
            crText = RGB (255, 0, 0);
          }    
        }
      }
    }

    // Store the color back in the NMLVCUSTOMDRAW struct.
    pLVCD->clrText = crText;
    
    // Tell Windows to paint the control itself.
    *pResult = CDRF_DODEFAULT;
  }
}