## OWASP Top 10 Vulnerabilities
| Vulnerability                 | Description                                             | Burp Suite Example                            |
|-------------------------------|---------------------------------------------------------|-----------------------------------------------|
| **A01: Broken Access Control** | Improper enforcement of permissions.                   | Use Burp's **Access Control Bypass** plugin to modify user roles and check unauthorized access. |
| **A02: Cryptographic Failures** | Weak encryption or poor handling of sensitive data.    | Intercept HTTPS traffic using Burp Proxy to check for plaintext sensitive information. |
| **A03: Injection**            | Unsanitized input leading to unintended commands.       | Use Burp's **Intruder** to send SQL payloads like `' OR 1=1 --` to login forms. |
| **A04: Insecure Design**      | Flaws in the application’s logic or architecture.       | Use **Repeater** to manually test for logical vulnerabilities like bypassing payment steps. |
| **A05: Security Misconfiguration** | Unnecessary features or default settings enabled.    | Use Burp's **Scanner** to detect outdated software or misconfigured headers. |
| **A06: Vulnerable Components** | Using outdated or insecure third-party software.       | Analyze **Server-Side Includes (SSI)** using Burp's **Proxy** logs for vulnerable libraries. |
| **A07: Identification and Authentication Failures** | Weak or broken authentication mechanisms. | Use Burp's **Intruder** to brute-force login credentials with common username/password lists. |
| **A08: Software and Data Integrity Failures** | Compromised software supply chains or lack of integrity checks. | Use Burp's **Logger++** extension to monitor traffic for unsigned or modified scripts. |
| **A09: Security Logging and Monitoring Failures** | Insufficient monitoring or logging of suspicious activities. | Simulate suspicious activities using Burp's tools and check server responses for monitoring alerts. |
| **A10: Server-Side Request Forgery (SSRF)** | Unsanitized server-side requests to external systems. | Use Burp's **Collaborator** to confirm SSRF by triggering out-of-band DNS requests. |

## Workflow Examples
### A03: Injection (SQLi Testing)
1. Intercept a request with user input in Burp Suite Proxy.
2. Send the request to **Intruder**.
3. Use a payload list like `OWASP-SQLi.txt` to inject malicious SQL commands.
4. Analyze the response for errors or unintended behavior.

### A05: Security Misconfiguration (Header Testing)
1. Capture server responses in Burp Proxy.
2. Inspect headers for security issues like:
   - Missing `X-Content-Type-Options`.
   - Misconfigured `Content-Security-Policy`.

### A07: Identification and Authentication Failures (Brute Force)
1. Intercept a login request in Burp Proxy.
2. Send it to **Intruder**.
3. Set the payload positions for username/password fields.
4. Use a wordlist like `rockyou.txt` to brute-force credentials.
5. Review responses for successful login attempts.

## Notes
- Use **Burp Scanner** for automated checks on common OWASP vulnerabilities.
- Leverage **Burp Collaborator** for out-of-band testing (e.g., SSRF, Blind XSS).
- Prioritize manual testing for logical flaws (e.g., Insecure Design).
- Regularly update Burp extensions for the latest testing methodologies.