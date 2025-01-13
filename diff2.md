## Intruder
Allows for automated and customisable attacks. It provides the ability to modify specific parts of a request and perform repetitive tests with variations of input data. Intruder is particularly useful for tasks like fuzzing and brute-forcing, where different values need to be tested against a target.

### Tabs
| Tab | Description |
| - | - |
| Positions | examine the positions within the request `where we want to insert our payloads` |
| Payloads | create, assign, and configure `payloads` |

### Attack types
| Type | Description |
| - | - |
| `Sniper` | Default & most common attack type, iterate through payloads by inserting `one at a time` into each defined position. |
| `Battering ram` | Sends all payloads simultaneously, each inserted into its defined position. Useful when testing for race conditions or when payloads need to be sent concurrently. |
| `Pitchfork` | Enables simultaneous testing of multiple positions with different payloads. It also always for definition of multiple payload sets, each associated with a specific position. |
| `Cluster bomb` | Combines sniper and pitchfork approaches. It performs a sniper-like attack on each position but simultaneously tests all payloads for each set. |

## Other Modules
### Decoder
Gives user data manipulation capabilities. It not only `decodee` data intercepted during an attack but also provides the function to `encode` our own data, prepping it for transmission to the target. Decoder also allows us to `create hashsums` of data, as well as providing a `Smart Decode` feature, which attempts to decode provided data recursively until it is back to being plaintext. Much like Cyberchef's "magic" function.

### Comparer
Comparer, as the name implies, lets us compare two pieces of data, either by `ASCII words or by bytes`.

### Sequencer
Allows us to evaluate the entropy, or randomness, of "tokens". Tokens are strings used to identify something and should ideally be generated in a cryptographically secure manner.

### Organizer tools
Designed to help you store and annotate copies of HTTP requests that you may want to revisit later.
