// KingPin - Core Game Engine
// Faithful port of DWarsDoc.cpp game logic

class GameEngine {
  constructor() {
    this.reset();
    this.copInfo = { ...CONFIG.DEFAULT_COPS };
    this.jailCardProb = CONFIG.JAIL_CARD_PROB;
    this.showMessages = true;
    this.messages = [];
    this.pendingEvents = [];
    this.gameOver = false;
    this.loadHighScores();
  }

  reset() {
    // Player stats
    this.playerName = "";
    this.drugs = new Array(CONFIG.NUM_DRUGS).fill(null).map(() => ({ number: 0, price: 0 }));
    this.guns = new Array(CONFIG.NUM_GUNS).fill(null).map(() => ({ number: 0, price: 0 }));
    this.numGuns = 0;
    this.cash = CONFIG.STARTING_CASH;
    this.debt = CONFIG.STARTING_DEBT;
    this.bank = 0;
    this.total = this.cash + this.bank - this.debt;
    this.coatSize = CONFIG.COAT_SIZE;
    this.coatUsed = 0;
    this.health = 100;

    // Game stats
    this.currentDay = 1;
    this.totalDays = CONFIG.TOTAL_DAYS;
    this.location = 0;
    this.copCount = 3;

    // Market prices for current location
    this.drugPrices = new Array(CONFIG.NUM_DRUGS).fill(0);
    this.drugSpecials = new Array(CONFIG.NUM_DRUGS).fill(0);

    // Flags
    this.makeLoan = true;
    this.sellGun = true;
    this.gameOver = false;
    this.messages = [];
    this.pendingEvents = [];
  }

  firstDay() {
    this.drugs = new Array(CONFIG.NUM_DRUGS).fill(null).map(() => ({ number: 0, price: 0 }));
    this.guns = new Array(CONFIG.NUM_GUNS).fill(null).map(() => ({ number: 0, price: 0 }));
    this.numGuns = 0;
    this.cash = CONFIG.STARTING_CASH;
    this.debt = CONFIG.STARTING_DEBT;
    this.bank = 0;
    this.total = -3500;
    this.coatSize = CONFIG.COAT_SIZE;
    this.coatUsed = 0;
    this.health = 100;
    this.currentDay = 1;
    this.makeLoan = true;
    this.sellGun = true;
    this.gameOver = false;
    this.messages = [];
    this.pendingEvents = [];

    this.events();
    this.generateDrugs();
  }

  newDay(newLocation) {
    this.currentDay++;
    this.location = newLocation;
    this.debt = Math.floor(this.debt * 1.1);
    this.bank = Math.floor(this.bank * 1.05);
    this.total = this.cash + this.bank - this.debt;
    this.makeLoan = true;
    this.sellGun = true;
    this.messages = [];
    this.pendingEvents = [];

    this.events();

    if (this.health <= 0) return;
    if (this.currentDay > this.totalDays) {
      this.currentDay = this.totalDays;
    }

    this.generateDrugs();
  }

  events() {
    let i = 0;
    if (this.total > 3000000) { i = 130; }
    else if (this.total > 1000000) { i = 115; }
    else { i = 100; }

    if (brandom(0, i) > 75) {
      i = brandom(0, 100);
      if (i < 33) {
        this.offerObject(false);
      } else if (i < 50) {
        this.randomOffer();
      } else {
        this.startOfficerHardAss();
      }
    }
  }

  offerObject(forceContainer) {
    if (brandom(0, 100) < 50 || forceContainer) {
      // Offer trenchcoat
      const price = brandom(CONFIG.MIN_TRENCHCOAT_PRICE, CONFIG.MAX_TRENCHCOAT_PRICE);
      if (price <= this.cash) {
        this.pendingEvents.push({
          type: 'trenchcoat_offer',
          price: price,
          message: `Would you like to buy a bigger trenchcoat for $${price}?`
        });
      }
    } else {
      // Offer gun at discount
      const gunIndex = brandom(0, CONFIG.NUM_GUNS);
      const price = Math.floor(CONFIG.GUNS[gunIndex].price / 10);
      if (price <= this.cash) {
        if (CONFIG.GUNS[gunIndex].space > (this.coatSize - this.coatUsed)) {
          // Not enough room, silently skip
        } else {
          this.pendingEvents.push({
            type: 'gun_offer',
            gunIndex: gunIndex,
            price: price,
            message: `Would you like to buy a ${CONFIG.GUNS[gunIndex].name} for $${price}?`
          });
        }
      }
    }
  }

  acceptTrenchcoatOffer(price) {
    this.coatSize += 20;
    this.cash -= price;
    this.total = this.cash + this.bank - this.debt;
  }

  acceptGunOffer(gunIndex, price) {
    this.cash -= price;
    this.total = this.cash + this.bank - this.debt;

    const totalInv = this.guns[gunIndex].price * this.guns[gunIndex].number;
    this.guns[gunIndex].price = Math.floor((totalInv + price) / (this.guns[gunIndex].number + 1));
    this.guns[gunIndex].number++;
    this.numGuns++;
    this.coatUsed += CONFIG.GUNS[gunIndex].space;
  }

  randomOffer() {
    const r = brandom(0, 100);
    let text = "";

    if (r < 10) {
      text = "You were mugged in the subway!";
      this.cash = Math.floor(this.cash * brandom(80, 95) / 1001);
    } else if (r < 30) {
      // Friend tries to give you drugs
      const amount = brandom(3, 7);
      let ind = this.isCarryingRandom(amount);

      if (amount > (this.coatSize - this.coatUsed)) {
        if (ind === -1) ind = brandom(0, CONFIG.NUM_DRUGS);
        text = `Your friend tries to give you ${amount} ${CONFIG.DRUGS[ind].name}, but you don't have enough room!`;
      } else if (ind === -1) {
        ind = brandom(0, CONFIG.NUM_DRUGS);
        text = `You meet a friend! He gives you ${amount} ${CONFIG.DRUGS[ind].name}`;
        this.drugs[ind].number += amount;
        this.coatUsed += amount;
      } else {
        text = `You meet a friend! You give him ${amount} ${CONFIG.DRUGS[ind].name}`;
        this.drugs[ind].number -= amount;
        this.coatUsed -= amount;
      }
    } else if (r < 50) {
      // Police dogs chase
      const amount = brandom(3, 7);
      let ind = this.isCarryingRandom(amount);

      if (ind !== -1) {
        text = `Police dogs chase you for ${brandom(3, 7)} blocks! You dropped some ${CONFIG.DRUGS[ind].name}! That's a drag, man!`;
        this.drugs[ind].number -= amount;
        this.coatUsed -= amount;
      } else {
        ind = brandom(0, CONFIG.NUM_DRUGS);
        const findAmount = brandom(3, 7);
        text = `You find ${findAmount} ${CONFIG.DRUGS[ind].name} on a dead dude in the subway`;
        if (findAmount > (this.coatSize - this.coatUsed)) {
          text += ", but you don't have room for it!";
        } else {
          text += "!";
          this.drugs[ind].number += findAmount;
          this.coatUsed += findAmount;
        }
      }
    } else if (r < 60 && (this.drugs[11].number + this.drugs[2].number) > 0) {
      // Mama's brownies (Pot=11, Hashish=2)
      const ind = (this.drugs[11].number > this.drugs[2].number) ? 11 : 2;
      let amount = brandom(2, 6);
      if (amount > this.drugs[ind].number) {
        amount = this.drugs[ind].number;
      }
      text = `Your mama made brownies with some of your ${CONFIG.DRUGS[ind].name}! They were great!`;
      this.drugs[ind].number -= amount;
      this.coatUsed -= amount;
    } else if (r < 65) {
      // Paraquat weed - not implemented in original either
    } else {
      const amount = brandom(1, 10);
      const activity = CONFIG.STOPPED_TO[brandom(0, CONFIG.NUM_STOPPED_TO)];
      if (this.cash >= amount) {
        text = `You stopped to ${activity}`;
        this.cash -= amount;
      } else {
        text = `You would have liked to ${activity}, but you don't have the cash!`;
      }
    }

    if (text) {
      this.messages.push(text);
    }
  }

  isCarryingRandom(amount) {
    for (let i = 0; i < 5; i++) {
      const ind = brandom(0, CONFIG.NUM_DRUGS);
      if (this.drugs[ind].number >= amount) return ind;
    }
    return -1;
  }

  generateDrugs() {
    let numEvents = 0;
    let numDrugs = 0;
    const deal = new Array(CONFIG.NUM_DRUGS).fill(0);

    this.drugPrices = new Array(CONFIG.NUM_DRUGS).fill(0);
    this.drugSpecials = new Array(CONFIG.NUM_DRUGS).fill(0);

    // Determine number of events
    if (brandom(0, 100) < 70) numEvents = 1;
    if (brandom(0, 100) < 40 && numEvents === 1) numEvents = 2;
    if (brandom(0, 100) < 5 && numEvents === 2) numEvents = 3;

    // Determine prices for each event
    let attempts = 0;
    while (numEvents > 0 && attempts < 100) {
      attempts++;
      const i = brandom(0, CONFIG.NUM_DRUGS);
      if (deal[i] !== 0) continue;

      const drug = CONFIG.DRUGS[i];
      if (drug.expensive && (!drug.cheap || brandom(0, 100) < 50)) {
        deal[i] = brandom(1, 3);
        this.drugPrices[i] = brandom(drug.minPrice, drug.maxPrice) * CONFIG.EXPENSIVE_MULTIPLY;
        numDrugs++;
        numEvents--;
      } else if (drug.cheap) {
        deal[i] = 1;
        this.drugPrices[i] = Math.floor(brandom(drug.minPrice, drug.maxPrice) / CONFIG.CHEAP_DIVIDE);
        numDrugs++;
        numEvents--;
      }
    }

    // Figure out how many drugs to have
    const loc = CONFIG.LOCATIONS[this.location];
    numDrugs = brandom(loc.minDrug, loc.maxDrug) - numDrugs;
    if (numDrugs >= CONFIG.NUM_DRUGS) numDrugs = CONFIG.NUM_DRUGS;

    // Determine prices for remaining drugs
    attempts = 0;
    while (numDrugs > 0 && attempts < 200) {
      attempts++;
      const i = brandom(0, CONFIG.NUM_DRUGS);
      if (this.drugPrices[i] === 0) {
        this.drugPrices[i] = brandom(CONFIG.DRUGS[i].minPrice, CONFIG.DRUGS[i].maxPrice);
        numDrugs--;
      }
    }

    // Generate messages for special deals
    for (let i = 0; i < CONFIG.NUM_DRUGS; i++) {
      if (deal[i]) {
        const drug = CONFIG.DRUGS[i];
        if (drug.expensive) {
          if (deal[i] === 1) {
            this.messages.push(`Cops made a big ${drug.name} bust! Prices are outrageous!`);
          } else {
            this.messages.push(`Addicts are buying ${drug.name} at ridiculous prices!`);
          }
          this.drugSpecials[i] = 1;
        } else if (drug.cheap) {
          this.messages.push(drug.cheapStr);
          this.drugSpecials[i] = 2;
        }
      }
    }
  }

  startOfficerHardAss() {
    const money = this.cash + this.bank - this.debt;
    let cops;

    if (money > 3000000) { cops = brandom(11, 27); }
    else if (money > 1000000) { cops = brandom(7, 14); }
    else if (money > 500000) { cops = brandom(6, 12); }
    else if (money > 100000) { cops = brandom(2, 8); }
    else { cops = brandom(1, 5); }

    this.pendingEvents.push({
      type: 'cop_encounter',
      cops: cops
    });
  }

  // Combat methods
  fightCop(cops) {
    let damage = 100 - (brandom(0, cops) * this.copInfo.toughness);

    for (let i = 0; i < CONFIG.NUM_GUNS; i++) {
      for (let j = 0; j < this.guns[i].number; j++) {
        damage += brandom(0, CONFIG.GUNS[i].damage);
      }
    }

    const result = { playerText: "", policeText: "", killed: false, copsRemaining: cops, reward: 0, doctorOffer: null };

    if (damage >= 100) {
      if (cops === 1) {
        const money = brandom(1500, 3000);
        result.playerText = `You killed Officer HardAss!\n\nYou find $${money} on his corpse!`;
        this.cash += money;
        result.killed = true;
        result.reward = money;
        result.copsRemaining = 0;

        // Doctor offer
        const docFee = brandom(1000, Math.max(1001, 2000 - (5 * this.health)));
        if (brandom(0, 100) < 75 && this.cash >= docFee && this.health < 100) {
          result.doctorOffer = docFee;
        }
        return result;
      } else {
        result.playerText = "You got one, man!";
        result.copsRemaining = cops - 1;
      }
    } else {
      result.playerText = "You missed!";
    }

    // Police attack
    const policeResult = this.policeAttack(result.copsRemaining);
    result.policeText = policeResult.text;

    return result;
  }

  runFromCops(cops) {
    const escapeProb = this.copInfo.escapeProb - ((cops - 1) * this.copInfo.deputyEscape);
    const result = { escaped: false, text: "", policeText: "" };

    if (brandom(0, 100) < escapeProb) {
      result.escaped = true;
      result.text = "You lose him in the alleys.";
      return result;
    }

    result.text = cops <= 1 ? "You can't lose him!" : "You can't lose them!";

    // Police attack
    const policeResult = this.policeAttack(cops);
    result.policeText = policeResult.text;

    return result;
  }

  surrenderToCops() {
    let hasDrugs = false;
    for (let i = 0; i < CONFIG.NUM_DRUGS; i++) {
      if (this.drugs[i].number !== 0) { hasDrugs = true; break; }
    }

    if (!hasDrugs) {
      return {
        text: "The police frisk you, but you are not carrying any drugs! They let you go with a reluctant apology.",
        noDrugs: true
      };
    }

    const getAway = brandom(0, 100);
    let cost = brandom(Math.floor(this.total / 8), Math.floor(this.total / 4));
    if (cost <= 0) cost = 5000;

    let text;
    let jailDays = 0;

    if (getAway < this.jailCardProb) {
      text = `The police confiscate all your drugs, but your lawyer gets the criminal charges dropped on a technicality! Court fees are $${cost}.`;
    } else {
      jailDays = brandom(1, 4);
      if (jailDays === 1) {
        text = `The police confiscate all your drugs and you spend ${jailDays} day in jail. You are charged $${cost} in fines`;
      } else {
        text = `The police confiscate all your drugs and you spend ${jailDays} days in jail. You are charged $${cost} in fines`;
      }
      this.currentDay += jailDays;
    }

    // Take cost
    this.cash -= cost;
    if (this.cash < 0) {
      this.bank += this.cash;
      this.cash = 0;
      if (this.bank <= 0) {
        this.debt -= this.bank;
        this.bank = 0;
      }
    }
    this.total = this.cash + this.bank - this.debt;

    // Confiscate all drugs
    for (let i = 0; i < CONFIG.NUM_DRUGS; i++) {
      this.coatUsed -= this.drugs[i].number;
      this.drugs[i].number = 0;
      this.drugs[i].price = 0;
    }

    return { text, noDrugs: false, jailDays, cost };
  }

  policeAttack(cops) {
    let damage = 0;
    let text = cops <= 1 ? "He's firing on you, man!\n" : "They're firing on you, man!\n";

    const hitProb = this.copInfo.hitProb + ((cops - 1) * this.copInfo.deputyHit);

    if (brandom(0, 100) < hitProb) {
      for (let i = 0; i < cops; i++) {
        damage += brandom(0, this.copInfo.damage);
      }
      if (damage === 0) damage = 1;

      text += `You've been hit for ${damage}!\n`;

      if (damage >= this.health) {
        text += cops <= 1
          ? "He wasted you, man! What a drag!"
          : "They wasted you, man! What a drag!";
        this.health = 0;
      } else {
        this.health -= damage;
      }
    } else {
      text += cops <= 1 ? "He missed!" : "They missed!";
    }

    return { text, damage };
  }

  acceptDoctor(fee) {
    this.health = 100;
    this.cash -= fee;
    this.total = this.cash + this.bank - this.debt;
  }

  // Drug trading
  buyDrug(drugIndex, quantity) {
    const cost = quantity * this.drugPrices[drugIndex];
    this.cash -= cost;
    this.total = this.cash + this.bank - this.debt;

    const totalInv = this.drugs[drugIndex].price * this.drugs[drugIndex].number;
    const totalPurchase = this.drugPrices[drugIndex] * quantity;
    this.drugs[drugIndex].price = Math.floor((totalInv + totalPurchase) / (this.drugs[drugIndex].number + quantity));
    this.drugs[drugIndex].number += quantity;
    this.coatUsed += quantity;
  }

  sellDrug(drugIndex, quantity) {
    const qty = Math.min(this.drugs[drugIndex].number, quantity);
    const money = qty * this.drugPrices[drugIndex];

    this.drugs[drugIndex].number -= qty;
    this.coatUsed -= qty;

    if (this.drugs[drugIndex].number <= 0) {
      this.drugs[drugIndex].number = 0;
      this.drugs[drugIndex].price = 0;
    }

    this.cash += money;
    this.total = this.cash + this.bank - this.debt;
    return money;
  }

  dumpDrug(drugIndex, quantity) {
    const qty = Math.min(this.drugs[drugIndex].number, quantity);
    this.drugs[drugIndex].number -= qty;
    this.coatUsed -= qty;

    if (this.drugs[drugIndex].number <= 0) {
      this.drugs[drugIndex].number = 0;
      this.drugs[drugIndex].price = 0;
    }

    // Check if cops spot the drop
    if (brandom(0, 100) < this.copInfo.dropProb) {
      return { spotted: true, drugName: CONFIG.DRUGS[drugIndex].name };
    }
    return { spotted: false };
  }

  // Gun trading
  buyGun(gunIndex) {
    const price = CONFIG.GUNS[gunIndex].price;
    this.cash -= price;
    this.total = this.cash + this.bank - this.debt;

    const totalInv = this.guns[gunIndex].price * this.guns[gunIndex].number;
    this.guns[gunIndex].price = Math.floor((totalInv + price) / (this.guns[gunIndex].number + 1));
    this.guns[gunIndex].number++;
    this.numGuns++;
    this.coatUsed += CONFIG.GUNS[gunIndex].space;
    this.sellGun = false;
  }

  sellGunItem(gunIndex, quantity) {
    const qty = Math.min(this.guns[gunIndex].number, quantity);
    const money = qty * CONFIG.GUNS[gunIndex].price;

    this.guns[gunIndex].number -= qty;
    this.numGuns -= qty;
    this.coatUsed -= qty * CONFIG.GUNS[gunIndex].space;

    if (this.guns[gunIndex].number <= 0) {
      this.guns[gunIndex].number = 0;
      this.guns[gunIndex].price = 0;
    }

    this.cash += money;
    this.total = this.cash + this.bank - this.debt;
    return money;
  }

  dumpGun(gunIndex, quantity) {
    const qty = Math.min(this.guns[gunIndex].number, quantity);
    this.guns[gunIndex].number -= qty;
    this.numGuns -= qty;
    this.coatUsed -= qty * CONFIG.GUNS[gunIndex].space;

    if (this.guns[gunIndex].number <= 0) {
      this.guns[gunIndex].number = 0;
      this.guns[gunIndex].price = 0;
    }
  }

  // Finance
  deposit(amount) {
    this.cash -= amount;
    this.bank += amount;
  }

  withdraw(amount) {
    this.cash += amount;
    this.bank -= amount;
  }

  borrow(amount) {
    this.makeLoan = false;
    this.cash += amount;
    this.debt += amount;
    this.total = this.cash + this.bank - this.debt;
  }

  payback(amount) {
    this.cash -= amount;
    this.debt -= amount;
    this.total = this.cash + this.bank - this.debt;
  }

  // Hospital
  getHospitalFee() {
    return brandom(1000, Math.max(1001, 2000 - (5 * this.health)));
  }

  heal(fee) {
    this.health = 100;
    this.cash -= fee;
    this.total = this.cash + this.bank - this.debt;
  }

  // Max borrow amount
  maxBorrow() {
    let max = this.cash * 30;
    if (max < 5500) max = 5500;
    return max;
  }

  // High scores
  loadHighScores() {
    try {
      const stored = localStorage.getItem('kingpin_scores');
      this.highScores = stored ? JSON.parse(stored) : [];
    } catch {
      this.highScores = [];
    }
  }

  saveHighScores() {
    try {
      localStorage.setItem('kingpin_scores', JSON.stringify(this.highScores));
    } catch { /* ignore */ }
  }

  finishGame(playerName) {
    this.playerName = playerName || "Anonymous";
    const entry = {
      name: this.playerName,
      money: this.total,
      alive: this.health > 0 ? "Yes" : "No"
    };

    let place = -1;
    for (let i = 0; i < this.highScores.length; i++) {
      if (this.highScores[i].money <= this.total) {
        place = i;
        break;
      }
    }

    if (place === -1 && this.highScores.length < CONFIG.MAX_HIGH_SCORES) {
      place = this.highScores.length;
    }

    if (place !== -1) {
      this.highScores.splice(place, 0, entry);
      if (this.highScores.length > CONFIG.MAX_HIGH_SCORES) {
        this.highScores = this.highScores.slice(0, CONFIG.MAX_HIGH_SCORES);
      }
      this.saveHighScores();
      return { placed: true, rank: place + 1 };
    }

    return { placed: false, rank: -1 };
  }

  clearHighScores() {
    this.highScores = [];
    this.saveHighScores();
  }

  // Save/Load game
  saveGame() {
    const state = {
      playerName: this.playerName,
      drugs: this.drugs,
      guns: this.guns,
      numGuns: this.numGuns,
      cash: this.cash,
      debt: this.debt,
      bank: this.bank,
      total: this.total,
      coatSize: this.coatSize,
      coatUsed: this.coatUsed,
      health: this.health,
      currentDay: this.currentDay,
      location: this.location,
      makeLoan: this.makeLoan,
      sellGun: this.sellGun,
      drugPrices: this.drugPrices,
      drugSpecials: this.drugSpecials,
      messages: this.messages,
    };
    try {
      localStorage.setItem('kingpin_save', JSON.stringify(state));
      return true;
    } catch { return false; }
  }

  loadGame() {
    try {
      const data = localStorage.getItem('kingpin_save');
      if (!data) return false;
      const state = JSON.parse(data);
      Object.assign(this, state);
      this.pendingEvents = [];
      this.gameOver = false;
      return true;
    } catch { return false; }
  }

  hasSavedGame() {
    return localStorage.getItem('kingpin_save') !== null;
  }

  clearSave() {
    localStorage.removeItem('kingpin_save');
  }
}
