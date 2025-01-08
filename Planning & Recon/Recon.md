# Recon
## Tools
| Tool           | Description                                           | Example of Usage                                                                 |
|----------------|-------------------------------------------------------|-----------------------------------------------------------------------------------|
| **theHarvester**| Gathers email addresses, subdomains, and more from public sources. | `theHarvester -d example.com -b google`                                             |
| **Shodan**      | Search engine for internet-connected devices.         | `shodan search "apache" -o results.json`                                           |
| **Recon-ng**    | Web reconnaissance framework with modules for gathering OSINT. | `recon-cli modules load recon/domains-hosts/google_site_web`                       |
| **SpiderFoot**  | Automates the process of gathering OSINT on domains, IPs, and more. | `spiderfoot -s example.com -m all -o results.json`                                |
| **Maltego**     | Data mining tool for link analysis, visualizing relationships between entities. | `maltego -i example.com`                                                          |
| **Censys**      | Search engine for discovering internet assets and vulnerabilities. | `censys search "apache" --limit 10`                                                |
| **Amass**       | DNS enumeration tool for discovering subdomains and mapping attack surfaces. | `amass enum -d example.com -o subdomains.txt`                                      |
| **Whois**       | Domain registration lookup tool.                       | `whois example.com`                                                               |
| **Google Dorking**| Advanced Google search queries to find sensitive data. | `site:example.com inurl:"admin"`                                                  |
| **FOCA**        | Tool for extracting metadata from documents and files. | `foca.exe -d example.com -t doc,pdf,xls`                                           |
| **Wigle**       | Wireless network geolocation tool for discovering Wi-Fi networks. | `wigle -t "SSID" -g "location"`                                                   |
| **Have I Been Pwned**| Check if email addresses or domains have been involved in breaches. | `https://haveibeenpwned.com/`                                                     |
| **OSINT Framework**| Collection of links and resources for conducting OSINT investigations. | `https://osintframework.com/`                                                     |
| **Pipl**        | People search engine for gathering information on individuals. | `pipl.com`                                                                        |
| **PublicWWW**   | Search engine for discovering source code snippets and web technologies. | `https://publicwww.com/websites?q="example"`                                      |
| **Wappalyzer** | online tool and browser extension that helps identify what technologies a website uses | `https://www.wappalyzer.com/` |
| **Wayback Machine** | A historical archive of websites that dates back to the late 90s | `https://archive.org/web/` |
| **GitHub** | A version control system that tracks changes to files in a project | `https://github.com/` |
| **S3 Buckets** | A storage service provided by Amazon AWS | `http(s)://[name].s3.amazonaws.com ` |

## Google Dorking
| Filter    | Example   | Description   |
|-----------|-----------|---------------|
| `site`    | site:tryhackme.com    | returns results only from the specified website address |
| `inurl`   | site:tryhackme.com    | returns results that have the specified word in the URL |
| `filetype` | site:tryhackme.com   | returns results which are a particular file extension |
| `intitle` | intitle:admin         | returns results that contain the specified word in the title |
