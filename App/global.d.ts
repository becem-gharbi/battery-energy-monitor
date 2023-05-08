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

  interface Measurement {
    current: number;
    voltage: number;
    power: number;
    timestamp: Date;
  }

  interface Session {
    timestamp: Date;
    measurements: Measurement[];
  }
}

export {};
