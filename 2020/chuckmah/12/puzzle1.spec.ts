// import { getAdjacentSeats } from "./puzzle1";

import { runCoordinates } from "./puzzle1";

const input = [
    'F10',
    'N3',
    'F7',
    'R90',
    'F11',
]




test('given the input , correct output!', () => {
    expect(runCoordinates(input)).toStrictEqual({
        x: 17,
        y: 8
    });
})
