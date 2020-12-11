import Axios from 'axios'

import * as Constants from '~/constants'

export default (nickname, id = null) => {
    return new Promise((resolve, reject) => {
        Axios.get(Constants.API_INITIALIZE, {
            params: id === null ? { nickname } : { nickname, id },
        })
            .then(response => {
                resolve({
                    type: Constants.ACTION_INITIALIZE,
                    data: {
                        nickname: response.data.nickname,
                        id: response.data.id,
                        rating: response.data.rating,
                        score: 0,
                        over: false,
                    },
                })
            })
            .catch(exception => {
                reject(exception)
            })
    })
}
