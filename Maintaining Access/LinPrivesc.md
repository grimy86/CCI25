# Priveledge escalation
Ok, we have a shell. Now what? Most shells tend to be unstable and non-interactive. Time to exploit of a vulnerability, design flaw, or configuration oversight in an operating system or application to `gain unauthorized access` to resources that are usually restricted from the users.

On Linux ideally we would be `looking for opportunities to gain access to a user account`. Some exploits will also allow you to add your own account. In particular something like [`Dirty C0w`](https://dirtycow.ninja/) or a writeable `/etc/shadow` or `/etc/passwd` would quickly give you SSH access to the machine, assuming SSH is open.

## System info
Note: any file containing system information `can be customized or changed`.

- `hostname`: This value can easily be changed or have a relatively meaningless string BUT, in unedited cases it can provide some info about a system's role inside of a network.

  Example: `SQL-PROD-01` for a SQL production server.

- `uname -a`: Additional details about the kernel used by the system. Useful when searching for any potential kernel vulnerabilities that could lead to privilege escalation.
- `/proc/version`: Provides information about the target system processes. May give you information on the kernel version and additional data such as whether a compiler (e.g. GCC) is installed.
- `/etc/issue` & `lsb_release -a`: Operating system information can also be identified by looking at the /etc/issue file.
- `ps`: Process Statis will output running processes.
  - `PID`: The process ID (unique to the process)
  - `TTY`: Terminal type used by the user
  - `Time`: Amount of CPU time used by the process (this is NOT the time this process has been running for)
  - `CMD`: The command or executable running (will NOT display any command line parameter)

  The “ps” command provides a few useful options:
  - `ps -A`: View all running processes
  - `ps axjf`: View process tree
  - `ps aux`: The aux option will show processes for all users (a), display the user that launched the process (u), and show processes that are not attached to a terminal (x). Looking at the ps aux command output, we can have a better understanding of the system and potential vulnerabilities.
- `systemctl list-units --type=service`: Lists systemctl services.
- `env`: Show environmental variables, The `PATH` variable `may have a compiler or a scripting language` (e.g. Python) that could be used to run code on the target system.
- `sudo -l`: List all commands your user can run using sudo.
- `ls -la`: Remember to always use the ls command with the `-la` parameter as it shows hidden files.

## User info
- `whoami`: Shows the user you are using.
- `Id`: General overview of the user’s privilege level and group memberships.
- `groups`: Lists the groups.
- `/etc/passwd`: discover users on the system. The output can be long and a bit intimidating but it can easily be cut and converted to a useful list for brute-force attacks.

  Remember that this will return all users, some of which are `system or service users` that would not be very useful. Another approach could be to `grep | home` as real users will most likely have their folders under the “home” directory.

- `history`: Looking at earlier commands with the history command can give us some idea about the target system and, albeit rarely, have stored information such as passwords or usernames.

## Network
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
  - `netstat -tuln`: Show open ports.
- `ss -tuln`: List active connections.

## Find command
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

Find specific file permissions:
Below is a short example used to find files that have the SUID bit set. The SUID bit allows the file to run with the privilege level of `the account that owns it, rather than the account which runs it`. This allows for an interesting privilege escalation.

- `find / -perm -u=s -type f 2>/dev/null`: Find files with the SUID bit, which allows us to run the file with a higher privilege level than the current user.

## General linux command
As we are in the Linux realm, familiarity with Linux commands, in general, will be very useful. Please spend some time getting comfortable with commands such as `find`, `less`, `locate`, `grep`, `cut`, `sort`, etc.

## Automated Enumeration Tools
Several tools can help you save time during the enumeration process. These tools should only be used to save time knowing they may miss some privilege escalation vectors:
- [`LinPeas`](https://github.com/carlospolop/privilege-escalation-awesome-scripts-suite/tree/master/linPEAS)
- [`LinEnum`](https://github.com/rebootuser/LinEnum)
- [`LES (Linux Exploit Suggester)`](https://github.com/mzet-/linux-exploit-suggester)
- [`Linux Smart Enumeration`](https://github.com/diego-treitos/linux-smart-enumeration)
- [`Linux Priv Checker`](https://github.com/linted/linuxprivchecker)

## Kernel exploits
The kernel on Linux systems `manages the communication between components such as the memory on the system and applications`. This critical function `requires the kernel to have specific privileges`; thus, a successful exploit will potentially lead to root privileges.

A failed kernel exploit can lead to a system crash.

The Kernel exploit methodology is simple;
1. Identify the kernel version
2. Search and find an exploit code for the kernel version of the target system
3. Run the exploit

Research sources:
1. Based on your findings, you can use Google to search for an existing exploit code.
2. Sources such as [`cvedetails`](https://www.cvedetails.com/) can also be useful.
3. Another alternative would be to use a script like `LES (Linux Exploit Suggester)` but remember that these tools can generate false positives (report a kernel vulnerability that does not affect the target system) or false negatives (not report any kernel vulnerabilities although the kernel is vulnerable).

Hints/Notes:
1. Being too specific about the kernel version when searching for exploits on `Google`, `Exploit-db`, or `searchsploit`
2. Be sure you understand how the exploit code works BEFORE you launch it. `Some exploit codes can make changes on the operating system that would make them unsecured in further use or make irreversible changes to the system`, creating problems later. Of course, these may not be great concerns within a lab or CTF environment, but these are absolute no-nos during a real penetration testing engagement.
3. Some exploits `may require further interaction` once they are run. Read all comments and instructions provided with the exploit code.
4. You can transfer the exploit code from your machine to the target system using the `SimpleHTTPServer Python module` and `wget` respectively.

## Sudo
The sudo command, by default, allows you to run a program with root privileges. Under some conditions, system administrators may need to give regular users some flexibility on their privileges.

Any user can check its current situation related to root privileges using the `sudo -l` command.

[`GTFObins`](https://gtfobins.github.io/) is a valuable source that provides information on how any program, on which you may have sudo rights, can be used.

Some applications will not have a known exploit within this context. Such an application you may see is the Apache2 server. n this case, we can use a "hack" to leak information leveraging a function of the application. As Apache2 has an option that supports loading alternative configuration files (-f : specify an alternate ServerConfigFile).

Loading the /etc/shadow file using this option will result in an error message that includes the first line of the /etc/shadow file.

## SUID
Much of Linux privilege controls rely on controlling the users and files interactions. This is done with permissions. By now, you know that files can have read, write, and execute permissions. These are given to users within their privilege levels. This changes with `SUID (Set-user Identification)` and `SGID (Set-group Identification)`. These `allow files to be executed with the permission level of the file owner or the group owner`, respectively.

`find / -type f -perm -04000 -ls 2>/dev/null` will list files that have SUID or SGID bits set.

A good practice would be to compare `executables` on this list with `GTFOBins`. Clicking on the `SUID` button will filter binaries known to be exploitable when the SUID bit is set (you can also use [this link](https://gtfobins.github.io/#+suid) for a pre-filtered list ).

## Capabilities

## Cron Jobs

## PATH

## NFS