// KingPin - Game Configuration
// Global drug trade across 15 world cities, 365-day gameplay

const CONFIG = {
  NUM_DRUGS: 12,
  NUM_GUNS: 4,
  NUM_LOCATIONS: 15,
  NUM_STOPPED_TO: 5,
  TOTAL_DAYS: 365,
  STARTING_CASH: 20000,
  STARTING_DEBT: 55000,
  COAT_SIZE: 100,
  CHEAP_DIVIDE: 4,
  EXPENSIVE_MULTIPLY: 4,
  MIN_TRENCHCOAT_PRICE: 2000,
  MAX_TRENCHCOAT_PRICE: 3000,
  MAX_HIGH_SCORES: 11,

  LOCATIONS: [
    { name: "Bogota",        policePresence: 10, minDrug: 8,  maxDrug: 12 },
    { name: "Medellin",      policePresence: 8,  minDrug: 9,  maxDrug: 12 },
    { name: "Mexico City",   policePresence: 25, minDrug: 7,  maxDrug: 12 },
    { name: "Sinaloa",       policePresence: 5,  minDrug: 9,  maxDrug: 12 },
    { name: "Bangkok",       policePresence: 30, minDrug: 7,  maxDrug: 12 },
    { name: "Kabul",         policePresence: 10, minDrug: 8,  maxDrug: 12 },
    { name: "Mumbai",        policePresence: 40, minDrug: 6,  maxDrug: 11 },
    { name: "Amsterdam",     policePresence: 5,  minDrug: 8,  maxDrug: 12 },
    { name: "Marseille",     policePresence: 35, minDrug: 7,  maxDrug: 12 },
    { name: "Lagos",         policePresence: 15, minDrug: 6,  maxDrug: 11 },
    { name: "Hong Kong",     policePresence: 70, minDrug: 5,  maxDrug: 10 },
    { name: "Miami",         policePresence: 60, minDrug: 6,  maxDrug: 12 },
    { name: "Sao Paulo",     policePresence: 20, minDrug: 7,  maxDrug: 12 },
    { name: "Karachi",       policePresence: 12, minDrug: 8,  maxDrug: 12 },
    { name: "London",        policePresence: 65, minDrug: 5,  maxDrug: 10 },
  ],

  DRUGS: [
    { name: "Acid",        minPrice: 10000,   maxPrice: 44000,   cheap: true,  expensive: false, cheapStr: "The market is flooded with cheap home-made acid!" },
    { name: "Cocaine",     minPrice: 150000,  maxPrice: 290000,  cheap: false, expensive: true,  cheapStr: "" },
    { name: "Hashish",     minPrice: 4800,    maxPrice: 12800,   cheap: true,  expensive: false, cheapStr: "The Marrakesh Express has arrived!" },
    { name: "Heroin",      minPrice: 55000,   maxPrice: 130000,  cheap: false, expensive: true,  cheapStr: "" },
    { name: "Ecstasy",     minPrice: 110,     maxPrice: 600,     cheap: true,  expensive: false, cheapStr: "Rival drug dealers raided a pharmacy and are selling cheap ecstasy!" },
    { name: "Xanax",       minPrice: 15000,   maxPrice: 44000,   cheap: false, expensive: false, cheapStr: "" },
    { name: "Special K",   minPrice: 5400,    maxPrice: 12500,   cheap: false, expensive: true,  cheapStr: "" },
    { name: "GHB",         minPrice: 10000,   maxPrice: 25000,   cheap: false, expensive: false, cheapStr: "" },
    { name: "Viagra",      minPrice: 2200,    maxPrice: 7000,    cheap: false, expensive: false, cheapStr: "" },
    { name: "Morphine",    minPrice: 6300,    maxPrice: 13000,   cheap: false, expensive: false, cheapStr: "" },
    { name: "Speed",       minPrice: 900,     maxPrice: 2500,    cheap: false, expensive: true,  cheapStr: "" },
    { name: "Pot",         minPrice: 3150,    maxPrice: 8900,    cheap: true,  expensive: false, cheapStr: "Columbian freighter dusted the Coast Guard! Pot prices have bottomed out!" },
  ],

  GUNS: [
    { name: "Uzi",               price: 25000,  space: 4,  damage: 6 },
    { name: "AK-47",             price: 35000,  space: 5,  damage: 9 },
    { name: "AR-15",             price: 45000,  space: 5,  damage: 8 },
    { name: "Grenade Launcher",  price: 75000,  space: 8,  damage: 15 },
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

  // Heat level thresholds (cop count scales with net worth)
  HEAT_THRESHOLDS: [
    { min: 30000000, label: "EXTREME", copMin: 11, copMax: 27 },
    { min: 10000000, label: "HIGH",    copMin: 7,  copMax: 14 },
    { min: 5000000,  label: "MEDIUM",  copMin: 6,  copMax: 12 },
    { min: 1000000,  label: "WARM",    copMin: 2,  copMax: 8  },
    { min: 0,        label: "LOW",     copMin: 1,  copMax: 5  },
  ],

  // Event frequency thresholds (also heat-based)
  EVENT_THRESHOLDS: [
    { min: 30000000, eventRange: 130 },
    { min: 10000000, eventRange: 115 },
    { min: 0,        eventRange: 100 },
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
