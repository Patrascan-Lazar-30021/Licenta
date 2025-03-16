using Licenta.Models;

public interface IAirQualityService
{
    Task<List<AirQuality>> GetAirQualityDataAsync();
}
