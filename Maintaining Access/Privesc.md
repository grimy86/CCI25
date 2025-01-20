## Enumeration
### System info
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

## Stabilizing your shell
### Python
- `python3 -c 'import pty; pty.spawn("/bin/bash")'`
