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