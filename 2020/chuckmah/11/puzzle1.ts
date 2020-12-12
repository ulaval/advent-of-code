import * as fs from 'fs';
import * as path from 'path';
import * as _ from 'lodash';

export const input = fs.readFileSync('input.txt', 'utf8').toString().replace(/\r\n/g, '\n');

export const numbers = input.split('\n').map(s => Number(s));


export const applySeatingRules = (seats: string[][]): string[] => {

    //the following rules are applied to every seat simultaneously:
    let results = [...seats];

    for (let row = 0; row < seats.length; row++) {
        const rowSeats = seats[row];
        for (let column = 0; column < rowSeats.length; column++) {
            const seat = rowSeats[column];
            if(seat !== '.'){
            const adjacentSeats = getAdjacentSeats(seats, row, column);

            //If a seat is empty (L) and there are no occupied seats adjacent to it, the seat becomes occupied.
            if (seat === 'L' && !adjacentSeats.includes('L')) {
                results[row][column] = '#';
            }
            //If a seat is occupied (#) and four or more seats adjacent to it are also occupied, the seat becomes empty.
            if (seat === '#' && _.countBy(adjacentSeats, '#') >= 4) {
                results[row][column] = 'L';
            }
            //Otherwise, the seat's state does not change.
            }

        }

    }

    return results;


}

export const getAdjacentSeats = (seats: string[][], row: number, column: number): string[] => {
    let adjacentSeats = [];
    //get left and right row in the same row
    if (column - 1 >= 0) {
        adjacentSeats.push(seats[row][column - 1]);
    }
    if (column + 1 < seats[row].length) {
        adjacentSeats.push(seats[row][column + 1]);
    }

    //get the seat in the upper row
    if (row - 1 >= 0) {
        adjacentSeats.push(seats[row - 1][column]);
        //get left and right row in the upper row
        if (column - 1 >= 0) {
            adjacentSeats.push(seats[row - 1][column - 1]);
        }
        if (column + 1 < seats[row - 1].length) {
            adjacentSeats.push(seats[row - 1][column + 1]);
        }
    }

    //get the seat in the upper row
    if (row + 1 < seats.length) {
        adjacentSeats.push(seats[row + 1][column]);

        //get left and right row in the upper row
        if (column - 1 >= 0) {
            adjacentSeats.push(seats[row + 1][column - 1]);
        }
        if (column + 1 < seats[row + 1].length) {
            adjacentSeats.push(seats[row + 1][column + 1]);
        }

    }

    return adjacentSeats;
}