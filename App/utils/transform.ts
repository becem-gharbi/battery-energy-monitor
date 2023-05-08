import Papa from "papaparse";

export function transformSession(session: Session) {
  return new Promise<Measurements>((resolve) => {
    let measurements: Measurements = {
      current: [],
      power: [],
      voltage: [],
    };

    Papa.parse(session, {
      complete: function (results) {
        const parsedData = results.data as string[][];

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

        resolve(measurements);
      },
    });
  });
}
