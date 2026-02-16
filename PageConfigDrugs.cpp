// PageConfigDrugs.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "PageConfigDrugs.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageConfigDrugs property page

IMPLEMENT_DYNCREATE(CPageConfigDrugs, CPropertyPage)

CPageConfigDrugs::CPageConfigDrugs() : CPropertyPage(CPageConfigDrugs::IDD)
{
	//{{AFX_DATA_INIT(CPageConfigDrugs)
	m_bCheap = FALSE;
	m_bExpensive = FALSE;
	m_CheapStr = _T("");
	m_nMax = 0;
	m_nMin = 0;
	m_NameStr = _T("");
	//}}AFX_DATA_INIT

  m_nCurSelection = 0;

}

CPageConfigDrugs::~CPageConfigDrugs()
{
}

void CPageConfigDrugs::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageConfigDrugs)
	DDX_Control(pDX, IDC_LIST_DRUG_NUM, m_DrugNumList);
	DDX_Check(pDX, IDC_CHECK_CHEAP, m_bCheap);
	DDX_Check(pDX, IDC_CHECK_EXPENSIVE, m_bExpensive);
	DDX_Text(pDX, IDC_EDIT_CHEAP_STRING, m_CheapStr);
	DDX_Text(pDX, IDC_EDIT_MAX_PRICE, m_nMax);
	DDX_Text(pDX, IDC_EDIT_MIN_PRICE, m_nMin);
	DDX_Text(pDX, IDC_EDIT_NAME, m_NameStr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageConfigDrugs, CPropertyPage)
	//{{AFX_MSG_MAP(CPageConfigDrugs)
	ON_LBN_SELCHANGE(IDC_LIST_DRUG_NUM, OnSelchangeListDrugNum)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageConfigDrugs message handlers
BOOL CPageConfigDrugs::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
  CString temp;
  for (int i = 0; i < NUM_DRUGS; i++)
  {
    temp.Format (_T("Drug #%d"), i+1);
    m_DrugNumList.AddString (temp);
  }

  m_DrugNumList.SetCurSel (0);

  m_NameStr = m_DrugList [0].Name;
  m_nMax = m_DrugList [0].MaxPrice;
  m_nMin = m_DrugList [0].MinPrice;
  m_bCheap = m_DrugList [0].Cheap;
  m_bExpensive = m_DrugList [0].Expensive;
  m_CheapStr = m_DrugList [0].CheapStr;

  m_nCurSelection = 0;

  UpdateData (FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CPageConfigDrugs::OnSelchangeListDrugNum() 
{
  UpdateData ();

	m_DrugList [m_nCurSelection].Name = m_NameStr;
  m_DrugList [m_nCurSelection].MaxPrice = m_nMax; 
  m_DrugList [m_nCurSelection].MinPrice = m_nMin;
  m_DrugList [m_nCurSelection].Cheap = m_bCheap;
  m_DrugList [m_nCurSelection].Expensive = m_bExpensive;
  m_DrugList [m_nCurSelection].CheapStr = m_CheapStr;

  int i = m_DrugNumList.GetCurSel ();
  m_nCurSelection = i;
	m_NameStr = m_DrugList [i].Name;
  m_nMax = m_DrugList [i].MaxPrice;
  m_nMin = m_DrugList [i].MinPrice;
  m_bCheap = m_DrugList [i].Cheap;
  m_bExpensive = m_DrugList [i].Expensive;
  m_CheapStr = m_DrugList [i].CheapStr;

  UpdateData (FALSE);
}

BOOL CPageConfigDrugs::OnKillActive() 
{
  UpdateData ();

	m_DrugList [m_nCurSelection].Name = m_NameStr;
  m_DrugList [m_nCurSelection].MaxPrice = m_nMax; 
  m_DrugList [m_nCurSelection].MinPrice = m_nMin;
  m_DrugList [m_nCurSelection].Cheap = m_bCheap;
  m_DrugList [m_nCurSelection].Expensive = m_bExpensive;
  m_DrugList [m_nCurSelection].CheapStr = m_CheapStr;
	
	return CPropertyPage::OnKillActive();
}
