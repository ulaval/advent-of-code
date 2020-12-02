import { readFileSync, read } from "fs";

const data = readFileSync("./input.txt", "utf8");
const inputArray: string[] = data.split("\n");

inputArray.some((numberA, index, array) => {
  const residualArray = array.slice(index + 1);
  return residualArray.some((numberB) => {
    if (parseInt(numberA) + parseInt(numberB) === 2020) {
      console.log(parseInt(numberA) * parseInt(numberB));
      return true;
    }

    return false;
  });
});

inputArray.some((numberA, indexA, arrayA) => {
  const residualArrayA = arrayA.slice(indexA + 1);
  return residualArrayA.some((numberB, indexB, arrayB) => {
    const residualArrayB = arrayB.slice(indexB + 1);
    return residualArrayB.some((numberC) => {
      if (parseInt(numberA) + parseInt(numberB) + parseInt(numberC) === 2020) {
        console.log(parseInt(numberA) * parseInt(numberB) * parseInt(numberC));
        return true;
      }

      return false;
    });
  });
});
