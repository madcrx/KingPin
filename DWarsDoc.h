// DWarsDoc.h : interface of the CDWarsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DWARSDOC_H__3337B7BE_5F97_4825_B12C_80E6D3640E9A__INCLUDED_)
#define AFX_DWARSDOC_H__3337B7BE_5F97_4825_B12C_80E6D3640E9A__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "Defines.h"

class CDWarsDoc : public CDocument
{
protected: // create from serialization only
	CDWarsDoc();
	DECLARE_DYNCREATE(CDWarsDoc)

// Attributes
public:
  BOOL m_bShowExit;
  BOOL m_bMakeLoan;
  BOOL m_bSellGun;

// Operations
public:
  void FirstDay ();
  void NewDay (int nNewLocation);
  void Events ();
  void GenerateDrugs ();
  void OfferObject(BOOL ForceContainer);
  void RandomOffer();
  void StartOfficerHardAss (CString loneStr, CString deputyStr);
  CString FinishGame ();

  void PlaySoundFile (CString fileName);
  void LoadPreferences ();
  void SavePreferences ();

  // Returns an index into the drugs array of a random drug that the player
  // is carrying at least "amount" of. If no suitable drug is found after 5
  // attempts, returns -1.
  int IsCarryingRandom (int amount);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDWarsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDWarsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDWarsDoc)
	afx_msg void OnFileOptions();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
  // Player stats
  CString m_PlayerName;
  inventory_t m_Drugs [NUM_DRUGS]; // number of 0 means none in possession
  inventory_t m_Guns [NUM_GUNS]; // number of 0 means none in possession
  int m_NumGuns;
  long m_Cash;
  long m_Debt;
  long m_Bank;
  long m_Total;
  int m_CoatSize;
  int m_CoatUsed;
  int m_Health;

  // Game stats
  int m_CurrentDay;
  int m_TotalDays;
  int m_Location; // Index into m_LocationList
  int m_CopCount;
  long m_DrugPrices [NUM_DRUGS];
  int m_DrugSpecials [NUM_DRUGS];

  // Constants
  location_t m_LocationList [NUM_LOCATIONS];
  drug_t m_DrugList [NUM_DRUGS];
  gun_t m_GunList [NUM_GUNS];
  CString m_StoppedToList [NUM_STOPPED_TO];
  cops_t m_CopInfo;
  int m_CheapDivide;
  int m_ExpensiveMultiply;
  int m_MinTrenchcoatPrice;
  int m_MaxTrenchcoatPrice;
  int m_JailCardProb;
  BOOL m_bShowMessages;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft eMbedded Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DWARSDOC_H__3337B7BE_5F97_4825_B12C_80E6D3640E9A__INCLUDED_)
