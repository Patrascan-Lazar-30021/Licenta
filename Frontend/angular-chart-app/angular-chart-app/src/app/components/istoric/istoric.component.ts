import { Component, OnInit } from '@angular/core';
import { MainService, AirQuality } from '../../service/service.component';

@Component({
  selector: 'app-istoric',
  templateUrl: './istoric.component.html',
  styleUrls: ['./istoric.component.css'],
})
export class IstoricComponent implements OnInit {
  airQualityData: AirQuality[] = [];

  constructor(private mainService: MainService) {}

  ngOnInit(): void {
    this.mainService.getAirQualityData().subscribe(
      (data) => {
        this.airQualityData = data;
      },
      (error) => {
        console.error('Error fetching data:', error);
      }
    );
  }
}
