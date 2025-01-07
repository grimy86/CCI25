# Windows
## Windows File Systems
| **File System**  | **Description**                              | **Use Cases**                |
|-------------------|----------------------------------------------|------------------------------|
| **NTFS**          | Supports journaling, encryption, large files | Windows, modern storage      |
| **FAT16/FAT32**   | Older, no journaling/encryption              | USB drives, legacy systems   |
| **HPFS**          | Obsolete, old systems                        | Legacy systems               |

## NTFS Features
| **Feature**            | **Description**                                     |
|------------------------|-----------------------------------------------------|
| **Journaling**         | Repairs after failure using logs                   |
| **Large File Support** | Handles files >4GB                                 |
| **Permissions**        | Granular access control                            |
| **Compression**        | Compress files/folders                             |
| **Encryption (EFS)**   | Encrypts files for security                        |
| **Alternate Data Streams** | Allows hidden data streams (used by malware)    |

## NTFS Permissions
| **Permission**   | **Files**               | **Folders**               |
|------------------|-------------------------|---------------------------|
| **Full Control** | Modify, delete          | Create, delete, manage    |
| **Modify**       | Read, write, delete     | Read, write, delete       |
| **Read & Execute**| Open, execute files     | Execute files in folder   |
| **Read**         | View content            | View content              |
| **Write**        | Modify file             | Create files, folders     |

## Important Windows Security Features
| **Feature**               | **Description**                                 | **Command to Open**                   |
|---------------------------|-------------------------------------------------|---------------------------------------|
| **BitLocker**              | Encrypts system drive for data protection      | `manage-bde -status`                 |
| **TPM**                    | Hardware module for cryptographic security     | `tpm.msc`                            |
| **VSS**                    | Snapshot tool, stores restore points; malware targets it | `vssadmin list shadows`             |
| **UAC**                    | User Account Control, manages permissions      | `secpol.msc` (Local Security Policy)  |
| **Firewall**               | Network protection: Domain, Private, Public    | `wf.msc`                             |

## Key Windows Commands for Pentesting
| **Command**   | **Description**                                      |
|---------------|------------------------------------------------------|
| **hostname**  | Displays system name                                 |
| **whoami**    | Shows the current logged-in user                     |
| **ipconfig**  | Displays IP settings                                 |
| **netstat**   | Shows network stats and active connections           |
| **net**       | Manages network resources                            |

## Windows Security Checklist
| **Protection Area**     | **Description**                                  | **Command to Open**                |
|-------------------------|--------------------------------------------------|------------------------------------|
| **Virus & Threat Protection** | Real-time malware protection, scans for threats | `ms-settings:windowsdefender`     |
| **Firewall**             | Protects against unauthorized network access    | `wf.msc`                          |
| **Device Security**      | Includes TPM, Core Isolation for process protection | `tpm.msc`                        |
| **App & Browser Control** | Protects against malicious apps and phishing   | `ms-settings:privacy`             |

# Active Directory
## Domain Overview
| Topic                         | Description                                                                                       |
|-------------------------------|---------------------------------------------------------------------------------------------------|
| **Small Network Scenario**     | With a small network, manually configuring and providing support works.                         |
| **Growth in Business**         | As business grows, managing individual computers becomes impractical.                            |
| **Windows Domain**             | A centralized network for managing users and computers.                                           |
| **Active Directory (AD)**      | Central repository for managing user/computer info in a domain.                                   |
| **Domain Controller (DC)**     | Server that runs AD services and manages the domain.                                             |
| **Advantages of a Domain**     | 1. Centralized identity management for users. <br> 2. Easier management of security policies.     |
| **Real-World Example**         | School/university networks use domains for authentication and privilege control.                |
| **THM Inc. Role**              | Configuring and managing the domain "THM.local".                                                  |

## Active Directory Domain Service (AD DS)
| Topic                         | Description                                                                                       |
|-------------------------------|---------------------------------------------------------------------------------------------------|
| **Active Directory (AD)**      | Holds information on domain objects (users, groups, machines).                                   |
| **Users**                      | Security principals authenticated by the domain.                                                  |
| **Machines**                   | Machines (computers) with limited rights; follow the `<ComputerName>$` naming scheme.            |
| **Security Groups**            | Groups managing permissions for users and computers (e.g., Domain Admins, Server Operators).     |
| **Active Directory Users and Computers (ADUC)** | Tool to manage users, groups, and machines in OUs.                       |
| **Organizational Units (OUs)** | OUs classify users and machines for role-based policies.                                         |
| **Default Containers**         | Predefined groups/containers like Builtin, Computers, Users, Domain Controllers.                 |
| **Security Groups vs OUs**     | OUs are for policy management, Security Groups for resource access.                              |

## Domain Administration Tasks
| Task                          | Description                                                                                       |
|-------------------------------|---------------------------------------------------------------------------------------------------|
| **Deleting Extra OUs**         | Enable "Advanced Features", uncheck "Protect object from accidental deletion", then delete OU.   |
| **Matching Users to Org Chart**| Check if users align with the organizational chart, create/delete as needed.                     |
| **Delegating Control**         | Delegate control for OUs to specific users (e.g., reset passwords).                               |
| **Delegating OU Control Steps**| 1. Right-click OU, "Delegate Control". <br> 2. Assign control to user (e.g., reset passwords).    |
| **Testing Password Reset**    | Reset passwords via PowerShell: `Set-ADAccountPassword sophie -Reset -NewPassword (Read-Host -AsSecureString -Prompt 'New Password')`. |
| **Force Password Reset**      | `Set-ADUser -ChangePasswordAtLogon $true -Identity sophie` to force reset at next logon.          |
| **RDP Login for Testing**     | After password reset, log in via RDP with new credentials and retrieve flags from desktop.       |

## Segregating Machines in Active Directory
| Task                         | Description                                                                                       |
|------------------------------|---------------------------------------------------------------------------------------------------|
| **Machines in "Computers" OU**| Machines (except Domain Controllers) placed in the "Computers" container by default.               |
| **Device Categories**         | Categories: 1. **Workstations**, 2. **Servers**, 3. **Domain Controllers**                         |
| **Creating New OUs**          | Create "Workstations" and "Servers" OUs under `thm.local`.                                         |
| **Moving Machines**           | Move machines to appropriate OUs for policy application.                                          |

## Group Policy Objects (GPO) Configuration
| **Task**                          | **Description**                                                                                                            |
|------------------------------------|----------------------------------------------------------------------------------------------------------------------------|
| **Group Policy Objects (GPOs)**    | Collections of settings applied to OUs to configure security and system settings.                                           |
| **GPO Scope**                      | GPO can apply to users or computers; linked to OUs and their sub-OUs.                                                        |
| **Editing a GPO**                  | Edit via `Computer Configuration -> Policies -> Windows Settings -> Security Settings -> Account Policies`.                |
| **GPO Distribution**               | GPOs distributed via SYSVOL on Domain Controllers; can take up to 2 hours to propagate. Use `gpupdate /force` to sync immediately. |
| **Restricting Control Panel Access** | GPO: **Prohibit Access to Control Panel** under `User Configuration -> Administrative Templates -> Control Panel`.         |
| **Auto Lock Screen GPO**           | Create GPO under `Computer Configuration -> Policies -> Windows Settings -> Security Settings -> Local Policies -> Security Options -> Interactive Logon: Machine inactivity limit`. |

## Authentication methods
| **Feature**                   | **Kerberos Authentication**                                                                                       | **NetNTLM Authentication**                                                                                       |
|-------------------------------|--------------------------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------|
| **Protocol Type**              | Default, modern protocol for Windows domains.                                                                      | Legacy protocol kept for compatibility.                                                                          |
| **Authentication Mechanism**   | Ticket-based, uses TGT/TGS for services.                                                                            | Challenge-response mechanism.                                                                                     |
| **Primary Purpose**            | Authenticate users, access services without sending credentials repeatedly.                                       | Used in legacy systems.                                                                                           |
| **Key Entity**                 | Key Distribution Center (KDC) on the DC.                                                                            | Domain Controller (DC) for verification of challenges.                                                           |
| **Ticket Issuance**            | TGT for accessing services.                                                                                       | No tickets, challenge-response is used.                                                                          |
| **Security**                   | Encrypted TGTs/TGS, no password hashes over the network.                                                           | Password hashes aren't sent, challenge prevents hash leakage.                                                     |
| **Usage in Modern Systems**    | Common in modern Windows networks.                                                                                 | Obsolete, used for legacy compatibility.                                                                         |
| **Service Access**             | Specific service tickets requested for access.                                                                     | Direct challenge-response validation.                                                                            |
| **Efficiency**                 | Efficient due to single TGT usage for multiple requests.                                                           | Less efficient with repeated challenge-response.                                                                 |
| **Protocols Supported**        | Standard protocol for modern systems, supported widely.                                                             | Legacy support.                                                                                                  |

## Trees, Forests and Trusts
| **Concept**             | **Description**                                                                                         |
|-------------------------|---------------------------------------------------------------------------------------------------------|
| **Single Domain**        | One domain for managing resources like users, computers, and servers.                                    |
| **Trees**                | Multiple domains with the same namespace (e.g., thm.local, uk.thm.local) to improve management.         |
| **Tree Structure**       | Root domain (e.g., thm.local) with subdomains (e.g., uk.thm.local) allowing separate management.        |
| **Forests**              | Union of multiple trees with different namespaces, e.g., merging thm.local and mht.local after an acquisition. |
| **Trust Relationships**  | Allows users in one domain to access resources in another domain, with one-way or two-way trust.        |
| **One-Way Trust**        | Users in Domain BBB can access resources in Domain AAA, but not the other way around.                   |
| **Two-Way Trust**        | Users from both domains can access resources in both domains.                                           |
| **Enterprise Admins**    | Administrative group with control over all domains in the enterprise.                                    |
| **Domain Admins**        | Administrative group with control over a single domain.                                                 |
| **Group Types**          | Security and Distribution groups: Security for access control, Distribution for email distribution.      |
