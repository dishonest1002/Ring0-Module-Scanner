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

<img width="941" height="302" alt="Снимок экрана 2026-03-25 194951" src="https://github.com/user-attachments/assets/aebc3e2b-2515-4b54-8951-b4f35b36cab6" />
<img width="731" height="392" alt="Снимок экрана 2026-03-25 194958" src="https://github.com/user-attachments/assets/40ec4b11-cec5-4970-8731-949831a4b0f4" />
<img width="1483" height="629" alt="Снимок экрана 2026-03-25 195009" src="https://github.com/user-attachments/assets/abdb3692-6a85-40c0-aaea-44b7c32073e7" />
<img width="1083" height="578" alt="Снимок экрана 2026-03-25 195018" src="https://github.com/user-attachments/assets/c7bc1d0a-91d1-483c-b693-752dadff9a8b" />

PAGE_FAULT_IN_NONPAGED_AREA (50)

Issue: Occurred during heuristic memory scanning of unallocated regions.

Resolution: Implemented rigorous MmIsAddressValid checks and SEH (__try/__except) blocks.

<img width="881" height="511" alt="Снимок экрана 2026-03-25 194557" src="https://github.com/user-attachments/assets/58d1d859-9205-4d00-b0db-800524c5e750" />
<img width="1434" height="385" alt="Снимок экрана 2026-03-25 194606" src="https://github.com/user-attachments/assets/c769618f-6302-44a2-a39c-98225cf77d15" />
<img width="1510" height="564" alt="Снимок экрана 2026-03-25 194627" src="https://github.com/user-attachments/assets/c9dcee9f-3a82-495e-93bb-fd5b6aa76057" />

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
