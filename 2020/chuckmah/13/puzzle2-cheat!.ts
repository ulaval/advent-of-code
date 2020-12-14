import * as fs from "fs";

interface IBus {
    busId: number;
    offset: number;
}
console.time("part2");

const data = fs.readFileSync("./input.txt", "utf8").split("\r\n");
// Crear un array con la informacion del id del bus y su offset respecto al primero
const buses: IBus[] = data[1]
    .split(",")
    .map((id, index) => ({ busId: parseInt(id), offset: index }))
    .filter((c) => !isNaN(c.busId));

/**
 * Calcula el siguiente timestamp para el que se cumplen las condiciones de los autobuses anteriores y el siguiente
 * @param initialTimestamp timestamp a partir del que empezar a buscar
 * @param increment incremento desde el rimestamp
 * @param nextBus siguiente bus que debe cumplir su condicion en el bloque calculado
 */
const nextTimestamp = (
    initialTimestamp: number,
    increment: number,
    nextBus: IBus
): number => {
    while ((initialTimestamp + nextBus.offset) % nextBus.busId != 0) {
        initialTimestamp += increment;
    }
    return initialTimestamp;
};

let timestamp = 0;
let increment = 1;

for (let bus = 1; bus < buses.length; bus++) {
    increment *= buses[bus - 1].busId;
    timestamp = nextTimestamp(timestamp, increment, buses[bus]);
    console.log(`nextTimestamp = ${timestamp}, ${increment} ${JSON.stringify(buses[bus])}`);
}

console.log("Answer:", timestamp);
console.timeEnd("part2");