# Tic-Tac-Toe — Tres en Raya

A two-player Tic-Tac-Toe game with a graphical interface built in C++11 using SFML. Developed as the second partial project for the Object-Oriented Programming subject — Telecommunications and Electronics Engineering.

---

## Features

- Two human players on the same device
- Automatic win and draw detection with winning line highlight
- Undo last move with **Z** key (only during active round)
- Round history shown on the right side of the board
- Save and load mid-game state with **S** key
- Global player statistics saved across sessions
- View player stats at any time with **H** key

---

## Dependencies

- C++11 or higher
- [SFML 2.6.1](https://www.sfml-dev.org/download/sfml/2.6.1/)
- [nlohmann/json](https://github.com/nlohmann/json) (already included in `lib/nlohmann/json.hpp`)
- A font file named `fuente.ttf` inside the `assets/` folder

---

## Project Structure

```
project/
├── src/
│   ├── main.cpp
│   ├── dominio/
│   │   ├── Simbolo.h
│   │   ├── Ficha.h
│   │   ├── Jugador.h
│   │   └── Tablero.h
│   ├── logica/
│   │   ├── EstadoJuego.h
│   │   ├── Partida.h
│   │   └── GestorPartidas.h
│   └── presentacion/
│       ├── Render.h
│       └── Interfaz.h
├── lib/
│   └── nlohmann/
│       └── json.hpp
├── data/
│   ├── partida.json
│   └── jugadores.json
├── assets/
│   ├── fuente.ttf
│   ├── sfml-system-2.dll
│   └── libsfml-system.a
└── README.md
```

Saved game data is stored automatically in the `data/` folder when you press **S** or go back to the main menu.

---

## How to Compile

### Linux

Make sure SFML is installed:
```bash
sudo apt install libsfml-dev
```

Then compile:
```bash
g++ -std=c++11 -o TresEnRaya src/main.cpp -lsfml-graphics -lsfml-window -lsfml-system
```

Run:
```bash
./TresEnRaya
```

---

### Windows (terminal with MinGW)

```bash
g++ -std=c++11 -o TresEnRaya src/main.cpp -I"C:/SFML/include" -L"C:/SFML/lib" -lsfml-graphics -lsfml-window -lsfml-system
```

Copy the DLL files from `C:/SFML/bin/` to the same folder as the generated `.exe`:
```
sfml-graphics-2.dll
sfml-window-2.dll
sfml-system-2.dll
```

> **Important — DLL fix:** if you get an error about a missing entry point in `sfml-system-2.dll`, use the fixed files included in the `assets/` folder of this repository:
> - Copy `assets/sfml-system-2.dll` → replace the one in `C:/SFML/bin/` and in your `.exe` folder
> - Copy `assets/libsfml-system.a` → replace the one in `C:/SFML/lib/`

---

### Code::Blocks

This project was developed and tested with **Code::Blocks + MinGW 13.1.0** and **SFML 2.6.1 for MinGW**.

Download links:
- [SFML 2.6.1 — GCC 13.1.0 MinGW (SEH) 64-bit](https://www.sfml-dev.org/download/sfml/2.6.1/)
- [MinGW 13.1.0 64-bit](https://github.com/niXman/mingw-builds-binaries/releases)

> Make sure the MinGW version in Code::Blocks matches the one used to build SFML (13.1.0). Using a different version will cause linking errors.

**Setup steps:**

1. Go to **Settings → Compiler → Search directories → Compiler** and add:
   ```
   C:\SFML\include
   ```

2. Go to **Settings → Compiler → Search directories → Linker** and add:
   ```
   C:\SFML\lib
   ```

3. Go to **Settings → Compiler → Linker settings → Link libraries** and add:
   ```
   sfml-graphics
   sfml-window
   sfml-system
   ```

4. Go to **Settings → Compiler → Compiler flags** and enable:
   ```
   Have g++ follow the C++11 ISO standard
   ```

5. Copy the following DLL files from `C:\SFML\bin\` to the folder where Code::Blocks generates the `.exe` (usually `bin/Debug/`):
   ```
   sfml-graphics-2.dll
   sfml-window-2.dll
   sfml-system-2.dll
   ```

6. Apply the DLL fix from the `assets/` folder (see Windows section above).

Press **F9** to build and run.

---

## Classes

| Class | Layer | Description |
|---|---|---|
| `Ficha` | Domain | Abstract base class for game pieces |
| `FichaX`, `FichaO` | Domain | Concrete pieces, inherit from `Ficha` |
| `Jugador` | Domain | Player with name, symbol and statistics |
| `Tablero` | Domain | 3x3 board, tracks occupied cells |
| `Partida` | Logic | Game flow, turn management, win detection |
| `GestorPartidas` | Logic | Save and load game data as JSON |
| `Render` | Presentation | Draws everything using SFML |
| `Interfaz` | Presentation | Main game loop, handles events and screens |

---

## STL Containers

| Container | Where | Why |
|---|---|---|
| `std::set<int>` | `Tablero` | Tracks occupied cells. Used in move validation, undo (`erase`), draw detection and hover highlighting via `celdasLibres()` |
| `std::vector<string>` | `Interfaz` | Stores the round results of the current session. Grows each round and is displayed on the right panel |
| `std::map<string, DatosJugador>` | `GestorPartidas` | Stores player statistics by name across sessions. Allows fast lookup and is persisted in `jugadores.json` |

---

## Authors

Developed as part of the **second partial exam of the Programming subject** — Career: Telecommunications and Electronics Engineering.

1. Israel Córdova Espinosa 
2. Willian Luis Rabeiro Águila 
3. Leyan Barrios Bosque
4. Alejandro Luzardo Bencomo Seguí
5. Gabriel Fonte Gómez 
6. Remberto Santalla Ramos
7. Luis José León García
8. Lilianny Paez Beltrán
