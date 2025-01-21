# Priveledge escalation
Ok, we have a shell. Now what? Most shells tend to be unstable and non-interactive. Time to exploit of a vulnerability, design flaw, or configuration oversight in an operating system or application to `gain unauthorized access` to resources that are usually restricted from the users.

## Linux
On Linux ideally we would be `looking for opportunities to gain access to a user account`. Some exploits will also allow you to add your own account. In particular something like [`Dirty C0w`](https://dirtycow.ninja/) or a writeable `/etc/shadow` or `/etc/passwd` would quickly give you SSH access to the machine, assuming SSH is open.

### System info
Note: any file containing system information `can be customized or changed`.

- `hostname`: This value can easily be changed or have a relatively meaningless string BUT, in unedited cases it can provide some info about a system's role inside of a network.

  Example: `SQL-PROD-01` for a SQL production server.

- `uname -a`: Additional details about the kernel used by the system. Useful when searching for any potential kernel vulnerabilities that could lead to privilege escalation.
- `/proc/version`: Provides information about the target system processes. May give you information on the kernel version and additional data such as whether a compiler (e.g. GCC) is installed.
- `/etc/issue`: Operating system information can also be identified by looking at the /etc/issue file.
- `ps`: Process Statis will output running processes.
  - `PID`: The process ID (unique to the process)
  - `TTY`: Terminal type used by the user
  - `Time`: Amount of CPU time used by the process (this is NOT the time this process has been running for)
  - `CMD`: The command or executable running (will NOT display any command line parameter)

  The “ps” command provides a few useful options:
  - `ps -A`: View all running processes
  - `ps axjf`: View process tree
  - `ps aux`: The aux option will show processes for all users (a), display the user that launched the process (u), and show processes that are not attached to a terminal (x). Looking at the ps aux command output, we can have a better understanding of the system and potential vulnerabilities.
- `env`: Show environmental variables, The `PATH` variable `may have a compiler or a scripting language` (e.g. Python) that could be used to run code on the target system.
- `sudo -l`: List all commands your user can run using sudo.
- `ls -la`: Remember to always use the ls command with the `-la` parameter as it shows hidden files.

### User info
- `Id`: General overview of the user’s privilege level and group memberships.
- `/etc/passwd`: discover users on the system. The output can be long and a bit intimidating but it can easily be cut and converted to a useful list for brute-force attacks.

  Remember that this will return all users, some of which are `system or service users` that would not be very useful. Another approach could be to `grep | home` as real users will most likely have their folders under the “home” directory.

- `history`: Looking at earlier commands with the history command can give us some idea about the target system and, albeit rarely, have stored information such as passwords or usernames.

### Network
- `ifconfig`: The target system `may be a pivoting point to another network`. The ifconfig command will give us information about the `network interfaces of the system`.

  Example: Our attacking machine can reach the `eth0` interface but can not directly access the two other networks. This can be confirmed using the `ip route` command to see which network routes exist.
- `netstat`: The netstat command can be used with several different options to gather information on `existing connections`.
  - `netstat -a`: shows all `listening ports` and `established connections`.
  - `netstat -at` or `netstat -au`: list TCP or UDP protocols respectively.
  - `netstat -l`: list ports in “listening” mode.
  - `netstat -lt`: list TCP ports in “listening” mode.
  - `netstat -s`: list network usage statistics by protocol. This can also be used with the `-t` or `-u` options to limit the output to a specific protocol.
  - `netstat -tp`: list connections with the service name and PID information. This can also be used with the `-l` option to list listening ports.
  - `netstat -i`: Show inteface statistics.
  - `netstat -ano`: `-a`: Display all sockets, `-n`: Do not resolve names & `-o`: Display timers.

### Find command
Searching the target system for important information and potential privilege escalation vectors can be fruitful. The built-in `find` command is useful and worth keeping in your arsenal.

- `find . -name flag1.txt`: find the file named “flag1.txt” in the current directory
- `find /home -name flag1.txt`: find the file names “flag1.txt” in the /home directory
- `find / -type d -name config`: find the directory named config under “/”
- `find / -type f -perm 0777`: find files with the 777 permissions (files readable, writable, and executable by all users)
- `find / -perm a=x`: find executable files
- `find /home -user frank`: find all files for user “frank” under “/home”
- `find / -mtime 10`: find files that were modified in the last 10 days
- `find / -atime 10`: find files that were accessed in the last 10 day
- `find / -cmin -60`: find files changed within the last hour (60 minutes)
- `find / -amin -60`: find files accesses within the last hour (60 minutes)
- `find / -size 50M`: find files with a 50 MB size

This command can also be used with `(+)` and `(-)` signs to specify a file that is larger or smaller than the given size.

Folders and files that can be written to or executed from:
- `find / -writable -type d 2>/dev/null`: Find world-writeable folders
- `find / -perm -222 -type d 2>/dev/null`: Find world-writeable folders
- `find / -perm -o w -type d 2>/dev/null`: Find world-writeable folders
- `find / -perm -o x -type d 2>/dev/null`: Find world-executable folders

The reason we see three different “find” commands that could potentially lead to the same result can be seen in the manual document.

Find development tools and supported languages:
- `find / -name perl*`
- `find / -name python*`
- `find / -name gcc*`

## Enumeration
### System info
- SSH keys: `/home/<user>/.ssh`
- Kernel version: `uname -a`
- Distro & version:
  - `lsb_release -a`
  - `cat /etc/*release`
- Users and Groups:
  - `whoami`
  - `id`
- Other users:
  - `cat /etc/passwd`
- Groups:
  - `groups`
### Processes and services
- Running processes: `ps aux`
- Services: `systemctl list-units --type=service`
### Files and permissions
- World-writable files: `find / -type f -perm -o+w 2>/dev/null`
- Shadow: `cat /etc/shadow`
- SUID binaries: `find / -perm -u=s -type f 2>/dev/null`
### Network
- Open ports: `netstat -tuln`
- Active connections: `ss -tuln`

## Windows
On Windows the options are often more limited. It's sometimes possible to find passwords for `running services in the registry`. `VNC servers`, for example, frequently leave passwords in the registry stored in plaintext. Some versions of the `FileZilla FTP server` also leave credentials in an XML file at `C:\Program Files\FileZilla Server\FileZilla Server.xml`
 or `C:\xampp\FileZilla Server\FileZilla Server.xml`. These can be `MD5 hashes` or in plaintext, depending on the version.

Ideally on Windows you would obtain a shell running as the `SYSTEM user`, or an `administrator account` running with high privileges. In such a situation it's possible to simply add your own account (in the administrators group) to the machine, then log in over `RDP`, `telnet`, `winexe`, `psexec`, `WinRM` or any number of other methods, dependent on the services running on the box.

The syntax for this is as follows:
- `net user <username> <password> /add`
- `net localgroup administrators <username> /add`