// DlgSelling.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "DlgSelling.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSelling dialog


CDlgSelling::CDlgSelling(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelling::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSelling)
	m_Fact1 = _T("");
	m_Profit = _T("");
	m_nNum = 0;
	m_Worth = _T("");
	//}}AFX_DATA_INIT

  m_nMin = 1;
  m_nMax = 1;
  m_nCurPrice = 0;
  m_nBoughtPrice = 0;
}


void CDlgSelling::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelling)
	DDX_Control(pDX, IDC_SLIDER_AMOUNT, m_AmountCtrl);
	DDX_Text(pDX, IDC_STATIC_FACT1, m_Fact1);
	DDX_Text(pDX, IDC_STATIC_PROFIT, m_Profit);
	DDX_Text(pDX, IDC_EDIT_NUM, m_nNum);
	DDV_MinMaxInt(pDX, m_nNum, m_nMin, m_nMax);
	DDX_Text(pDX, IDC_STATIC_WORTH, m_Worth);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelling, CDialog)
	//{{AFX_MSG_MAP(CDlgSelling)
	ON_BN_CLICKED(IDC_BUTTON_MAX, OnButtonMax)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_NUM, OnChangeEditNum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSelling message handlers

BOOL CDlgSelling::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
  m_AmountCtrl.SetRange (m_nMin, m_nMax);	

  // Bring up SIP entry box
  ::SHSipPreference (m_hWnd, SIP_UP);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSelling::OnButtonMax() 
{
  m_AmountCtrl.SetPos (m_nMax);
  m_nNum = m_nMax;
  int nWorth = m_nNum * m_nCurPrice;
  int nProfit = (m_nNum * m_nCurPrice) - (m_nNum * m_nBoughtPrice);
  m_Worth.Format (_T("$%d"), nWorth);
  m_Profit.Format (_T("$%d"), nProfit);

  UpdateData (FALSE);
}

void CDlgSelling::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
  // Get position from bar
  int pos = m_AmountCtrl.GetPos ();
  if (pos <= m_nMax && pos >= m_nMin)
  {
    m_nNum = pos;

    int nWorth = m_nNum * m_nCurPrice;
    int nProfit = (m_nNum * m_nCurPrice) - (m_nNum * m_nBoughtPrice);
    m_Worth.Format (_T("$%d"), nWorth);
    m_Profit.Format (_T("$%d"), nProfit);

    UpdateData (FALSE);
  }
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDlgSelling::OnChangeEditNum() 
{
  UpdateData ();

  m_AmountCtrl.SetPos (m_nNum);

  int nWorth = m_nNum * m_nCurPrice;
  int nProfit = (m_nNum * m_nCurPrice) - (m_nNum * m_nBoughtPrice);
  m_Worth.Format (_T("$%d"), nWorth);
  m_Profit.Format (_T("$%d"), nProfit);

  UpdateData (FALSE);
}
