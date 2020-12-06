// https://github.com/simardo/adventofcode2020/tree/main/src/06

console.log('6 décembre');

// part 1
function doPart1(input: string): void {
    const groups: string[] = input.split('\n');
    groups.push('');
    const group: Set<string>[] = [];
    while (groups.length > 0) {
        const ginfo: string[] = groups.splice(0, groups.indexOf('') + 1);

        const answ: Set<string> = ginfo.reduce((a, p) => {
            const s: string[] = [...p];
            s.forEach(ss => a.add(ss));
            return a;
        }, new Set<string>());

        group.push(answ);
    }
    const r: number = group.reduce((a, p) => p.size + a, 0);
    console.log(r);
}

doPart1(INPUT);

// part 2
function doPart2(input: string): void {
    const groups: string[] = input.split('\n');
    groups.push('');
    const group: Set<string>[] = [];
    while (groups.length > 0) {
        const pinfo: string[] = groups.splice(0, groups.indexOf('') + 1);

        const passport: Set<string> = pinfo.reduce((a, p) => {
            if (p === '') {
                return a;
            }
            return a === undefined ? new Set([...p]) : new Set([...p].filter(x => a.has(x)));
        }, undefined! as Set<string>);

        group.push(passport);
    }
    const r: number = group.reduce((a, p) => p.size + a, 0);
    console.log(r);
}

doPart2(INPUT);
