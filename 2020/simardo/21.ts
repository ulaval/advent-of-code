// https://github.com/simardo/adventofcode2020/tree/main/src/21

console.log('21 décembre');

const ingrRx: RegExp = /(.+)?\(contains(.+)\)/;

type Food = {
    ingredients: Set<string>;
    allergies: Set<string>;
}

function intersection(setA: Set<string>, setB: Set<string>): Set<string> {
    let _intersection = new Set<string>()
    for (let elem of setB) {
        if (setA.has(elem)) {
            _intersection.add(elem)
        }
    }
    return _intersection
}

function difference(setA: Set<string>, setB: Set<string>): Set<string> {
    let _difference = new Set(setA)
    for (let elem of setB) {
        _difference.delete(elem)
    }
    return _difference
}

// part 1
function doPart1(input: string): void {
    const foodRaw = input.split('\n');

    const tableA: { [key: string]: Set<string> } = {};
    const tableI: { [key: string]: Set<string> } = {};
    const foods: Food[] = [];

    foodRaw.map(i => {
        const [, ingr, allg] = i.match(ingrRx)!;

        const ingredients: string[] = ingr.trim().split(' ');
        const allergies: string[] = allg.trim().split(',').map(a => a.trim());

        allergies.forEach(a => {
            let i: Set<string> = tableA[a];
            if (i === undefined) {
                i = new Set();
                tableA[a] = i;
            }

            ingredients.forEach(ii => i.add(ii));
        });

        ingredients.forEach(i => {
            let a: Set<string> = tableI[i];
            if (a === undefined) {
                a = new Set();
                tableI[i] = a;
            }

            allergies.forEach(aa => a.add(aa));
        });

        foods.push({
            ingredients: new Set(ingredients),
            allergies: new Set(allergies)
        })
    });

    for (let i: number = 0; i < foods.length; i++) {
        const f1: Food = foods[i];
        for (let j: number = i + 1; j < foods.length; j++) {
            const f2: Food = foods[j];

            const interI: Set<string> = intersection(f1.ingredients, f2.ingredients);
            const interA: Set<string> = intersection(f1.allergies, f2.allergies);

            Object.entries(tableI).filter(e => !interI.has(e[0])).forEach(e => {
                const [key, value] = e;
                tableI[key] = difference(value, interA);
            });
        }
    }

    const r = Object.entries(tableI).filter(e => e[1].size === 0).reduce((a, e) => {
        const [key] = e;

        let count: number = 0;
        foods.forEach(f => {
            if (f.ingredients.has(key)) {
                count++;
            }
        });

        return a + count;
    }, 0);

    console.log(r);
}

doPart1(INPUT);

// part 2
function doPart2(input: string): void {
    const foodRaw = input.split('\n');

    let tableA: { [key: string]: Set<string> } = {};
    const tableI: { [key: string]: Set<string> } = {};
    const foods: Food[] = [];

    foodRaw.map(i => {
        const [, ingr, allg] = i.match(ingrRx)!;

        const ingredients: string[] = ingr.trim().split(' ');
        const allergies: string[] = allg.trim().split(',').map(a => a.trim());

        allergies.forEach(a => {
            let i: Set<string> = tableA[a];
            if (i === undefined) {
                i = new Set();
                tableA[a] = i;
            }

            ingredients.forEach(ii => i.add(ii));
        });

        ingredients.forEach(i => {
            let a: Set<string> = tableI[i];
            if (a === undefined) {
                a = new Set();
                tableI[i] = a;
            }

            allergies.forEach(aa => a.add(aa));
        });

        foods.push({
            ingredients: new Set(ingredients),
            allergies: new Set(allergies)
        })
    });

    for (let i: number = 0; i < foods.length; i++) {
        const f1: Food = foods[i];
        for (let j: number = i + 1; j < foods.length; j++) {
            const f2: Food = foods[j];

            const interI: Set<string> = intersection(f1.ingredients, f2.ingredients);
            const interA: Set<string> = intersection(f1.allergies, f2.allergies);

            Object.entries(tableI).filter(e => !interI.has(e[0])).forEach(e => {
                const [key, value] = e;
                tableI[key] = difference(value, interA);
            });
        }
    }

    tableA = {};
    Object.entries(tableI).forEach(e => {
        const [ingr, allergies] = e;

        for (let elem of allergies) {
            let allg = tableA[elem];
            if (allg === undefined) {
                allg = new Set();
                tableA[elem] = allg;
            }
            allg.add(ingr);
        }
    });

    while (Object.entries(tableA).find(e => e[1].size > 1)) {
        Object.entries(tableA).filter(e => e[1].size === 1).forEach(e => {
            Object.entries(tableA).filter(ee => ee[0] != e[0]).forEach(ee => {
                const [ingr, allg] = ee;

                tableA[ingr] = difference(allg, e[1]);
            });
        });
    }

    const r: string[] = [];
    Object.keys(tableA).sort().forEach(k => {
        for (let elem of tableA[k]) {
            r.push(elem);
        }
    })
    console.log(r.join(','));
}

doPart2(INPUT);
