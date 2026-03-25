#ifndef RING0_IOCTL_H
#define RING0_IOCTL_H

// Device paths:
// DEVICE_NAME   — kernel-side name, passed to IoCreateDevice
// SYMBOLIC_NAME — DOS-side link, passed to IoCreateSymbolicLink
// DEVICE_PATH   — user-mode path, passed to CreateFileW
#define DEVICE_NAME     L"\\Device\\Ring0ModuleScanner"
#define SYMBOLIC_NAME   L"\\DosDevices\\Ring0ModuleScanner"
#define DEVICE_PATH     L"\\\\.\\Ring0ModuleScanner"

// IOCTL control codes — METHOD_BUFFERED, FILE_ANY_ACCESS
#define IOCTL_GET_MODULES    CTL_CODE(FILE_DEVICE_UNKNOWN, 0x800, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_GET_ANTICHEATS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x801, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_GET_SUSPICIOUS CTL_CODE(FILE_DEVICE_UNKNOWN, 0x802, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_VERIFY_LICENSE CTL_CODE(FILE_DEVICE_UNKNOWN, 0x803, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_HIDE_SELF      CTL_CODE(FILE_DEVICE_UNKNOWN, 0x804, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_FIND_HIDDEN    CTL_CODE(FILE_DEVICE_UNKNOWN, 0x805, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define MAX_MODULES  256
#define MAX_NAME_LEN 64
#define MAX_HIDDEN   64

// Per-module metadata returned by IOCTL_GET_MODULES.
// SignatureLevel/Type mirror the KLDR_DATA_TABLE_ENTRY bitfield values.
typedef struct _MODULE_INFO {
    WCHAR   Name[MAX_NAME_LEN]; // BaseDllName from KLDR_DATA_TABLE_ENTRY
    PVOID   Base;               // DllBase — virtual address of the module
    ULONG   Size;               // SizeOfImage in bytes
    ULONG   Flags;              // raw KLDR Flags field
    BOOLEAN IsAntiCheat;        // matched against known anti-cheat names
    UCHAR   SignatureLevel;     // SE_SIGNING_LEVEL_* constant
    UCHAR   SignatureType;      // 0=none 1=embedded 2=catalog
    BOOLEAN IsSigned;           // SignatureLevel >= AUTHENTICODE
    BOOLEAN IsMicrosoft;        // SignatureLevel >= MICROSOFT
    BOOLEAN IsSuspicious;       // SignatureLevel == UNSIGNED
} MODULE_INFO;

// Output buffer for IOCTL_GET_MODULES / IOCTL_GET_ANTICHEATS / IOCTL_GET_SUSPICIOUS
typedef struct _SCAN_RESULT {
    ULONG       ModuleCount;
    ULONG       AntiCheatCount;
    ULONG       SuspiciousCount;
    MODULE_INFO Modules[MAX_MODULES];
} SCAN_RESULT;

// Input/output for IOCTL_VERIFY_LICENSE
typedef struct _LICENSE_REQUEST {
    CHAR Hwid[64];
} LICENSE_REQUEST;

typedef struct _LICENSE_RESPONSE {
    BOOLEAN Valid;
    CHAR    Message[128];
} LICENSE_RESPONSE;

// Output buffer for IOCTL_FIND_HIDDEN.
// A module is considered hidden if a valid PE exists in kernel memory
// but has no corresponding entry in PsLoadedModuleList (DKOM technique).
typedef struct _HIDDEN_MODULE {
    PVOID Base;
    ULONG Size;
    WCHAR Name[MAX_NAME_LEN]; // from Export Directory; zeroed if unavailable
} HIDDEN_MODULE;

typedef struct _HIDDEN_RESULT {
    ULONG         Count;
    HIDDEN_MODULE Modules[MAX_HIDDEN];
} HIDDEN_RESULT;

#endif // RING0_IOCTL_H