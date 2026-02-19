// KingPin - UI Controller
// Handles all rendering, modals, and user interactions

class GameUI {
  constructor(engine) {
    this.engine = engine;
    this.currentModal = null;
    this.fightState = null;
    this.init();
  }

  init() {
    this.cacheElements();
    this.bindEvents();
    this.showSplash();
  }

  cacheElements() {
    // Main screen elements
    this.splash = document.getElementById('splash-screen');
    this.gameScreen = document.getElementById('game-screen');
    this.dayEl = document.getElementById('stat-day');
    this.districtEl = document.getElementById('stat-district');
    this.cashEl = document.getElementById('stat-cash');
    this.bankEl = document.getElementById('stat-bank');
    this.debtEl = document.getElementById('stat-debt');
    this.totalEl = document.getElementById('stat-total');
    this.healthBar = document.getElementById('health-bar');
    this.healthText = document.getElementById('health-text');
    this.gunsEl = document.getElementById('stat-guns');
    this.coatEl = document.getElementById('stat-coat');
    this.output = document.getElementById('output');

    // Buttons
    this.btnJet = document.getElementById('btn-jet');
    this.btnBuySell = document.getElementById('btn-buysell');
    this.btnFinance = document.getElementById('btn-finance');
    this.btnGuns = document.getElementById('btn-guns');
    this.btnHospital = document.getElementById('btn-hospital');
    this.btnEnd = document.getElementById('btn-end');

    // Modal
    this.modalOverlay = document.getElementById('modal-overlay');
    this.modalContent = document.getElementById('modal-content');
  }

  bindEvents() {
    document.getElementById('btn-new-game').addEventListener('click', () => this.showNewGame());
    document.getElementById('btn-load-game').addEventListener('click', () => this.loadGame());

    this.btnJet.addEventListener('click', () => this.showJet());
    this.btnBuySell.addEventListener('click', () => this.showDrugs());
    this.btnFinance.addEventListener('click', () => this.showFinance());
    this.btnGuns.addEventListener('click', () => this.showGunShop());
    this.btnHospital.addEventListener('click', () => this.showHospital());
    this.btnEnd.addEventListener('click', () => this.endGame());

    document.getElementById('btn-menu-new').addEventListener('click', () => this.confirmNewGame());
    document.getElementById('btn-menu-save').addEventListener('click', () => this.saveGame());
    document.getElementById('btn-menu-scores').addEventListener('click', () => this.showScores());
    document.getElementById('btn-menu-about').addEventListener('click', () => this.showAbout());

    this.modalOverlay.addEventListener('click', (e) => {
      if (e.target === this.modalOverlay) this.closeModal();
    });
  }

  // ──── SPLASH SCREEN ────
  showSplash() {
    this.splash.classList.remove('hidden');
    this.gameScreen.classList.add('hidden');

    const loadBtn = document.getElementById('btn-load-game');
    loadBtn.style.display = this.engine.hasSavedGame() ? '' : 'none';
  }

  // ──── NEW GAME ────
  showNewGame() {
    let html = `<div class="modal-header">New Game</div>
      <div class="modal-body">
        <label class="modal-label">Choose your starting district:</label>
        <div class="location-list">`;

    CONFIG.LOCATIONS.forEach((loc, i) => {
      let extra = '';
      if (i === CONFIG.BANK_LOCATION) extra = ' (Bank)';
      else if (i === CONFIG.GUN_SHOP_LOCATION) extra = ' (Guns)';
      else if (i === CONFIG.HOSPITAL_LOCATION) extra = ' (Hospital)';
      html += `<button class="location-btn" data-loc="${i}">${loc.name}${extra}</button>`;
    });

    html += `</div></div>`;
    this.showModal(html, 'new-game-modal');

    document.querySelectorAll('.location-btn').forEach(btn => {
      btn.addEventListener('click', () => {
        const loc = parseInt(btn.dataset.loc);
        this.closeModal();
        this.startGame(loc);
      });
    });
  }

  startGame(location) {
    this.engine.reset();
    this.engine.location = location;
    this.engine.firstDay();

    this.splash.classList.add('hidden');
    this.gameScreen.classList.remove('hidden');

    this.output.innerHTML = '';
    this.updateScreen();
    this.processEvents();
  }

  confirmNewGame() {
    this.showConfirm("Start a new game? Current progress will be lost.", () => {
      this.showNewGame();
    });
  }

  // ──── LOAD/SAVE ────
  loadGame() {
    if (this.engine.loadGame()) {
      this.splash.classList.add('hidden');
      this.gameScreen.classList.remove('hidden');
      this.updateScreen();
      this.checkDayEnd();
    } else {
      this.showAlert("No saved game found.");
    }
  }

  saveGame() {
    if (this.engine.saveGame()) {
      this.showAlert("Game saved!");
    } else {
      this.showAlert("Failed to save game.");
    }
  }

  // ──── SCREEN UPDATE ────
  updateScreen() {
    const e = this.engine;
    this.dayEl.textContent = `${e.currentDay}/${e.totalDays}`;
    this.districtEl.textContent = CONFIG.LOCATIONS[e.location].name;
    this.cashEl.textContent = formatMoney(e.cash);
    this.bankEl.textContent = formatMoney(e.bank);
    this.debtEl.textContent = formatMoney(e.debt);
    this.totalEl.textContent = formatMoney(e.total);

    this.healthBar.style.width = `${Math.max(0, e.health)}%`;
    this.healthBar.className = 'health-fill' +
      (e.health <= 25 ? ' critical' : e.health <= 50 ? ' warning' : '');
    this.healthText.textContent = e.health;

    this.gunsEl.textContent = e.numGuns;
    this.coatEl.textContent = `${e.coatUsed}/${e.coatSize}`;

    // Location-restricted facilities
    this.btnFinance.disabled = !e.isAtBank();
    this.btnGuns.disabled = !e.isAtGunShop();
    this.btnHospital.disabled = !e.isAtHospital();

    // Update heat level indicator
    const heat = e.getHeatLevel();
    const heatEl = document.getElementById('stat-heat');
    if (heatEl) {
      heatEl.textContent = heat.label;
      heatEl.className = 'stat-value heat-' + heat.label.toLowerCase();
    }

    // Show end button if last day
    if (e.currentDay >= e.totalDays) {
      this.btnJet.classList.add('hidden');
      this.btnEnd.classList.remove('hidden');
    } else {
      this.btnJet.classList.remove('hidden');
      this.btnEnd.classList.add('hidden');
    }
  }

  addOutput(text) {
    const line = document.createElement('div');
    line.className = 'output-line';
    line.textContent = text;
    this.output.appendChild(line);
    this.output.scrollTop = this.output.scrollHeight;
  }

  clearOutput() {
    this.output.innerHTML = '';
  }

  // ──── EVENT PROCESSING ────
  processEvents() {
    // Show messages first
    this.engine.messages.forEach(msg => {
      if (msg) this.addOutput(msg);
    });

    // Process pending events (offers, cop encounters)
    this.processPendingEvent(0);
  }

  processPendingEvent(index) {
    if (index >= this.engine.pendingEvents.length) return;

    const event = this.engine.pendingEvents[index];

    if (event.type === 'trenchcoat_offer') {
      this.showConfirm(event.message, () => {
        this.engine.acceptTrenchcoatOffer(event.price);
        this.addOutput(`You bought a bigger trenchcoat! (+20 space)`);
        this.updateScreen();
        this.processPendingEvent(index + 1);
      }, () => {
        this.processPendingEvent(index + 1);
      });
    } else if (event.type === 'gun_offer') {
      this.showConfirm(event.message, () => {
        this.engine.acceptGunOffer(event.gunIndex, event.price);
        this.addOutput(`You bought a ${CONFIG.GUNS[event.gunIndex].name}!`);
        this.updateScreen();
        this.processPendingEvent(index + 1);
      }, () => {
        this.processPendingEvent(index + 1);
      });
    } else if (event.type === 'cop_encounter') {
      this.showFight(event.cops);
    }
  }

  checkDayEnd() {
    if (this.engine.currentDay >= this.engine.totalDays) {
      this.btnJet.classList.add('hidden');
      this.btnEnd.classList.remove('hidden');
    }
    if (this.engine.currentDay + 1 === this.engine.totalDays) {
      this.showAlert("You have only one day left!");
    }
  }

  // ──── JET (TRAVEL) ────
  showJet() {
    const e = this.engine;
    let html = `<div class="modal-header">Jet</div>
      <div class="modal-body">
        <div class="modal-info">Current: <strong>${CONFIG.LOCATIONS[e.location].name}</strong></div>
        <label class="modal-label">Where do you want to go?</label>
        <div class="location-list">`;

    CONFIG.LOCATIONS.forEach((loc, i) => {
      if (i !== e.location) {
        let extra = '';
        if (i === CONFIG.BANK_LOCATION) extra = ' (Bank)';
        else if (i === CONFIG.GUN_SHOP_LOCATION) extra = ' (Guns)';
        else if (i === CONFIG.HOSPITAL_LOCATION) extra = ' (Hospital)';
        html += `<button class="location-btn" data-loc="${i}">${loc.name}${extra}</button>`;
      }
    });

    html += `</div>
        <div class="modal-actions">
          <button class="btn btn-cancel" id="modal-cancel">Cancel</button>
        </div>
      </div>`;

    this.showModal(html, 'jet-modal');

    document.getElementById('modal-cancel').addEventListener('click', () => this.closeModal());

    document.querySelectorAll('.location-btn').forEach(btn => {
      btn.addEventListener('click', () => {
        const loc = parseInt(btn.dataset.loc);
        this.closeModal();
        this.travel(loc);
      });
    });
  }

  travel(newLocation) {
    this.clearOutput();
    this.engine.newDay(newLocation);

    if (this.engine.health <= 0) {
      this.updateScreen();
      this.playerDied();
      return;
    }

    this.updateScreen();
    this.processEvents();
    this.checkDayEnd();
  }

  // ──── DRUG MARKET ────
  showDrugs() {
    const e = this.engine;
    let html = `<div class="modal-header">Drug Market</div>
      <div class="modal-body">
        <div class="market-stats">
          <span>Cash: <strong>${formatMoney(e.cash)}</strong></span>
          <span>Coat: <strong>${e.coatUsed}/${e.coatSize}</strong></span>
        </div>

        <div class="market-section">
          <h3>Available to Buy</h3>
          <div class="drug-table" id="buy-list"></div>
        </div>

        <div class="market-section">
          <h3>Your Stash</h3>
          <div class="drug-table" id="sell-list"></div>
        </div>

        <div class="modal-actions">
          <button class="btn btn-close" id="modal-close">Close</button>
        </div>
      </div>`;

    this.showModal(html, 'drug-modal');
    this.renderDrugLists();
    document.getElementById('modal-close').addEventListener('click', () => this.closeModal());
  }

  renderDrugLists() {
    const e = this.engine;
    const buyList = document.getElementById('buy-list');
    const sellList = document.getElementById('sell-list');
    if (!buyList || !sellList) return;

    // Update stats
    const statsEl = document.querySelector('.market-stats');
    if (statsEl) {
      statsEl.innerHTML = `
        <span>Cash: <strong>${formatMoney(e.cash)}</strong></span>
        <span>Coat: <strong>${e.coatUsed}/${e.coatSize}</strong></span>`;
    }

    // Buy list
    let buyHtml = `<div class="table-row table-header">
      <span class="col-name">Drug</span>
      <span class="col-price">Price</span>
      <span class="col-action">Action</span>
    </div>`;

    for (let i = 0; i < CONFIG.NUM_DRUGS; i++) {
      if (e.drugPrices[i] !== 0) {
        const specialClass = e.drugSpecials[i] === 1 ? ' expensive-deal' : e.drugSpecials[i] === 2 ? ' cheap-deal' : '';
        buyHtml += `<div class="table-row${specialClass}">
          <span class="col-name">${CONFIG.DRUGS[i].name}</span>
          <span class="col-price">${formatMoney(e.drugPrices[i])}</span>
          <span class="col-action"><button class="btn btn-sm btn-buy" data-drug="${i}">Buy</button></span>
        </div>`;
      }
    }
    buyList.innerHTML = buyHtml;

    // Sell list
    let sellHtml = `<div class="table-row table-header">
      <span class="col-name">Drug</span>
      <span class="col-qty">Qty</span>
      <span class="col-price">Paid</span>
      <span class="col-action2">Actions</span>
    </div>`;

    let hasStash = false;
    for (let i = 0; i < CONFIG.NUM_DRUGS; i++) {
      if (e.drugs[i].number > 0) {
        hasStash = true;
        sellHtml += `<div class="table-row">
          <span class="col-name">${CONFIG.DRUGS[i].name}</span>
          <span class="col-qty">${e.drugs[i].number}</span>
          <span class="col-price">${formatMoney(e.drugs[i].price)}</span>
          <span class="col-action2">
            <button class="btn btn-sm btn-sell" data-drug="${i}">Sell</button>
            <button class="btn btn-sm btn-dump" data-drug="${i}">Drop</button>
          </span>
        </div>`;
      }
    }
    if (!hasStash) {
      sellHtml += `<div class="table-row empty-row"><span>No drugs in your stash</span></div>`;
    }
    sellList.innerHTML = sellHtml;

    // Bind buy buttons
    document.querySelectorAll('.btn-buy').forEach(btn => {
      btn.addEventListener('click', () => {
        const drug = parseInt(btn.dataset.drug);
        this.showBuyDrug(drug);
      });
    });

    // Bind sell buttons
    document.querySelectorAll('.btn-sell').forEach(btn => {
      btn.addEventListener('click', () => {
        const drug = parseInt(btn.dataset.drug);
        this.showSellDrug(drug);
      });
    });

    // Bind dump buttons
    document.querySelectorAll('.btn-dump').forEach(btn => {
      btn.addEventListener('click', () => {
        const drug = parseInt(btn.dataset.drug);
        this.showDumpDrug(drug);
      });
    });
  }

  showBuyDrug(drugIndex) {
    const e = this.engine;
    const maxAfford = Math.floor(e.cash / e.drugPrices[drugIndex]);
    const space = e.coatSize - e.coatUsed;

    if (maxAfford <= 0) {
      this.showAlert("You can not afford this drug");
      return;
    }
    if (space <= 0) {
      this.showAlert("You have no more room!");
      return;
    }

    const max = Math.min(maxAfford, space);
    this.showQuantityPicker(
      `Buy ${CONFIG.DRUGS[drugIndex].name}`,
      `You can afford ${maxAfford}\nRoom for ${space}`,
      "How many do you buy?",
      1, max, 1,
      (qty) => {
        e.buyDrug(drugIndex, qty);
        this.updateScreen();
        this.renderDrugLists();
      }
    );
  }

  showSellDrug(drugIndex) {
    const e = this.engine;
    const carrying = e.drugs[drugIndex].number;
    const curPrice = e.drugPrices[drugIndex];
    const boughtPrice = e.drugs[drugIndex].price;

    if (curPrice === 0) {
      this.showAlert("This drug is not being sold here right now. You can still drop it.");
      return;
    }

    this.showSellPicker(
      `Sell ${CONFIG.DRUGS[drugIndex].name}`,
      `Carrying: ${carrying}`,
      1, carrying, 1,
      curPrice, boughtPrice,
      (qty) => {
        e.sellDrug(drugIndex, qty);
        this.updateScreen();
        this.renderDrugLists();
      }
    );
  }

  showDumpDrug(drugIndex) {
    const e = this.engine;
    const carrying = e.drugs[drugIndex].number;

    this.showQuantityPicker(
      `Drop ${CONFIG.DRUGS[drugIndex].name}`,
      `Carrying: ${carrying}`,
      "How many do you drop?",
      1, carrying, 1,
      (qty) => {
        const result = e.dumpDrug(drugIndex, qty);
        this.updateScreen();
        this.renderDrugLists();

        if (result.spotted) {
          this.closeModal();
          this.addOutput(`Cops spotted you dropping ${result.drugName}!`);
          const heat = e.getHeatLevel();
          const cops = brandom(heat.copMin, heat.copMax);

          setTimeout(() => this.showFight(cops), 300);
        }
      }
    );
  }

  // ──── FIGHT SCREEN ────
  showFight(cops) {
    this.fightState = { cops };

    const text = cops === 1
      ? "Officer HardAss is chasing you!"
      : `Officer HardAss and ${cops} of his deputies are chasing you!`;

    let html = `<div class="modal-header fight-header">Police Encounter!</div>
      <div class="modal-body fight-body">
        <div id="fight-text" class="fight-text">${text}</div>
        <div class="fight-stats">
          <div class="fight-stat">
            <label>Health</label>
            <div class="health-bar-container small">
              <div class="health-fill" id="fight-health-bar" style="width:${this.engine.health}%"></div>
            </div>
            <span id="fight-health-text">${this.engine.health}</span>
          </div>
          <div class="fight-stat">
            <label>Guns</label>
            <span id="fight-guns">${this.engine.numGuns}</span>
          </div>
          <div class="fight-stat">
            <label>Cops</label>
            <span id="fight-cops">${cops}</span>
          </div>
        </div>
        <div id="fight-log" class="fight-log"></div>
        <div class="fight-actions" id="fight-actions">
          <button class="btn btn-fight" id="btn-fight-fight" ${this.engine.numGuns === 0 ? 'disabled' : ''}>Fight</button>
          <button class="btn btn-run" id="btn-fight-run">Run</button>
          <button class="btn btn-surrender" id="btn-fight-stay">Surrender</button>
        </div>
      </div>`;

    // Use closeable=true so Continue buttons work via closeModal()
    this.showModal(html, 'fight-modal', true);

    document.getElementById('btn-fight-fight').addEventListener('click', () => this.doFight());
    document.getElementById('btn-fight-run').addEventListener('click', () => this.doRun());
    document.getElementById('btn-fight-stay').addEventListener('click', () => this.doSurrender());

    // Prevent closing by clicking overlay during fight
    this.modalOverlay.onclick = (e) => {
      if (e.target === this.modalOverlay && this.currentModal !== 'fight-modal') {
        this.closeModal();
      }
    };
  }

  updateFightScreen() {
    const e = this.engine;
    const healthBar = document.getElementById('fight-health-bar');
    const healthText = document.getElementById('fight-health-text');
    const copsText = document.getElementById('fight-cops');
    const fightText = document.getElementById('fight-text');

    if (healthBar) {
      healthBar.style.width = `${Math.max(0, e.health)}%`;
      healthBar.className = 'health-fill' +
        (e.health <= 25 ? ' critical' : e.health <= 50 ? ' warning' : '');
    }
    if (healthText) healthText.textContent = e.health;
    if (copsText) copsText.textContent = this.fightState.cops;

    if (fightText) {
      fightText.textContent = this.fightState.cops === 1
        ? "Officer HardAss is chasing you!"
        : `Officer HardAss and ${this.fightState.cops} of his deputies are chasing you!`;
    }
  }

  addFightLog(text) {
    const log = document.getElementById('fight-log');
    if (log) {
      const line = document.createElement('div');
      line.className = 'fight-log-line';
      line.textContent = text;
      log.appendChild(line);
      log.scrollTop = log.scrollHeight;
    }
  }

  doFight() {
    const result = this.engine.fightCop(this.fightState.cops);
    this.fightState.cops = result.copsRemaining;

    this.addFightLog(result.playerText);
    if (result.policeText) {
      this.addFightLog(result.policeText);
    }

    this.updateFightScreen();
    this.updateScreen();

    if (result.killed && result.copsRemaining === 0) {
      // Won the fight
      document.getElementById('fight-actions').innerHTML =
        `<button class="btn btn-close" id="btn-fight-done">Continue</button>`;
      document.getElementById('btn-fight-done').addEventListener('click', () => {
        this.closeModal();
        this.restoreOverlayHandler();
        if (result.doctorOffer) {
          this.showConfirm(`Do you pay a doctor ${formatMoney(result.doctorOffer)} to sew you up?`, () => {
            this.engine.acceptDoctor(result.doctorOffer);
            this.updateScreen();
          });
        }
      });
      return;
    }

    if (this.engine.health <= 0) {
      document.getElementById('fight-actions').innerHTML =
        `<button class="btn btn-close" id="btn-fight-dead">Continue</button>`;
      document.getElementById('btn-fight-dead').addEventListener('click', () => {
        this.closeModal();
        this.restoreOverlayHandler();
        this.playerDied();
      });
    }
  }

  doRun() {
    const result = this.engine.runFromCops(this.fightState.cops);

    if (result.escaped) {
      this.addFightLog(result.text);
      document.getElementById('fight-actions').innerHTML =
        `<button class="btn btn-close" id="btn-fight-escaped">Continue</button>`;
      document.getElementById('btn-fight-escaped').addEventListener('click', () => {
        this.closeModal();
        this.restoreOverlayHandler();
      });
      return;
    }

    this.addFightLog(result.text);
    if (result.policeText) {
      this.addFightLog(result.policeText);
    }

    this.updateFightScreen();
    this.updateScreen();

    if (this.engine.health <= 0) {
      document.getElementById('fight-actions').innerHTML =
        `<button class="btn btn-close" id="btn-fight-dead">Continue</button>`;
      document.getElementById('btn-fight-dead').addEventListener('click', () => {
        this.closeModal();
        this.restoreOverlayHandler();
        this.playerDied();
      });
    }
  }

  doSurrender() {
    const result = this.engine.surrenderToCops();
    this.addFightLog(result.text);
    this.updateScreen();

    document.getElementById('fight-actions').innerHTML =
      `<button class="btn btn-close" id="btn-fight-done">Continue</button>`;
    document.getElementById('btn-fight-done').addEventListener('click', () => {
      this.closeModal();
      this.restoreOverlayHandler();
      this.checkDayEnd();
    });
  }

  restoreOverlayHandler() {
    this.modalOverlay.onclick = (e) => {
      if (e.target === this.modalOverlay) this.closeModal();
    };
  }

  playerDied() {
    this.showPlayerNamePrompt((name) => {
      const result = this.engine.finishGame(name);
      let msg = "You're dead! Game over.";
      if (result.placed) {
        msg += ` You ranked #${result.rank}!`;
      }
      this.showAlert(msg, () => {
        this.showScores(() => {
          this.engine.clearSave();
          this.showSplash();
        });
      });
    });
  }

  endGame() {
    this.showPlayerNamePrompt((name) => {
      const result = this.engine.finishGame(name);
      let msg;
      if (result.placed) {
        msg = `You kick ass! You rank number ${result.rank}!`;
      } else {
        msg = "You didn't place this time.";
      }
      this.showAlert(msg, () => {
        this.showScores(() => {
          this.engine.clearSave();
          this.showSplash();
        });
      });
    });
  }

  // ──── FINANCE (Bronx only) ────
  showFinance() {
    const e = this.engine;
    let tempCash = e.cash;
    let tempBank = e.bank;
    let tempDebt = e.debt;

    const render = () => {
      let html = `<div class="modal-header">Loan Shark & Bank</div>
        <div class="modal-body">
          <div class="finance-stats">
            <div class="finance-row"><span>Cash:</span><strong id="fin-cash">${formatMoney(tempCash)}</strong></div>
            <div class="finance-row"><span>Bank:</span><strong id="fin-bank">${formatMoney(tempBank)}</strong></div>
            <div class="finance-row"><span>Debt:</span><strong id="fin-debt">${formatMoney(tempDebt)}</strong></div>
            <div class="finance-row"><span>Day:</span><strong>${e.currentDay}/${e.totalDays}</strong></div>
          </div>
          <div class="finance-actions">
            <button class="btn btn-action" id="fin-deposit" ${tempCash <= 0 ? 'disabled' : ''}>Deposit</button>
            <button class="btn btn-action" id="fin-withdraw" ${tempBank <= 0 ? 'disabled' : ''}>Withdraw</button>
            <button class="btn btn-action" id="fin-borrow" ${!e.makeLoan ? 'disabled' : ''}>Borrow</button>
            <button class="btn btn-action" id="fin-payback" ${tempDebt <= 0 || tempCash <= 0 ? 'disabled' : ''}>Pay Back</button>
          </div>
          <div class="modal-actions">
            <button class="btn btn-close" id="fin-done">Done</button>
          </div>
        </div>`;

      this.showModal(html, 'finance-modal');

      document.getElementById('fin-deposit').addEventListener('click', () => {
        this.showQuantityPicker("Deposit", `You have ${formatMoney(tempCash)} in cash`, "How much to deposit?",
          1, tempCash, 1, (amt) => {
            tempCash -= amt; tempBank += amt;
            e.cash = tempCash; e.bank = tempBank;
            e.total = e.cash + e.bank - e.debt;
            this.updateScreen();
            render();
          });
      });

      document.getElementById('fin-withdraw').addEventListener('click', () => {
        this.showQuantityPicker("Withdraw", `You have ${formatMoney(tempBank)} in the bank`, "How much to withdraw?",
          1, tempBank, 1, (amt) => {
            tempCash += amt; tempBank -= amt;
            e.cash = tempCash; e.bank = tempBank;
            e.total = e.cash + e.bank - e.debt;
            this.updateScreen();
            render();
          });
      });

      document.getElementById('fin-borrow').addEventListener('click', () => {
        const maxBorrow = e.maxBorrow();
        this.showQuantityPicker("Borrow", `Cash: ${formatMoney(tempCash)}, Bank: ${formatMoney(tempBank)}`,
          "How much to borrow?", 1, maxBorrow, 1, (amt) => {
            tempCash += amt; tempDebt += amt;
            e.cash = tempCash; e.debt = tempDebt;
            e.makeLoan = false;
            e.total = e.cash + e.bank - e.debt;
            this.updateScreen();
            render();
          });
      });

      document.getElementById('fin-payback').addEventListener('click', () => {
        const maxPay = Math.min(tempCash, tempDebt);
        this.showQuantityPicker("Pay Back", `Cash: ${formatMoney(tempCash)}, Debt: ${formatMoney(tempDebt)}`,
          "How much to pay back?", 1, maxPay, 1, (amt) => {
            tempCash -= amt; tempDebt -= amt;
            e.cash = tempCash; e.debt = tempDebt;
            e.total = e.cash + e.bank - e.debt;
            this.updateScreen();
            render();
          });
      });

      document.getElementById('fin-done').addEventListener('click', () => {
        this.closeModal();
        this.updateScreen();
      });
    };

    render();
  }

  // ──── GUN SHOP (Ghetto only) ────
  showGunShop() {
    const e = this.engine;

    const render = () => {
      let buyHtml = '';
      for (let i = 0; i < CONFIG.NUM_GUNS; i++) {
        buyHtml += `<div class="table-row">
          <span class="col-name">${CONFIG.GUNS[i].name}</span>
          <span class="col-price">${formatMoney(CONFIG.GUNS[i].price)}</span>
          <span class="col-stat">S:${CONFIG.GUNS[i].space}</span>
          <span class="col-stat">D:${CONFIG.GUNS[i].damage}</span>
          <span class="col-action"><button class="btn btn-sm btn-buy gun-buy" data-gun="${i}" ${!e.sellGun ? 'disabled' : ''}>Buy</button></span>
        </div>`;
      }

      let sellHtml = '';
      let hasGuns = false;
      for (let i = 0; i < CONFIG.NUM_GUNS; i++) {
        if (e.guns[i].number > 0) {
          hasGuns = true;
          sellHtml += `<div class="table-row">
            <span class="col-name">${CONFIG.GUNS[i].name}</span>
            <span class="col-price">${formatMoney(e.guns[i].price)}</span>
            <span class="col-qty">${e.guns[i].number}</span>
            <span class="col-action2">
              <button class="btn btn-sm btn-sell gun-sell" data-gun="${i}">Sell</button>
              <button class="btn btn-sm btn-dump gun-dump" data-gun="${i}">Drop</button>
            </span>
          </div>`;
        }
      }
      if (!hasGuns) {
        sellHtml = `<div class="table-row empty-row"><span>No guns in inventory</span></div>`;
      }

      let html = `<div class="modal-header">Gun Shop</div>
        <div class="modal-body">
          <div class="market-stats">
            <span>Cash: <strong>${formatMoney(e.cash)}</strong></span>
            <span>Coat: <strong>${e.coatUsed}/${e.coatSize}</strong></span>
          </div>
          <div class="market-section">
            <h3>Available Guns</h3>
            <div class="drug-table">
              <div class="table-row table-header">
                <span class="col-name">Name</span>
                <span class="col-price">Price</span>
                <span class="col-stat">Spc</span>
                <span class="col-stat">Dmg</span>
                <span class="col-action">Action</span>
              </div>
              ${buyHtml}
            </div>
          </div>
          <div class="market-section">
            <h3>Your Arsenal</h3>
            <div class="drug-table">
              <div class="table-row table-header">
                <span class="col-name">Name</span>
                <span class="col-price">Paid</span>
                <span class="col-qty">#</span>
                <span class="col-action2">Actions</span>
              </div>
              ${sellHtml}
            </div>
          </div>
          <div class="modal-actions">
            <button class="btn btn-close" id="modal-close">Close</button>
          </div>
        </div>`;

      this.showModal(html, 'gun-modal');
      document.getElementById('modal-close').addEventListener('click', () => {
        this.closeModal();
        this.updateScreen();
      });

      document.querySelectorAll('.gun-buy').forEach(btn => {
        btn.addEventListener('click', () => {
          const gun = parseInt(btn.dataset.gun);
          const space = e.coatSize - e.coatUsed;
          if (e.cash - CONFIG.GUNS[gun].price <= 0) {
            this.showAlert("You can not afford this gun!");
            return;
          }
          if (space - CONFIG.GUNS[gun].space < 0) {
            this.showAlert("You do not have enough room!");
            return;
          }
          e.buyGun(gun);
          this.updateScreen();
          render();
        });
      });

      document.querySelectorAll('.gun-sell').forEach(btn => {
        btn.addEventListener('click', () => {
          const gun = parseInt(btn.dataset.gun);
          this.showQuantityPicker(`Sell ${CONFIG.GUNS[gun].name}`,
            `Carrying: ${e.guns[gun].number}`, "How many to sell?",
            1, e.guns[gun].number, 1, (qty) => {
              e.sellGunItem(gun, qty);
              this.updateScreen();
              render();
            });
        });
      });

      document.querySelectorAll('.gun-dump').forEach(btn => {
        btn.addEventListener('click', () => {
          const gun = parseInt(btn.dataset.gun);
          this.showQuantityPicker(`Drop ${CONFIG.GUNS[gun].name}`,
            `Carrying: ${e.guns[gun].number}`, "How many to drop?",
            1, e.guns[gun].number, 1, (qty) => {
              e.dumpGun(gun, qty);
              this.updateScreen();
              render();
            });
        });
      });
    };

    render();
  }

  // ──── HOSPITAL (Queens only) ────
  showHospital() {
    const e = this.engine;

    if (e.health >= 100) {
      this.showAlert("You are at full health already");
      return;
    }

    const fee = e.getHospitalFee();
    if (e.cash < fee) {
      this.showAlert("You do not have enough money to get fixed up");
      return;
    }

    this.showConfirm(`Do you pay a doctor ${formatMoney(fee)} to sew you up?`, () => {
      e.heal(fee);
      this.updateScreen();
      this.addOutput("The doctor patched you up. Health restored to 100.");
    });
  }

  // ──── HIGH SCORES ────
  showScores(callback) {
    const scores = this.engine.highScores;
    let rows = '';
    if (scores.length === 0) {
      rows = '<div class="table-row empty-row"><span>No high scores yet</span></div>';
    } else {
      scores.forEach((s, i) => {
        rows += `<div class="table-row">
          <span class="col-rank">${i + 1}</span>
          <span class="col-name">${this.escapeHtml(s.name)}</span>
          <span class="col-price">${formatMoney(s.money)}</span>
          <span class="col-stat">${s.alive}</span>
        </div>`;
      });
    }

    let html = `<div class="modal-header">High Scores</div>
      <div class="modal-body">
        <div class="drug-table">
          <div class="table-row table-header">
            <span class="col-rank">#</span>
            <span class="col-name">Name</span>
            <span class="col-price">Money</span>
            <span class="col-stat">Alive</span>
          </div>
          ${rows}
        </div>
        <div class="modal-actions">
          <button class="btn btn-close" id="scores-close">Close</button>
          <button class="btn btn-danger" id="scores-clear">Clear</button>
        </div>
      </div>`;

    this.showModal(html, 'scores-modal');

    document.getElementById('scores-close').addEventListener('click', () => {
      this.closeModal();
      if (callback) callback();
    });

    document.getElementById('scores-clear').addEventListener('click', () => {
      this.showConfirm("Are you sure you want to erase all high scores?", () => {
        this.engine.clearHighScores();
        this.showScores(callback);
      });
    });
  }

  // ──── ABOUT ────
  showAbout() {
    const html = `<div class="modal-header">About KingPin</div>
      <div class="modal-body">
        <div class="about-text">
          <p><strong>KingPin</strong> - Drug Wars</p>
          <p>Deal drugs across 8 NYC districts. You have 30 days to pay off your debt and get rich.</p>
          <p>Original concept by John E. Dell (1984).<br>
          C++ WinCE version by AtomWare.<br>
          Web port by Claude Code.</p>
          <p>Buy low, sell high, avoid the cops, and try to pay off your debt!</p>
        </div>
        <div class="modal-actions">
          <button class="btn btn-close" id="about-close">Close</button>
        </div>
      </div>`;

    this.showModal(html, 'about-modal');
    document.getElementById('about-close').addEventListener('click', () => this.closeModal());
  }

  // ──── GENERIC MODALS ────
  showModal(html, className, closeable = true) {
    this.modalContent.innerHTML = html;
    this.modalContent.className = 'modal-content ' + (className || '');
    this.modalOverlay.classList.remove('hidden');
    this.currentModal = className;
    this.modalCloseable = closeable;
  }

  closeModal() {
    if (!this.modalCloseable) return;
    this.modalOverlay.classList.add('hidden');
    this.currentModal = null;
  }

  forceCloseModal() {
    this.modalOverlay.classList.add('hidden');
    this.currentModal = null;
  }

  showAlert(message, callback) {
    const html = `<div class="modal-header">Notice</div>
      <div class="modal-body">
        <div class="alert-text">${this.escapeHtml(message)}</div>
        <div class="modal-actions">
          <button class="btn btn-close" id="alert-ok">OK</button>
        </div>
      </div>`;

    this.showModal(html, 'alert-modal');
    document.getElementById('alert-ok').addEventListener('click', () => {
      this.closeModal();
      if (callback) callback();
    });
  }

  showConfirm(message, onYes, onNo) {
    const html = `<div class="modal-header">Confirm</div>
      <div class="modal-body">
        <div class="alert-text">${this.escapeHtml(message)}</div>
        <div class="modal-actions">
          <button class="btn btn-action" id="confirm-yes">Yes</button>
          <button class="btn btn-cancel" id="confirm-no">No</button>
        </div>
      </div>`;

    this.showModal(html, 'confirm-modal');
    document.getElementById('confirm-yes').addEventListener('click', () => {
      this.closeModal();
      if (onYes) onYes();
    });
    document.getElementById('confirm-no').addEventListener('click', () => {
      this.closeModal();
      if (onNo) onNo();
    });
  }

  showQuantityPicker(title, info, question, min, max, initial, onConfirm) {
    const html = `<div class="modal-header">${this.escapeHtml(title)}</div>
      <div class="modal-body">
        <div class="qty-info">${this.escapeHtml(info)}</div>
        <div class="qty-question">${this.escapeHtml(question)}</div>
        <div class="qty-controls">
          <input type="range" id="qty-slider" min="${min}" max="${max}" value="${initial}" class="qty-slider">
          <div class="qty-input-row">
            <input type="number" id="qty-input" min="${min}" max="${max}" value="${initial}" class="qty-input">
            <button class="btn btn-sm" id="qty-max">Max</button>
          </div>
        </div>
        <div class="modal-actions">
          <button class="btn btn-action" id="qty-ok">OK</button>
          <button class="btn btn-cancel" id="qty-cancel">Cancel</button>
        </div>
      </div>`;

    this.showModal(html, 'quantity-modal');

    const slider = document.getElementById('qty-slider');
    const input = document.getElementById('qty-input');

    slider.addEventListener('input', () => { input.value = slider.value; });
    input.addEventListener('input', () => {
      let v = parseInt(input.value) || min;
      if (v < min) v = min;
      if (v > max) v = max;
      slider.value = v;
    });
    document.getElementById('qty-max').addEventListener('click', () => {
      slider.value = max;
      input.value = max;
    });

    document.getElementById('qty-ok').addEventListener('click', () => {
      let val = parseInt(input.value) || min;
      if (val < min) val = min;
      if (val > max) val = max;
      this.closeModal();
      onConfirm(val);
    });

    document.getElementById('qty-cancel').addEventListener('click', () => {
      this.closeModal();
    });
  }

  showSellPicker(title, info, min, max, initial, curPrice, boughtPrice, onConfirm) {
    const html = `<div class="modal-header">${this.escapeHtml(title)}</div>
      <div class="modal-body">
        <div class="qty-info">${this.escapeHtml(info)}</div>
        <div class="sell-info">
          <div>Market Price: <strong>${formatMoney(curPrice)}</strong></div>
          <div>Profit per unit: <strong class="${curPrice - boughtPrice >= 0 ? 'profit' : 'loss'}">${formatMoney(curPrice - boughtPrice)}</strong></div>
        </div>
        <div class="qty-controls">
          <input type="range" id="qty-slider" min="${min}" max="${max}" value="${initial}" class="qty-slider">
          <div class="qty-input-row">
            <input type="number" id="qty-input" min="${min}" max="${max}" value="${initial}" class="qty-input">
            <button class="btn btn-sm" id="qty-max">Max</button>
          </div>
        </div>
        <div class="sell-totals">
          <div>Total Worth: <strong id="sell-worth">${formatMoney(initial * curPrice)}</strong></div>
          <div>Total Profit: <strong id="sell-profit" class="${(initial * curPrice) - (initial * boughtPrice) >= 0 ? 'profit' : 'loss'}">${formatMoney((initial * curPrice) - (initial * boughtPrice))}</strong></div>
        </div>
        <div class="modal-actions">
          <button class="btn btn-action" id="qty-ok">Sell</button>
          <button class="btn btn-cancel" id="qty-cancel">Cancel</button>
        </div>
      </div>`;

    this.showModal(html, 'sell-modal');

    const slider = document.getElementById('qty-slider');
    const input = document.getElementById('qty-input');
    const worthEl = document.getElementById('sell-worth');
    const profitEl = document.getElementById('sell-profit');

    const updateTotals = (qty) => {
      const worth = qty * curPrice;
      const profit = (qty * curPrice) - (qty * boughtPrice);
      worthEl.textContent = formatMoney(worth);
      profitEl.textContent = formatMoney(profit);
      profitEl.className = profit >= 0 ? 'profit' : 'loss';
    };

    slider.addEventListener('input', () => {
      input.value = slider.value;
      updateTotals(parseInt(slider.value));
    });
    input.addEventListener('input', () => {
      let v = parseInt(input.value) || min;
      if (v < min) v = min;
      if (v > max) v = max;
      slider.value = v;
      updateTotals(v);
    });
    document.getElementById('qty-max').addEventListener('click', () => {
      slider.value = max;
      input.value = max;
      updateTotals(max);
    });

    document.getElementById('qty-ok').addEventListener('click', () => {
      let val = parseInt(input.value) || min;
      if (val < min) val = min;
      if (val > max) val = max;
      this.closeModal();
      onConfirm(val);
    });
    document.getElementById('qty-cancel').addEventListener('click', () => {
      this.closeModal();
    });
  }

  showPlayerNamePrompt(callback) {
    const html = `<div class="modal-header">Enter Your Name</div>
      <div class="modal-body">
        <input type="text" id="player-name-input" class="name-input" placeholder="Your name..." maxlength="20" value="${this.escapeHtml(this.engine.playerName || '')}">
        <div class="modal-actions">
          <button class="btn btn-action" id="name-ok">OK</button>
        </div>
      </div>`;

    this.showModal(html, 'name-modal');

    const nameInput = document.getElementById('player-name-input');
    nameInput.focus();

    const submit = () => {
      const name = nameInput.value.trim() || "Anonymous";
      this.closeModal();
      callback(name);
    };

    document.getElementById('name-ok').addEventListener('click', submit);
    nameInput.addEventListener('keypress', (e) => {
      if (e.key === 'Enter') submit();
    });
  }

  escapeHtml(text) {
    const div = document.createElement('div');
    div.textContent = text;
    return div.innerHTML;
  }
}

// Initialize game
document.addEventListener('DOMContentLoaded', () => {
  const engine = new GameEngine();
  const ui = new GameUI(engine);
  window.game = { engine, ui }; // For debugging
});
