# Nmap
## Subnetting
| Term | Definition |
|-|-|
| network segment | This refers tp a physical connection, a group of computers connected using a shared medium like a Ethernet switch or WiFi access point. |
| subnet(work) | This refers to a logical connection, equivalent of one or more network segments connected together and configured to use the same router. |

## Enumerating Targets
If you want to check the list of hosts that Nmap will scan, you can use `nmap -sL TARGETS`.


## Summary
| Scan Type |	Example Command |
|-|-|
| Skip reverse-dns lookup | `sudo nmap -n MACHINE_IP/24` |
| Discover live hosts without port scanning | `sudo nmap -sn MACHINE_IP/24` |
| ARP Scan | `sudo nmap -PR -sn MACHINE_IP/24` |
| ICMP Echo Scan | `sudo nmap -PE -sn MACHINE_IP/24` |
| ICMP Timestamp Scan | `sudo nmap -PP -sn MACHINE_IP/24` |
| ICMP Address Mask Scan | `sudo nmap -PM -sn MACHINE_IP/24` |
| TCP SYN Ping Scan | `sudo nmap -PS22,80,443 -sn MACHINE_IP/30` |
| TCP ACK Ping Scan | `sudo nmap -PA22,80,443 -sn MACHINE_IP/30` |
| UDP Ping Scan | `sudo nmap -PU53,161,162 -sn MACHINE_IP/30` |

## Live Host Discovery
### Protocols
| Protocol | Description | Packet example |
|-|-|-|
| ARP | Sends a frame to the **broadcast** address on the network segment `asking who has the MAC-address of a certain IP-address`. Subsequently storing the MAC in it's routing table. | `Who has 10.10.210.1? Tell 10.10.210.6` |
| ICMP | ICMP has many types. ICMP ping uses Type 8 (Echo) and Type 0 (Echo Reply). | `[Echo (ping) request or Timespamp request] id=0x22e1, seq=0/0, ttl=...` |
| TCP | Send a specially-crafted packet to common TCP ports to check whether the target will respond. This method is efficient, especially when ICMP Echo is blocked. | `[PortNumber: 80] [SYN or ACK] Seq=1 Win=1024 Len=0 MSS=1460...` |
| UDP | Send a specially-crafted packet to common UDP ports to check whether the target will respond. This method is efficient, especially when ICMP Echo is blocked. | For live hosts we will only see `UDP traffic`. If a host is down we will also see `ICMP(type 3) traffic`. |

`Nmap, by default, uses a ping scan to find live hosts`, then proceeds to scan live hosts only.
To be able to use different protocols we need priviledged or `sudo` access to nmap, otherwise nmap will default back to `TCP` scanning.
If you want to use Nmap to discover online hosts without port-scanning the live systems, you can issue `nmap -sn TARGETS`.

### ARP scanning
Inside of a `subnet` we can use `ARP` requests to see if a host is online. Remember, an ARP query `aims to get the hardware` address (MAC address) so that communication over the link-layer becomes possible. `ARP queries won’t be routed` and hence **cannot cross the subnet router**. ARP is a link-layer protocol, and ARP **packets are bound to their subnet**.

Basically, a host that replies to ARP queries is up. If you want Nmap only to perform an ARP scan without port-scanning, you can use `nmap -PR -sn TARGETS`, where `-PR` indicates that you only want an ARP scan.

![Arp scan](https://tryhackme-images.s3.amazonaws.com/user-uploads/5f04259cf9bf5b57aed2c476/room-content/f0ce4cd34b827f529255c5c73bb909d1.png)

Talking about ARP scans, we should mention a scanner built around ARP queries: `arp-scan`; it provides many options to customize your scan. Visit the arp-scan wiki for detailed information. One popular choice is `arp-scan --localnet` or simply `arp-scan -l`.  You can also specify the interface using `-I`. For instance, `sudo arp-scan -I eth0 -l` will send ARP queries for all valid IP addresses on the eth0 interface.

### ICMP scanning
ICMP (Internet Control Message Protocol) is a network protocol used for diagnostic and error-reporting purposes. Think of it as a way for devices on a network to exchange quick "status updates" or ask basic questions to help maintain communication.

An `ICMP echo scan` works by sending an ICMP echo request (`ICMP Type 8/Echo`) and expects the target to reply with an ICMP echo (`ICMP Type 0/Echo`) reply if it is online. Many firewalls block ICMP echo; new versions of MS Windows are configured with a host firewall that blocks ICMP echo requests by default.

To use ICMP echo request to discover live hosts, add the option `-PE`. 

![ICMP scan](https://tryhackme-images.s3.amazonaws.com/user-uploads/5f04259cf9bf5b57aed2c476/room-content/25fb5fd5d2009cf69d7aae40e8fde2ec.png)

Because ICMP echo requests tend to be blocked, you might also consider `ICMP Timestamp` or `ICMP Address Mask requests` to tell if a system is online. Nmap uses timestamp request (`ICMP Type 13`) and checks whether it will get a Timestamp reply (`ICMP Type 14`). Adding the `-PP` option tells Nmap to use ICMP timestamp requests.

![ICMP timestamp scan](https://tryhackme-images.s3.amazonaws.com/user-uploads/5f04259cf9bf5b57aed2c476/room-content/06443faaa41a349ff46732d60e2e3bcd.png)

Similarly, Nmap uses address mask queries (`ICMP Type 17`) and checks whether it gets an address mask reply (`ICMP Type 18`). This scan can be enabled with the option `-PM`.

![ICMP address mask scan](https://tryhackme-images.s3.amazonaws.com/user-uploads/5f04259cf9bf5b57aed2c476/room-content/14c31c66e002e2f50b0f8525c8d8e456.png)

### TCP scanning
#### SYN
We can send a packet with the `SYN (Synchronize)` flag set to a TCP port, 80 by default, and wait for a response. An open port should reply with a `SYN/ACK (Acknowledge)`; a closed port would result in an `RST (Reset)`. In this case, **we only check whether we will get any response to infer whether the host is up**, the specific state of the port is not significant here.

![TCP 3-way handshake / SYN scan](https://tryhackme-images.s3.amazonaws.com/user-uploads/5f04259cf9bf5b57aed2c476/room-content/168d48701c5f872cf1930e08b32bcd6f.png)

If you want Nmap to use TCP SYN ping, you can do so via the option `-PS` followed by the port number, range, list, or a combination of them. For example, `-PS21` will target port 21, while `-PS21-25` will target ports 21, 22, 23, 24, and 25. Finally `-PS80,443,8080` will target the three ports 80, 443, and 8080.

Privileged users (root and sudoers) can send TCP SYN packets and `don’t need to complete the TCP 3-way handshake` even if the port is open. Unprivileged users `have no choice but to complete the 3-way handshake` if the port is open.

#### ACK
This sends a packet with the ACK flag set. You `must be running Nmap as a privileged user` to be able to accomplish this. If you try it as an unprivileged user, Nmap will attempt a 3-way handshake.

By default, port 80 is used. The syntax is similar to TCP SYN ping. `-PA` should be followed by a port number, range, list, or a combination of them. For example, consider `-PA21`, `-PA21-25` and `-PA80,443,8080`. If no port is specified, port 80 will be used.

 Any TCP packet with an ACK flag `should get a TCP packet back with an RST flag set`. The target responds with the RST flag set because the TCP packet with the ACK flag is not part of any ongoing connection. The expected response is used to detect if the target host is up. The systems that don’t respond are offline or inaccessible.

 ![ACK scan](https://tryhackme-images.s3.amazonaws.com/user-uploads/5f04259cf9bf5b57aed2c476/room-content/db5ab44a8c700c4ab0603e85e456040d.png)

 ### UDP scanning
Contrary to TCP SYN ping, sending a UDP packet to an open port is not expected to lead to any reply. However, if we send a `UDP packet to a closed` UDP port, we `expect to get an ICMP port unreachable packet`.

![UDP scanning](https://tryhackme-images.s3.amazonaws.com/user-uploads/5f04259cf9bf5b57aed2c476/room-content/c8b2d403667487322058619e561186d2.png)

The syntax to specify the ports is similar to that of TCP SYN ping and TCP ACK ping; Nmap uses `-PU` for UDP ping.

## Basic Port Scans
