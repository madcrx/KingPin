// KingPin - Transaction Animations
// Simple, Apple Watch-friendly animated toasts after each game action

const Anim = (() => {
  let container = null;
  let timeout = null;

  function init() {
    container = document.getElementById('anim-overlay');
  }

  // Show a transaction animation
  function show(type) {
    if (!container) init();
    if (!container) return;

    // Clear any running animation
    clearTimeout(timeout);
    container.innerHTML = '';
    container.className = 'anim-overlay anim-active';

    const anim = buildAnimation(type);
    if (!anim) return;

    container.appendChild(anim);

    // Auto-dismiss
    const duration = 1200;
    timeout = setTimeout(() => {
      container.className = 'anim-overlay anim-fade';
      setTimeout(() => {
        container.className = 'anim-overlay';
        container.innerHTML = '';
      }, 300);
    }, duration);
  }

  function buildAnimation(type) {
    const wrap = document.createElement('div');
    wrap.className = 'anim-scene';

    switch (type) {
      case 'buy-drug':
        wrap.innerHTML = buildBuyDrug();
        break;
      case 'sell-drug':
        wrap.innerHTML = buildSellDrug();
        break;
      case 'drop-drug':
        wrap.innerHTML = buildDropDrug();
        break;
      case 'buy-gun':
        wrap.innerHTML = buildBuyGun();
        break;
      case 'sell-gun':
        wrap.innerHTML = buildSellGun();
        break;
      case 'travel':
        wrap.innerHTML = buildTravel();
        break;
      case 'deposit':
        wrap.innerHTML = buildDeposit();
        break;
      case 'withdraw':
        wrap.innerHTML = buildWithdraw();
        break;
      case 'borrow':
        wrap.innerHTML = buildBorrow();
        break;
      case 'payback':
        wrap.innerHTML = buildPayback();
        break;
      case 'heal':
        wrap.innerHTML = buildHeal();
        break;
      case 'fight-hit':
        wrap.innerHTML = buildFightHit();
        break;
      case 'fight-win':
        wrap.innerHTML = buildFightWin();
        break;
      case 'fight-miss':
        wrap.innerHTML = buildFightMiss();
        break;
      case 'escape':
        wrap.innerHTML = buildEscape();
        break;
      case 'arrest':
        wrap.innerHTML = buildArrest();
        break;
      case 'coat':
        wrap.innerHTML = buildCoat();
        break;
      case 'mugged':
        wrap.innerHTML = buildMugged();
        break;
      default:
        return null;
    }

    return wrap;
  }

  // ── SVG helpers ──

  function svg(w, h, content, cls) {
    return `<svg class="anim-svg ${cls || ''}" viewBox="0 0 ${w} ${h}" width="${w}" height="${h}">${content}</svg>`;
  }

  // ── Animation builders ──
  // Each returns an SVG string with animated elements

  function buildBuyDrug() {
    // Pill capsule dropping in with bounce
    return svg(80, 80, `
      <g class="anim-drop-bounce">
        <rect x="24" y="30" width="32" height="18" rx="9" fill="#00ff88" opacity="0.9"/>
        <line x1="40" y1="30" x2="40" y2="48" stroke="#0a0a0f" stroke-width="2"/>
        <rect x="24" y="30" width="16" height="18" rx="9" fill="#00cc66" opacity="0.7"/>
      </g>
      <g class="anim-coins-fall">
        <circle cx="20" cy="10" r="6" fill="#ffd700" opacity="0.8"/>
        <text x="20" y="14" text-anchor="middle" font-size="9" font-weight="bold" fill="#0a0a0f">$</text>
        <circle cx="58" cy="14" r="5" fill="#ffd700" opacity="0.6"/>
        <text x="58" y="17.5" text-anchor="middle" font-size="7" font-weight="bold" fill="#0a0a0f">$</text>
      </g>
    `);
  }

  function buildSellDrug() {
    // Cash rising up with glow
    return svg(80, 80, `
      <g class="anim-cash-rise">
        <rect x="22" y="36" width="36" height="20" rx="3" fill="#00ff88" opacity="0.9"/>
        <text x="40" y="50" text-anchor="middle" font-size="14" font-weight="bold" fill="#0a0a0f">$</text>
      </g>
      <g class="anim-cash-rise-delay1">
        <rect x="14" y="42" width="24" height="14" rx="2" fill="#00cc66" opacity="0.6"/>
        <text x="26" y="52" text-anchor="middle" font-size="10" font-weight="bold" fill="#0a0a0f">$</text>
      </g>
      <g class="anim-cash-rise-delay2">
        <rect x="44" y="44" width="22" height="12" rx="2" fill="#00ff88" opacity="0.5"/>
        <text x="55" y="53" text-anchor="middle" font-size="9" font-weight="bold" fill="#0a0a0f">$</text>
      </g>
      <circle class="anim-glow-pulse" cx="40" cy="40" r="30" fill="none" stroke="#00ff88" stroke-width="2" opacity="0.3"/>
    `);
  }

  function buildDropDrug() {
    // Pill tumbling down
    return svg(80, 80, `
      <g class="anim-tumble-fall">
        <rect x="28" y="20" width="24" height="14" rx="7" fill="#888" opacity="0.7"/>
        <line x1="40" y1="20" x2="40" y2="34" stroke="#555" stroke-width="1.5"/>
      </g>
      <g class="anim-puff" opacity="0">
        <circle cx="40" cy="65" r="4" fill="#666" opacity="0.4"/>
        <circle cx="32" cy="62" r="3" fill="#555" opacity="0.3"/>
        <circle cx="48" cy="63" r="3.5" fill="#555" opacity="0.3"/>
      </g>
    `);
  }

  function buildBuyGun() {
    // Gun silhouette with muzzle flash
    return svg(80, 80, `
      <g class="anim-gun-recoil">
        <rect x="16" y="34" width="38" height="8" rx="2" fill="#aaa"/>
        <rect x="36" y="34" width="10" height="20" rx="2" fill="#999"/>
        <rect x="10" y="32" width="8" height="12" rx="1" fill="#bbb"/>
      </g>
      <g class="anim-muzzle-flash">
        <polygon points="8,38 0,32 2,38 0,44" fill="#ffd700" opacity="0.9"/>
        <polygon points="6,38 -2,30 0,38 -2,46" fill="#ff6600" opacity="0.6"/>
      </g>
      <g class="anim-shell-eject">
        <rect x="42" y="30" width="4" height="7" rx="1" fill="#ffd700" opacity="0.8"/>
      </g>
    `);
  }

  function buildSellGun() {
    // Gun fading + cash appearing
    return svg(80, 80, `
      <g class="anim-fade-out-left">
        <rect x="20" y="34" width="30" height="7" rx="2" fill="#888"/>
        <rect x="34" y="34" width="8" height="16" rx="2" fill="#777"/>
      </g>
      <g class="anim-cash-rise">
        <circle cx="55" cy="35" r="10" fill="#ffd700" opacity="0.8"/>
        <text x="55" y="39" text-anchor="middle" font-size="12" font-weight="bold" fill="#0a0a0f">$</text>
      </g>
    `);
  }

  function buildTravel() {
    // Arrow/jet whooshing across
    const loc = randomFrom(['Bronx', 'Ghetto', 'Manhattan', 'Brooklyn', 'Queens']);
    return svg(80, 80, `
      <g class="anim-jet-whoosh">
        <polygon points="50,40 30,30 34,40 30,50" fill="#00ccff" opacity="0.9"/>
        <rect x="50" y="37" width="14" height="6" rx="3" fill="#00aadd" opacity="0.7"/>
      </g>
      <line class="anim-trail-1" x1="10" y1="38" x2="30" y2="38" stroke="#00ccff" stroke-width="2" opacity="0" stroke-linecap="round"/>
      <line class="anim-trail-2" x1="5" y1="42" x2="26" y2="42" stroke="#0088aa" stroke-width="1.5" opacity="0" stroke-linecap="round"/>
      <line class="anim-trail-3" x1="15" y1="35" x2="28" y2="35" stroke="#00ccff" stroke-width="1" opacity="0" stroke-linecap="round"/>
    `);
  }

  function buildDeposit() {
    // Coin dropping into slot
    return svg(80, 80, `
      <rect x="20" y="45" width="40" height="24" rx="4" fill="#2a2a4a" stroke="#3a3a6a" stroke-width="2"/>
      <rect x="32" y="42" width="16" height="4" rx="2" fill="#3a3a6a"/>
      <g class="anim-coin-drop">
        <circle cx="40" cy="12" r="8" fill="#ffd700" opacity="0.9"/>
        <text x="40" y="16" text-anchor="middle" font-size="10" font-weight="bold" fill="#0a0a0f">$</text>
      </g>
      <text x="40" y="61" text-anchor="middle" font-size="9" font-weight="bold" fill="#3a3a6a">BANK</text>
    `);
  }

  function buildWithdraw() {
    // Coin rising out of vault
    return svg(80, 80, `
      <rect x="20" y="45" width="40" height="24" rx="4" fill="#2a2a4a" stroke="#3a3a6a" stroke-width="2"/>
      <rect x="32" y="42" width="16" height="4" rx="2" fill="#3a3a6a"/>
      <g class="anim-coin-rise">
        <circle cx="40" cy="56" r="8" fill="#ffd700" opacity="0.9"/>
        <text x="40" y="60" text-anchor="middle" font-size="10" font-weight="bold" fill="#0a0a0f">$</text>
      </g>
      <text x="40" y="61" text-anchor="middle" font-size="9" font-weight="bold" fill="#3a3a6a">BANK</text>
    `);
  }

  function buildBorrow() {
    // Bills fanning out from center
    return svg(80, 80, `
      <g class="anim-fan-out-1">
        <rect x="28" y="30" width="24" height="14" rx="2" fill="#ff6644" opacity="0.7"/>
        <text x="40" y="40" text-anchor="middle" font-size="9" font-weight="bold" fill="#fff">$</text>
      </g>
      <g class="anim-fan-out-2">
        <rect x="28" y="34" width="24" height="14" rx="2" fill="#ff4422" opacity="0.6"/>
        <text x="40" y="44" text-anchor="middle" font-size="9" font-weight="bold" fill="#fff">$</text>
      </g>
      <g class="anim-fan-out-3">
        <rect x="28" y="38" width="24" height="14" rx="2" fill="#cc3322" opacity="0.5"/>
        <text x="40" y="48" text-anchor="middle" font-size="9" font-weight="bold" fill="#fff">$</text>
      </g>
      <text x="40" y="70" text-anchor="middle" font-size="8" fill="#ff4444" class="anim-text-fade">DEBT</text>
    `);
  }

  function buildPayback() {
    // Bills collapsing inward + checkmark
    return svg(80, 80, `
      <g class="anim-collapse-in-1">
        <rect x="10" y="32" width="22" height="12" rx="2" fill="#00cc66" opacity="0.7"/>
        <text x="21" y="41" text-anchor="middle" font-size="8" font-weight="bold" fill="#0a0a0f">$</text>
      </g>
      <g class="anim-collapse-in-2">
        <rect x="48" y="34" width="22" height="12" rx="2" fill="#00cc66" opacity="0.7"/>
        <text x="59" y="43" text-anchor="middle" font-size="8" font-weight="bold" fill="#0a0a0f">$</text>
      </g>
      <g class="anim-check-appear">
        <polyline points="30,42 38,50 54,30" fill="none" stroke="#00ff88" stroke-width="4" stroke-linecap="round" stroke-linejoin="round"/>
      </g>
    `);
  }

  function buildHeal() {
    // Medical cross with heartbeat pulse
    return svg(80, 80, `
      <g class="anim-heal-pulse">
        <rect x="34" y="20" width="12" height="36" rx="2" fill="#ff4444"/>
        <rect x="22" y="32" width="36" height="12" rx="2" fill="#ff4444"/>
      </g>
      <polyline class="anim-heartbeat" points="10,60 20,60 26,50 32,70 38,55 42,60 50,60"
        fill="none" stroke="#ff4444" stroke-width="2.5" stroke-linecap="round" stroke-linejoin="round" opacity="0"/>
      <circle class="anim-heal-glow" cx="40" cy="38" r="24" fill="none" stroke="#ff4444" stroke-width="1.5" opacity="0"/>
    `);
  }

  function buildFightHit() {
    // Impact starburst
    return svg(80, 80, `
      <g class="anim-impact-burst">
        <polygon points="40,10 44,30 60,18 48,34 70,36 48,42 60,58 44,48 40,68 36,48 20,58 32,42 10,36 32,34 20,18 36,30"
          fill="#ff6600" opacity="0.9"/>
        <polygon points="40,20 43,32 52,24 46,35 58,36 46,40 52,50 43,44 40,56 37,44 28,50 34,40 22,36 34,35 28,24 37,32"
          fill="#ffd700" opacity="0.8"/>
      </g>
    `);
  }

  function buildFightWin() {
    // Victory star with sparkles
    return svg(80, 80, `
      <g class="anim-victory-spin">
        <polygon points="40,8 46,28 68,28 50,40 56,60 40,48 24,60 30,40 12,28 34,28"
          fill="#ffd700" opacity="0.9"/>
      </g>
      <circle class="anim-sparkle-1" cx="18" cy="16" r="2" fill="#fff" opacity="0"/>
      <circle class="anim-sparkle-2" cx="64" cy="20" r="2.5" fill="#fff" opacity="0"/>
      <circle class="anim-sparkle-3" cx="14" cy="54" r="2" fill="#ffd700" opacity="0"/>
      <circle class="anim-sparkle-4" cx="68" cy="58" r="1.5" fill="#ffd700" opacity="0"/>
    `);
  }

  function buildFightMiss() {
    // Whoosh/dodge lines
    return svg(80, 80, `
      <line class="anim-whoosh-1" x1="10" y1="30" x2="55" y2="28" stroke="#888" stroke-width="3" stroke-linecap="round" opacity="0"/>
      <line class="anim-whoosh-2" x1="5" y1="40" x2="60" y2="38" stroke="#666" stroke-width="2" stroke-linecap="round" opacity="0"/>
      <line class="anim-whoosh-3" x1="12" y1="50" x2="52" y2="48" stroke="#888" stroke-width="2.5" stroke-linecap="round" opacity="0"/>
      <text class="anim-miss-text" x="40" y="68" text-anchor="middle" font-size="11" font-weight="bold" fill="#666" opacity="0">MISS</text>
    `);
  }

  function buildEscape() {
    // Speed lines + running figure hint
    return svg(80, 80, `
      <g class="anim-runner">
        <circle cx="50" cy="28" r="6" fill="#00ccff" opacity="0.8"/>
        <line x1="50" y1="34" x2="50" y2="50" stroke="#00ccff" stroke-width="2.5" stroke-linecap="round"/>
        <line x1="50" y1="42" x2="42" y2="36" stroke="#00ccff" stroke-width="2" stroke-linecap="round"/>
        <line x1="50" y1="42" x2="58" y2="38" stroke="#00ccff" stroke-width="2" stroke-linecap="round"/>
        <line x1="50" y1="50" x2="42" y2="60" stroke="#00ccff" stroke-width="2" stroke-linecap="round"/>
        <line x1="50" y1="50" x2="58" y2="58" stroke="#00ccff" stroke-width="2" stroke-linecap="round"/>
      </g>
      <line class="anim-speed-1" x1="8" y1="30" x2="28" y2="30" stroke="#00ccff" stroke-width="2" stroke-linecap="round" opacity="0"/>
      <line class="anim-speed-2" x1="4" y1="40" x2="22" y2="40" stroke="#0088aa" stroke-width="1.5" stroke-linecap="round" opacity="0"/>
      <line class="anim-speed-3" x1="10" y1="50" x2="26" y2="50" stroke="#00ccff" stroke-width="1.5" stroke-linecap="round" opacity="0"/>
    `);
  }

  function buildArrest() {
    // Jail bars sliding down
    return svg(80, 80, `
      <g class="anim-bars-drop">
        <rect x="16" y="0" width="4" height="64" rx="2" fill="#888" opacity="0.8"/>
        <rect x="28" y="0" width="4" height="64" rx="2" fill="#888" opacity="0.8"/>
        <rect x="40" y="0" width="4" height="64" rx="2" fill="#888" opacity="0.8"/>
        <rect x="52" y="0" width="4" height="64" rx="2" fill="#888" opacity="0.8"/>
        <rect x="64" y="0" width="4" height="64" rx="2" fill="#888" opacity="0.8"/>
        <rect x="12" y="0" width="60" height="4" rx="2" fill="#aaa"/>
        <rect x="12" y="60" width="60" height="4" rx="2" fill="#aaa"/>
      </g>
      <text class="anim-text-fade" x="40" y="76" text-anchor="middle" font-size="8" fill="#ff4444">BUSTED</text>
    `);
  }

  function buildCoat() {
    // Trenchcoat expanding
    return svg(80, 80, `
      <g class="anim-coat-expand">
        <polygon points="40,12 26,24 20,62 60,62 54,24" fill="#8B4513" opacity="0.8"/>
        <polygon points="40,12 26,24 28,62 40,62" fill="#A0522D" opacity="0.7"/>
        <rect x="36" y="14" width="8" height="4" rx="2" fill="#654321"/>
        <line x1="40" y1="24" x2="40" y2="58" stroke="#654321" stroke-width="1"/>
        <circle cx="38" cy="32" r="1.5" fill="#654321"/>
        <circle cx="38" cy="40" r="1.5" fill="#654321"/>
        <circle cx="38" cy="48" r="1.5" fill="#654321"/>
      </g>
      <text class="anim-text-fade" x="40" y="76" text-anchor="middle" font-size="7" fill="#8B4513">+20</text>
    `);
  }

  function buildMugged() {
    // Red flash / danger
    return svg(80, 80, `
      <g class="anim-shake">
        <text x="40" y="48" text-anchor="middle" font-size="36" font-weight="bold" fill="#ff4444" opacity="0.9">!</text>
      </g>
      <circle class="anim-danger-ring" cx="40" cy="40" r="30" fill="none" stroke="#ff4444" stroke-width="3" opacity="0"/>
      <circle class="anim-danger-ring-2" cx="40" cy="40" r="20" fill="none" stroke="#ff2222" stroke-width="2" opacity="0"/>
    `);
  }

  // ── Utility ──

  function randomFrom(arr) {
    return arr[Math.floor(Math.random() * arr.length)];
  }

  return { show };
})();
