#  Ring0ModuleScanner

A high-performance Windows kernel-mode driver and user-mode client for scanning loaded kernel modules, detecting anti-cheat software, identifying hidden drivers (DKOM), and verifying software licenses.

>  **For educational and research purposes only.**
> This project requires a test-signed environment (kernel debugging enabled or test signing on).

---

##  Media & Demo

### Main Interface & Successful Detection
<img width="841" height="381" alt="Снимок экрана 2026-03-25 193058" src="https://github.com/user-attachments/assets/8a282d78-4944-40f0-a24e-7bfb8078af8d" />

### Kernel-Mode Logging (DebugView)
<img width="248" height="523" alt="Снимок экрана 2026-03-25 181713" src="https://github.com/user-attachments/assets/98369d7b-1f8a-41b1-94d0-d5e83b918b17" />

---

##  Features

-  **Module enumeration** — lists all loaded kernel drivers with signature metadata.
-  **Anti-cheat detection** — identifies known anti-cheat drivers (EAC, BattlEye, Vanguard, etc.).
-  **Suspicious module detection** — flags unsigned kernel modules.
-  **Hidden module detection** — finds drivers hidden via DKOM (Direct Kernel Object Manipulation).
-  **Self-hiding (DKOM)** — unlinks the driver from `PsLoadedModuleList` at runtime.
-  **License verification** — HWID-based license check via IOCTL.

---

##  Architecture

```text
┌─────────────────────┐      IOCTL      ┌──────────────────────┐
│     client.exe      │ ───────────────►│  Ring0ModuleScanner  │
│    (user-mode)      │ ◄───────────────│   .sys (kernel-mode) │
└─────────────────────┘                 └──────────────────────┘
                                                  │
                                          PsLoadedModuleList
                                          PE header scanning
 Stability & Debugging (The WinDbg Journey)
Kernel development is 20% coding and 80% debugging BSODs. This project features documented resolution of critical kernel exceptions to ensure system reliability in Test Mode.

Analyzed Exceptions:
KMODE_EXCEPTION_NOT_HANDLED (1e)

Issue: Encountered during initial implementation of the system thread contexts.

Resolution: Fixed via proper stack alignment and exception handling.
<img width="1483" height="629" alt="Снимок экрана 2026-03-25 195009" src="https://github.com/user-attachments/assets/f11398c7-657c-4aa3-8b0a-5d420042e38a" />
<img width="731" height="392" alt="Снимок экрана 2026-03-25 194958" src="https://github.com/user-attachments/assets/2eeee727-0e54-43a9-a128-a8477d6372d2" />
<img width="941" height="302" alt="Снимок экрана 2026-03-25 194951" src="https://github.com/user-attachments/assets/36107781-c7c0-4fb3-a528-dceabbf77253" />
<img width="1083" height="578" alt="Снимок экрана 2026-03-25 195018" src="https://github.com/user-attachments/assets/567a5ee8-a8b1-4860-9418-3bf1d3dcc196" />

PAGE_FAULT_IN_NONPAGED_AREA (50)

Issue: Occurred during heuristic memory scanning of unallocated regions.

Resolution: Implemented rigorous MmIsAddressValid checks and SEH (__try/__except) blocks.
<img width="1510" height="564" alt="Снимок экрана 2026-03-25 194627" src="https://github.com/user-attachments/assets/da9cc9e3-b3e9-4d13-91b2-83abf325153b" />
<img width="1434" height="385" alt="Снимок экрана 2026-03-25 194606" src="https://github.com/user-attachments/assets/e178ce7b-7c3a-4895-8f6f-1c9a2443d3bd" />
<img width="881" height="511" alt="Снимок экрана 2026-03-25 194557" src="https://github.com/user-attachments/assets/88430896-22c4-4e33-bebc-76a53d019af2" />


 Build & Setup
Requirements
Windows 10/11 x64

Visual Studio 2022

Windows Driver Kit (WDK)

1. Enable Test Mode
To load the driver, you must enable test signing:

DOS
bcdedit /set testsigning on
Reboot is required after running this command.

2. Loading the Driver
DOS
sc create Ring0Scanner type= kernel binPath= "C:\path\to\Ring0ModuleScanner.sys"
sc start Ring0Scanner
 Author
**dishonest** — Systems programmer focusing on Windows Kernel, Security Research & Reverse Engineering.  
Currently pursuing Software Engineering (121/123).  
GitHub: [github.com/dishonest1002](https://github.com/dishonest1002)
