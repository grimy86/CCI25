# Red team engagements
## Defining scope and objectives
Engagements can be very complex and bureaucratic.
The key to a successful engagement is clearly defined client objectives or goals.

Example:
- No exfiltration of data.
- Production servers are off-limits.
- 10.0.3.8/18 is out of scope.
- 10.0.0.8/20 is in scope.
- System downtime is not permitted under any circumstances.
- Exfiltration of PII is prohibited.

Objectives:
1. Identify system misconfigurations and network weaknesses.
   1. Focus on exterior systems.
2. Determine the effectiveness of endpoint detection and response systems.
3. Evaluate overall security posture and response.
   1. SIEM and detection measures.
   2. Remediation.
   3. Segmentation of DMZ and internal servers.
4. Use of white cards is permitted depending on downtime and length.
5. Evaluate the impact of data exposure and exfiltration.


Scope:
1. System downtime is not permitted under any circumstances.
   1. Any form of DDoS or DoS is prohibited.
   2. Use of any harmful malware is prohibited; this includes ransomware and other variations.
2. Exfiltration of PII is prohibited. Use arbitrary exfiltration data.
3. Attacks against systems within 10.0.4.0/22 are permitted.
4. Attacks against systems within 10.0.12.0/22 are prohibited.
5. Bean Enterprises will closely monitor interactions with the DMZ and critical/production systems.
   1. Any interaction with "*.bethechange.xyz" is prohibited.
   2. All interaction with "*.globalenterprises.thm" is permitted.

## Rules of engagement
Here is a [ROE template](https://redteam.guide/docs/templates/roe_template/).

| Section Name | Section Details |
|-|-|
| Executive Summary | Overarching summary of all contents and authorization within RoE document |
| Purpose |Defines why the RoE document is used |
| References |Any references used throughout the RoE document (HIPAA, ISO, etc.) |
| Scope | Statement of the agreement to restrictions and guidelines |
| Definitions | Definitions of technical terms used throughout the RoE document |
| Rules of Engagement and Support Agreement | Defines obligations of both parties and general technical expectations of engagement conduct |
| Provisions | Define exceptions and additional information from the Rules of Engagement |
| Requirements, Restrictions, and Authority | Define specific expectations of the red team cell |
| Ground Rules | Define limitations of the red team cell's interactions |
| Resolution of Issues/Points of Contact | Contains all essential personnel involved in an engagement |
| Authorization | Statement of authorization for the engagement |
| Approval | Signatures from both parties approving all subsections of the preceding document |
| Appendix | Any further information from preceding subsections |

## Campaign planning
Prior to this task, we have primarily focused on engagement planning and documentation from the business perspective. Campaign planning uses the information acquired and planned from the client objectives and RoE and applies it to various plans and documents to identify how and what the red team will do.

| Type of Plan | Explanation of Plan | Plan Contents |
|-|-|-|
| Engagement Plan | An overarching description of technical requirements of the red team. | CONOPS, Resource and Personnel Requirements, Timelines |
| Operations Plan | An expansion of the Engagement Plan. Goes further into specifics of each detail. | Operators, Known Information, Responsibilities, etc. |
| Mission Plan | The exact commands to run and execution time of the engagement. | Commands to run, Time Objectives, Responsible Operator, etc. |
| Remediation Plan | Defines how the engagement will proceed after the campaign is finished. | Report, Remediation consultation, etc. |

## Engagement plan
### Concept of operations
`The Concept of Operation (CONOPS)` is a part of the engagement plan that details a high-level overview of the proceedings of an engagement.
The CONOPS document should be written from a semi-technical summary perspective, assuming the target audience/reader has zero to minimal technical knowledge.

Critical components:
- Client Name
- Service Provider
- Timeframe
- General Objectives/Phases
- Other Training Objectives (Exfiltration)
- High-Level Tools/Techniques planned to be used
- Threat group to emulate (if any)

### Resource plan
The resource plan is the second document of the engagement plan, detailing a brief overview of dates, knowledge required (optional), resource requirements.
The plan extends the CONOPS and includes specific details, such as dates, knowledge required, etc.

Unlike the CONOPS, the resource plan should not be written as a summary; instead, written as bulleted lists of subsections.
As with most red team documents, there is no standard set of resource plan templates or documents; below is an outline of example subsections of the resource plan.

- Header
    - Personnel writing
    - Dates
    - Customer
- Engagement Dates
    - Reconnaissance Dates
    - Initial Compromise Dates
    - Post-Exploitation and Persistence Dates
    - Misc. Dates
- Knowledge Required (optional)
    - Reconnaissance
    - Initial Compromise
    - Post-Exploitation
- Resource Requirements
    - Personnel
    - Hardware
    - Cloud
    - Misc.

## Operations plan
The operations plan is a flexible document(s) that provides specific details of the engagement and actions occurring. The plan expands upon the current CONOPS and should include a majority of specific engagement information; the ROE can also be placed here depending on the depth and structure of the ROE.

The operations plan should follow a similar writing scheme to the resource plan, using bulleted lists and small sub-sections. As with the other red team documents, there is no standard set of operation plan templates or documents; below is an outline of example subsections within the operations plan.

- Header
    - Personnel writing
    - Dates
    - Customer
- Halting/stopping conditions (can be placed in ROE depending on depth)
- Required/assigned personnel
- Specific TTPs and attacks planned
- Communications plan
- Rules of Engagement (optional)

### Communication plan
The most notable addition to this document is the communications plan. The communications plan should summarize how the red cell will communicate with other cells and the client overall. Each team will have its preferred method to communicate with clients:
- vectr.io
- Email
- Slack

## Mission plan
The mission plan is a cell-specific document that details the exact actions to be completed by operators.
The document uses information from previous plans and assigns actions to them.

How the document is written and detailed will depend on the team; as this is an internally used document, the structure and detail have less impact.

- Objectives
- Operators
- Exploits/Attacks
- Targets (users/machines/objectives)
- Execution plan variations