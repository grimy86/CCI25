# Linux
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

