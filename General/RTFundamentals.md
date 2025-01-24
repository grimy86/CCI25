# Read Team Fundamentals
- A penetration tester is tasked to carry out conventional vulnerability assessments.
- A red teamer is tasked to go beyond a pentest and carry out an actual simulated attack.

## Vulnerability Assessment and Penetration Tests Limitations
This is the simplest form of security assessment.
A vulnerability assessment focuses on scanning hosts for vulnerabilities as individual entities so that security deficiencies can be `identified` and effective security measures can be deployed to `protect` the network in a prioritized manner.
Most of the work can be done with automated tools and performed by operators without requiring much technical knowledge.

### Advanced Persistent Threats and why Regular Pentesting is not Enough
While the conventional security engagements we have mentioned cover the finding of most technical vulnerabilities, there are limitations on such processes and the extent to which they can effectively prepare a company against a real attacker. Such limitations include:
- Time constraints
- Budget
- Limited scope
- Non-disruptive
- Heavy IT focus

As a consequence, some aspects of penetration tests might significantly differ from a real attack, like:
- Penetration tests are LOUD: Usually, pentesters won't put much effort into trying to go undetected. Unlike real attackers, they don't mind being easy to detect.
- Non-technical attack vectors might be overlooked: Attacks based on `social engineering` or physical intrusions are usually not included in what is tested.
- Relaxation of security mechanisms: While doing a regular penetration test, some security mechanisms might be temporarily disabled or relaxed for the pentesting team in favor of efficiency.

On the other hand, real attackers won't follow an ethical code and are mostly unrestricted in their actions. Nowadays, the most prominent threat actors are known as `Advanced Persistent Threats (APT)`, which are highly skilled groups of attackers, usually sponsored by nations or organised criminal groups.

## Red team engagements
To keep up with the emerging threats, red team engagements were designed to shift the focus from regular penetration tests into a process that allows us to clearly see our defensive team's capabilities at `detecting` and `responding` to a real threat actor. They don't replace traditional penetration tests, but complement them by focusing on detection and response rather than prevention.

Red teaming is a term borrowed from the military. In military exercises, a group would take the role of a `red team` to simulate attack techniques to test the reaction capabilities of a defending team, generally known as `blue team`, against known adversary strategies. Translated into the world of cybersecurity, red team engagements consist of emulating a real threat actor's `Tactics, Techniques and Procedures (TTPs)` so that we can measure how well our blue team responds to them and ultimately improve any security controls in place.

Every red team engagement will start by defining clear goals, often referenced as `crown jewels` or `flags`, ranging from compromising a given critical host to stealing some sensitive information from the target.

Red team engagements also improve on regular penetration tests by considering several attack surfaces:

- Technical Infrastructure: Like in a regular penetration test, a red team will try to uncover technical vulnerabilities, with a much `higher emphasis on stealth and evasion`.
- Social Engineering: `Targeting people` through phishing campaigns, phone calls or social media to `trick them into revealing information` that should be private.
- Physical Intrusion: Using techniques like `lockpicking`, `RFID cloning`, exploiting weaknesses in electronic access control devices to access restricted areas of facilities.

Depending on the resources available, the red team exercise can be run in several ways:

- Full Engagement: Simulate an attacker's full workflow, from initial compromise until final goals have been achieved.
- Assumed Breach: Start by assuming the attacker has already gained control over some assets, and try to achieve the goals from there. As an example, the red team could receive access to some user's credentials or even a workstation in the internal network.
- Table-top Exercise:  An over the table simulation where scenarios are discussed between the red and blue teams to evaluate how they would theoretically respond to certain threats. Ideal for situations where doing live simulations might be complicated.

## Teams and functions of an engagement
There are several factors and people involved within a red team engagement. Everyone will have their mindset and methodology to approach the engagement personnel.

| Teams | [Definitions](https://redteam.guide/docs/definitions/) |
|-|-|
| Red cell | A red cell is the component that makes up the `offensive portion` of a red team engagement that simulates a given target's strategic and tactical responses. |
| Blue cell | The blue cell is the opposite side of red. It includes all the components defending a target network. The blue cell is typically comprised of `blue team members, defenders, internal staff, and an organisation's management`. |
| White cell | Serves as `referee` between red cell activities and blue cell responses `during an engagement`. Controls the engagement environment/network. `Monitors adherence to the ROE`. `Coordinates activities` required to achieve engagement goals. Correlates red cell activities with defensive actions. Ensures the engagement is conducted without bias to either side. |

These teams or cells can be broken down further into an engagement hierarchy.

![Team cells](/Img/TeamCells.png)

| Role | Purpose |
|-|-|
| Red Team Lead | `Plans and organises` engagements at a high level—delegates, assistant lead, and operators engagement assignments. |
| Red Team Assistant Lead | Assists the team lead in `overseeing engagement` operations and operators. Can also assist in writing engagement plans and documentation if needed. |
| Red Team Operator | `Executes` assignments delegated by team leads. Interpret and analyse engagement plans from team leads. |

## Engagement structure
Structures usually follow a `kill chain` of sorts, which is a military concept that identifies the structure of an attack. In this case we'll look at the common `Lockheed Martin Cyber Kill Chain`.

1. Recon
2. Weaponisation
3. Delivery
4. Exploitation
5. Installation
6. Command & control
7. Actions on objectives