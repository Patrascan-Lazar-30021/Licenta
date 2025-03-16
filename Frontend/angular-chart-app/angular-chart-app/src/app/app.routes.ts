import { Routes } from '@angular/router';
import { ChartComponent } from './components/chart/chart.component';

export const routes: Routes = [
  { path: 'chart', component: ChartComponent },
  { path: '', redirectTo: 'chart', pathMatch: 'full' } 
];
