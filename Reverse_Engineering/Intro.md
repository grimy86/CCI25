# Intro to (Malware) Analysis
Notice how malware is in brackets, this is because analysis of other software in order to reverse it later on happens the same way.

E.g: A game cheat could also be classified as `malware`. In order to write the code for the anti-cheat we'd have to do some analysis on the cheat as well.

>[!IMPORTANT]
>Don't perform malware analysis on a live machine not purpose-built for malware analysis.

## Malware analysis
The word malware is derived from the term `MALicious softWARE`. Therefore, any software that has a malicious purpose can be considered malware. Malware is further classified into different categories based on its behavior. 

Here we will ponder the steps we will take if we suspect that we found malware in a machine.

### The purpose behind Malware Analysis
- `Security Operations` teams analyze malware to write detections for malicious activity in their networks.
- `Incident Response` teams analyze malware to determine what damage has been done to an environment to remediate and revert that damage.
- `Threat Hunt` teams analyze malware to identify IOCs, which they use to hunt for malware in a network.
- `Malware Researchers` in security product vendor teams analyze malware to add detections for them in their security products.
- `Threat Research` teams in OS Vendors like Microsoft and Google analyze malware to discover the vulnerabilities exploited and add more security features to the OS/applications.

### Safety first!
Please note that malware is like a weapon because it `can produce great harm if not handled with care`. For this reason, always take the following precautions while analyzing malware:

- Never analyze malware or suspected malware on a machine that does not have the `sole purpose of analyzing malware`.
- When not analyzing or moving malware samples around to different locations, always `keep them in password-protected zip/rar or other archives so that we can avoid accidental detonation`.
- Only extract the malware from this password-protected archive inside the `isolated environment`, and `only when analyzing` it.
- `Create an isolated VM` specifically for malware analysis, which has the `capability of being reverted to a clean slate` once you are done.
- Ensure that all `internet connections are closed` or at least monitored.
- Once you are done with malware analysis, `revert the VM to its clean slate for the next malware analysis session` to avoid residue from a previous malware execution corrupting the next one.

## Techniques of malware analysis
Malware Analysis is like solving a puzzle. Different tools and techniques are used to find the pieces of this puzzle.

Most of the time, you will have an executable file (also called a binary or a PE file. PE stands for Portable Executable), a malicious document file, or a Network Packet Capture (Pcap). 

The Portable Executable is the most prevalent type of file analyzed while performing Malware Analysis.

To find the different puzzle pieces, you will often use various tools, tricks, and shortcuts. These techniques can be grouped into the following two categories:
- Static Analysis
- Dynamic Analysis

### Static Analysis
When malware is analyzed `without being executed`, it is called Static Analysis.

In this case, the different properties of the `PE file` are analyzed without running it. Similarly, in the case of a `malicious document`, exploring the document's properties without analyzing it will be considered Static Analysis.

Examples of static analysis include:
- Checking for `strings` in malware
- Checking the `PE header` for information related to different `sections`
- Looking at the code using a `disassembler`. 

Malware `often uses techniques to avoid static analysis`:
- `obfuscation`
- `packing`
- `other means of hiding its properties`

To circumvent these techniques, we often use `dynamic analysis`.

### Dynamic Analysis
Malware faces a dilemma. It has to execute to fulfil its purpose, and no matter how much obfuscation is added to the code, it becomes an easy target for detection once it runs.

Sometimes we might need to run the malware in a controlled environment to observe what it does in these cases.

Dynamic analysis techniques include:
- Running the malware in a VM
  - In a `manual` fashion with tools installed to monitor the malware's activity
  - In the form of sandboxes that perform this task `automatically`.

Once we run the malware in a controlled environment, we can use our knowledge from the `Windows Forensics` rooms to `identify what it did in our environment`.

The advantage here is that since we control the environment, we can configure it to avoid noise, like activity from a legitimate user or Windows Services. Thus, everything we observe in such an environment points to malware activity, making it easier to identify what the malware did in this scenario.

>[!NOTE]
> This is specific to malware reversal, Windows forensics and the Windows environment. 
> 
> However let's say you're reversing / analyzing a "safe" program then don't mind this part above.

Malware, however, often uses techniques to prevent an analyst from performing dynamic analysis. Since most dynamic analysis is performed in a controlled environment.

Most methods to bypass dynamic analysis include `detecting the environment` in which it is being run. Therefore, in these cases, the `malware uses a different, benign code path if it identifies that it is being run in a controlled environment`.

## Basic static analysis
When analyzing a new piece of malware, the first step is usually performing basic static analysis. Basic static analysis can be considered sizing up the malware, trying to find its properties before diving deep into analysis. It provides us with an overview of what we are dealing with. Sometimes it might give us some critical information, for example, what API calls the malware is making or whether it's packed or not. However, other times, it might only give us information to help us size the malware up and give us an idea of the effort required to analyze it.

So without further ado, let's see some of the techniques we can use to perform basic static analysis.

We will be using the attached Remnux VM. `Remnux` (`Reverse Engineering Malware Linux`) is a Linux distribution purpose-built for malware analysis. It has many tools required for malware analysis already installed on it.

### Examining the file type
Though often the file type of malware is visible in the file extension and is obvious, sometimes malware authors try to trick users by using `misleading file extensions`.


### Examining Strings
Another really important command that provides us with useful information about a file is the `strings` command. This command lists down the strings present in a file.

Looking at strings in a file can often give `clues related to the behavior` of malware. 

E.g: `URLDownloadToFile` in the output of the strings command will mean that this malware is doing something with the URLDownloadToFile `Windows API`. Most likely, it is `downloading a file from the internet and saving it on the disk`.

Similarly, strings might also provide `contextual information` that helps us later during malware analysis.

### Calculating Hashes
File Hashing provides us with a fixed-size unique number that identifies a file. A File Hash can therefore be considered a unique identifier for a file.

This identifier can be shared with other analysts or searched online for information sharing purposes.

Please note that a single bit of difference in two files will result in different hashes, so changing the hash of a file is as simple as changing one bit in it.

Commonly, `md5sum`, `sha1sum` and `sha256sum` hashes are used for file hashing.

### AV scans and VirusTotal
Scanning a file using AVs or searching for a hash on VirusTotal can also provide useful information about the classification of malware performed by security researchers. However, when using an online scanner, it is recommended to `search for the malware's hash instead of uploading` online to avoid leaking sensitive information online. 

Only upload a sample if you are sure of what you are doing.

### PE Header
The PE File Header contains the metadata about a Portable Executable file. This data can help us find a lot of helpful information to help us in our analysis.

However, some of the vital information found in the PE header is explained below:
- Imports/Exports
- Sections
- Analyzing other PE header info

## Basic dynamic analysis
Many of the properties of a malware sample can be hidden when it's not running. However, when we perform dynamic analysis, we can lay these properties bare and learn more about the behavior of a malware sample.

>[!IMPORTANT]
> Dynamic analysis requires running live malware samples that can be destructive. It is highly recommended that you perform malware analysis in an isolated Virtual Machine. 
> 
> You can create a clean snapshot of your Virtual Machine before performing any malware analysis and revert it to start from a clean state again after every analysis. 
> 
> Don't perform malware analysis on a live machine not purpose-built for malware analysis.

## Introduction to Sandboxes
Sandbox is a term borrowed from the military. A sandbox is a box of sand, as the name suggests, modeling the terrain where an operation has to take place, in which a military team dry runs their scenarios to identify possible outcomes.

 In malware analysis, a sandbox is an isolated environment mimicking the actual target environment of a malware, where an analyst runs a sample to learn more about it. `Malware analysis sandboxes heavily rely on Virtual Machines`, their ability to take snapshots and revert to a clean state when required.

### Open-Source sandboxes
Though it is good to understand what a good sandbox is made of, building a sandbox from scratch is not always necessary. One can always set up Open Source Sandboxes. These sandboxes provide the framework for performing basic dynamic analysis and are also customizable to a significant extent to help those with a more adventurous mindset.

- [Cuckoo's sandbox](https://github.com/cuckoosandbox/cuckoo)
- [CAPE sandbox](https://github.com/kevoreilly/CAPEv2)
- Online sandboxes
  - [Online Cuckoo sandbox](https://cuckoo.cert.ee/)
  - [Any.run](https://any.run/)
  - [Intezer](https://analyze.intezer.com/)
  - [Hybrid Analysis](https://hybrid-analysis.com/)

## Anti-analysis techniques
While the security researchers are devising techniques and tools to analyze malware, the malware authors are working on rendering these tools and techniques ineffective. We find a great deal of information if we use the previous techniques.

However, there are ways malware authors can make our life difficult.

### Packing and Obfuscation
Malware authors often use packing and obfuscation to make an analyst's life difficult. A packer obfuscates, compresses, or encrypts the contents of malware. These techniques make it difficult to analyze malware statically. Specifically, a packed malware will not show important information when running a string search against it.

Read [packing and identifying packed executables](/Windows_Internals/PE.md#packing-and-identifying-packed-executables).

### Sandbox evasion
As we learned about previously, we can always run a sample in a sandbox to analyze it. In many cases, that might help us analyze samples that evade our basic static analysis techniques. 

However, malware authors have some tricks up their sleeves that hamper that effort. 

Some of these techniques are as follows:
- `Long sleep calls`: Malware authors know that `sandboxes run for a limited time`. Therefore, they program the malware not to `perform any activity for a long time after execution`. This is often `accomplished through long sleep calls`. The purpose of this technique is to `time out the sandbox`.
- `User activity detection`: Some malware samples will `wait for user activity` before performing malicious activity. The premise of this technique is that `there will be no user in a sandbox`. Therefore there will be no `mouse movement` or `typing on the keyboard`. Advanced malware also detects `patterns in mouse movements that are often used in automated sandboxes`. This technique is designed to `bypass automated sandbox detection`.
- `Footprinting user activity`: Some malware checks for `user files or activity`, like if there are any files in the `MS Office history` or `internet browsing history`. If no or little activity is found, the malware will consider the machine as a sandbox and quit.
- `Detecting VMs`: Sandboxes run on virtual machines. `Virtual machines leave artifacts` that can be identified by malware. For example, some `drivers installed in VMs` being run on VMWare or Virtualbox give away the fact that the machine is a VM. `Malware authors often associate VMs with sandboxes` and would `terminate the malware if a VM is detected`.

The above list is not exhaustive but gives us an idea of what to expect when analyzing malware.