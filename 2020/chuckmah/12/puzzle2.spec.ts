import { runCoordinates } from "./puzzle2";

const input1 = [
    'F10'
]

//F10 moves the ship to the waypoint 10 times (a total of 100 units east and 10 units north),
// leaving the ship at east 100, north 10. The waypoint stays 10 units east and 1 unit north of the ship.
test('given the input , correct output!', () => {
    expect(runCoordinates(input1)).toStrictEqual({
        x: 100,
        y: 10
    });
})


const input2 = [
    'F10',
    'N3'
]

//F10 moves the ship to the waypoint 10 times (a total of 100 units east and 10 units north),
// leaving the ship at east 100, north 10. The waypoint stays 10 units east and 1 unit north of the ship.
test('given the input2 , correct output!', () => {
    expect(runCoordinates(input2)).toStrictEqual({
        x: 100,
        y: 10
    });
})



const input3 = [
    'F10',
    'N3',
    'F7'
]

//F10 moves the ship to the waypoint 10 times (a total of 100 units east and 10 units north),
// leaving the ship at east 100, north 10. The waypoint stays 10 units east and 1 unit north of the ship.
test('given the input3 , correct output!', () => {
    expect(runCoordinates(input3)).toStrictEqual({
        x: 170,
        y: 38
    });
})


const input4 = [
    'F10',
    'N3',
    'F7',
    'R90',
    'F11'
]

//F10 moves the ship to the waypoint 10 times (a total of 100 units east and 10 units north),
// leaving the ship at east 100, north 10. The waypoint stays 10 units east and 1 unit north of the ship.
test('given the input4 , correct output!', () => {
    expect(runCoordinates(input4)).toStrictEqual({
        x: 214,
        y: 72
    });
})
