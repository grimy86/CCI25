# Linux
## Directories
| **Directory Name**       | **Directory Path** | **Directory Description**                                                                 |
|---------------------------|--------------------|------------------------------------------------------------------------------------------|
| **Etcetera**             | `/etc`            | Contains system configuration files, such as `passwd`, `shadow`, and `sudoers`.          |
| **Variable Data**        | `/var`            | Stores frequently updated data like logs, backups, and temporary files.                 |
| **Root User Home**       | `/root`           | Home directory for the `root` user.                                                     |
| **Temporary**            | `/tmp`            | Stores temporary files; contents are cleared on system reboot.                          |
| **User System Resources**| `/usr`            | Contains system applications, libraries, and documentation for user programs.           |
| **Home Directories**     | `/home`           | Stores personal directories for all non-root users.                                      |
| **Boot Files**           | `/boot`           | Files required for booting the system, including the kernel and bootloader.             |
| **Device Files**         | `/dev`            | Contains device files for accessing hardware and peripherals.                           |
| **System Binaries**      | `/bin`            | Essential system commands and binaries (e.g., `ls`, `cp`).                              |
| **System Libraries**     | `/lib`            | Shared libraries and kernel modules required for system binaries in `/bin` and `/sbin`. |
| **Optional Packages**    | `/opt`            | Used for optional or third-party software installations.                                |
| **Process Files**        | `/proc`           | Virtual filesystem providing information about running processes and system resources.  |
| **System Information**   | `/sys`            | Virtual filesystem providing information about hardware and system configurations.       |
| **System Administration**| `/sbin`           | System administration commands (e.g., `ifconfig`, `reboot`).                            |
| **Media Mount Points**   | `/media`          | Temporary mount points for removable media like USB drives and CDs.                     |
| **Mount Points**         | `/mnt`            | Temporary mount points for manually mounted filesystems.                                |

## Commands
| Command               | Description                                         | Example                                    |
|-----------------------|-----------------------------------------------------|--------------------------------------------|
| `ls`                 | Lists files and directories in the current location. | `ls`                                       |
| `ls -a`              | Lists all files, including hidden ones.              | `ls -a`                                    |
| `cd [directory]`     | Changes the current working directory.               | `cd /var/log`                              |
| `pwd`                | Prints the current working directory.                | `pwd`                                      |
| `cat [filename]`     | Displays the content of a file.                      | `cat /etc/passwd`                          |
| `grep [pattern]`     | Searches for a pattern in files or output.           | `grep 'admin' users.txt`                   |
| `find -name [name]`  | Searches for files matching a name.                  | `find -name passwords.txt`                 |
| `nano [filename]`    | Opens a simple text editor in the terminal.          | `nano config.txt`                          |
| `vim [filename]`     | Opens a powerful text editor in the terminal.        | `vim config.txt`                           |
| `mkdir [directory]`  | Creates a new directory.                             | `mkdir backups`                            |
| `rm [file/directory]`| Removes files or directories.                        | `rm example.txt`                           |
| `rmdir [directory]`  | Removes an empty directory.                          | `rmdir old_folder`                         |
| `mv [src] [dest]`    | Moves or renames files or directories.               | `mv file.txt /tmp/`                        |
| `cp [src] [dest]`    | Copies files or directories.                         | `cp file.txt backup.txt`                   |
| `scp [src] [dest]`   | Securely copies files between systems.               | `scp file.txt user@host:/path`             |
| `wget [url]`         | Downloads files from the internet.                   | `wget http://example.com/file.zip`         |
| `echo [text]`        | Prints text to the terminal or writes to a file.     | `echo "hello" > greetings.txt`             |
| `ssh [user@host]`    | Connects to a remote server securely.                | `ssh admin@192.168.1.1`                    |
| `ps`                 | Displays running processes.                          | `ps`                                       |
| `ps aux`             | Displays all running processes in detail.            | `ps aux`                                   |
| `top`                | Displays real-time system resource usage.            | `top`                                      |
| `kill [pid]`         | Terminates a process by its ID.                      | `kill 1234`                                |
| `sigterm`            | Sends the SIGTERM signal to terminate gracefully.    | `kill -15 1234`                            |
| `sigkill`            | Sends the SIGKILL signal to force termination.       | `kill -9 1234`                             |
| `sigstop`            | Sends the SIGSTOP signal to pause a process.         | `kill -19 1234`                            |
| `systemctl`          | Manages system services (start, stop, enable, etc.). | `systemctl restart apache2`                |
| `tee [file]`         | Outputs text to both the terminal and a file.        | `echo "data" | tee output.txt`             |
| `fg`                 | Brings a background process to the foreground.       | `fg`                                       |
| `bg`                 | Sends a process to the background.                   | `bg`                                       |
| `crontab`            | Edits or lists scheduled tasks.                      | `crontab -l`                               |
| `file [filename]`    | Identifies the type of a file.                        | `file example.txt`                         |
| `su [user]`          | Switches to another user account.                    | `su root`                                  |
| `whoami`             | Displays the current user’s name.                    | `whoami`                                   |

## Common OS files for path traversal
| Location | Description |
| - | - |
| `/etc/issue` | contains a message or system identification to be printed before the login prompt. |
| `/etc/profile` | controls system-wide default variables, such as Export variables, File creation mask (umask), Terminal types, Mail messages to indicate when new mail has arrived |
| `/proc/version` | specifies the version of the Linux kernel |
| `/etc/passwd` | has all registered users that have access to a system |
| `/etc/shadow` | contains information about the system's users' passwords |
| `/root/.bash_history` | contains the history commands for root user |
| `/var/log/dmessage` | contains global system messages, including the messages that are logged during system startup |
| `/var/mail/root` | all emails for root user |
| `/root/.ssh/id_rsa` | Private SSH keys for a root or any known valid user on the server |
| `/var/log/apache2/access.log` | the accessed requests for Apache web server |
| `C:\boot.ini` | contains the boot options for computers with BIOS firmware |