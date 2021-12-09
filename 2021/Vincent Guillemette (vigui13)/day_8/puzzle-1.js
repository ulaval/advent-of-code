const convertInput = require('../input-converter');

convertInput(__dirname, (x) =>
    x.split('|').map((x) => x.split(' ').filter((x) => !!x))
).then((input) => {
    const count = input.reduce((a, c) => {
        a += c[1].filter((o) => [2, 4, 3, 7].includes(o.length)).length;
        return a;
    }, 0);

    console.log(count);
});
