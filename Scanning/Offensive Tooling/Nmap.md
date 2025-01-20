# Nmap
## Subnetting
| Term | Definition |
|-|-|
| network segment | This refers tp a physical connection, a group of computers connected using a shared medium like a Ethernet switch or WiFi access point. |
| subnet(work) | This refers to a logical connection, equivalent of one or more network segments connected together and configured to use the same router. |

## Enumerating Targets
If you want to check the list of hosts that Nmap will scan, you can use `nmap -sL TARGETS`.


## Summary
| Purpose |	Example Command |
|-|-|
| **Host discovery** | - |
| Discover live hosts without port scanning | `sudo nmap -sn MACHINE_IP/24` |
| ARP Scan | `sudo nmap -PR -sn MACHINE_IP/24` |
| ICMP Echo Scan | `sudo nmap -PE -sn MACHINE_IP/24` |
| ICMP Timestamp Scan | `sudo nmap -PP -sn MACHINE_IP/24` |
| ICMP Address Mask Scan | `sudo nmap -PM -sn MACHINE_IP/24` |
| TCP SYN Ping Scan | `sudo nmap -PS22,80,443 -sn MACHINE_IP/30` |
| TCP ACK Ping Scan | `sudo nmap -PA22,80,443 -sn MACHINE_IP/30` |
| UDP Ping Scan | `sudo nmap -PU53,161,162 -sn MACHINE_IP/30` |
| **DNS discovery** | - |
| Skip reverse-dns lookup | `sudo nmap -n MACHINE_IP/24` |
| DNS offline host discovery | `sudo nmap -R MACHINE_IP/24` |
| Specify DNS server | `sudo nmap --dns-servers DNS_SERVER MACHINE_IP/24` |
| **Basic port scans** | - |
| TCP connect scan | `sudo nmap -sT MACHINE_IP` |
| TCP SYN scan | `sudo nmap -sS MACHINE_IP` |
| UDP scan | `sudo nmap -sU MACHINE_IP` |
| **Advanced port scans** | - |
| TCP Null scan | `sudo nmap -sN MACHINE_IP` |
| TCP FIN scan | `sudo nmap -sF MACHINE_IP` |
| TCP Xmas scan | `sudo nmap -sX MACHINE_IP` |
| TCP Maimon scan | `sudo nmap -sM MACHINE_IP` |
| TCP ACK scan | `sudo nmap -sA MACHINE_IP` |
| TCP Window scan | `sudo nmap -sW MACHINE_IP` |
| Custom scan | `--scanflags FLAGS` |
| **Spoofing and decoys** | - |
| Basic spoofing | `nmap -S SPOOFED_IP MACHINE_IP` |
| Spoofing specifying the interface | `nmap -e NET_INTERFACE -Pn -S SPOOFED_IP MACHINE_IP` |
| Spoof mac | `--spoof-mac SPOOFED_MAC` |
| Decoy | `nmap -D DECOY1_IP,DECOY2_IP,ME MACHINE_IP` where `ME` indicates that your IP address should appear in the third order. |
| Random decoys | `nmap -D 10.10.0.1,10.10.0.2,RND,RND,ME MACHINE_IP` where the third and fourth source IP addresses are assigned randomly. |
| Idle/Zombie scan | `nmap -sI ZOMBIE_IP MACHINE_IP`, where `ZOMBIE_IP` is the IP address of the idle host (zombie). |
| **Packet fragments** | - |
| Fragment packets | Add `-f` or `-ff` for further fragmentation. |
| Increase packet size | `--data-length NUM` |
| Change the default fragment size value | Use `--mtu`. |
| **Post port scanning** | - |
| Service and version | `nmap -sV MACHINE_IP` |
| Control detection intensity | `--version-intensity LEVEL` where levels are between 0 and 9. |
| Higest intensity detection | `-sV --version-all` |
| OS detection | `nmap -O MACHINE_IP` |
| Traceroute | `nmap --traceroute MACHINE_IP` |
| Run default scripts | `nmap --script=default MACHINE_IP` or `nmap -sC MACHINE_IP` or `nmap --script "SCRIPT-NAME" MACHINE_IP`|
| All | `-A`, equivalent to `-sV -O -sC --traceroute` |
| **Saving output** | - |
| Normal format | `-oN FILENAME` |
| Grepable format | `-oG FILENAME` |
| XML format | `-oX FILENAME` |
| Use all formats | `-oA FILENAME` |
| Script kiddie | `-oS FILENAME` |
| **Misc** | - |
| Enable fast mode | `sudo nmap -F MACHINE_IP` |
| Scan ports in consecutive order | `sudo nmap -r MACHINE_IP` |
| Specify ports | `sudo nmap -p22,80,443 MACHINE_IP` |
| Port range | `sudo nmap -p22-443 MACHINE_IP` |
| All ports | `sudo nmap -p- MACHINE_IP` |
| Scan timing | `-T<0-5>` where 0=paranoid, 1=sneaky, 2=polite, 3=normal, 4=aggressive, 5=insane |
| Control packet rate | `--min-rate <number>` & `--max-rate <number>` = packets/second |
| Control probing parallelization | `--min-parallelism <numprobes>` & `--max-parallelism <numprobes>` = Nmap probes the targets to discover which hosts are live and which ports are open; probing parallelization specifies the number of such probes that can be run in parallel. |
| Specify the network interface | `-e NET_INTERFACE` |
| Specify source port number | `--source-port PORT_NUM` |
| Let Nmap provide more detailed reasoning | `--reason` |
| Let Nmap provide more detailed output | Use `-v` or `-vv` for even more verbosity. |
| Denugging | `-d` |
| More details for debugging | `-dd` |


## The process of network mapping
1. Enumerate targets
2. Discover live hosts
3. Reverse-DNS lookup
4. Scan ports
5. Detect versions
6. Detect OS
7. Traceroute
8. Scripts
9. Write output / logging

## Nmap TCP and UDP port states
| Port state | Description |
|-|-|
| Open | Service is `actively listening` for connections on the port. |
| Closed | `No service listening`, `port is accessible` / reachable but a firewall or other security appliances might be blocking the packets. |
| Filtered | Nmap cannot determine if the port is `open or closed`. The `port is not accessible`. Usually due to a firewall preventing nmap. |
| Unfiltered | Nmap cannot determine if the port is `open or closed`. The `port is accessible`. Encountered when `TCP ACK` scanning. |
| Open/Filtered | Nmap cannot determine if the port is `open or filtered`. |
| Closed/Filtered | Nmap cannot determine if the port is `closed or filtered`. |

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

## Basic Port Scanning
### TCP flags
![TCP Header RFC793](https://tryhackme-images.s3.amazonaws.com/user-uploads/5f04259cf9bf5b57aed2c476/room-content/79ca8e4acbd573a27cee413cde927769.png)

Setting a flag bit means setting its value to 1. From left to right, the TCP header flags are:
1. URG: Urgent flag indicates that the urgent pointer filed is significant.  a TCP segment with the URG flag set is processed immediately without consideration of having to wait on previously sent TCP segments.
2. ACK: Used to acknowledge the receipt of a TCP segment.
3. PSH: Asking TCP to pass the data to the application promptly.
4. RST: Used to reset the connection. Also used when data is sent to a host and there is no service on the receiving end to answer.
5. SYN: Used to initiate a TCP 3-way handshake and synchronize sequence numbers with the other host. The sequence number should be set randomly during TCP connection establishment.
6. FIN: The sender has no more data to send.

### TCP connect scan
Similar to a TCP 3-way handshake BUT we are interested in learning whether the TCP port is open, not establishing a TCP connection. Hence the connection is torn as soon as its state is confirmed by sending a RST/ACK.
![TCP connect scan](https://tryhackme-images.s3.amazonaws.com/user-uploads/5f04259cf9bf5b57aed2c476/room-content/514972cd54b3f58c83f951978ea9183e.png)

### TCP SYN scan
Unprivileged users are limited to connect scan. However, the default scan mode is SYN scan, and it requires a privileged (root or sudoer) user to run it.

SYN scan does not need to complete the TCP 3-way handshake; instead, it tears down the connection once it receives a response from the server.

![TCP SYN scan](https://tryhackme-images.s3.amazonaws.com/user-uploads/5f04259cf9bf5b57aed2c476/room-content/48e631fd3deba4a2b759ca48405fcc08.png)

### UDP scan
UDP is a connectionless protocol, and hence it does not require any handshake for connection establishment. We cannot guarantee that a service listening on a UDP port would respond to our packets.

However, if a UDP packet is sent to a closed port, an ICMP port unreachable error (type 3, code 3) is returned.

![UDP scan, port closed](https://tryhackme-images.s3.amazonaws.com/user-uploads/5f04259cf9bf5b57aed2c476/room-content/8b8b32517699b96777641a97dbf9d880.png)

## Advanced port scans
Security researchers and hackers wanted to know what would happen if we send a TCP packet, which is not part of any ongoing TCP connection, with `one or more flags set`.

### TCP Null scan
The null scan does not set any flag; all six flag bits are set to zero.

A TCP packet with no flags set will not trigger any response when it reaches an open port. However, we expect the target server to respond with an RST packet if the port is closed.

Because the null scan relies on the lack of a response to infer that the port is not closed, it cannot indicate with certainty that these ports are open; there is a possibility that the ports are not responding due to a firewall rule.

![Null scan](https://tryhackme-images.s3.amazonaws.com/user-uploads/5f04259cf9bf5b57aed2c476/room-content/224e01a913a1ce7b0fb2b9290ff5e1c8.png)

### TCP FIN scan
The FIN scan sends a TCP packet with the FIN flag set. No response will be sent if the TCP port is open. The target system should respond with an RST if the port is closed.

Again, Nmap cannot be sure if the port is open or if a firewall is blocking the traffic related to this TCP port. It's worth noting some firewalls will 'silently' drop the traffic without sending an RST.

![FIN scan](https://tryhackme-images.s3.amazonaws.com/user-uploads/5f04259cf9bf5b57aed2c476/room-content/74dc07da7351a5a7f258948ec59efccc.png)

### TCP Xmas scan
 An Xmas scan sets the `FIN, PSH, and URG flags` simultaneously.

Like the Null scan and FIN scan, if an RST packet is received, it means that the port is closed. Otherwise, it will be reported as open|filtered.

![Xmas scan](https://tryhackme-images.s3.amazonaws.com/user-uploads/5f04259cf9bf5b57aed2c476/room-content/4304eacbc3db1af21657f285bc16ebce.png)

### TCP Maimon scan
The FIN and ACK bits are set. The target should send an RST packet as a response. However, `certain BSD-derived systems drop the packet if it is an open port` exposing the open ports.

This scan won’t work on most targets encountered in modern networks. Most target systems respond with an RST packet regardless of whether the TCP port is open.

![Maimon scan](https://tryhackme-images.s3.amazonaws.com/user-uploads/5f04259cf9bf5b57aed2c476/room-content/8ca5e5e0f6e0a1843cebe11b5b0785b3.png)

### TCP ACK scan
Not to be confused with the TCP ping ACK scan. An ACK scan will send a TCP packet with the ACK flag set. The target would respond to the ACK with RST regardless of the state of the port.

The TCP packet with the ACK flag set should be sent only in response to a received TCP packet to acknowledge the receipt of some data.  Hence, this scan won’t tell us whether the target port is open in a simple setup.

Based on which ACK packets resulted in responses, you will learn which ports were not blocked by the firewall. In other words, this type of scan is more `suitable to discover firewall rule sets and configuration`.

![TCP ACK scan](https://tryhackme-images.s3.amazonaws.com/user-uploads/5f04259cf9bf5b57aed2c476/room-content/a991831cedbb2761dde1fe66012a7311.png)

### TCP Window scan
Almost the same as the ACK scan; it examines the `TCP Window field of the RST packets` returned.

`On specific systems, this can reveal that the port is open`. We expect to get an RST packet in reply to our “uninvited” ACK packets, regardless of whether the port is open or closed.

If we repeat our TCP window scan against a server behind a firewall, we expect to get more satisfying results. The ports that responded differently, indicate that the firewall does not block them.

### Spoofing
In some network setups, you will be able to scan a target system using a spoofed IP address and even a spoofed MAC address. This is only beneficial in a situation where you can guarantee to capture the response. If you try to scan a target from some random network using a spoofed IP address, `chances are you won’t have any response routed to you`, and the scan results could be unreliable.

![spoofed scanning](https://tryhackme-images.s3.amazonaws.com/user-uploads/5f04259cf9bf5b57aed2c476/room-content/45b982d501fd26deb2b381059b16f80c.png)

In general, you expect to specify the network interface using `-e` and to explicitly disable ping scan `-Pn`. Therefore, instead of `nmap -S SPOOFED_IP MACHINE_IP`, you will need to issue `nmap -e NET_INTERFACE -Pn -S SPOOFED_IP MACHINE_IP` to tell Nmap explicitly which network interface to use and not to expect to receive a ping reply.

When you are on the same subnet as the target machine, you would be able to spoof your MAC address as well. You can specify the source MAC address using `--spoof-mac SPOOFED_MAC`.

### Decoys
Spoofing only works in a minimal number of cases where certain conditions are met. Therefore, the attacker might resort to using decoys to make it more challenging to be pinpointed. The concept is simple, `make the scan appear to be coming from many IP addresses so that the attacker’s IP address would be lost among them`.

 The scan of the target machine will appear to be coming from 3 different sources, and consequently, the `replies will go the decoys as well`.

![Decoy scanning](https://tryhackme-images.s3.amazonaws.com/user-uploads/5f04259cf9bf5b57aed2c476/room-content/754fc455556a424ca83f512665beaf7d.png)

### Fragmented packets
Nmap provides the option `-f` to fragment packets. Once chosen, the IP data will be `divided into 8 bytes or less`. Adding another -f (`-f -f` or `-ff`) `will split the data into 16 byte-fragments` instead of 8. You can change the default value by using `--mtu`. However, you should always choose a multiple of 8 bytes.

In other words, the 24 bytes of the TCP header, in this case, would be divided over two IP fragments, the first containing 16 bytes and the second containing 8 bytes of the TCP header.

The data that we will fragment across multiple packets is highlighted in red. To aid in the reassembly on the recipient side, IP uses the identification (ID) and fragment offset, shown on the second row of the figure below.

On the other hand, if you prefer to increase the size of your packets to make them look innocuous, you can use the option `--data-length NUM`, where num specifies the number of bytes you want to append to your packets.

![IP Header fragment](https://tryhackme-images.s3.amazonaws.com/user-uploads/5f04259cf9bf5b57aed2c476/room-content/5e55834e2638ba7ec9e84a0900b68ccb.png)

### Idle/Zombie Scan
Spoofing will only work in specific network setups. It requires you to be in a position where you can monitor the traffic. Considering these limitations, spoofing your IP address can have little use; however, we can give it an upgrade with the idle scan.

The idle scan, or zombie scan, `requires an idle system connected to the network that you can communicate with`. Nmap will make `each probe appear as if coming from the idle (zombie) host`, then it will `check for indicators whether the idle (zombie) host received any response` to the spoofed probe.

This is accomplished by checking the IP identification (IP ID) value in the IP header. The idle (zombie) scan requires the following three steps to discover whether a port is open:

1. Trigger the idle host to respond so that you can record the current IP ID on the idle host.
2. Send a SYN packet to a TCP port on the target. The packet should be spoofed to appear as if it was coming from the idle host (zombie) IP address.
3. Trigger the idle machine again to respond so that you can compare the new IP ID with the one received earlier.

![Finding idle IP ID](https://tryhackme-images.s3.amazonaws.com/user-uploads/5f04259cf9bf5b57aed2c476/room-content/a93e181f0effe000554a8b307448bbb2.png)

![Spoofed IP ID scan](https://tryhackme-images.s3.amazonaws.com/user-uploads/5f04259cf9bf5b57aed2c476/room-content/2b0de492e2154a30760852e07cebae0e.png)

## Nmap Post port scans
### Service detection
Once you discover open ports, you can probe the available port to detect the running service.
`-sV` will force Nmap to proceed with the TCP 3-way handshake and establish the connection in order to discover versions, etc.

### OS detection
Nmap can detect the Operating System (OS) based on its behaviour and any telltale signs in its responses.

### Traceroute
Traceroute finds the routers between you and the target. Note that Nmap’s traceroute works slightly different than the `traceroute` command found on Linux and macOS or `tracert` found on MS Windows.

 Standard traceroute starts with a packet of low TTL (Time to Live) and keeps increasing until it reaches the target. Remember, TTL refers to the `amount of time or “hops” that a packet is set to exist` inside a network before being discarded by a router.

### Nmap scripting engine
Scripts make it possible to add custom functionality that do not exist via the built-in commands. Nmap provides support for scripts using the `Lua` language. `Nmap Scripting Engine (NSE) is a Lua interpreter` that allows Nmap to execute Nmap scripts written in Lua language.

However, we don’t need to learn Lua to make use of Nmap scripts. Your Nmap default installation can easily contain close to 600 scripts.

You can specify to use any or a group of these installed scripts; moreover, you can install other user’s scripts and use them for your scans. Let’s begin with the default scripts. You can choose to run the scripts in the default category using `--script=default` or simply adding `-sC`.

In addition to default, categories include:
- auth
- broadcast
- brute
- default
- discovery
- dos
- exploit
- external
- fuzzer
- intrusive
- malware
- safe
- version
- vuln

### Saving the scan results
Whenever you run a Nmap scan, it is only reasonable to save the results in a file. 

The three main formats are:
1. **Normal format:** similar to the output you get on the screen when scanning a target.
2. **Grepable format:** makes filtering the scan output for specific keywords or terms efficient.
3. **XML format:** most convenient to process the output in other programs.

There is a fourth one that we **cannot recommend**: Script Kiddie.