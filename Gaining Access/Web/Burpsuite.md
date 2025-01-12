## Burp Suite Basics Info
| **Feature**                | **Description**                                                                                       | **Key Notes/Commands**                                                    |
|-----------------------------|-------------------------------------------------------------------------------------------------------|---------------------------------------------------------------------------|
| **Features of Burp**       | A web application security testing tool with modules for scanning, proxying, and exploiting.          | Includes tools like Proxy, Repeater, Scanner, and Intruder.              |
| **Dashboard**              | Central interface showing project activity, alerts, and scanning progress.                           | Use for quick navigation and monitoring ongoing tests.                   |
| **Navigation**             | Organized into tabs like Proxy, Target, Repeater, and Intruder for ease of use.                       | Use tabs to quickly switch between tools.                                |
| **Options**                | Configurable settings for tools and preferences, such as proxy interception and target scope.         | Adjust settings for scope and interception based on test requirements.   |
| **Burp Proxy**             | Intercepts and manipulates HTTP/HTTPS traffic between the browser and the server.                     | Use with FoxyProxy for seamless browser integration.                     |
| **Connecting (FoxyProxy)** | Browser extension to redirect traffic through Burp Suite's proxy listener.                            | Configure browser proxy settings to match Burp's proxy listener.         |
| **Site Map**               | Displays a hierarchical view of the application being tested.                                         | Use for exploring and mapping application structure.                     |
| **Issue Definitions**      | Provides details about vulnerabilities identified during scans.                                       | Includes severity levels and remediation suggestions.                    |
| **Burp Suite Browser**     | A Chromium-based browser integrated with Burp Suite for testing without manual proxy setup.           | Ideal for testing HTTPS and complex authentication flows.                |
| **Scoping and Targeting**  | Define target applications and directories to include or exclude in the tests.                        | Reduces noise by focusing on specific areas of the application.          |
| **Proxying HTTPS**         | Allows interception of HTTPS traffic via Burp's CA certificate.                                       | Install Burp's certificate in the browser for SSL interception.          |
| **Example Attack**         | Manual or automated testing to find and exploit vulnerabilities like SQL injection or XSS.            | Use Repeater or Intruder for payload testing and automation.             |
| **Conclusion**             | Summarizes findings and generates reports for further analysis or client deliverables.                | Export detailed reports in professional engagements.                     |

## Repeater
Enables us to `modify and resend intercepted requests` to a target of our choosing.
It allows us to take requests captured in the Burp Proxy and manipulate them, sending them `repeatedly` as needed.

Once a request has been captured in the Proxy module, we can send it to Repeater by either right-clicking on the request and selecting `Send to Repeater`, or by utilizing the keyboard shortcut `Ctrl + R`.

## Intruder
Offers `automated and customisable request manipulation` and enables tasks such as `fuzzing` and `brute-forcing`.
Intruder's functionality is comparable to command-line tools like `Wfuzz` or `ffuf`.

it's important to note that while Intruder can be used with Burp Community Edition, it is rate-limited, significantly reducing its speed compared to Burp Professional.

The initial view of Intruder presents a simple interface where we can select our target.
This field will already be populated if a request has been sent from the Proxy (using `Ctrl + I` or right-clicking and selecting `Send to Intruder`).

