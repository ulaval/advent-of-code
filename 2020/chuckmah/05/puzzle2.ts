
import { getPassportsNumberSeatIds, getComlumn, getRow, getSeatId } from './puzzle1';
import * as _ from 'lodash';


const sortedPassportsNumberSeatIds = _.orderBy(getPassportsNumberSeatIds)

const min = _.min(getPassportsNumberSeatIds);
const max = _.max(getPassportsNumberSeatIds);

sortedPassportsNumberSeatIds.forEach(passportsNumberSeatId => {

    // si c'est pas de premier ou le dernier siege
    if (passportsNumberSeatId !== min && passportsNumberSeatId !== max) {
        // regarder si c'est le siege plus haut 
        console.log(passportsNumberSeatId);
        if (!_.includes(sortedPassportsNumberSeatIds, passportsNumberSeatId + 1)) {
            console.log(`siege = ${passportsNumberSeatId + 1}`);
        } else if (!_.includes(sortedPassportsNumberSeatIds, passportsNumberSeatId - 1)) {
            console.log(`siege = ${passportsNumberSeatId - 1}`);
        }
    }

})





