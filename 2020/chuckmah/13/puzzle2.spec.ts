// import { getAdjacentSeats } from "./puzzle1";

import { busIds, busIdsWithIndexes, findFirstTimestamps } from "./puzzle2";


const input1 = busIds('7,13,x,x,59,x,31,19');


test('given the input , correct output!', () => {
    expect(findFirstTimestamps(busIdsWithIndexes(input1))).toStrictEqual(1068781);
})

const input2 = busIds('1789,37,47,1889');


test('given the input , correct output!', () => {
    expect(findFirstTimestamps(busIdsWithIndexes(input2))).toStrictEqual(1202161486);
})

