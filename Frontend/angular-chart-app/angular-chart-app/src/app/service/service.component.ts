import { HttpClient } from '@angular/common/http';
import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';

export interface AirQuality {
  id: number;
  temperature: number;
  humidity: number;
  mq135: number;
  mq7: number;
  datetime: string;
}

@Injectable({
  providedIn: 'root',
})
export class MainService {
  private apiUrl = 'http://localhost:7103/AirQuality'; // Ensure this matches your backend

  constructor(private http: HttpClient) {}

  getAirQualityData(): Observable<AirQuality[]> {
    return this.http.get<AirQuality[]>(this.apiUrl);
  }
}
