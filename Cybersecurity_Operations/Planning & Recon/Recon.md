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
| **crt.sh**     | Certificate Search | `https://crt.sh/` |
| **Certificate Transparency Search Tool** | See Who’s Issued SSL/TLS Certificates to Your Domain Name | `https://ui.ctsearch.entrust.com/ui/ctsearchui` |

## Google Dorking
| Filter    | Example   | Description   |
|-----------|-----------|---------------|
| `site`    | site:tryhackme.com    | returns results only from the specified website address |
| `inurl`   | site:tryhackme.com    | returns results that have the specified word in the URL |
| `filetype` | site:tryhackme.com   | returns results which are a particular file extension |
| `intitle` | intitle:admin         | returns results that contain the specified word in the title |
| `subdomain enumeration` | site:*.tryhackme.com -site:www.tryhackme.com | Used as an OSINT method |

## Content Discovery / Web Walking
| Where to look | Description |
|---------------|-------------|
| `view-source:`    | Source of the web-app |
| `HTML comments`   | Could contain valuabe info |
| `Editing a style` | E.g: `Display: none` is a common way to hide HTML elements |
| `Breakpoints` | Force the browser to stop processing the JavaScript and pause the current execution |
| Network tab   | Examine network entries, server responses, etc.   |
| `robots.txt`  | Tells search engines which pages they are and aren't allowed to show on their search engine results |
| favicon       | Tells search engines which pages they are and aren't allowed to show on their search engine results, try parse it. |
| `Sitemap.xml` | Sitemap.xml file gives a list of every file the website owner wishes to be listed on a search engine |
| HTTP headers  | Headers can sometimes contain useful information such as the webserver software and possibly the programming/scripting language in use. |
| Framework Stack | Establish the framework used to build the site from: favicon, HTML comments, copyright notices, credits, etc. and enumerate from there |
| OSINT         | Use OSINT methods like google dorking, etc. |
| `DNSrecon` | Bruteforce DNS subdomain enumeration |
| `Sublist3r` (& `dnsenum`) | Speed up the process of OSINT subdomain discovery, bruteforce, google, etc. |
| `Ffuf` | Test for virtual hosts |


## Subdomain Enumeration
When an `SSL/TLS` certificate is created for a domain by a CA, CA's create publicly accessible logs of every SSL/TLS certificate created for a domain name. The purpose of `Certificate Transparency logs` is to stop malicious and accidentally made certificates from being used. We can use this service to our advantage to discover subdomains belonging to a domain, sites like `https://crt.sh` and `https://ui.ctsearch.entrust.com/ui/ctsearchui` offer a searchable database of certificates that shows current and historical results.

## Bruteforce DNS enumeration
Trying tens, hundreds, thousands or even millions of different possible subdomains from a pre-defined list of commonly used subdomains.
E.g: `admin.example.com` or `staging.example.com`

Note: this IS `NOT like go/dirbuster`, they focus on directories and files so `example.com/directory` or `example.com/file.extension`.

Note: `Sublist3r` automates this process and does some google dorking too.

## Virtual Hosts
A web server can host multiple websites on the same IP address. It uses the Host header in the HTTP request to figure out which website to serve.

Example: Server at 192.168.1.1 hosts: `example.com` & `admin.example.com`

Some subdomains aren't always hosted in publically accessible DNS results, such as development versions of a web application or administration portals.
Instead, the DNS record could be kept on a private DNS server or recorded on the developer's machines in their `Linux: /etc/hosts file` or `Windows: c:\windows\system32\drivers\etc\hosts` which maps domain names to IP addresses.

Because web servers can host multiple websites from one server when a website is requested from a client, the server knows which website the client wants from the Host header. We can `utilise this host header by making changes to it` and monitoring the response to see if we've discovered a new website.

Like with DNS Bruteforce, we can automate this process by using a `wordlist of commonly used subdomains`.

## Passive reconnaissance
In passive reconnaissance, you rely on publicly available knowledge. Think of it like you are looking at target territory from afar without stepping foot on that territory.

Passive reconnaissance activities include many activities, for instance:
- Looking up DNS records of a domain from a public DNS server.
- Checking job ads related to the target website.
- Reading news articles about the target company.

| Tool | Description | Example |
| - | - | - |
| Whois | request and response protocol that follows the RFC 3912 specification. A WHOIS server listens on TCP port 43 for incoming requests. The domain registrar is responsible for maintaining the WHOIS records for the domain names it is leasing. The WHOIS server replies with various information related to the domain requested. Of particular interest, we can learn. | `Registrar`, `Contact info` of registrant, `Creation-, Update- and Expiration dates`, `Name Server` |
| nslookup | Find the IP address of a domain name using nslookup, which stands for Name Server Look Up. | `nslookup -type=[A(ipv4) or AAAA(ipv6)m CNAME, MX, SOA, TXT] [DOMAIN_NAME] [SERVER].` |
| dig | For more advanced DNS queries and additional functionality, you can use dig, the acronym for “Domain Information Groper” | `dig [SERVER] [DOMAIN_NAME] [TYPE]`, e.g: `dig tryhackme.com MX` |
| DNSDumpster | Dump subdomain records | `https://dnsdumpster.com/` |
| Shodan.io | Helpful to learn various pieces of information about the client’s network, without actively connecting to it. | `https://www.shodan.io/` |

## Active reconnaissance
Cannot be achieved so discreetly as it requires direct engagement with the target. Think of it like you check the locks on the doors and windows, among other potential entry points.

Examples of active reconnaissance activities include:
- Connecting to one of the company servers such as HTTP, FTP, and SMTP.
- Calling the company in an attempt to get information (social engineering).
- Entering company premises pretending to be a repairman.

| Tool | Description | Example |
| - | - | - |
| Web browser | Connecting to TCP ports. There are also plenty of add-ons: `FoxyProxy`, `User-Agent Switcher and Manager`, `Wappalyzer`, etc. | Connect to a `port` that has a supported web-service and look at the `developer tools` |
| Ping | Check whether you can reach the remote system and that the remote system can reach you back. The ping command sends a packet to a remote system, and the remote system replies. This way, you can conclude that the remote system is `online` and that the network is working between the two systems. | `ping -c 5 10.10.228.63`, pings the machine 5 times |
| traceroute | Traces the route taken by the packets from your system to another host. | `traceroute 10.10.228.63` on linux or `tracert 10.10.228.63` on windows |
| Telnet | The default port used by telnet is 23 and it sends all data in **cleartext**. You can use Telnet to connect to any service and grab its banner since it relies on TCP. | `telnet 10.10.228.63 80` |
| Netcat or nc (as client or as server) | Netcat supports both TCP and UDP protocols. It can function as a client that connects to a listening port; alternatively, it can act as a server that listens on a port of your choice. | `nc 10.10.228.63 80` or `nc -lvnp 80` where l = listen, v = verbose, n = numeric only, no DNS resolution, p = port specification |