import type { Options } from "highcharts";

declare global {
  type HighchartsOptions = Options;

  interface Settings {
    debug: bool;
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
  }

  type Session = File;
}

export {};
