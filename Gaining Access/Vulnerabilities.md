# Vulnerabilities
General path:
1. Manage to get an IP or domain to scan and enumerate more information
2. Manage to find running services
3. Explore the running services or results from a previous scan to find version numbers.
4. Research the version in a database to find a useable PoC
5. Exploit
6. Privesc

## Some terms
| Term | Definition |
|-|-|
| Vulnerability | A vulnerability is defined as a weakness or flaw in the design, implementation or behaviours of a system or application. |
| Exploit | An exploit is something such as an action or behaviour that utilises a vulnerability on a system or application. |
| Proof of Concept (PoC) | A PoC is a technique or tool that often demonstrates the exploitation of a vulnerability. |

## Types
| Vulnerability	| Description |
|-|-|
| Operating System | These types of vulnerabilities are found within Operating Systems (OSs) and often result in privilege escalation. |
| (Mis)Configuration-based | These types of vulnerability stem from an incorrectly configured application or service. For example, a website exposing customer details. |
| Weak or Default Credentials | Applications and services that have an element of authentication will come with default credentials when installed. For example, an administrator dashboard may have the username and password of "admin". These are easy to guess by an attacker. |
| Application Logic | These vulnerabilities are a result of poorly designed applications. For example, poorly implemented authentication mechanisms that may result in an attacker being able to impersonate a user. |
| Human-Factor | Human-Factor vulnerabilities are vulnerabilities that leverage human behaviour. For example, phishing emails are designed to trick humans into believing they are legitimate. |

## Scoring Vulnerabilities (CVSS & VPR)
### Common Vulnerability Scoring System
Free and open-source.
| Rating | Score |
|-|-|
| `None` | 0 |
| `Low` |	0.1 - 3.9 |
| `Medium` | 4.0 - 6.9 |
| `High`	 | 7.0 - 8.9 |
| `Critical` | 9.0 - 10.0 |

### Vulnerability Priority Rating
Assess vulnerability based on the risk it poses to an organisation.
| Rating | Score |
|-|-|
| `Low` |	0.0 - 3.9 |
| `Medium` | 4.0 - 6.9 |
| `High`	 | 7.0 - 8.9 |
| `Critical` | 9.0 - 10.0 |

## Vulnerability databases
1. [NVD (National Vulnerability Database)](https://nvd.nist.gov/vuln)
1. [Exploit-DB](https://www.exploit-db.com/)

## Scanning for vulns
- Automated: use a scanner like `nessus`.
- Manual: use a database like `Exploit DB`, `Rapid7`, `NVD` or a tool like: `Msfconsole`, `GitHub`, `Searchsploit`.
