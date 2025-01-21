## Capabilities
Another method system administrators can use to increase the privilege level of a process or binary is “Capabilities”. Capabilities `help manage privileges at a more granular level`. We can use the `getcap` tool to list enabled capabilities.

For example, if the SOC analyst needs to use a tool that needs to initiate socket connections, a regular user would not be able to do that. If the system administrator does not want to give this user higher privileges, they can `change the capabilities of the binary`. As a result, the binary would get through its task without needing a higher privilege user.

When run as an unprivileged user, `getcap -r / will generate a huge amount of errors`, so it is good practice to `redirect the error messages to /dev/null`. We do this by using `getcap -r / 2>/dev/null`.

`GTFObins` has a good list of binaries that can be leveraged for privilege escalation if we find any set capabilities.

## Cron Jobs
`Cron jobs` are used to `run scripts or binaries at specific times`. By default, they `run with the privilege of their owners` and not the current user. While properly configured cron jobs are not inherently vulnerable, they can provide a privilege escalation vector under some conditions.

The idea is quite simple; if there is a scheduled task that runs with root privileges and we can change the script that will be run, then our script will run with root privileges.

Cron job configurations are stored as `crontabs` (cron tables) to see the next time and date the task will run.

`Each user on the system have their crontab file` and can run specific tasks whether they are logged in or not. As you can expect, our goal will be to `find a cron job set by root and have it run our script`, ideally a shell.

Any user can read the `system-wide file keeping` cron jobs under `/etc/crontab`

Basically, rewrite the script you find with something like a reverse shell in there and make sure it's executeable using: `chmod +x <filename>`.


## PATH
If a folder for which your user has write permission is located in the path, you could potentially hijack an application to run a script. `PATH` in Linux is an `environmental variable` that `tells the operating system where to search for executables`. For any `command that is not built into the shell` or that is `not defined with an absolute path`, Linux will start searching in folders defined under PATH.

E.g: If we type `python` in the command line, the operating system will start searching in the paths defined in `echo $PATH` for the python binary.

Typically the PATH will look like this: `echo $PATH`. To find the path of the program we could use: `where <program_name>`.

As you will see, `this depends entirely on the existing configuration of the target system`, so be sure you can answer the questions:
- What folders are located under $PATH
- Does your current user have write privileges for any of these folders?
- Can you modify $PATH?
- Is there a script/application you can start that will be affected by this vulnerability?

If any writable folder is listed under PATH we could create a binary named `example` under that directory and have our “path” script run it. As the `SUID` bit is set, this `binary will run with root privilege`.

A simple search for writable folders can done using:
-  `find / -writable 2>/dev/null`: all writeable folders
-  `find / -writable 2>/dev/null | cut -d "/" -f 2 | sort -u`: cut and sorted
-  `find / -writable 2>/dev/null | grep usr | cut -d "/" -f 2,3 | sort -u`: targeting a folder like `/usr`.
-  `find / -writable 2>/dev/null | cut -d "/" -f 2,3 | grep -v proc | sort -u`: ridden of many results related to running processes

We can also add a folder to the path like so: `export PATH=/tmp:$PATH`.

PATH vulnerability example:

You can `add the writable directory to your user's PATH` and `create a file named "somename"` that the "./test" executable will read. The "somename" `file can simply be a "cat" command that will read the flag file`.

## NFS
Privilege escalation vectors are not confined to internal access. `Shared folders and remote management interfaces` such as SSH and Telnet can also help you gain root access on the target system. Some cases will also require using both vectors, e.g. finding a root SSH private key on the target system and connecting via SSH with root privileges instead of trying to increase your current user’s privilege level.

Another vector that is more relevant to CTFs and exams is a `misconfigured network shell`. This vector can sometimes be seen during penetration testing engagements when a `network backup system is present`.

`NFS` (Network File Sharing) configuration is kept in the `/etc/exports` file. This file is created during the NFS server installation and can usually be read by users.

Start by enumerating mountable shares:
1. `showmount -e <MACHINE_IP>`
2. `mkdir /tmp/backupsonattackermachine`
3. `mount -o rw <MACHINE_IP>:/backups /tmp/backupsonattackermachine`
4. As we can set `SUID` bits, a simple executable that will run `/bin/bash` on the target system will do the job.
5. On the target system execute the executable.

Quick summary:
- Kernel has high priveledges -> exploit
- Sudo priveledges on binaries / programs -> gtfobins
- SUID files are executable by the owner or group owner -> gtfobins
- Capabilities are partly priveledges on binaries -> gtfobins??
- Cron jobs are autorun scripts -> modify root scripts (to a shell)
- PATH 