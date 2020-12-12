import { group } from "console";

import fs from 'fs';

const groups: string[][][] = fs.readFileSync(__dirname + '/data-6.txt', 'utf8').split('\n\n').map(
    group => group.split('\n')
        .map(person => person.split('')));

console.log(groups
    .map(group => group.flat(1))
    .map(group => new Set(group))
    .map(group => group.size)
    .reduce((sum, count) => sum + count, 0));

const intersection = <T>(a: Set<T>, b: Set<T>) => new Set([...a].filter(x => b.has(x)));

console.log(groups
    .map(group => group.map(person => new Set(person))
        .reduce((result: Set<string> | undefined, person) => {
            if (result === undefined) { return person; }
            return intersection(result, person);
        }, undefined))
    .map(group => group?.size || 0)
    .reduce((sum, count) => sum + count, 0));
