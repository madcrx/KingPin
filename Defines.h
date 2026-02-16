#if !defined POCKET_DOPE_WARS_DEFINES_H
#define POCKET_DOPE_WARS_DEFINES_H

#define NUM_GUNS 4
#define NUM_DRUGS 12
#define NUM_LOCATIONS 8
#define NUM_STOPPED_TO 5

int brandom(int bot,int top);

typedef struct COPS {
   int EscapeProb,DeputyEscape,HitProb,DeputyHit,Damage,Toughness;
   int DropProb;
} cops_t;

typedef struct GUN {
   CString Name;
   long Price;
   int Space;
   int Damage;
} gun_t;

typedef struct HISCORE {
   CString Time;
   long Money;
   char Dead;
   CString Name;
} hiscore_t;

typedef struct LOCATION {
   CString Name;
   int PolicePresence;
   int MinDrug,MaxDrug;
} location_t;

typedef struct DRUG {
   CString Name;
   long MinPrice,MaxPrice;
   BOOL Cheap,Expensive;
   CString CheapStr;
} drug_t;

typedef struct INVENTORY {
   long Price;
   int Number;
} inventory_t;

#endif // POCKET_DOPE_WARS_DEFINES_H