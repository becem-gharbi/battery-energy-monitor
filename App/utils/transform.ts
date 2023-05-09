import Papa from "papaparse";

export function transformSession(session: Session) {
  return new Promise<Measurements>((resolve) => {
    let measurements: Measurements = {
      current: [],
      power: [],
      voltage: [],
      energy: 0,
    };

    Papa.parse(session, {
      header: true,
      dynamicTyping: true,

      complete: function (results) {
        let parsedData = results.data as {
          Time: number;
          Current: number;
          Voltage: number;
        }[];

        parsedData.forEach((el) => {
          if (!el.Time || !el.Current || !el.Voltage) {
            return;
          }

          const timestamp = new Date(el.Time + session.lastModified);
          const localTimestamp =
            timestamp.getTime() - timestamp.getTimezoneOffset() * 60 * 1000;
          const current = Number(el.Current.toFixed(2));
          const voltage = Number(el.Voltage.toFixed(2));
          const power = Number((current * voltage).toFixed(2));

          measurements.current.push([localTimestamp, current]);
          measurements.voltage.push([localTimestamp, voltage]);
          measurements.power.push([localTimestamp, power]);
        });

        for (let i = 0; i < measurements.power.length - 1; i++) {
          const deltaX =
            (measurements.power[i + 1][0] - measurements.power[i][0]) / 1000;
          const deltaY =
            (measurements.power[i + 1][1] + measurements.power[i][1]) / 2;

          const area = deltaX * deltaY;

          if (isNaN(area)) continue;

          measurements.energy += deltaX * deltaY;
        }

        resolve(measurements);
      },
    });
  });
}
