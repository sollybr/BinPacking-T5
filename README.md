# 📦 Bin Packing Metaheuristics Project

This project implements heuristic and metaheuristic approaches for the Bin Packing Problem, including:

- First Fit (FF)
- Best Fit (BF)
- MultiStart Random (MR)
- Local Search (exhaustive neighborhood exploration)

---

# ⚙️ Build Requirements

This project supports multiple toolchains. You only need **one** of the options below.

---

## 🟢 Option 1 — MSYS2 + GCC + Ninja (Recommended)

This is the recommended setup for development and experimentation.

### 📥 Install MSYS2

Download from:

[https://www.msys2.org/](https://www.msys2.org/)

Install in any directory (e.g., default or custom path).

---

### 📦 Install required packages

Open the **MSYS2 UCRT64 terminal** and run:

```
pacman -S --needed mingw-w64-ucrt-x86_64-toolchain
pacman -S --needed mingw-w64-ucrt-x86_64-cmake
pacman -S --needed mingw-w64-ucrt-x86_64-ninja
```

This installs:

- GCC compiler
- CMake
- Ninja build system

---

### 🚀 Build project

**Inside the MSYS2 UCRT64 terminal:**

```
cmake -S . -B build -G "Ninja"
cmake --build build
```

---

## 🟡 Option 2 — Ninja + existing compiler

If you already have a C compiler installed (GCC or Clang), you can use Ninja directly.

### 📥 Install Ninja

Download from:

[Releases · ninja-build/ninja · GitHub](https://github.com/ninja-build/ninja/releases)

Ensure it is available in your system PATH.

Verify:

```
ninja --version
```

---

### 🚀 Build project

```
cmake -S . -B build -G "Ninja"
cmake --build build
```

---

## 🔵 Option 3 — Microsoft Visual Studio (MSVC)

If using Visual Studio Build Tools:

### 📥 Install

Download:

[VS Studio Downloads](https://visualstudio.microsoft.com/downloads/)

Install:

- “Desktop development with C++”

---

### ⚠️ Important

Use the correct terminal:

```
x64 Native Tools Command Prompt for VS
```

---

### 🚀 Build project

```
cmake -S . -B buildcmake --build build
```

CMake will automatically select the appropriate generator (NMake or MSBuild).

---

# ❗ Troubleshooting

## “No toolchain found”

This means CMake cannot find:

- a C compiler (gcc or cl)
- or a build system (ninja / make / msbuild)

Check:

```
gcc --versionclninja --versioncmake --version
```

---

## PATH issues

If using MSYS2:

- Do NOT manually configure Windows PATH unless you know what you're doing
- Always prefer running inside the MSYS2 terminal

---

# 🧠 Recommended Setup

For this project (metaheuristics + experiments):

| Toolchain                  | Recommendation                      |
| -------------------------- | ----------------------------------- |
| MSYS2 + GCC + Ninja        | ⭐ Best (fast, reproducible, simple) |
| Ninja + existing GCC/Clang | Good                                |
| MSVC                       | OK but heavier setup                |
| Raw CMD builds (Win)       | Not recommended                     |

---

# 🚀 Typical workflow

```
cmake -S . -B build -G Ninja
cmake --build build
./binpacking filename --partidas 50 --tempo 5 --vizinhanca 1000
```
