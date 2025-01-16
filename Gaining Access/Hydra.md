## Hydra Cheat Sheet
Hydra is a parallelized login cracker which supports numerous protocols to attack. It is very fast and flexible, and new modules are easy to add.

| Command                                           | Description                                               | Example                                             |
|---------------------------------------------------|-----------------------------------------------------------|-----------------------------------------------------|
| `hydra -l [user] -p [password] [target] [service]`| Performs a brute-force attack with one username and one password. | `hydra -l admin -p password123 192.168.1.10 ssh`    |
| `hydra -L [userlist] -p [password] [target] [service]`| Uses a list of usernames and a single password.           | `hydra -L users.txt -p password123 192.168.1.10 ssh`|
| `hydra -l [user] -P [passwordlist] [target] [service]`| Uses a single username and a list of passwords.           | `hydra -l admin -P rockyou.txt 192.168.1.10 ftp`    |
| `hydra -L [userlist] -P [passwordlist] [target] [service]`| Uses lists of usernames and passwords.                   | `hydra -L users.txt -P rockyou.txt 192.168.1.10 ssh`|
| `hydra -e [mode] [target] [service]`              | Tests additional passwords based on `mode` (e.g., empty, reverse). | `hydra -l admin -P rockyou.txt -e nsr 192.168.1.10 http` |
| `hydra -t [threads] [target] [service]`           | Sets the number of parallel connections (default: 16).    | `hydra -l admin -P passwords.txt -t 4 192.168.1.10 ssh` |
| `hydra -vV [target] [service]`                    | Enables verbose output for detailed logging.              | `hydra -vV -l admin -P rockyou.txt 192.168.1.10 ssh`|
| `hydra -s [port] [target] [service]`              | Specifies a non-default port for the service.             | `hydra -l admin -P rockyou.txt -s 2222 192.168.1.10 ssh`|
| `hydra -f [target] [service]`                     | Stops the attack after the first successful login.         | `hydra -l admin -P rockyou.txt -f 192.168.1.10 ssh` |
| `hydra -o [file] [target] [service]`              | Saves successful login attempts to a file.                | `hydra -l admin -P rockyou.txt -o results.txt ssh://192.168.1.10` |

---

## Common Services and Commands
| Service       | Example Command                                      |
|---------------|------------------------------------------------------|
| **SSH**       | `hydra -l root -P passwords.txt 192.168.1.10 ssh`    |
| **FTP**       | `hydra -L users.txt -P passwords.txt 192.168.1.10 ftp`|
| **HTTP GET**  | `hydra -L users.txt -P passwords.txt 192.168.1.10 http-get /login` |
| **HTTP POST** | `hydra -L users.txt -P passwords.txt 192.168.1.10 http-post-form "/login:user=^USER^&pass=^PASS^:F=incorrect"` |
| **RDP**       | `hydra -l admin -P passwords.txt 192.168.1.10 rdp`   |
| **MySQL**     | `hydra -L users.txt -P passwords.txt 192.168.1.10 mysql` |
| **SMB**       | `hydra -L users.txt -P passwords.txt 192.168.1.10 smb` |

---

## Workflow Example
1. **Test a Single Username and Wordlist**
   ```bash
   hydra -l admin -P rockyou.txt 192.168.1.10 ssh