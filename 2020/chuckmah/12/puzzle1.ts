import * as fs from 'fs';
import * as path from 'path';
import * as _ from 'lodash';

export const input = fs.readFileSync('input.txt', 'utf8').toString().replace(/\r\n/g, '\n');

export const coordinates = input.split('\n');


export const runCoordinates = (coordinates: string[]) => {
    let result: {
        x: number,
        y: number
    } = {
        x: 0,
        y: 0
    };



    let currentDirection = 'E';
    coordinates.forEach(coordinate => {
        let action = coordinate.substring(0, 1);
        let unit = Number(coordinate.substring(1));

        switch (action) {
            case 'N':
                //Action N means to move north by the given value.
                result.y += unit;
                break;
            case 'S':
                //Action S means to move south by the given value.
                result.y -= unit;
                break;
            case 'E':
                //Action E means to move east by the given value.
                result.x += unit;
                break;
            case 'W':
                //Action W means to move west by the given value.
                result.x -= unit;
                break;
            case 'L':

                //Action L means to turn left the given number of degrees.
                currentDirection = changeDirection(currentDirection, unit, true);
                break;
            case 'R':
                //Action R means to turn right the given number of degrees.
                currentDirection = changeDirection(currentDirection, unit, false);

                break;
            case 'F':
                switch (currentDirection) {
                    case 'N':
                        //Action N means to move north by the given value.
                        result.y += unit;
                        break;
                    case 'S':
                        //Action S means to move south by the given value.
                        result.y -= unit;
                        break;
                    case 'E':
                        //Action E means to move east by the given value.
                        result.x += unit;
                        break;
                    case 'W':
                        //Action W means to move west by the given value.
                        result.x -= unit;
                        break;

                    default:
                        break;
                }
                break;
            default:
                break;
        }

    });

    return {
        x: Math.abs(result.x),
        y: Math.abs(result.y),
    };
}


let possibleDirections = ['E', 'S', 'W', 'N'];
const changeDirection = (currentDirection: string, deg: number, counterclockwize: boolean): string => {
    let currentDirectionIndex = possibleDirections.indexOf(currentDirection);
    let unitDeg = 0;
    switch (deg) {
        case 90:
            unitDeg = 1;
            break;
        case 180:
            unitDeg = 2;
            break;
        case 270:
            unitDeg = 3;
            break;

        default:
            break;
    }

    if (counterclockwize) {
        //counterclockwise
        unitDeg = -Math.abs(unitDeg);
    }


    return possibleDirections[(((currentDirectionIndex + unitDeg) % possibleDirections.length) + possibleDirections.length) % possibleDirections.length];

}

//console.log(changeDirection('E', 90, false));
// let result = runCoordinates(coordinates);
// console.log(result.x + result.y);