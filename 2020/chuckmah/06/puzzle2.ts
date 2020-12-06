import { input, groupAnswers } from './puzzle1';
import * as _ from 'lodash';


let result = 0;

groupAnswers.forEach(groupAnswer => {
    result += _.intersection.apply(null, groupAnswer).length;
});

console.log(result);