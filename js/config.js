// KingPin - Game Configuration
// Drug Wars - 30-day NYC gameplay

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
    { name: "Bronx",         policePresence: 15, minDrug: 6,  maxDrug: 10 },
    { name: "Ghetto",        policePresence: 5,  minDrug: 7,  maxDrug: 12 },
    { name: "Central Park",  policePresence: 25, minDrug: 6,  maxDrug: 10 },
    { name: "Manhattan",     policePresence: 70, minDrug: 5,  maxDrug: 10 },
    { name: "Coney Island",  policePresence: 15, minDrug: 7,  maxDrug: 11 },
    { name: "Brooklyn",      policePresence: 20, minDrug: 7,  maxDrug: 11 },
    { name: "Queens",        policePresence: 40, minDrug: 6,  maxDrug: 10 },
    { name: "Staten Island", policePresence: 10, minDrug: 7,  maxDrug: 12 },
  ],

  // Special location indices
  BANK_LOCATION: 0,       // Bronx
  GUN_SHOP_LOCATION: 1,   // Ghetto
  HOSPITAL_LOCATION: 6,   // Queens

  DRUGS: [
    { name: "Acid",      minPrice: 1000,  maxPrice: 4400,  cheap: true,  expensive: false, cheapStr: "The market is flooded with cheap home-made acid!" },
    { name: "Cocaine",   minPrice: 15000, maxPrice: 29000, cheap: false, expensive: true,  cheapStr: "" },
    { name: "Hashish",   minPrice: 480,   maxPrice: 1280,  cheap: true,  expensive: false, cheapStr: "The Marrakesh Express has arrived!" },
    { name: "Heroin",    minPrice: 5500,  maxPrice: 13000, cheap: false, expensive: true,  cheapStr: "" },
    { name: "Ecstasy",   minPrice: 11,    maxPrice: 60,    cheap: true,  expensive: false, cheapStr: "Rival drug dealers raided a pharmacy and are selling cheap ecstasy!" },
    { name: "MDA",       minPrice: 1500,  maxPrice: 4400,  cheap: false, expensive: false, cheapStr: "" },
    { name: "PCP",       minPrice: 1000,  maxPrice: 2500,  cheap: false, expensive: true,  cheapStr: "" },
    { name: "Shrooms",   minPrice: 630,   maxPrice: 1300,  cheap: false, expensive: false, cheapStr: "" },
    { name: "Speed",     minPrice: 90,    maxPrice: 250,   cheap: false, expensive: true,  cheapStr: "" },
    { name: "Weed",      minPrice: 315,   maxPrice: 890,   cheap: true,  expensive: false, cheapStr: "Columbian freighter dusted the Coast Guard! Weed prices have bottomed out!" },
    { name: "Opium",     minPrice: 540,   maxPrice: 1250,  cheap: false, expensive: false, cheapStr: "" },
    { name: "Ludes",     minPrice: 220,   maxPrice: 700,   cheap: false, expensive: false, cheapStr: "" },
  ],

  GUNS: [
    { name: "Baretta",              price: 3400, space: 4, damage: 5 },
    { name: "Saturday Night Special", price: 2950, space: 4, damage: 4 },
    { name: "Shotgun",              price: 6400, space: 5, damage: 9 },
    { name: ".357 Magnum",          price: 5700, space: 4, damage: 8 },
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

  // Cop count scales with net worth
  HEAT_THRESHOLDS: [
    { min: 3000000, label: "EXTREME", copMin: 11, copMax: 27 },
    { min: 1000000, label: "HIGH",    copMin: 7,  copMax: 14 },
    { min: 500000,  label: "MEDIUM",  copMin: 6,  copMax: 12 },
    { min: 100000,  label: "WARM",    copMin: 2,  copMax: 8  },
    { min: 0,       label: "LOW",     copMin: 1,  copMax: 5  },
  ],

  EVENT_THRESHOLDS: [
    { min: 3000000, eventRange: 130 },
    { min: 1000000, eventRange: 115 },
    { min: 0,       eventRange: 100 },
  ],
};

// Utility: random integer in [bot, top)
function brandom(bot, top) {
  return Math.floor(Math.random() * (top - bot)) + bot;
}

// Utility: format money with condensed suffixes ($1k, $2.5k, $15.25m, etc.)
function formatMoney(n) {
  const neg = n < 0;
  const abs = Math.abs(n);
  let str;
  if (abs >= 1000000000) {
    str = (abs / 1000000000).toFixed(2).replace(/\.?0+$/, '') + 'b';
  } else if (abs >= 1000000) {
    str = (abs / 1000000).toFixed(2).replace(/\.?0+$/, '') + 'm';
  } else if (abs >= 1000) {
    str = (abs / 1000).toFixed(2).replace(/\.?0+$/, '') + 'k';
  } else {
    str = abs.toString();
  }
  return (neg ? '-$' : '$') + str;
}
