# Windows persistence
## Introduction
After gaining the first foothold on your target's internal network, you'll want to ensure you `don't lose access` to it before actually getting to the crown jewels. Establishing persistence is one of the first tasks we'll have as attackers when gaining access to a network. In simple terms, persistence refers to `creating alternate ways to regain access to a host without going through the exploitation phase all over again`.

There are many reasons why you'd want to establish persistence as quick as possible, including:

- Re-exploitation isn't always possible
- Gaining a foothold is hard to reproduce
- The blue team is after you