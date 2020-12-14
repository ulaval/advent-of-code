import * as fs from 'fs';
import * as path from 'path';
import * as _ from 'lodash';


export const input = fs.readFileSync('input.txt', 'utf8').toString().replace(/\r\n/g, '\n');

export const lines = input.split('\n');

export const busIds = (lines: string) => {
    return lines.split(',')
}


type BusIdsWithIndexes = {
    busID: number,
    index: number
}

//'7,13,x,x,59,x,31,19'
export const busIdsWithIndexes = (values: string[]) => {

    return values.reduce((acc: BusIdsWithIndexes[], currentValue: string, index: number) => {
        if (currentValue !== 'x') {
            acc.push({
                busID: Number(currentValue),
                index: index
            })
        }
        return acc
    }, [] as BusIdsWithIndexes[]);
}


export const findFirstTimestamps = (busIdsWithIndexes: BusIdsWithIndexes[]) => {
    let timestamps = 760171380521445;
    while (true) {

        let isPossible = true;
        for (let index = 1; index < busIdsWithIndexes.length; index++) {

            const nextElement: BusIdsWithIndexes = busIdsWithIndexes[index];
            if ((timestamps + nextElement.index) % nextElement.busID !== 0) {
                isPossible = false;
                break;
            }

        }
        if (isPossible) {
            return timestamps;
        }




        //iterate through all timestamps that bus one start 
        // console.log(timestamps + Number(busId[0]));
        timestamps = timestamps + busIdsWithIndexes[0].busID;
    }



}

console.log(findFirstTimestamps(busIdsWithIndexes(busIds(lines[1]))));