# Rocky

Rocky is a Just-In-Time (JIT) compiler project that uses LLVM's ORCJIT API as its backend. The goal is to implement a compact language and compiler pipeline able to JIT-compile programs and run simple games (for example, Pong or Tic-Tac-Toe) using Raylib bindings. The project includes a C-based frontend, a testing suite, and build automation via Pixi.

Project Website - [https://rocky.sohamk10.workers.dev/](https://rocky.sohamk10.workers.dev/)

## Project goals

- Implement a toy programming language and a complete compiler pipeline:
  - Lexer → Parser → AST → IR → ORCJIT codegen → runtime
- Use LLVM ORCJIT to compile code at runtime.
- Provide bindings (or a small runtime) so compiled programs can use Raylib to run simple graphical demos (Pong, Tic-Tac-Toe).
- Provide a clean C-based codebase with unit and integration tests.

## Key tools

- **Pixi** — package manager and task runner used to provision toolchains and invoke build/test tasks. Install first; it will install the rest of the required tools automatically.
- **Git** — source control.
- **CMake** + **Ninja** — build system (managed by Pixi).
- **Clang** on Linux, **MSVC** on Windows — system C/C++ compilers (installed by Pixi where needed).
- **LLVM** — provided by Pixi for testing and JIT backend.

> **Note:** You only need to install Pixi and Git manually; everything else is handled by Pixi.

## Quickstart — Setup & build

### 1. Install Pixi and Git

#### Windows

- Install Pixi:
  - Follow the [Pixi installation guide](https://pixi.prefix.dev/latest/installation/#__tabbed_1_2).
  - Verify using `pixi --help` in CMD and PowerShell.
- Install Git:
  - Follow the [Git installation guide](https://git-scm.com/install/windows).
  - Verify using `git --help` in CMD and PowerShell.

#### Linux

- Install Pixi:
  - Follow the [Pixi installation guide](https://pixi.prefix.dev/latest/installation/#__tabbed_1_1).
  - Verify using `pixi --help`.
- Install Git:
  - Install using your package manager, or run `pixi global install git`.
  - See the [Git installation guide](https://git-scm.com/install/linux) for package manager links.

### 2. Clone the repository

Clone the repository, enter it, and recursively initialize submodules:

- `git clone https://github.com/skadewdl3/rocky.git`
- `cd rocky`
- `git submodule update --init --recursive --remote`

### 3. Install toolchain and dependencies via Pixi

- `pixi install`

### 4. Configure the project

- `pixi run configure` — configures the build (provisions native compilers on first run; on Windows this step installs MSVC on first run).

### 5. Build and run the sample

#### `pixi run run`

Builds and runs the main example/program. The sample run prints assembly and exercises the front-end pipeline.

**Notes:**

- Windows users: prefer running commands from the Windows Command Prompt (CMD) rather than PowerShell when using the provided Pixi tasks.
- Pixi handles CMake, Ninja, LLVM toolchains, and other dependencies automatically — do not attempt to install these manually unless you have a special requirement.

## Command summary

- `pixi install` — install required tools managed by Pixi.
- `pixi run configure` — configure the build (provisions native compilers on first run).
- `pixi run run` — build and run the main example/program.
- `pixi run test` — run the test suite via ctest (see [Testing](#testing) below).
- `pixi run lit` — run Lit-based integration tests.

## Project layout (important paths)

- `src/` — compiler implementation and front-end (`src/main.c` is the CLI entrypoint).
- `include/` or `rocky/` — public headers (project headers included by sources).
- `tests/` — unit and integration tests:
  - `tests/*.c` — Unity unit tests for low-level C modules (lexer, parser, arena, etc.).
  - `tests/lit/` — Lit integration tests for the compiler pipeline (AST dumps, IR checks).
- `external/` — third-party test helpers (e.g., Unity).

## Testing

Rocky uses a two-tier testing strategy:

- **Unit tests** with Unity (C unit test framework). Unit tests live in `tests/` and are discovered automatically by the CMake test integration.
- **Integration tests** with LLVM `lit` + `FileCheck` under `tests/lit/`. These validate compiler output (AST, IR, etc.).

**Common test commands:**

- Run all tests: `pixi run test`
- Run unit tests only (filter by label/path): `pixi run test lexer`
- Run Lit tests only: `pixi run lit`
- Run a specific lit test: `pixi run lit ir/add`

CMake builds replace placeholders like `%rocky` and `%parser` with the actual binary paths in test runs.

## Contributing

- Currently, only selected people from VIT / VIIT are allowed to contribute to the project.

## License

See the `LICENSE` file in the repository root for licensing information.

---

If anything in the environment fails (missing `pixi` or `git`, or a build error):

- Run `pixi --help` and `git --help` to confirm both tools are installed and on your PATH.
- Check that you executed `pixi install` and `pixi run configure` before building.
- For platform-specific issues (Windows MSVC provisioning, or Linux toolchain paths), include exact error output when opening an issue so the problem can be reproduced.
