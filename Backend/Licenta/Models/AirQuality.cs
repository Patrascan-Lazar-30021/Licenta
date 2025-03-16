namespace Licenta.Models
{
    public class AirQuality
    {
        public int Id { get; set; }
        public float Temperature { get; set; }
        public float Humidity { get; set; }
        public int Mq135 { get; set; }
        public int Mq7 { get; set; }
        public DateTime Datetime { get; set; }
    }

}
