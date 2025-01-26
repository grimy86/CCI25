# Phishing
## Intro to phishing attacks
Before you learn what `phishing` is, you'll need to understand the term `social engineering`. Social engineering is the `psychological manipulation` of people into performing or divulging information by exploiting weaknesses in human nature. These "weaknesses" can be `curiosity`, `jealously`, `greed` and even `kindness and the willingness to help someone`.

Phishing is a source of `social engineering delivered through email` to trick someone into either revealing personal information, credentials or even executing malicious code on their computer.

A term you'll come across and the type of phishing campaign a red team would participate in is `spear-phishing`, as with throwing a physical spear; you'd have a target to aim at, the same can be said with spear-phishing in that `you're targeting an individual, business or organisation rather than just anybody as mass`. This is an effective form of phishing for a red team engagement as they are bespoke to the target it makes them hard to detect by technology such as spam filters, antivirus and firewalls.

Some other methods of phishing through other mediums are `smishing` which is `phishing through SMS messages`, and `vishing` which is performed through `phone calls`.

## Writing convincing emails
We have three things to work with regarding phishing emails: the sender's email address, the subject and the content.

***The Senders Address:***

Ideally, the sender's address would be from a `domain name that spoofs a significant brand`, a `known contact`, or a `coworker`.

To find what brands or people a victim interacts with, you can employ `OSINT (Open Source Intelligence) tactics`:
- Observe their social media account for any `brands or friends they talk to`.
- Searching Google for the victim's name and rough location for any reviews the victim may have left about `local businesses or brands`.
- Looking at the victim's `business website to find suppliers`.
- Looking at `LinkedIn to find coworkers` of the victim.

***The Subject:***

You should set the subject to something quite `urgent`, `worrying`, or `piques the victim's curiosity`, so they `do not ignore it and act on it quickly`.

Examples of this could be:
- Your account has been compromised.
- Your package has been dispatched/shipped.
- Staff payroll information (do not forward!)
- Your photos have been published.

***The Content:***

If **impersonating a brand or supplier**, it would be pertinent to `research their standard email templates` and `branding` (style, logo's images, signoffs etc.) and `make your content look the same` as theirs, so the victim doesn't expect anything.

If **impersonating a contact or coworker**, it could be beneficial to contact them; first, they may have some `branding in their template`, have a particular `email signature` or even something small such as `how they refer to themselves`, for example, someone might have the name Dorothy and their email is dorothy@company.thm.
Still, in their signature, it might say "`Best Regards, Dot`".

Learning these somewhat small things can sometimes have quite dramatic psychological effects on the victim and convince them more to open and act on the email.

If you've set up a spoof website to harvest data or distribute malware, the links to this should be disguised using the `anchor text` and changing it either to some text which says "Click Here" or changing it to a correct looking link that reflects the business you are spoofing, for example:
- `<a href="http://spoofsite.thm">Click Here</a>`
- `<a href="http://spoofsite.thm">https://onlinebank.thm</a>`

## Phishing infrastructure
- Domain Name:

    You'll need to `register either an authentic-looking domain name or one that mimics the identity of another domain`.

- Email Server/Account:

     You'll need to either `set up an email server or register with an SMTP email provider`. 

- DNS Records:

    Setting up DNS Records such as `SPF`, `DKIM`, `DMARC` will improve the deliverability of your emails and `make sure they're getting into the inbox rather than the spam folder`.

- Web Server:

    You'll need to `set up webservers or purchase web hosting` from a company to host your phishing websites.

- SSL/TLS Certificates:

    Creating SSL/TLS certificates for your chosen domain name will add an `extra layer of authenticity` to the attack.

- Analytics:

     When a phishing campaign is part of a red team engagement, keeping analytics information is more important. You'll need `something to keep track of the emails that have been sent, opened or clicked`. You'll also need to combine it with information from your phishing websites for which users have supplied personal information or downloaded software. 

### Automation And Useful Software
Some of the above infrastructures can be quickly automated by using the below tools.

- [GoPhish - (Open-Source Phishing Framework)](https://getgophish.com/)
    
    GoPhish is a web-based framework to make setting up phishing campaigns more straightforward. GoPhish allows you to store your SMTP server settings for sending emails, has a web-based tool for creating email templates using a simple WYSIWYG (What You See Is What You Get) editor. You can also schedule when emails are sent and have an analytics dashboard that shows how many emails have been sent, opened or clicked.

- [SET - (Social Engineering Toolkit)](https://www.trustedsec.com/resources/tools/the-social-engineer-toolkit-set)

    The Social Engineering Toolkit contains a multitude of tools, but some of the important ones for phishing are the ability to create spear-phishing attacks and deploy fake versions of common websites to trick victims into entering their credentials.

![Phishing infrastructure](/Img/Phishing.png)

## Droppers
Droppers are `software` that phishing victims tend to be tricked into downloading and running on their system. The dropper may advertise itself as something useful or legitimate such as a codec to view a certain video or software to open a specific file.

The droppers are not usually malicious themselves, so they tend to pass antivirus checks. `Once installed, the intended malware is either unpacked or downloaded from a server` and installed onto the victim's computer. The malicious software usually `connects back to the attacker's infrastructure`. The attacker can take control of the victim's computer, which can further explore and exploit the local network.

## Choosing a phishing domain
Choosing the right Phishing domain to launch your attack from is essential to ensure you have the psychological edge over your target. A red team engagement can use some of the below methods for choosing the perfect domain name.

**Expired Domains:**

Although not essential, buying a domain name with some history `may lead to better scoring of your domain when it comes to spam filters`. Spam filters have a tendency to not trust brand new domain names compared to ones with some history.

**Typosquatting:**

Typosquatting is when a registered domain `looks very similar to the target domain you're trying to impersonate`. Here are some of the common methods:
- Misspelling: goggle.com Vs google.com
- Additional Period: go.ogle.com Vs google.com
- Switching numbers for letters: g00gle.com Vs google.com
- Phrasing: googles.com Vs google.com
- Additional Word: googleresults.com Vs google.com

These changes might look unrealistic, but `at a glance, the human brain tends to fill in the blanks` and see what it wants to see, i.e. the correct domain name.

**TLD Alternatives:**

A TLD (Top Level Domain) is the .com .net .co.uk .org .gov e.t.c part of a domain name, there are 100's of variants of TLD's now. A common trick for choosing a domain would be to use the `same name but with a different TLD`. For example, register tryhackme.co.uk to impersonate tryhackme.com.

**IDN Homograph Attack/Script Spoofing:**

Originally domain names were made up of Latin characters a-z and 0-9, but in 1998, `IDN (internationalized domain name)` was implemented to support language-specific script or alphabet from other languages such as Arabic, Chinese, Cyrillic, Hebrew and more. An issue that arises from the IDN implementation is that different letters from different languages can actually appear identical. For example, Unicode character U+0430 (Cyrillic small letter a) looks identical to Unicode character U+0061 (Latin small letter a) used in English, enabling attackers to register a domain name that looks almost identical to another.

![IDN Homograp](/Img/IDN.png)

## Using MS Office in phishing
Often during phishing campaigns, a Microsoft Office document (typically Word, Excel or PowerPoint) will be included as an attachment. `Office documents can contain macros`; macros do have a legitimate use but can also be used to run computer commands that can cause malware to be installed onto the victim's computer or connect back to an attacker's network and allow the attacker to take control of the victim's computer.

## Using browser exploits
Another method of gaining control over a victim's computer could be through browser exploits; this is when there is a `vulnerability against a browser itself` (Internet Explorer/Edge, Firefox, Chrome, Safari, etc.), which allows the attacker to run remote commands on the victim's computer.

Browser exploits aren't usually a common path to follow in a red team engagement unless you have prior knowledge of old technology being used on-site. Many browsers are kept up to date, hard to exploit due to how browsers are developed, and the exploits are often worth a lot of money if reported back to the developers.

That being said, it can happen, and as previously mentioned, it could be used to target old technologies on-site because possibly the browser software cannot be updated due to incompatibility with commercial software/hardware, which can happen quite often in big institutions such as education, government and especially health care.

Usually, the victim would receive an email, convincing them to visit a particular website set up by the attacker. Once the victim is on the site, the exploit works against the browser, and now the attacker can perform any commands they wish on the victim's computer.

An example of this is CVE-2021-40444 from September 2021, which is a vulnerability found in Microsoft systems that allowed the execution of code just from visiting a website.

