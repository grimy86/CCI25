# ASP.NET Core Web API overview
![ASP](/Frameworks/Images//ASP.png)

## Theory
ASP.NET Core MVC voorziet een framework voor het maken van API’s met behulp van de
MVC (Model View Controller) pattern. REST is een architecturale style maar geen standaard. Deze gaat bepalen hoe een goed gestructureerde API er moet uit zien.
**Constraints:**
- Uniform Interface
- Client-server
- Statelessness
- Layered system
- Cacheable
- Code on demand

**Score your API based on the maturity:**
- Richardson Maturity Model

Outer-facing contract:
- URI
- Hierarchical data
- Filter, sorting, oredering
- RPC-style calls

![Routing verbs](/Frameworks/Images//RoutingVerbs.png)

Basis CRUD operaties en hun HTTP / Web equivalent:
- `Create` == `Post`
- `Read` == `Get`
- `Update` == `Put`
- `Delete` == `Delete`

Meer HTTP operaties:
- `PATCH`: Update gedeeltelijk een bestaande bron op basis van de verstrekte gegevens. Het wordt gebruikt wanneer je slechts een deel van de bron wilt bijwerken.

- `HEAD`: Vergelijkbaar met GET, maar het retourneert alleen de headerinformatie, niet de feitelijke gegevens.

- `OPTIONS`: Geeft informatie over de communicatieopties voor de doelbron.

- `TRACE`: Echos terug de ontvangen verzoekinformatie, zodat een client kan zien wat (indien iets) aan de andere kant van de server is aangekomen.

- `CONNECT`: Reserveren van de netwerkverbinding voor het gebruik van een duplex tunnel, meestal gebruikt met HTTPS.

| Status codes | Description |
|-|-|
| Level 100 | Informative codes|
| Level 200 | Success codes |
| 200 | ok |
| 201 | created |
| 204 | no content (for delete method) |
| Level 300 | Redirection codes (not really used in API) |
| Level 400 | User-error codes |
| 400 | bad request |
| 401 | unauthorized |
| 403 | authorized but no rights |
| 404 | data not found |
| 405 | method not allowed |
| 406 | not acceptable / wrong format |
| 409 | conflict / concurrency |
| 415 | unsupported media type |
| 415 | unprocessable entity / validation error |
| Level 500 | Insernal server error codes |

Wanneer we vandaag spreken over API’s, dan spreken in één adem over Json, maar Json is geen
onderdeel van REST. Het is wel het meest gebruikte formaat voor een response, maar het kan
evengoed XML zijn.

anneer we gaan bepalen welk type response we terug krijgen of geven, dan spreken we over
content negotiation.

## Practice

1. Create MVC architecture project in VS
   1. ASP.NET Core Web Application API
   2. Project name ends with .API and solution name doesn't because of n amount of projects in solution
   3. Remove default stuff like weather forecast controller
   4. Change the projects debug profile to console app
      1. Disable launch browser
      2. Use some default app url like localhost:51044
2. Create data store
   1. NuGet Add
      1. EFCore
      2. EFCore.SqlServer
      3. EFCore.Tools
   2. Create models / entities
   3. DBContext
   4. Create EF CRUD service interface & repository
   5. Startup -> Configure services
   6. Add-Migration InitialMigration
   7. application.json logging

        ```json
        {
            "Logging":{
                "Console":{
                    "LogLevel":{
                    "Microsoft.Hosting.Lifetime": "Trace"
                    }
                }
            },
            "AllowedHosts": "*"
        }
        ```
3. Create our controller
   1. IActionResult methods
   2. Add routing attributes
   3. Configure endpoint routing in Startup.cs Configure()
   4. Test requests in postman, status codes and all..
   5. Return the correct status codes methods from the MVC controller classes and handle bad requests
   6. ConfigureServices in the startup.cs again to accept more than just JSON
4. Returning custom objects using Models / Data Transfer Objects
   1. Change the controller return types from IActionResult to something like `ActionResult<IEnumerable<AuthorDto>>`, (remember DTO = Data Transfer Object)
   2. Instead of the manual object mapping that we did in step 3 we can use NuGet `AutoMapper.Extensions.Microsoft.DependencyInjection`
      1. Create a objectProfile class that inherits from profile
      2. Now, create a mapping, the finished class looks like this:

      ```cs
      namespace CourseLibrary.API.Profiles
      {
         public class AuthorsProfile : Profile
         {
            public AuthorsProfile()
            {
                  CreateMap<Entities.Author, Models.AuthorDto>()
                     .ForMember(
                        dest => dest.Name,
                        opt => opt.MapFrom(src => $"{src.FirstName} {src.LastName}"))
                     .ForMember(
                        dest => dest.Age,
                        opt => opt.MapFrom(src => src.DateOfBirth.GetCurrentAge()));
            }
         }
      }
      ```
5. Error handling:
   1. When you expect a validation fault, DON'T use exception handling. It costs quite come resources, the API user might loop this and crash the API...
   2. Also, Internal Server Errors give away the entire stacktrace which is a security concern and the API user can't use it anyways cause it's on our server, so:
      1. Project properties -> Debug tab -> `ASPNETCORE_ENVIRONMENT:Development`, change this to `ASPNETCORE_ENVIRONMENT:Production`.
      2. Navigate to `Startup.cs.Configure()` and add:

      ```cs
      app.UseExceptionHandler(appBuilder =>
      {
         appBuilder.Run(async context =>
         {
            context.Response.StatusCode = 500;
            await context.Response.WriteAsync("Een onverwachte fout heeft zich voorgedaan. Probeer het later opnieuw.");
         });
      });
      ```
6. Filtering and searching, usually used when you know what items are inside of a collection
