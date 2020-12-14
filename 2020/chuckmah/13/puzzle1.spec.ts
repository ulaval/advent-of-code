// import { getAdjacentSeats } from "./puzzle1";

import { busIdOfTheEarliest, busIds } from "./puzzle1";


const input1 = busIds('7,13,x,x,59,x,31,19');
const timestamps = 939;

test('given the input , correct output!', () => {
    expect(busIdOfTheEarliest(timestamps, input1)).toStrictEqual(295);
})
