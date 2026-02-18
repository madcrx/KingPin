# KingPin - Drug Wars for the Web

A faithful web port of the classic **Drug Wars** / **Pocket DopeWars** game, originally a Windows CE/MFC C++ application by AtomWare, based on John E. Dell's 1984 original.

## How to Play

You are a drug dealer in New York City. You have **30 days** to pay off your $5,500 debt to the loan shark and make as much money as possible.

**Open `index.html` in any modern browser to play.** No build step, no dependencies.

### Game Mechanics

- **Travel** between 8 NYC districts (Bronx, Ghetto, Central Park, Manhattan, Coney Island, Brooklyn, Queens, Staten Island)
- **Buy low, sell high** - drug prices fluctuate daily with random market events
- **Avoid the cops** - police encounters let you fight, run, or surrender
- **Finance** - deposit/withdraw at the bank (Bronx), borrow from the loan shark
- **Guns** - buy weapons at the gun shop (Ghetto) to fight cops
- **Hospital** - heal injuries (Queens)
- **Trenchcoat** - random offers to increase your carrying capacity

### Special Locations

| Location | Feature |
|----------|---------|
| Bronx | Bank & Loan Shark |
| Ghetto | Gun Shop |
| Queens | Hospital |

### Tips

- Debt grows 10% per day, bank savings grow 5% per day
- Watch for market events - "cheap" deals (red) and "expensive" busts (blue) can mean huge profits
- Cops scale with your net worth - the richer you get, the more heat you attract
- Guns take up coat space but let you fight back during encounters

## Project Structure

```
index.html          - Main entry point
css/style.css       - Dark retro-modern theme
js/config.js        - Game constants, drug/gun/location data
js/engine.js        - Core game logic (faithful C++ port)
js/ui.js            - UI controller, modals, rendering
```

## Origins

Ported from the original C++ Windows CE/MFC source code by AtomWare. Every game mechanic — price generation, cop encounters, events, finance, combat — has been faithfully recreated in vanilla JavaScript.

## Testing on Windows PC (with iOS Preview)

Want to see how the game looks and feels on an iPhone or iPad, but you only have a Windows PC? Follow these steps using **free tools**.

### What You Need

| Tool | Purpose | Download |
|------|---------|----------|
| **Google Chrome** | Browser with built-in device emulator | [google.com/chrome](https://www.google.com/chrome/) |

That's it — Chrome is the only tool required. No installs beyond the browser itself.

### Step-by-Step Guide

#### 1. Get the Files from GitHub

**Option A — Download as ZIP (easiest, no Git needed):**
1. Go to the repository on GitHub
2. Click the green **"Code"** button
3. Click **"Download ZIP"**
4. Extract the ZIP to any folder on your PC (e.g. `C:\KingPin`)

**Option B — Clone with Git (if you have Git installed):**
```
git clone https://github.com/madcrx/KingPin.git
```

#### 2. Open the Game in Chrome

1. Open **Google Chrome**
2. Press `Ctrl + O` (or drag the file into Chrome)
3. Navigate to the extracted folder and open **`index.html`**
4. The game loads — you can play it right now in desktop view

#### 3. Open Chrome DevTools

Press **`F12`** on your keyboard (or `Ctrl + Shift + I`)

This opens the Chrome Developer Tools panel on the right side of the screen.

#### 4. Enable Device Emulation (iOS Preview)

1. In the DevTools panel, click the **Toggle Device Toolbar** button — it looks like a small phone/tablet icon in the top-left corner of DevTools (or press `Ctrl + Shift + M`)
2. A toolbar appears above the page with a device dropdown menu
3. Click the device dropdown (it may say "Dimensions: Responsive")
4. Select an iOS device from the list:
   - **iPhone SE** — smaller iPhone screen
   - **iPhone XR** — standard iPhone
   - **iPhone 12 Pro** — modern iPhone
   - **iPhone 14 Pro Max** — large iPhone
   - **iPad Air** — tablet view
   - **iPad Mini** — smaller tablet view
5. The page reloads in that device's screen size and resolution

#### 5. Fine-Tune the Preview

- **Rotate:** Click the rotate icon (↻) in the device toolbar to switch between portrait and landscape
- **Zoom:** If the emulated screen is too small, change the zoom % in the device toolbar (e.g. 75%, 100%, 125%)
- **Touch simulation:** Chrome automatically simulates touch events — clicks become taps, drag becomes swipe
- **Add more devices:** Click the device dropdown → **"Edit..."** at the bottom to enable additional devices (iPod Touch, older iPhones, etc.)

#### 6. Test Different Screen Sizes

Repeat step 4 with different devices to make sure the game looks good on:
- Small phones (iPhone SE — 375×667)
- Standard phones (iPhone 12 Pro — 390×844)
- Large phones (iPhone 14 Pro Max — 430×932)
- Tablets (iPad Air — 820×1180)

### Quick Reference

| Action | Shortcut |
|--------|----------|
| Open DevTools | `F12` or `Ctrl + Shift + I` |
| Toggle device mode | `Ctrl + Shift + M` |
| Refresh page | `F5` |
| Hard refresh (clear cache) | `Ctrl + Shift + R` |

### Important Notes

- Chrome's device emulator is a **visual approximation** — it matches screen size, pixel ratio, and touch behavior but does not run actual iOS Safari. For 99% of web games like this, it is accurate enough.
- The game uses responsive CSS and works across all screen sizes, so it should display correctly on any emulated device.
- No internet connection is needed after downloading — the game runs entirely offline.
