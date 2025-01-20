## DirBuster Cheat Sheet
| Command                                           | Description                                               | Example                                                 |
|---------------------------------------------------|-----------------------------------------------------------|---------------------------------------------------------|
| Select wordlist                                   | Specify a dictionary file for directory brute-forcing.    | Use the **DirBuster** GUI to choose `directory-list-2.3-medium.txt`. |
| Configure target                                  | Set the target URL and port.                              | Target `http://192.168.1.10:80`.                       |
| Set file extensions                               | Include specific file extensions for brute-forcing.       | Add `.php,.html,.txt` to the extensions list.           |
| Threads                                           | Increase or decrease the number of threads for efficiency.| Set threads to 50 for faster scanning.                  |
| Recursive scanning                                | Enable scanning of subdirectories.                        | Enable recursive mode in settings.                     |

### DirBuster Example Workflow:
1. Open DirBuster and input the target URL (e.g., `http://192.168.1.10:80`).
2. Select a wordlist like `directory-list-2.3-medium.txt`.
3. Configure file extensions to include `.php, .txt, .html`.
4. Set the thread count to 50 for faster scans.
5. Start the scan and analyze results for accessible directories/files.

## GoBuster Cheat Sheet
| Command                                                    | Description                                               | Example                                                 |
|------------------------------------------------------------|-----------------------------------------------------------|---------------------------------------------------------|
| `gobuster dir -u [URL] -w [wordlist]`                      | Scans directories using a wordlist.                       | `gobuster dir -u http://192.168.1.10 -w common.txt`     |
| `gobuster dir -u [URL] -w [wordlist] -x [extensions]`      | Adds file extensions to the directory scan.               | `gobuster dir -u http://192.168.1.10 -w common.txt -x php,html,txt` |
| `gobuster dir -u [URL] -w [wordlist] -t [threads]`         | Sets the number of threads for the scan.                  | `gobuster dir -u http://192.168.1.10 -w common.txt -t 50` |
| `gobuster dir -u [URL] -w [wordlist] -o [outputfile]`      | Saves scan results to a file.                             | `gobuster dir -u http://192.168.1.10 -w common.txt -o results.txt` |
| `gobuster dir -u [URL] -w [wordlist] --wildcard`           | Detects wildcard subdomains or directories.               | `gobuster dir -u http://192.168.1.10 -w common.txt --wildcard` |
| `gobuster dns -d [domain] -w [wordlist]`                   | Scans for subdomains of a domain.                         | `gobuster dns -d example.com -w subdomains.txt`         |
| `gobuster vhost -u [URL] -w [wordlist]`                    | Scans for virtual hostnames using a wordlist.             | `gobuster vhost -u http://192.168.1.10 -w vhosts.txt`   |

## Common GoBuster Workflows
### Scan Directories with Extensions
```bash
gobuster dir -u http://192.168.1.10 -w common.txt -x php,html,txt
