# Application Programming Interface (API) introduction
An API is a way for two or more software components to communicate with each other.
APIs define rules for how requests and responses should be structured.

## Types
There are different types of APIs depending on how they are used and what they interact with:

- Hardware APIs

    These allow software to `communicate with hardware`.

    Example: DirectX API → Used in game development to interact with GPUs.

| API Type | Description | Example |
|-|-|-|
| Local APIs (OS APIs) | These allow applications to interact with the operating system. | Win32 API → Used for Windows applications to `interact with system resources` like files, memory, processes, etc. Which provides functions like CreateFile(), ReadFile(), etc., which allow programs to access the Windows system. |
| Web APIs | These allow `communication over a network`, often using HTTP. | REST API, SOAP API, GraphQL API, A client sends a request (e.g., GET /users) to a server, and the server responds with data. |
| Library APIs | These APIs are built into `software libraries` to allow developers to use pre-built functionality. | The .NET API (like System.IO.File.ReadAllText()) lets you work with files in C#. |
| Hardware APIs | These allow software to `communicate with hardware`. | Example: DirectX API → Used in game development to interact with GPUs. |