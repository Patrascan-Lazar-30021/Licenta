using Licenta.Models;
using Microsoft.Data.SqlClient;
using MySqlConnector;

public class AirQualityService : IAirQualityService
{
    private readonly string _connectionString;

    public AirQualityService(IConfiguration configuration)
    {
        _connectionString = configuration.GetConnectionString("DefaultConnection");
    }

    public async Task<List<AirQuality>> GetAirQualityDataAsync()
    {
        List<AirQuality> dataList = new List<AirQuality>();

        using (MySqlConnection conn = new MySqlConnection(_connectionString))
        {
            await conn.OpenAsync();

            string query = "SELECT * FROM airquality";
            MySqlCommand cmd = new MySqlCommand(query, conn);

            using (MySqlDataReader reader = await cmd.ExecuteReaderAsync())
            {
                while (await reader.ReadAsync())
                {
                    AirQuality data = new AirQuality
                    {
                        Id = reader.GetInt32("id"),
                        Temperature = reader.GetFloat("temperature"),
                        Humidity = reader.GetFloat("humidity"),
                        Mq135 = reader.GetInt32("mq135"),
                        Mq7 = reader.GetInt32("mq7"),
                        Datetime = reader.GetDateTime("datetime")
                    };
                    dataList.Add(data);
                }
            }
        }

        return dataList;
    }
}