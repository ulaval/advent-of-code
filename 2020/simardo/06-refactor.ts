// https://github.com/simardo/adventofcode2020/tree/main/src/06

console.log('6 décembre');

// part 1
function doPart1(input: string): void {
    const groups: string[] = input.split('\n\n');

    const r: number = groups.reduce((a,g)=> {
        const answ: Set<string> = g.split('\n').reduce((aa, gg) => {
            [...gg].forEach(ss => aa.add(ss));
            return aa;
        }, new Set<string>());

        return answ.size + a;
    }, 0);

    console.log(r);
}

doPart1(INPUT);

// part 2
function doPart2(input: string): void {
    const groups: string[] = input.split('\n\n');

    const r: number = groups.reduce((a,g)=> {
        const answ: Set<string> = g.split('\n').reduce((aa, gg) => aa === undefined ? new Set([...gg]) : new Set([...gg].filter(x => aa.has(x))), undefined! as Set<string>);

        return answ.size + a;
    }, 0);

    console.log(r);
}

doPart2(INPUT);
