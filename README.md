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

## Original Source

The `*.cpp`, `*.h`, `*.rc` files are the original C++ Windows CE/MFC source code from which this web version was ported. Every game mechanic - price generation, cop encounters, events, finance, combat - has been faithfully recreated.
