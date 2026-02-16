// DlgQuantity.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "DlgQuantity.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgQuantity dialog


CDlgQuantity::CDlgQuantity(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgQuantity::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgQuantity)
	m_nNum = 0;
	m_Question = _T("");
	m_Fact1 = _T("");
	//}}AFX_DATA_INIT

  m_nMin = 1;
  m_nMax = 1;
}


void CDlgQuantity::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgQuantity)
	DDX_Control(pDX, IDC_SLIDER_AMOUNT, m_AmountCtrl);
	DDX_Text(pDX, IDC_EDIT_NUM, m_nNum);
	DDV_MinMaxInt(pDX, m_nNum, m_nMin, m_nMax);
	DDX_Text(pDX, IDC_STATIC_QUESTION, m_Question);
	DDX_Text(pDX, IDC_STATIC_FACT1, m_Fact1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgQuantity, CDialog)
	//{{AFX_MSG_MAP(CDlgQuantity)
	ON_BN_CLICKED(IDC_BUTTON_MAX, OnButtonMax)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_NUM, OnChangeEditNum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgQuantity message handlers

BOOL CDlgQuantity::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
  m_AmountCtrl.SetRange (m_nMin, m_nMax);	
  SetWindowText (m_Title);

  // Bring up SIP entry box
  ::SHSipPreference (m_hWnd, SIP_UP);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgQuantity::OnButtonMax() 
{
  m_AmountCtrl.SetPos (m_nMax);
  m_nNum = m_nMax;
  UpdateData (FALSE);
}

void CDlgQuantity::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
  // Get position from bar
  int pos = m_AmountCtrl.GetPos ();
  if (pos <= m_nMax && pos >= m_nMin)
  {
    m_nNum = pos;
    UpdateData (FALSE);
  }
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDlgQuantity::OnChangeEditNum() 
{
  UpdateData ();

  m_AmountCtrl.SetPos (m_nNum);
}
