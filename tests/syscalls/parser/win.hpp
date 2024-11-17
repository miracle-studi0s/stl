#ifndef WIN_H_
#define WIN_H_

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

typedef long NTSTATUS;

typedef enum _MEMORY_INFORMATION_CLASS {
    MemoryBasicInformation
} MEMORY_INFORMATION_CLASS, * PMEMORY_INFORMATION_CLASS;

namespace win {
	struct _UNICODE_STRING {
		USHORT Length;         // 0x0
		USHORT MaximumLength;  // 0x2
		WCHAR* Buffer;         // 0x4
	};

    struct _STRING64
    {
        USHORT Length;                                                          //0x0
        USHORT MaximumLength;                                                   //0x2
        ULONGLONG Buffer;                                                       //0x8
    };

	struct _LDR_DATA_TABLE_ENTRY {
		struct _LIST_ENTRY InLoadOrderLinks;            // 0x0
		struct _LIST_ENTRY InMemoryOrderLinks;          // 0x8
		struct _LIST_ENTRY InInitializationOrderLinks;  // 0x10
		VOID* DllBase;                                  // 0x18
		VOID* EntryPoint;                               // 0x1c
		ULONG SizeOfImage;                              // 0x20
		_UNICODE_STRING FullDllName;                    // 0x24
		_UNICODE_STRING BaseDllName;                    // 0x2c
	};
	struct _PEB_LDR_DATA {
		ULONG Length;                                        // 0x0
		UCHAR Initialized;                                   // 0x4
		VOID* SsHandle;                                      // 0x8
		struct _LIST_ENTRY InLoadOrderModuleList;            // 0xc
		struct _LIST_ENTRY InMemoryOrderModuleList;          // 0x14
		struct _LIST_ENTRY InInitializationOrderModuleList;  // 0x1c
		VOID* EntryInProgress;                               // 0x24
		UCHAR ShutdownInProgress;                            // 0x28
		VOID* ShutdownThreadId;                              // 0x2c
	};

	struct _CLIENT_ID32 {
		ULONG UniqueProcess;  // 0x0
		ULONG UniqueThread;   // 0x4
	};

	typedef struct _RTL_USER_PROCESS_PARAMETERS {
		BYTE           Reserved1[16];
		PVOID          Reserved2[10];
		_UNICODE_STRING ImagePathName;
		_UNICODE_STRING CommandLine;
	} RTL_USER_PROCESS_PARAMETERS, * PRTL_USER_PROCESS_PARAMETERS;

	typedef VOID(WINAPI* PPS_POST_PROCESS_INIT_ROUTINE)(VOID);

    struct _PEB64
    {
        UCHAR InheritedAddressSpace;                                            //0x0
        UCHAR ReadImageFileExecOptions;                                         //0x1
        UCHAR BeingDebugged;                                                    //0x2
        union
        {
            UCHAR BitField;                                                     //0x3
            struct
            {
                UCHAR ImageUsesLargePages : 1;                                    //0x3
                UCHAR IsProtectedProcess : 1;                                     //0x3
                UCHAR IsImageDynamicallyRelocated : 1;                            //0x3
                UCHAR SkipPatchingUser32Forwarders : 1;                           //0x3
                UCHAR IsPackagedProcess : 1;                                      //0x3
                UCHAR IsAppContainer : 1;                                         //0x3
                UCHAR IsProtectedProcessLight : 1;                                //0x3
                UCHAR IsLongPathAwareProcess : 1;                                 //0x3
            };
        };
        UCHAR Padding0[4];                                                      //0x4
        VOID* Mutant;                                                           //0x8
        VOID* ImageBaseAddress;                                                 //0x10
        struct _PEB_LDR_DATA* Ldr;                                              //0x18
        struct _RTL_USER_PROCESS_PARAMETERS* ProcessParameters;                 //0x20
        VOID* SubSystemData;                                                    //0x28
        VOID* ProcessHeap;                                                      //0x30
        struct _RTL_CRITICAL_SECTION* FastPebLock;                              //0x38
        union _SLIST_HEADER* volatile AtlThunkSListPtr;                         //0x40
        VOID* IFEOKey;                                                          //0x48
        union
        {
            ULONG CrossProcessFlags;                                            //0x50
            struct
            {
                ULONG ProcessInJob : 1;                                           //0x50
                ULONG ProcessInitializing : 1;                                    //0x50
                ULONG ProcessUsingVEH : 1;                                        //0x50
                ULONG ProcessUsingVCH : 1;                                        //0x50
                ULONG ProcessUsingFTH : 1;                                        //0x50
                ULONG ProcessPreviouslyThrottled : 1;                             //0x50
                ULONG ProcessCurrentlyThrottled : 1;                              //0x50
                ULONG ProcessImagesHotPatched : 1;                                //0x50
                ULONG ReservedBits0 : 24;                                         //0x50
            };
        };
        UCHAR Padding1[4];                                                      //0x54
        union
        {
            VOID* KernelCallbackTable;                                          //0x58
            VOID* UserSharedInfoPtr;                                            //0x58
        };
        ULONG SystemReserved;                                                   //0x60
        ULONG AtlThunkSListPtr32;                                               //0x64
        VOID* ApiSetMap;                                                        //0x68
        ULONG TlsExpansionCounter;                                              //0x70
        UCHAR Padding2[4];                                                      //0x74
        struct _RTL_BITMAP* TlsBitmap;                                          //0x78
        ULONG TlsBitmapBits[2];                                                 //0x80
        VOID* ReadOnlySharedMemoryBase;                                         //0x88
        VOID* SharedData;                                                       //0x90
        VOID** ReadOnlyStaticServerData;                                        //0x98
        VOID* AnsiCodePageData;                                                 //0xa0
        VOID* OemCodePageData;                                                  //0xa8
        VOID* UnicodeCaseTableData;                                             //0xb0
        ULONG NumberOfProcessors;                                               //0xb8
        ULONG NtGlobalFlag;                                                     //0xbc
        union _LARGE_INTEGER CriticalSectionTimeout;                            //0xc0
        ULONGLONG HeapSegmentReserve;                                           //0xc8
        ULONGLONG HeapSegmentCommit;                                            //0xd0
        ULONGLONG HeapDeCommitTotalFreeThreshold;                               //0xd8
        ULONGLONG HeapDeCommitFreeBlockThreshold;                               //0xe0
        ULONG NumberOfHeaps;                                                    //0xe8
        ULONG MaximumNumberOfHeaps;                                             //0xec
        VOID** ProcessHeaps;                                                    //0xf0
        VOID* GdiSharedHandleTable;                                             //0xf8
        VOID* ProcessStarterHelper;                                             //0x100
        ULONG GdiDCAttributeList;                                               //0x108
        UCHAR Padding3[4];                                                      //0x10c
        struct _RTL_CRITICAL_SECTION* LoaderLock;                               //0x110
        ULONG OSMajorVersion;                                                   //0x118
        ULONG OSMinorVersion;                                                   //0x11c
        USHORT OSBuildNumber;                                                   //0x120
        USHORT OSCSDVersion;                                                    //0x122
        ULONG OSPlatformId;                                                     //0x124
        ULONG ImageSubsystem;                                                   //0x128
        ULONG ImageSubsystemMajorVersion;                                       //0x12c
        ULONG ImageSubsystemMinorVersion;                                       //0x130
        UCHAR Padding4[4];                                                      //0x134
        ULONGLONG ActiveProcessAffinityMask;                                    //0x138
        ULONG GdiHandleBuffer[60];                                              //0x140
        VOID(*PostProcessInitRoutine)();                                       //0x230
        struct _RTL_BITMAP* TlsExpansionBitmap;                                 //0x238
        ULONG TlsExpansionBitmapBits[32];                                       //0x240
        ULONG SessionId;                                                        //0x2c0
        UCHAR Padding5[4];                                                      //0x2c4
        union _ULARGE_INTEGER AppCompatFlags;                                   //0x2c8
        union _ULARGE_INTEGER AppCompatFlagsUser;                               //0x2d0
        VOID* pShimData;                                                        //0x2d8
        VOID* AppCompatInfo;                                                    //0x2e0
        struct _UNICODE_STRING CSDVersion;                                      //0x2e8
        struct _ACTIVATION_CONTEXT_DATA* ActivationContextData;                 //0x2f8
        struct _ASSEMBLY_STORAGE_MAP* ProcessAssemblyStorageMap;                //0x300
        struct _ACTIVATION_CONTEXT_DATA* SystemDefaultActivationContextData;    //0x308
        struct _ASSEMBLY_STORAGE_MAP* SystemAssemblyStorageMap;                 //0x310
        ULONGLONG MinimumStackCommit;                                           //0x318
        VOID* SparePointers[2];                                                 //0x320
        VOID* PatchLoaderData;                                                  //0x330
        struct _CHPEV2_PROCESS_INFO* ChpeV2ProcessInfo;                         //0x338
        ULONG AppModelFeatureState;                                             //0x340
        ULONG SpareUlongs[2];                                                   //0x344
        USHORT ActiveCodePage;                                                  //0x34c
        USHORT OemCodePage;                                                     //0x34e
        USHORT UseCaseMapping;                                                  //0x350
        USHORT UnusedNlsField;                                                  //0x352
        VOID* WerRegistrationData;                                              //0x358
        VOID* WerShipAssertPtr;                                                 //0x360
        VOID* EcCodeBitMap;                                                     //0x368
        VOID* pImageHeaderHash;                                                 //0x370
        union
        {
            ULONG TracingFlags;                                                 //0x378
            struct
            {
                ULONG HeapTracingEnabled : 1;                                     //0x378
                ULONG CritSecTracingEnabled : 1;                                  //0x378
                ULONG LibLoaderTracingEnabled : 1;                                //0x378
                ULONG SpareTracingBits : 29;                                      //0x378
            };
        };
        UCHAR Padding6[4];                                                      //0x37c
        ULONGLONG CsrServerReadOnlySharedMemoryBase;                            //0x380
        ULONGLONG TppWorkerpListLock;                                           //0x388
        struct _LIST_ENTRY TppWorkerpList;                                      //0x390
        VOID* WaitOnAddressHashTable[128];                                      //0x3a0
        VOID* TelemetryCoverageHeader;                                          //0x7a0
        ULONG CloudFileFlags;                                                   //0x7a8
        ULONG CloudFileDiagFlags;                                               //0x7ac
        CHAR PlaceholderCompatibilityMode;                                      //0x7b0
        CHAR PlaceholderCompatibilityModeReserved[7];                           //0x7b1
        struct _LEAP_SECOND_DATA* LeapSecondData;                               //0x7b8
        union
        {
            ULONG LeapSecondFlags;                                              //0x7c0
            struct
            {
                ULONG SixtySecondEnabled : 1;                                     //0x7c0
                ULONG Reserved : 31;                                              //0x7c0
            };
        };
        ULONG NtGlobalFlag2;                                                    //0x7c4
        ULONGLONG ExtendedFeatureDisableMask;                                   //0x7c8
    };

	struct _TEB64 {
		ULONG64 Reserved1[12];
		ULONG64 ProcessEnvironmentBlock;
		ULONG64 Reserved2[399];
		BYTE Reserved3[1952];
		ULONG64 TlsSlots[64];
		BYTE Reserved4[8];
		ULONG64 Reserved5[26];
		ULONG64 ReservedForOle; // Windows 2000 only
		ULONG64 Reserved6[4];
		ULONG64 TlsExpansionSlots;
	};
}

#endif  // WIN_H_