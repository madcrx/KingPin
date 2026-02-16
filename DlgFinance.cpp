// DlgFinance.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "DWarsDoc.h"
#include "DlgFinance.h"
#include "DlgQuantity.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFinance dialog


CDlgFinance::CDlgFinance(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFinance::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFinance)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
  m_Cash = 0;
  m_Debt = 0;
  m_Bank = 0;
  m_Total = 0;
  m_bLoanGiven = FALSE;
}


void CDlgFinance::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFinance)
	DDX_Control(pDX, IDC_STATIC_TOTAL, m_TotalCtrl);
	DDX_Control(pDX, IDC_STATIC_DEBT, m_DebtCtrl);
	DDX_Control(pDX, IDC_STATIC_DAY, m_DayCtrl);
	DDX_Control(pDX, IDC_STATIC_CASH, m_CashCtrl);
	DDX_Control(pDX, IDC_STATIC_BANK, m_BankCtrl);
	DDX_Control(pDX, IDC_BUTTON_WITHDRAWL, m_WithdrawlCtrl);
	DDX_Control(pDX, IDC_BUTTON_PAYBACK, m_PaybackCtrl);
	DDX_Control(pDX, IDC_BUTTON_DEPOSIT, m_DepositCtrl);
	DDX_Control(pDX, IDC_BUTTON_BORROW, m_BorrowCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFinance, CDialog)
	//{{AFX_MSG_MAP(CDlgFinance)
	ON_BN_CLICKED(IDC_BUTTON_DEPOSIT, OnButtonDeposit)
	ON_BN_CLICKED(IDC_BUTTON_WITHDRAWL, OnButtonWithdrawl)
	ON_BN_CLICKED(IDC_BUTTON_BORROW, OnButtonBorrow)
	ON_BN_CLICKED(IDC_BUTTON_PAYBACK, OnButtonPayback)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFinance message handlers


BOOL CDlgFinance::OnInitDialog() 
{
	CDialog::OnInitDialog();

  CFrameWnd *pWnd = (CFrameWnd*)AfxGetMainWnd ();
  if (pWnd != NULL)
  {
    CDWarsDoc *pDoc = (CDWarsDoc *)pWnd->GetActiveDocument ();
    if (pDoc != NULL)
    {
      m_Cash = pDoc->m_Cash;
      m_Debt = pDoc->m_Debt;
      m_Bank = pDoc->m_Bank;
      m_Total = pDoc->m_Total;

      pDoc->PlaySoundFile (_T("Sounds\\CashReg.wav"));
    }
  }

  if (m_bLoanGiven)
  {
    m_BorrowCtrl.EnableWindow (FALSE);
  }

  LoadScreen ();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgFinance::LoadScreen ()
{
  CFrameWnd *pWnd = (CFrameWnd*)AfxGetMainWnd ();
  if (pWnd != NULL)
  {
    CDWarsDoc *pDoc = (CDWarsDoc *)pWnd->GetActiveDocument ();
    if (pDoc != NULL)
    {
      // Enable/Disable deposit button
      m_DepositCtrl.EnableWindow (m_Cash > 0);

      // Enable/Disable withdrawl button
      m_WithdrawlCtrl.EnableWindow (m_Bank > 0);

      // Enable/Disable repay loan button
      m_PaybackCtrl.EnableWindow (m_Debt > 0);

      CString temp;
      temp.Format (_T("$%d"), m_Debt);
      m_DebtCtrl.SetWindowText (temp);
      temp.Format (_T("$%d"), m_Bank);
      m_BankCtrl.SetWindowText (temp);
      temp.Format (_T("$%d"), m_Cash);
      m_CashCtrl.SetWindowText (temp);
      temp.Format (_T("$%d"), m_Total);
      m_TotalCtrl.SetWindowText (temp);
      temp.Format (_T("%d/%d"), pDoc->m_CurrentDay, pDoc->m_TotalDays);
      m_DayCtrl.SetWindowText (temp);
    }
  }
}

void CDlgFinance::OnButtonDeposit() 
{
  if (m_Cash <= 0)
  {
    return;
  }
  
  CDlgQuantity dlg;
  
  dlg.m_Fact1.Format (_T ("You have $%d in cash"), m_Cash);
  dlg.m_Question = _T("How much do you wish to deposit?");
  dlg.m_Title = _T("Deposit Money");
  dlg.m_nMin = 1;
  dlg.m_nMax = m_Cash;
  dlg.m_nNum = 1;
  
  int ret = dlg.DoModal ();
  if (IDOK == ret)
  {
    m_Cash -= dlg.m_nNum;
    m_Bank += dlg.m_nNum;
    LoadScreen ();
  }
}

void CDlgFinance::OnButtonWithdrawl() 
{
  if (m_Bank <= 0)
  {
    return;
  }
  
  CDlgQuantity dlg;
  
  dlg.m_Fact1.Format (_T ("You have $%d in the bank"), m_Bank);
  dlg.m_Question = _T("How much do you wish to withdrawl?");
  dlg.m_Title = _T("Withdrawl Money");
  dlg.m_nMin = 1;
  dlg.m_nMax = m_Bank;
  dlg.m_nNum = 1;
  
  int ret = dlg.DoModal ();
  if (IDOK == ret)
  {
    m_Cash += dlg.m_nNum;
    m_Bank -= dlg.m_nNum;
    LoadScreen ();
  }
}

void CDlgFinance::OnButtonBorrow() 
{
  long nMax = m_Cash * 30;
  if (nMax < 5500)
  {
    nMax = 5500;
  }
  
  CDlgQuantity dlg;
  
  dlg.m_Fact1.Format (_T ("You have $%d in cash and $%d in the bank"), 
    m_Cash, m_Bank);
  dlg.m_Question = _T("How much would you like to borrow?");
  dlg.m_Title = _T("Borrow Money");
  dlg.m_nMin = 1;
  dlg.m_nMax = nMax;
  dlg.m_nNum = 1;
  
  int ret = dlg.DoModal ();
  if (IDOK == ret)
  {
    m_bLoanGiven = TRUE;
    m_Cash += dlg.m_nNum;
    m_Debt += dlg.m_nNum;
    m_Total = m_Cash + m_Bank - m_Debt;
    LoadScreen ();

    m_BorrowCtrl.EnableWindow (FALSE);
  }
}

void CDlgFinance::OnButtonPayback() 
{
  if (m_Cash <= 0)
  {
    return;
  }
  
  CDlgQuantity dlg;
  
  dlg.m_Fact1.Format (_T ("You have $%d in cash and owe $%d"), m_Cash, m_Debt);
  dlg.m_Question = _T("How much do you wish to payback?");
  dlg.m_Title = _T("Payback Money");
  dlg.m_nMin = 1;
  if (m_Cash < m_Debt)
  {
    dlg.m_nMax = m_Cash;
  }
  else
  {
    dlg.m_nMax = m_Debt;
  }
  dlg.m_nNum = 1;
  
  int ret = dlg.DoModal ();
  if (IDOK == ret)
  {
    m_Cash -= dlg.m_nNum;
    m_Debt -= dlg.m_nNum;
    m_Total = m_Cash + m_Bank - m_Debt;
    LoadScreen ();
  }
}

void CDlgFinance::OnOK() 
{
  CFrameWnd *pWnd = (CFrameWnd*)AfxGetMainWnd ();
  if (pWnd != NULL)
  {
    CDWarsDoc *pDoc = (CDWarsDoc *)pWnd->GetActiveDocument ();
    if (pDoc != NULL)
    {
      pDoc->m_Cash = m_Cash;
      pDoc->m_Debt = m_Debt;
      pDoc->m_Bank = m_Bank;
      pDoc->m_Total = pDoc->m_Cash + pDoc->m_Bank - pDoc->m_Debt;
    }
  }
  
  CDialog::OnOK();
}
