import * as fs from 'fs';
import * as path from 'path';
import * as _ from 'lodash';

export const input = fs.readFileSync('input.txt', 'utf8').toString().replace(/\r\n/g, '\n');

export const lines = input.split('\n');
export const timestamps = Number(lines[0]);


export const busIds = (lines: string) => {
    return lines.split(',').filter(busId => busId !== 'x').map(busId => Number(busId)).sort();
}


export const busIdOfTheEarliest = (timestamps: number, busIds: number[]): number => {

    let nextTimeStamps = busIds.map(busId => (timestamps - (timestamps % busId)) + busId);

    let earliestBusId = _.min(nextTimeStamps);
    if (earliestBusId) {
        let indexOfEaliestBusId = nextTimeStamps.indexOf(earliestBusId!);
        return (nextTimeStamps[indexOfEaliestBusId] - timestamps) * busIds[indexOfEaliestBusId];
    }

    throw new Error('!');

}

console.log(busIdOfTheEarliest(timestamps, busIds(lines[1])));
