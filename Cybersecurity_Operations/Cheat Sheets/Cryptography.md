# Cryptography
## Hashing and Password Security
| **Task**                                  | **Description**                                                                 |
|-------------------------------------------|---------------------------------------------------------------------------------|
| **Hash Functions**                        | Functions that convert input into fixed-size output, commonly used for security.|
| **Insecure Password Storage**             | Storing passwords in plaintext or weakly hashed forms, making them vulnerable.  |
| **Secure Password Storage**               | Using strong hashing algorithms like bcrypt, PBKDF2, or Argon2 for passwords.   |
| **Recognizing Password Hashes**           | Identifying hash types like MD5, SHA-1, SHA-256, etc., based on their format.   |
| **Password Cracking**                     | Techniques to retrieve plaintext passwords using tools like Hashcat or John.    |
| **Hashing for Integrity Checking**        | Verifying file integrity with checksums like MD5 or SHA256.                     |

---

## Asymmetric Encryption
| **Task**                                  | **Description**                                                                 |
|-------------------------------------------|---------------------------------------------------------------------------------|
| **Common Use of Asymmetric Encryption**   | Secure communication via key pairs (public/private).                            |
| **RSA**                                   | Widely-used algorithm for encryption and digital signatures.                    |
| **Diffie-Hellman Key Exchange**           | Method for secure key exchange over an insecure channel.                        |
| **SSH**                                   | Protocol for secure remote access using encryption.                             |
| **Digital Signatures and Certificates**   | Validates data authenticity and integrity using private keys and certificates.  |
| **PGP and GPG**                           | Tools for encrypting, signing, and securing emails or files.                    |

## Hashcat
| Command                              | Description                                             | Example                                    |
|--------------------------------------|---------------------------------------------------------|--------------------------------------------|
| `hashcat -m [hash-type] [hashfile]`  | Runs Hashcat to crack hashes using default settings.    | `hashcat -m 1000 hashes.txt`               |
| `hashcat -a 0 -m [hash-type] [hashfile] [wordlist]` | Performs a dictionary attack.                         | `hashcat -a 0 -m 1000 hashes.txt rockyou.txt` |
| `hashcat -a 3 -m [hash-type] [hashfile]` | Performs a brute-force attack.                        | `hashcat -a 3 -m 1000 hashes.txt ?a?a?a?a` |
| `hashcat -a 6 -m [hash-type] [hashfile] [wordlist] ?d?d` | Performs a hybrid attack (dictionary + mask).         | `hashcat -a 6 -m 1000 hashes.txt rockyou.txt ?d?d` |
| `hashcat --show [hashfile]`          | Shows already cracked passwords from the file.         | `hashcat --show hashes.txt`                |
| `hashcat --restore`                  | Resumes a previously paused cracking session.          | `hashcat --restore`                        |
| `hashcat --status`                   | Displays the status of an ongoing session.             | `hashcat --status`                         |
| `hashcat --benchmark`                | Benchmarks Hashcat for supported hash types.           | `hashcat --benchmark`                      |

## Associated Tools
| Command                  | Description                                                    | Example                                     |
|--------------------------|----------------------------------------------------------------|---------------------------------------------|
| `hashid [hash]`          | Identifies the type of a given hash.                          | `hashid -m 1000 hashes.txt`                |
| `hashcat-utils`          | Tools for manipulating wordlists and masks.                   | `splitlen.bin input.txt 5 output.txt`      |
| `hcxtools`               | Tools for handling Wi-Fi handshakes for Hashcat.              | `hcxpcapngtool -o hashes.hccapx capture.pcapng` |

## Common Cracking Workflow
1. **Identify the Hash Type**  
   Use a tool like `hashid` to identify the hash format:  
   ```bash
   hashid -m hashes.txt
2. **Run a Dictionary Attack**  
    Use a wordlist like rockyou.txt for common passwords:
    `hashcat -a 0 -m 1000 hashes.txt rockyou.txt`
3. **Run a Brute-Force Attack**  
    Use a mask for likely patterns (e.g., 4 characters, all printable):
    `hashcat -a 3 -m 1000 hashes.txt ?a?a?a?a`
4. **Hybrid Attack (Wordlist + Mask)**
    Combine a dictionary attack with a mask for flexible cracking:
    `hashcat -a 6 -m 1000 hashes.txt rockyou.txt ?d?d`

5. **Show Cracked Results**
    Display the cracked passwords after a session:
    `hashcat --show hashes.txt`

## John the Ripper
| Command                              | Description                                             | Example                                    |
|--------------------------------------|---------------------------------------------------------|--------------------------------------------|
| `john [file]`                        | Runs John the Ripper to crack hashes.                   | `john hashes.txt`                          |
| `john --wordlist=[file] [hashfile]`  | Cracks hashes using a specified wordlist.               | `john --wordlist=rockyou.txt hashes.txt`   |
| `john --show [file]`                 | Shows cracked passwords from the specified file.        | `john --show hashes.txt`                   |
| `john --format=[format] [file]`      | Specifies the format of the hash for cracking.          | `john --format=NT hashes.txt`              |
| `john --restore`                     | Resumes a previously interrupted cracking session.       | `john --restore`                           |

## Associated Tools
| Command                  | Description                                                    | Example                                     |
|--------------------------|----------------------------------------------------------------|---------------------------------------------|
| `ssh2john [file]`        | Converts an SSH private key file into a hash for cracking.     | `ssh2john id_rsa > id_rsa.hash`             |
| `zip2john [file]`        | Extracts hash from a ZIP file for cracking.                    | `zip2john archive.zip > archive.hash`       |
| `pdf2john [file]`        | Extracts hash from a PDF file for cracking.                    | `pdf2john secure.pdf > secure.hash`         |
| `rar2john [file]`        | Extracts hash from a RAR file for cracking.                    | `rar2john archive.rar > archive.hash`       |
| `keepass2john [file]`    | Extracts hash from a KeePass database file.                    | `keepass2john database.kdbx > database.hash`|

## Common Cracking Workflow
1. **Extract Hashes**  
   Use the appropriate `*2john` tool to generate a hash file for the target format:  
   ```bash
   ssh2john id_rsa > id_rsa.hash
2. **Run John with a Wordlist**
    Use a common wordlist like rockyou.txt to attempt cracking:
    `john --wordlist=rockyou.txt id_rsa.hash`
3. **View Results**
    After the cracking completes, display the cracked passwords:
    `john --show id_rsa.hash`