import type { Options } from "highcharts";

declare global {
  type HighchartsOptions = Options;

  interface Settings {
    debug: 0 | 1;
    sampleRate: number;
    savingRate: number;
    currentGain: number;
    currentOffset: number;
    voltageGain: number;
    voltageOffset: number;
  }

  interface Measurements {
    current: number[][];
    voltage: number[][];
    power: number[][];
    energy: number;
  }

  type Session = File;
}

export {};
