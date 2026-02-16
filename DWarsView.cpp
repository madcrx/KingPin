// DWarsView.cpp : implementation of the CDWarsView class
//

#include "stdafx.h"
#include "DWars.h"

#include "DWarsDoc.h"
#include "DWarsView.h"

#include "DlgNewGame.h"
#include "DlgJet.h"
#include "DlgDrugs.h"
#include "DlgFinance.h"
#include "DlgScores.h"
#include "DlgGuns.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDWarsView

IMPLEMENT_DYNCREATE(CDWarsView, CFormView)

BEGIN_MESSAGE_MAP(CDWarsView, CFormView)
	//{{AFX_MSG_MAP(CDWarsView)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON_BUYSELL, OnButtonBuysell)
	ON_BN_CLICKED(IDC_BUTTON_FINANCES, OnButtonFinances)
	ON_BN_CLICKED(IDC_BUTTON_JET, OnButtonJet)
	ON_COMMAND(ID_FILE_NEWGAME, OnFileNewgame)
	ON_COMMAND(ID_INFO_HIGHSCORES, OnInfoHighscores)
	ON_BN_CLICKED(IDC_BUTTON_ENDGAME, OnButtonEndgame)
	ON_COMMAND(ID_FILE_OPENGAME, OnFileOpengame)
	ON_COMMAND(ID_FILE_SAVEASGAME, OnFileSaveasgame)
	ON_COMMAND(ID_FILE_SAVEGAME, OnFileSavegame)
	ON_BN_CLICKED(IDC_BUTTON_HOSPITAL, OnButtonHospital)
	ON_BN_CLICKED(IDC_BUTTON_GUNS, OnButtonGuns)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDWarsView construction/destruction

CDWarsView::CDWarsView()
	: CFormView(CDWarsView::IDD)
{
	//{{AFX_DATA_INIT(CDWarsView)
	m_Output = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here
  m_bInitialScreen = TRUE;
  m_pSplashScreen = NULL;

  m_Font.CreateFont(12,0,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,_T("Arial"));
}

CDWarsView::~CDWarsView()
{
}

void CDWarsView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDWarsView)
	DDX_Control(pDX, IDC_BUTTON_HOSPITAL, m_HospitalCtrl);
	DDX_Control(pDX, IDC_BUTTON_GUNS, m_GunsCtrl);
	DDX_Control(pDX, IDC_BUTTON_BUYSELL, m_BuySellCtrl);
	DDX_Control(pDX, IDC_BUTTON_ENDGAME, m_EndCtrl);
	DDX_Control(pDX, IDC_STATIC_GUNS, m_GunCtrl);
	DDX_Control(pDX, IDC_STATIC_TOTAL, m_TotalCtrl);
	DDX_Control(pDX, IDC_STATIC_HEALTH, m_HealthTextCtrl);
	DDX_Control(pDX, IDC_STATIC_DISTRICT, m_DistrictCtrl);
	DDX_Control(pDX, IDC_STATIC_DEBT, m_DebtCtrl);
	DDX_Control(pDX, IDC_STATIC_DAY, m_DayCtrl);
	DDX_Control(pDX, IDC_STATIC_CASH, m_CashCtrl);
	DDX_Control(pDX, IDC_STATIC_BANK, m_BankCtrl);
	DDX_Control(pDX, IDC_EDIT_OUTPUT, m_OutputCtrl);
	DDX_Control(pDX, IDC_BUTTON_JET, m_JetCtrl);
	DDX_Control(pDX, IDC_BUTTON_FINANCES, m_FinanceCtrl);
	DDX_Control(pDX, IDC_PROGRESS_HEALTH, m_HealthCtrl);
	DDX_Text(pDX, IDC_EDIT_OUTPUT, m_Output);
	//}}AFX_DATA_MAP
}

BOOL CDWarsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CDWarsView::OnInitialUpdate() 
{
  CFormView::OnInitialUpdate();
  
  m_OutputCtrl.SetFont (&m_Font);

  // it may seem a bit crazy to do this extra check here,
  // but in the case of a file opened from a file browser, 
  // the other checks do not get hit
  CDWarsDoc* pDoc = GetDocument();
  if (pDoc == NULL)
  {
    return;
  }

  // See if number of days is up
  if (pDoc->m_CurrentDay == pDoc->m_TotalDays)
  {
    m_JetCtrl.ShowWindow (SW_HIDE);
    m_EndCtrl.ShowWindow (SW_SHOW);
  }
}

void CDWarsView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
  m_OutputCtrl.SetWindowText (m_Output);
  LoadScreen ();
}

/////////////////////////////////////////////////////////////////////////////
// CDWarsView diagnostics

#ifdef _DEBUG
void CDWarsView::AssertValid() const
{
	CFormView::AssertValid();
}

void CDWarsView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CDWarsDoc* CDWarsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDWarsDoc)));
	return (CDWarsDoc*)m_pDocument;
}
#endif //_DEBUG

void CDWarsView::SetOutputText (CString text)
{
  m_OutputCtrl.SetWindowText (text);
}

void CDWarsView::AddOutputText (CString text)
{
  CString temp;
  m_OutputCtrl.GetWindowText (temp);
  temp += text;
  m_OutputCtrl.SetWindowText (temp);
}

void CDWarsView::LoadScreen ()
{
  CDWarsDoc* pDoc = GetDocument();
  if (pDoc == NULL)
  {
    return;
  }

  if (m_bInitialScreen)
  {
    // Not in a game yet, so don't show anything
    m_DistrictCtrl.SetWindowText (_T(""));
    m_DebtCtrl.SetWindowText (_T(""));
    m_BankCtrl.SetWindowText (_T(""));
    m_CashCtrl.SetWindowText (_T(""));
    m_TotalCtrl.SetWindowText (_T(""));
    m_DayCtrl.SetWindowText (_T(""));
    m_HealthTextCtrl.SetWindowText (_T(""));
    m_HealthCtrl.SetPos (100);
    m_GunCtrl.SetWindowText (_T(""));

    m_JetCtrl.EnableWindow (FALSE);
    m_FinanceCtrl.EnableWindow (FALSE);
    m_GunsCtrl.EnableWindow (FALSE);
    m_HospitalCtrl.EnableWindow (FALSE);
    m_BuySellCtrl.EnableWindow (FALSE);

    if (m_pSplashScreen == NULL)
    {
      m_pSplashScreen = new CSplashScreen ();
      if (m_pSplashScreen != NULL)
      {
        CRect rect;
        GetClientRect (&rect);
        m_pSplashScreen->Create (NULL, _T("DWarsSplashScreen"), 
          WS_CHILD | WS_VISIBLE, rect, this, 32, NULL);
        m_pSplashScreen->BringWindowToTop ();
        m_pSplashScreen->Invalidate ();
      }
    }

    return;
  }
  else
  {
    // See if at bank/loan area
    m_FinanceCtrl.EnableWindow (pDoc->m_Location == 0);

    // See if at gun shop location
    m_GunsCtrl.EnableWindow ((pDoc->m_Location == 1));

    // See if at hospital location
    m_HospitalCtrl.EnableWindow ((pDoc->m_Location == 6));

    m_JetCtrl.EnableWindow (TRUE);
    m_BuySellCtrl.EnableWindow (TRUE);
  }
  
  CString temp;
  m_DistrictCtrl.SetWindowText (pDoc->m_LocationList [pDoc->m_Location].Name);
  temp.Format (_T("$%d"), pDoc->m_Debt);
  m_DebtCtrl.SetWindowText (temp);
  temp.Format (_T("$%d"), pDoc->m_Bank);
  m_BankCtrl.SetWindowText (temp);
  temp.Format (_T("$%d"), pDoc->m_Cash);
  m_CashCtrl.SetWindowText (temp);
  temp.Format (_T("$%d"), pDoc->m_Total);
  m_TotalCtrl.SetWindowText (temp);
  temp.Format (_T("%d/%d"), pDoc->m_CurrentDay, pDoc->m_TotalDays);
  m_DayCtrl.SetWindowText (temp);
  temp.Format (_T("%d"), pDoc->m_Health);
  m_HealthTextCtrl.SetWindowText (temp);
  m_HealthCtrl.SetPos (pDoc->m_Health);
  temp.Format (_T("%d"), pDoc->m_NumGuns);
  m_GunCtrl.SetWindowText (temp);
}

/////////////////////////////////////////////////////////////////////////////
// CDWarsView message handlers

void CDWarsView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
  ModifyStyle (WS_VSCROLL | WS_HSCROLL, NULL);
}


void CDWarsView::OnButtonBuysell() 
{
  CDWarsDoc* pDoc = GetDocument();
  if (pDoc == NULL)
  {
    return;
  }

  CDlgDrugs dlg;
  dlg.DoModal ();

  // Check to make sure player is still alive
  if (pDoc->m_Health <= 0)
  {
    CString message = pDoc->FinishGame ();
    if (message != _T(""))
    {
      AfxMessageBox (message);
    }

    CDlgScores dlg;
    dlg.DoModal ();

    pDoc->m_bShowExit = TRUE;
 
    OnFileNewgame ();
    return;
  }

  LoadScreen ();
}

void CDWarsView::OnButtonFinances() 
{
  CDWarsDoc* pDoc = GetDocument();
  if (pDoc == NULL)
  {
    return;
  }

  CDlgFinance dlg;
  
  dlg.m_bLoanGiven = !pDoc->m_bMakeLoan;

  int ret = dlg.DoModal ();
  
  if (IDOK == ret)
  {
    LoadScreen ();

    pDoc->m_bMakeLoan = !dlg.m_bLoanGiven;
  }
}

void CDWarsView::OnButtonJet() 
{
  CDWarsDoc* pDoc = GetDocument();
  if (pDoc == NULL)
  {
    return;
  }

  CDlgJet dlg;
  dlg.m_Place = _T("Current Location:   ");
  dlg.m_Place += pDoc->m_LocationList [pDoc->m_Location].Name;

  int ret = dlg.DoModal ();

  if (IDOK == ret)
  {
    // Reset output screen
    m_OutputCtrl.SetWindowText (_T(""));
    
    // Start a new day
    pDoc->NewDay (dlg.m_nLocation);

    // Check to make sure player is still alive
    if (pDoc->m_Health <= 0)
    {
      CString message = pDoc->FinishGame ();
      if (message != _T(""))
      {
        AfxMessageBox (message);
      }

      CDlgScores dlg;
      dlg.DoModal ();

      pDoc->m_bShowExit = TRUE;
 
      OnFileNewgame ();
      return;
    }

    // Load the values behind the screen ctrls
    LoadScreen ();

    // See if at bank/loan area
    m_FinanceCtrl.EnableWindow (pDoc->m_Location == 0);

    // See if at gun shop location
    m_GunsCtrl.EnableWindow ((pDoc->m_Location == 1));

    // See if at hospital location
    m_HospitalCtrl.EnableWindow ((pDoc->m_Location == 6));

    // See if number of days is up
    if (pDoc->m_CurrentDay >= pDoc->m_TotalDays)
    {
      m_JetCtrl.ShowWindow (SW_HIDE);
      m_EndCtrl.ShowWindow (SW_SHOW);
    }
    else if ((pDoc->m_CurrentDay + 1) == pDoc->m_TotalDays)
    {
      AfxMessageBox (_T("You have only one day left!"));
    }
  }
}

void CDWarsView::OnFileNewgame() 
{
  CDWarsDoc* pDoc = GetDocument();
  if (pDoc == NULL)
  {
    return;
  }

  CDlgNewGame dlg;
  dlg.m_bShowExit = pDoc->m_bShowExit;

  int ret = dlg.DoModal ();
  if (IDOK == ret)
  {
    pDoc->m_Location = dlg.m_nLocation;

    // Set the document's file
    pDoc->SetPathName (_T("Nicky is the world's best dog!")); // Can not just set it to _T("")

    // Reset output screen
    m_OutputCtrl.SetWindowText (_T(""));

    pDoc->FirstDay ();

    // Allow display of values
    m_bInitialScreen = FALSE;

    // Destroy splash screen
    if (m_pSplashScreen != NULL)
    {
      if (m_pSplashScreen->m_hWnd)
      {
        m_pSplashScreen->DestroyWindow ();
      }
      delete m_pSplashScreen;
      m_pSplashScreen = NULL;
    }

    LoadScreen ();

    // See if at bank/loan area
    m_FinanceCtrl.EnableWindow (pDoc->m_Location == 0);

    // See if at gun shop location
    m_GunsCtrl.EnableWindow ((pDoc->m_Location == 1));

    // See if at hospital location
    m_HospitalCtrl.EnableWindow ((pDoc->m_Location == 6));

    m_JetCtrl.ShowWindow (SW_SHOW);
    m_EndCtrl.ShowWindow (SW_HIDE);

    // Push down SIP entry box
    ::SHSipPreference (m_hWnd, SIP_DOWN);
  }
  else if (IDCANCEL == ret)
  {
    if (pDoc->m_bShowExit)
    {
      PostQuitMessage (1);
    }
  }
}

void CDWarsView::OnInfoHighscores() 
{
  CDlgScores dlg;
  dlg.DoModal ();
}

void CDWarsView::OnButtonEndgame() 
{
  CDWarsDoc* pDoc = GetDocument();
  if (pDoc != NULL)
  {
    CString message = pDoc->FinishGame ();
    if (message != _T(""))
    {
      AfxMessageBox (message);
    }
  }

  CDlgScores dlg;
  dlg.DoModal ();

  pDoc->m_bShowExit = TRUE;

  OnFileNewgame ();
}

void CDWarsView::OnFileOpengame() 
{
  CDWarsDoc* pDoc = GetDocument();
  if (pDoc == NULL)
  {
    return;
  }

  // Create open file dialog
  CFileDialog dlg (TRUE, NULL, NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST, 
    _T("DopeWars File (*.dop)|*.dop||"));

  int ret = dlg.DoModal ();
  if (IDOK == ret)
  {
    CString filePathName;
    filePathName = dlg.GetPathName ();

    // Open the file
    CFile file;
    if( !file.Open (filePathName, CFile::modeRead)) 
    {
#ifdef _DEBUG
      afxDump << "Unable to open file" << "\n";
      return;
#endif
    }
    
    // Set the document's file
    pDoc->SetPathName (filePathName);

    // Open archive for this file
    CArchive ar (&file, CArchive::load);
    pDoc->Serialize (ar);

    // Allow display of values
    m_bInitialScreen = FALSE;

    // Destroy splash screen
    if (m_pSplashScreen != NULL)
    {
      if (m_pSplashScreen->m_hWnd)
      {
        m_pSplashScreen->DestroyWindow ();
      }
      delete m_pSplashScreen;
      m_pSplashScreen = NULL;
    }

    // Refresh values on screen
    LoadScreen ();

    // See if at bank/loan area
    m_FinanceCtrl.EnableWindow (pDoc->m_Location == 0);

    // See if at gun shop location
    m_GunsCtrl.EnableWindow ((pDoc->m_Location == 1));

    // See if at hospital location
    m_HospitalCtrl.EnableWindow ((pDoc->m_Location == 6));

    // See if number of days is up
    if (pDoc->m_CurrentDay == pDoc->m_TotalDays)
    {
      m_JetCtrl.ShowWindow (SW_HIDE);
      m_EndCtrl.ShowWindow (SW_SHOW);
    }
    else if ((pDoc->m_CurrentDay + 1) == pDoc->m_TotalDays)
    {
      AfxMessageBox (_T("You have only one day left!"));
      m_JetCtrl.ShowWindow (SW_SHOW);
      m_EndCtrl.ShowWindow (SW_HIDE);
    }
    else
    {
      m_JetCtrl.ShowWindow (SW_SHOW);
      m_EndCtrl.ShowWindow (SW_HIDE);
    }
  }
}

void CDWarsView::OnFileSavegame() 
{
  CDWarsDoc* pDoc = GetDocument();
  if (pDoc == NULL)
  {
    return;
  }

  // get the file for this game.  If this is the first save, then filePathName will 
  // equal "".  If the user has chosen to start a new game, then
  // filePathName will equal "Nicky is the world's best dog!".  SetPathName will not
  // allow the file to be set to "", so something else had to be chosen
  CString filePathName = _T("Nicky is the world's best dog!");
  filePathName = pDoc->GetPathName ();
  if (filePathName == _T("") || filePathName == _T("Nicky is the world's best dog!"))
  {
    OnFileSaveasgame ();
    return;
  }
  
  // Open the file
  CFile file;
  if( !file.Open( filePathName, CFile::modeCreate | CFile::modeWrite ) ) 
  {
#ifdef _DEBUG
    afxDump << "Unable to open file" << "\n";
    return;
#endif
  }
  
  // Open archive for this file
  CArchive ar (&file, CArchive::store);
  pDoc->Serialize (ar);
}

void CDWarsView::OnFileSaveasgame() 
{
  CDWarsDoc* pDoc = GetDocument();
  if (pDoc == NULL)
  {
    return;
  }

  // Create save as file dialog
  CFileDialog dlg (FALSE, _T("dop"), NULL, OFN_OVERWRITEPROMPT, 
    _T("DopeWars File (*.dop)|*.dop||"));
  
  CString filePathName;
  int ret = dlg.DoModal ();
  if (IDOK == ret)
  {
    filePathName = dlg.GetPathName ();

    // Open the file
    CFile file;
    if( !file.Open( filePathName, CFile::modeCreate | CFile::modeWrite ) ) 
    {
  #ifdef _DEBUG
      afxDump << "Unable to open file" << "\n";
      return;
  #endif
    }
  
    // Set the document's file
    pDoc->SetPathName (filePathName);

    // Open archive for this file
    CArchive ar (&file, CArchive::store);
    pDoc->Serialize (ar);
  }
}

void CDWarsView::OnButtonHospital() 
{
  CDWarsDoc* pDoc = GetDocument();
  if (pDoc == NULL)
  {
    return;
  }

  pDoc->PlaySoundFile (_T("Sounds\\Hospital.wav"));

  if (pDoc->m_Health >= 100)
  {
    AfxMessageBox (_T("You are at full health already"));
    return;
  }

  // Figure out doctor fee
  int nMoney = brandom (1000, (2000 - (5 * pDoc->m_Health)));
  if (pDoc->m_Cash < nMoney)
  {
    AfxMessageBox (_T("You do not have enough money to get fixed up"));
    return;
  }

  CString text;
  text.Format (_T("Do you pay a doctor $%d to sew you up?"), nMoney);
  int ret = AfxMessageBox (text, MB_YESNO);
  if (ret == IDYES)
  {
    pDoc->m_Health = 100;
    pDoc->m_Cash -= nMoney;
    pDoc->m_Total = pDoc->m_Cash + pDoc->m_Bank - pDoc->m_Debt;

    // Load the values behind the screen ctrls
    LoadScreen ();
  }
}

void CDWarsView::OnButtonGuns() 
{
  CDlgGuns dlg;
  dlg.DoModal ();

  // Load the values behind the screen ctrls
  LoadScreen ();
}
