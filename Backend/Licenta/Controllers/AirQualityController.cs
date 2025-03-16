using Licenta.Models;
using Microsoft.AspNetCore.Mvc;

[ApiController]
[Route("[controller]")]
public class AirQualityController : ControllerBase
{
    private readonly IAirQualityService _airQualityService;

    public AirQualityController(IAirQualityService airQualityService)
    {
        _airQualityService = airQualityService;
    }       

    [HttpGet]
    public async Task<IEnumerable<AirQuality>> Get()
    {
        return await _airQualityService.GetAirQualityDataAsync();
    }
}
