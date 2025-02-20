# Processes
A process might seem a lot like a program, but they are two different things.

The program contains the instructions that you want your machine to execute and the process contains the environment that it needs to be processing those instructions. It maintains and represents the execution of a program.

When you actually run the program or .exe file, it becomes a `process` (or multiple). At this point you initialize an `instance` of the executable program that is being ran, this is the process.

A process has `components` or `resources` that it compromises of or interact with. The [Microsoft docs](https://learn.microsoft.com/en-us/windows/win32/procthread/about-processes-and-threads) give brief break-down of these components.

Here's a few examples of default applications that start processes:
- MsMpEng (Microsoft Defender)
- wininit (keyboard and mouse)
- lsass (credential storage)

Applications running on your operating system can contain `one or more processes`.

<details>
<summary> Kernel structure </summary>

```C
//0x840 bytes (sizeof)
struct _EPROCESS
{
    struct _KPROCESS Pcb;                                                   //0x0
    struct _EX_PUSH_LOCK ProcessLock;                                       //0x1c8
    VOID* UniqueProcessId;                                                  //0x1d0
    struct _LIST_ENTRY ActiveProcessLinks;                                  //0x1d8
    struct _EX_RUNDOWN_REF RundownProtect;                                  //0x1e8
    union
    {
        ULONG Flags2;                                                       //0x1f0
        struct
        {
            ULONG JobNotReallyActive:1;                                     //0x1f0
            ULONG AccountingFolded:1;                                       //0x1f0
            ULONG NewProcessReported:1;                                     //0x1f0
            ULONG ExitProcessReported:1;                                    //0x1f0
            ULONG ReportCommitChanges:1;                                    //0x1f0
            ULONG LastReportMemory:1;                                       //0x1f0
            ULONG ForceWakeCharge:1;                                        //0x1f0
            ULONG CrossSessionCreate:1;                                     //0x1f0
            ULONG NeedsHandleRundown:1;                                     //0x1f0
            ULONG RefTraceEnabled:1;                                        //0x1f0
            ULONG PicoCreated:1;                                            //0x1f0
            ULONG EmptyJobEvaluated:1;                                      //0x1f0
            ULONG DefaultPagePriority:3;                                    //0x1f0
            ULONG PrimaryTokenFrozen:1;                                     //0x1f0
            ULONG ProcessVerifierTarget:1;                                  //0x1f0
            ULONG RestrictSetThreadContext:1;                               //0x1f0
            ULONG AffinityPermanent:1;                                      //0x1f0
            ULONG AffinityUpdateEnable:1;                                   //0x1f0
            ULONG PropagateNode:1;                                          //0x1f0
            ULONG ExplicitAffinity:1;                                       //0x1f0
            ULONG Flags2Available1:2;                                       //0x1f0
            ULONG EnableReadVmLogging:1;                                    //0x1f0
            ULONG EnableWriteVmLogging:1;                                   //0x1f0
            ULONG FatalAccessTerminationRequested:1;                        //0x1f0
            ULONG DisableSystemAllowedCpuSet:1;                             //0x1f0
            ULONG Flags2Available2:3;                                       //0x1f0
            ULONG InPrivate:1;                                              //0x1f0
        };
    };
    union
    {
        ULONG Flags;                                                        //0x1f4
        struct
        {
            ULONG CreateReported:1;                                         //0x1f4
            ULONG NoDebugInherit:1;                                         //0x1f4
            ULONG ProcessExiting:1;                                         //0x1f4
            ULONG ProcessDelete:1;                                          //0x1f4
            ULONG ManageExecutableMemoryWrites:1;                           //0x1f4
            ULONG VmDeleted:1;                                              //0x1f4
            ULONG OutswapEnabled:1;                                         //0x1f4
            ULONG Outswapped:1;                                             //0x1f4
            ULONG FailFastOnCommitFail:1;                                   //0x1f4
            ULONG Wow64VaSpace4Gb:1;                                        //0x1f4
            ULONG AddressSpaceInitialized:2;                                //0x1f4
            ULONG SetTimerResolution:1;                                     //0x1f4
            ULONG BreakOnTermination:1;                                     //0x1f4
            ULONG DeprioritizeViews:1;                                      //0x1f4
            ULONG WriteWatch:1;                                             //0x1f4
            ULONG ProcessInSession:1;                                       //0x1f4
            ULONG OverrideAddressSpace:1;                                   //0x1f4
            ULONG HasAddressSpace:1;                                        //0x1f4
            ULONG LaunchPrefetched:1;                                       //0x1f4
            ULONG Reserved:1;                                               //0x1f4
            ULONG VmTopDown:1;                                              //0x1f4
            ULONG ImageNotifyDone:1;                                        //0x1f4
            ULONG PdeUpdateNeeded:1;                                        //0x1f4
            ULONG VdmAllowed:1;                                             //0x1f4
            ULONG ProcessRundown:1;                                         //0x1f4
            ULONG ProcessInserted:1;                                        //0x1f4
            ULONG DefaultIoPriority:3;                                      //0x1f4
            ULONG ProcessSelfDelete:1;                                      //0x1f4
            ULONG SetTimerResolutionLink:1;                                 //0x1f4
        };
    };
    union _LARGE_INTEGER CreateTime;                                        //0x1f8
    ULONGLONG ProcessQuotaUsage[2];                                         //0x200
    ULONGLONG ProcessQuotaPeak[2];                                          //0x210
    ULONGLONG PeakVirtualSize;                                              //0x220
    ULONGLONG VirtualSize;                                                  //0x228
    struct _LIST_ENTRY SessionProcessLinks;                                 //0x230
    union
    {
        VOID* ExceptionPortData;                                            //0x240
        ULONGLONG ExceptionPortValue;                                       //0x240
        ULONGLONG ExceptionPortState:3;                                     //0x240
    };
    struct _EX_FAST_REF Token;                                              //0x248
    ULONGLONG MmReserved;                                                   //0x250
    struct _EX_PUSH_LOCK AddressCreationLock;                               //0x258
    struct _EX_PUSH_LOCK PageTableCommitmentLock;                           //0x260
    struct _ETHREAD* RotateInProgress;                                      //0x268
    struct _ETHREAD* ForkInProgress;                                        //0x270
    struct _EJOB* volatile CommitChargeJob;                                 //0x278
    struct _RTL_AVL_TREE CloneRoot;                                         //0x280
    volatile ULONGLONG NumberOfPrivatePages;                                //0x288
    volatile ULONGLONG NumberOfLockedPages;                                 //0x290
    VOID* Win32Process;                                                     //0x298
    struct _EJOB* volatile Job;                                             //0x2a0
    VOID* SectionObject;                                                    //0x2a8
    VOID* SectionBaseAddress;                                               //0x2b0
    ULONG Cookie;                                                           //0x2b8
    struct _PAGEFAULT_HISTORY* WorkingSetWatch;                             //0x2c0
    VOID* Win32WindowStation;                                               //0x2c8
    VOID* InheritedFromUniqueProcessId;                                     //0x2d0
    volatile ULONGLONG OwnerProcessId;                                      //0x2d8
    struct _PEB* Peb;                                                       //0x2e0
    struct _PSP_SESSION_SPACE* Session;                                     //0x2e8
    VOID* Spare1;                                                           //0x2f0
    struct _EPROCESS_QUOTA_BLOCK* QuotaBlock;                               //0x2f8
    struct _HANDLE_TABLE* ObjectTable;                                      //0x300
    VOID* DebugPort;                                                        //0x308
    struct _EWOW64PROCESS* WoW64Process;                                    //0x310
    struct _EX_FAST_REF DeviceMap;                                          //0x318
    VOID* EtwDataSource;                                                    //0x320
    ULONGLONG PageDirectoryPte;                                             //0x328
    struct _FILE_OBJECT* ImageFilePointer;                                  //0x330
    UCHAR ImageFileName[15];                                                //0x338
    UCHAR PriorityClass;                                                    //0x347
    VOID* SecurityPort;                                                     //0x348
    struct _SE_AUDIT_PROCESS_CREATION_INFO SeAuditProcessCreationInfo;      //0x350
    struct _LIST_ENTRY JobLinks;                                            //0x358
    VOID* HighestUserAddress;                                               //0x368
    struct _LIST_ENTRY ThreadListHead;                                      //0x370
    volatile ULONG ActiveThreads;                                           //0x380
    ULONG ImagePathHash;                                                    //0x384
    ULONG DefaultHardErrorProcessing;                                       //0x388
    LONG LastThreadExitStatus;                                              //0x38c
    struct _EX_FAST_REF PrefetchTrace;                                      //0x390
    VOID* LockedPagesList;                                                  //0x398
    union _LARGE_INTEGER ReadOperationCount;                                //0x3a0
    union _LARGE_INTEGER WriteOperationCount;                               //0x3a8
    union _LARGE_INTEGER OtherOperationCount;                               //0x3b0
    union _LARGE_INTEGER ReadTransferCount;                                 //0x3b8
    union _LARGE_INTEGER WriteTransferCount;                                //0x3c0
    union _LARGE_INTEGER OtherTransferCount;                                //0x3c8
    ULONGLONG CommitChargeLimit;                                            //0x3d0
    volatile ULONGLONG CommitCharge;                                        //0x3d8
    volatile ULONGLONG CommitChargePeak;                                    //0x3e0
    struct _MMSUPPORT_FULL Vm;                                              //0x400
    struct _LIST_ENTRY MmProcessLinks;                                      //0x540
    volatile ULONG ModifiedPageCount;                                       //0x550
    LONG ExitStatus;                                                        //0x554
    struct _RTL_AVL_TREE VadRoot;                                           //0x558
    VOID* VadHint;                                                          //0x560
    ULONGLONG VadCount;                                                     //0x568
    volatile ULONGLONG VadPhysicalPages;                                    //0x570
    ULONGLONG VadPhysicalPagesLimit;                                        //0x578
    struct _ALPC_PROCESS_CONTEXT AlpcContext;                               //0x580
    struct _LIST_ENTRY TimerResolutionLink;                                 //0x5a0
    struct _PO_DIAG_STACK_RECORD* TimerResolutionStackRecord;               //0x5b0
    ULONG RequestedTimerResolution;                                         //0x5b8
    ULONG SmallestTimerResolution;                                          //0x5bc
    union _LARGE_INTEGER ExitTime;                                          //0x5c0
    struct _INVERTED_FUNCTION_TABLE_KERNEL_MODE* InvertedFunctionTable;     //0x5c8
    struct _EX_PUSH_LOCK InvertedFunctionTableLock;                         //0x5d0
    ULONG ActiveThreadsHighWatermark;                                       //0x5d8
    ULONG LargePrivateVadCount;                                             //0x5dc
    struct _EX_PUSH_LOCK ThreadListLock;                                    //0x5e0
    VOID* WnfContext;                                                       //0x5e8
    struct _EJOB* ServerSilo;                                               //0x5f0
    UCHAR SignatureLevel;                                                   //0x5f8
    UCHAR SectionSignatureLevel;                                            //0x5f9
    struct _PS_PROTECTION Protection;                                       //0x5fa
    UCHAR HangCount:3;                                                      //0x5fb
    UCHAR GhostCount:3;                                                     //0x5fb
    UCHAR PrefilterException:1;                                             //0x5fb
    union
    {
        ULONG Flags3;                                                       //0x5fc
        struct
        {
            ULONG Minimal:1;                                                //0x5fc
            ULONG ReplacingPageRoot:1;                                      //0x5fc
            ULONG Crashed:1;                                                //0x5fc
            ULONG JobVadsAreTracked:1;                                      //0x5fc
            ULONG VadTrackingDisabled:1;                                    //0x5fc
            ULONG AuxiliaryProcess:1;                                       //0x5fc
            ULONG SubsystemProcess:1;                                       //0x5fc
            ULONG IndirectCpuSets:1;                                        //0x5fc
            ULONG RelinquishedCommit:1;                                     //0x5fc
            ULONG HighGraphicsPriority:1;                                   //0x5fc
            ULONG CommitFailLogged:1;                                       //0x5fc
            ULONG ReserveFailLogged:1;                                      //0x5fc
            ULONG SystemProcess:1;                                          //0x5fc
            ULONG AllImagesAtBasePristineBase:1;                            //0x5fc
            ULONG AddressPolicyFrozen:1;                                    //0x5fc
            ULONG ProcessFirstResume:1;                                     //0x5fc
            ULONG ForegroundExternal:1;                                     //0x5fc
            ULONG ForegroundSystem:1;                                       //0x5fc
            ULONG HighMemoryPriority:1;                                     //0x5fc
            ULONG EnableProcessSuspendResumeLogging:1;                      //0x5fc
            ULONG EnableThreadSuspendResumeLogging:1;                       //0x5fc
            ULONG SecurityDomainChanged:1;                                  //0x5fc
            ULONG SecurityFreezeComplete:1;                                 //0x5fc
            ULONG VmProcessorHost:1;                                        //0x5fc
            ULONG VmProcessorHostTransition:1;                              //0x5fc
            ULONG AltSyscall:1;                                             //0x5fc
            ULONG TimerResolutionIgnore:1;                                  //0x5fc
            ULONG DisallowUserTerminate:1;                                  //0x5fc
            ULONG EnableProcessRemoteExecProtectVmLogging:1;                //0x5fc
            ULONG EnableProcessLocalExecProtectVmLogging:1;                 //0x5fc
            ULONG MemoryCompressionProcess:1;                               //0x5fc
            ULONG EnableProcessImpersonationLogging:1;                      //0x5fc
        };
    };
    LONG DeviceAsid;                                                        //0x600
    VOID* SvmData;                                                          //0x608
    struct _EX_PUSH_LOCK SvmProcessLock;                                    //0x610
    ULONGLONG SvmLock;                                                      //0x618
    struct _LIST_ENTRY SvmProcessDeviceListHead;                            //0x620
    ULONGLONG LastFreezeInterruptTime;                                      //0x630
    struct _PROCESS_DISK_COUNTERS* DiskCounters;                            //0x638
    VOID* PicoContext;                                                      //0x640
    VOID* EnclaveTable;                                                     //0x648
    ULONGLONG EnclaveNumber;                                                //0x650
    struct _EX_PUSH_LOCK EnclaveLock;                                       //0x658
    ULONG HighPriorityFaultsAllowed;                                        //0x660
    struct _PO_PROCESS_ENERGY_CONTEXT* EnergyContext;                       //0x668
    VOID* VmContext;                                                        //0x670
    ULONGLONG SequenceNumber;                                               //0x678
    ULONGLONG CreateInterruptTime;                                          //0x680
    ULONGLONG CreateUnbiasedInterruptTime;                                  //0x688
    ULONGLONG TotalUnbiasedFrozenTime;                                      //0x690
    ULONGLONG LastAppStateUpdateTime;                                       //0x698
    ULONGLONG LastAppStateUptime:61;                                        //0x6a0
    ULONGLONG LastAppState:3;                                               //0x6a0
    volatile ULONGLONG SharedCommitCharge;                                  //0x6a8
    struct _EX_PUSH_LOCK SharedCommitLock;                                  //0x6b0
    struct _LIST_ENTRY SharedCommitLinks;                                   //0x6b8
    union
    {
        struct
        {
            ULONGLONG AllowedCpuSets;                                       //0x6c8
            ULONGLONG DefaultCpuSets;                                       //0x6d0
        };
        struct
        {
            ULONGLONG* AllowedCpuSetsIndirect;                              //0x6c8
            ULONGLONG* DefaultCpuSetsIndirect;                              //0x6d0
        };
    };
    VOID* DiskIoAttribution;                                                //0x6d8
    VOID* DxgProcess;                                                       //0x6e0
    ULONG Win32KFilterSet;                                                  //0x6e8
    USHORT Machine;                                                         //0x6ec
    UCHAR MmSlabIdentity;                                                   //0x6ee
    UCHAR Spare0;                                                           //0x6ef
    unionvolatile _PS_INTERLOCKED_TIMER_DELAY_VALUES ProcessTimerDelay;     //0x6f0
    volatile ULONG KTimerSets;                                              //0x6f8
    volatile ULONG KTimer2Sets;                                             //0x6fc
    volatile ULONG ThreadTimerSets;                                         //0x700
    ULONGLONG VirtualTimerListLock;                                         //0x708
    struct _LIST_ENTRY VirtualTimerListHead;                                //0x710
    union
    {
        struct _WNF_STATE_NAME WakeChannel;                                 //0x720
        struct _PS_PROCESS_WAKE_INFORMATION WakeInfo;                       //0x720
    };
    union
    {
        ULONG MitigationFlags;                                              //0x750
        struct
        {
            ULONG ControlFlowGuardEnabled:1;                                //0x750
            ULONG ControlFlowGuardExportSuppressionEnabled:1;               //0x750
            ULONG ControlFlowGuardStrict:1;                                 //0x750
            ULONG DisallowStrippedImages:1;                                 //0x750
            ULONG ForceRelocateImages:1;                                    //0x750
            ULONG HighEntropyASLREnabled:1;                                 //0x750
            ULONG StackRandomizationDisabled:1;                             //0x750
            ULONG ExtensionPointDisable:1;                                  //0x750
            ULONG DisableDynamicCode:1;                                     //0x750
            ULONG DisableDynamicCodeAllowOptOut:1;                          //0x750
            ULONG DisableDynamicCodeAllowRemoteDowngrade:1;                 //0x750
            ULONG AuditDisableDynamicCode:1;                                //0x750
            ULONG DisallowWin32kSystemCalls:1;                              //0x750
            ULONG AuditDisallowWin32kSystemCalls:1;                         //0x750
            ULONG EnableFilteredWin32kAPIs:1;                               //0x750
            ULONG AuditFilteredWin32kAPIs:1;                                //0x750
            ULONG DisableNonSystemFonts:1;                                  //0x750
            ULONG AuditNonSystemFontLoading:1;                              //0x750
            ULONG PreferSystem32Images:1;                                   //0x750
            ULONG ProhibitRemoteImageMap:1;                                 //0x750
            ULONG AuditProhibitRemoteImageMap:1;                            //0x750
            ULONG ProhibitLowILImageMap:1;                                  //0x750
            ULONG AuditProhibitLowILImageMap:1;                             //0x750
            ULONG SignatureMitigationOptIn:1;                               //0x750
            ULONG AuditBlockNonMicrosoftBinaries:1;                         //0x750
            ULONG AuditBlockNonMicrosoftBinariesAllowStore:1;               //0x750
            ULONG LoaderIntegrityContinuityEnabled:1;                       //0x750
            ULONG AuditLoaderIntegrityContinuity:1;                         //0x750
            ULONG EnableModuleTamperingProtection:1;                        //0x750
            ULONG EnableModuleTamperingProtectionNoInherit:1;               //0x750
            ULONG RestrictIndirectBranchPrediction:1;                       //0x750
            ULONG IsolateSecurityDomain:1;                                  //0x750
        } MitigationFlagsValues;                                            //0x750
    };
    union
    {
        ULONG MitigationFlags2;                                             //0x754
        struct
        {
            ULONG EnableExportAddressFilter:1;                              //0x754
            ULONG AuditExportAddressFilter:1;                               //0x754
            ULONG EnableExportAddressFilterPlus:1;                          //0x754
            ULONG AuditExportAddressFilterPlus:1;                           //0x754
            ULONG EnableRopStackPivot:1;                                    //0x754
            ULONG AuditRopStackPivot:1;                                     //0x754
            ULONG EnableRopCallerCheck:1;                                   //0x754
            ULONG AuditRopCallerCheck:1;                                    //0x754
            ULONG EnableRopSimExec:1;                                       //0x754
            ULONG AuditRopSimExec:1;                                        //0x754
            ULONG EnableImportAddressFilter:1;                              //0x754
            ULONG AuditImportAddressFilter:1;                               //0x754
            ULONG DisablePageCombine:1;                                     //0x754
            ULONG SpeculativeStoreBypassDisable:1;                          //0x754
            ULONG CetUserShadowStacks:1;                                    //0x754
            ULONG AuditCetUserShadowStacks:1;                               //0x754
            ULONG AuditCetUserShadowStacksLogged:1;                         //0x754
            ULONG UserCetSetContextIpValidation:1;                          //0x754
            ULONG AuditUserCetSetContextIpValidation:1;                     //0x754
            ULONG AuditUserCetSetContextIpValidationLogged:1;               //0x754
            ULONG CetUserShadowStacksStrictMode:1;                          //0x754
            ULONG BlockNonCetBinaries:1;                                    //0x754
            ULONG BlockNonCetBinariesNonEhcont:1;                           //0x754
            ULONG AuditBlockNonCetBinaries:1;                               //0x754
            ULONG AuditBlockNonCetBinariesLogged:1;                         //0x754
            ULONG XtendedControlFlowGuard_Deprecated:1;                     //0x754
            ULONG AuditXtendedControlFlowGuard_Deprecated:1;                //0x754
            ULONG PointerAuthUserIp:1;                                      //0x754
            ULONG AuditPointerAuthUserIp:1;                                 //0x754
            ULONG AuditPointerAuthUserIpLogged:1;                           //0x754
            ULONG CetDynamicApisOutOfProcOnly:1;                            //0x754
            ULONG UserCetSetContextIpValidationRelaxedMode:1;               //0x754
        } MitigationFlags2Values;                                           //0x754
    };
    VOID* PartitionObject;                                                  //0x758
    ULONGLONG SecurityDomain;                                               //0x760
    ULONGLONG ParentSecurityDomain;                                         //0x768
    VOID* CoverageSamplerContext;                                           //0x770
    VOID* MmHotPatchContext;                                                //0x778
    struct _RTL_AVL_TREE DynamicEHContinuationTargetsTree;                  //0x780
    struct _EX_PUSH_LOCK DynamicEHContinuationTargetsLock;                  //0x788
    struct _PS_DYNAMIC_ENFORCED_ADDRESS_RANGES DynamicEnforcedCetCompatibleRanges; //0x790
    ULONG DisabledComponentFlags;                                           //0x7a0
    volatile LONG PageCombineSequence;                                      //0x7a4
    struct _EX_PUSH_LOCK EnableOptionalXStateFeaturesLock;                  //0x7a8
    ULONG* volatile PathRedirectionHashes;                                  //0x7b0
    struct _PS_SYSCALL_PROVIDER* SyscallProvider;                           //0x7b8
    struct _LIST_ENTRY SyscallProviderProcessLinks;                         //0x7c0
    struct _PSP_SYSCALL_PROVIDER_DISPATCH_CONTEXT SyscallProviderDispatchContext; //0x7d0
    union
    {
        ULONG MitigationFlags3;                                             //0x7d8
        struct
        {
            ULONG RestrictCoreSharing:1;                                    //0x7d8
            ULONG DisallowFsctlSystemCalls:1;                               //0x7d8
            ULONG AuditDisallowFsctlSystemCalls:1;                          //0x7d8
            ULONG MitigationFlags3Spare:29;                                 //0x7d8
        } MitigationFlags3Values;                                           //0x7d8
    };
    union
    {
        ULONG Flags4;                                                       //0x7dc
        struct
        {
            ULONG ThreadWasActive:1;                                        //0x7dc
            ULONG MinimalTerminate:1;                                       //0x7dc
            ULONG ImageExpansionDisable:1;                                  //0x7dc
            ULONG SessionFirstProcess:1;                                    //0x7dc
        };
    };
    union
    {
        ULONG SyscallUsage;                                                 //0x7e0
        struct
        {
            ULONG SystemModuleInformation:1;                                //0x7e0
            ULONG SystemModuleInformationEx:1;                              //0x7e0
            ULONG SystemLocksInformation:1;                                 //0x7e0
            ULONG SystemStackTraceInformation:1;                            //0x7e0
            ULONG SystemHandleInformation:1;                                //0x7e0
            ULONG SystemExtendedHandleInformation:1;                        //0x7e0
            ULONG SystemObjectInformation:1;                                //0x7e0
            ULONG SystemBigPoolInformation:1;                               //0x7e0
            ULONG SystemExtendedProcessInformation:1;                       //0x7e0
            ULONG SystemSessionProcessInformation:1;                        //0x7e0
            ULONG SystemMemoryTopologyInformation:1;                        //0x7e0
            ULONG SystemMemoryChannelInformation:1;                         //0x7e0
            ULONG SystemUnused:1;                                           //0x7e0
            ULONG SystemPlatformBinaryInformation:1;                        //0x7e0
            ULONG SystemFirmwareTableInformation:1;                         //0x7e0
            ULONG SystemBootMetadataInformation:1;                          //0x7e0
            ULONG SystemWheaIpmiHardwareInformation:1;                      //0x7e0
            ULONG SystemSuperfetchPrefetch:1;                               //0x7e0
            ULONG SystemSuperfetchPfnQuery:1;                               //0x7e0
            ULONG SystemSuperfetchPrivSourceQuery:1;                        //0x7e0
            ULONG SystemSuperfetchMemoryListQuery:1;                        //0x7e0
            ULONG SystemSuperfetchMemoryRangesQuery:1;                      //0x7e0
            ULONG SystemSuperfetchPfnSetPriority:1;                         //0x7e0
            ULONG SystemSuperfetchMovePages:1;                              //0x7e0
            ULONG SystemSuperfetchPfnSetPageHeat:1;                         //0x7e0
            ULONG SysDbgGetTriageDump:1;                                    //0x7e0
            ULONG SysDbgGetLiveKernelDump:1;                                //0x7e0
            ULONG SyscallUsageValuesSpare:5;                                //0x7e0
        } SyscallUsageValues;                                               //0x7e0
    };
    LONG SupervisorDeviceAsid;                                              //0x7e4
    VOID* SupervisorSvmData;                                                //0x7e8
    struct _PROCESS_NETWORK_COUNTERS* NetworkCounters;                      //0x7f0
    union _PROCESS_EXECUTION Execution;                                     //0x7f8
    VOID* ThreadIndexTable;                                                 //0x800
}; 
```

</details>

## High-level components
| Component | Purpose |
|-|-|
| `Name` | Define the name of the process, typically inherited from the application. |
| `Status` | Determines how the process is running (running, suspended, etc.) |
| `Private virtual address space` | A set of virtual memory addresses available to be used by the process. |
| `Executable program` | The initial code and data of the executable that is stored into the private virtual address space. |
| `List of open handles` | A list of open handles to be used by the process's threads to interact with system resources. |
| `Security context` | This is the access token that identifies the user, security groups, privileges, attributes, claims, capabilities, UAC virtualization state, session and limited user-account state associated with the process. It also identifies the AppContainer and it's also related to sandboxing information. |
| `User name` | User that initiated the process. Can denote privilege of the process |
| `Process ID (PID)` | A unique identifier for the process. Internally this is part of an identifier named "client ID". |
| `Threads` (of execution) | A process contains at least one thread of execution. |
| `Environment variables` | Metadata used by the process to understand what OS environment it's running in. |
| `Priority class` | Tells the scheduler how often the CPU should look at the threads in this process. |
| `Minimum and maximum working set sizes (RAM)` | The amount of RAM the process can use. |
| `Process state` | The current state of the process like; Created, Terminated, Running, Waiting, Suspended, Blocked, etc. |

## Low-level components
| Component | Purpose |
|-|-|
| `Code` | Code to be executed by the process. |
| `Global Variables` | Stored variables. |
| `Process Heap` | Defines the heap where data is stored. |
| `Process Resources` | Defines further resources of the process. |
| `Process Environment Block` | Data structure to define process information. |

![Process](/Windows_Internals/Images/Process.png)

## Threads
In essence, processes aren't even executed by the CPU. The threads inside of the process are executed by the CPU, they typically represent the code.

A `thread` is an `executable unit- or entity` employed by a process and scheduled for execution based on device factors.

When we have a process with two or more threads it's called a Multi-Threaded process. At first programs were Single-Threaded but as CPU's evolved and got multiple cores this gave us a way to get a lot more done with our threads.

Threads may seem like a bare-bones and simple component, but it's `function is critical` to processes. Without this a process wouldn't be able to "run". We can simplify the definition of a thread: `controlling the execution of a process`.

- Device factors can vary based on CPU and memory specifications, priority and logical factors, and others.
- All threads within a process share the process's virtual address space and system resources, such as code, global variables, etc.

Threads can also switch between eachother to control execution (`context-switching`), commonly seen in multi-threaded applications. However, this involves the kernel scheduler and can become quite expensive. To solve this issue Windows implements two mechanisms to reduce the overhead cost for the CPU:
- `Fibers`
- `User-mode Scheduling (UMS)` 

Threads also have their unique values and architecture-specific components called the `Thread context`. The Windows `GetThreadContext` function provides access to this `architecture-specific structure (context block)`.

### Thread context
| Component | Purpose |
|-|-|
| `Context Structure` or `Volatile registers` | Holds a set of CPU registers that represent the state of the processor maintained by the kernel. |
| `Two stacks` | All data relevant and specific to the thread (exceptions, procedure calls, etc.). One to execute Kernel-mode and one for User-mode execution. |
| `Thread-Local Storage` (TLS) | A private storage area (a unique data environment) used for allocation by sub-systems, run-time libraries and DLLs. |
| `Thread ID` or `Stack Argument` | Unique value (identifier) assigned to each thread, part of the `client ID structure`. |
| `Security context` | Sometimes threads have their own security context or token. Commonly used by multi-threaded server applications that clone the security context of their served client. |
| `Priority class` | Representing the priority of the execution of the thread. |

![Threads](/Windows_Internals/Images/Threads.png)

<details>
<summary> Kernel structure </summary>

```C
//0x788 bytes (sizeof)
struct _ETHREAD
{
    struct _KTHREAD Tcb;                                                    //0x0
    union _LARGE_INTEGER CreateTime;                                        //0x4c0
    union
    {
        union _LARGE_INTEGER ExitTime;                                      //0x4c8
        struct _LIST_ENTRY KeyedWaitChain;                                  //0x4c8
    };
    union
    {
        struct _LIST_ENTRY PostBlockList;                                   //0x4d8
        struct
        {
            VOID* ForwardLinkShadow;                                        //0x4d8
            VOID* StartAddress;                                             //0x4e0
        };
    };
    union
    {
        struct _TERMINATION_PORT* TerminationPort;                          //0x4e8
        struct _ETHREAD* ReaperLink;                                        //0x4e8
        VOID* KeyedWaitValue;                                               //0x4e8
    };
    ULONGLONG ActiveTimerListLock;                                          //0x4f0
    struct _LIST_ENTRY ActiveTimerListHead;                                 //0x4f8
    struct _CLIENT_ID Cid;                                                  //0x508
    union
    {
        struct _KSEMAPHORE KeyedWaitSemaphore;                              //0x518
        struct _KSEMAPHORE AlpcWaitSemaphore;                               //0x518
    };
    union _PS_CLIENT_SECURITY_CONTEXT ClientSecurity;                       //0x538
    struct _LIST_ENTRY IrpList;                                             //0x540
    ULONGLONG TopLevelIrp;                                                  //0x550
    struct _DEVICE_OBJECT* DeviceToVerify;                                  //0x558
    VOID* Win32StartAddress;                                                //0x560
    VOID* ChargeOnlySession;                                                //0x568
    VOID* LegacyPowerObject;                                                //0x570
    struct _LIST_ENTRY ThreadListEntry;                                     //0x578
    struct _EX_RUNDOWN_REF RundownProtect;                                  //0x588
    struct _EX_PUSH_LOCK ThreadLock;                                        //0x590
    ULONG ReadClusterSize;                                                  //0x598
    volatile ULONG MmLockOrdering;                                          //0x59c
    union
    {
        ULONG CrossThreadFlags;                                             //0x5a0
        struct
        {
            ULONG Terminated:1;                                             //0x5a0
            ULONG ThreadInserted:1;                                         //0x5a0
            ULONG HideFromDebugger:1;                                       //0x5a0
            ULONG ActiveImpersonationInfo:1;                                //0x5a0
            ULONG HardErrorsAreDisabled:1;                                  //0x5a0
            ULONG BreakOnTermination:1;                                     //0x5a0
            ULONG SkipCreationMsg:1;                                        //0x5a0
            ULONG SkipTerminationMsg:1;                                     //0x5a0
            ULONG CopyTokenOnOpen:1;                                        //0x5a0
            ULONG ThreadIoPriority:3;                                       //0x5a0
            ULONG ThreadPagePriority:3;                                     //0x5a0
            ULONG RundownFail:1;                                            //0x5a0
            ULONG UmsForceQueueTermination:1;                               //0x5a0
            ULONG IndirectCpuSets:1;                                        //0x5a0
            ULONG DisableDynamicCodeOptOut:1;                               //0x5a0
            ULONG ExplicitCaseSensitivity:1;                                //0x5a0
            ULONG PicoNotifyExit:1;                                         //0x5a0
            ULONG DbgWerUserReportActive:1;                                 //0x5a0
            ULONG ForcedSelfTrimActive:1;                                   //0x5a0
            ULONG SamplingCoverage:1;                                       //0x5a0
            ULONG ImpersonationSchedulingGroup:1;                           //0x5a0
            ULONG ReservedCrossThreadFlags:7;                               //0x5a0
        };
    };
    union
    {
        ULONG SameThreadPassiveFlags;                                       //0x5a4
        struct
        {
            ULONG ActiveExWorker:1;                                         //0x5a4
            ULONG MemoryMaker:1;                                            //0x5a4
            ULONG StoreLockThread:2;                                        //0x5a4
            ULONG ClonedThread:1;                                           //0x5a4
            ULONG KeyedEventInUse:1;                                        //0x5a4
            ULONG SelfTerminate:1;                                          //0x5a4
            ULONG RespectIoPriority:1;                                      //0x5a4
            ULONG ActivePageLists:1;                                        //0x5a4
            ULONG SecureContext:1;                                          //0x5a4
            ULONG ZeroPageThread:1;                                         //0x5a4
            ULONG WorkloadClass:1;                                          //0x5a4
            ULONG GenerateDumpOnBadHandleAccess:1;                          //0x5a4
            ULONG BalanceSetManager:1;                                      //0x5a4
            ULONG ReservedSameThreadPassiveFlags:18;                        //0x5a4
        };
    };
    union
    {
        ULONG SameThreadApcFlags;                                           //0x5a8
        struct
        {
            UCHAR OwnsProcessAddressSpaceExclusive:1;                       //0x5a8
            UCHAR OwnsProcessAddressSpaceShared:1;                          //0x5a8
            UCHAR HardFaultBehavior:1;                                      //0x5a8
            volatile UCHAR StartAddressInvalid:1;                           //0x5a8
            UCHAR EtwCalloutActive:1;                                       //0x5a8
            UCHAR SuppressSymbolLoad:1;                                     //0x5a8
            UCHAR Prefetching:1;                                            //0x5a8
            UCHAR OwnsVadExclusive:1;                                       //0x5a8
            UCHAR SystemPagePriorityActive:1;                               //0x5a9
            UCHAR SystemPagePriority:3;                                     //0x5a9
            UCHAR AllowUserWritesToExecutableMemory:1;                      //0x5a9
            UCHAR AllowKernelWritesToExecutableMemory:1;                    //0x5a9
            UCHAR OwnsVadShared:1;                                          //0x5a9
            UCHAR PasidMsrValid:1;                                          //0x5a9
            UCHAR SlabReplenishInProgress:1;                                //0x5aa
        };
    };
    UCHAR CacheManagerActive;                                               //0x5ac
    UCHAR DisablePageFaultClustering;                                       //0x5ad
    UCHAR ActiveFaultCount;                                                 //0x5ae
    UCHAR LockOrderState;                                                   //0x5af
    ULONG SharedPsModuleLockAcquires;                                       //0x5b0
    ULONG MmReserved;                                                       //0x5b4
    ULONGLONG AlpcMessageId;                                                //0x5b8
    union
    {
        VOID* AlpcMessage;                                                  //0x5c0
        ULONG AlpcReceiveAttributeSet;                                      //0x5c0
    };
    struct _LIST_ENTRY AlpcWaitListEntry;                                   //0x5c8
    LONG ExitStatus;                                                        //0x5d8
    ULONG CacheManagerCount;                                                //0x5dc
    ULONG IoBoostCount;                                                     //0x5e0
    ULONG IoQoSBoostCount;                                                  //0x5e4
    ULONG IoQoSThrottleCount;                                               //0x5e8
    ULONG KernelStackReference;                                             //0x5ec
    struct _LIST_ENTRY BoostList;                                           //0x5f0
    struct _LIST_ENTRY DeboostList;                                         //0x600
    ULONGLONG BoostListLock;                                                //0x610
    ULONGLONG IrpListLock;                                                  //0x618
    VOID* ReservedForSynchTracking;                                         //0x620
    struct _SINGLE_LIST_ENTRY CmCallbackListHead;                           //0x628
    struct _GUID* ActivityId;                                               //0x630
    struct _SINGLE_LIST_ENTRY SeLearningModeListHead;                       //0x638
    VOID* VerifierContext;                                                  //0x640
    VOID* AdjustedClientToken;                                              //0x648
    VOID* WorkOnBehalfThread;                                               //0x650
    struct _PS_PROPERTY_SET PropertySet;                                    //0x658
    VOID* PicoContext;                                                      //0x670
    ULONGLONG UserFsBase;                                                   //0x678
    ULONGLONG UserGsBase;                                                   //0x680
    struct _THREAD_ENERGY_VALUES* EnergyValues;                             //0x688
    union
    {
        ULONGLONG SelectedCpuSets;                                          //0x690
        ULONGLONG* SelectedCpuSetsIndirect;                                 //0x690
    };
    struct _EJOB* Silo;                                                     //0x698
    struct _UNICODE_STRING* ThreadName;                                     //0x6a0
    struct _CONTEXT* SetContextState;                                       //0x6a8
    VOID* EtwSupport;                                                       //0x6b0
    struct _LIST_ENTRY OwnerEntryListHead;                                  //0x6b8
    ULONGLONG DisownedOwnerEntryListLock;                                   //0x6c8
    struct _LIST_ENTRY DisownedOwnerEntryListHead;                          //0x6d0
    VOID* SchedulerSharedDataObject;                                        //0x6e0
    VOID* CmThreadInfo;                                                     //0x6e8
    VOID* FlsData;                                                          //0x6f0
    ULONG LastExpectedRunTime;                                              //0x6f8
    ULONG LastSoftParkElectionRunTime;                                      //0x6fc
    ULONGLONG LastSoftParkElectionGeneration;                               //0x700
    struct _GROUP_AFFINITY LastSoftParkElectionGroupAffinity;               //0x708
    ULONGLONG UserIsolationDomain;                                          //0x718
    union
    {
        struct _KAPC UpdateTebApc;                                          //0x720
        struct
        {
            UCHAR UpdateTebApcFill1[3];                                     //0x720
            CHAR Win32kPriorityFloor;                                       //0x723
        };
        struct
        {
            UCHAR UpdateTebApcFill2[4];                                     //0x720
            UCHAR LastSoftParkElectionQos;                                  //0x724
            UCHAR LastSoftParkElectionWorkloadType;                         //0x725
            UCHAR LastSoftParkElectionRunningType;                          //0x726
            UCHAR MmSlabIdentity;                                           //0x727
        };
        struct
        {
            UCHAR UpdateTebApcFill3[64];                                    //0x720
            union _RTL_THREAD_RNG_STATE RngState;                           //0x760
        };
        struct
        {
            UCHAR UpdateTebApcFill4[72];                                    //0x720
            VOID* UsedByRngState;                                           //0x768
        };
        struct
        {
            UCHAR UpdateTebApcFill5[83];                                    //0x720
            UCHAR UpdateTebSpareByte2;                                      //0x773
            ULONG UpdateTebSpareLong2;                                      //0x774
        };
    };
    ULONGLONG Win32kThreadLock;                                             //0x778
    VOID* ThreadIndex;                                                      //0x780
};
```

</details>

## Fibers
Think of fibers like a lightweight thread that you control / schedule yourself. Fibers are invisible to the kernel because they're implemented in user mode in Kernel32.dll, making scheduling of execution manual rather than relying on Windows priority-based scheduling mechanism.

In most cases, letting Windows manage threads automatically is a better choice over managing User-mode fibers manually.

### Working with Fibers
1. You start with a normal thread and call `ConvertThreadToFiber`. This function converts the thread to a running fiber.
2. You can make more fibers using `CreateFiber`. Each fiber can have it's own set of fibers.
3. Instead of Windows deciding which fiber runs, you call `SwitchToFiber` to manually choose which fiber gets to execute.
4. The new fiber runs until it exits or until it calls SwitchToFiber, again selecting another fiber to run.

### Fibers limitations
- Invisible to the kernel: Since the operating system doesn’t know fibers exist, it can’t schedule them properly. This can lead to bad performance.
- TLS issues: Sharing thread local storage (TLS) can be an issue because several fibers can be running on the same thread.
- No True Multithreading: Fibers don’t run on multiple processors at the same time, they are limited to cooperative multi-tasking only. Only one fiber runs per thread.
- Poor I/O performance: Fiber local storage (FLS) exists but doesn't solve all the issues. If a fiber is waiting on a file or network request, the entire thread is stuck waiting.

<details>
<summary> User-mode structure </summary>

```C
typedef struct _NT_FIBER {
    PVOID FiberData;         // Pointer to user-defined fiber-specific (storage) data, similar to TLS
    struct _NT_FIBER *Self;  // Self-reference for integrity checks
    PVOID StackBase;         // Base of the fiber’s stack (highest memory address)
    PVOID StackLimit;        // Stack limit (where stack grows towards)
    PVOID DeallocationStack; // Pointer to memory reserved for stack deallocation
    CONTEXT FiberContext;    // CPU register state for fiber switching
    BOOLEAN FiberFlags;      // Flags (e.g.: Is this the primary fiber?) + other metadeta
} NT_FIBER, *PNT_FIBER;
```

</details>

## User-mode Scheduling threads
User-mode scheduling (UMS) threads, which are available only on 64-bit versions of Windows are an improved version of fibers, with fewer downsides.

They still allow programs to manage their own scheduling instead of relying entirely on the Windows scheduler. However, UMS threads have their own kernel thread state, because of that they are visible to the kernel in contrast to fibers. 

This visibility to the kernel means:
- Allow multiple UMS threads to issue system calls that block execution (e.g.: waiting for file access).
- Share and manage resources properly, unlike fibers.

### How UMS Threads work
- When multiple UMS threads need to run in user mode, they can switch between each other without involving the Windows scheduler.
- From the kernel’s perspective, it looks like the same thread is still running, even though UMS threads are switching internally.
- When a UMS thread needs to enter the kernel (e.g., making a system call), it temporarily switches to a dedicated kernel-mode thread (this is called a directed context switch).
- Every thread in a process shares the same virtual address space, meaning they can read and write the same memory.
- Threads cannot access another process’s memory unless:
    - The other process explicitly shares memory (e.g., using a file mapping object).
    - The process has special permissions (e.g., using ReadProcessMemory and WriteProcessMemory).

### UMS Threads limitations
- UMS threads still can't run on multiple processors at the same time.
- However, they do follow a pre-emptible model, meaning they aren't purely cooperative like fibers (they can be interrupted if needed).

## Services
A service is a process that is designed to perform a specific service for the operating system. These processes get started by the Windows `service control manager (SCM)` and are usually background processes.

Since it runs in the background it doesn't have a GUI or require any interaction from the user.

They run independently of user sessions and provide essential system functions, such as networking, printing, and security. They can start automatically, manually, or on demand.

### Types of services
| System services critical to the OS | Purpose |
|-|-|
| `wininit.exe` | Windows Initialization |
| `lsass.exe` | Local Security Authority |
| `services.exe` | Service Control Manager |

| Networking Services to manage connections | Purpose |
|-|-|
| `Dhcp` | Dynamic Host Configuration Protocol |
| `Dnscache` | DNS Client Service |
| `LanmanServer` | File Sharing & Network Services |

| Security Services to protect the system | purpose |
|-|-|
| WinDefend | Windows Defender Antivirus |
| EventLog | Windows Event Logging |
| W32Time | Windows Time Synchronization |

| Hardware Services to manage devices | purpose |
|-|-|
| Spooler | Print Spooler |
| PlugPlay | Plug and Play service |
| AudioSrv | Windows Audio |

| Application Services installed by third-party apps | purpose |
|-|-|
| SQL Server | MSSQLSERVER database services |
| Apache or Nginx | Web server services |
| VMware or VirtualBox | OS virtualization |

## Child-Parent processes
It's also possible for processes to create / initialize other processes. The process that created the other is called the `parent process`. The process that got created is called the `child process`.

E.g: explorer.exe initializing a msedge.exe process that initializes multiple other msedge.exe processes.

```bash
explorer.exe
└── msedge.exe
    ├── msedge.exe
    ├── msedge.exe
    ├── msedge.exe
    ├── msedge.exe
    ├── msedge.exe
    ├── msedge.exe
    ├── msedge.exe
    ├── msedge.exe
    └── msedge.exe
```

## Handles
Like we've mentioned before in the overview, everything in Windows could be seen as an [object](/Windows_Internals/Introduction.md). Oversimplified but, a handle is a `reference` to a Windows object.

When threads are being run they often require system resources like registry keys, files, folders, session information, etc. 

Essentially, it's a declaration from a thread saying that this `system resource` / `object` is being used by the process.

> [!NOTE]
> A handle makes the specified system resource solely available to it's process.
> 
> It acts as if it's in a locked state from the perspective of outside processes.
>
> If you've ever tried to delete a file that's still open in some process like Word you'd get a message saying: "This action can't be completed because the file is open in Word.".

## Jobs / Job Object
A job (object) in Windows is a management structure that groups multiple processes together into a singular unit. It allows the system (or an administrator) to control and apply limits (e.g., CPU, memory, I/O) to all processes inside the job as a single unit.

- When a process is assigned to a job, it cannot leave the job unless explicitly allowed.
- If a job is terminated, all processes inside it are also terminated.
- Jobs are often used in server environments to control resource usage for groups of processes.

A job can:
- Apply limits to processes inside the job (e.g., memory, CPU usage).
- Monitor and track resource usage for all processes in the job.
- Control process behavior, such as preventing them from creating new processes outside the job.

Essentially, job objects make up for the lack of a structured process tree (unlike UNIX, where processes naturally have parent-child relationships). But jobs are actually more powerful because they allow fine-tuned control over multiple processes at once.

## Named pipes
Named pipes are just a mechanism for two processes to talk to eachother. This comes with another more windows-specific vulnerability; name squatting.

1. Create a named pipe that is used for client-server communication.
2. Start a client that uses said pipe.
3. Use client impersonation to get client priveleges.

## Process creation in the kernel
The steps the kernel takes to create a process are:
1. Initialize the process address space
    - Map `KUSER_SHARED_DATA`, read-only shared memory used for system time, tick count, and other global data.
    - Map the `executable`, Loads the program file into memory.
    - Map `ntdll.dll`, This library is essential for `system calls`, so it’s always mapped into the process.
    - Allocate the [PEB](/Windows_Internals/Virtual_Memory.md#peb), Stores information like command-line arguments, loaded modules, and heap details.
2. Create the initial thread
   - Allocate the stack(s), each thread gets a user-mode stack and a kernel-mode stack.
   - Allocate the [TEB](/Windows_Internals/Virtual_Memory.md#teb), stores per-thread information like thread ID, exception handling data, and TLS slots.
   - Set the instruction pointer to `ntdll.LdrInitializeThunk`, instead of directly executing the program, the thread first runs a function in ntdll.dll to prepare the environment.
     - Handles dynamic DLL loading → Loads required DLLs like kernel32.dll, user32.dll, etc.
     - Processes TLS Callbacks → Calls thread-local storage (TLS) initializers.
     - Calls DllMain for loaded DLLs → If a DLL has a DllMain function, it gets executed here.
     - Sets up the loader lock → Prevents race conditions during DLL loading.
     - Performs a system call: `ZwContinue` → A system call that resumes execution in a new thread context, transferring control to `RtlUserThreadStart`.

   - `RtlUserThreadStart`: calls `kernel32.BaseThreadInitThunk` transferring to User-mode.
   - `BaseThreadInitThunk`:
      - Sets up SEH (structured exception handling).
      - Calls `mainCRTStartup(PEB)`.
   - `mainCRTStartup(PEB)` (provided by the C runtime library):
calls `main(argc, argv)` (for C programs) or `WinMain` (for Windows GUI applications).

> [!NOTE]
> The PEB and TEB are part of a process’s virtual address space in memory. Don't confuse a process's [Virtual Memory Components](/Windows_Internals/Virtual_Memory.md) with process components.

## Tools
There are multiple utilities available that make observing processes easier:
- [Process Hacker 2 / System informer](https://github.com/winsiderss/systeminformer)
- [Process Explorer](https://learn.microsoft.com/en-us/sysinternals/downloads/process-explorer)
- [Procmon](https://learn.microsoft.com/en-us/sysinternals/downloads/procmon)

<!--
TO DO:
- PICO processes, maybe [https://www.youtube.com/watch?v=GhG6Fc__HEE&list=PLt9cUwGw6CYF6Kj19mBZpfhQPsRIC5vGl&index=2]
-->