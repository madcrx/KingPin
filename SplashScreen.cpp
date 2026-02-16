// SplashScreen.cpp : implementation file
//
#include "stdafx.h"
#include "resource.h"
#include "SplashScreen.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSplashScreen

CSplashScreen::CSplashScreen()
{
  m_Bitmap.LoadBitmap (IDB_SPLASH);
}

CSplashScreen::~CSplashScreen()
{
}


BEGIN_MESSAGE_MAP(CSplashScreen, CWnd)
	//{{AFX_MSG_MAP(CSplashScreen)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSplashScreen message handlers

void CSplashScreen::OnPaint() 
{
  CPaintDC dc(this); // device context for painting
  
  CRect rect;

  // Cover background
  GetClientRect (&rect);
  dc.FillSolidRect (&rect, RGB (0, 0, 0));

  CDC tempDC;
  tempDC.CreateCompatibleDC ((CDC*)&dc);
  CBitmap* oldBitmap = (CBitmap*)tempDC.SelectObject (m_Bitmap);
  dc.BitBlt (0, 0, rect.right, rect.bottom, &tempDC, 0, 0, SRCCOPY);

}
