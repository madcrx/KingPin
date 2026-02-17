// KingPin - Game Configuration
// Faithful port of DWars (Pocket DopeWars) C++ source

const CONFIG = {
  NUM_DRUGS: 12,
  NUM_GUNS: 4,
  NUM_LOCATIONS: 8,
  NUM_STOPPED_TO: 5,
  TOTAL_DAYS: 30,
  STARTING_CASH: 2000,
  STARTING_DEBT: 5500,
  COAT_SIZE: 100,
  CHEAP_DIVIDE: 4,
  EXPENSIVE_MULTIPLY: 4,
  MIN_TRENCHCOAT_PRICE: 200,
  MAX_TRENCHCOAT_PRICE: 300,
  MAX_HIGH_SCORES: 11,

  LOCATIONS: [
    { name: "Bronx",         policePresence: 10, minDrug: 7,  maxDrug: 12 },
    { name: "Ghetto",        policePresence: 5,  minDrug: 8,  maxDrug: 12 },
    { name: "Central Park",  policePresence: 15, minDrug: 6,  maxDrug: 12 },
    { name: "Manhattan",     policePresence: 90, minDrug: 4,  maxDrug: 10 },
    { name: "Coney Island",  policePresence: 20, minDrug: 6,  maxDrug: 12 },
    { name: "Brooklyn",      policePresence: 70, minDrug: 4,  maxDrug: 11 },
    { name: "Queens",        policePresence: 50, minDrug: 6,  maxDrug: 12 },
    { name: "Staten Island", policePresence: 20, minDrug: 6,  maxDrug: 12 },
  ],

  DRUGS: [
    { name: "Acid",        minPrice: 1000,  maxPrice: 4400,  cheap: true,  expensive: false, cheapStr: "The market is flooded with cheap home-made acid!" },
    { name: "Cocaine",     minPrice: 15000, maxPrice: 29000, cheap: false, expensive: true,  cheapStr: "" },
    { name: "Hashish",     minPrice: 480,   maxPrice: 1280,  cheap: true,  expensive: false, cheapStr: "The Marrakesh Express has arrived!" },
    { name: "Heroin",      minPrice: 5500,  maxPrice: 13000, cheap: false, expensive: true,  cheapStr: "" },
    { name: "Ecstasy",     minPrice: 11,    maxPrice: 60,    cheap: true,  expensive: false, cheapStr: "Rival drug dealers raided a pharmacy and are selling cheap ecstasy!" },
    { name: "Xanax",       minPrice: 1500,  maxPrice: 4400,  cheap: false, expensive: false, cheapStr: "" },
    { name: "Special K",   minPrice: 540,   maxPrice: 1250,  cheap: false, expensive: true,  cheapStr: "" },
    { name: "GHB",         minPrice: 1000,  maxPrice: 2500,  cheap: false, expensive: false, cheapStr: "" },
    { name: "Viagra",      minPrice: 220,   maxPrice: 700,   cheap: false, expensive: false, cheapStr: "" },
    { name: "Morphine",    minPrice: 630,   maxPrice: 1300,  cheap: false, expensive: false, cheapStr: "" },
    { name: "Speed",       minPrice: 90,    maxPrice: 250,   cheap: false, expensive: true,  cheapStr: "" },
    { name: "Pot",         minPrice: 315,   maxPrice: 890,   cheap: true,  expensive: false, cheapStr: "Columbian freighter dusted the Coast Guard! Pot prices have bottomed out!" },
  ],

  GUNS: [
    { name: "Baretta",              price: 3000, space: 4, damage: 5 },
    { name: ".38 Special",          price: 3500, space: 4, damage: 9 },
    { name: "Ruger",                price: 2900, space: 4, damage: 4 },
    { name: "Saturday Night Special", price: 3100, space: 4, damage: 7 },
  ],

  STOPPED_TO: [
    "have a beer",
    "smoke a joint",
    "smoke a cigar",
    "smoke a Djarum",
    "smoke a cigarette",
  ],

  DEFAULT_COPS: {
    escapeProb: 70,
    deputyEscape: 2,
    hitProb: 65,
    deputyHit: 2,
    damage: 5,
    toughness: 2,
    dropProb: 30,
  },

  JAIL_CARD_PROB: 10,

  // Location-specific features
  FINANCE_LOCATION: 0,   // Bronx
  GUN_SHOP_LOCATION: 1,  // Ghetto
  HOSPITAL_LOCATION: 6,  // Queens
};

// Utility: random integer in [bot, top)
function brandom(bot, top) {
  return Math.floor(Math.random() * (top - bot)) + bot;
}
