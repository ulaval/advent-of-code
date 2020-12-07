import { parseRule } from "./puzzle1";

test('light red bags contain 1 bright white bag, 2 muted yellow bags. should return good rule', () => {
    expect(JSON.stringify(parseRule('light red bags contain 1 bright white bag, 2 muted yellow bags. '))).toBe(JSON.stringify({
        name: 'light red',
        contains: [
            {
                type: 'bright white',
                quantity: 1
            },
            {
                type: 'muted yellow',
                quantity: 2
            }
        ]
    }));
})

test('muted blue bags contain 3 mirrored tan bags.. should return good rule', () => {
    expect(JSON.stringify(parseRule('muted blue bags contain 3 mirrored tan bags. '))).toBe(JSON.stringify({
        name: 'muted blue',
        contains: [
            {
                type: 'mirrored tan',
                quantity: 3
            }
        ]
    }));
})

test('faded blue bags contain no other bags.. should return good rule', () => {
    expect(JSON.stringify(parseRule('faded blue bags contain no other bags.'))).toBe(JSON.stringify({
        name: 'faded blue',
        contains: [
        ]
    }));
})



test('shiny gold bags contain 1 clear coral bag, 1 muted green bag, 5 muted teal bags, 4 dull olive bags.. should return good rule', () => {
    expect(JSON.stringify(parseRule('shiny gold bags contain 1 clear coral bag, 1 muted green bag, 5 muted teal bags, 4 dull olive bags. '))).toBe(JSON.stringify({
        name: 'shiny gold',
        contains: [
            {
                type: 'clear coral',
                quantity: 1
            },
            {
                type: 'muted green',
                quantity: 1
            },
            {
                type: 'muted teal',
                quantity: 5
            },
            {
                type: 'dull olive',
                quantity: 4
            }
        ]
    }));
})