# Networking
Networks are simply things connected.
For example: "the internet" is one big network of connected computer networks.

## Internet Protocol Addresses (IPv4)
| Tip                                                                                     |
|-----------------------------------------------------------------------------------------|
| Private IP ranges are reserved for internal networks and not routable on the internet.  |
| Public IPs are globally unique and used to communicate over the internet.               |
| Private IP ranges:                                                                     |
|   - Class A: 10.0.0.0 – 10.255.255.255 (Large networks).                                |
|   - Class B: 172.16.0.0 – 172.31.255.255 (Medium networks).                             |
|   - Class C: 192.168.0.0 – 192.168.255.255 (Small networks).                            |
| Loopback addresses: 127.0.0.0/8, typically used to test network configurations locally.  |
| Link-local addresses: 169.254.0.0/16, used when no DHCP server is available.            |
| Public IPs are assigned by ISPs and must be purchased or leased.                        |
| Use CIDR notation (e.g., /24) to define subnets within IP ranges.                       |
| Avoid using overlapping private IP ranges in different subnets to prevent conflicts.    |
| NAT (Network Address Translation) is used to map private IPs to a single public IP.     |
| IPv6 private IP ranges:                                                                |
|   - Unique Local Addresses (ULA): fc00::/7.                                             |
|   - Link-local IPv6: fe80::/10, automatically assigned for local communication.         |
| IPv4 public addresses are becoming scarce; IPv6 adoption is growing to address this.    |
| Always assign static IPs to critical infrastructure like servers and printers.          |
| Use a DHCP server to dynamically assign IPs to devices on your network.                 |
| Check your external IP address using tools like `whatismyip.com` or `ipconfig`/`ifconfig`.|

## Common Protocols
| Protocol    | Layer       | Purpose                                                               |
|-------------|-------------|-----------------------------------------------------------------------|
| HTTP        | Application | Transfers hypertext for websites (web browsing).                      |
| HTTPS       | Application | Secure version of HTTP, encrypts web traffic (TLS/SSL).               |
| FTP         | Application | Transfers files between systems.                                      |
| SFTP        | Application | Secure File Transfer Protocol, encrypts file transfers.               |
| SMTP        | Application | Sends emails between mail servers.                                    |
| IMAP        | Application | Accesses and manages email on mail servers.                           |
| POP3        | Application | Retrieves emails from servers (download and delete).                  |
| DNS         | Application | Resolves domain names to IP addresses.                                |
| DHCP        | Application | Dynamically assigns IP addresses to devices on a network.             |
| SNMP        | Application | Monitors and manages network devices.                                 |
| Telnet      | Application | Provides remote access to devices (unsecured).                        |
| SSH         | Application | Secure remote access and command execution.                           |
| NTP         | Application | Synchronizes system clocks across devices.                            |
| TCP         | Transport   | Ensures reliable data transmission (connection-oriented).             |
| UDP         | Transport   | Transmits data quickly without reliability checks (connectionless).   |
| IP          | Network     | Delivers packets across networks.                                     |
| ICMP        | Network     | Sends error messages and network diagnostics (e.g., ping).            |
| ARP         | Network     | Resolves IP addresses to MAC addresses within a local network.        |
| RARP        | Network     | Resolves MAC addresses to IP addresses.                               |
| BGP         | Network     | Manages routing between autonomous systems on the internet.           |
| OSPF        | Network     | Determines best routes within a single autonomous system.             |
| Ethernet    | Data Link   | Defines wired local area network (LAN) standards.                     |
| Wi-Fi       | Data Link   | Defines wireless local area network (WLAN) standards.                 |
| PPP         | Data Link   | Provides point-to-point connections.                                  |
| VLAN        | Data Link   | Segments networks into virtual LANs.                                  |
| MPLS        | Data Link/Network | Directs data efficiently through complex networks.              |

## Ports & Connectivity
| Tip                                                                                  |
|--------------------------------------------------------------------------------------|
| Ports 0-1023 are "well-known" ports and typically require privileged access to use.  |
| Ports 1024-49151 are "registered" ports, often used by user applications or services.|
| Ports 49152-65535 are "dynamic" or "ephemeral" ports, used temporarily for connections.|
| Port 80 is commonly used for HTTP traffic, ensure it’s open for web servers.         |
| Port 443 is for HTTPS traffic, crucial for secure websites and applications.         |
| Avoid exposing sensitive ports (e.g., 22 for SSH, 3389 for RDP) directly to the internet.|
| Use a firewall to restrict unused or unnecessary ports to enhance security.          |
| Check open ports on a device using tools like `netstat` or `nmap`.                   |
| Block or close unused ports to reduce attack surfaces.                               |
| Use non-default ports for services when possible to deter automated attacks.         |
| Use port forwarding in NAT to map external requests to internal servers.             |
| Test connectivity to a port using `telnet` or tools like `nc` (netcat).              |
| Use port filtering or ACLs to control which devices can access specific ports.       |
| Monitor open ports regularly to detect unauthorized services or changes.             |
| Be aware that some ports (e.g., 53 for DNS) can be exploited for attacks like DDoS.  |
