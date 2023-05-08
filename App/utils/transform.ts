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
      complete: function (results) {
        let parsedData = results.data as string[][];

        parsedData.shift();

        parsedData.forEach((el) => {
          const timestamp = new Date(parseInt(el[0]) + session.lastModified);
          const localTimestamp =
            timestamp.getTime() - timestamp.getTimezoneOffset() * 60 * 1000;
          const current = Number(parseFloat(el[1]).toFixed(2));
          const voltage = Number(parseFloat(el[2]).toFixed(2));
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
