// DWars.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DWars.h"
#include "Defines.h"

#include "MainFrm.h"

#include "DWarsDoc.h"
#include "DWarsView.h"

#include "PageAboutGeneral.h"
#include "PageAboutGraphics.h"
#include "PageAboutSource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

int brandom(int bot,int top)
{
  //Returns a random integer not less than bot and less than top
  return (int)((float)(top-bot)*rand()/(RAND_MAX+1.0))+bot;
}

/////////////////////////////////////////////////////////////////////////////
// CDWarsApp

BEGIN_MESSAGE_MAP(CDWarsApp, CWinApp)
	//{{AFX_MSG_MAP(CDWarsApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_FILE_EXIT, OnFileExit)
	ON_COMMAND(ID_INFO_SOUND, OnInfoSound)
	ON_UPDATE_COMMAND_UI(ID_INFO_SOUND, OnUpdateInfoSound)
	ON_COMMAND(ID_INFO_SOUND_OFF, OnInfoSoundOff)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDWarsApp construction

CDWarsApp::CDWarsApp()
	: CWinApp()
{
  m_bPlaySounds = TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDWarsApp object

CDWarsApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CDWarsApp initialization

BOOL CDWarsApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("AtomWare"));

  // Seed the random-number generator with current time so that
  // the numbers will be different every time we run.
  CTime time = CTime::GetCurrentTime();
  time_t timeStruct = time.GetTime ();
  srand( timeStruct );

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CDWarsDoc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		RUNTIME_CLASS(CDWarsView));
	AddDocTemplate(pDocTemplate);
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

  MyRegisterShellFileTypes ();

  // Read if program should generate any sounds
  int nTemp = GetProfileInt (_T("Preferences"), _T("PlaySound"), 1);
  m_bPlaySounds = (BOOL) nTemp;

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

  // Update toolbar button for sound
  CMainFrame *mainFrame = (CMainFrame *) m_pMainWnd;
  if (mainFrame != NULL)
  {
    mainFrame->ToggleSound (m_bPlaySounds);
  }

	return TRUE;
}

void CDWarsApp::MyRegisterShellFileTypes ()
{
  HKEY hKey = NULL;
  DWORD Disposition = 0;
	TCHAR szPathName[_MAX_PATH];
  CString fileTypeID = _T("DopeWars.Document");
  CString fileTypeName = _T("DopeWars Saved Game");
  DWORD dwDisposition = 0;

	::GetModuleFileName(AfxGetInstanceHandle(), szPathName, _MAX_PATH);
  CString execPathName = szPathName;
  CString execCommand = _T("\"") + execPathName + _T("\" \"%1\"");
  CString defaultIconPathName = execPathName + _T(",0");

  // Create/Open the key for the document type
  if (::RegCreateKeyEx (HKEY_CLASSES_ROOT, fileTypeID, 0, NULL, 
    0, 0, NULL, &hKey, &Disposition) == ERROR_SUCCESS)
  {
    // Set the document type's key's default value to the name of the document type
    ::RegSetValueEx (hKey, NULL, 0, REG_SZ, (const BYTE *) (LPCTSTR)fileTypeName, 
      (fileTypeName.GetLength () + 1) * sizeof (TCHAR));
  
    // Close key now that we are done with it
    ::RegCloseKey (hKey);
  }

  // Create the key for the executable path and filename to run
  CString execKeyName = fileTypeID + _T("\\Shell\\Open\\Command");
  if (::RegCreateKeyEx (HKEY_CLASSES_ROOT, execKeyName, 0, NULL, 
    0, 0, NULL, &hKey, &Disposition) == ERROR_SUCCESS)
  {
    // Set the key to the executable path and filename
    ::RegSetValueEx (hKey, NULL, 0, REG_SZ, (const BYTE *) (LPCTSTR)execCommand, 
      (execCommand.GetLength () + 1) * sizeof (TCHAR));
    
    // Close key now that we are done with it
    ::RegCloseKey (hKey);
  }

  // Create the key for the default icon path and filename
  CString iconKeyName = fileTypeID + _T("\\DefaultIcon");
  if (::RegCreateKeyEx (HKEY_CLASSES_ROOT, iconKeyName, 0, NULL, 
    0, 0, NULL, &hKey, &Disposition) == ERROR_SUCCESS)
  {
    // Set the key to the executable path and filename
    ::RegSetValueEx (hKey, NULL, 0, REG_SZ, (const BYTE *) (LPCTSTR)defaultIconPathName, 
      (defaultIconPathName.GetLength () + 1) * sizeof (TCHAR));
    
    // Close key now that we are done with it
    ::RegCloseKey (hKey);
  }

  // Need to create file extension key
  if (::RegCreateKeyEx (HKEY_CLASSES_ROOT, _T(".dop"), 0, 0, 0, 0, NULL, &hKey, &dwDisposition) 
    == ERROR_SUCCESS)
  {
    // Need to assign fileTypeID
    ::RegSetValueEx (hKey, NULL, 0, REG_SZ, (const BYTE *) (LPCTSTR) fileTypeID,
      (fileTypeID.GetLength () + 1) * sizeof (TCHAR));
    ::RegCloseKey (hKey);
  }
}

void CDWarsApp::PlaySoundFile (CString fileName)
{
  if (!m_bPlaySounds)
  {
    return;
  }

  CString filePath = fileName;
  int nPlace;

	TCHAR szBuff[_MAX_PATH];
	VERIFY(::GetModuleFileName(m_hInstance, szBuff, _MAX_PATH));

  CString directory = szBuff;
  nPlace = directory.ReverseFind (_T('\\'));
  if (nPlace != -1)
  {
    directory = directory.Left (nPlace);
    filePath = directory + _T("\\") + fileName;
  }

  ::sndPlaySound (filePath, SND_ASYNC | SND_NODEFAULT);
}

// App command to run the dialog
void CDWarsApp::OnAppAbout()
{
  CPropertySheet sheet;
  CPageAboutGeneral pageGeneral;
  CPageAboutSource pageSource;
  CPageAboutGraphics pageGraphics;

  sheet.AddPage (&pageGeneral);
  sheet.AddPage (&pageSource);
  sheet.AddPage (&pageGraphics);
  sheet.DoModal ();
}

void CDWarsApp::OnFileExit() 
{
  PostQuitMessage (1);
}

// Takes the number in "price" and prints it into the string "buffer"
// adding commas to split up thousands, and adding a currency symbol
// to the start.
void CDWarsApp::FormatPrice (long price, CString string)
{
  /*
   char text[80];
   long absprice;
   text[0]=0;

   if (price<0) 
     absprice = -price; 
   else 
     absprice = price;

   while (text[0]==0 || absprice>0) 
   {
      if (absprice >= 1000)
        sprintf (buffer,"%03d", (int)(absprice%1000l));
      else 
        sprintf(buffer,"%d", (int)(price%1000l));
      price/=1000l;
      absprice/=1000l;
      if (text[0]) 
        strcat(buffer,",");      

      strcat(buffer,text);
      strcpy(text,buffer);
   }
   strcpy(buffer,"$");
   strcat(buffer,text);
   return buffer;
*/
}

void CDWarsApp::OnInfoSound() 
{
  m_bPlaySounds = !m_bPlaySounds;
  WriteProfileInt (_T("Preferences"), _T("PlaySound"), (int)m_bPlaySounds);

  CMainFrame *mainFrame = (CMainFrame *) AfxGetMainWnd ();
  if (mainFrame != NULL)
  {
    mainFrame->ToggleSound (m_bPlaySounds);
  }
}

void CDWarsApp::OnUpdateInfoSound(CCmdUI* pCmdUI) 
{
  pCmdUI->SetCheck ((int)m_bPlaySounds);
}

void CDWarsApp::OnInfoSoundOff() 
{
  m_bPlaySounds = !m_bPlaySounds;
  WriteProfileInt (_T("Preferences"), _T("PlaySound"), (int)m_bPlaySounds);

  CMainFrame *mainFrame = (CMainFrame *) AfxGetMainWnd ();
  if (mainFrame != NULL)
  {
    mainFrame->ToggleSound (m_bPlaySounds);
  }
}
