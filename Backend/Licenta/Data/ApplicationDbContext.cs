using Licenta.Models;
using Microsoft.EntityFrameworkCore;

namespace Licenta.Data
{
    public class ApplicationDbContext : DbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options) : base(options){
        }

        public DbSet<AirQuality> SensorData { get; set; }

    }
    
}
