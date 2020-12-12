import * as fs from 'fs';
import * as path from 'path';
import * as _ from 'lodash';
import { coordinates } from './puzzle1';



export type Waypoint = {
    x: number,
    y: number
}

export const runCoordinates = (coordinates: string[]) => {
    let waypoint: Waypoint = {
        x: 10,
        y: 1
    };

    let position: {
        x: number,
        y: number
    } = {
        x: 0,
        y: 0
    };



    // let currentDirection = 'E';
    coordinates.forEach(coordinate => {
        let action = coordinate.substring(0, 1);
        let unit = Number(coordinate.substring(1));

        switch (action) {
            case 'N':
                //Action N means to move north by the given value.
                waypoint.y += unit;
                break;
            case 'S':
                //Action S means to move south by the given value.
                waypoint.y -= unit;
                break;
            case 'E':
                //Action E means to move east by the given value.
                waypoint.x += unit;
                break;
            case 'W':
                //Action W means to move west by the given value.
                waypoint.x -= unit;
                break;
            case 'L':

                //     //Action L means to turn left the given number of degrees.
                waypoint = rotateWaypoint(waypoint, unit, true);

                break;
            case 'R':
                //Action R means to turn right the given number of degrees.
                waypoint = rotateWaypoint(waypoint, unit, false);

                break;
            case 'F':
                //Action F means to move forward to the waypoint a number of times equal to the given value.
                position = {
                    x: position.x + (unit * waypoint.x),
                    y: position.y + (unit * waypoint.y)
                }
                break;
            default:
                break;
        }

    });

    return {
        x: Math.abs(position.x),
        y: Math.abs(position.y),
    };
}


//https://flexbooks.ck12.org/cbook/ck-12-interactive-middle-school-math-8-for-ccss/section/1.10/primary/lesson/rotations-on-the-coordinate-plane-msm8-ccss
const rotateWaypoint = (currentWaypoint: Waypoint, deg: number, counterclockwize: boolean): Waypoint => {
    if (!counterclockwize) {
        switch (deg) {
            case 90:
                return {
                    x: currentWaypoint.y,
                    y: -currentWaypoint.x
                }
                break;
            case 180:
                return {
                    x: -currentWaypoint.x,
                    y: -currentWaypoint.y
                }
                break;
            case 270:
                return {
                    x: -currentWaypoint.y,
                    y: currentWaypoint.x
                }
                break;
            default:
                break;
        }
    } else {
        switch (deg) {
            case 90:
                return {
                    x: -currentWaypoint.y,
                    y: currentWaypoint.x
                }
                break;
            case 180:
                return {
                    x: -currentWaypoint.x,
                    y: -currentWaypoint.y
                }
                break;
            case 270:
                return {
                    x: currentWaypoint.y,
                    y: -currentWaypoint.x
                }
                break;
            default:
                break;
        }
    }

    throw new Error('!');

}

//console.log(changeDirection('E', 90, false));
let result = runCoordinates(coordinates);
console.log(result.x + result.y);