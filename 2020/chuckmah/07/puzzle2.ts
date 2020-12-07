import { parseRules, Rules } from './puzzle1';
import * as _ from 'lodash';


console.log(Object.keys(parseRules()).length);

}

export const countNumberBag = (bagName: string, rules: Rules): number => {
    let numberBag = 1;

    const bagNameRule = rules[bagName];
    if (bagNameRule.contains.length > 0) {
        bagNameRule.contains.forEach(bagNameRuleContain => {

            numberBag += countNumberBag(bagNameRuleContain.type, rules) * bagNameRuleContain.quantity;
        })
    }


    return numberBag;
}

console.log(countNumberBag('shiny gold', parseRules()) - 1);