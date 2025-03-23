# Common Software Architectures
| Architecture | Best for | Key Benefit |
|-|-|-|
| `MVVM` | WPF, MAUI, Xamarin | Data binding, testability |
| `MVC` | Web apps (ASP.NET, Django) | Scalability, separation |
| `MVP` | WinForms, legacy apps | Easier unit testing |
| `Layered` | Enterprise apps | Clear separation of concerns |
| `Microservices` | Cloud-based, scalable apps | Independent services |
| `Event-Driven` | Real-time, IoT | High responsiveness |
| `Hexagonal` | Large applications | Flexibility, maintainability |
| `Clean` | Scalable systems | Strong separation, longevity |
| `CQRS` | High-performance apps | Optimized read/write ops |
| `ECS` | Game development | Better performance |


## MVVM (Model-View-ViewModel)
MVVM separates the UI (**View**) from the business logic (**ViewModel**) while keeping data and state management in the **Model**.  
- **Used in:** WPF, MAUI, Xamarin  
- **Best for:** Desktop & mobile apps  

**Components:**
- **Model:** Manages data and business logic (e.g., database calls).
- **View:** The UI (XAML in WPF/MAUI).
- **ViewModel:** Acts as a bridge between the View and Model using data binding.

---

## MVC (Model-View-Controller)
The Controller processes user requests (e.g., `/GetUser`), retrieves data from the Model, and passes it to the View.  
- **Used in:** ASP.NET Core, Spring, Django  
- **Best for:** Web apps & APIs  

**Components:**
- **Model:** Handles data and business logic.
- **View:** UI layer (HTML, Razor, or templates).
- **Controller:** Handles user input and updates Model/View.

## MVP (Model-View-Presenter)
Similar to MVVM, but the **Presenter** directly updates the **View** (no data binding like MVVM).  
- **Used in:** WinForms, legacy desktop apps  
- **Best for:** Older desktop applications  

**Components:**
- **Model:** Manages data.
- **View:** Displays UI, but contains no logic.
- **Presenter:** Acts as a mediator between Model and View.

## Layered Architecture (N-Tier)
A structured architecture where components are divided into separate layers.  
- **Used in:** Large applications, enterprise software  
- **Best for:** Scalable web and desktop applications  

**Common Layers:**
1. **Presentation Layer:** UI (Web, desktop, API)
2. **Business Logic Layer (BLL):** Processes data
3. **Data Access Layer (DAL):** Handles database interactions  

## Microservices Architecture
Instead of a single app, multiple **independent services** communicate via **APIs (REST, gRPC)**.  
- **Used in:** Netflix, Amazon, Cloud applications  
- **Best for:** Large, scalable web services  

**Why Use Microservices?**
✅ Scalable  
✅ Independent deployment  
✅ Fault-tolerant  

## Event-Driven Architecture
A system where components react to **events** instead of directly calling each other.  
- **Used in:** IoT, real-time apps, trading systems  
- **Best for:** High-performance, decoupled applications  

**Why Use It?**
✅ Components are loosely coupled  
✅ High responsiveness  
✅ Better scalability  

## Hexagonal (Ports and Adapters) Architecture
Focuses on **isolating core business logic** and keeping dependencies (UI, Database, APIs) **separate**.  
- **Used in:** Scalable applications, long-term projects  
- **Best for:** Maintainable and testable code  

**Why Use It?**
✅ Increased testability  
✅ More flexibility for changing technologies  

## Clean Architecture
A layered design that keeps the **core business logic** at the center, making dependencies flow inward.  
- **Used in:** Large applications  
- **Best for:** Long-term maintainability  

**Why Use It?**
✅ Separation of concerns  
✅ Better dependency management  

## CQRS (Command-Query Responsibility Segregation)
Separates **read operations** from **write operations** to optimize performance.  
- **Used in:** High-performance web apps, financial systems  
- **Best for:** Systems with heavy database operations  

**Why Use It?**
✅ Faster queries  
✅ Scales well with microservices  

## ECS (Entity-Component-System)
A **game development** pattern that replaces traditional OOP hierarchies with a **data-driven approach**.  
- **Used in:** Unity, Unreal Engine  
- **Best for:** Performance-intensive games  

**Why Use It?**
✅ More efficient than OOP  
✅ Better memory management