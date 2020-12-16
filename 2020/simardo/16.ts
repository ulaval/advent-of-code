// https://github.com/simardo/adventofcode2020/tree/main/src/16

console.log('16 décembre');

const rx: RegExp = /(.+)?:\s(\d+\-\d+)\sor\s(\d+\-\d+)/;

// part 1
function doPart1(input: string): void {
    const doc: string[] = input.split('\n');

    let ticket: number[] | null | undefined;
    let tickets: number[][] = [];
    const ranges: [string, [number, number], [number, number]][] = [];

    doc.filter(l => l).forEach(line => {
        const match = line.match(rx);
        if (match) {
            const [, field, range1, range2] = match;
            const r1: number[] = range1.split('-').map(r => Number.parseInt(r));
            const r2: number[] = range2.split('-').map(r => Number.parseInt(r));
            ranges.push([field, [r1[0], r1[1]], [r2[0], r2[1]]])
        } else if (line === 'your ticket:') {
            ticket = null;
        } else if (line === 'nearby tickets:') {
            //
        } else if (ticket === null) {
            ticket = line.split(',').map(n => Number.parseInt(n));
        } else {
            tickets.push(line.split(',').map(n => Number.parseInt(n)))
        }
    });

    const inRange: (n: number) => boolean = (n => ranges.some(r => {
        const [, range1, range2] = r;
        return (n >= range1[0] && n <= range1[1]) || (n >= range2[0] && n <= range2[1]);
    }));

    const r = tickets.reduce((a, ticket) =>
        a + ticket.reduce((s, n) => inRange(n) ? s : s + n, 0)
        , 0);

    console.log(r);
}

doPart1(INPUT);

// part 2
function doPart2(input: string): void {
    const doc: string[] = input.split('\n');

    let ticket: number[] | null | undefined;
    let tickets: number[][] = [];
    const ranges: [string, [number, number], [number, number]][] = [];

    doc.filter(l => l).forEach(line => {
        const match = line.match(rx);
        if (match) {
            const [, field, range1, range2] = match;
            const r1: number[] = range1.split('-').map(r => Number.parseInt(r));
            const r2: number[] = range2.split('-').map(r => Number.parseInt(r));
            ranges.push([field, [r1[0], r1[1]], [r2[0], r2[1]]])
        } else if (line === 'your ticket:') {
            ticket = null;
        } else if (line === 'nearby tickets:') {
            // tickets = [];
        } else if (ticket === null) {
            ticket = line.split(',').map(n => Number.parseInt(n));
        } else {
            tickets.push(line.split(',').map(n => Number.parseInt(n)))
        }
    });

    const inRange: (n: number) => boolean = (n => ranges.some(r => {
        const [, range1, range2] = r;
        return (n >= range1[0] && n <= range1[1]) || (n >= range2[0] && n <= range2[1]);
    }));

    const inRangeFields: (n: number) => string[] = (n => ranges.filter(r => {
        const [, range1, range2] = r;
        return (n >= range1[0] && n <= range1[1]) || (n >= range2[0] && n <= range2[1]);
    }).map(r => r[0]));

    const valid: number[][] = tickets.filter(t => t.reduce((s, n) => inRange(n) ? s : s + 1, 0) === 0);
    valid.push(ticket!);

    const classes: Set<string>[] = [];

    valid.forEach((ticket, ti) => {
        ticket.forEach((field, i) => {
            if (ti === 0) {
                classes[i] = new Set(inRangeFields(field));
            } else {
                classes[i] = new Set(inRangeFields(field).filter(v => classes[i].has(v)));
            }
        });
    });

    while (!classes.every(c => c.size === 1)) {
        classes.forEach((c, i) => {
            if (c.size === 1) {
                classes.forEach((cc, ii) => {
                    if (ii !== i) {
                        const v: string = c.values().next().value;
                        cc.delete(v);
                    }
                });
            }
        });
    }

    const r = ticket!.reduce((m, f, i) => (classes[i].values().next().value as string).startsWith('departure') ? m * f : m, 1);
    console.log(r);
}

doPart2(INPUT);
