# Static analysis
## Lab Setup
Some famous software used for creating and using Virtual Machines includes [Oracle VirtualBox](https://www.virtualbox.org/) and [VMWare Workstation Pro](https://www.vmware.com/products/desktop-hypervisor/workstation-and-fusion).

Following steps portray the usage of Virtual Machines for malware analysis:

1. Created a fresh Virtual Machine with a new OS install
2. Set up the machine by installing all the required analysis tools in it
3. Take a snapshot of the machine
4. Copy/Download malware samples inside the VM and analyze it
5. Revert the machine to the snapshot after the analysis completes

### FLARE VM
The [`FLARE VM`](https://github.com/mandiant/flare-vm) is a Windows-based VM well-suited for malware analysis created by Mandiant (Previously FireEye).
It contains some of the community's favorite malware analysis tools. Since it is a Windows-based VM, it can perform dynamic analysis of Windows-based malware.

### REMnux:
[`REMnux`](https://github.com/REMnux) stands for Reverse Engineering Malware Linux.
It is a Linux-based malware analysis distribution created by Lenny Zeltser in 2010.

Like the FLARE VM, it includes some of the most popular reverse engineering and malware analysis tools pre-installed.

Being a Linux-based distribution, it cannot be used to perform dynamic analysis of Windows-based malware.

## String search
In the [intro to (Malware) Analysis](/Reverse_Engineering/Intro.md), we identified that searching for strings is one of the first steps in analysis.

### How a string search works:
A string search `looks at the binary data` in a malware sample regardless of its file type and `identifies sequences of ASCII or Unicode characters followed by a null character`. Wherever it finds such a sequence, it reports that as a string. This might raise the question that not all sequences of binary data that looks like ASCII or Unicode characters will be actual strings, which is right. 

Many sequences of bytes can fulfill the criteria mentioned above but are not strings of useful value; rather, they might include memory addresses, assembly instructions, etc. Therefore, a string search leads to `many False Positives (FPs)`. These FPs show up as garbage in the output of our string search and should be ignored. It is up to the analyst to identify the useful strings and ignore the rest.

### What to look for?
Since an analyst has to identify actual strings of interest and differentiate them from the garbage, it is good to know what to look for when performing a string search. Although a lot of useful information can be unearthed in a string search, the following artifacts can be used as `Indicators of Compromise (IOCs)` and prove more useful.

- Information about the possible functionality:
  - Windows `Functions` and `APIs` like:
    - `SetWindowsHook`
    - `CreateProcess`
    - `InternetOpen`
    - `etc`

- Information about possible C2 communication:
  - `IP Addresses`
  - `URLs`
  - `Domains`

- Information that helps set the context for further analysis:
  - `Miscellaneous strings` such as `Bitcoin addresses`
  - `Text used for Message Boxes`
  - `etc`

### Basic String Search
The `strings` utility, which is pre-installed in `Linux machines` can be used for a basic string search.

Similarly, the FLARE VM comes with a Windows utility, `strings.exe`, that performs the same task. This Windows strings utility is `part of the Sysinternals suite`, a set of `tools published by Microsoft to analyze different aspects of a Windows machine`. Details about the strings utility can be found in [Microsoft Documentation](https://learn.microsoft.com/en-us/sysinternals/downloads/strings). 

The good thing about the command line strings utility is that it can `dump strings to a file for further analysis`.

```
C:\Users\Administrator\Desktop>strings <path to binary>
```

Several other tools included in the FLARE VM can be used for string search.

For example:
- `CyberChef` (Desktop>FLARE>Utilities>Cyberchef) has a recipe for basic string search as well.
- `PEstudio` (Desktop>FLARE>Utilities>pestudio) also provides a string search utility.

    PEstudio also provides some additional information about the strings, like, the encoding, size of the string, offset in the binary where the string was found, and a hint to guess what the string is related to. It also has a column for a blacklist, which matches the strings against some signatures.

E.g:
PEstudio shows strings found by PEstudio in a malware sample. This can be done by selecting strings in the left pane after loading the PE file in PEstudio. The blacklist here shows a bunch of Windows API calls, which PEstudio flags as potentially used in malicious processes. You can learn about these APIs using resources like [MalAPI](https://malapi.io/) or MSDN.

### Obfuscated strings
Searching for strings often proves one of the most effective first steps in malware analysis. The malware authors know this and don't want a simple string search to thwart their malicious activities. Therefore, `they deploy techniques to obfuscate strings` in their malware. Malware authors use several techniques to obfuscate the key parts of their code. These techniques often render a string search ineffective, i.e., we won't find much information when we search for strings.

#### FLOSS
Mandiant (then FireEye) launched [`FLOSS`](https://github.com/mandiant/flare-floss) to solve this problem, short for FireEye Labs Obfuscated String Solver. FLOSS uses several techniques to deobfuscate and extract strings that would not be otherwise found using a string search. The type of strings that FLOSS can extract and how it works can be found in [Mandiant's blog post](https://www.mandiant.com/resources/blog/automatically-extracting-obfuscated-strings).

To execute FLOSS, open a command prompt and navigate to the Desktop directory.

```
C:\Users\Administrator\Desktop>floss -h
```

This command will open the `help page for FLOSS`. We can use the following command to use FLOSS to search for obfuscated strings in a binary.

```
C:\Users\Administrator\Desktop>floss --no-static-strings <path to binary>
```

Please remember that the command `might take some time to execute`, and you might see what appear to be some `error messages before the results are generated`.

## Fingerprinting malware
When analyzing malware, it is often required to identify unique malware and `differentiate them from each other`.

File names can't be used for this purpose as they can be duplicated easily and might be confusing. Also, a file name can be changed easily as well. Hence, a hash function is used to identify a malware sample uniquely.

A hash function takes a file/data of arbitrary length as input and creates a fixed-length unique output based on file contents. This process is irreversible, as you can't recreate the file's contents using the hash. `Hash functions have a very low probability (practically zero) of two files having different content but the same hash`. A hash remains the same as long as the file's content remains the same. However, even a slight change (1 bit) in content will result in a different hash. It might be noted that the `file name is not a part of the content`; therefore, changing the file name does not affect the hash of a file.

Besides identifying files, hashes are also used to store passwords to authenticate users. In malware analysis, hash files can be used to identify unique malware, search for this malware in different malware repositories and databases, and as an Indicator of Compromise (IOC).

### Commonly used methods of calculating File hashes
For identification of files, a hash of the complete file is taken. There are various methods to take the hash. The most commonly used methods are:
- Md5sum
- Sha1sum
- Sha256sum

The first two types of hashes are now considered insecure or prone to collision attacks (when two or more inputs result in the same hash). Although a collision attack for these hash functions is not very probable, it is still possible. Therefore, `sha256sum is currently considered the most secure method` of calculating a file hash.

### Finding similar files with hashes
Another scenario in which hash functions help a malware analyst is identifying similar files using hashes. We already established that even a slight change in the contents of a file would result in a different hash.

However, some types of hashes can help identify the similarity among different files:
- `Imphash`:

  The imphash stands for "import hash". Imports are functions that an executable file imports from other files or Dynamically Linked Libraries (DLLs). The imphash is a hash of the function calls/libraries that a malware sample imports and the order in which these libraries are present in the sample. This helps identify samples from the same threat groups or performing similar activities.

  Any malware samples with the same imports in the same order will have the same imphash. This helps in identifying similar samples.

  ![Imphash](/Reverse_Engineering/Images/Imphash.png)

- `Fuzzy hashes/SSDEEP`:

  Another way to identify similar malware is through fuzzy hashes. A fuzzy hash is a `Context Triggered Piecewise Hash (CTPH)`. This hash is calculated by dividing a file into pieces and calculating the hashes of the different pieces. This method creates `multiple inputs with similar sequences of bytes`, even though the whole file might be different.


Multiple utilities can be used to calculate ssdeep, like CyberChef. However after having ssdeep installed you can show the help menu like so:

  ```
  C:\Users\Administrator\Desktop>ssdeep-2.14.1\ssdeep.exe -h
  ```

### Signature-based detection
While using imphash or ssdeep provides a way to identify if some files are similar, sometimes we just need to identify if a file contains the information of interest. Hashes are not the ideal tool to perform this task.

#### Signatures
Signatures are a way to `identify if a particular file has a particular type of content`. We can consider a signature as a pattern that might be found inside a file. This pattern is often a `sequence of bytes` in a file, with or without any context regarding where it is found. Security researchers often use signatures to identify patterns in a file, `identify if a file is malicious, and identify suspected behavior and malware family`.  

#### Yara rules
Yara rules are a type of `signature-based rule`. It is famously called a `pattern-matching swiss army knife for malware researchers`. Yara can identify information based on binary and textual patterns, such as hexadecimal and strings contained within a file.

The security community publishes a [repository of open-source Yara rules](https://github.com/Yara-Rules/rules) that we can use as per our needs. When analyzing malware, we can use this repository to dig into the community's collective wisdom. However, while using these rules, please keep in mind that `some might depend on context`. Some others might just be used for the `identification of patterns that can be non-malicious as well`. Hence, `just because a rule hits doesn't mean the file is malicious`.

#### Proprietary signatures - Anti-virus Scans
Besides the open-source signatures, Antivirus companies spend lots of resources to create proprietary signatures. The advantage of these proprietary signatures is that since they have to be sold commercially, there are lesser chances of False Positives (FPs, when a signature hits a non-malicious file). However, this might lead to a few False Negatives (FNs, when a malicious file does not hit any signature).

Antivirus scanning helps identify if a file is malicious with high confidence. Antivirus software will often mention the signature that the file has hit, which might hint at the file's functionality. However, we must note that despite their best efforts, every AV product in the market has some FPs and some FNs. Therefore, when analyzing malware, it is prudent to get a verdict from multiple products. The Virustotal website makes this task easier for us, where we can find the verdict about a file from 60+ AV vendors, apart from some very useful information. We also touched upon this topic in our Intro to Malware Analysis room. Please remember, if you are analyzing a sensitive file, it is best practice to search for its hash on Virustotal or other scanning websites instead of uploading the file itself. This is done to avoid leaking sensitive information on the internet and letting a sophisticated attacker know that you are analyzing their malware.

Since we have covered Yara rules in detail in the Yara room and Virustotal scanning in the Intro to malware analysis room, we will not cover them again here. However, the FLARE VM has another very cool tool that can be used for signature scanning. 

#### Capa