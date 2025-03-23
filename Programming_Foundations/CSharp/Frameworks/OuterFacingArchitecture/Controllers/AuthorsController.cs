using CourseLibrary.API.Entities;
using CourseLibrary.API.Services;
using Microsoft.AspNetCore.Mvc;
using System;

namespace CourseLibrary.API.Controllers
{
    [ApiController]
    [Route("api/authors")]
    // why not use [Route("api/[controller]")] ??
    public class AuthorsController : ControllerBase
    {
        private readonly ICourseLibraryRepository _courseLibraryRepository;

        [HttpGet()] // [HttpGet("api/authors")]
        public IActionResult GetAuthors()
        {
            var authorsFromRepo = _courseLibraryRepository.GetAuthors();
            return Ok(authorsFromRepo);

            //return new JsonResult(authorsFromRepo);
        }

        [HttpGet("{authorId}")]
        public IActionResult GetAuthor(Guid authorId)
        {
            var authorFromRepo = _courseLibraryRepository.GetAuthor(authorId);
            if (authorFromRepo == null) return NotFound();
            else return Ok(authorFromRepo);
            
            /*
            if (!_courseLibraryRepository.AuthorExists(authorId))
            {
                return NotFound();
            }

            var authorFromRepo = _courseLibraryRepository.GetAuthor(authorId);
            return Ok(authorFromRepo);
            */
        }

        public AuthorsController(ICourseLibraryRepository courseLibraryRepository)
        {
            _courseLibraryRepository = courseLibraryRepository ?? throw new ArgumentNullException(nameof(courseLibraryRepository));
        }
    }
}
