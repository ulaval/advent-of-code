const convertInput = require('../input-converter');

convertInput(__dirname, (x) => {
    const rawAxis = x.split(' ')[0];
    const rawValue = parseInt(x.split(' ')[1]);

    const axis = ['up', 'down'].includes(rawAxis) ? 'y' : 'x';
    const value =
        axis === 'x' ? rawValue : rawAxis === 'up' ? rawValue * -1 : rawValue;

    return {
        x: axis === 'x' ? value : 0,
        y: axis === 'y' ? value : 0,
    };
}).then((nav) => {
    const trajectory = nav.reduce(
        (a, c) => {
            a.x += c.x;
            a.y += c.y;
            return a;
        },
        { x: 0, y: 0 }
    );
    console.log(trajectory.x * trajectory.y);
});
