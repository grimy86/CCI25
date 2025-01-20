## CAPA Cheat Sheet

| Command                                               | Description                                                 | Example                                                   |
|-------------------------------------------------------|-------------------------------------------------------------|-----------------------------------------------------------|
| `capa [file]`                                         | Analyzes a binary file for capabilities.                    | `capa malware.exe`                                        |
| `capa --rules [rules-dir] [file]`                     | Specifies a custom rules directory for analysis.            | `capa --rules ./custom-rules malware.exe`                 |
| `capa --format [format] [file]`                       | Outputs results in a specified format (json, yaml, pgrep).  | `capa --format json malware.exe > output.json`            |
| `capa --tag [tags] [file]`                            | Filters results based on specific tags.                     | `capa --tag persistence malware.exe`                      |
| `capa --signatures [sigfile] [file]`                  | Adds custom function signatures to the analysis.            | `capa --signatures myfuncs.sig malware.exe`               |
| `capa --verbose [file]`                               | Displays additional diagnostic information.                 | `capa --verbose malware.exe`                              |
| `capa --ignore-unsupported`                           | Skips errors related to unsupported file types.             | `capa --ignore-unsupported unknownfile.bin`               |
| `capa --color`                                        | Enables colorized output for better readability.            | `capa --color malware.exe`                                |

---

## Common CAPA Workflows
### Basic Analysis of a Malware Binary
```bash
# Basic Analysis of a Malware Binary
capa malware.exe

# Analyzing with Verbose Output
capa --verbose malware.exe

# Using a Custom Ruleset for Analysis
capa --rules ./custom-rules malware.exe

# Exporting Results in JSON Format
capa --format json malware.exe > results.json

# Filtering for Specific Tags (e.g., Persistence)
capa --tag persistence malware.exe
```