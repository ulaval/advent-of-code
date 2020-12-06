import * as fs from 'fs';
import * as path from 'path';
import * as _ from 'lodash';

const input = fs.readFileSync('input.txt', 'utf8').toString().replace(/\r\n/g, '\n');

export const passportsNumbers = input.split('\n');


export const getRow = (passportsNumber: string): number => {
    const passportsNumberRows = passportsNumber.substring(0, 7).split('');
    let resultMin = 0;
    let resultMax = 127;
    passportsNumberRows.forEach((val) => {

        if (val === 'F') {
            //  take the lower half
            resultMin = resultMin;
            resultMax = _.floor((resultMin + resultMax) / 2);

        } else {
            //  take the upper  half
            resultMin = _.ceil((resultMin + resultMax) / 2);
            resultMax = resultMax;

        }
    });

    if (resultMin !== resultMax) {
        throw new Error(`unable to find row! resultMin = ${resultMin} resultMax =${resultMax}`);
    }

    return resultMin
}


export const getComlumn = (passportsNumber: string): number => {
    const passportsNumberColumn = passportsNumber.substring(7, 10).split('');

    let resultMin = 0;
    let resultMax = 7;

    passportsNumberColumn.forEach((val) => {

        if (val === 'L') {
            //  take the lower half
            resultMin = resultMin;
            resultMax = _.floor((resultMin + resultMax) / 2);

        } else {
            //  take the upper  half
            resultMin = _.ceil((resultMin + resultMax) / 2);
            resultMax = resultMax;

        }

    });

    if (resultMin !== resultMax) {
        throw new Error(`unable to find row! resultMin = ${resultMin} resultMax =${resultMax}`);
    }

    return resultMin
}


export const getSeatId = (row: number, column: number): number => {
    return row * 8 + column;
}



export const getPassportsNumberSeatIds = passportsNumbers.map(passportsNumber => {
    return getSeatId(getRow(passportsNumber), getComlumn(passportsNumber));
})



// console.log(`highestSeatId = ${_.max(getPassportsNumberSeatIds)}`);