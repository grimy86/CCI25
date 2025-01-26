# Principles of security
## The CIA triad
The `CIA` triad is an information security model used in `consideration` throughout creating a security policy.

1. Confidentiality
    The `protection` of data `from unauthorized access` and misuse.

    Example: Employee records and accounting documents will be considered sensitive. Confidentiality will be provided in the sense that only HR administrators will access employee records, where vetting and tight access controls are in place.

2. Integrity
    The condition where `information` is `kept accurate` and consistent unless authorized changes are made.

    Example: Hash verifications and digital signatures can help ensure that transactions are authentic and that files have not been modified or corrupted.

3. Availability
    In order for `data` to be useful, it must be available and `accessible` by the user.

    Example: Having reliable and well-tested hardware for their information technology servers (i.e. reputable servers).

## The DAD triad
The security of a system is `attacked through one of several means`. It can be via the disclosure of secret data, alteration of data, or destruction of data.
1. Disclosure
2. Alteration
3. Destruction or Denial

## Principles of Privileges
The levels of access given to individuals are determined on two primary factors:
1. The individual's `role/function` within the organisation
2. The `sensitivity` of the information being stored on the system

Two key concepts are used to assign and manage the access rights of individuals:
1. Privileged Identity Management (`PIM`)
    Used to `translate` a user's `role` within an organisation `into` an access `role on a system`.

2. Privileged Access Management (`PAM`).
    `Management of the privileges` a system's access role has, amongst other things

## Security models
### The Bell-La Padula Model
Used to achieve confidentiality. This model has a few assumptions, such as an organisation's hierarchical structure it is used in, where everyone's responsibilities/roles are well-defined.

Works by `granting access` to pieces of data (called objects) on a strictly `need to know basis`. This model uses the rule "`no write down, no read up`".

![Bell-La Padula Model](/Img/BellLaPadula.png)

### Biba Model
The Biba model is arguably the equivalent of the Bell-La Padula model but for the integrity of the CIA triad.

This model applies the rule to objects (data) and subjects (users) that can be summarised as "`no write up, no read down`". This rule means that subjects can create or write content to objects at or below their level but can only read the contents of objects above the subject's level.

![Biba Model](/Img/Biba.png)

### Clark-Wilson Model
The Clark-Wilson Model also aims to achieve integrity by using the following concepts:

- Constrained Data Item (CDI): This refers to the data type whose integrity we want to preserve.
- Unconstrained Data Item (UDI): This refers to all data types beyond CDI, such as user and system input.
- Transformation Procedures (TPs): These procedures are programmed operations, such as read and write, and should maintain the integrity of CDIs.
- Integrity Verification Procedures (IVPs): These procedures check and ensure the validity of CDIs.

### Other models
- Brewer and Nash model
- Goguen-Meseguer model
- Sutherland model
- Graham-Denning model
- Harrison-Ruzzo-Ullman model

## Zero trust principle vs. Trust but verify
1. Zero Trust
   
   This principle treats `trust as a vulnerability`, and consequently, it caters to insider-related threats. After considering trust as a vulnerability, zero trust tries to eliminate it. It is teaching indirectly, “never trust, always verify.” In other words, every entity is considered adversarial until proven otherwise. Zero trust does not grant trust to a device based on its location or ownership. This approach contrasts with older models that would trust internal networks or enterprise-owned devices. Authentication and authorization are required before accessing any resource. As a result, if any breach occurs, the damage would be more contained if a zero trust architecture had been implemented.

2. Trust but Verify
   
   This principle teaches that we should `always verify even when we trust` an entity and its behaviour. An entity might be a user or a system. Verifying usually requires setting up proper logging mechanisms; verifying indicates going through the logs to ensure everything is normal. In reality, it is not feasible to verify everything; just think of the work it takes to review all the actions taken by a single entity, such as Internet pages browsed by a single user. This requires automated security mechanisms, such as proxy, intrusion detection, and intrusion prevention systems.


## Threat Modelling & Incident Response
Threat modelling is the process of `reviewing`, `improving`, and `testing` the `security protocols` in place in an organisation's information technology infrastructure and services.

The principles all return to:
- Preparation
- Identification
- Mitigations
- Review

For example, an effective threat model includes:
- Threat intelligence
- Asset identification
- Mitigation capabilities
- Risk assessment

To help with this, there are frameworks such as `STRIDE` (Spoofing identity, Tampering with data, Repudiation threats, Information disclosure, Denial of Service and Elevation of privileges) and `PASTA` (Process for Attack Simulation and Threat Analysis).

Incidents are classified using a rating of urgency and impact. Urgency will be determined by the type of attack faced, where the impact will be determined by the affected system and what impact that has on business operations.

![Incident rating & Classification](/Img/IncidentRating.png)

An incident is responded to by a Computer Security Incident Response Team (`CSIRT`) which is prearranged group of employees with technical knowledge about the systems and/or current incident. To successfully solve an incident, these steps are often referred to as the six phases of Incident Response that takes place, listed in the table below:
| Action | Description |
|-|-|
| Preparation | Do we have the resources and plans in place to deal with the security incident? |
| Identification | Has the threat and the threat actor been correctly identified in order for us to respond to? |
| Containment | Can the threat/security incident be contained to prevent other systems or users from being impacted? |
| Eradication | Remove the active threat. |
| Recovery | Perform a full review of the impacted systems to return to business as usual operations. |
| Lessons Learned | What can be learnt from the incident? I.e. if it was due to a phishing email, employees should be trained better to detect phishing emails. |