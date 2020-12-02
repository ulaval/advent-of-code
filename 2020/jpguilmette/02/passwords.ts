import { readFileSync } from "fs";

let counter: number = 0;
const data = readFileSync("./input.txt", "utf8");
data.split("\n").forEach((str) => {
  const splitString: string[] = str.replace(new RegExp("[:]"), "").split(" ");

  const min: number = +splitString[0].substring(0, splitString[0].indexOf("-"));
  const max: number = +splitString[0].substring(
    splitString[0].indexOf("-") + 1
  );
  const occurrence: number = (
    splitString[2].match(new RegExp(splitString[1], "g")) || []
  ).length;
  if (min <= occurrence && occurrence <= max) counter++;
});

console.log(counter);

counter = 0;

data.split("\n").forEach((str) => {
  const splitString: string[] = str.replace(new RegExp("[:]"), "").split(" ");

  const pos1: number = +splitString[0].substring(
    0,
    splitString[0].indexOf("-")
  );
  const pos2: number = +splitString[0].substring(
    splitString[0].indexOf("-") + 1
  );
  const passwordArray: string = splitString[2];
  if (
    (passwordArray[pos1 - 1] === splitString[1]) !==
    (passwordArray[pos2 - 1] === splitString[1])
  )
    counter++;
});

console.log(counter);
